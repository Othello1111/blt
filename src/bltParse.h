
/*
 * bltParse.h --
 *
 *	Copyright 1993-2004 George A Howlett.
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

#ifndef _BLT_PARSE_H
#define _BLT_PARSE_H

#include "tclInterp.h"

BLT_EXTERN int Blt_ParseBraces(Tcl_Interp *interp, const char *string, 
	const char **termPtr, ParseValue *pvPtr);

BLT_EXTERN int Blt_ParseNestedCmd(Tcl_Interp *interp, const char *string, 
	int flags, const char **termPtr, ParseValue *pvPtr);

BLT_EXTERN int Blt_ParseQuotes(Tcl_Interp *interp, const char *string, 
	int termChar, int flags, const char **termPtr, ParseValue * pvPtr);

BLT_EXTERN void Blt_ExpandParseValue(ParseValue *pvPtr, int needed);

#endif 
