
/*
 * bltPicture.h --
 *
 *	Copyright 2004 George A Howlett.
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

#ifndef _BLT_PICTURE_H
#define _BLT_PICTURE_H

#include <bltHash.h>

/*
 *---------------------------------------------------------------------------
 *
 * Blt_Pixel --
 *
 *      A union representing either a pixel as a RGBA quartet or a single
 *      word value.
 *
 *---------------------------------------------------------------------------
 */
typedef union {
    unsigned int u32;		
    struct {
#ifdef WORDS_BIGENDIAN
	unsigned char a, r, g, b;
#else 
	unsigned char b, g, r, a;
#endif    
    } u8;
} Blt_Pixel;

#define Red	u8.r
#define Blue	u8.b
#define Green	u8.g
#define Alpha	u8.a

#define ALPHA_OPAQUE		(0xFF)
#define ALPHA_TRANSPARENT	(0)
#define MAXINTENSITY		(0xFF)

#define GAMMA	(1.0f)

struct _Blt_Ps;

/*
 *---------------------------------------------------------------------------
 *
 * Blt_Picture --
 *
 *      The structure below represents a picture.  Each pixel occupies a
 *      32-bit word of memory: one byte for each of the red, green, and blue
 *      color intensities, and another for alpha-channel image compositing
 *      (e.g. transparency).
 *
 *---------------------------------------------------------------------------
 */
struct _Blt_Picture {
    void *buffer;		/* Unaligned (malloc'ed) memory for pixels. */
    Blt_Pixel *bits;		/* Array of pixels containing the RGBA
				 * values. */
    short int delay;
    short int flags;		/* Flags describing the picture. */
    short int width, height;	/* Dimensions of the image in pixels. */
    short int pixelsPerRow;	/* Stride of the image. */
    short int reserved;
};

#define BLT_PIC_COLOR  (1<<0)	/* Indicates if color or greyscale. */
#define BLT_PIC_BLEND  (1<<1)	/* Picture has partial opaque pixels. */
#define BLT_PIC_MASK   (1<<2)	/* Pixels are either 100% opaque or
				 * transparent. The separate BLEND and MASK
				 * flags are so that don't premultiply alphas
				 * for masks. */

#define BLT_PIC_ASSOCIATED_COLORS (1<<3)
				/* Indicates if RGB components have been
				 * premultiplied by their alphas. */

#define BLT_PIC_DIRTY (1<<4)	/* Indicates that the picture contents have
				 * changed. Cached items may need to be
				 * refreshed. For example, may need to
				 * premultiply alphas again. */ 

#define BLT_PIC_FMT_ASCII		(1<<0)
#define BLT_PIC_FMT_LOADED		(1<<1)

#define BLT_PAINTER_DITHER		(1<<0)

#define BLT_PAINTER_BLEND_MASK		(0x0F)
#define BLT_PAINTER_BLEND_NONE		(0)
#define BLT_PAINTER_BLEND_MIN_ALPHAS	(1<<1)
#define BLT_PAINTER_BLEND_MAX_ALPHAS	(1<<2)
#define BLT_PAINTER_BLEND_DIFF		(1<<3)
#define BLT_PAINTER_BLEND_MULTIPLY	(1<<4)
#define BLT_PAINTER_BLEND_UNDER		(1<<6)

typedef enum GradientShapes {
    BLT_GRADIENT_SHAPE_LINEAR,
    BLT_GRADIENT_SHAPE_BILINEAR,
    BLT_GRADIENT_SHAPE_RADIAL,	
    BLT_GRADIENT_SHAPE_RECTANGULAR
} Blt_GradientShape;

typedef enum GradientPaths {
    BLT_GRADIENT_PATH_X,
    BLT_GRADIENT_PATH_Y,
    BLT_GRADIENT_PATH_XY,
    BLT_GRADIENT_PATH_YX,
} Blt_GradientPath;

typedef struct {
    Blt_GradientShape shape;	/* Determines the shape of gradient. */

    Blt_GradientPath path;	/* Determines the direction of a linear or
				 * bilinear gradient. */

    int logScale;		/* If non-zero, use a logarithmic scale to
				 * ramp colors. */

    int jitter;			/* If non-zero, add jitter error to
				 * gradient. */

} Blt_Gradient;

typedef struct _Blt_PictureImage *Blt_PictureImage;
typedef struct _Blt_ResampleFilter *Blt_ResampleFilter;
typedef struct _Blt_ConvolveFilter *Blt_ConvolveFilter;
typedef struct _Blt_Picture *Blt_Picture;

/*
 * Blt_Picture is supposed to be an opaque type.  Use the macros below to
 * access its members.
 */

#define Blt_PictureBits(p)	((p)->bits)
#define Blt_PictureFlags(p)	((p)->flags)
#define Blt_PictureHeight(p)	((p)->height)
#define Blt_PicturePixel(p,x,y) ((p)->bits + ((p)->pixelsPerRow * (y)) + (x))
#define Blt_PictureWidth(p)	((p)->width)
#define Blt_PictureStride(p)	((p)->pixelsPerRow)
#define Blt_PictureDelay(p)	((p)->delay)

#define Blt_PictureIsDirty(p)	((p)->flags & BLT_PIC_DIRTY)
#define Blt_PictureIsOpaque(p)	\
	(((p)->flags & (BLT_PIC_BLEND | BLT_PIC_MASK)) == 0)
#define Blt_PictureIsMasked(p)  ((p)->flags &  BLT_PIC_MASK) 
#define Blt_PictureIsBlended(p) ((p)->flags &  BLT_PIC_BLEND)
#define Blt_PictureIsColor(p)   ((p)->flags &  BLT_PIC_COLOR)
#define Blt_PictureIsGreyscale(p)   (!Blt_IsColorPicture(p))

typedef enum PictureArithOps {
    PIC_ARITH_ADD,
    PIC_ARITH_AND,
    PIC_ARITH_NAND,
    PIC_ARITH_NOR,
    PIC_ARITH_OR,
    PIC_ARITH_RSUB,
    PIC_ARITH_SUB,
    PIC_ARITH_XOR,
    PIC_ARITH_MIN,
    PIC_ARITH_MAX,
} Blt_PictureArithOps;

typedef struct {
    unsigned int x, y;
} PictureCoordinate;

typedef enum BlendingModes {
    BLT_BLEND_NORMAL,		/* C = F */
    BLT_BLEND_MULTIPLY,		/* C = F * B */
    BLT_BLEND_SCREEN,		/* C = 1 - (1 - F * B */
    BLT_BLEND_DARKEN,		/* C = min(F,B) */
    BLT_BLEND_LIGHTEN,		/* C = max(F,B) */
    BLT_BLEND_DIFFERENCE,	/* C = |F - B| */
    BLT_BLEND_HARDLIGHT,
    BLT_BLEND_SOFTLIGHT,
    BLT_BLEND_COLORDODGE,	/* C = B / (1 - F) */ 
    BLT_BLEND_COLORBURN,	/* C = (1 - B) / F */
    BLT_BLEND_OVERLAY,		/* C = B * (F + (2 * F) * (1 - B)) */
} Blt_BlendingMode;

BLT_EXTERN Blt_ResampleFilter bltBoxFilter; /* The ubiquitous box filter */
BLT_EXTERN Blt_ResampleFilter bltMitchellFilter; 
BLT_EXTERN Blt_ResampleFilter bltBellFilter; 
BLT_EXTERN Blt_ResampleFilter bltTentFilter; 

BLT_EXTERN Blt_ResampleFilter bltTableFilter;

typedef struct {
    int x, y, w, h;
} PictRegion;

#define Blt_AddPictures(dest, src) \
    Blt_ApplyPictureToPicture(dest, src, 0, 0, (src)->width, (src)->height, \
	0, 0, PIC_ARITH_ADD)
#define Blt_SubtractPictures(dest, src) \
    Blt_ApplyPictureToPicture(dest, src, 0, 0, (src)->width, (src)->height, \
	0, 0, PIC_ARITH_SUB)
#define Blt_AndPictures(dest, src) \
    Blt_ApplyPictureToPicture(dest, src, 0, 0, (src)->width, (src)->height, \
	0, 0, PIC_ARITH_AND)
#define Blt_OrPictures(dest, src) \
    Blt_ApplyPictureToPicture(dest, src, 0, 0, (src)->width, (src)->height, \
	0, 0, PIC_ARITH_OR)
#define Blt_XorPictures(dest, src) \
    Blt_ApplyPictureToPicture(dest, src, 0, 0, (src)->width, (src)->height, \
	0, 0, PIC_ARITH_XOR)

/* Prototypes of picture routines */

BLT_EXTERN void Blt_ApplyPictureToPicture(Blt_Picture dest, Blt_Picture src,
	int x, int y, int w, int h, int dx, int dy, Blt_PictureArithOps op);

BLT_EXTERN void Blt_ApplyScalarToPicture(Blt_Picture dest, Blt_Pixel *colorPtr, 
	Blt_PictureArithOps op);

BLT_EXTERN void Blt_ApplyPictureToPictureWithMask(Blt_Picture dest, 
	Blt_Picture src, Blt_Picture mask, int x, int y, int w, int h, 
	int dx, int dy, int invert, Blt_PictureArithOps op);

BLT_EXTERN void Blt_ApplyScalarToPictureWithMask(Blt_Picture dest, 
	Blt_Pixel *colorPtr, Blt_Picture mask, int invert, 
	Blt_PictureArithOps op);

BLT_EXTERN void Blt_MaskPicture(Blt_Picture dest, Blt_Picture mask, 
	int x, int y, int w, int h, int dx, int dy, Blt_Pixel *colorPtr);

BLT_EXTERN void Blt_BlankPicture(Blt_Picture picture, Blt_Pixel *colorPtr);
BLT_EXTERN void Blt_BlankRegion(Blt_Picture picture, int x, int y, int w, int h,
	 Blt_Pixel *colorPtr);

BLT_EXTERN void Blt_BlurPicture(Blt_Picture dest, Blt_Picture src, 
	unsigned int r);

BLT_EXTERN void Blt_ResizePicture(Blt_Picture picture, int w, int h);
BLT_EXTERN void Blt_AdjustPicture(Blt_Picture picture, int w, int h);

BLT_EXTERN Blt_Picture Blt_ClonePicture(Blt_Picture picture);

BLT_EXTERN void Blt_ConvolvePicture(Blt_Picture dest, Blt_Picture src, 
	Blt_ConvolveFilter vFilter, Blt_ConvolveFilter hFilter);

BLT_EXTERN Blt_Picture Blt_CreatePicture(int w, int h);

BLT_EXTERN Blt_Picture Blt_DitherPicture(Blt_Picture picture, 
	Blt_Pixel *palette);

BLT_EXTERN void Blt_FlipPicture(Blt_Picture picture, int vertically);

BLT_EXTERN void Blt_FreePicture(Blt_Picture picture);

BLT_EXTERN void Blt_GradientPicture(Blt_Picture picture, Blt_Pixel *highPtr, 
	Blt_Pixel *lowPtr, Blt_Gradient *gradientPtr);

BLT_EXTERN Blt_Picture Blt_GreyscalePicture(Blt_Picture picture);

BLT_EXTERN Blt_Picture Blt_QuantizePicture (Blt_Picture picture, int nColors);

BLT_EXTERN void Blt_ResamplePicture (Blt_Picture dest, Blt_Picture src, 
	Blt_ResampleFilter hFilter, Blt_ResampleFilter vFilter);

BLT_EXTERN Blt_Picture Blt_ScalePicture(Blt_Picture picture, int x, int y, 
	int w, int h, int dw, int dh);

BLT_EXTERN Blt_Picture Blt_ScalePictureArea(Blt_Picture picture, int x, int y,
	int w, int h, int dw, int dh);

BLT_EXTERN Blt_Picture Blt_RotatePicture (Blt_Picture picture, float angle);

BLT_EXTERN void Blt_TilePicture(Blt_Picture dest, Blt_Picture src, int xOrigin, 
	int yOrigin, int x, int y, int w, int h);

BLT_EXTERN int Blt_PictureToPsData(Blt_Picture picture, int nComponents, 
	Tcl_DString *resultPtr, const char *prefix);

BLT_EXTERN void Blt_SelectPixels(Blt_Picture dest, Blt_Picture src, 
	Blt_Pixel *lowerPtr, Blt_Pixel *upperPtr);

BLT_EXTERN int Blt_GetPicture(Tcl_Interp *interp, const char *string, 
	Blt_Picture *picturePtr);

BLT_EXTERN int Blt_GetPictureFromObj(Tcl_Interp *interp, Tcl_Obj *objPtr, 
	Blt_Picture *picturePtr);

BLT_EXTERN int Blt_GetResampleFilterFromObj(Tcl_Interp *interp, Tcl_Obj *objPtr,
	Blt_ResampleFilter *filterPtr);

BLT_EXTERN const char *Blt_NameOfResampleFilter(Blt_ResampleFilter filter);

BLT_EXTERN void Blt_AssociateColors(Blt_Picture picture);

BLT_EXTERN void Blt_UnassociateColors(Blt_Picture picture);

BLT_EXTERN void Blt_MultiplyPixels(Blt_Picture picture, float value);

BLT_EXTERN int Blt_GetBBoxFromObjv(Tcl_Interp *interp, int objc, 
	Tcl_Obj *const *objv, PictRegion *regionPtr);

BLT_EXTERN int Blt_AdjustRegionToPicture(Blt_Picture picture, 
	PictRegion *regionPtr);

BLT_EXTERN int Blt_GetPixelFromObj(Tcl_Interp *interp, Tcl_Obj *objPtr, 
	Blt_Pixel *pixelPtr);

BLT_EXTERN int Blt_GetPixel(Tcl_Interp *interp, const char *string, 
	Blt_Pixel *pixelPtr);

BLT_EXTERN const char *Blt_NameOfPixel(Blt_Pixel *pixelPtr);

BLT_EXTERN Blt_Picture Blt_PictureFromPictImage(Blt_PictureImage image);

BLT_EXTERN void Blt_NotifyImageChanged(Blt_PictureImage image);

BLT_EXTERN int Blt_QueryColors(Blt_Picture picture, Blt_HashTable *tablePtr);

BLT_EXTERN void Blt_ClassifyPicture(Blt_Picture picture);

BLT_EXTERN void Blt_TentHorizontally(Blt_Picture dest, Blt_Picture src);
BLT_EXTERN void Blt_TentVertically(Blt_Picture dest, Blt_Picture src);
BLT_EXTERN void Blt_ZoomHorizontally(Blt_Picture dest, Blt_Picture src, 
	Blt_ResampleFilter filter);
BLT_EXTERN void Blt_ZoomVertically(Blt_Picture dest, Blt_Picture src, 
	Blt_ResampleFilter filter);
BLT_EXTERN void Blt_BlendPictures(Blt_Picture dest, Blt_Picture src, 
	int sx, int sy, int w, int h, int dx, int dy);

BLT_EXTERN void Blt_BlendPicturesByMode(Blt_Picture dest, Blt_Picture src, 
	Blt_BlendingMode mode);

BLT_EXTERN void Blt_SelectPixelsP(Blt_Picture dest, Blt_Picture src, 
	Blt_Pixel *lowPtr , Blt_Pixel *highPtr);

BLT_EXTERN void Blt_FadePicture(Blt_Picture dest, Blt_Picture src, 
	int sx, int sy, int w, int h, int dx, int dy, int alpha);

BLT_EXTERN void Blt_CopyPictureBits(Blt_Picture dest, Blt_Picture src, 
	int sx, int sy, int w, int h, int dx, int dy);

BLT_EXTERN void Blt_GammaCorrectPicture(Blt_Picture dest, Blt_Picture src, 
	float gamma);

BLT_EXTERN void Blt_SharpenPicture(Blt_Picture dest, Blt_Picture src);

BLT_EXTERN void Blt_TexturePicture(Blt_Picture picture, Blt_Pixel *lowPtr, 
	Blt_Pixel *highPtr, int type);

BLT_EXTERN void Blt_ApplyColorToPicture(Blt_Picture pict, Blt_Pixel *colorPtr);

BLT_EXTERN void Blt_SizeOfPicture(Blt_Picture pict, int *wPtr, int *hPtr);

#ifdef _BLT_DBUFFER_H
BLT_EXTERN Blt_DBuffer Blt_PictureToDBuffer(Blt_Picture picture, int nComp);
#endif	/* _BLT_DBUFFER_H */

#ifdef _TK
BLT_EXTERN Blt_Picture Blt_PhotoToPicture (Tk_PhotoHandle photo);
BLT_EXTERN Blt_Picture Blt_PhotoAreaToPicture (Tk_PhotoHandle photo, 
	int x, int y, int w, int h);
BLT_EXTERN Blt_Picture Blt_DrawableToPicture(Tk_Window tkwin, 
 	Drawable drawable, int x, int y, int w, int h, float gamma);
BLT_EXTERN Blt_Picture Blt_WindowToPicture(Display *display, 
	Drawable drawable, int x, int y, int w, int h, float gamma);
BLT_EXTERN void Blt_PictureToPhoto(Blt_Picture picture, Tk_PhotoHandle photo);
BLT_EXTERN int Blt_SnapPhoto(Tcl_Interp *interp, Tk_Window tkwin, 
	Drawable drawable, int sx, int sy, int w, int h, int dw, int dh, 
	const char *photoName, float gamma);
BLT_EXTERN int Blt_SnapPicture(Tcl_Interp *interp, Tk_Window tkwin, 
	Drawable drawable, int sx, int sy, int w, int h, int dw, int dh, 
	const char *imageName, float gamma);
BLT_EXTERN Blt_Picture Blt_BitmapToPicture(Display *display, Pixmap bitmap,
	int w, int h, Blt_Pixel *fg, Blt_Pixel *bg);
BLT_EXTERN Blt_Pixel Blt_XColorToPixel(XColor *colorPtr);
BLT_EXTERN int Blt_IsPicture(Tk_Image tkImage);
BLT_EXTERN Blt_Picture Blt_GetPictureFromImage(Tk_Image tkImage);
#endif	/* _TK */

#endif /*_BLT_PICTURE_H*/
