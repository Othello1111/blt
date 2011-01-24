
/*
 * bltPictXpm.c --
 *
 * This module implements XPM file format conversion routines for the picture
 * image type in the BLT toolkit.
 *
 *	Copyright 2003-2005 George A Howlett.
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
 *
 */

#include "blt.h"

#include "config.h"
#ifdef HAVE_LIBXPM
#include <tcl.h>
#include <bltAlloc.h>
#include <bltSwitch.h>
#include <bltDBuffer.h>
#include <bltHash.h>
#include "bltPicture.h"
#include "bltPictFmts.h"
#include <ctype.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#ifdef HAVE_MEMORY_H
#  include <memory.h>
#endif /* HAVE_MEMORY_H */

#ifdef HAVE_STRING_H
#  include <string.h>
#endif /* HAVE_STRING_H */

#ifndef HAVE_SPRINTF_S
BLT_EXTERN int sprintf_s(char *s, size_t size, const char *fmt, /*args*/ ...);
#endif	/* HAVE_SPRINTF_S */

#define TRUE 	1
#define FALSE 	0

typedef struct _Blt_Picture Picture;

#include <X11/xpm.h>

typedef struct {
    Tcl_Obj *dataObjPtr;
    Tcl_Obj *fileObjPtr;
    int flags;			/* Flag. */
    Blt_Pixel bg;
    int index;
} XpmExportSwitches;

typedef struct {
    Tcl_Obj *dataObjPtr;
    Tcl_Obj *fileObjPtr;
} XpmImportSwitches;

BLT_EXTERN Blt_SwitchParseProc Blt_ColorSwitchProc;

static Blt_SwitchCustom colorSwitch = {
    Blt_ColorSwitchProc, NULL, (ClientData)0,
};

static Blt_SwitchSpec exportSwitches[] = 
{
    {BLT_SWITCH_CUSTOM, "-bg", "color",
	Blt_Offset(XpmExportSwitches, bg), 0, 0, &colorSwitch},
    {BLT_SWITCH_OBJ, "-data", "data",
	Blt_Offset(XpmExportSwitches, dataObjPtr), 0},
    {BLT_SWITCH_OBJ, "-file", "fileName",
	Blt_Offset(XpmExportSwitches, fileObjPtr), 0},
    {BLT_SWITCH_BITMASK, "-noquantize", "",
	Blt_Offset(XpmExportSwitches, flags), 0, PIC_NOQUANTIZE},
    {BLT_SWITCH_INT_NNEG, "-index", "int",
	Blt_Offset(XpmExportSwitches, index), 0},
    {BLT_SWITCH_END}
};

static Blt_SwitchSpec importSwitches[] = 
{
    {BLT_SWITCH_OBJ, "-data", "data",
	Blt_Offset(XpmImportSwitches, dataObjPtr), 0},
    {BLT_SWITCH_OBJ, "-file", "fileName",
	Blt_Offset(XpmImportSwitches, fileObjPtr), 0},
    {BLT_SWITCH_END}
};

DLLEXPORT extern Tcl_AppInitProc Blt_PictureXpmInit;
extern char *Blt_Itoa(int);


static int
XpmHeader(Blt_DBuffer buffer)
{
    unsigned char *line, *next;
    unsigned char *bp;

    Blt_DBuffer_ResetCursor(buffer);
    bp = Blt_DBuffer_End(buffer);
    bp[0] = '\0';		/* Guaranteed to have 1 extra byte in the
				 * buffer to create an ASCIZ string. */

    for (line = Blt_DBuffer_Pointer(buffer); *line != '\0'; line = next) {
#define XPM_MAX_LINE 4097
	char substring[XPM_MAX_LINE+1];
	int value;
	char *s;

	/* Find the start of the next line */
	if ((*line == '\n') || (*line == '\r')) {
	    line++;
	}
	next = line;
	while ((*next != '\r') && (*next != '\n') && (*next != '\0')) {
	    if (!isascii(*next)) {
		return FALSE;
	    }
	    next++;
	}
	/* Verify that we won't overrun the buffer with "sscanf". */
	if ((next - line) > XPM_MAX_LINE) {
	    return FALSE;
	}
	s = (char *)line;
	if (sscanf(s, "#define %s %d", substring,  &value) == 2) {
	    char *p;
	    char c;
	    char *name;

	    p = strrchr(substring, '_');

	    if (p == NULL) {
		name = substring;
	    } else {
		name = p + 1;
	    }
	    c = name[0];
	    if ((c == 'f') && (strcmp("format", name) == 0)) {
		return TRUE;
	    } else {
		return FALSE;
	    }
	} else if (sscanf(s, "/* %s */", substring) == 1) {
	    if ((strcmp("XPM", substring) == 0) || 
		(strcmp("XPM2", substring) == 0)) {
		return TRUE;
	    }
	}
    }
    return FALSE;
}

/*
 *---------------------------------------------------------------------------
 *
 * IsXpm --
 *
 *      Attempts to parse an XBM file header.
 *
 * Results:
 *      Returns 1 is the header is XBM and 0 otherwise.  Note that
 *      the validity of the header values is not checked here.  That's
 *	done in XpmToPicture.
 *
 *---------------------------------------------------------------------------
 */
static int
IsXpm(Blt_DBuffer buffer)
{
    int bool;

    bool = XpmHeader(buffer);
    return bool;
}

/*
 *---------------------------------------------------------------------------
 *
 * XpmToPicture --
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
XpmToPicture(
    Tcl_Interp *interp, 
    const char *fileName,
    Blt_DBuffer buffer,
    XpmImportSwitches *switchesPtr)
{
    Picture *destPtr;
    Blt_Pixel *palette;
    XpmImage xpm;
    int i, result;
    int maskColorIndex;

    Blt_DBuffer_ResetCursor(buffer);
    result = XpmCreateXpmImageFromBuffer((char *)Blt_DBuffer_Bytes(buffer), &xpm,
	(XpmInfo *)NULL);
    if (result != XpmSuccess) {
	Tcl_AppendResult(interp, "error reading \"", fileName, 
		"\" can't read XPM image. ", (char *)NULL);
	return NULL;
    }
    destPtr = NULL;
    palette = NULL;
    if ((xpm.height < 1) || (xpm.width < 1)) {
	Tcl_AppendResult(interp, "error reading \"", fileName, 
		"\" invalid XPM dimensions \"", (char *)NULL);
	Tcl_AppendResult(interp, Blt_Itoa(xpm.width), " x ", (char *)NULL);
	Tcl_AppendResult(interp, Blt_Itoa(xpm.height), "\"", (char *)NULL);
	goto bad;
    }
    if (xpm.colorTable == NULL) {
	Tcl_AppendResult(interp, "error reading \"", fileName, 
		"\" no XPM color table available. ", (char *)NULL);
	goto bad;
    }
    destPtr = Blt_CreatePicture(xpm.width, xpm.height);
    palette = Blt_Malloc(xpm.ncolors * sizeof(Blt_Pixel));
    if (palette == NULL) {
	Tcl_AppendResult(interp, "error reading \"", fileName, 
		"\" can't allocate a ", Blt_Itoa(xpm.ncolors), 
		" color XPM palette.", (char *)NULL);
	goto bad;
    }
    maskColorIndex = -1;
    for (i = 0; i < xpm.ncolors; i++) {
        char *colorName;

        if (xpm.colorTable[i].c_color) {
             colorName = xpm.colorTable[i].c_color;
	} else if (xpm.colorTable[i].g_color) {
             colorName = xpm.colorTable[i].g_color;
	} else if (xpm.colorTable[i].g4_color) {
             colorName = xpm.colorTable[i].g4_color;
	} else if (xpm.colorTable[i].m_color) {
             colorName = xpm.colorTable[i].m_color;
	} else if (xpm.colorTable[i].symbolic) {
	    colorName = xpm.colorTable[i].symbolic;
	} else {
	    palette[i].u32 = 0xFFBEBEBE;
            continue;
	}
	if (strncmp(colorName, "None", 4) == 0) {
	    maskColorIndex = i;
	    palette[i].u32 = 0x00000000;
	    continue;
	}
	if (Blt_GetPixel(interp, colorName, palette + i) != TCL_OK) {
	    palette[i].u32 = 0xFFBEBEBE;
	}
    }
    {
	int y;
	unsigned int *pixelPtr;		/* Pointer */
	Blt_Pixel *destRowPtr;

	destRowPtr = destPtr->bits;
	pixelPtr = (unsigned int *)xpm.data;
	for (y = 0; y < xpm.height; y++) {
	    Blt_Pixel *dp, *dend;
	    
	    for (dp = destRowPtr, dend = dp + xpm.width; dp < dend; dp++) {
		if (*pixelPtr >= xpm.ncolors) {
		    Tcl_AppendResult(interp, "error reading \"", fileName, 
			"\" bad color index ", Blt_Itoa(*pixelPtr), 
			" in XPM image.", (char *)NULL);
		    goto bad;
		}
		if (*pixelPtr == maskColorIndex) {
		    destPtr->flags |= BLT_PIC_MASK;
		}
		*dp = palette[*pixelPtr];
		pixelPtr++;
	    }
	    destRowPtr += destPtr->pixelsPerRow;
	}
    }
    Blt_Free(palette);
    XpmFreeXpmImage(&xpm);
    if (destPtr != NULL) {
	Blt_Chain chain;

	chain = Blt_Chain_Create();
	Blt_Chain_Append(chain, destPtr);
	return chain;
    }
 bad:
    if (destPtr != NULL) {
	Blt_FreePicture(destPtr);
    }
    if (palette != NULL) {
	Blt_Free(palette);
    }
    XpmFreeXpmImage(&xpm);
    return NULL;
}

/*
 *---------------------------------------------------------------------------
 *
 * PictureToXpm --
 *
 *      Reads an XBM file and converts it into a picture.
 *
 * Results:
 *      The picture is returned.  If an error occured, such
 *	as the designated file could not be opened, NULL is returned.
 *
 *---------------------------------------------------------------------------
 */
static int
PictureToXpm(Tcl_Interp *interp, Blt_Picture original, Blt_DBuffer buffer,
	     XpmExportSwitches *switchesPtr)
{
    Picture *srcPtr;
    int nColors;
    Blt_HashTable colorTable;
    char fmt[20];
    int quantize;
    Blt_Pixel *bgColorPtr;

    quantize = ((switchesPtr->flags & PIC_NOQUANTIZE) == 0);
    bgColorPtr = &switchesPtr->bg;

    srcPtr = original;
    if (Blt_PictureIsBlended(srcPtr)) {
	Blt_Picture background, mask;
	Blt_Pixel black, white;

	background = Blt_CreatePicture(srcPtr->width, srcPtr->height);
	Blt_BlankPicture(background, bgColorPtr);

	mask = Blt_CreatePicture(srcPtr->width, srcPtr->height);
	/* Don't select 100% transparent pixels */
	white.u32 = 0xFFFFFFFF;
	black.u32 = 0x01000000;
	Blt_SelectPixels(mask, srcPtr, &black, &white);
	Blt_BlendPictures(background, srcPtr, 0, 0, srcPtr->width, 
		srcPtr->height, 0, 0);

	/* Put back the mask by and-ing the pictures together */
	Blt_AndPictures(background, mask);
	if (srcPtr != original) {
	    Blt_FreePicture(srcPtr);
	}
	srcPtr = background;
    }
    if (Blt_PictureFlags(srcPtr) & BLT_PIC_ASSOCIATED_COLORS) {
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
    nColors = Blt_QueryColors(srcPtr, (Blt_HashTable *)NULL);
    if ((quantize) && (nColors > 256)) {
	Blt_Picture quant;

	quant = Blt_QuantizePicture(srcPtr, 256);
	if (srcPtr != original) {
	    Blt_FreePicture(srcPtr);
	}
	srcPtr = quant;
    }
    Blt_InitHashTable(&colorTable, BLT_ONE_WORD_KEYS);
    nColors = Blt_QueryColors(srcPtr, &colorTable);
    if (Blt_PictureIsMasked(srcPtr)) {
	nColors++;
    }
    /* Header. */
    {
	unsigned int size;
	int cpp;

	cpp = 1;
	size = 16;
	while (size < nColors) {
	    size *= 16;
	    cpp++;
	}
	sprintf_s(fmt, 20, "%%0%dx", cpp);
	/* Write the header line */
	Blt_DBuffer_Print(buffer, "/* XPM */\n");
	Blt_DBuffer_Print(buffer, "static char * image_name[] = {\n");
	Blt_DBuffer_Print(buffer, "    /* Creator: BLT %s */\n", BLT_VERSION);
	Blt_DBuffer_Print(buffer, "    \"%d %d %d %d\",\n", srcPtr->width, 
		      srcPtr->height, nColors, cpp);
	Blt_DBuffer_Print(buffer, "    /* Colors used: %d */\n", nColors);
    }

    /* Color table. */
    {
	unsigned long i;
	const char *colorkey;
	Blt_HashEntry *hPtr;
	Blt_HashSearch cursor;

	colorkey = (Blt_PictureIsColor(srcPtr)) ? "c" : "m";
	i = 0;
	Blt_DBuffer_Print(buffer, "    ");
	for (hPtr = Blt_FirstHashEntry(&colorTable, &cursor); hPtr != NULL;
	     hPtr = Blt_NextHashEntry(&cursor)) {
	    Blt_Pixel pixel;
	    unsigned long key;

	    Blt_SetHashValue(hPtr, i);
	    key = (unsigned long)Blt_GetHashKey(&colorTable, hPtr);
	    pixel.u32 = (unsigned int)key;
	    Blt_DBuffer_Print(buffer, "\"");
	    Blt_DBuffer_Print(buffer, fmt, i);
	    Blt_DBuffer_Print(buffer, " %s #%02x%02x%02x\", ", colorkey, 
		pixel.Red, pixel.Green, pixel.Blue);
	    i++;
	    if ((i % 4) == 0) {
		Blt_DBuffer_Print(buffer, "\n    ");
	    }
	}
	if (Blt_PictureIsMasked(srcPtr)) {
	    i++;
	    Blt_DBuffer_Print(buffer, "\"");
	    Blt_DBuffer_Print(buffer, fmt, i);
	    Blt_DBuffer_Print(buffer, " %s None\",\n", colorkey, i);
	}	    
	if ((i % 4) != 0) {
	    Blt_DBuffer_Print(buffer, "\n");
	}
    }
    /* Image data. */
    {
	Blt_Pixel *srcRowPtr;
	int y;
	int count;

	srcRowPtr = srcPtr->bits;
	count = 0;
	for (y = 0; y < srcPtr->height; y++) {
	    Blt_Pixel *sp, *send;
	    Blt_DBuffer_Print(buffer, "\"");
	    for (sp = srcRowPtr, send = sp + srcPtr->width; sp < send; sp++) {
		Blt_HashEntry *hPtr;
		unsigned long i;
		unsigned long key;
		Blt_Pixel pixel;

		pixel.u32 = sp->u32;
		pixel.Alpha = 0xFF;
		key = (unsigned long)pixel.u32;
		hPtr = Blt_FindHashEntry(&colorTable, (char *)key);
		if (hPtr == NULL) {
		    fprintf(stderr, "can't find %x\n", sp->u32);
		    Blt_DBuffer_Print(buffer, fmt, nColors);
		    continue;
		}
		if (sp->Alpha == 0x00) {
		    i = (unsigned long)nColors;
		} else {
		    i = (unsigned long)Blt_GetHashValue(hPtr);
		}
		Blt_DBuffer_Print(buffer, fmt, i);
	    }
	    Blt_DBuffer_Print(buffer, "\",\n");
	    srcRowPtr += srcPtr->pixelsPerRow;
	}
    } 
    Blt_DBuffer_Print(buffer, "};\n");
    if (srcPtr != original) {
	Blt_FreePicture(srcPtr);
    }
    Blt_DeleteHashTable(&colorTable);
    return TCL_OK;
}

static Blt_Chain
ReadXpm(Tcl_Interp *interp, const char *fileName, Blt_DBuffer buffer)
{
    XpmImportSwitches switches;

    memset(&switches, 0, sizeof(switches));
    return XpmToPicture(interp, fileName, buffer, &switches);
}

static Tcl_Obj *
WriteXpm(Tcl_Interp *interp, Blt_Picture picture)
{
    Tcl_Obj *objPtr;
    Blt_DBuffer buffer;
    XpmExportSwitches switches;
    int result;
    
    /* Default export switch settings. */
    memset(&switches, 0, sizeof(switches));
    switches.bg.u32 = 0xFFFFFFFF; /* white */
    buffer = Blt_DBuffer_Create();
    result = PictureToXpm(interp, picture, buffer, &switches);
    objPtr = NULL;
    if (result == TCL_OK) {
	objPtr = Tcl_NewStringObj((char *)Blt_DBuffer_Bytes(buffer), 
		Blt_DBuffer_Length(buffer));
    }
    Blt_DBuffer_Destroy(buffer);
    return objPtr;
}

static Blt_Chain
ImportXpm(
    Tcl_Interp *interp, 
    int objc,
    Tcl_Obj *const *objv,
    const char **fileNamePtr)
{
    Blt_Chain chain;
    Blt_DBuffer buffer;
    XpmImportSwitches switches;
    const char *string;

    memset(&switches, 0, sizeof(switches));
    if (Blt_ParseSwitches(interp, importSwitches, objc - 3, objv + 3, 
	&switches, BLT_SWITCH_DEFAULTS) < 0) {
	return NULL;
    }
    if ((switches.dataObjPtr != NULL) && (switches.fileObjPtr != NULL)) {
	Tcl_AppendResult(interp, "more than one import source: ",
		"use only one -file or -data flag.", (char *)NULL);
	return NULL;
    }
    chain = NULL;
    buffer = Blt_DBuffer_Create();
    if (switches.dataObjPtr != NULL) {
	int nBytes;

	string = Tcl_GetStringFromObj(switches.dataObjPtr, &nBytes);
	Blt_DBuffer_AppendData(buffer, (unsigned char *)string, nBytes);
	string = "data buffer";
	*fileNamePtr = NULL;
    } else {
	string = Tcl_GetString(switches.fileObjPtr);
	if (Blt_DBuffer_LoadFile(interp, string, buffer) != TCL_OK) {
	    Blt_DBuffer_Destroy(buffer);
	    return NULL;
	}
	*fileNamePtr = string;
    }
    chain = XpmToPicture(interp, string, buffer, &switches);
    Blt_DBuffer_Destroy(buffer);
    return chain;
}

static int
ExportXpm(Tcl_Interp *interp, unsigned int index, Blt_Chain chain, int objc, 
	  Tcl_Obj *const *objv)
{
    Blt_DBuffer buffer;
    Blt_Picture picture;
    XpmExportSwitches switches;
    int result;

    memset(&switches, 0, sizeof(switches));
    switches.bg.u32 = 0xFFFFFFFF; /* Default bgcolor is white. */
    switches.index = index;
    if (Blt_ParseSwitches(interp, exportSwitches, objc - 3, objv + 3, 
	&switches, BLT_SWITCH_DEFAULTS) < 0) {
	return TCL_ERROR;
    }
    if ((switches.dataObjPtr != NULL) && (switches.fileObjPtr != NULL)) {
	Tcl_AppendResult(interp, "more than one export destination: ",
		"use only one -file or -data switch.", (char *)NULL);
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
    result = PictureToXpm(interp, picture, buffer, &switches);
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
Blt_PictureXpmInit(Tcl_Interp *interp)
{
#ifdef USE_TCL_STUBS
    if (Tcl_InitStubs(interp, TCL_VERSION, 1) == NULL) {
	return TCL_ERROR;
    };
#endif
    if (Tcl_PkgRequire(interp, "blt_extra", BLT_VERSION, /*Exact*/1) == NULL) {
	return TCL_ERROR;
    }
    if (Tcl_PkgProvide(interp, "blt_picture_xpm", BLT_VERSION) != TCL_OK) {
	return TCL_ERROR;
    }
    return Blt_PictureRegisterFormat(interp,
	"xpm",			/* Name of format. */
	IsXpm,			/* Discovery routine. */
	ReadXpm,		/* Read format procedure. */
	WriteXpm,		/* Write format procedure. */
	ImportXpm,		/* Import format procedure. */
	ExportXpm);		/* Export format procedure. */
}

#endif /* HAVE_LIBXPM */
 
