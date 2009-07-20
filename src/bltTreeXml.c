
/*
 *
 * bltTreeXml.c --
 *
 *	Copyright 1998-2005 George A Howlett.
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

#include <blt.h>

#include "config.h"
#include <tcl.h>

#include <bltSwitch.h>
#include <bltAssert.h>
#include <bltAlloc.h>
#include <bltTree.h>
#include <string.h>

#ifdef HAVE_CTYPE_H
#  include <ctype.h>
#endif /* HAVE_CTYPE_H */

#define TRUE 	1
#define FALSE 	0
/*
 * The macro below is used to modify a "char" value (e.g. by casting
 * it to an unsigned character) so that it can be used safely with
 * macros such as isspace.
 */
#define UCHAR(c) ((unsigned char) (c))

DLLEXPORT extern Tcl_AppInitProc Blt_TreeXmlInit;

static Blt_TreeImportProc ImportXmlProc;
static Blt_TreeExportProc ExportXmlProc;

extern char *Blt_Itoa(int);

/*
 * Format	Import		Export
 * xml		file/data	file/data
 * html		file/data	file/data
 *
 * $tree import xml $node fileName -data dataString 
 * $table export xml $node -file defaultFileName 
 * $tree import html $node -file fileName -data dataString 
 * $table export html $node -file defaultFileName 
 */

/*
 * ImportSwitches --
 */
typedef struct {
    Tcl_Obj *fileObj;	/* Name of file representing the channel. */
    Tcl_Obj *dataObj;
    Tcl_Interp *interp;
    unsigned int flags;
    Blt_TreeNode root;
} ImportSwitches;

#define IMPORT_TRIMCDATA  (1<<0)
#define IMPORT_OVERWRITE  (1<<1)

#define IMPORT_ATTRIBUTES (1<<2)
#define IMPORT_BASEURI    (1<<3)
#define IMPORT_CDATA	  (1<<4)
#define IMPORT_COMMENTS	  (1<<5)
#define IMPORT_DTD        (1<<6)
#define IMPORT_LOCATION   (1<<7)
#define IMPORT_PI         (1<<8)
#define IMPORT_NS         (1<<9)
#define IMPORT_ALL	  (IMPORT_ATTRIBUTES | IMPORT_COMMENTS | IMPORT_CDATA |\
			   IMPORT_DTD |	IMPORT_PI | IMPORT_LOCATION | \
			   IMPORT_BASEURI)

#define SYM_BASEURI       "#baseuri"
#define SYM_BYTEIDX       "#byteindex"
#define SYM_CDATA         "#cdata"
#define SYM_COLNO         "#column"
#define SYM_COMMENT       "#comment"
#define SYM_LINENO        "#line"
#define SYM_NS		  "#namespace"
#define SYM_NOTATION      "#notation"
#define SYM_PI            "#pi"
#define SYM_PUBID         "#publicid"
#define SYM_SYSID         "#systemid"

extern Blt_SwitchParseProc Blt_TreeNodeSwitchProc;

static Blt_SwitchCustom nodeSwitch = {
    Blt_TreeNodeSwitchProc, NULL, (ClientData)0,
};

static Blt_SwitchSpec importSwitches[] = 
{
    {BLT_SWITCH_BITMASK,   "-all",		"",
	Blt_Offset(ImportSwitches, flags),	0, IMPORT_ALL},
    {BLT_SWITCH_BOOLEAN,   "-comments",		"bool",
	Blt_Offset(ImportSwitches, flags),	0, IMPORT_COMMENTS},
    {BLT_SWITCH_OBJ,      "-data",		"data",
	Blt_Offset(ImportSwitches, dataObj),	0, 0},
    {BLT_SWITCH_OBJ,      "-file",		"fileName",
	Blt_Offset(ImportSwitches, fileObj),	0, 0},
    {BLT_SWITCH_BOOLEAN,  "-locations",		"bool",
	Blt_Offset(ImportSwitches, flags),	0, IMPORT_LOCATION},
    {BLT_SWITCH_CUSTOM,   "-root",		"node",
	Blt_Offset(ImportSwitches, root),	0, 0, &nodeSwitch},
    {BLT_SWITCH_BOOLEAN,  "-attributes",	"bool",
	Blt_Offset(ImportSwitches, flags),	0, IMPORT_ATTRIBUTES},
    {BLT_SWITCH_BOOLEAN,  "-namespace",		"bool",
	Blt_Offset(ImportSwitches, flags),	0, IMPORT_NS},
    {BLT_SWITCH_BOOLEAN,  "-cdata",		"bool",
	Blt_Offset(ImportSwitches, flags),	0, IMPORT_CDATA},
    {BLT_SWITCH_BOOLEAN,   "-overwrite",	"bool",
	Blt_Offset(ImportSwitches, flags),	0, IMPORT_OVERWRITE},
    {BLT_SWITCH_BOOLEAN,   "-processinginstructions",  "bool",
	Blt_Offset(ImportSwitches, flags),	0, IMPORT_PI},
    {BLT_SWITCH_BOOLEAN,   "-trimwhitespace",	"bool",
	Blt_Offset(ImportSwitches, flags),	0, IMPORT_TRIMCDATA},
    {BLT_SWITCH_END}
};

/*
 * ExportSwitches --
 */
typedef struct {
    Tcl_Obj *fileObj;
    Tcl_Obj *dataObj;
    Blt_TreeNode root;

    /* Private fields. */
    Tcl_Interp *interp;
    unsigned int flags;
    Tcl_Channel channel;	/* If non-NULL, channel to write output to. */
    Tcl_DString *dsPtr;
} ExportSwitches;

static Blt_SwitchSpec exportSwitches[] = 
{
    {BLT_SWITCH_OBJ, "-data", "data",
	Blt_Offset(ExportSwitches, dataObj), 0, 0},
    {BLT_SWITCH_OBJ, "-file", "fileName",
	Blt_Offset(ExportSwitches, fileObj), 0, 0},
    {BLT_SWITCH_END}
};

#ifdef HAVE_LIBEXPAT
#include <expat.h>

typedef struct {
    Blt_Tree tree;
    Blt_TreeNode root;
    Blt_TreeNode parent;
    Tcl_Interp *interp;
    int flags;
    Blt_HashTable stringTable;
    XML_Parser parser;
} ImportData;


static Tcl_Obj *
GetStringObj(ImportData *importPtr, const char *string)
{
    Blt_HashEntry *hPtr;
    int isNew;

    hPtr = Blt_CreateHashEntry(&importPtr->stringTable, string, &isNew);
    if (isNew) {
	Tcl_Obj *objPtr;

	objPtr = Tcl_NewStringObj(string, -1);
	Tcl_IncrRefCount(objPtr);
	Blt_SetHashValue(hPtr, objPtr);
	return objPtr;
    }
    return Blt_GetHashValue(hPtr);
}

static const char *
GetBaseUri(ImportData *importPtr, Blt_TreeNode node)
{
    Blt_TreeNode top;

    top = Blt_Tree_ParentNode(importPtr->root);
    do {
	if (Blt_Tree_ValueExists(importPtr->tree, node, SYM_BASEURI)) {
	    Tcl_Obj *objPtr;

	    if (Blt_Tree_GetValue((Tcl_Interp *)NULL, importPtr->tree, node, 
			SYM_BASEURI, &objPtr) == TCL_OK) {
		return Tcl_GetString(objPtr);
	    }
	}
	node = Blt_Tree_ParentNode(node);
    } while (node != top);
    return NULL;
}

static void
SetLocation(ImportData *importPtr, Blt_TreeNode node)
{
    Blt_Tree_SetValue(importPtr->interp, importPtr->tree, node, SYM_LINENO, 
	Tcl_NewIntObj(XML_GetCurrentLineNumber(importPtr->parser)));
    Blt_Tree_SetValue(importPtr->interp, importPtr->tree, node, SYM_COLNO, 
	Tcl_NewIntObj(XML_GetCurrentColumnNumber(importPtr->parser)));
    Blt_Tree_SetValue(importPtr->interp, importPtr->tree, node, SYM_BYTEIDX, 
	Tcl_NewLongObj(XML_GetCurrentByteIndex(importPtr->parser)));
}

static void
GetNotationProc(
    void *userData,
    const XML_Char *notationName,
    const XML_Char *base,
    const XML_Char *systemId,
    const XML_Char *publicId)
{
    ImportData *importPtr = userData;

    if (publicId != NULL) {
	Blt_Tree_SetValue(importPtr->interp, importPtr->tree, 
		importPtr->parent, SYM_PUBID, Tcl_NewStringObj(publicId, -1));
    }
    if (systemId != NULL) {
	Blt_Tree_SetValue(importPtr->interp, importPtr->tree, 
		importPtr->parent, SYM_SYSID, Tcl_NewStringObj(systemId, -1));
    } 
    if (base != NULL) {
	Blt_Tree_SetValue(importPtr->interp, importPtr->tree, 
		importPtr->parent, SYM_BASEURI, Tcl_NewStringObj(base, -1));
    }
    if (notationName != NULL) {
	Blt_Tree_SetValue(importPtr->interp, importPtr->tree, 
		importPtr->parent, SYM_NOTATION, 
		Tcl_NewStringObj(notationName, -1));
    }
}

static void
GetCommentProc(void *userData, const XML_Char *string) 
{
    ImportData *importPtr = userData;

    if ((importPtr->flags & IMPORT_DTD) == 0) {
	Blt_Tree tree;
	Blt_TreeNode child;
	Tcl_Obj *objPtr;

	tree = importPtr->tree;
	objPtr = GetStringObj(importPtr, string);
	child = Blt_Tree_CreateNode(tree, importPtr->parent, SYM_COMMENT, -1);
	Blt_Tree_SetValue(importPtr->interp, tree, child, SYM_COMMENT, objPtr);
	if (importPtr->flags & IMPORT_LOCATION) {
	    SetLocation(importPtr, child);
	}
    }
}

static void
GetProcessingInstructionProc(
    void *userData, 
    const char *target, 
    const char *data)
{
    ImportData *importPtr = userData;

    if ((importPtr->flags & IMPORT_DTD) == 0) {
	Tcl_Obj *objPtr;
	Blt_Tree tree;
	Blt_TreeNode child;

	tree = importPtr->tree;
	objPtr = GetStringObj(importPtr, data);
	child = Blt_Tree_CreateNode(tree, importPtr->parent, SYM_PI, -1);
	Blt_Tree_SetValue(importPtr->interp, tree, child, target, objPtr);
	if (importPtr->flags & IMPORT_LOCATION) {
	    SetLocation(importPtr, child);
	}
    }
}

static void
GetCharacterDataProc(void *userData, const XML_Char *string, int length) 
{
    ImportData *importPtr = userData;
    Blt_Tree tree;
    Blt_TreeNode child;
    Tcl_Obj *objPtr;

    if (importPtr->flags & IMPORT_TRIMCDATA) {
	const char *p, *pend;

	for (p = string, pend = p + length; p < pend; p++) {
	    if (!isspace(UCHAR(*p))) {
		break;
	    }
	}
	if (p == pend) {
	    return;
	}
	length = pend - p;
	string = p;
    }
    tree = importPtr->tree;
    child = Blt_Tree_LastChild(importPtr->parent);
    if ((child != NULL) && (strcmp(Blt_Tree_NodeLabel(child), SYM_CDATA)==0)) {

	/* Last child added was a CDATA node, append new data to it.  */
	
	if (Blt_Tree_GetValue(importPtr->interp, tree, child, SYM_CDATA, 
		&objPtr) == TCL_OK) {
	    Tcl_AppendToObj(objPtr, string, length);
	    return;
	}
    } 
    objPtr = Tcl_NewStringObj(string, length);
    child = Blt_Tree_CreateNode(tree, importPtr->parent, SYM_CDATA,-1);
    Blt_Tree_SetValue(importPtr->interp, tree, child, SYM_CDATA, objPtr);
    if (importPtr->flags & IMPORT_LOCATION) {
	SetLocation(importPtr, child);
    }
}

static void
DumpStringTable(Blt_HashTable *tablePtr)
{
    Blt_HashEntry *hPtr;
    Blt_HashSearch iter;

    for (hPtr = Blt_FirstHashEntry(tablePtr, &iter); hPtr != NULL;
	 hPtr = Blt_NextHashEntry(&iter)) {
	Tcl_Obj *objPtr;

	objPtr = Blt_GetHashValue(hPtr);
	Tcl_DecrRefCount(objPtr);
    }
    Blt_DeleteHashTable(tablePtr);
}

static void
StartDocTypeProc(
    void       *userData,
    const char *doctypeName,
    const char *systemId,
    const char *publicId,
    int         has_internal_subset)
{   
    ImportData *importPtr = userData;

    if (publicId != NULL) {
	Blt_Tree_SetValue(importPtr->interp, importPtr->tree, importPtr->root, 
		SYM_PUBID, Tcl_NewStringObj(publicId, -1));
    }
    if (systemId != NULL) {
	Blt_Tree_SetValue(importPtr->interp, importPtr->tree, importPtr->root, 
		SYM_SYSID, Tcl_NewStringObj(systemId, -1));
    } 
    importPtr->flags |= IMPORT_DTD;
}

static void
EndDocTypeProc(void *userData)
{
    ImportData *importPtr = userData;

    importPtr->flags &= ~IMPORT_DTD;
}



static void
StartElementProc(void *userData, const char *element, const char **attr) 
{
    Blt_TreeNode child;
    ImportData *importPtr = userData;
    Blt_Tree tree;

    tree = importPtr->tree;
    child = NULL;
    if (importPtr->flags & IMPORT_OVERWRITE) {
	child = Blt_Tree_FindChild(importPtr->parent, element);
    }
    if (child == NULL) {
	child = Blt_Tree_CreateNode(tree, importPtr->parent, element, -1);
    }
    if (importPtr->flags & IMPORT_ATTRIBUTES) {
	const char **p;

	for (p = attr; *p != NULL; p += 2) {
	    Tcl_Obj *objPtr;
	    
	    objPtr = GetStringObj(importPtr, *(p+1));
	    Blt_Tree_SetValue(importPtr->interp, tree, child, *p, objPtr);
	}
    }
    if (importPtr->flags & IMPORT_LOCATION) {
	SetLocation(importPtr, child);
    }
    if (importPtr->flags & IMPORT_BASEURI) {
	const char *oldBase, *newBase;

	newBase = XML_GetBase(importPtr->parser);
	oldBase = GetBaseUri(importPtr, importPtr->parent);
	assert(oldBase != NULL);
	if (strcmp(oldBase, newBase) != 0) {
	    Blt_Tree_SetValue(importPtr->interp, tree, importPtr->parent, 
		SYM_BASEURI, Tcl_NewStringObj(newBase, -1));
	}
    }
    importPtr->parent = child;	/* Increase depth.  */
}

static void
EndElementProc(void *userData, const char *element) 
{
    ImportData *importPtr = userData;

    importPtr->parent = Blt_Tree_ParentNode(importPtr->parent);
}

static int
ReadXmlFromFile(
    Tcl_Interp *interp, 
    XML_Parser parser, 
    const char *fileName)
{
    int closeChannel;
    int done;
    Tcl_Channel channel;

    closeChannel = TRUE;
    if ((fileName[0] == '@') && (fileName[1] != '\0')) {
	int mode;
	
	channel = Tcl_GetChannel(interp, fileName+1, &mode);
	if (channel == NULL) {
	    return FALSE;
	}
	if ((mode & TCL_READABLE) == 0) {
	    Tcl_AppendResult(interp, "channel \"", fileName, 
		"\" not opened for reading", (char *)NULL);
	    return FALSE;
	}
	closeChannel = FALSE;
    } else {
	channel = Tcl_OpenFileChannel(interp, fileName, "r", 0);
	if (channel == NULL) {
	    return FALSE;	/* Can't open dump file. */
	}
    }
    done = FALSE;
    while (!done) {
	int length;
#define BUFFSIZE	8191
	char buffer[BUFFSIZE+1];
	
	length = Tcl_Read(channel, buffer, sizeof(char) * BUFFSIZE);
	if (length < 0) {
	    Tcl_AppendResult(interp, "\nread error: ", Tcl_PosixError(interp),
			     (char *)NULL);
	    if (closeChannel) {
		Tcl_Close(interp, channel);
	    }
	    return FALSE;
	}
	done = Tcl_Eof(channel);
	if (!XML_Parse(parser, buffer, length, done)) {
	    Tcl_AppendResult(interp, "\n", fileName, ":",
			Blt_Itoa(XML_GetCurrentLineNumber(parser)), ": ",
			"error: ", 
			XML_ErrorString(XML_GetErrorCode(parser)), 
			(char *)NULL);
	    Tcl_AppendResult(interp, "\n", fileName, ":",
			Blt_Itoa(XML_GetCurrentByteIndex(parser)), ": ",
			"error: ", 
			XML_ErrorString(XML_GetErrorCode(parser)), 
			(char *)NULL);
	    fprintf(stderr, "buffer=%.*s\n", XML_GetCurrentByteIndex(parser), 
		    buffer);
	    if (closeChannel) {
		Tcl_Close(interp, channel);
	    }
	    return FALSE;
	}
    }
    if (closeChannel) {
	Tcl_Close(interp, channel);
    }
    return TRUE;
}


static int
GetExternalEntityRefProc(
    XML_Parser parser, 
    const XML_Char *context,
    const XML_Char *base,
    const XML_Char *systemId,
    const XML_Char *publicId)
{
    ImportData *importPtr;
    Tcl_DString ds;
    Tcl_Interp *interp;
    XML_Parser newParser, oldParser;
    int result;

    importPtr = XML_GetUserData(parser);
    assert(importPtr != NULL);
    interp = importPtr->interp;
    Tcl_DStringInit(&ds);
    if ((base != NULL) && (Tcl_GetPathType(systemId) == TCL_PATH_RELATIVE)) {
	const char **argv;
	const char **baseNames, **sysIdNames;
	int argc;
	int i, j;
	int nBase, nSysId;

	Tcl_SplitPath(base, &nBase, &baseNames);
	Tcl_SplitPath(systemId, &nSysId, &sysIdNames);
	argc = nBase + nSysId;
	argv = Blt_Malloc(sizeof(char *) * (argc + 1));
	if (argv == NULL) {
	    return FALSE;
	}
	for (i = 0; i < nBase; i++) {
	    argv[i] = baseNames[i];
	}
	for (j = 0; j < nSysId; j++, i++) {
	    argv[i] = sysIdNames[j];
	}
	argv[i] = NULL;
	Tcl_JoinPath(argc, argv, &ds);
	Blt_Free(baseNames);
	Blt_Free(sysIdNames);
	Blt_Free(argv);
    } else {
	Tcl_DStringAppend(&ds, systemId, -1);
    }
    newParser = XML_ExternalEntityParserCreate(parser, context, NULL);
    if (newParser == NULL) {
	Tcl_AppendResult(interp, "can't create external entity ref parser", 
			 (char *)NULL);
	return FALSE;
    }
    oldParser = importPtr->parser;
    importPtr->parser = newParser;
    result = ReadXmlFromFile(interp, newParser, Tcl_DStringValue(&ds));
    importPtr->parser = oldParser;
    Tcl_DStringFree(&ds);
    XML_ParserFree(newParser);
    return result;
}

static int
ImportXmlFile(
    Tcl_Interp *interp, 
    Blt_Tree tree, 
    Blt_TreeNode parent, 
    Tcl_Obj *objPtr,
    unsigned int flags) 
{
    ImportData import;
    XML_Parser parser;
    int result;
    char *fileName;

    if (flags & IMPORT_NS) {
	parser = XML_ParserCreateNS(NULL, ':');
    } else {
	parser = XML_ParserCreate(NULL);
    }
    if (parser == NULL) {
	Tcl_AppendResult(interp, "can't create XML parser", (char *)NULL);
	return TCL_ERROR;
    }
    import.flags = flags;
    import.interp = interp;
    import.parent = parent;
    import.parser = parser;
    import.root = parent;
    import.tree = tree;
    Blt_InitHashTable(&import.stringTable, BLT_STRING_KEYS);
    XML_SetUserData(parser, &import);

    fileName = Tcl_GetString(objPtr);
    /* Set baseURI */
    {
	Tcl_DString ds;
	int argc;
	const char **argv;

	Tcl_DStringInit(&ds);
	Tcl_SplitPath(fileName, &argc, &argv);
	Tcl_JoinPath(argc - 1, argv, &ds);
	XML_SetBase(parser, Tcl_DStringValue(&ds));
	if (flags & IMPORT_BASEURI) {
	    Blt_Tree_SetValue(interp, tree, parent, SYM_BASEURI, 
	       Tcl_NewStringObj(Tcl_DStringValue(&ds), Tcl_DStringLength(&ds)));
	}
	Blt_Free(argv);
	Tcl_DStringFree(&ds);
    }
    XML_SetExternalEntityRefHandler(parser, GetExternalEntityRefProc);
    XML_SetElementHandler(parser, StartElementProc, EndElementProc);
    if (flags & IMPORT_CDATA) {
	XML_SetCharacterDataHandler(parser, GetCharacterDataProc);
    }
    if (flags & IMPORT_BASEURI) {
	XML_SetNotationDeclHandler(parser, GetNotationProc);
	XML_SetDoctypeDeclHandler(parser, StartDocTypeProc, EndDocTypeProc);
    }
    if (flags & IMPORT_PI) {
	XML_SetProcessingInstructionHandler(parser, 
		GetProcessingInstructionProc);
    }
    if (flags & IMPORT_COMMENTS) {
	XML_SetCommentHandler(parser, GetCommentProc);
    }
    result = ReadXmlFromFile(interp, parser, fileName);
    XML_ParserFree(parser);
    DumpStringTable(&import.stringTable);
    return (result) ? TCL_OK : TCL_ERROR;
} 


static int
ImportXmlData(
    Tcl_Interp *interp, 
    Blt_Tree tree, 
    Blt_TreeNode parent, 
    Tcl_Obj *dataObjPtr,
    unsigned int flags) 
{
    ImportData import;
    XML_Parser parser;
    char *string;
    int length;
    int result;

    if (flags & IMPORT_NS) {
	parser = XML_ParserCreateNS(NULL, ':');
    } else {
	parser = XML_ParserCreate(NULL);
    }
    if (parser == NULL) {
	Tcl_AppendResult(interp, "can't create parser", (char *)NULL);
	return TCL_ERROR;
    }
    import.flags = flags;
    import.interp = interp;
    import.parent = parent;
    import.parser = parser;
    import.root = parent;
    import.tree = tree;
    Blt_InitHashTable(&import.stringTable, BLT_STRING_KEYS);
    XML_SetBase(parser, ".");
    XML_SetUserData(parser, &import);
    XML_SetExternalEntityRefHandler(parser, GetExternalEntityRefProc);
    XML_SetElementHandler(parser, StartElementProc, EndElementProc);
    if (flags & IMPORT_CDATA) {
	XML_SetCharacterDataHandler(parser, GetCharacterDataProc);
    }
    if (flags & IMPORT_BASEURI) {
	XML_SetNotationDeclHandler(parser, GetNotationProc);
	XML_SetDoctypeDeclHandler(parser, StartDocTypeProc, EndDocTypeProc);
    }
    if (flags & IMPORT_PI) {
	XML_SetProcessingInstructionHandler(parser, 
		GetProcessingInstructionProc);
    }
    if (flags & IMPORT_COMMENTS) {
	XML_SetCommentHandler(parser, GetCommentProc);
    }
    string = Tcl_GetStringFromObj(dataObjPtr, &length);
    result = XML_Parse(parser, string, length, 1);
    if (!result) {
	Tcl_AppendResult(interp, "\nparse error at line ",
		Blt_Itoa(XML_GetCurrentLineNumber(parser)), ":  ",
		XML_ErrorString(XML_GetErrorCode(parser)),
		(char *)NULL);
    }
    XML_ParserFree(parser);
    DumpStringTable(&import.stringTable);
    return (result) ? TCL_OK : TCL_ERROR;
} 

static int
ImportXmlProc(
    Tcl_Interp *interp, 
    Blt_Tree tree, 
    int objc, 
    Tcl_Obj *const *objv)
{
    int result;
    ImportSwitches switches;

    memset(&switches, 0, sizeof(switches));
    nodeSwitch.clientData = tree;
    switches.root = Blt_Tree_RootNode(tree);
    switches.flags = IMPORT_ATTRIBUTES | IMPORT_CDATA;
    if (Blt_ParseSwitches(interp, importSwitches, objc - 3, objv + 3, 
	&switches, BLT_SWITCH_DEFAULTS) < 0) {
	return TCL_ERROR;
    }
    result = TCL_ERROR;
    if ((switches.dataObj != NULL) && (switches.fileObj != NULL)) {
	Tcl_AppendResult(interp, "can't set both -file and -data switches.",
			 (char *)NULL);
	goto error;
    }
    if (switches.fileObj != NULL) {
	result = ImportXmlFile(interp, tree, switches.root, switches.fileObj, 
		switches.flags);
    } else if (switches.dataObj != NULL) {
	result = ImportXmlData(interp, tree, switches.root, switches.dataObj, 
		switches.flags);
    } else {
	result = TCL_OK;
    }
 error:
    Blt_FreeSwitches(importSwitches, (char *)&switches, 0);
    return result;
}

#endif /* HAVE_LIBEXPAT */

static int
XmlFlush(ExportSwitches *exportPtr) 
{
    int nWritten;
    char *line;
    int length;

    line = Tcl_DStringValue(exportPtr->dsPtr);
    length = Tcl_DStringLength(exportPtr->dsPtr);
    nWritten = Tcl_Write(exportPtr->channel, line, length);
    if (nWritten != length) {
	Tcl_AppendResult(exportPtr->interp, "can't write xml element: ",
		Tcl_PosixError(exportPtr->interp), (char *)NULL);
	return TCL_ERROR;
    }
    Tcl_DStringSetLength(exportPtr->dsPtr, 0);
    return TCL_OK;
}

static void
XmlPutEscapeString(const char *from, size_t length, ExportSwitches *exportPtr)
{
    const char *p, *pend;

    for (p = from, pend = from + length; p < pend; /*empty*/) {
	switch (*p) {
	case '\'': 
	    if (p > from) {
		Tcl_DStringAppend(exportPtr->dsPtr, from, p - from);
	    }
	    from = ++p;
	    Tcl_DStringAppend(exportPtr->dsPtr, "&apos;", 6);
	    break;
	case '&':  
	    if (p > from) {
		Tcl_DStringAppend(exportPtr->dsPtr, from, p - from);
	    }
	    from = ++p;
	    Tcl_DStringAppend(exportPtr->dsPtr, "&amp;", 5);
	    break;
	case '>':  
	    if (p > from) {
		Tcl_DStringAppend(exportPtr->dsPtr, from, p - from);
	    }
	    from = ++p;
	    Tcl_DStringAppend(exportPtr->dsPtr, "&gt;", 4);
	    break; 
	case '<':  
	    if (p > from) {
		Tcl_DStringAppend(exportPtr->dsPtr, from, p - from);
	    }
	    from = ++p;
	    Tcl_DStringAppend(exportPtr->dsPtr, "&lt;", 4);
	    break; 
	case '"':  
	    if (p > from) {
		Tcl_DStringAppend(exportPtr->dsPtr, from, p - from);
	    }
	    from = ++p;
	    Tcl_DStringAppend(exportPtr->dsPtr, "&quot;", 6);
	    break;
	default:  
	    p++;
	    break;
	}
    }	
    if (p > from) {
	Tcl_DStringAppend(exportPtr->dsPtr, from, p - from);
    }
}

static void
XmlOpenStartElement(ExportSwitches *exportPtr, Blt_TreeNode node)
{
    size_t i;

    if (exportPtr->channel != NULL) {
	Tcl_DStringSetLength(exportPtr->dsPtr, 0);
    }
    for (i = 0; i < Blt_Tree_NodeDepth(node); i++) {
	Tcl_DStringAppend(exportPtr->dsPtr, "  ", 2);
    }
    Tcl_DStringAppend(exportPtr->dsPtr, "<", 1);
    Tcl_DStringAppend(exportPtr->dsPtr, Blt_Tree_NodeLabel(node), -1);
}

static int
XmlCloseStartElement(ExportSwitches *exportPtr)
{
    Tcl_DStringAppend(exportPtr->dsPtr, ">\n", 2);
    if (exportPtr->channel != NULL) {
	return XmlFlush(exportPtr);
    }
    return TCL_OK;
}

static int
XmlEndElement(ExportSwitches *exportPtr, Blt_TreeNode node)
{
    size_t i;

    Tcl_DStringAppend(exportPtr->dsPtr, "\n", 1);
    for (i = 0; i < Blt_Tree_NodeDepth(node); i++) {
	Tcl_DStringAppend(exportPtr->dsPtr, "  ", 2);
    }
    Tcl_DStringAppend(exportPtr->dsPtr, "</", 2);
    Tcl_DStringAppend(exportPtr->dsPtr, Blt_Tree_NodeLabel(node), -1);
    Tcl_DStringAppend(exportPtr->dsPtr, ">\n", 2);
    if (exportPtr->channel != NULL) {
	return XmlFlush(exportPtr);
    }
    return TCL_OK;
}

static void
XmlAppendAttribute(
    ExportSwitches *exportPtr, 
    const char *attrName, 
    const char *value, 
    int length)
{
    size_t valueLen;

    if (length < 0) {
	valueLen = strlen(value);
    } else {
	valueLen = (size_t)length;
    }
    Tcl_DStringAppend(exportPtr->dsPtr, " ", 1);
    Tcl_DStringAppend(exportPtr->dsPtr, attrName, -1);
    Tcl_DStringAppend(exportPtr->dsPtr, "=", 1);
    Tcl_DStringAppend(exportPtr->dsPtr, "\"", 1);
    XmlPutEscapeString(value, valueLen, exportPtr);
    Tcl_DStringAppend(exportPtr->dsPtr, "\"", 1);
}

static void
XmlAppendCharacterData(
    ExportSwitches *exportPtr, 
    const char *string, 
    int length)
{
    if (length < 0) {
	length = strlen(string);
    } 
    Tcl_DStringAppend(exportPtr->dsPtr, "CDATA=(", -1);
    XmlPutEscapeString(string, length, exportPtr);
    Tcl_DStringAppend(exportPtr->dsPtr, ")", -1);
}

static int
XmlExportElement(Blt_Tree tree, Blt_TreeNode parent, ExportSwitches *exportPtr)
{
    Blt_TreeKey key;
    Blt_TreeKeyIterator iter;
    Blt_TreeNode child;

    if (strcmp(Blt_Tree_NodeLabel(parent), SYM_CDATA) == 0) {
	Tcl_Obj *valueObjPtr;
	const char *value;
	int nBytes;

	/* Just output the CDATA field. */
	if (Blt_Tree_GetValue(exportPtr->interp, tree, parent, SYM_CDATA, 
		&valueObjPtr) != TCL_OK) {
	    return TCL_ERROR;
	}
	value = Tcl_GetStringFromObj(valueObjPtr, &nBytes);
	XmlAppendCharacterData(exportPtr, value, nBytes);
	return TCL_OK;
    }
    XmlOpenStartElement(exportPtr, parent);
    for (key = Blt_Tree_FirstKey(tree, parent, &iter); key != NULL; 
	 key = Blt_Tree_NextKey(tree, &iter)) {
	Tcl_Obj *valueObjPtr;
	const char *value;
	int nBytes;

	if (Blt_Tree_GetValueByKey(exportPtr->interp, tree, parent, key,
		&valueObjPtr) != TCL_OK) {
	    return TCL_ERROR;
	}
	value = Tcl_GetStringFromObj(valueObjPtr, &nBytes);
	XmlAppendAttribute(exportPtr, key, value, nBytes);
    }
    XmlCloseStartElement(exportPtr);
    for (child = Blt_Tree_FirstChild(parent); child != NULL; 
	 child = Blt_Tree_NextSibling(child)) {
	if (XmlExportElement(tree, child, exportPtr) != TCL_OK) {
	    return TCL_ERROR;
	}
    }
    return XmlEndElement(exportPtr, parent);
}

static int
XmlExport(Blt_Tree tree, ExportSwitches *exportPtr)
{
    if (XmlExportElement(tree, exportPtr->root, exportPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if (exportPtr->channel != NULL) {
	return XmlFlush(exportPtr);
    }
    return TCL_OK;
}

static int
ExportXmlProc(
    Tcl_Interp *interp, 
    Blt_Tree tree, 
    int objc, 
    Tcl_Obj *const *objv)
{
    ExportSwitches switches;
    Tcl_Channel channel;
    Tcl_DString ds;
    int closeChannel;
    int result;

    closeChannel = FALSE;
    channel = NULL;

    Tcl_DStringInit(&ds);
    memset(&switches, 0, sizeof(switches));
    nodeSwitch.clientData = tree;
    switches.root = Blt_Tree_RootNode(tree);
    switches.flags = IMPORT_ATTRIBUTES | IMPORT_CDATA;
    if (Blt_ParseSwitches(interp, exportSwitches, objc - 3 , objv + 3, 
	&switches, BLT_SWITCH_DEFAULTS) < 0) {
	return TCL_ERROR;
    }
    result = TCL_ERROR;
    if (switches.fileObj != NULL) {
	char *fileName;

	closeChannel = TRUE;
	fileName = Tcl_GetString(switches.fileObj);
	if ((fileName[0] == '@') && (fileName[1] != '\0')) {
	    int mode;
	    
	    channel = Tcl_GetChannel(interp, fileName+1, &mode);
	    if (channel == NULL) {
		goto error;
	    }
	    if ((mode & TCL_WRITABLE) == 0) {
		Tcl_AppendResult(interp, "channel \"", fileName, 
			"\" not opened for writing", (char *)NULL);
		goto error;
	    }
	    closeChannel = FALSE;
	} else {
	    channel = Tcl_OpenFileChannel(interp, fileName, "w", 0666);
	    if (channel == NULL) {
		goto error;	/* Can't open export file. */
	    }
	}
    }
    switches.interp = interp;
    switches.dsPtr = &ds;
    switches.channel = channel;
    result = XmlExport(tree, &switches); 
    if ((switches.channel == NULL) && (result == TCL_OK)) {
	Tcl_DStringResult(interp, &ds);
    } 
 error:
    Tcl_DStringFree(&ds);
    if (closeChannel) {
	Tcl_Close(interp, channel);
    }
    Blt_FreeSwitches(exportSwitches, (char *)&switches, 0);
    return result;
}

int 
Blt_TreeXmlInit(Tcl_Interp *interp)
{
    if (Tcl_PkgRequire(interp, "blt_core", BLT_VERSION, /*Exact*/1) == NULL) {
	return TCL_ERROR;
    }
    if (Tcl_PkgProvide(interp, "blt_tree_xml", BLT_VERSION) != TCL_OK) { 
	return TCL_ERROR;
    }
    return Blt_Tree_RegisterFormat(interp,
        "xml",			/* Name of format. */
#ifdef HAVE_LIBEXPAT
	ImportXmlProc,		/* Import procedure. */
#else
	NULL,			/* Import procedure. */
#endif	/* HAVE_LIBEXPAT */
	ExportXmlProc);		/* Export procedure. */

}
