
/*
 * bltWindow.c --
 *
 * This module implements additional window functions for the BLT
 * toolkit.
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

#include <X11/Xlib.h>
#ifdef notdef /* WIN32 */
#include <X11/Xproto.h>
#endif
#include "tkDisplay.h"
#include "bltHash.h"

/* 
 * Cache drawable information.
 *
 * There are specific times when we need information about the drawable
 * that is not available via the normal argument passing.  For example,
 * XFT font rendering requires that the correct depth XftDraw be used.
 * If we create a painter from a drawable, we need to know its depth,
 * colormap, and visual also.
 * 
 * We can usually get this information using XGetWindowAttributes at
 * the cost of a round-trip to the X server.  Instead we'll cache it
 * in a hash table.  We don't have to cache every window. We need to
 * watch destroy events and freeing pixmaps.
 */

typedef struct {
    Display *display;
    Drawable drawable;
} DrawableKey;

static Blt_HashTable attribTable;
static int initialized = FALSE;

Blt_DrawableAttributes *
Blt_GetDrawableAttribs(Display *display, Drawable drawable)
{
    if (drawable != None) {
	Blt_HashEntry *hPtr;
	DrawableKey key;

	if (!initialized) {
	    Blt_InitHashTable(&attribTable, sizeof(DrawableKey));
	    initialized = TRUE;
	}
	key.drawable = drawable;
	key.display = display;
	hPtr = Blt_FindHashEntry(&attribTable, &key);
	if (hPtr != NULL) {
	    return Blt_GetHashValue(hPtr);
	}
    }
    return NULL;		/* Don't have any information about this
				 * drawable. */
}

void
Blt_SetDrawableAttribs(
    Display *display,
    Drawable drawable, 
    int depth,
    int width, int height,
    Colormap colormap,
    Visual *visual)
{
    if (drawable != None) {
	Blt_DrawableAttributes *attrPtr;
	Blt_HashEntry *hPtr;
	int isNew;
	DrawableKey key;

	if (!initialized) {
	    Blt_InitHashTable(&attribTable, sizeof(DrawableKey));
	    initialized = TRUE;
	}
	key.drawable = drawable;
	key.display = display;
	hPtr = Blt_CreateHashEntry(&attribTable, &key, &isNew);
	if (isNew) {
	    attrPtr = Blt_AssertMalloc(sizeof(Blt_DrawableAttributes));
	    Blt_SetHashValue(hPtr, attrPtr);
	}  else {
	    attrPtr = Blt_GetHashValue(hPtr);
	}
	/* Set or reset information for drawable. */
	attrPtr->id = drawable;
	attrPtr->depth = depth;
	attrPtr->colormap = colormap;
	attrPtr->visual = visual;
	attrPtr->width = width;
	attrPtr->height = height;
    }
}

void
Blt_SetDrawableAttribsFromWindow(Tk_Window tkwin, Drawable drawable)
{
    if (drawable != None) {
	Blt_SetDrawableAttribs(Tk_Display(tkwin), drawable, Tk_Width(tkwin), 
		Tk_Height(tkwin), Tk_Depth(tkwin), Tk_Colormap(tkwin), 
		Tk_Visual(tkwin));
    }
}

void
Blt_FreeDrawableAttribs(Display *display, Drawable drawable)
{
    Blt_HashEntry *hPtr;
    DrawableKey key;

    if (drawable != None) {
	if (!initialized) {
	    Blt_InitHashTable(&attribTable, sizeof(DrawableKey));
	    initialized = TRUE;
	}
	key.drawable = drawable;
	key.display = display;
	hPtr = Blt_FindHashEntry(&attribTable, &key);
	if (hPtr != NULL) {
	    Blt_DrawableAttributes *attrPtr;
	    
	    attrPtr = Blt_GetHashValue(hPtr);
	    Blt_DeleteHashEntry(&attribTable, hPtr);
	    Blt_Free(attrPtr);
	}
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_FindChild --
 *
 *      Performs a linear search for the named child window in a given
 *	parent window.
 *
 *	This can be done via Tcl, but not through Tk's C API.  It's 
 *	simple enough, if you peek into the Tk_Window structure.
 *
 * Results:
 *      The child Tk_Window. If the named child can't be found, NULL
 *	is returned.
 *
 *---------------------------------------------------------------------------
 */

/*LINTLIBRARY*/
Tk_Window
Blt_FindChild(Tk_Window parent, char *name)
{
    TkWindow *winPtr;
    TkWindow *parentPtr = (TkWindow *)parent;

    for (winPtr = parentPtr->childList; winPtr != NULL; 
	winPtr = winPtr->nextPtr) {
	if (strcmp(name, winPtr->nameUid) == 0) {
	    return (Tk_Window)winPtr;
	}
    }
    return NULL;
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_FirstChildWindow --
 *
 *      Performs a linear search for the named child window in a given
 *	parent window.
 *
 *	This can be done via Tcl, but not through Tk's C API.  It's 
 *	simple enough, if you peek into the Tk_Window structure.
 *
 * Results:
 *      The child Tk_Window. If the named child can't be found, NULL
 *	is returned.
 *
 *---------------------------------------------------------------------------
 */
/*LINTLIBRARY*/
Tk_Window
Blt_FirstChild(Tk_Window parent)
{
    TkWindow *parentPtr = (TkWindow *)parent;
    return (Tk_Window)parentPtr->childList;
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_FindChild --
 *
 *      Performs a linear search for the named child window in a given
 *	parent window.
 *
 *	This can be done via Tcl, but not through Tk's C API.  It's 
 *	simple enough, if you peek into the Tk_Window structure.
 *
 * Results:
 *      The child Tk_Window. If the named child can't be found, NULL
 *	is returned.
 *
 *---------------------------------------------------------------------------
 */

/*LINTLIBRARY*/
Tk_Window
Blt_NextChild(Tk_Window tkwin)
{
    TkWindow *winPtr = (TkWindow *)tkwin;

    if (winPtr == NULL) {
	return NULL;
    }
    return (Tk_Window)winPtr->nextPtr;
}

/*
 *---------------------------------------------------------------------------
 *
 * UnlinkWindow --
 *
 *	This procedure removes a window from the childList of its
 *	parent.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The window is unlinked from its childList.
 *
 *---------------------------------------------------------------------------
 */
static void
UnlinkWindow(TkWindow *winPtr)
{
    TkWindow *prevPtr;

    prevPtr = winPtr->parentPtr->childList;
    if (prevPtr == winPtr) {
	winPtr->parentPtr->childList = winPtr->nextPtr;
	if (winPtr->nextPtr == NULL) {
	    winPtr->parentPtr->lastChildPtr = NULL;
	}
    } else {
	while (prevPtr->nextPtr != winPtr) {
	    prevPtr = prevPtr->nextPtr;
	    if (prevPtr == NULL) {
		panic("UnlinkWindow couldn't find child in parent");
	    }
	}
	prevPtr->nextPtr = winPtr->nextPtr;
	if (winPtr->nextPtr == NULL) {
	    winPtr->parentPtr->lastChildPtr = prevPtr;
	}
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_RelinkWindow --
 *
 *	Relinks a window into a new parent.  The window is unlinked
 *	from its original parent's child list and added onto the end
 *	of the new parent's list.
 *
 *	FIXME:  If the window has focus, the focus should be moved
 *		to an ancestor.  Otherwise, Tk becomes confused 
 *		about which Toplevel turns on focus for the window. 
 *		Right now this is done at the TCL layer.  For example,
 *		see blt::CreateTearoff in tabset.tcl.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The window is unlinked from its childList.
 *
 *---------------------------------------------------------------------------
 */
void
Blt_RelinkWindow(
    Tk_Window tkwin,		/* Child window to be linked. */
    Tk_Window newParent,
    int x, int y)
{
    TkWindow *winPtr, *parentWinPtr;

    if (Blt_ReparentWindow(Tk_Display(tkwin), Tk_WindowId(tkwin), 
		Tk_WindowId(newParent), x, y) != TCL_OK) {
	return;
    }
    winPtr = (TkWindow *)tkwin;
    parentWinPtr = (TkWindow *)newParent;

    winPtr->flags &= ~TK_REPARENTED;
    UnlinkWindow(winPtr);	/* Remove the window from its parent's list */

    /* Append the window onto the end of the parent's list of children */
    winPtr->parentPtr = parentWinPtr;
    winPtr->nextPtr = NULL;
    if (parentWinPtr->childList == NULL) {
	parentWinPtr->childList = winPtr;
    } else {
	parentWinPtr->lastChildPtr->nextPtr = winPtr;
    }
    parentWinPtr->lastChildPtr = winPtr;
}

#ifdef notdef
/*
 *---------------------------------------------------------------------------
 *
 * Blt_RelinkWindow --
 *
 *	Relinks a window into a new parent.  The window is unlinked
 *	from its original parent's child list and added onto the end
 *	of the new parent's list.
 *
 *	FIXME:  If the window has focus, the focus should be moved
 *		to an ancestor.  Otherwise, Tk becomes confused 
 *		about which Toplevel turns on focus for the window. 
 *		Right now this is done at the TCL layer.  For example,
 *		see blt::CreateTearoff in tabset.tcl.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The window is unlinked from its childList.
 *
 *---------------------------------------------------------------------------
 */
void
Blt_RelinkWindow2(
    Tk_Window tkwin,		/* Child window to be linked. */
    Window window,
    Tk_Window newParent,
    int x, int y)
{
#ifdef notdef
    TkWindow *winPtr, *parentWinPtr;
#endif
    if (Blt_ReparentWindow(Tk_Display(tkwin), window,
	    Tk_WindowId(newParent), x, y) != TCL_OK) {
	return;
    }
#ifdef notdef
    winPtr = (TkWindow *)tkwin;
    parentWinPtr = (TkWindow *)newParent;

    winPtr->flags &= ~TK_REPARENTED;
    UnlinkWindow(winPtr);	/* Remove the window from its parent's list */

    /* Append the window onto the end of the parent's list of children */
    winPtr->parentPtr = parentWinPtr;
    winPtr->nextPtr = NULL;
    if (parentWinPtr->childList == NULL) {
	parentWinPtr->childList = winPtr;
    } else {
	parentWinPtr->lastChildPtr->nextPtr = winPtr;
    }
    parentWinPtr->lastChildPtr = winPtr;
#endif
}

void
Blt_UnlinkWindow(Tk_Window tkwin) /* Child window to be linked. */
{
    TkWindow *winPtr;
    Window root;

    root = Tk_RootWindow(tkwin);
    if (Blt_ReparentWindow(Tk_Display(tkwin), Tk_WindowId(tkwin), root, 0, 0) 
	!= TCL_OK) {
	return;
    }
    winPtr = (TkWindow *)tkwin;
    winPtr->flags &= ~TK_REPARENTED;
#ifdef notdef
    UnlinkWindow(winPtr);	/* Remove the window from its parent's list */
#endif
}
#endif

/*
 *---------------------------------------------------------------------------
 *
 * Blt_Toplevel --
 *
 *      Climbs up the widget hierarchy to find the top level window of
 *      the window given.
 *
 * Results:
 *      Returns the Tk_Window of the toplevel widget.
 *
 *---------------------------------------------------------------------------
 */
Tk_Window
Blt_Toplevel(Tk_Window tkwin)
{
    while (!Tk_IsTopLevel(tkwin)) {
	tkwin = Tk_Parent(tkwin);
    }
    return tkwin;
}

void
Blt_RootCoordinates(
    Tk_Window tkwin, 
    int x, int y, 
    int *rootXPtr, int *rootYPtr)
{
    int vx, vy, vw, vh;
    int rootX, rootY;

    Tk_GetRootCoords(tkwin, &rootX, &rootY);
    x += rootX;
    y += rootY;
    Tk_GetVRootGeometry(tkwin, &vx, &vy, &vw, &vh);
    x += vx;
    y += vy;
    *rootXPtr = x;
    *rootYPtr = y;
}


/* Find the toplevel then  */
int
Blt_RootX(Tk_Window tkwin)
{
    int x;
    
    for (x = 0; tkwin != NULL;  tkwin = Tk_Parent(tkwin)) {
	x += Tk_X(tkwin) + Tk_Changes(tkwin)->border_width;
	if (Tk_IsTopLevel(tkwin)) {
	    break;
	}
    }
    return x;
}

int
Blt_RootY(Tk_Window tkwin)
{
    int y;
    
    for (y = 0; tkwin != NULL;  tkwin = Tk_Parent(tkwin)) {
	y += Tk_Y(tkwin) + Tk_Changes(tkwin)->border_width;
	if (Tk_IsTopLevel(tkwin)) {
	    break;
	}
    }
    return y;
}

void
Blt_SetWindowInstanceData(Tk_Window tkwin, ClientData instanceData)
{
    TkWindow *winPtr = (TkWindow *)tkwin;

    winPtr->instanceData = instanceData;
}

ClientData
Blt_GetWindowInstanceData(Tk_Window tkwin)
{
    TkWindow *winPtr;

    while (tkwin != NULL) {
	winPtr = (TkWindow *)tkwin;
	if (winPtr->instanceData != NULL) {
	    return (ClientData)winPtr->instanceData;
	}
	tkwin = Tk_Parent(tkwin);
    }
    return NULL;
}

void
Blt_DeleteWindowInstanceData(Tk_Window tkwin)
{
    /* empty */
}
