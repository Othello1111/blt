
/*
 * bltPictXbm.c --
 *
 * This module implements XBM file format conversion routines for
 * the picture image type in the BLT toolkit.
 *
 *	Copyright 2003-2005 George A Howlett.
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
 *
 */

#include "blt.h"

#include "config.h"
#include <tcl.h>
#include <bltSwitch.h>
#include <bltDBuffer.h>
#include "bltPicture.h"
#include "bltPictFmts.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#ifdef HAVE_STRING_H
#  include <string.h>
#endif /* HAVE_STRING_H */

#define UCHAR(c) ((unsigned char) (c))
#define ISASCII(c) (UCHAR(c)<=0177)

DLLEXPORT extern Tcl_AppInitProc Blt_PictureXbmInit;

extern char *Blt_Itoa(int);
extern char *Blt_InitHexTable(unsigned char *);

#define TRUE 	1
#define FALSE 	0

typedef struct _Blt_Picture Picture;

#include <ctype.h>

typedef struct {
    int hotX, hotY;
    int width, height;
    int version;
} Xbm;

typedef struct {
    Tcl_Obj *dataObjPtr;
    Tcl_Obj *fileObjPtr;
    Blt_Pixel bg, fg;		/* Colors for XBM image format. */
} XbmImportSwitches;

typedef struct {
    Tcl_Obj *dataObjPtr;
    Tcl_Obj *fileObjPtr;
    Blt_Pixel bg;
    int index;
} XbmExportSwitches;

BLT_EXTERN Blt_SwitchParseProc Blt_ColorSwitchProc;
static Blt_SwitchCustom colorSwitch = {
    Blt_ColorSwitchProc, NULL, (ClientData)0,
};

static Blt_SwitchSpec importSwitches[] = 
{
    {BLT_SWITCH_CUSTOM, "-bg", "color",
	Blt_Offset(XbmImportSwitches, bg), 0, 0, &colorSwitch},
    {BLT_SWITCH_OBJ, "-data", "data",
	Blt_Offset(XbmImportSwitches, dataObjPtr), 0},
    {BLT_SWITCH_CUSTOM, "-fg", "color",
	Blt_Offset(XbmImportSwitches, fg), 0, 0, &colorSwitch},
    {BLT_SWITCH_OBJ, "-file", "fileName",
	Blt_Offset(XbmImportSwitches, fileObjPtr), 0},
    {BLT_SWITCH_END}
};

static Blt_SwitchSpec exportSwitches[] = 
{
    {BLT_SWITCH_CUSTOM, "-bg", "color",
	Blt_Offset(XbmExportSwitches, bg), 0, 0, &colorSwitch},
    {BLT_SWITCH_OBJ, "-data", "data",
	Blt_Offset(XbmExportSwitches, dataObjPtr), 0},
    {BLT_SWITCH_OBJ, "-file", "fileName",
	Blt_Offset(XbmExportSwitches, fileObjPtr), 0},
    {BLT_SWITCH_INT_NNEG, "-index", "int",
	Blt_Offset(XbmExportSwitches, index), 0},
    {BLT_SWITCH_END}
};


/*
 * Parse the lines that define the dimensions of the bitmap,
 * plus the first line that defines the bitmap data (it declares
 * the name of a data variable but doesn't include any actual
 * data).  These lines look something like the following:
 *
 *		#define foo_width 16
 *		#define foo_height 16
 *		#define foo_x_hot 3
 *		#define foo_y_hot 3
 *		static char foo_bits[] = {
 *
 * The x_hot and y_hot lines may or may not be present.  It's
 * important to check for "char" in the last line, in order to
 * reject old X10-style bitmaps that used shorts.
 */

static int
XbmHeader(Blt_DBuffer data, Xbm *xbmPtr)
{
    unsigned char *line, *next;

    xbmPtr->width = xbmPtr->height = 0;
    xbmPtr->hotX = xbmPtr->hotY = -1;
    xbmPtr->version = 11;

    Blt_DBuffer_ResetCursor(data);
    for (line = Blt_DBuffer_Pointer(data); *line != '\0'; line = next) {
#define XBM_MAX_LINE 1023
	char substring[XBM_MAX_LINE+1];
	char *s;
	int value;

	/* Find the start of the next line */
	if ((*line == '\n') || (*line == '\r')) {
	    line++;
	}
	next = line;
	while ((*next != '\r') && (*next != '\n') && (*next != '\0')) {
	    if (*next & !ISASCII(*next)) {
		return FALSE;
	    }
	    next++;
	}
	/* Verify that we won't overrun the buffer with "sscanf". */
	if ((next - line) > XBM_MAX_LINE) {
	    return FALSE;
	}
	s = (char *)line;
	if (sscanf(s, "#define %s %d", substring,  &value) == 2) {
	    char *name;
	    char c;
	    char *p;

	    p = strrchr(substring, '_');
	    if (p == NULL) {
		name = substring;
	    } else {
		name = p + 1;
	    }
	    c = name[0];
	    if ((c == 'w') && (strcmp("width", name) == 0)) {
		xbmPtr->width = value;
	    } else if ((c == 'h') && (strcmp("height", name) == 0)){
		xbmPtr->height = value;
	    } else if ((c == 'h') && (strcmp("hot", name) == 0)) {
		name -= 2;
		if (name > substring) {
		    if (name[1] == '_') {
			if (name[0] == 'x') {
			    xbmPtr->hotX = value;
			} else if (name[0] == 'y') {
			    xbmPtr->hotY = value;
			}
		    }
		}
	    }
	    continue;
	} else if (sscanf(s, "static short %s = {", substring) == 1) {
	    xbmPtr->version = 10;
	} else if (sscanf(s,"static unsigned char %s = {", substring) == 1) {
	    xbmPtr->version = 11;
	} else if (sscanf(s, "static char %s = {", substring) == 1) {
	    xbmPtr->version = 11;
	} else {
	    continue;
	}
	if (*next == '\r') {
	    next++;
	}
	Blt_DBuffer_SetPointer(data, next);
	return TRUE;
    }
    return FALSE;
}

/*
 *---------------------------------------------------------------------------
 *
 * XbmGetHexValue --
 *
 *	Converts the hexadecimal string into an unsigned integer
 *	value.  The hexadecimal string need not have a leading "0x".
 *
 * Results:
 *	Returns a standard TCL result. If the conversion was
 *	successful, TCL_OK is returned, otherwise TCL_ERROR.
 *
 * Side Effects:
 * 	If the conversion fails, interp->result is filled with an
 *	error message.
 *
 *---------------------------------------------------------------------------
 */
static int
XbmGetHexValue(const char *string, int *valuePtr)
{
    static unsigned char hexTable[256];
    static int initialized = 0;
    const char *s;
    int accum;

    if (!initialized) {
	Blt_InitHexTable(hexTable);
	initialized++;
    }

    s = string;
    if ((s[0] == '0') && ((s[1] == 'x') || (s[1] == 'X'))) {
	s += 2;
    }
    if (s[0] == '\0') {
	return FALSE;	/* Error: empty string or only found "0x".  */
    }
    accum = 0;
    for ( /*empty*/ ; *s != '\0'; s++) {
	unsigned char byte;

	/* Check if character is a hex digit and accumulate. */
	byte = hexTable[(int)*s];
	if (byte == 0xFF) {
	    return FALSE;	/* Not a hexadecimal number */
	}
	accum = (accum << 4) | byte;
    }
    *valuePtr = accum;
    return TRUE;
}

/*
 *---------------------------------------------------------------------------
 *
 * XbmBitmapData --
 *
 *	Converts a list of ASCII values into a picture.
 *
 * Results:
 *	A standard TCL result.
 *
 * Side Effects:
 * 	If an error occurs while processing the data, interp->result
 * 	is filled with a corresponding error message.  
 *
 *	The data sink is damaged by "strtok".  Unlike XbmReadHeader,
 *	here it's okay, since if we're already this far, we know it's
 *	an XBM image and we assume that the data sink won't be reused.
 *
 *---------------------------------------------------------------------------
 */
static int
XbmBitmapData(
    Blt_DBuffer data,		/* Data sink to be read from. */
    int version,		/* X10 or X11. */
    Blt_Pixel *fgColorPtr,		/* Foreground bitmap color (bit is 1). */
    Blt_Pixel *bgColorPtr,		/* Background bitmap color (bit is 0). */
    Picture *destPtr)		/* Picture to be populated from XBM
				 * image. */
{
    Blt_Pixel *destRowPtr;
    char *string;		/* Used to tell strtok that have
				 * continued processing the same
				 * string. */
    int y;

    destRowPtr = destPtr->bits;
    string = (char *)Blt_DBuffer_Pointer(data);
    for (y = 0; y < destPtr->height; y++) {
	int x;
	Blt_Pixel *dp;

	dp = destRowPtr;
	if (version == 10) {
	    for (x = 0; x < destPtr->width; /* empty */) {
		char *p;
		int i, u16;
		
		p = strtok(string, ",;}\n\r\t "), string = NULL;
		if ((p == NULL) || (!XbmGetHexValue(p, &u16))) {
		    return FALSE;
		}
		for (i = 0; (x < destPtr->width) && (i < 16); i++, x++) {
		    dp->u32 = (u16 & (1<<i)) ? 
			fgColorPtr->u32 : bgColorPtr->u32;
		    dp++;
		}
	    }
	} else {
	    for (x = 0; x < destPtr->width; /* empty */) {
		char *p;
		int i, u8;

		p = strtok(string, ",;}\n\r\t "), string = NULL;
		if ((p == NULL) || (!XbmGetHexValue(p, &u8))) {
		    return FALSE;
		}
		for (i = 0; (x < destPtr->width) && (i < 8); i++, x++) {
		    dp->u32 = (u8 & (1<<i)) ? 
			fgColorPtr->u32 : bgColorPtr->u32;
		    dp++;
		}
	    }
	}
	destRowPtr += destPtr->pixelsPerRow;
    }
    if (bgColorPtr->Alpha == 0x00) {	/* Background is 100% transparent. */
	if (fgColorPtr->Alpha == 0xFF) {
	    destPtr->flags |= BLT_PIC_MASK;
	} else {
	    destPtr->flags |= BLT_PIC_BLEND;
	}
    } else if (bgColorPtr->Alpha != 0xFF) { /* Partial transparency. */
	destPtr->flags |= BLT_PIC_BLEND;
    } else if (fgColorPtr->Alpha == 0x00) { 
	/* Background is 100% opaque and foreground is 100%
	 * transparent. */
	destPtr->flags |= BLT_PIC_MASK;
    }
    return TRUE;
}

/*
 *---------------------------------------------------------------------------
 *
 * IsXbm --
 *
 *      Attempts to parse an XBM file header.
 *
 * Results:
 *      Returns 1 is the header is XBM and 0 otherwise.  Note that
 *      the validity of the header values is not checked here.  That's
 *	done in Blt_XbmToPicture.
 *
 *---------------------------------------------------------------------------
 */
static int
IsXbm(Blt_DBuffer data)
{
    Xbm xbm;
    int bool;

    bool = XbmHeader(data, &xbm);
    return bool;
}

/*
 *---------------------------------------------------------------------------
 *
 * XbmToPicture --
 *
 *      Reads an XBM file and converts it into a picture.
 *
 * Results:
 *      The picture is returned.  If an error occured, such
 *	as the designated file could not be opened, NULL is returned.
 *
 *---------------------------------------------------------------------------
 */
static Blt_Chain
XbmToPicture(
    Tcl_Interp *interp, 
    const char *fileName,
    Blt_DBuffer buffer,
    XbmImportSwitches *switchesPtr)
{
    Blt_Picture picture;
    Xbm xbm;

    picture = NULL;
    if (!XbmHeader(buffer, &xbm)) {
	    Tcl_AppendResult(interp, "error reading \"", fileName, 
		"\" invalid XBM header", (char *)NULL);
	    goto error;
    }
    if ((xbm.width > 0) && (xbm.height > 0)) {
	picture = Blt_CreatePicture(xbm.width, xbm.height);
	if (!XbmBitmapData(buffer, xbm.version, &switchesPtr->fg, 
		&switchesPtr->bg, picture)) { 
	    Tcl_AppendResult(interp, "error reading \"", fileName, 
		"\" invalid XBM data", (char *)NULL);
	    goto error;
	}
    } else {
	Tcl_AppendResult(interp, "error reading \"", fileName, 
		"\" invalid XBM dimensions \"", (char *)NULL);
	Tcl_AppendResult(interp, Blt_Itoa(xbm.width), " x ", (char *)NULL);
	Tcl_AppendResult(interp, Blt_Itoa(xbm.height), "\"", (char *)NULL);
	goto error;
    }

    Blt_DBuffer_Free(buffer);
    if (picture) {
	Blt_Chain chain;

	chain = Blt_Chain_Create();
	Blt_Chain_Append(chain, picture);
	return chain;
    }
 error:
    if (picture) {
	Blt_FreePicture(picture);
    }
    Blt_DBuffer_Free(buffer);
    return NULL;
}

/*
 *---------------------------------------------------------------------------
 *
 * PictureToXbm --
 *
 *      Writes a XBM format image to the provided data buffer.
 *
 * Results:
 *      A standard TCL result.  If an error occured, TCL_ERROR is
 *	returned and an error message will be place in the interpreter
 *	result. Otherwise, the data sink will contain the binary
 *	output of the image.
 *
 * Side Effects:
 *	Memory is allocated for the data sink.
 *
 *---------------------------------------------------------------------------
 */
static int
PictureToXbm(Tcl_Interp *interp, Blt_Picture original, Blt_DBuffer buffer,
	     XbmExportSwitches *switchesPtr)
{
    Picture *srcPtr;

    srcPtr = original;
    Blt_DBuffer_Print(buffer, "#define picture_width %d\n", srcPtr->width);
    Blt_DBuffer_Print(buffer, "#define picture_height %d\n", srcPtr->height);
    Blt_DBuffer_Print(buffer, "#define picture_x_hot %d\n", srcPtr->width / 2);
    Blt_DBuffer_Print(buffer, "#define picture_y_hot %d\n", srcPtr->height / 2);
    Blt_DBuffer_Print(buffer, "static char picture_bits[] = {\n    ");
    {
	Blt_Pixel *cp, *srcRowPtr;
	Blt_Pixel palette[256];
	int count, i;
	int y;
	
	/* Create a B&W palette for dithering the image. */
	for (cp = palette, i = 0; i < 256; i++, cp++) {
	    int c;
	    
	    c = (i + 127) / 255;
	    cp->Blue = cp->Green = cp->Red = (unsigned char) (c * 255 + 0.5);
	    cp->Alpha = ALPHA_OPAQUE;
	} 

	/* Remove any transparent pixels by blending into a solid
	 * white background. */
	if (!Blt_PictureIsOpaque(srcPtr)) {
	    Blt_Picture background;

	    /* Blend picture with solid color background. */
	    background = Blt_CreatePicture(srcPtr->width, srcPtr->height);
	    Blt_BlankPicture(background, &switchesPtr->bg); 
	    Blt_BlendPictures(background, srcPtr, 0, 0, srcPtr->width, 
		srcPtr->height, 0, 0);
	    if (srcPtr != original) {
		Blt_FreePicture(srcPtr);
	    }
	    srcPtr = background;
	}
	if (srcPtr->flags & BLT_PIC_ASSOCIATED_COLORS) {
	    Blt_Picture unassoc;
	    /* 
	     * The picture has an alpha burned into the components.  Create a
	     * temporary copy removing pre-multiplied alphas.
	     */ 
	    unassoc = Blt_ClonePicture(srcPtr);
	    Blt_UnassociateColors(unassoc);
	    if (srcPtr != original) {
		Blt_FreePicture(srcPtr);
	    }
	    srcPtr = unassoc;
	}
	/* Now dither the picture to 2 colors. */
	{
	    Blt_Picture dither;

	    dither = Blt_DitherPicture(srcPtr, palette);
	    if (srcPtr != original) {
		Blt_FreePicture(srcPtr);
	    }
	    srcPtr = dither;
	}
	/* Write the dithered image data. */
	count = 0;
	srcRowPtr = srcPtr->bits;
	for (y = 0; y < srcPtr->height; y++) {
	    Blt_Pixel *sp;
	    int x;
	    
	    sp = srcRowPtr;
	    for (x = 0; x < srcPtr->width; /* empty */) {
		unsigned char bits;
		int i;

		bits = 0;
		for (i = 0; (x < srcPtr->width) && (i < 8); i++, x++) {
		    if (sp->Red == 0x00) {
			bits |= (1<<i);
		    }
		    sp++;
		}
		count++;
		Blt_DBuffer_Print(buffer, "0x%02x, ", bits);
		if (count > 11) {
		    Blt_DBuffer_Print(buffer, "\n    ");
		    count = 0;
		}
	    }
	    srcRowPtr += srcPtr->pixelsPerRow;
	}
	Blt_DBuffer_Print(buffer, "\n};\n");

	/* Free the temporary images. */
	if (srcPtr != original) {
	    Blt_FreePicture(srcPtr);
	}
    }
    return TCL_OK;
}

static Blt_Chain
ReadXbm(Tcl_Interp *interp, const char *fileName, Blt_DBuffer buffer)
{
    XbmImportSwitches switches;

    memset(&switches, 0, sizeof(switches));
    return XbmToPicture(interp, fileName, buffer, &switches);
}

static Tcl_Obj *
WriteXbm(Tcl_Interp *interp, Blt_Chain chain)
{
    Tcl_Obj *objPtr;
    Blt_DBuffer buffer;
    XbmExportSwitches switches;
    Blt_Picture picture;

    /* Default export switch settings. */
    memset(&switches, 0, sizeof(switches));
    switches.bg.u32 = 0xFFFFFFFF; /* white */

    picture = Blt_GetNthPicture(chain, 0);
    if (picture == NULL) {
	return Blt_EmptyStringObj();
    }
    buffer = Blt_DBuffer_Create();
    if (PictureToXbm(interp, picture, buffer, &switches) != TCL_OK) {
	objPtr = NULL;
    } else {
	objPtr = Tcl_NewStringObj((char *)Blt_DBuffer_Bytes(buffer), 
		Blt_DBuffer_Length(buffer));
    }
    Blt_DBuffer_Destroy(buffer);
    return objPtr;
}

static Blt_Chain
ImportXbm(
    Tcl_Interp *interp, 
    int objc,
    Tcl_Obj *const *objv,
    const char **fileNamePtr)
{
    Blt_Chain chain;
    Blt_DBuffer buffer;
    XbmImportSwitches switches;
    const char *string;

    memset(&switches, 0, sizeof(switches));
    if (Blt_ParseSwitches(interp, importSwitches, objc - 3, objv + 3, 
	&switches, BLT_SWITCH_DEFAULTS) < 0) {
	Blt_FreeSwitches(importSwitches, (char *)&switches, 0);
	return NULL;
    }
    if ((switches.dataObjPtr != NULL) && (switches.fileObjPtr != NULL)) {
	Tcl_AppendResult(interp, "more than one import source: ",
		"use only one -file or -data flag.", (char *)NULL);
	Blt_FreeSwitches(importSwitches, (char *)&switches, 0);
	return NULL;
    }
    buffer = Blt_DBuffer_Create();
    chain = NULL;
    if (switches.dataObjPtr != NULL) {
	int nBytes;

	string = Tcl_GetStringFromObj(switches.dataObjPtr, &nBytes);
	Blt_DBuffer_AppendData(buffer, (unsigned char *)string, nBytes);
	string = "data buffer";
	*fileNamePtr = NULL;
    } else {
	string = Tcl_GetString(switches.fileObjPtr);
	if (Blt_DBuffer_LoadFile(interp, string, buffer) != TCL_OK) {
	    goto error;
	}
	*fileNamePtr = string;
    }
    chain = XbmToPicture(interp, string, buffer, &switches);
 error:
    Blt_FreeSwitches(importSwitches, (char *)&switches, 0);
    Blt_DBuffer_Destroy(buffer);
    return chain;
}

static int
ExportXbm(Tcl_Interp *interp, Blt_Chain chain, int objc, Tcl_Obj *const *objv)
{
    XbmExportSwitches switches;
    Blt_DBuffer buffer;
    int result;
    Blt_Picture picture;

    memset(&switches, 0, sizeof(switches));
    switches.bg.u32 = 0xFFFFFFFF; /* Default bgcolor is white. */

    if (Blt_ParseSwitches(interp, exportSwitches, objc - 3, objv + 3, 
	&switches, BLT_SWITCH_DEFAULTS) < 0) {
	Blt_FreeSwitches(exportSwitches, (char *)&switches, 0);
	return TCL_ERROR;
    }
    if ((switches.dataObjPtr != NULL) && (switches.fileObjPtr != NULL)) {
	Tcl_AppendResult(interp, "more than one export destination: ",
		"use only one -file or -data flag.", (char *)NULL);
	Blt_FreeSwitches(exportSwitches, (char *)&switches, 0);
	return TCL_ERROR;
    }
    picture = Blt_GetNthPicture(chain, switches.index);
    if (picture == NULL) {
	Tcl_AppendResult(interp, "no picture at index ", 
		Blt_Itoa(switches.index), (char *)NULL);
	Blt_FreeSwitches(exportSwitches, (char *)&switches, 0);
	return TCL_ERROR;
    }

    buffer = Blt_DBuffer_Create();
    result = PictureToXbm(interp, picture, buffer, &switches);
    if (result != TCL_OK) {
	Tcl_AppendResult(interp, "can't convert \"", 
		Tcl_GetString(objv[2]), "\"", (char *)NULL);
	goto error;
    }
    if (switches.fileObjPtr != NULL) {
	char *fileName;

	fileName = Tcl_GetString(switches.fileObjPtr);
	result = Blt_DBuffer_SaveFile(interp, fileName, buffer);
    } else if (switches.dataObjPtr != NULL) {
	Tcl_Obj *objPtr;

	objPtr = Blt_DBuffer_StringObj(buffer);
	objPtr = Tcl_ObjSetVar2(interp, switches.dataObjPtr, NULL, objPtr, 0);
	result = (objPtr == NULL) ? TCL_ERROR : TCL_OK;
    } else {
	Tcl_SetObjResult(interp, Blt_DBuffer_StringObj(buffer));
    }  
 error:
    Blt_FreeSwitches(exportSwitches, (char *)&switches, 0);
    Blt_DBuffer_Destroy(buffer);
    return result;
}

int 
Blt_PictureXbmInit(Tcl_Interp *interp)
{
#ifdef USE_TCL_STUBS
    if (Tcl_InitStubs(interp, TCL_VERSION, 1) == NULL) {
	return TCL_ERROR;
    };
#endif
    if (Tcl_PkgRequire(interp, "blt_extra", BLT_VERSION, /*Exact*/1) == NULL) {
	return TCL_ERROR;
    }
    if (Tcl_PkgProvide(interp, "blt_picture_xbm", BLT_VERSION) != TCL_OK) {
	return TCL_ERROR;
    }
    return Blt_PictureRegisterFormat(interp,
	"xbm",			/* Name of format. */
	IsXbm,			/* Discovery routine. */
	ReadXbm,		/* Read format procedure. */
	WriteXbm,		/* Write format procedure. */
	ImportXbm,		/* Import format procedure. */
	ExportXbm);		/* Export format procedure. */
}
