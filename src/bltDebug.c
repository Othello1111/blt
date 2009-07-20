
/*
 * bltDebug.c --
 *
 *	Copyright 1993-1998 George A Howlett.
 *
 *	Permission is hereby granted, free of charge, to any person obtaining
 *	a copy of this software and associated documentation files (the
 *	"Software"), to deal in the Software without restriction, including
 *	without limitation the rights to use, copy, modify, merge, publish,
 *	distribute, sublicense, and/or sell copies of the Software, and to
 *	permit persons to whom the Software is furnished to do so, subject to
 *	the following conditions:
 *
 *	The above copyright notice and this permission notice shall be
 *	included in all copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *	LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *	OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *	WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "bltInt.h"

#ifndef NO_BLTDEBUG

#define DEBUG_THREAD_KEY "BLT Debug Command Data"
#define MAX_STACK 2048

#ifdef TIME_WITH_SYS_TIME
#include <sys/time.h>
#include <time.h>
#else
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#else
#include <time.h>
#endif /* HAVE_SYS_TIME_H */
#endif /* TIME_WITH_SYS_TIME */

#include "bltChain.h"

static Tcl_CmdObjTraceProc DebugProc;
static Tcl_ObjCmdProc DebugCmd;

typedef struct {
    const char *pattern;
    Tcl_Obj *nameObjPtr;
} Watch;

typedef struct {
    Blt_Chain chain; 	/* Chain of watches. */
    Tcl_Interp *interp;
    unsigned char *stack;
} DebugCmdInterpData;

#define SETBIT(i) \
    dataPtr->stack[(i) >> 3] |= (1 << ((i) & 0x07))
#define GETBIT(i) \
    (dataPtr->stack[(i) >> 3] & (1 << ((i) & 0x07)))
#define UNSETBIT(i) \
    dataPtr->stack[(i) >> 3] &= ~(1 << ((i) & 0x07))

/*
 *---------------------------------------------------------------------------
 *
 * DebugInterpDeleteProc --
 *
 *	This is called when the interpreter hosting the "debug" command
 *	is deleted.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Removes the hash table managing all debug names.
 *
 *---------------------------------------------------------------------------
 */
/* ARGSUSED */
static void
DebugInterpDeleteProc(
    ClientData clientData,	/* Interpreter-specific data. */
    Tcl_Interp *interp)
{
    DebugCmdInterpData *dataPtr = clientData;

    /* All debug instances should already have been destroyed when
     * their respective TCL commands were deleted. */
    Blt_Chain_Destroy(dataPtr->chain);
    Tcl_DeleteAssocData(interp, DEBUG_THREAD_KEY);
    Blt_Free(dataPtr->stack);
    Blt_Free(dataPtr);
}

/*
 *---------------------------------------------------------------------------
 *
 * GetDebugCmdInterpData --
 *
 *---------------------------------------------------------------------------
 */
static DebugCmdInterpData *
GetDebugCmdInterpData(Tcl_Interp *interp)
{
    DebugCmdInterpData *dataPtr;
    Tcl_InterpDeleteProc *proc;

    dataPtr = (DebugCmdInterpData *)
	Tcl_GetAssocData(interp, DEBUG_THREAD_KEY, &proc);
    if (dataPtr == NULL) {
	dataPtr = Blt_AssertMalloc(sizeof(DebugCmdInterpData));
	dataPtr->interp = interp;
	Tcl_SetAssocData(interp, DEBUG_THREAD_KEY, DebugInterpDeleteProc,
		 dataPtr);
	dataPtr->chain = Blt_Chain_Create();
	dataPtr->stack = Blt_Malloc(MAX_STACK);
    }
    return dataPtr;
}

static Watch *
GetWatch(DebugCmdInterpData *dataPtr, Tcl_Obj *objPtr)
{
    Blt_ChainLink link;
    char c;
    Watch *watchPtr;
    char *name, *string;

    name = Tcl_GetString(objPtr);
    c = name[0];
    for (link = Blt_Chain_FirstLink(dataPtr->chain); link != NULL;
	link = Blt_Chain_NextLink(link)) {
	watchPtr = Blt_Chain_GetValue(link);
	string = Tcl_GetString(watchPtr->nameObjPtr);
	if ((string[0] == c) && (strcmp(name, string) == 0)) {
	    return watchPtr;
	}
    }
    link = Blt_Chain_AllocLink(sizeof(Watch));
    watchPtr = Blt_Chain_GetValue(link);
    watchPtr->nameObjPtr = objPtr;
    Tcl_IncrRefCount(objPtr);
    /* Prepend watch onto chain. */
    Blt_Chain_LinkBefore(dataPtr->chain, link, (Blt_ChainLink)NULL);
    return watchPtr;
}

static void
DeleteWatch(DebugCmdInterpData *dataPtr, Tcl_Obj *objPtr)
{
    Blt_ChainLink link;
    char c;
    char *name;

    name = Tcl_GetString(objPtr);
    c = name[0];
    for (link = Blt_Chain_FirstLink(dataPtr->chain); link != NULL;
	link = Blt_Chain_NextLink(link)) {
	Watch *watchPtr;
	char *string;

	watchPtr = Blt_Chain_GetValue(link);
	string = Tcl_GetString(watchPtr->nameObjPtr);
	if ((string[0] == c) && (strcmp(name, string) == 0)) {
	    Tcl_DecrRefCount(watchPtr->nameObjPtr);
	    Blt_Chain_DeleteLink(dataPtr->chain, link);
	    return;
	}
    }
}

/*ARGSUSED*/
static int
DebugProc(
    ClientData clientData,	/* Interpreter-specific data. */
    Tcl_Interp *interp,		/* Not used. */
    int level,			/* Current level */
    const char *command,	/* Command before substitution */
    Tcl_Command token,		/* Not used. */
    int objc,
    Tcl_Obj *const *objv)	/* Command after parsing, but before
				 * evaluation */
{
    DebugCmdInterpData *dataPtr = clientData;
    Tcl_Channel errChannel;
    Tcl_DString dString;
    const char *lineStart;
    const char *string;
    char prompt[200];
    int count;
    const char *p;
    int i;
    Tcl_Obj *listObjPtr, *objPtr;

    /* This is pretty crappy, but there's no way to trigger stack pops */
    for (i = level + 1; i < MAX_STACK; i++) {
	UNSETBIT(i);
    }
    if (Blt_Chain_GetLength(dataPtr->chain) > 0) {
	int found;
	Blt_ChainLink link;

	found = FALSE;
	for (link = Blt_Chain_FirstLink(dataPtr->chain); 
	     link != NULL; link = Blt_Chain_NextLink(link)) {
	    Watch *watchPtr;
	    const char *cmd, *pattern;

	    watchPtr = Blt_Chain_GetValue(link);
	    cmd = Tcl_GetString(objv[0]);
	    pattern = Tcl_GetString(watchPtr->nameObjPtr);
	    if (Tcl_StringMatch(cmd, pattern)) {
		found = TRUE;
		break;
	    }
	}
	if ((found) && (level < MAX_STACK)) {
	    SETBIT(level), SETBIT(level + 1);
	}
	if ((level >= MAX_STACK) || (!GETBIT(level))) {
	    return TCL_OK;
	}
    }
    /*
     * Use stderr channel, for compatibility with systems that don't have a
     * tty (like WIN32).  In reality, it doesn't make a difference since Tk's
     * Win32 console can't handle large streams of data anyways.
     */
    errChannel = Tcl_GetStdChannel(TCL_STDERR);
    if (errChannel == NULL) {
	Tcl_AppendResult(interp, "can't get stderr channel", (char *)NULL);
	Tcl_BackgroundError(interp);
	return TCL_ERROR;
    }
    Tcl_DStringInit(&dString);

    sprintf_s(prompt, 200, "%-2d-> ", level);
    p = command;
    /* Skip leading spaces in command line. */
    while(isspace(UCHAR(*p))) {
	p++;
    }
    lineStart = p;
    count = 0;
    while (*p != '\0') {
	if (*p == '\n') {
	    if (count > 0) {
		Tcl_DStringAppend(&dString, "     ", -1);
	    } else {
		Tcl_DStringAppend(&dString, prompt, -1);
	    }
	    Tcl_DStringAppend(&dString, lineStart, p - lineStart);
	    Tcl_DStringAppend(&dString, "\n", -1);
	    p++;
	    lineStart = p;
	    count++;
	    if (count > 6) {
		break;		/* Stop after 6 lines. */
	    }
	} else {
	    p++;
	}
    }   
    while (isspace(UCHAR(*lineStart))) {
	lineStart++;
    }
    if (lineStart < p) {
	if (count > 0) {
	    Tcl_DStringAppend(&dString, "     ", -1);
	} else {
	    Tcl_DStringAppend(&dString, prompt, -1);
	}
	Tcl_DStringAppend(&dString, lineStart, p - lineStart);
	if (count <= 6) {
	    Tcl_DStringAppend(&dString, "\n", -1);
	}
    }
    if (count > 6) {
	Tcl_DStringAppend(&dString, "     ...\n", -1);
    }
    listObjPtr = Tcl_NewListObj(objc, objv);
    Tcl_IncrRefCount(listObjPtr);
#ifdef notdef
    objPtr = Tcl_SubstObj(interp, listObjPtr, TCL_SUBST_VARIABLES);
#else
    objPtr = NULL;
#endif
    if (objPtr == NULL) {
	string = Tcl_GetString(listObjPtr);
    } else {
	Tcl_IncrRefCount(objPtr);
	string = Tcl_GetString(objPtr);
    }
    lineStart = string;
    sprintf_s(prompt, 200, "  <- ");
    count = 0;
    for (p = string; *p != '\0'; /* empty */) {
	if (*p == '\n') {
	    if (count > 0) {
		Tcl_DStringAppend(&dString, "     ", -1);
	    } else {
		Tcl_DStringAppend(&dString, prompt, -1);
	    }
	    count++;
	    Tcl_DStringAppend(&dString, lineStart, p - lineStart);
	    Tcl_DStringAppend(&dString, "\n", -1);
	    p++;
	    lineStart = p;
	    if (count > 6) {
		break;
	    }
	} else {
	    p++;
	}
    }   
    if (lineStart < p) {
	if (count > 0) {
	    Tcl_DStringAppend(&dString, "     ", -1);
	} else {
	    Tcl_DStringAppend(&dString, prompt, -1);
	}
	Tcl_DStringAppend(&dString, lineStart, p - lineStart);
	if (count <= 6) {
	    Tcl_DStringAppend(&dString, "\n", -1);
	}
    }
    if (count > 6) {
	Tcl_DStringAppend(&dString, "      ...\n", -1);
    }
    Tcl_DStringAppend(&dString, "\n", -1);
    Tcl_DecrRefCount(listObjPtr);
    if (objPtr != NULL) {
	Tcl_DecrRefCount(objPtr);
    }
    Tcl_Write(errChannel, (char *)Tcl_DStringValue(&dString), -1);
    Tcl_Flush(errChannel);
    Tcl_DStringFree(&dString);
    return TCL_OK;
}

/*ARGSUSED*/
static int
DebugCmd(
    ClientData clientData,	/* Not used. */
    Tcl_Interp *interp,
    int objc,
    Tcl_Obj *const *objv)
{
    Blt_ChainLink link;
    DebugCmdInterpData *dataPtr = clientData;
    Tcl_Obj *listObjPtr;
    Watch *watchPtr;
    const char *string;
    char c;
    int newLevel;
    int i;
    int length;
    static Tcl_Trace token;
    static int level;

    if (objc == 1) {
	Tcl_SetIntObj(Tcl_GetObjResult(interp), level);
	return TCL_OK;
    }
    string = Tcl_GetStringFromObj(objv[1], &length);
    c = string[0];
    if ((c == 'w') && (strncmp(string, "watch", length) == 0)) {
	/* Add patterns of command names to watch to the chain */
	for (i = 2; i < objc; i++) {
	    GetWatch(dataPtr, objv[i]);
	}
    } else if ((c == 'i') && (strncmp(string, "ignore", length) == 0)) {
	for (i = 2; i < objc; i++) {
	    DeleteWatch(dataPtr, objv[i]);
	}
    } else {
	goto levelTest;
    }
    /* Return the current watch patterns */
    listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
    for (link = Blt_Chain_FirstLink(dataPtr->chain); link != NULL;
	link = Blt_Chain_NextLink(link)) {
	watchPtr = Blt_Chain_GetValue(link);
	Tcl_ListObjAppendElement(interp, listObjPtr, watchPtr->nameObjPtr);
    }
    Tcl_SetObjResult(interp, listObjPtr);
    return TCL_OK;

  levelTest:
    if (Tcl_GetBooleanFromObj(interp, objv[1], &newLevel) == TCL_OK) {
	if (newLevel > 0) {
	    newLevel = 10000;	/* Max out the level */
	}
    } else if (Tcl_GetIntFromObj(interp, objv[1], &newLevel) == TCL_OK) {
	if (newLevel < 0) {
	    newLevel = 0;
	}
    } else {
	return TCL_ERROR;
    }
    if (token != 0) {
	Tcl_DeleteTrace(interp, token);
    }
    if (newLevel > 0) {
	token = Tcl_CreateObjTrace(interp, newLevel, 0, DebugProc, 
				   dataPtr, NULL);
    }
    level = newLevel;
    Tcl_SetIntObj(Tcl_GetObjResult(interp), level);
    return TCL_OK;
}

int
Blt_DebugCmdInitProc(Tcl_Interp *interp)
{
    static Blt_InitCmdSpec cmdSpec = {"debug", DebugCmd,};

    cmdSpec.clientData = GetDebugCmdInterpData(interp);
    return Blt_InitCmd(interp, "::blt", &cmdSpec);
}

#endif /* NO_BLTDEBUG */
