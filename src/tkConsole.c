
/*
 * tkConsole.c --
 *
 *	This file implements a TCL console for systems that may not
 *	otherwise have access to a console.  It uses the Text widget
 *	and provides special access via a console command.
 *
 * Copyright (c) 1995-1996 Sun Microsystems, Inc.
 *
 * See the file "license.terms" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 * SCCS: @(#) tkConsole.c 1.55 98/01/02 17:40:37
 */

#include "config.h"
#undef USE_TK_STUBS
#undef USE_TCL_STUBS
#include "blt.h"
#include <tcl.h>
#include <tk.h>
#include <locale.h>
#include <stdio.h>
#ifdef HAVE_STRING_H
#include <string.h>
#endif

#define _VERSION(a,b,c)	    (((a) << 16) + ((b) << 8) + (c))

#define _TCL_VERSION _VERSION(TCL_MAJOR_VERSION, TCL_MINOR_VERSION, TCL_RELEASE_SERIAL)
#define _TK_VERSION _VERSION(TK_MAJOR_VERSION, TK_MINOR_VERSION, TK_RELEASE_SERIAL)

#if (_TCL_VERSION < _VERSION(8,2,0))

/*
 * A data structure of the following type holds information for each console
 * which a handler (i.e. a TCL command) has been defined for a particular
 * top-level window.
 */

typedef struct {
    Tcl_Interp *consoleInterp;	/* Interpreter for the console. */
    Tcl_Interp *interp;		/* Interpreter to send console commands. */
} ConsoleInfo;

static Tcl_Interp *gStdoutInterp = NULL;

#if (_TCL_VERSION < _VERSION(8,1,0))
#define HAVE_BROKEN_LIB_PATH 1
#undef HAVE_UTF
#endif

#if (_TCL_VERSION >= _VERSION(8,1,1)) 
#define HAVE_UTF 1
extern void TclInitSubsystems _ANSI_ARGS_((const char *argv0));
#else 
#endif

/*
 * Forward declarations for procedures defined later in this file:
 *
 * The first three will be used in the tk app shells...
 */

extern Tcl_AppInitProc Blt_ConsoleInit;
extern void Blt_ConsoleCreate _ANSI_ARGS_((void));

static Tcl_CmdDeleteProc ConsoleDeleteProc;
static Tcl_CmdProc ConsoleCmd;
static Tcl_CmdProc InterpreterCmd;
static Tk_EventProc ConsoleEventProc;

static void ConsolePrint _ANSI_ARGS_((Tcl_Interp *interp, int devId, 
	const char *buffer, long size));

static int ConsoleInput _ANSI_ARGS_((ClientData instanceData, char *buf, 
	int toRead, int *errorCode));
static int ConsoleOutput _ANSI_ARGS_((ClientData instanceData, char *buf, 
	int toWrite, int *errorCode));
static int ConsoleClose _ANSI_ARGS_((ClientData instanceData,
	Tcl_Interp *interp));
static void ConsoleWatch _ANSI_ARGS_((ClientData instanceData, int mask));
static int ConsoleHandle _ANSI_ARGS_((ClientData instanceData, int direction, 
	ClientData *handlePtr));

/*
 * This structure describes the channel type structure for file based IO:
 */

static Tcl_ChannelType consoleChannelType =
{
    "console",			/* Type name. */
    NULL,			/* Always non-blocking.*/
    ConsoleClose,		/* Close proc. */
    ConsoleInput,		/* Input proc. */
    ConsoleOutput,		/* Output proc. */
    NULL,			/* Seek proc. */
    NULL,			/* Set option proc. */
    NULL,			/* Get option proc. */
    ConsoleWatch,		/* Watch for events on console. */
    ConsoleHandle,		/* Get a handle from the device. */
};

/*
 *---------------------------------------------------------------------------
 *
 * Blt_ConsoleCreate --
 *
 * 	Create the console channels and install them as the standard
 * 	channels.  All I/O will be discarded until Blt_ConsoleInit is
 * 	called to attach the console to a text widget.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Creates the console channel and installs it as the standard
 *	channels.
 *
 *---------------------------------------------------------------------------
 */

void
Blt_ConsoleCreate()
{
    Tcl_Channel channel;

#ifdef HAVE_UTF
    TclInitSubsystems(NULL);
#endif
    channel = Tcl_CreateChannel(&consoleChannelType, "console0",
	(ClientData)TCL_STDIN, TCL_READABLE);
    if (channel != NULL) {
	Tcl_SetChannelOption(NULL, channel, "-translation", "lf");
	Tcl_SetChannelOption(NULL, channel, "-buffering", "none");
#ifdef HAVE_UTF
	Tcl_SetChannelOption(NULL, channel, "-encoding", "utf-8");
#endif
    }
    Tcl_SetStdChannel(channel, TCL_STDIN);
    channel = Tcl_CreateChannel(&consoleChannelType, "console1",
	(ClientData)TCL_STDOUT, TCL_WRITABLE);
    if (channel != NULL) {
	Tcl_SetChannelOption(NULL, channel, "-translation", "lf");
	Tcl_SetChannelOption(NULL, channel, "-buffering", "none");
#ifdef HAVE_UTF
	Tcl_SetChannelOption(NULL, channel, "-encoding", "utf-8");
#endif
    }
    Tcl_SetStdChannel(channel, TCL_STDOUT);
    channel = Tcl_CreateChannel(&consoleChannelType, "console2",
	(ClientData)TCL_STDERR, TCL_WRITABLE);
    if (channel != NULL) {
	Tcl_SetChannelOption(NULL, channel, "-translation", "lf");
	Tcl_SetChannelOption(NULL, channel, "-buffering", "none");
#ifdef HAVE_UTF
	Tcl_SetChannelOption(NULL, channel, "-encoding", "utf-8");
#endif
    }
    Tcl_SetStdChannel(channel, TCL_STDERR);
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_ConsoleInit --
 *
 *	Initialize the console.  This code actually creates a new
 *	application and associated interpreter.  This effectivly hides
 *	the implementation from the main application.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	A new console it created.
 *
 *---------------------------------------------------------------------------
 */

int
Blt_ConsoleInit(interp)
    Tcl_Interp *interp;		/* Interpreter to use for prompting. */
{
    Tcl_Interp *consoleInterp;
    ConsoleInfo *info;
    Tk_Window tkMain = Tk_MainWindow(interp);

#ifdef MAC_TCL
    static char initCmd[] = "source -rsrc {Console}";
#else
    static char initCmd[] = "source $tk_library/console.tcl";
#endif

    consoleInterp = Tcl_CreateInterp();
    if (consoleInterp == NULL) {
	goto error;
    } 
#if defined(HAVE_BROKEN_LIB_PATH) && defined(TCLLIBPATH)
    Tcl_SetVar(consoleInterp, "tclDefaultLibrary", 
	       TCLLIBPATH, TCL_GLOBAL_ONLY);
#endif
    /*
     * Initialized TCL and Tk.
     */
    if (Tcl_Init(consoleInterp) != TCL_OK) {
	goto error;
    }
    if (Tk_Init(consoleInterp) != TCL_OK) {
	goto error;
    }
    gStdoutInterp = interp;

    /*
     * Add console commands to the interp
     */
    info = Tcl_Alloc(sizeof(ConsoleInfo));
    info->interp = interp;
    info->consoleInterp = consoleInterp;
    Tcl_CreateCommand(interp, "console", ConsoleCmd, info,
	(Tcl_CmdDeleteProc *)ConsoleDeleteProc);
    Tcl_CreateCommand(consoleInterp, "consoleinterp", InterpreterCmd, info, 
	(Tcl_CmdDeleteProc *)NULL);

    Tk_CreateEventHandler(tkMain, StructureNotifyMask, ConsoleEventProc, info);

    Tcl_Preserve(consoleInterp);
    if (Tcl_Eval(consoleInterp, initCmd) == TCL_ERROR) {
	/* goto error; -- no problem for now... */
	printf("Eval error: %s", consoleInterp->result);
    }
    Tcl_Release((ClientData)consoleInterp);
    return TCL_OK;

  error:
    if (consoleInterp != NULL) {
	Tcl_DeleteInterp(consoleInterp);
    }
    return TCL_ERROR;
}

/*
 *---------------------------------------------------------------------------
 *
 * ConsolePrint --
 *
 *	Prints to the give text to the console.  Given the main interp
 *	this functions find the appropiate console interp and forwards
 *	the text to be added to that console.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *---------------------------------------------------------------------------
 */

static void
ConsolePrint(interp, devId, buffer, size)
    Tcl_Interp *interp;		/* Main interpreter. */
    int devId;			/* TCL_STDOUT for stdout, TCL_STDERR for
                                 * stderr. */
    const char *buffer;		/* Text buffer. */
    long size;			/* Size of text buffer. */
{
    Tcl_DString command, output;
    Tcl_CmdInfo cmdInfo;
    char *cmd;
    ConsoleInfo *info;
    Tcl_Interp *consoleInterp;
    int result;

    if (interp == NULL) {
	return;
    }
    if (devId == TCL_STDERR) {
	cmd = "tkConsoleOutput stderr ";
    } else {
	cmd = "tkConsoleOutput stdout ";
    }

    result = Tcl_GetCommandInfo(interp, "console", &cmdInfo);
    if (result == 0) {
	return;
    }
    info = (ConsoleInfo *) cmdInfo.clientData;

    Tcl_DStringInit(&output);
    Tcl_DStringAppend(&output, buffer, size);

    Tcl_DStringInit(&command);
    Tcl_DStringAppend(&command, cmd, strlen(cmd));
    Tcl_DStringAppendElement(&command, output.string);

    consoleInterp = info->consoleInterp;
    Tcl_Preserve((ClientData)consoleInterp);
    Tcl_Eval(consoleInterp, command.string);
    Tcl_Release((ClientData)consoleInterp);

    Tcl_DStringFree(&command);
    Tcl_DStringFree(&output);
}

/*
 *---------------------------------------------------------------------------
 *
 * ConsoleOutput--
 *
 *	Writes the given output on the IO channel. Returns count of how
 *	many characters were actually written, and an error indication.
 *
 * Results:
 *	A count of how many characters were written is returned and an
 *	error indication is returned in an output argument.
 *
 * Side effects:
 *	Writes output on the actual channel.
 *
 *---------------------------------------------------------------------------
 */

static int
ConsoleOutput(instanceData, buf, toWrite, errorCode)
    ClientData instanceData;	/* Indicates which device to use. */
    char *buf;			/* The data buffer. */
    int toWrite;		/* How many bytes to write? */
    int *errorCode;		/* Where to store error code. */
{
    *errorCode = 0;
    Tcl_SetErrno(0);

    if (gStdoutInterp != NULL) {
	ConsolePrint(gStdoutInterp, (int)instanceData, buf, toWrite);
    }
    return toWrite;
}

/*
 *---------------------------------------------------------------------------
 *
 * ConsoleInput --
 *
 *	Read input from the console.  Not currently implemented.
 *
 * Results:
 *	Always returns EOF.
 *
 * Side effects:
 *	None.
 *
 *---------------------------------------------------------------------------
 */

 /* ARGSUSED */
static int
ConsoleInput(instanceData, buf, bufSize, errorCode)
    ClientData instanceData;	/* Not Used.. */
    char *buf;			/* Where to store data read. */
    int bufSize;		/* How much space is available
                                         * in the buffer? */
    int *errorCode;		/* Where to store error code. */
{
    return 0;			/* Always return EOF. */
}

/*
 *---------------------------------------------------------------------------
 *
 * ConsoleClose --
 *
 *	Closes the IO channel.
 *
 * Results:
 *	Always returns 0 (success).
 *
 * Side effects:
 *	Frees the dummy file associated with the channel.
 *
 *---------------------------------------------------------------------------
 */

 /* ARGSUSED */
static int
ConsoleClose(instanceData, interp)
    ClientData instanceData;	/* Not Used.. */
    Tcl_Interp *interp;		/* Not Used.. */
{
    return 0;
}

/*
 *---------------------------------------------------------------------------
 *
 * ConsoleWatch --
 *
 *	Called by the notifier to set up the console device so that
 *	events will be noticed. Since there are no events on the
 *	console, this routine just returns without doing anything.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *---------------------------------------------------------------------------
 */

 /* ARGSUSED */
static void
ConsoleWatch(instanceData, mask)
    ClientData instanceData;	/* Device ID for the channel. */
    int mask;			/* OR-ed combination of
                                         * TCL_READABLE, TCL_WRITABLE and
                                         * TCL_EXCEPTION, for the events
                                         * we are interested in. */
{
}

/*
 *---------------------------------------------------------------------------
 *
 * ConsoleHandle --
 *
 *	Invoked by the generic IO layer to get a handle from a channel.
 *	Because console channels are not devices, this function always
 *	fails.
 *
 * Results:
 *	Always returns TCL_ERROR.
 *
 * Side effects:
 *	None.
 *
 *---------------------------------------------------------------------------
 */

 /* ARGSUSED */
static int
ConsoleHandle(instanceData, direction, handlePtr)
    ClientData instanceData;	/* Device ID for the channel. */
    int direction;		/* TCL_READABLE or TCL_WRITABLE to indicate
				 * which direction of the channel is being
				 * requested. */
    ClientData *handlePtr;	/* Where to store handle */
{
    return TCL_ERROR;
}

/*
 *---------------------------------------------------------------------------
 *
 * ConsoleCmd --
 *
 *	The console command implements a TCL interface to the various console
 *	options.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *---------------------------------------------------------------------------
 */

static int
ConsoleCmd(clientData, interp, argc, argv)
    ClientData clientData;	/* Not used. */
    Tcl_Interp *interp;		/* Current interpreter. */
    int argc;			/* Number of arguments. */
    char **argv;		/* Argument strings. */
{
    ConsoleInfo *info = (ConsoleInfo *) clientData;
    char c;
    int length;
    int result;
    Tcl_Interp *consoleInterp;

    if (argc < 2) {
	Tcl_AppendResult(interp, "wrong # args: should be \"", argv[0],
	    " option ?arg arg ...?\"", (char *)NULL);
	return TCL_ERROR;
    }
    c = argv[1][0];
    length = strlen(argv[1]);
    result = TCL_OK;
    consoleInterp = info->consoleInterp;
    Tcl_Preserve(consoleInterp);
    if ((c == 't') && (strncmp(argv[1], "title", length)) == 0) {
	Tcl_DString dString;

	Tcl_DStringInit(&dString);
	Tcl_DStringAppend(&dString, "wm title . ", -1);
	if (argc == 3) {
	    Tcl_DStringAppendElement(&dString, argv[2]);
	}
	Tcl_Eval(consoleInterp, Tcl_DStringValue(&dString));
	Tcl_DStringFree(&dString);
    } else if ((c == 'h') && (strncmp(argv[1], "hide", length)) == 0) {
	Tcl_Eval(info->consoleInterp, "wm withdraw .");
    } else if ((c == 's') && (strncmp(argv[1], "show", length)) == 0) {
	Tcl_Eval(info->consoleInterp, "wm deiconify .");
    } else if ((c == 'e') && (strncmp(argv[1], "eval", length)) == 0) {
	if (argc == 3) {
	    Tcl_Eval(info->consoleInterp, argv[2]);
	} else {
	    Tcl_AppendResult(interp, "wrong # args: should be \"", argv[0],
		" eval command\"", (char *)NULL);
	    return TCL_ERROR;
	}
    } else {
	Tcl_AppendResult(interp, "bad option \"", argv[1],
	    "\": should be hide, show, or title",
	    (char *)NULL);
	result = TCL_ERROR;
    }
    Tcl_Release(consoleInterp);
    return result;
}

/*
 *---------------------------------------------------------------------------
 *
 * InterpreterCmd --
 *
 *	This command allows the console interp to communicate with the
 *	main interpreter.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	None.
 *
 *---------------------------------------------------------------------------
 */

static int
InterpreterCmd(clientData, interp, argc, argv)
    ClientData clientData;	/* Not used. */
    Tcl_Interp *interp;		/* Current interpreter. */
    int argc;			/* Number of arguments. */
    char **argv;		/* Argument strings. */
{
    ConsoleInfo *info = (ConsoleInfo *) clientData;
    char c;
    int length;
    int result;
    Tcl_Interp *otherInterp;

    if (argc < 2) {
	Tcl_AppendResult(interp, "wrong # args: should be \"", argv[0],
	    " option ?arg arg ...?\"", (char *)NULL);
	return TCL_ERROR;
    }
    c = argv[1][0];
    length = strlen(argv[1]);
    otherInterp = info->interp;
    Tcl_Preserve(otherInterp);
    if ((c == 'e') && (strncmp(argv[1], "eval", length)) == 0) {
	result = Tcl_GlobalEval(otherInterp, argv[2]);
	Tcl_AppendResult(interp, otherInterp->result, (char *)NULL);
    } else if ((c == 'r') && (strncmp(argv[1], "record", length)) == 0) {
	Tcl_RecordAndEval(otherInterp, argv[2], TCL_EVAL_GLOBAL);
	result = TCL_OK;
	Tcl_AppendResult(interp, otherInterp->result, (char *)NULL);
    } else {
	Tcl_AppendResult(interp, "bad option \"", argv[1],
	    "\": should be eval or record",
	    (char *)NULL);
	result = TCL_ERROR;
    }
    Tcl_Release(otherInterp);
    return result;
}

/*
 *---------------------------------------------------------------------------
 *
 * ConsoleDeleteProc --
 *
 *	If the console command is deleted we destroy the console window
 *	and all associated data structures.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	A new console it created.
 *
 *---------------------------------------------------------------------------
 */

void
ConsoleDeleteProc(clientData)
    ClientData clientData;
{
    ConsoleInfo *info = (ConsoleInfo *) clientData;

    Tcl_DeleteInterp(info->consoleInterp);
    info->consoleInterp = NULL;
}

/*
 *---------------------------------------------------------------------------
 *
 * ConsoleEventProc --
 *
 *	This event procedure is registered on the main window of the
 *	slave interpreter.  If the user or a running script causes the
 *	main window to be destroyed, then we need to inform the console
 *	interpreter by invoking "tkConsoleExit".
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Invokes the "tkConsoleExit" procedure in the console interp.
 *
 *---------------------------------------------------------------------------
 */

static void
ConsoleEventProc(ClientData clientData, XEvent *eventPtr)
{
    ConsoleInfo *info = clientData;
    Tcl_Interp *consoleInterp;

    if (eventPtr->type == DestroyNotify) {
	consoleInterp = info->consoleInterp;

	/*
         * It is possible that the console interpreter itself has
         * already been deleted. In that case the consoleInterp
         * field will be set to NULL. If the interpreter is already
         * gone, we do not have to do any work here.
         */

	if (consoleInterp == (Tcl_Interp *)NULL) {
	    return;
	}
	Tcl_Preserve(consoleInterp);
	Tcl_Eval(consoleInterp, "tkConsoleExit");
	Tcl_Release(consoleInterp);
    }
}

#endif /* _TCL_VERSION >= 8.2.0 */
