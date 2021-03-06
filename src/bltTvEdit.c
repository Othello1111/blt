
/*
  Remember row,column where string was acquired.
  postcombobox x y 
	icon?, text, row, column position, fg, bg button?
	based upon style.
  grab set
  SetIcon
  SetText
  SetBg
  SetFg
  SetFont
  SetButton  
 */

/*
 * bltTvEdit.c --
 *
 * This module implements an hierarchy widget for the BLT toolkit.
 *
 *	Copyright 1998-2004 George A Howlett.
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

#ifndef NO_TREEVIEW
#include "bltOp.h"
#include "bltTreeView.h"
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#define TEXTBOX_FOCUS	(1<<0)
#define TEXTBOX_REDRAW	(1<<1)

static Tcl_IdleProc DisplayTextbox;
static Tcl_FreeProc DestroyTextbox;
static Tcl_TimerProc BlinkCursorProc;
static Tcl_ObjCmdProc TextboxCmd;

/*
 * Textbox --
 *
 *	This structure is shared by entries when their labels are
 *	edited via the keyboard.  It maintains the location of the
 *	insertion cursor and the text selection for the editted entry.
 *	The structure is shared since we need only one.  The "focus"
 *	entry should be the only entry receiving KeyPress/KeyRelease
 *	events at any time.  Information from the previously editted
 *	entry is overwritten.
 *
 *	Note that all the indices internally are in terms of bytes,
 *	not characters.  This is because UTF-8 strings may encode a
 *	single character into a multi-byte sequence.  To find the
 *	respective character position
 *
 *		n = Tcl_NumUtfChars(string, index);
 *
 *	where n is the resulting character number.
 */
typedef struct {

    /*
     * This is a SNAFU in the Tk API.  It assumes that only an official
     * Tk "toplevel" widget will ever become a toplevel window (i.e. a
     * window whose parent is the root window).  Because under Win32,
     * Tk tries to use the widget record associated with the TopLevel
     * as a Tk frame widget, to read its menu name.  What this means
     * is that any widget that's going to be a toplevel, must also look
     * like a frame. Therefore we've copied the frame widget structure
     * fields into the token.
     */

    Tk_Window tkwin;		/* Window that embodies the frame.  NULL
				 * means that the window has been destroyed
				 * but the data structures haven't yet been
				 * cleaned up. */
    Display *display;		/* Display containing widget.  Used, among
				 * other things, so that resources can be
				 * freed even after tkwin has gone away. */
    Tcl_Interp *interp;		/* Interpreter associated with widget.  Used
				 * to delete widget command. */
    Tcl_Command widgetCmd;	/* Token for frame's widget command. */
    char *className;		/* Class name for widget (from configuration
				 * option).  Malloc-ed. */
    int mask;			/* Either FRAME or TOPLEVEL;  used to select
				 * which configuration options are valid for
				 * widget. */
    char *screenName;		/* Screen on which widget is created.  Non-null
				 * only for top-levels.  Malloc-ed, may be
				 * NULL. */
    char *visualName;		/* Textual description of visual for window,
				 * from -visual option.  Malloc-ed, may be
				 * NULL. */
    char *colormapName;		/* Textual description of colormap for window,
				 * from -colormap option.  Malloc-ed, may be
				 * NULL. */
    char *menuName;		/* Textual description of menu to use for
				 * menubar. Malloc-ed, may be NULL. */
    Colormap colormap;		/* If not None, identifies a colormap
				 * allocated for this window, which must be
				 * freed when the window is deleted. */
    Tk_3DBorder border;		/* Structure used to draw 3-D border and
				 * background.  NULL means no background
				 * or border. */
    int borderWidth;		/* Width of 3-D border (if any). */
    int relief;			/* 3-d effect: TK_RELIEF_RAISED etc. */
    int highlightWidth;		/* Width in pixels of highlight to draw
				 * around widget when it has the focus.
				 * 0 means don't draw a highlight. */
    XColor *highlightBgColorPtr;
				/* Color for drawing traversal highlight
				 * area when highlight is off. */
    XColor *highlightColorPtr;	/* Color for drawing traversal highlight. */
    int width;			/* Width to request for window.  <= 0 means
				 * don't request any size. */
    int height;			/* Height to request for window.  <= 0 means
				 * don't request any size. */
    Tk_Cursor cursor;		/* Current cursor for window, or None. */
    char *takeFocus;		/* Value of -takefocus option;  not used in
				 * the C code, but used by keyboard traversal
				 * scripts.  Malloc'ed, but may be NULL. */
    int isContainer;		/* 1 means this window is a container, 0 means
				 * that it isn't. */
    char *useThis;		/* If the window is embedded, this points to
				 * the name of the window in which it is
				 * embedded (malloc'ed).  For non-embedded
				 * windows this is NULL. */
    int flags;			/* Various flags;  see below for
				 * definitions. */

    /* Textbox-specific fields */
    TreeView *viewPtr;
    int x, y;			/* Position of window. */

    int active;			/* Indicates that the frame is active. */
    int exportSelection;

    int insertPos;		/* Position of the cursor within the
				 * array of bytes of the entry's label. */

    int cursorX, cursorY;	/* Position of the insertion cursor in the
				 * textbox window. */
    short int cursorWidth;	/* Size of the insertion cursor symbol. */
    short int cursorHeight;

    int selAnchor;		/* Fixed end of selection. Used to extend
				 * the selection while maintaining the
				 * other end of the selection. */
    int selFirst;		/* Position of the first character in the
				 * selection. */
    int selLast;		/* Position of the last character in the
				 * selection. */

    int cursorOn;		/* Indicates if the cursor is displayed. */
    int onTime, offTime;	/* Time in milliseconds to wait before
				 * changing the cursor from off-to-on
				 * and on-to-off. Setting offTime to 0 makes
				 * the cursor steady. */
    Tcl_TimerToken timerToken;	/* Handle for a timer event called periodically
				 * to blink the cursor. */
    /* Data-specific fields. */
    TreeViewEntry *entryPtr;	/* Selected entry */
    TreeViewColumn *columnPtr;	/* Column of entry to be edited */
    TreeViewStyle *stylePtr;
    TreeViewIcon icon;
    int gap;
    char *string;
    TextLayout *textPtr;
    Blt_Font font;
    GC gc;

    Tk_3DBorder selBorder;
    int selRelief;
    int selBW;
    XColor *selFgColor;		/* Text color of a selected entry. */
    int buttonBW;
    Tk_3DBorder buttonBorder;
    int buttonRelief;
} Textbox;

#define DEF_TEXTBOX_BACKGROUND		RGB_WHITE
#define DEF_TEXTBOX_BORDERWIDTH	STD_BORDERWIDTH
#ifdef WIN32
#define DEF_TEXTBOX_BUTTON_BACKGROUND  RGB_GREY85
#else
#define DEF_TEXTBOX_BUTTON_BACKGROUND  RGB_GREY90
#endif
#define DEF_TEXTBOX_BUTTON_BORDERWIDTH	"2"
#define DEF_TEXTBOX_BUTTON_RELIEF	"raised"
#define DEF_TEXTBOX_CURSOR		(char *)NULL
#define DEF_TEXTBOX_EXPORT_SELECTION	"no"
#define DEF_TEXTBOX_NORMAL_BACKGROUND 	STD_NORMAL_BACKGROUND
#define DEF_TEXTBOX_NORMAL_FG_MONO	STD_ACTIVE_FG_MONO
#define DEF_TEXTBOX_RELIEF		"solid"
#define DEF_TEXTBOX_SELECT_BACKGROUND 	RGB_LIGHTBLUE0
#define DEF_TEXTBOX_SELECT_BG_MONO  	STD_SELECT_BG_MONO
#define DEF_TEXTBOX_SELECT_BORDERWIDTH "1"
#define DEF_TEXTBOX_SELECT_FOREGROUND 	STD_SELECT_FOREGROUND
#define DEF_TEXTBOX_SELECT_FG_MONO  	STD_SELECT_FG_MONO
#define DEF_TEXTBOX_SELECT_RELIEF	"flat"

/* Textbox Procedures */
static Blt_ConfigSpec textboxConfigSpecs[] =
{
    {BLT_CONFIG_BORDER, "-background", "background", "Background",
	DEF_TEXTBOX_BACKGROUND, Blt_Offset(Textbox, border), 0},
    {BLT_CONFIG_SYNONYM, "-bd", "borderWidth", (char *)NULL, (char *)NULL, 0,0},
    {BLT_CONFIG_SYNONYM, "-bg", "background", (char *)NULL, (char *)NULL, 0,0},
    {BLT_CONFIG_ACTIVE_CURSOR, "-cursor", "cursor", "Cursor",
	DEF_TEXTBOX_CURSOR, Blt_Offset(Textbox, cursor), 
	BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_PIXELS_NNEG, "-borderwidth", "borderWidth", "BorderWidth",
	DEF_TEXTBOX_BORDERWIDTH, Blt_Offset(Textbox, borderWidth),
	BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_BORDER, "-buttonbackground", "buttonBackground", 
	"ButtonBackground", DEF_TEXTBOX_BUTTON_BACKGROUND,
	Blt_Offset(Textbox, buttonBorder), 0},
    {BLT_CONFIG_RELIEF, "-buttonrelief", "buttonRelief", "ButtonRelief",
	DEF_TEXTBOX_BUTTON_RELIEF, Blt_Offset(Textbox, buttonRelief),
	BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_PIXELS_NNEG, "-buttonborderwidth", "buttonBorderWidth", 
	"ButtonBorderWidth", DEF_TEXTBOX_BUTTON_BORDERWIDTH, 
	Blt_Offset(Textbox, buttonBW),
	BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_BOOLEAN, "-exportselection", "exportSelection",
	"ExportSelection", DEF_TEXTBOX_EXPORT_SELECTION, 
	Blt_Offset(Textbox, exportSelection), 
	BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_RELIEF, "-relief", "relief", "Relief", DEF_TEXTBOX_RELIEF, 
	Blt_Offset(Textbox, relief), BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_BORDER, "-selectbackground", "selectBackground", "Background",
	DEF_TEXTBOX_SELECT_BG_MONO, Blt_Offset(Textbox, selBorder),
	BLT_CONFIG_MONO_ONLY},
    {BLT_CONFIG_BORDER, "-selectbackground", "selectBackground", "Background",
	DEF_TEXTBOX_SELECT_BACKGROUND, Blt_Offset(Textbox, selBorder),
	BLT_CONFIG_COLOR_ONLY},
    {BLT_CONFIG_PIXELS_NNEG, "-selectborderwidth", "selectBorderWidth", 
        "BorderWidth", DEF_TEXTBOX_SELECT_BORDERWIDTH, 
	Blt_Offset(Textbox, selBW), BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_COLOR, "-selectforeground", "selectForeground", "Foreground",

	DEF_TEXTBOX_SELECT_FG_MONO, Blt_Offset(Textbox, selFgColor),
	BLT_CONFIG_MONO_ONLY},
    {BLT_CONFIG_COLOR, "-selectforeground", "selectForeground", "Foreground",
	DEF_TEXTBOX_SELECT_FOREGROUND, Blt_Offset(Textbox, selFgColor),
	BLT_CONFIG_COLOR_ONLY},
    {BLT_CONFIG_RELIEF, "-selectrelief", "selectRelief", "Relief",
	DEF_TEXTBOX_SELECT_RELIEF, Blt_Offset(Textbox, selRelief),
	BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_END, (char *)NULL, (char *)NULL, (char *)NULL, (char *)NULL, 
	0, 0}
};

static Tk_LostSelProc TextboxLostSelectionProc;
static Tk_SelectionProc TextboxSelectionProc;
static Tk_EventProc TextboxEventProc;

typedef int (TextboxCmdProc)(Textbox *tbPtr, Tcl_Interp *interp, int objc, 
	Tcl_Obj *const *objv);


/*
 *---------------------------------------------------------------------------
 *
 * EventuallyRedraw --
 *
 *	Queues a request to redraw the widget at the next idle point.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Information gets redisplayed.  Right now we don't do selective
 *	redisplays:  the whole window will be redrawn.
 *
 *---------------------------------------------------------------------------
 */
static void
EventuallyRedraw(Textbox *tbPtr)
{
    if ((tbPtr->tkwin != NULL) && 
	((tbPtr->flags & TEXTBOX_REDRAW) == 0)) {
	tbPtr->flags |= TEXTBOX_REDRAW;
	Tcl_DoWhenIdle(DisplayTextbox, tbPtr);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * BlinkCursorProc --
 *
 *	This procedure is called as a timer handler to blink the
 *	insertion cursor off and on.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The cursor gets turned on or off, redisplay gets invoked,
 *	and this procedure reschedules itself.
 *
 *---------------------------------------------------------------------------
 */
static void
BlinkCursorProc(ClientData clientData)
{
    Textbox *tbPtr = clientData;
    int interval;

    if (!(tbPtr->flags & TEXTBOX_FOCUS) || (tbPtr->offTime == 0)) {
	return;
    }
    if (tbPtr->active) {
	tbPtr->cursorOn ^= 1;
	interval = (tbPtr->cursorOn) ? tbPtr->onTime : tbPtr->offTime;
	tbPtr->timerToken = 
	    Tcl_CreateTimerHandler(interval, BlinkCursorProc, tbPtr);
	EventuallyRedraw(tbPtr);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * TextboxEventProc --
 *
 * 	This procedure is invoked by the Tk dispatcher for various
 * 	events on treeview widgets.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	When the window gets deleted, internal structures get
 *	cleaned up.  When it gets exposed, it is redisplayed.
 *
 *---------------------------------------------------------------------------
 */
static void
TextboxEventProc(ClientData clientData, XEvent *eventPtr)
{
    Textbox *tbPtr = clientData;

    if (eventPtr->type == Expose) {
	if (eventPtr->xexpose.count == 0) {
	    EventuallyRedraw(tbPtr);
	}
    } else if (eventPtr->type == ConfigureNotify) {
	EventuallyRedraw(tbPtr);
    } else if ((eventPtr->type == FocusIn) || (eventPtr->type == FocusOut)) {
	if (eventPtr->xfocus.detail == NotifyInferior) {
	    return;
	}
	if (eventPtr->type == FocusIn) {
	    tbPtr->flags |= TEXTBOX_FOCUS;
	} else {
	    tbPtr->flags &= ~TEXTBOX_FOCUS;
	}
	Tcl_DeleteTimerHandler(tbPtr->timerToken);
	if ((tbPtr->active) && (tbPtr->flags & TEXTBOX_FOCUS)) {
	    tbPtr->cursorOn = TRUE;
	    if (tbPtr->offTime != 0) {
		tbPtr->timerToken = Tcl_CreateTimerHandler(tbPtr->onTime, 
		   BlinkCursorProc, tbPtr);
	    }
	} else {
	    tbPtr->cursorOn = FALSE;
	    tbPtr->timerToken = (Tcl_TimerToken) NULL;
	}
	EventuallyRedraw(tbPtr);
    } else if (eventPtr->type == DestroyNotify) {
	if (tbPtr->tkwin != NULL) {
	    tbPtr->tkwin = NULL;
	}
	if (tbPtr->flags & TEXTBOX_REDRAW) {
	    Tcl_CancelIdleCall(DisplayTextbox, tbPtr);
	}
	if (tbPtr->timerToken != NULL) {
	    Tcl_DeleteTimerHandler(tbPtr->timerToken);
	}
	tbPtr->viewPtr->comboWin = NULL;
	Tcl_EventuallyFree(tbPtr, DestroyTextbox);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * TextboxLostSelectionProc --
 *
 *	This procedure is called back by Tk when the selection is
 *	grabbed away from a Text widget.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The existing selection is unhighlighted, and the window is
 *	marked as not containing a selection.
 *
 *---------------------------------------------------------------------------
 */
static void
TextboxLostSelectionProc(ClientData clientData)
{
    Textbox *tbPtr = clientData;

    if ((tbPtr->selFirst >= 0) && (tbPtr->exportSelection)) {
	tbPtr->selFirst = tbPtr->selLast = -1;
	EventuallyRedraw(tbPtr);
    }
}

static int
PointerToIndex(Textbox *tbPtr, int x, int y)
{
    TextLayout *textPtr;
    Blt_FontMetrics fontMetrics;
    TextFragment *fragPtr;
    int nBytes;
    int i;
    int total;

    if ((tbPtr->string == NULL) || (tbPtr->string[0] == '\0')) {
	return 0;
    }
    x -= tbPtr->selBW;
    y -= tbPtr->selBW;

    textPtr = tbPtr->textPtr;

    /* Bound the y-coordinate within the window. */
    if (y < 0) {
	y = 0;
    } else if (y >= textPtr->height) {
	y = textPtr->height - 1;
    }
    /* 
     * Compute the line that contains the y-coordinate. 
     *
     * FIXME: This assumes that segments are distributed 
     *	     line-by-line.  This may change in the future.
     */
    Blt_GetFontMetrics(tbPtr->font, &fontMetrics);
    fragPtr = textPtr->fragments;
    total = 0;
    for (i = (y / fontMetrics.linespace); i > 0; i--) {
	total += fragPtr->count;
	fragPtr++;
    }
    if (x < 0) {
	nBytes = 0;
    } else if (x >= textPtr->width) {
	nBytes = fragPtr->count;
    } else {
	int newX;

	/* Find the character underneath the pointer. */
	nBytes = Blt_MeasureChars(tbPtr->font, fragPtr->text, fragPtr->count, 
		 x, 0, &newX);
	if ((newX < x) && (nBytes < fragPtr->count)) {
	    double fract;
	    int length, charSize;
	    const char *next;

	    next = fragPtr->text + nBytes;
#if HAVE_UTF
	    {
		Tcl_UniChar dummy;

		length = Tcl_UtfToUniChar(next, &dummy);
	    }
#else
	    length = 1;
#endif
	    charSize = Blt_TextWidth(tbPtr->font, next, length);
	    fract = ((double)(x - newX) / (double)charSize);
	    if (ROUND(fract)) {
		nBytes += length;
	    }
	}
    }
    return nBytes + total;
}

static int
IndexToPointer(Textbox *tbPtr)
{
    int x, y;
    int maxLines;
    TextLayout *textPtr;
    Blt_FontMetrics fontMetrics;
    int nBytes;
    int sum;
    TextFragment *fragPtr;
    int i;

    textPtr = tbPtr->textPtr;
    Blt_GetFontMetrics(tbPtr->font, &fontMetrics);
    maxLines = (textPtr->height / fontMetrics.linespace) - 1;

    sum = 0;
    x = y = tbPtr->borderWidth;
    if (tbPtr->icon != NULL) {
	x += TreeView_IconWidth(tbPtr->icon) + 2 * tbPtr->gap;
    }
    fragPtr = textPtr->fragments;
    for (i = 0; i <= maxLines; i++) {
	/* Total the number of bytes on each line.  Include newlines. */
	nBytes = fragPtr->count + 1;
	if ((sum + nBytes) > tbPtr->insertPos) {
	    x += Blt_TextWidth(tbPtr->font, fragPtr->text, 
		tbPtr->insertPos - sum);
	    break;
	}
	y += fontMetrics.linespace;
	sum += nBytes;
	fragPtr++;
    }
    tbPtr->cursorX = x;
    tbPtr->cursorY = y;
    tbPtr->cursorHeight = fontMetrics.linespace;
    tbPtr->cursorWidth = 3;
    return TCL_OK;
}

static void
UpdateLayout(Textbox *tbPtr)
{
    TreeView *viewPtr;
    TextStyle ts;
    int width, height;
    TextLayout *textPtr;
    int gap, offset;
    int iw, ih;

    viewPtr = tbPtr->viewPtr;
    offset = gap = iw = ih = 0;
    if (tbPtr->icon != NULL) {
	iw = TreeView_IconWidth(tbPtr->icon) + 4;
	ih = TreeView_IconHeight(tbPtr->icon);
	gap = tbPtr->gap;
    }

    /* The layout is based upon the current font. */
    Blt_Ts_InitStyle(ts);
    Blt_Ts_SetFont(ts, tbPtr->font);
    textPtr = Blt_Ts_CreateLayout(tbPtr->string, -1, &ts);
    if (tbPtr->textPtr != NULL) {
	Blt_Free(tbPtr->textPtr);
    }
    tbPtr->textPtr = textPtr;

    width = iw + textPtr->width + gap * 2;
    height = MAX(ih, textPtr->height);
    if ((tbPtr->columnPtr == &viewPtr->treeColumn) && (!viewPtr->flatView)) {
	int level;
	
	level = DEPTH(viewPtr, tbPtr->entryPtr->node);
	offset = -(ICONWIDTH(level) + 2);
    }

    if (width <= (tbPtr->columnPtr->width + offset)) {
	width = (tbPtr->columnPtr->width + offset);
    } 
    if (height < tbPtr->entryPtr->height) {
	height = tbPtr->entryPtr->height;
    }
    tbPtr->width = width + (2 * tbPtr->borderWidth);
    tbPtr->height = height + (2 * tbPtr->borderWidth);
    IndexToPointer(tbPtr);
    Tk_MoveResizeWindow(tbPtr->tkwin, tbPtr->x, tbPtr->y, 
	      tbPtr->width, tbPtr->height);
    Tk_MapWindow(tbPtr->tkwin);
    XRaiseWindow(tbPtr->display, Tk_WindowId(tbPtr->tkwin));
}

static void
InsertText(Textbox *tbPtr, char *insertText, int insertPos, int nBytes)
{
    int oldSize, newSize;
    char *oldText, *newText;

    oldText = tbPtr->string;
    oldSize = (int)strlen(oldText);
    newSize = oldSize + nBytes + 1;
    newText = Blt_AssertMalloc(sizeof(char) * newSize);
    if (insertPos == oldSize) {	/* Append */
	sprintf_s(newText, newSize, "%s%s", oldText, insertText);
    } else if (insertPos == 0) {/* Prepend */
	sprintf_s(newText, newSize, "%s%s", insertText, oldText);
    } else {			/* Insert into existing. */
	sprintf_s(newText, newSize, "%.*s%s%s", insertPos, oldText, insertText,
		oldText + insertPos);
    }

    /* 
     * All indices from the start of the insertion to the end of the
     * string need to be updated.  Simply move the indices down by the
     * number of characters added.  
     */
    if (tbPtr->selFirst >= insertPos) {
	tbPtr->selFirst += nBytes;
    }
    if (tbPtr->selLast > insertPos) {
	tbPtr->selLast += nBytes;
    }
    if ((tbPtr->selAnchor > insertPos) || (tbPtr->selFirst >= insertPos)) {
	tbPtr->selAnchor += nBytes;
    }
    if (tbPtr->string != NULL) {
	Blt_Free(tbPtr->string);
    }
    tbPtr->string = newText;
    tbPtr->insertPos = insertPos + nBytes;
    UpdateLayout(tbPtr);
}

static int
DeleteText(Textbox *tbPtr, int firstPos, int lastPos)
{
    char *oldText, *newText;
    int oldSize, newSize;
    int nBytes;
    char *p;

    oldText = tbPtr->string;
    if (firstPos > lastPos) {
	return TCL_OK;
    }
    lastPos++;			/* Now is the position after the last
				 * character. */

    nBytes = lastPos - firstPos;
    oldSize = strlen(oldText) + 1;
    newSize = oldSize - nBytes + 1;
    newText = Blt_AssertMalloc(sizeof(char) * newSize);
    p = newText;
    if (firstPos > 0) {
	strncpy(p, oldText, firstPos);
	p += firstPos;
    }
    *p = '\0';
    if (lastPos < oldSize) {
	strcpy(p, oldText + lastPos);
    }
    Blt_Free(oldText);

    /*
     * Since deleting characters compacts the character array, we need to
     * update the various character indices according.  It depends where
     * the index occurs in relation to range of deleted characters:
     *
     *	 before		Ignore.
     *   within		Move the index back to the start of the deletion.
     *	 after		Subtract off the deleted number of characters,
     *			since the array has been compressed by that
     *			many characters.
     *
     */
    if (tbPtr->selFirst >= firstPos) {
	if (tbPtr->selFirst >= lastPos) {
	    tbPtr->selFirst -= nBytes;
	} else {
	    tbPtr->selFirst = firstPos;
	}
    }
    if (tbPtr->selLast >= firstPos) {
	if (tbPtr->selLast >= lastPos) {
	    tbPtr->selLast -= nBytes;
	} else {
	    tbPtr->selLast = firstPos;
	}
    }
    if (tbPtr->selLast <= tbPtr->selFirst) {
	tbPtr->selFirst = tbPtr->selLast = -1; /* Cut away the entire
						    * selection. */ 
    }
    if (tbPtr->selAnchor >= firstPos) {
	if (tbPtr->selAnchor >= lastPos) {
	    tbPtr->selAnchor -= nBytes;
	} else {
	    tbPtr->selAnchor = firstPos;
	}
    }
    if (tbPtr->insertPos >= firstPos) {
	if (tbPtr->insertPos >= lastPos) {
	    tbPtr->insertPos -= nBytes;
	} else {
	    tbPtr->insertPos = firstPos;
	}
    }
    tbPtr->string = newText;
    UpdateLayout(tbPtr);
    EventuallyRedraw(tbPtr);
    return TCL_OK;
}

static int
AcquireText(TreeView *viewPtr, Textbox *tbPtr, TreeViewEntry *entryPtr, 
	    TreeViewColumn *columnPtr)
{
    TreeViewStyle *stylePtr;
    int x, y;
    const char *string;
    TreeViewIcon icon;

    if (columnPtr == &viewPtr->treeColumn) {
	int level;

	level = DEPTH(viewPtr, entryPtr->node);
	x = SCREENX(viewPtr, entryPtr->worldX);
	y = SCREENY(viewPtr, entryPtr->worldY);
#ifdef notdef
	x += ICONWIDTH(level) + ICONWIDTH(level + 1) + 4;
#endif
	if (!viewPtr->flatView) {
	    x += ICONWIDTH(level);
	}
	string = GETLABEL(entryPtr);
	stylePtr = columnPtr->stylePtr;
	icon = Blt_TreeView_GetEntryIcon(viewPtr, entryPtr);
    } else {
	TreeViewValue *valuePtr;

	x = SCREENX(viewPtr, columnPtr->worldX);
	y = SCREENY(viewPtr, entryPtr->worldY);
	stylePtr = columnPtr->stylePtr;
	valuePtr = Blt_TreeView_FindValue(entryPtr, columnPtr);
	string = valuePtr->fmtString;
	if (valuePtr->stylePtr != NULL) {
	    stylePtr = valuePtr->stylePtr;
	}
	icon = stylePtr->icon;
    }
    if (tbPtr->textPtr != NULL) {
	Blt_Free(tbPtr->textPtr);
	tbPtr->textPtr = NULL;
    }
    if (tbPtr->string != NULL) {
	Blt_Free(tbPtr->string);
    }
    if (string == NULL) {
	string = "";
    }
    tbPtr->icon = icon;
    tbPtr->entryPtr = entryPtr;
    tbPtr->columnPtr = columnPtr;
    tbPtr->x = x - tbPtr->borderWidth;
    tbPtr->y = y - tbPtr->borderWidth;
    
    tbPtr->gap = stylePtr->gap;
    tbPtr->string = Blt_AssertStrdup(string);
    tbPtr->gc = Blt_TreeView_GetStyleGC(stylePtr);
    tbPtr->font = Blt_TreeView_GetStyleFont(viewPtr, stylePtr);
    tbPtr->selFirst = tbPtr->selLast = -1;
    UpdateLayout(tbPtr);
    Tk_MapWindow(tbPtr->tkwin);
    EventuallyRedraw(tbPtr);
    return TCL_OK;
}


/*
 *---------------------------------------------------------------------------
 *
 * GetIndexFromObj --
 *
 *	Parse an index into an entry and return either its value
 *	or an error.
 *
 * Results:
 *	A standard TCL result.  If all went well, then *indexPtr is
 *	filled in with the character index (into entryPtr) corresponding to
 *	string.  The index value is guaranteed to lie between 0 and
 *	the number of characters in the string, inclusive.  If an
 *	error occurs then an error message is left in the interp's result.
 *
 * Side effects:
 *	None.
 *
 *---------------------------------------------------------------------------
 */
static int
GetIndexFromObj(Tcl_Interp *interp, Textbox *tbPtr, Tcl_Obj *objPtr, 
		int *indexPtr)
{
    int textPos;
    char c;
    char *string;

    string = Tcl_GetString(objPtr);
    if ((tbPtr->string == NULL) || (tbPtr->string[0] == '\0')) {
	*indexPtr = 0;
	return TCL_OK;
    }
    c = string[0];
    if ((c == 'a') && (strcmp(string, "anchor") == 0)) {
	textPos = tbPtr->selAnchor;
    } else if ((c == 'e') && (strcmp(string, "end") == 0)) {
	textPos = strlen(tbPtr->string);
    } else if ((c == 'i') && (strcmp(string, "insert") == 0)) {
	textPos = tbPtr->insertPos;
    } else if ((c == 'n') && (strcmp(string, "next") == 0)) {
	textPos = tbPtr->insertPos;
	if (textPos < (int)strlen(tbPtr->string)) {
	    textPos++;
	}
    } else if ((c == 'l') && (strcmp(string, "last") == 0)) {
	textPos = tbPtr->insertPos;
	if (textPos > 0) {
	    textPos--;
	}
    } else if ((c == 's') && (strcmp(string, "sel.first") == 0)) {
	if (tbPtr->selFirst < 0) {
	    textPos = -1;
	} else {
	    textPos = tbPtr->selFirst;
	}
    } else if ((c == 's') && (strcmp(string, "sel.last") == 0)) {
	if (tbPtr->selLast < 0) {
	    textPos = -1;
	} else {
	    textPos = tbPtr->selLast;
	}
    } else if (c == '@') {
	int x, y;

	if (Blt_GetXY(interp, tbPtr->tkwin, string, &x, &y) != TCL_OK) {
	    return TCL_ERROR;
	}
	textPos = PointerToIndex(tbPtr, x, y);
    } else if (isdigit((int)c)) {
	int number;
	int maxChars;

	if (Tcl_GetIntFromObj(interp, objPtr, &number) != TCL_OK) {
	    return TCL_ERROR;
	}
	/* Don't allow the index to point outside the label. */
	maxChars = Tcl_NumUtfChars(tbPtr->string, -1);
	if (number < 0) {
	    textPos = 0;
	} else if (number > maxChars) {
	    textPos = strlen(tbPtr->string);
	} else {
	    textPos = Tcl_UtfAtIndex(tbPtr->string, number) - tbPtr->string;
	}
    } else {
	if (interp != NULL) {
	    Tcl_AppendResult(interp, "bad label index \"", string, "\"",
			     (char *)NULL);
	}
	return TCL_ERROR;
    }
    *indexPtr = textPos;
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * SelectText --
 *
 *	Modify the selection by moving its un-anchored end.  This
 *	could make the selection either larger or smaller.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The selection changes.
 *
 *---------------------------------------------------------------------------
 */
static int
SelectText(Textbox *tbPtr, int textPos)
{
    int selFirst, selLast;

    /*
     * Grab the selection if we don't own it already.
     */
    if ((tbPtr->exportSelection) && (tbPtr->selFirst == -1)) {
	Tk_OwnSelection(tbPtr->tkwin, XA_PRIMARY, 
			TextboxLostSelectionProc, tbPtr);
    }
    /*  If the anchor hasn't been set yet, assume the beginning of the text*/
    if (tbPtr->selAnchor < 0) {
	tbPtr->selAnchor = 0;
    }
    if (tbPtr->selAnchor <= textPos) {
	selFirst = tbPtr->selAnchor;
	selLast = textPos;
    } else {
	selFirst = textPos;
	selLast = tbPtr->selAnchor;
    }
    if ((tbPtr->selFirst != selFirst) || (tbPtr->selLast != selLast)) {
	tbPtr->selFirst = selFirst;
	tbPtr->selLast = selLast;
	EventuallyRedraw(tbPtr);
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * TextboxSelectionProc --
 *
 *	This procedure is called back by Tk when the selection is
 *	requested by someone.  It returns part or all of the selection
 *	in a buffer provided by the caller.
 *
 * Results:
 *	The return value is the number of non-NULL bytes stored at
 *	buffer.  Buffer is filled (or partially filled) with a
 *	NUL-terminated string containing part or all of the
 *	selection, as given by offset and maxBytes.
 *
 * Side effects:
 *	None.
 *
 *---------------------------------------------------------------------------
 */
static int
TextboxSelectionProc(
    ClientData clientData,	/* Information about the widget. */
    int offset,			/* Offset within selection of first
				 * character to be returned. */
    char *buffer,		/* Location in which to place
				 * selection. */
    int maxBytes)		/* Maximum number of bytes to place
				 * at buffer, not including terminating
				 * NULL character. */
{
    Textbox *tbPtr = clientData;
    int size;

    size = (int)strlen(tbPtr->string + offset);
    /*
     * Return the string currently in the textbox.
     */
    strncpy(buffer, tbPtr->string + offset, maxBytes);
    buffer[maxBytes] = '\0';
    return (size > maxBytes) ? maxBytes : size;
}


static void
DestroyTextbox(DestroyData data)
{
    Textbox *tbPtr = (Textbox *)data;

    Blt_FreeOptions(textboxConfigSpecs, (char *)tbPtr, 
	tbPtr->display, 0);

    if (tbPtr->string != NULL) {
	Blt_Free(tbPtr->string);
    }
    if (tbPtr->textPtr != NULL) {
	Blt_Free(tbPtr->textPtr);
    }
    if (tbPtr->timerToken != NULL) {
	Tcl_DeleteTimerHandler(tbPtr->timerToken);
    }
    if (tbPtr->tkwin != NULL) {
	Tk_DeleteSelHandler(tbPtr->tkwin, XA_PRIMARY, XA_STRING);
    }
    Blt_Free(tbPtr);
}

static void
ConfigureTextbox(Textbox *tbPtr)
{
#ifdef notdef
    GC newGC;
    Textbox *tbPtr = viewPtr->tbPtr;
    XGCValues gcValues;
    unsigned long gcMask;

    /*
     * GC for edit window.
     */
    gcMask = 0;
    newGC = Tk_GetGC(tbPtr->tkwin, gcMask, &gcValues);
    if (tbPtr->gc != NULL) {
	Tk_FreeGC(tbPtr->display, tbPtr->gc);
    }
    tbPtr->gc = newGC;
    tbPtr->width = tbPtr->textPtr->width + 
	2 * (tbPtr->borderWidth + tbPtr->highlightWidth);
    tbPtr->height = tbPtr->textPtr->height + 
	2 * (tbPtr->borderWidth + tbPtr->highlightWidth);
    
    if (Tk_IsMapped(tbPtr->tkwin)) {
	if ((tbPtr->height != Tk_Height(tbPtr->tkwin)) ||
	    (tbPtr->width != Tk_Width(tbPtr->tkwin))) {
	    Tk_ResizeWindow(tbPtr->tkwin, tbPtr->width, tbPtr->height);
	}
    }
#endif
}

int
Blt_TreeView_CreateTextbox(TreeView *viewPtr, TreeViewEntry *entryPtr, 
			   TreeViewColumn *columnPtr)
{
    Tk_Window tkwin;
    Textbox *tbPtr;

    if (viewPtr->comboWin != NULL) {
	Tk_DestroyWindow(viewPtr->comboWin);
    }
    tkwin = Tk_CreateWindow(viewPtr->interp, viewPtr->tkwin, "edit", 
	(char *)NULL);
    if (tkwin == NULL) {
	return TCL_ERROR;
    }

    Tk_MakeWindowExist(tkwin);

    Tk_SetClass(tkwin, "TreeViewEditor"); 

    tbPtr = Blt_AssertCalloc(1, sizeof(Textbox));

    tbPtr->interp = viewPtr->interp;
    tbPtr->display = Tk_Display(tkwin);
    tbPtr->tkwin = tkwin;
    tbPtr->borderWidth = 1;
    tbPtr->relief = TK_RELIEF_SOLID;
    tbPtr->selRelief = TK_RELIEF_FLAT;
    tbPtr->selBW = 1;
    tbPtr->selAnchor = -1;
    tbPtr->selFirst = tbPtr->selLast = -1;
    tbPtr->onTime = 600;
    tbPtr->active = TRUE;
    tbPtr->offTime = 300;
    tbPtr->viewPtr = viewPtr;
    tbPtr->buttonRelief = TK_RELIEF_SUNKEN;
    tbPtr->buttonBW = 1;
    viewPtr->comboWin = tkwin;
    Blt_SetWindowInstanceData(tkwin, tbPtr);
    Tk_CreateSelHandler(tkwin, XA_PRIMARY, XA_STRING, 
	TextboxSelectionProc, tbPtr, XA_STRING);
    Tk_CreateEventHandler(tkwin, ExposureMask | StructureNotifyMask |
	FocusChangeMask, TextboxEventProc, tbPtr);
    Tcl_CreateObjCommand(viewPtr->interp, Tk_PathName(tkwin), 
	TextboxCmd, tbPtr, NULL);
    if (Blt_ConfigureWidgetFromObj(viewPtr->interp, tkwin, textboxConfigSpecs, 0, 
	(Tcl_Obj **)NULL, (char *)tbPtr, 0) != TCL_OK) {
	Tk_DestroyWindow(tkwin);
	return TCL_ERROR;
    }
    AcquireText(viewPtr, tbPtr, entryPtr, columnPtr);
    tbPtr->insertPos = strlen(tbPtr->string);
    
    Tk_MoveResizeWindow(tkwin, tbPtr->x, tbPtr->y, tbPtr->width, tbPtr->height);
    Tk_MapWindow(tkwin);
    Tk_MakeWindowExist(tkwin);
    XRaiseWindow(tbPtr->display, Tk_WindowId(tkwin));
    EventuallyRedraw(tbPtr);
    return TCL_OK;
}

static void
DisplayTextbox(ClientData clientData)
{
    Textbox *tbPtr = clientData;
    Pixmap drawable;
    int i;
    int x1, x2;
    int count, nChars;
    int selStart, selEnd, selLength;
    int x, y;
    TextFragment *fragPtr;
    Blt_FontMetrics fontMetrics;
#ifdef notdef
    int buttonX, buttonY, buttonWidth, buttonHeight;
#endif
    tbPtr->flags &= ~TEXTBOX_REDRAW;
    if (!Tk_IsMapped(tbPtr->tkwin)) {
	return;
    }
    if (tbPtr->columnPtr == NULL) {
	return;
    }
    drawable = Tk_GetPixmap(tbPtr->display, Tk_WindowId(tbPtr->tkwin), 
	Tk_Width(tbPtr->tkwin), Tk_Height(tbPtr->tkwin), 
	Tk_Depth(tbPtr->tkwin));

    Blt_Fill3DRectangle(tbPtr->tkwin, drawable, tbPtr->border, 0, 0,
	Tk_Width(tbPtr->tkwin), Tk_Height(tbPtr->tkwin), 
	tbPtr->borderWidth, tbPtr->relief);

    x = tbPtr->borderWidth + tbPtr->gap;
    y = tbPtr->borderWidth;

#ifdef notdef
    buttonX = Tk_Width(tbPtr->tkwin) - 
	(tbPtr->borderWidth + tbPtr->gap + 1);
    buttonY = tbPtr->borderWidth + 1;
#endif

    if (tbPtr->icon != NULL) {
	y += (tbPtr->height - TreeView_IconHeight(tbPtr->icon)) / 2;
	Tk_RedrawImage(TreeView_IconBits(tbPtr->icon), 0, 0, 
		       TreeView_IconWidth(tbPtr->icon), 
		       TreeView_IconHeight(tbPtr->icon), 
		       drawable, x, y);
	x += TreeView_IconWidth(tbPtr->icon) + tbPtr->gap;
    }
    
    Blt_GetFontMetrics(tbPtr->font, &fontMetrics);
    fragPtr = tbPtr->textPtr->fragments;
    count = 0;
    y = tbPtr->borderWidth;
    if (tbPtr->height > fontMetrics.linespace) {
	y += (tbPtr->height - fontMetrics.linespace) / 2;
    }
    for (i = 0; i < tbPtr->textPtr->nFrags; i++, fragPtr++) {
	int leftPos, rightPos;

	leftPos = count;
	count += fragPtr->count;
	rightPos = count;
	if ((rightPos < tbPtr->selFirst) || (leftPos > tbPtr->selLast)) {
	    /* No part of the text fragment is selected. */
	    Blt_DrawChars(Tk_Display(tbPtr->tkwin), drawable, tbPtr->gc, 
		tbPtr->font, Tk_Depth(tbPtr->tkwin), 0.0f, fragPtr->text, 
		fragPtr->count, x + fragPtr->x, y + fragPtr->y);
	    continue;
	}

	/*
	 *  A text fragment can have up to 3 regions:
	 *
	 *	1. Text before the start the selection
	 *	2. Selected text itself (drawn in a raised border)
	 *	3. Text following the selection.
	 */

	selStart = leftPos;
	selEnd = rightPos;
	/* First adjust selected region for current line. */
	if (tbPtr->selFirst > leftPos) {
	    selStart = tbPtr->selFirst;
	}
	if (tbPtr->selLast < rightPos) {
	    selEnd = tbPtr->selLast;
	}
	selLength = (selEnd - selStart);
	x1 = x;

	if (selStart > leftPos) { /* Normal text preceding the selection */
	    nChars = (selStart - leftPos);
	    Blt_MeasureChars(tbPtr->font, tbPtr->string + leftPos,
		    nChars, 10000, DEF_TEXT_FLAGS, &x1);
	    x1 += x;
	}
	if (selLength > 0) {	/* The selection itself */
	    int width;

	    Blt_MeasureChars(tbPtr->font, fragPtr->text + selStart, selLength,
		10000, DEF_TEXT_FLAGS, &x2);
	    x2 += x;
	    width = (x2 - x1) + 1;
	    Blt_Fill3DRectangle(tbPtr->tkwin, drawable, tbPtr->selBorder,
		x1, y + fragPtr->y - fontMetrics.ascent, 
	        width, fontMetrics.linespace,
		tbPtr->selBW, tbPtr->selRelief);
	}
	Blt_DrawChars(Tk_Display(tbPtr->tkwin), drawable, tbPtr->gc, 
		tbPtr->font, Tk_Depth(tbPtr->tkwin), 0.0f, fragPtr->text, 
		fragPtr->count, fragPtr->x + x, fragPtr->y + y);
    }
    if ((tbPtr->flags & TEXTBOX_FOCUS) && (tbPtr->cursorOn)) {
	int left, top, right, bottom;

	IndexToPointer(tbPtr);
	left = tbPtr->cursorX + 1;
	right = left + 1;
	top = tbPtr->cursorY;
	if (tbPtr->height > fontMetrics.linespace) {
	    top += (tbPtr->height - fontMetrics.linespace) / 2;
	}
	bottom = top + tbPtr->cursorHeight - 1;
	XDrawLine(tbPtr->display, drawable, tbPtr->gc, left, top, left,
		bottom);
	XDrawLine(tbPtr->display, drawable, tbPtr->gc, left - 1, top, right,
		top);
	XDrawLine(tbPtr->display, drawable, tbPtr->gc, left - 1, bottom, 
		right, bottom);
    }
    Blt_Draw3DRectangle(tbPtr->tkwin, drawable, tbPtr->border, 0, 0,
	Tk_Width(tbPtr->tkwin), Tk_Height(tbPtr->tkwin), 
	tbPtr->borderWidth, tbPtr->relief);
    XCopyArea(tbPtr->display, drawable, Tk_WindowId(tbPtr->tkwin),
	tbPtr->gc, 0, 0, Tk_Width(tbPtr->tkwin), 
	Tk_Height(tbPtr->tkwin), 0, 0);
    Tk_FreePixmap(tbPtr->display, drawable);
}

/*ARGSUSED*/
static int
ApplyOp(Textbox *tbPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    TreeViewEntry *entryPtr;
    TreeView *viewPtr = tbPtr->viewPtr;
    TreeViewColumn *columnPtr;
    int valid;
    TreeViewStyle *stylePtr;
    char *newValue;

    entryPtr = tbPtr->entryPtr;
    valid = TRUE;
    newValue = tbPtr->string;

    columnPtr = tbPtr->columnPtr;
    stylePtr = NULL;
    if (columnPtr != &viewPtr->treeColumn) {
	TreeViewValue *valuePtr;

	valuePtr = Blt_TreeView_FindValue(tbPtr->entryPtr, columnPtr);
	if (valuePtr != NULL) {
	    stylePtr = valuePtr->stylePtr;
	}
    }
    if (stylePtr == NULL) {
	stylePtr = columnPtr->stylePtr;
    }
    if (stylePtr->validateCmd != NULL) {
	Tcl_DString dString;
	int result;

	Blt_TreeView_PercentSubst(viewPtr, entryPtr, stylePtr->validateCmd, &dString);
	Tcl_DStringAppend(&dString, " ", -1);
	Tcl_DStringAppend(&dString, tbPtr->string, -1);
	result = Tcl_GlobalEval(interp, Tcl_DStringValue(&dString));
	Tcl_DStringFree(&dString);
	if (result == TCL_OK) {
	    newValue = Tcl_GetString(Tcl_GetObjResult(interp));
	} else {
	    valid = FALSE;
	}
    }
    if (valid) {
	if (columnPtr == &viewPtr->treeColumn) {
	    if (entryPtr->labelUid != NULL) {
		Blt_TreeView_FreeUid(viewPtr, entryPtr->labelUid);
	    }
	    if (newValue == NULL) {
		entryPtr->labelUid = Blt_TreeView_GetUid(viewPtr, "");
	    } else {
		entryPtr->labelUid = Blt_TreeView_GetUid(viewPtr, newValue);
	    }
	} else {
	    Tcl_Obj *objPtr;
	    
	    objPtr = Tcl_NewStringObj(newValue, -1);
	    if (Blt_Tree_SetValueByKey(interp, viewPtr->tree, entryPtr->node, 
		columnPtr->key, objPtr) != TCL_OK) {
		Tcl_DecrRefCount(objPtr);
		return TCL_ERROR;
	    }
	    entryPtr->flags |= ENTRY_DIRTY;
	}	
    }
    if (viewPtr != NULL) {
	Blt_TreeView_ConfigureEntry(viewPtr, entryPtr, 0, NULL, BLT_CONFIG_OBJV_ONLY);
	viewPtr->flags |= (LAYOUT_PENDING | DIRTY);
	Blt_TreeView_EventuallyRedraw(viewPtr);
    }
    Tk_DestroyWindow(tbPtr->tkwin);
    return TCL_OK;
}

/*ARGSUSED*/
static int
CancelOp(Textbox *tbPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tk_DestroyWindow(tbPtr->tkwin);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * CgetOp --
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
CgetOp(Textbox *tbPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    return Blt_ConfigureValueFromObj(interp, tbPtr->tkwin, 
	textboxConfigSpecs, (char *)tbPtr, objv[2], 0);
}

/*
 *---------------------------------------------------------------------------
 *
 * ConfigureOp --
 *
 * 	This procedure is called to process a list of configuration
 *	options database, in order to reconfigure the one of more
 *	entries in the widget.
 *
 *	  .c configure option value
 *
 * Results:
 *	A standard TCL result.  If TCL_ERROR is returned, then
 *	interp->result contains an error message.
 *
 * Side effects:
 *	Configuration information, such as text string, colors, font,
 *	etc. get set for viewPtr; old resources get freed, if there
 *	were any.  The hypertext is redisplayed.
 *
 *---------------------------------------------------------------------------
 */
static int
ConfigureOp(Textbox *tbPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    if (objc == 2) {
	return Blt_ConfigureInfoFromObj(interp, tbPtr->tkwin, 
		textboxConfigSpecs, (char *)tbPtr, (Tcl_Obj *)NULL, 0);
    } else if (objc == 3) {
	return Blt_ConfigureInfoFromObj(interp, tbPtr->tkwin, 
		textboxConfigSpecs, (char *)tbPtr, objv[3], 0);
    }
    if (Blt_ConfigureWidgetFromObj(interp, tbPtr->tkwin, 
	textboxConfigSpecs, objc - 2, objv + 2, (char *)tbPtr, 
	BLT_CONFIG_OBJV_ONLY) != TCL_OK) {
	return TCL_ERROR;
    }
    ConfigureTextbox(tbPtr);
    EventuallyRedraw(tbPtr);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * DeleteOp --
 *
 *	Remove one or more characters from the label of an entry.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Memory gets freed, the entry gets modified and (eventually)
 *	redisplayed.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
DeleteOp(Textbox *tbPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    int firstPos, lastPos;

    if (tbPtr->entryPtr == NULL) {
	return TCL_OK;
    }
    if (GetIndexFromObj(interp, tbPtr, objv[2], &firstPos) != TCL_OK) {
	return TCL_ERROR;
    }
    lastPos = firstPos;
    if ((objc == 4) && 
	(GetIndexFromObj(interp, tbPtr, objv[3], &lastPos) != TCL_OK)) {
	return TCL_ERROR;
    }
    if (firstPos > lastPos) {
	return TCL_OK;
    }
    return DeleteText(tbPtr, firstPos, lastPos);
}


/*
 *---------------------------------------------------------------------------
 *
 * IcursorOp --
 *
 *	Returns the numeric index of the given string. Indices can be
 *	one of the following:
 *
 *	"anchor"	Selection anchor.
 *	"end"		End of the label.
 *	"insert"	Insertion cursor.
 *	"sel.first"	First character selected.
 *	"sel.last"	Last character selected.
 *	@x,y		Index at X-Y screen coordinate.
 *	number		Returns the same number.
 *
 * Results:
 *	A standard TCL result.  If the argument does not represent a
 *	valid label index, then TCL_ERROR is returned and the interpreter
 *	result will contain an error message.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
IcursorOp(Textbox *tbPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    int textPos;

    if (GetIndexFromObj(interp, tbPtr, objv[2], &textPos) != TCL_OK) {
	return TCL_ERROR;
    }
    if (tbPtr->columnPtr != NULL) {
	tbPtr->insertPos = textPos;
	IndexToPointer(tbPtr);
	EventuallyRedraw(tbPtr);
    }
    return TCL_OK;
}


/*
 *---------------------------------------------------------------------------
 *
 * IndexOp --
 *
 *	Returns the numeric index of the given string. Indices can be
 *	one of the following:
 *
 *	"anchor"	Selection anchor.
 *	"end"		End of the label.
 *	"insert"	Insertion cursor.
 *	"sel.first"	First character selected.
 *	"sel.last"	Last character selected.
 *	@x,y		Index at X-Y screen coordinate.
 *	number		Returns the same number.
 *
 * Results:
 *	A standard TCL result.  If the argument does not represent a
 *	valid label index, then TCL_ERROR is returned and the interpreter
 *	result will contain an error message.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
IndexOp(Textbox *tbPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    int textPos;

    if (GetIndexFromObj(interp, tbPtr, objv[2], &textPos) != TCL_OK) {
	return TCL_ERROR;
    }
    if ((tbPtr->columnPtr != NULL) && (tbPtr->string != NULL)) {
	int nChars;

	nChars = Tcl_NumUtfChars(tbPtr->string, textPos);
	Tcl_SetIntObj(Tcl_GetObjResult(interp), nChars);
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * InsertOp --
 *
 *	Add new characters to the label of an entry.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	New information gets added to tbPtr;  it will be redisplayed
 *	soon, but not necessarily immediately.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
InsertOp(Textbox *tbPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    int extra;
    int insertPos;
    char *string;

    if (tbPtr->entryPtr == NULL) {
	return TCL_ERROR;
    }
    if (GetIndexFromObj(interp, tbPtr, objv[2], &insertPos) != TCL_OK) {
	return TCL_ERROR;
    }
    string = Tcl_GetStringFromObj(objv[3], &extra);
    if (extra == 0) {	/* Nothing to insert. Move the cursor anyways. */
	tbPtr->insertPos = insertPos;
    } else {
	InsertText(tbPtr, string, insertPos, extra);
    }
    return TCL_OK;
}

/*ARGSUSED*/
static int
SelectionAdjustOp(Textbox *tbPtr, Tcl_Interp *interp, int objc, 
		  Tcl_Obj *const *objv)
{
    int textPos;
    int half1, half2;

    if (GetIndexFromObj(interp, tbPtr, objv[3], &textPos) != TCL_OK) {
	return TCL_ERROR;
    }
    half1 = (tbPtr->selFirst + tbPtr->selLast) / 2;
    half2 = (tbPtr->selFirst + tbPtr->selLast + 1) / 2;
    if (textPos < half1) {
	tbPtr->selAnchor = tbPtr->selLast;
    } else if (textPos > half2) {
	tbPtr->selAnchor = tbPtr->selFirst;
    }
    return SelectText(tbPtr, textPos);
}

/*ARGSUSED*/
static int
SelectionClearOp(Textbox *tbPtr, Tcl_Interp *interp, int objc, 
		 Tcl_Obj *const *objv)
{
    if (tbPtr->selFirst != -1) {
	tbPtr->selFirst = tbPtr->selLast = -1;
	EventuallyRedraw(tbPtr);
    }
    return TCL_OK;
}

/*ARGSUSED*/
static int
SelectionFromOp(Textbox *tbPtr, Tcl_Interp *interp, int objc, 
		Tcl_Obj *const *objv)
{
    int textPos;

    if (GetIndexFromObj(interp, tbPtr, objv[3], &textPos) != TCL_OK) {
	return TCL_ERROR;
    }
    tbPtr->selAnchor = textPos;
    return TCL_OK;
}

/*ARGSUSED*/
static int
SelectionPresentOp(Textbox *tbPtr, Tcl_Interp *interp, int objc, 
		   Tcl_Obj *const *objv)
{
    Tcl_SetBooleanObj(Tcl_GetObjResult(interp), (tbPtr->selFirst != -1));
    return TCL_OK;
}

/*ARGSUSED*/
static int
SelectionRangeOp(Textbox *tbPtr, Tcl_Interp *interp, int objc,
		 Tcl_Obj *const *objv)
{
    int selFirst, selLast;

    if (GetIndexFromObj(interp, tbPtr, objv[3], &selFirst) != TCL_OK) {
	return TCL_ERROR;
    }
    if (GetIndexFromObj(interp, tbPtr, objv[4], &selLast) != TCL_OK) {
	return TCL_ERROR;
    }
    tbPtr->selAnchor = selFirst;
    return SelectText(tbPtr, selLast);
}

/*ARGSUSED*/
static int
SelectionToOp(Textbox *tbPtr, Tcl_Interp *interp, int objc, 
	      Tcl_Obj *const *objv)
{
    int textPos;

    if (GetIndexFromObj(interp, tbPtr, objv[3], &textPos) != TCL_OK) {
	return TCL_ERROR;
    }
    return SelectText(tbPtr, textPos);
}


static Blt_OpSpec selectionOps[] =
{
    {"adjust", 1, SelectionAdjustOp, 4, 4, "index",},
    {"clear", 1, SelectionClearOp, 3, 3, "",},
    {"from", 1, SelectionFromOp, 4, 4, "index"},
    {"present", 1, SelectionPresentOp, 3, 3, ""},
    {"range", 1, SelectionRangeOp, 5, 5, "start end",},
    {"to", 1, SelectionToOp, 4, 4, "index"},
};

static int nSelectionOps = sizeof(selectionOps) / sizeof(Blt_OpSpec);

/*
 *	This procedure handles the individual options for text
 *	selections.  The selected text is designated by start and end
 *	indices into the text pool.  The selected segment has both a
 *	anchored and unanchored ends.  The following selection
 *	operations are implemented:
 *
 *	  "adjust"	- resets either the first or last index
 *			  of the selection.
 *	  "clear"	- clears the selection. Sets first/last
 *			  indices to -1.
 *	  "from"	- sets the index of the selection anchor.
 *	  "present"	- return "1" if a selection is available,
 *			  "0" otherwise.
 *	  "range"	- sets the first and last indices.
 *	  "to"		- sets the index of the un-anchored end.
 */
static int
SelectionOp(Textbox *tbPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    TextboxCmdProc *proc;
    int result;

    proc = Blt_GetOpFromObj(interp, nSelectionOps, selectionOps, BLT_OP_ARG2, 
	objc, objv, 0);
    if (proc == NULL) {
	return TCL_ERROR;
    }
    result = (*proc) (tbPtr, interp, objc, objv);
    return result;
}

/*
 *---------------------------------------------------------------------------
 *
 * TextboxCmd --
 *
 *	This procedure handles entry operations.
 *
 * Results:
 *	A standard TCL result.
 *
 *---------------------------------------------------------------------------
 */
static Blt_OpSpec comboOps[] =
{
    {"apply", 1, ApplyOp, 2, 2, "",},
    {"cancel", 2, CancelOp, 2, 2, "",},
    {"cget", 2, CgetOp, 3, 3, "value",},
    {"configure", 2, ConfigureOp, 2, 0, "?option value...?",},
    {"delete", 1, DeleteOp, 3, 4, "first ?last?"},
    {"icursor", 2, IcursorOp, 3, 3, "index"},
    {"index", 3, IndexOp, 3, 3, "index"},
    {"insert", 3, InsertOp, 4, 4, "index string"},
    {"selection", 1, SelectionOp, 2, 0, "args"},
};
static int nComboOps = sizeof(comboOps) / sizeof(Blt_OpSpec);

static int
TextboxCmd(ClientData clientData, Tcl_Interp *interp, int objc, 
	   Tcl_Obj *const *objv)
{
    Textbox *tbPtr = clientData;
    TextboxCmdProc *proc;
    int result;

    proc = Blt_GetOpFromObj(interp, nComboOps, comboOps, BLT_OP_ARG1, objc, 
	objv, 0);
    if (proc == NULL) {
	return TCL_ERROR;
    }
    result = (*proc) (tbPtr, interp, objc, objv);
    return result;
}

#endif

