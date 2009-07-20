
/*
 * bltCsv.c --
 *
 * This module implements a CSV reader procedure for the BLT toolkit.
 *
 *	Copyright 1991-2004 George A Howlett.
 *
 *	Permission is hereby granted, free of charge, to any person
 *	obtaining a copy of this software and associated documentation
 *	files (the "Software"), to deal in the Software without
 *	restriction, including without limitation the rights to use,
 *	copy, modify, merge, publish, distribute, sublicense, and/or
 *	sell copies of the Software, and to permit persons to whom the
 *	Software is furnished to do so, subject to the following
 *	conditions:
 *
 *	The above copyright notice and this permission notice shall be
 *	included in all copies or substantial portions of the
 *	Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
 *	KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *	WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 *	PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 *	OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *	OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 *	OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 *	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "bltInt.h"

static int
ParseCsvChannel(Tcl_Interp *interp, Tcl_Channel channel)
{
    int inQuotes, isQuoted, isPath;
    char *fp, *field;
    Tcl_DString dString;
    Tcl_Obj *listObjPtr, *recordObjPtr;
    int fieldSize;

    isPath = isQuoted = inQuotes = FALSE;
    listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
    recordObjPtr = NULL;

    Tcl_DStringInit(&dString);
    fieldSize = 128;
    Tcl_DStringSetLength(&dString, fieldSize + 1);
    fp = field = Tcl_DStringValue(&dString);
    for (;;) {
	char *bp, *bend;
#define BUFFSIZE	8191
	char buffer[BUFFSIZE+1];
	int nBytes;

	nBytes = Tcl_Read(channel, buffer, sizeof(char) * BUFFSIZE);
	for (bp = buffer, bend = bp + nBytes; bp < bend; bp++) {
	    switch (*bp) {
	    case '\t':
	    case ' ':
		/* 
		 * Add whitespace only if it's not leading or we're inside of
		 * quotes or a path.
		 */
		if ((fp != field) || (inQuotes) || (isPath)) {
		    *fp++ = *bp; 
		}
		break;

	    case '\\':
		/* 
		 * Handle special case CSV files that allow unquoted paths.
		 * Example:  ...,\this\path " should\have been\quoted\,...
		 */
		if (fp == field) {
		    isPath = TRUE; 
		}
		*fp++ = *bp;
		break;

	    case '"':
		if (inQuotes) {
		    if (*(bp+1) == '"') {
			*fp++ = '"';
			bp++;
		    } else {
			inQuotes = FALSE;
		    }
		} else {
		    /* 
		     * If the quote doesn't start a field, then treat all
		     * quotes in the field as ordinary characters.
		     */
		    if (fp == field) {
			isQuoted = inQuotes = TRUE; 
		    } else {
			*fp++ = *bp;
		    }
		}
		break;

	    case ',':
	    case '\n':
		if (inQuotes) {
		    *fp++ = *bp;	/* Copy the comma or newline. */
		} else {
		    char *last;
		    Tcl_Obj *objPtr;

		    if ((isPath) && (*bp == ',') && (fp != field) && 
			(*(fp - 1) != '\\')) {
			*fp++ = *bp;	/* Copy the comma or newline. */
			break;
		    }    
		    /* "last" points to the character after the last character
		     * in the field. */
		    last = fp;	

		    /* Remove trailing spaces only if the field wasn't
		     * quoted. */
		    if ((!isQuoted) && (!isPath)) {
			while ((last > field) && (isspace(*(last - 1)))) {
			    last--;
			}
		    }
		    if (recordObjPtr == NULL) {
			if (*bp == '\n') {
			    break;	/* Ignore empty lines. */
			}
			recordObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
		    }
		    /* End of field. Append field to record. */
		    objPtr = Tcl_NewStringObj(field, last - field);
		    Tcl_ListObjAppendElement(interp, recordObjPtr, objPtr);
		    if (*bp == '\n') {
			/* On newlines append the record to the list. */
			Tcl_ListObjAppendElement(interp, listObjPtr, 
						 recordObjPtr);
			recordObjPtr = NULL;
		    }
		    fp = field;
		    isPath = isQuoted = FALSE;
		}
		break;

	    default:
		*fp++ = *bp;		/* Copy the character. */
	    }
	    if ((fp - field) >= fieldSize) {
		int offset;

		/* 
		 * We've exceeded the current maximum size of the field.
		 * Double the size of the field, but make sure to reset the
		 * pointers (fp and field) to the (possibly) new memory
		 * location.
		 */
		offset = fp - field;
		fieldSize += fieldSize;
		Tcl_DStringSetLength(&dString, fieldSize + 1);
		field = Tcl_DStringValue(&dString);
		fp = field + offset;
	    }
	}
	if (nBytes < 1) {
	    /* 
	     * We're reached the end of input. But there may not have been a
	     * final newline to trigger the final appends. So check if 1) a
	     * last field is still needs appending the the last record and if
	     * 2) a last record is still needs appending to the list.
	     */
	    if (fp != field) {
		char *last;
		Tcl_Obj *objPtr;

		last = fp;
		/* Remove trailing spaces */
		while (isspace(*(last - 1))) {
		    last--;
		}
		objPtr = Tcl_NewStringObj(field, last - field);
		if (recordObjPtr == NULL) {
		    recordObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
		}
	    }		    
	    if (recordObjPtr != NULL) {
		Tcl_ListObjAppendElement(interp, listObjPtr, recordObjPtr);
	    }
	    break;
	}
    }
    Tcl_DStringFree(&dString);
    Tcl_SetObjResult(interp, listObjPtr);
    return TCL_OK;
}

static int
ParseCsvData(Tcl_Interp *interp, Tcl_Obj *objPtr)
{
    int inQuotes, isQuoted, isPath;
    char *fp, *field;
    Tcl_DString dString;
    Tcl_Obj *listObjPtr, *recordObjPtr;
    int fieldSize;

    isPath = isQuoted = inQuotes = FALSE;
    listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
    recordObjPtr = NULL;

    Tcl_DStringInit(&dString);
    fieldSize = 128;
    Tcl_DStringSetLength(&dString, fieldSize + 1);
    fp = field = Tcl_DStringValue(&dString);
    {
	char *bp, *bend;
	char *buffer;
	int nBytes;

	buffer = Tcl_GetStringFromObj(objPtr, &nBytes);
	for (bp = buffer, bend = bp + nBytes; bp < bend; bp++) {
	    switch (*bp) {
	    case '\t':
	    case ' ':
		/* 
		 * Add whitespace only if it's not leading or we're inside of
		 * quotes or a path.
		 */
		if ((fp != field) || (inQuotes) || (isPath)) {
		    *fp++ = *bp; 
		}
		break;

	    case '\\':
		if (fp == field) {
		    isPath = TRUE; 
		}
		*fp++ = *bp;
		break;

	    case '"':
		if (inQuotes) {
		    if (*(bp+1) == '"') {
			*fp++ = '"';
			bp++;
		    } else {
			inQuotes = FALSE;
		    }
		} else {
		    /* 
		     * If the quote doesn't start a field, then treat all
		     * quotes in the field as ordinary characters.
		     */
		    if (fp == field) {
			isQuoted = inQuotes = TRUE; 
		    } else {
			*fp++ = *bp;
		    }
		}
		break;

	    case ',':
	    case '\n':
		if (inQuotes) {
		    *fp++ = *bp;	/* Copy the comma or newline. */
		} else {
		    char *last;
		    Tcl_Obj *objPtr;

		    if ((isPath) && (*bp == ',') && (fp != field) && 
			(*(fp - 1) != '\\')) {
			*fp++ = *bp;	/* Copy the comma or newline. */
			break;
		    }    
		    /* "last" points to the character after the last character
		     * in the field. */
		    last = fp;	

		    /* Remove trailing spaces only if the field wasn't
		     * quoted. */
		    if ((!isQuoted) && (!isPath)) {
			while ((last > field) && (isspace(*(last - 1)))) {
			    last--;
			}
		    }
		    if (recordObjPtr == NULL) {
			if (*bp == '\n') {
			    break;	/* Ignore empty lines. */
			}
			recordObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
		    }
		    /* End of field. Append field to record. */
		    objPtr = Tcl_NewStringObj(field, last - field);
		    Tcl_ListObjAppendElement(interp, recordObjPtr, objPtr);
		    if (*bp == '\n') {
			/* On newlines append the record to the list. */
			Tcl_ListObjAppendElement(interp, listObjPtr, 
						 recordObjPtr);
			recordObjPtr = NULL;
		    }
		    fp = field;
		    isPath = isQuoted = FALSE;
		}
		break;

	    default:
		*fp++ = *bp;		/* Copy the character. */
	    }
	    if ((fp - field) >= fieldSize) {
		int offset;

		/* 
		 * We've exceeded the current maximum size of the field.
		 * Double the size of the field, but make sure to reset the
		 * pointers to the (possibly) new memory location.
		 */
		offset = fp - field;
		fieldSize += fieldSize;
		Tcl_DStringSetLength(&dString, fieldSize + 1);
		field = Tcl_DStringValue(&dString);
		fp = field + offset;
	    }
	}

	/* 
	 * We're reached the end of input. But there may not have been a final
	 * newline to trigger the final appends. So check if 1) a last field
	 * is still needs appending the the last record and if 2) a last
	 * record is still needs appending to the list.
	 */
	if (fp != field) {
	    char *last;
	    Tcl_Obj *objPtr;
	    
	    last = fp;
	    /* Remove trailing spaces */
	    while (isspace(*(last - 1))) {
		last--;
	    }
	    objPtr = Tcl_NewStringObj(field, last - field);
	    if (recordObjPtr == NULL) {
		recordObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
	    }
	}		    
	if (recordObjPtr != NULL) {
	    Tcl_ListObjAppendElement(interp, listObjPtr, recordObjPtr);
	}
    }
    Tcl_DStringFree(&dString);
    Tcl_SetObjResult(interp, listObjPtr);
    return TCL_OK;
}

static int
ParseCsvFile(Tcl_Interp *interp, const char *fileName)
{
    int result;
    int closeChannel;
    Tcl_Channel channel;

    closeChannel = TRUE;
    if ((fileName[0] == '@') && (fileName[1] != '\0')) {
	int mode;
	
	channel = Tcl_GetChannel(interp, fileName+1, &mode);
	if (channel == NULL) {
	    return TCL_ERROR;
	}
	if ((mode & TCL_READABLE) == 0) {
	    Tcl_AppendResult(interp, "channel \"", fileName, 
		"\" not opened for reading", (char *)NULL);
	    return TCL_ERROR;
	}
	closeChannel = FALSE;
    } else {
	channel = Tcl_OpenFileChannel(interp, fileName, "r", 0);
	if (channel == NULL) {
	    return TCL_ERROR;		/* Can't open dump file. */
	}
    }
    result = ParseCsvChannel(interp, channel);
    if (closeChannel) {
	Tcl_Close(interp, channel);
    }
    return result;
}

static int
CsvCmd(ClientData clientData, Tcl_Interp *interp, int objc, 
       Tcl_Obj *const *objv)
{
    if (objc == 2) {
	return ParseCsvFile(interp, Tcl_GetString(objv[1]));
    }
    if (objc == 3) {
	char *string;

        string = Tcl_GetString(objv[1]);
        if (strcmp(string, "-data") == 0) {
	    return  ParseCsvData(interp, objv[2]);
	} 
    }
    Tcl_AppendResult(interp, "wrong # args: should be \"", Tcl_GetString(objv[0]),
	 " ?fileName? ?-data dataString?", (char *)NULL);
    return TCL_ERROR;
}
    
int
Blt_CsvCmdInitProc(Tcl_Interp *interp)
{
    static Blt_InitCmdSpec cmdSpec = {"csv", CsvCmd,};

    return Blt_InitCmd(interp, "::blt", &cmdSpec);
}
