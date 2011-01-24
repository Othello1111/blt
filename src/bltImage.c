
/*
 * bltImage.c --
 *
 * This module implements image processing procedures for the BLT toolkit.
 *
 *	Copyright 1997-2004 George A Howlett.
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a
 *	copy of this software and associated documentation files (the
 *	"Software"), to deal in the Software without restriction, including
 *	without limitation the rights to use, copy, modify, merge, publish,
 *	distribute, sublicense, and/or sell copies of the Software, and to
 *	permit persons to whom the Software is furnished to do so, subject to
 *	the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included
 *	in all copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 *	OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *	LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *	OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *	WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "bltInt.h"
#include "bltImage.h"
#include <X11/Xutil.h>

/*
 * Each call to Tk_GetImage returns a pointer to one of the following
 * structures, which is used as a token by clients (widgets) that display
 * images.
 */
typedef struct _TkImage {
    Tk_Window tkwin;			/* Window passed to Tk_GetImage (needed
					 * to "re-get" the image later if the *
					 * manager changes). */
    Display *display;			/* Display for tkwin.  Needed because
					 * when the image is eventually freed
					 * tkwin may not exist anymore. */
    struct _TkImageMaster *masterPtr;	/* Master for this image (identifiers
					 * image manager, for example). */
    ClientData instanceData;		/* One word argument to pass to image
					 * manager when dealing with this image
					 * instance. */
    Tk_ImageChangedProc *changeProc;	/* Code in widget to call when image
					 * changes in a way that affects
					 * redisplay. */
    ClientData widgetClientData;	/* Argument to pass to changeProc. */
    struct _TkImage *nextPtr;		/* Next in list of all image instances
					 * associated with the same name. */
} TkImage;

/*
 * For each image master there is one of the following structures, which
 * represents a name in the image table and all of the images instantiated from
 * it.  Entries in mainPtr->imageTable point to these structures.
 */
typedef struct _TkImageMaster {
    Tk_ImageType *typePtr;		/* Information about image type.  NULL
					 * means that no image manager owns this
					 * image: the image was deleted. */
    ClientData masterData;		/* One-word argument to pass to image
					 * mgr when dealing with the master, as
					 * opposed to instances. */
    int width, height;			/* Last known dimensions for image. */
    void *tablePtr;			/* Pointer to hash table containing
					 * image (the imageTable field in some
					 * TkMainInfo structure). */
    void *hPtr;				/* Hash entry in mainPtr->imageTable for
					 * this structure (used to delete the
					 * hash entry). */
    void *instancePtr;			/* Pointer to first in list of instances
					 * derived from this name. */
    int deleted;			/* Flag set when image is being 
					 * deleted. */
    Tk_Window tkwin;			/* Main window of interpreter (used to
					 * detect when the world is falling
					 * apart.) */
} TkImageMaster;

/*
 *---------------------------------------------------------------------------
 *
 * Blt_Image_IsDeleted --
 *
 *	Is there any other way to determine if an image has been deleted?
 *
 * Results:
 *	Returns 1 if the image has been deleted, 0 otherwise.
 *
 *---------------------------------------------------------------------------
 */
/*LINTLIBRARY*/
int
Blt_Image_IsDeleted(Tk_Image tkImage)	/* Token for image. */
{
    TkImage *imagePtr = (TkImage *) tkImage;

    if (imagePtr->masterPtr == NULL) {
	return TRUE;
    }
    return (imagePtr->masterPtr->typePtr == NULL);
}

/*LINTLIBRARY*/
Tk_ImageMaster
Blt_Image_GetMaster(Tk_Image tkImage)	/* Token for image. */
{
    TkImage *imagePtr = (TkImage *)tkImage;

    return (Tk_ImageMaster)imagePtr->masterPtr;
}

/*LINTLIBRARY*/
ClientData
Blt_Image_GetInstanceData(Tk_Image tkImage) /* Token for image. */
{
    TkImage *imagePtr = (TkImage *)tkImage;

    return imagePtr->instanceData;
}

/*LINTLIBRARY*/
Tk_ImageType *
Blt_Image_GetType(Tk_Image tkImage)	/* Token for image. */
{
    TkImageMaster *masterPtr;

    masterPtr = (TkImageMaster *)Blt_Image_GetMaster(tkImage);
    return masterPtr->typePtr;
}

const char *
Blt_Image_Name(Tk_Image tkImage)
{
    Tk_ImageMaster master;

    master = Blt_Image_GetMaster(tkImage);
    return Tk_NameOfImage(master);
}

const char *
Blt_Image_NameOfType(Tk_Image tkImage)
{
    TkImageMaster *masterPtr;

    masterPtr = (TkImageMaster *)Blt_Image_GetMaster(tkImage);
    return masterPtr->typePtr->name;
}

