
/*
 * bltTabset.c --
 *
 * This module implements a tabnotebook widget for the BLT toolkit.
 *
 *	Copyright 1998-2004 George A Howlett.
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

#include "bltInt.h"

#ifndef NO_TABSET
#include "bltOp.h"
#include "bltBind.h"
#include "bltChain.h"
#include "bltFont.h"
#include "bltBgStyle.h"
#include "bltImage.h"
#include "bltPicture.h"
#include "bltPainter.h"
#include "bltText.h"
#include "bltHash.h"

#define DEBUG0			0
#define DEBUG1			0
#define DEBUG2			1

#define INVALID_FAIL		0
#define INVALID_OK		1

#define TABWIDTH_NONE		-2
#define TABWIDTH_SAME		-1
#define TABWIDTH_VARIABLE	0

#define PHOTO_ICON		1

#define FCLAMP(x)		((((x) < 0.0) ? 0.0 : ((x) > 1.0) ? 1.0 : (x)))
#define SWAP(a,b)		{ int tmp; tmp = (a), (a) = (b), (b) = tmp; }

#define GAP			1
#define SELECT_PADX		4
#define SELECT_PADY		2
#define OUTER_PAD		0
#define LABEL_PAD		4
#define CORNER_OFFSET		3
#define CLOSE_WIDTH		16
#define CLOSE_HEIGHT		16
 
#define TAB_SCROLL_OFFSET	10

#define END			(-1)
#define ODD(x)			((x) | 0x01)

#define SIDE_LEFT		(1<<0)
#define SIDE_TOP		(1<<1)
#define SIDE_RIGHT		(1<<2)
#define SIDE_BOTTOM		(1<<3)

#define VPORTWIDTH(b)		 \
    ((((b)->side) & (SIDE_TOP|SIDE_BOTTOM)) ? \
	(Tk_Width((b)->tkwin) - 2 * (b)->inset) : \
	(Tk_Height((b)->tkwin) - 2 * (b)->inset))

#define VPORTHEIGHT(b)		 \
    ((((b)->side) & (SIDE_LEFT|SIDE_RIGHT)) ? \
	(Tk_Width((b)->tkwin) - 2 * (b)->inset) :	\
	(Tk_Height((b)->tkwin) - 2 * (b)->inset))

#define GETATTR(t,attr)		\
   (((t)->attr != NULL) ? (t)->attr : (t)->setPtr->defStyle.attr)

/*
 *---------------------------------------------------------------------------
 *
 *  Internal widget flags:
 *
 *	LAYOUT_PENDING  The layout of the widget needs to be recomputed.
 *
 *	REDRAW_PENDING	A redraw request is pending for the widget.
 *
 *	SCROLL_PENDING	A scroll request is pending.
 *
 *	FOCUS		The widget is receiving keyboard events.
 *			Draw the focus highlight border around the widget.
 *
 *	MULTIPLE_TIER	Tabset is using multiple tiers.
 *
 *	SCROLLING	Tabset has enough tabs to be scrolled.
 *
 *	SCROLL_TABS	Scroll tabs if there are enough tabs to be scrolled.
 *
 *	SHOW_SINGLE_TAB	Display window in a tab even if only one tab.
 *
 *	CLOSE_NEEDED	Include a "x" button on each tab that automatically
 *			closes the tab.
 *
 *---------------------------------------------------------------------------
 */
#define LAYOUT_PENDING	   (1<<0)	/* Indicates the tabset has been
					 * changed so that it geometry needs
					 * to be recalculated before its
					 * redrawn. */
#define REDRAW_PENDING	   (1<<1)	/* Indicates the tabset needs to be
					 * redrawn at the next idle point. */
#define SCROLL_PENDING	   (1<<2)	/* Indicates a scroll request that  */
#define FOCUS		   (1<<3)	/* Indicates the tabset/tab has
					 * focus. */
#define TEAROFF		   (1<<4)	/* Indicates if the perforation should
					 * be drawn (see -tearoff). */
#define SCROLLING	   (1<<5)
#define MULTIPLE_TIER	   (1<<6)	/* Indicates the tabset is using
					 * multiple tiers of tabs. */
#define ACTIVE_PERFORATION (1<<7)	/* Indicates if the perforation should
					 * should be drawn with active
					 * colors. */
#define REDRAW_ALL	   (1<<9)	/* Draw the entire tabset including
					 * the folder.  If not set, indicates
					 * that only the tabs need to be drawn
					 * (activate, deactivate, scroll,
					 * etc).  This avoids drawing the
					 * folder again. */
#define SLANT_NONE          0
#define SLANT_LEFT	   (1<<10)
#define SLANT_RIGHT        (1<<11)
#define SLANT_BOTH         (SLANT_LEFT | SLANT_RIGHT)

#define CLOSE_NEEDED       (1<<13)	/* Draw a close button on each tab. */
#define SHOW_SINGLE_TAB	   (1<<14)	/* Display window in a tab even if
					 * there is only one tab displayed. */
#define SCROLL_TABS	   (1<<15) 	/* Allow tabs to be scrolled if
					 * needed. Otherwise tab sizes will
					 * shrink to fit the space. */

#define TAB_LABEL	   (ClientData)0
#define TAB_PERFORATION    (ClientData)1
#define TAB_BUTTON         (ClientData)2

#ifdef notdef
#define DEF_ACTIVEBACKGROUND		RBG_GREY85
#define DEF_ACTIVEFOREGROUND		STD_ACTIVE_FOREGROUND
#else
#define DEF_ACTIVEBACKGROUND		RGB_SKYBLUE4
#define DEF_ACTIVEFOREGROUND		RGB_WHITE
#endif

#define DEF_BACKGROUND			RGB_GREY77
#define DEF_BORDERWIDTH			"0"
#define DEF_COMMAND			(char *)NULL
#define DEF_CURSOR			(char *)NULL
#define DEF_DASHES			"1"
#define DEF_FONT			STD_FONT_SMALL
#define DEF_FOREGROUND			STD_NORMAL_FOREGROUND
#define DEF_FOREGROUND			STD_NORMAL_FOREGROUND
#define DEF_GAP				"1"
#define DEF_HEIGHT			"0"
#define DEF_HIGHLIGHTBACKGROUND		STD_NORMAL_BACKGROUND
#define DEF_HIGHLIGHTCOLOR		RGB_BLACK
#define DEF_HIGHLIGHTTHICKNESS		"0"
#define DEF_JUSTIFY			"center"
#define DEF_OUTERPAD			"0"
#define DEF_PAGEHEIGHT			"0"
#define DEF_PAGEWIDTH			"0"
#define DEF_RELIEF			"flat"
#define DEF_ROTATE			"0.0"
#define DEF_SCROLLINCREMENT		"0"
#define DEF_SCROLLTABS			"0"
#define DEF_SELECTBACKGROUND		STD_NORMAL_BACKGROUND
#define DEF_SELECTBORDERWIDTH		"1"
#define DEF_SELECTCOMMAND		(char *)NULL
#define DEF_CLOSECOMMAND		(char *)NULL
#define DEF_SELECTFOREGROUND		RGB_BLACK
#define DEF_SELECTMODE			"multiple"
#define DEF_SELECTPADX			"4"
#define DEF_SELECTPADY			"2"
#define DEF_SELECTRELIEF		"raised"
#define DEF_SHADOWCOLOR			RGB_BLACK
#define DEF_CLOSEBUTTON			"0"
#define DEF_SHOWSINGLETAB		"1"
#define DEF_SIDE			"top"
#define DEF_SLANT			"none"
#define DEF_TABRELIEF			"raised"
#define DEF_TABWIDTH			"same"
#define DEF_TAKEFOCUS			"1"
#define DEF_TEAROFF			"no"
#define DEF_ICONPOSITION		"left"
#define DEF_TIERS			"1"
#define DEF_TROUGHCOLOR			"grey60"
#define DEF_WIDTH			"0"

#define DEF_CLOSEBUTTON_ACTIVEBACKGROUND	RGB_RED
#define DEF_CLOSEBUTTON_ACTIVEFOREGROUND	RGB_WHITE
#define DEF_CLOSEBUTTON_ACTIVERELIEF		"raised"
#define DEF_CLOSEBUTTON_BACKGROUND		RGB_GREY70
#define DEF_CLOSEBUTTON_BORDERWIDTH		"0"
#define DEF_CLOSEBUTTON_COMMAND		(char *)NULL
#define DEF_CLOSEBUTTON_FOREGROUND		RGB_GREY95
#define DEF_CLOSEBUTTON_RELIEF		"flat"

#define DEF_TAB_ACTIVEBACKGROUND	(char *)NULL
#define DEF_TAB_ACTIVEFOREGROUND	(char *)NULL
#define DEF_TAB_ANCHOR			"center"
#define DEF_TAB_BACKGROUND		(char *)NULL
#define DEF_TAB_BORDERWIDTH		"1"
#define DEF_TAB_BUTTON			(char *)NULL
#define DEF_TAB_CLOSEBUTTON		"1"
#define DEF_TAB_COMMAND			(char *)NULL
#define DEF_TAB_DATA			(char *)NULL
#define DEF_TAB_FILL			"none"
#define DEF_TAB_FONT			(char *)NULL
#define DEF_TAB_FOREGROUND		(char *)NULL
#define DEF_TAB_HEIGHT			"0"
#define DEF_TAB_HIDE			"no"
#define DEF_TAB_IMAGE			(char *)NULL
#define DEF_TAB_IPAD			"0"
#define DEF_TAB_PAD			"3"
#define DEF_TAB_PERFORATIONCOMMAND	(char *)NULL
#define DEF_TAB_SELECTBACKGROUND	(char *)NULL
#define DEF_TAB_SELECTBORDERWIDTH 	"1"
#define DEF_TAB_SELECTCOMMAND		(char *)NULL
#define DEF_TAB_SELECTFOREGROUND	(char *)NULL
#define DEF_TAB_STATE			"normal"
#define DEF_TAB_STIPPLE			"BLT"
#define DEF_TAB_TEXT			(char *)NULL
#define DEF_TAB_VISUAL			(char *)NULL
#define DEF_TAB_WIDTH			"0"
#define DEF_TAB_WINDOW			(char *)NULL
#define DEF_TAB_WINDOWHEIGHT		"0"
#define DEF_TAB_WINDOWWIDTH		"0"

typedef struct _Tabset Tabset;

static Tk_GeomRequestProc EmbeddedWidgetGeometryProc;
static Tk_GeomLostSlaveProc EmbeddedWidgetCustodyProc;
static Tk_GeomMgr tabMgrInfo = {
    (char *)"tabset",		     /* Name of geometry manager used by
				      * winfo */
    EmbeddedWidgetGeometryProc,	     /* Procedure to for new geometry
				      * requests */
    EmbeddedWidgetCustodyProc,	     /* Procedure when window is taken away */
};

static Blt_OptionParseProc ObjToIconProc;
static Blt_OptionPrintProc IconToObjProc;
static Blt_OptionFreeProc  FreeIconProc;
static Blt_OptionParseProc ObjToChildProc;
static Blt_OptionPrintProc ChildToObjProc;
static Blt_OptionParseProc ObjToSlantProc;
static Blt_OptionPrintProc SlantToObjProc;
static Blt_OptionParseProc ObjToTabWidthProc;
static Blt_OptionPrintProc TabWidthToObjProc;
static Blt_OptionParseProc ObjToStateProc;
static Blt_OptionPrintProc StateToObjProc;

/*
 * Contains a pointer to the widget that's currently being configured.  This
 * is used in the custom configuration parse routine for icons.
 */

static Blt_CustomOption iconOption = {
    ObjToIconProc, IconToObjProc, FreeIconProc, (ClientData)0,
};

static Blt_CustomOption childOption = {
    ObjToChildProc, ChildToObjProc, NULL, (ClientData)0,
};

static Blt_CustomOption slantOption = {
    ObjToSlantProc, SlantToObjProc, NULL, (ClientData)0,
};

static Blt_CustomOption tabWidthOption = {
    ObjToTabWidthProc, TabWidthToObjProc, NULL, (ClientData)0,
};

static Blt_CustomOption stateOption = {
    ObjToStateProc, StateToObjProc, NULL, (ClientData)0
};

typedef struct {
    short int x, y;			/* Location of region. */
    short int w, h;			/* Dimensions of region. */
} GadgetRegion;

/*
 * Icon --
 *
 *	When multiple instances of an image are displayed in the same widget,
 *	this can be inefficient in terms of both memory and time.  We only
 *	need one instance of each image, regardless of number of times we use
 *	it.  And searching/deleting instances can be very slow as the list
 *	gets large.
 *
 *	The workaround, employed below, is to maintain a hash table of images
 *	that maintains a reference count for each image.
 */

typedef struct _Icon {
    Blt_HashEntry *hashPtr;		/* Hash table pointer to the image. */
    Tk_Image tkImage;			/* The Tk image being cached. */
    Blt_Picture picture;
    float angle;
    short int width, height;		/* Dimensions of the cached image. */
    int refCount;		        /* Reference counter for this image. */
} *Icon;

#define IconHeight(i)	(((i) == NULL) ? 0 : (i)->height)
#define IconWidth(i)	(((i) == NULL) ? 0 : (i)->width)
#define IconBits(i)	((i)->tkImage)

/*
 * Button --
 */
typedef struct {
    int borderWidth;			/* Width of 3D border around this
					 * button. */
    int pad;				/* Amount of extra padding around
					 * the button. */
    int relief;				/* 3D relief of button. */
    int activeRelief;			/* 3D relief when the button is
					 * active. */
    XColor *normalFg;			/* Foreground color of the button when
					 * the button is inactive. */
    XColor *normalBg;			/* Background color of the button when
					 * the button is inactive. */
    XColor *activeFg;			/* Foreground color of the button
					 * when the button is active. */
    XColor *activeBg;			/* Background color of the button
					 * when the button is active. */
    Tcl_Obj *cmdObjPtr;			/* Command to be executed when the the
					 * button is invoked. */
    Blt_Picture normal0;		/* Contains the image to be displayed
					 * when the button is inactive at 0
					 * degrees rotation. */
    Blt_Picture active0;		/* Contains the image to be displayed
					 * when the button is active at 0
					 * degreees rotation. */

    Blt_Picture normal;			/* Contains the image to be displayed
					 * when the button is inactive at 0
					 * degrees rotation. */
    Blt_Picture active;			/* Contains the image to be displayed
					 * when the button is active at 0
					 * degreees rotation. */
    short int width, height;		/* The dimensions of the button. */
} Button;

static Blt_ConfigSpec buttonSpecs[] =
{
    {BLT_CONFIG_COLOR, "-activebackground", "activeBackrgound", 
	"ActiveBackground", DEF_CLOSEBUTTON_ACTIVEBACKGROUND, 
	Blt_Offset(Button, activeBg), 0},
    {BLT_CONFIG_COLOR, "-activeforeground", "activeForergound", 
	"ActiveForeground", DEF_CLOSEBUTTON_ACTIVEFOREGROUND, 
	Blt_Offset(Button, activeFg), 0},
    {BLT_CONFIG_COLOR, "-background", "backrgound", "Background", 
	DEF_CLOSEBUTTON_BACKGROUND, Blt_Offset(Button, normalBg), 0},
    {BLT_CONFIG_COLOR, "-foreground", "forergound", "Foreground", 
	DEF_CLOSEBUTTON_FOREGROUND, Blt_Offset(Button, normalFg), 0},
    {BLT_CONFIG_RELIEF, "-activerelief", "activeRelief", "ActiveRelief",
	DEF_CLOSEBUTTON_ACTIVERELIEF, Blt_Offset(Button, activeRelief), 0},
    {BLT_CONFIG_SYNONYM, "-bd", "borderWidth", (char *)NULL, (char *)NULL, 0,0},
    {BLT_CONFIG_PIXELS_NNEG, "-borderwidth", "borderWidth", "BorderWidth",
	DEF_CLOSEBUTTON_BORDERWIDTH, Blt_Offset(Button, borderWidth),
	BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_RELIEF, "-relief", "relief", "Relief", DEF_CLOSEBUTTON_RELIEF, 
	Blt_Offset(Button, relief), 0},
    {BLT_CONFIG_END, (char *)NULL, (char *)NULL, (char *)NULL,
	(char *)NULL, 0, 0}
};

#define NORMAL		(0)
#define ACTIVE		(1<<0)
#define DISABLED	(1<<1)
#define HIDE		(1<<2)
#define STATE_MASK	(ACTIVE|DISABLED|HIDE)
#define ONSCREEN	(1<<3)
#define TEAROFF_REDRAW	(1<<4)

typedef struct {
    const char *name;			/* Identifier for tab. */
    Blt_HashEntry *hashPtr;
    int index;				/* Index of the tab. */
    unsigned int flags;
    int tier;				/* Index of tier [1..numTiers]
					 * containing this tab. */

    int worldX, worldY;			/* Position of tab in world
					 * coordinates. */
    int worldWidth, worldHeight;	/* Dimensions of the tab at 0 degree
					 * rotation.  It includes the *
					 * border, padding, label, etc. */
    int screenX, screenY;		/* Location of tab on screen. */
    int screenWidth;
    int screenHeight;			/*  */

    Tabset *setPtr;			/* Tabset that includes this
					 * tab. Needed for callbacks can pass
					 * only a tab pointer.  */
    /*
     * Tab label:
     */
    const char *text;			/* String displayed as the tab's
					 * label. */
    TextLayout *layoutPtr;

    Icon icon;				/* Icon displayed as the label. */

    /* Dimensions of the tab label, corrected for side. */
    short int rotWidth, rotHeight; 

    short int textWidth0, textHeight0;
    short int labelWidth0, labelHeight0;
    Blt_Pad iPadX, iPadY;		/* Internal padding around the text */

    Blt_Font font;

    /*
     * Normal:
     */
    XColor *textColor;			/* Text color */
    Blt_Background bg;		        /* Background color and border for
					 * tab. */
    /*
     * Selected: Tab is currently selected.
     */
    XColor *selColor;			/* Selected text color */
    Blt_Background selBg;		/* 3D border of selected folder. */

    /*
     * Active: Mouse passes over the tab.
     */
    Blt_Background activeBg;		/* Active background color. */
    XColor *activeFg;			/* Active text color */
    Pixmap stipple;			/* Stipple for outline of embedded
					 * window when torn off. */
    /*
     * Embedded widget information:
     */
    Tk_Window tkwin;			/* Widget to be mapped when the tab is
					 * selected.  If NULL, don't make
					 * space for the page. */
    int reqSlaveWidth, reqSlaveHeight;	/* If non-zero, overrides the
					 * requested dimensions of the
					 * embedded widget. */
    Tk_Window container;		/* The window containing the embedded
					 * widget.  Does not necessarily have
					 * to be the parent. */
    Tk_Anchor anchor;			/* Anchor: indicates how the embedded
					 * widget is positioned within the
					 * extra space on the page. */
    Blt_Pad xPad, yPad;			/* Padding around embedded widget. */
    int fill;				/* Indicates how the window should
					 * fill the page. */

    /*
     * Auxillary information:
     */
    Tcl_Obj *cmdObjPtr;			/* Command invoked when the tab is
					 * selected */
    const char *data;			/* This value isn't used in C code.
					 * It may be used by clients in Tcl
					 * bindings * to associate extra data
					 * (other than the * label or name)
					 * with the tab. */

    Tcl_Obj *closeObjPtr;		/* Command to be executed when the tab
					 * is closed. */
    Blt_ChainLink link;			/* Pointer to where the tab resides in
					 * the list of tabs. */
    Tcl_Obj *perfCmdObjPtr;		/* Command invoked when the tab is
					 * selected */
    GC textGC;
    GC backGC;

    /* Gadget positions and locations: */
    GadgetRegion buttonRegion;
    GadgetRegion textRegion;
    GadgetRegion iconRegion;
    GadgetRegion focusRegion;
} Tab;

static Blt_ConfigSpec tabSpecs[] =
{
    {BLT_CONFIG_BACKGROUND, "-activebackground", "activeBackground",
	"ActiveBackground", DEF_TAB_ACTIVEBACKGROUND,
	Blt_Offset(Tab, activeBg), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_COLOR, "-activeforeground", "activeForeground", 
	"ActiveForeground", DEF_TAB_ACTIVEFOREGROUND, 
	Blt_Offset(Tab, activeFg), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_ANCHOR, "-anchor", "anchor", "Anchor", DEF_TAB_ANCHOR, 
	Blt_Offset(Tab, anchor), BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_BACKGROUND, "-background", "background", "Background",
	(char *)NULL, Blt_Offset(Tab, bg), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_SYNONYM, "-bg", "background", (char *)NULL, (char *)NULL, 0, 0},
    {BLT_CONFIG_BITMASK, "-closebutton", "closeButton", "CloseButton", 
	DEF_TAB_CLOSEBUTTON, Blt_Offset(Tab, flags), 
	BLT_CONFIG_DONT_SET_DEFAULT, (Blt_CustomOption *)CLOSE_NEEDED},
    {BLT_CONFIG_OBJ, "-closecommand", "closeCommand", "CloseCommand",
	DEF_CLOSECOMMAND, Blt_Offset(Tab, closeObjPtr), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_OBJ, "-command", "command", "Command", DEF_TAB_COMMAND, 
        Blt_Offset(Tab, cmdObjPtr), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_STRING, "-data", "data", "data", DEF_TAB_DATA, 
	Blt_Offset(Tab, data), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_SYNONYM, "-fg", "foreground", (char *)NULL, (char *)NULL, 0, 0},
    {BLT_CONFIG_FILL, "-fill", "fill", "Fill", DEF_TAB_FILL, 
	Blt_Offset(Tab, fill), BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_COLOR, "-foreground", "foreground", "Foreground", (char *)NULL,
	Blt_Offset(Tab, textColor), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_FONT, "-font", "font", "Font", (char *)NULL, 
	Blt_Offset(Tab, font), 0},
    {BLT_CONFIG_CUSTOM, "-image", "image", "Image", DEF_TAB_IMAGE, 
	Blt_Offset(Tab, icon), BLT_CONFIG_NULL_OK, &iconOption},
    {BLT_CONFIG_PAD, "-ipadx", "iPadX", "PadX", DEF_TAB_IPAD, 
	Blt_Offset(Tab, iPadX), BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_PAD, "-ipady", "iPadY", "PadY", DEF_TAB_IPAD, 
	Blt_Offset(Tab, iPadY), BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_PAD, "-padx", "padX", "PadX", 	DEF_TAB_PAD, 
	Blt_Offset(Tab, xPad), 0},
    {BLT_CONFIG_PAD, "-pady", "padY", "PadY", DEF_TAB_PAD, 
	Blt_Offset(Tab, yPad), 0},
    {BLT_CONFIG_OBJ, "-perforationcommand", "perforationcommand", 
	"PerforationCommand", DEF_TAB_PERFORATIONCOMMAND, 
	Blt_Offset(Tab, perfCmdObjPtr), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_BACKGROUND, "-selectbackground", "selectBackground", 
	"Background", DEF_TAB_SELECTBACKGROUND, Blt_Offset(Tab, selBg), 
	BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_COLOR, "-selectforeground", "selectForeground", "Foreground",
	DEF_TAB_SELECTFOREGROUND, Blt_Offset(Tab, selColor), 
	BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_CUSTOM, "-state", "state", "State", DEF_TAB_STATE, 
	Blt_Offset(Tab, flags), BLT_CONFIG_DONT_SET_DEFAULT, &stateOption},
    {BLT_CONFIG_BITMAP, "-stipple", "stipple", "Stipple", DEF_TAB_STIPPLE, 
	Blt_Offset(Tab, stipple), 0},
    {BLT_CONFIG_STRING, "-text", "Text", "Text", DEF_TAB_TEXT, 
	Blt_Offset(Tab, text), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_CUSTOM, "-window", "window", "Window", DEF_TAB_WINDOW, 
	Blt_Offset(Tab, tkwin), BLT_CONFIG_NULL_OK, &childOption},
    {BLT_CONFIG_PIXELS_NNEG, "-windowheight", "windowHeight", "WindowHeight",
	DEF_TAB_WINDOWHEIGHT, Blt_Offset(Tab, reqSlaveHeight), 
	BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_PIXELS_NNEG, "-windowwidth", "windowWidth", "WindowWidth",
	DEF_TAB_WINDOWWIDTH, Blt_Offset(Tab, reqSlaveWidth), 
	BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_END, (char *)NULL, (char *)NULL, (char *)NULL,
	(char *)NULL, 0, 0}
};

/*
 * TabStyle --
 */
typedef struct {
    Tk_Window tkwin;			/* Default window to map pages. */

    int borderWidth;			/* Width of 3D border around the tab's
					 * label. */
    int pad;				/* Extra padding of a tab entry */

    Blt_Font font;

    XColor *textColor;
    Blt_Background bg;			/* Normal background. */

    XColor *selColor;			/* Selected foreground. */
    Blt_Background selBg;		/* Selected background. */

    Blt_Background activeBg;		/* Active background. */
    XColor *activeFg;			/* Active foreground. */

    Blt_Dashes dashes;
    GC activeGC;
    int relief;
    Tcl_Obj *cmdObjPtr;			/* Command invoked when the tab is
					 * selected */
    Tcl_Obj *perfCmdObjPtr;	

} TabStyle;

struct _Tabset {
    Tk_Window tkwin;			/* Window that embodies the widget.
					 * NULL means that the window has been
					 * destroyed but the data structures
					 * haven't yet been cleaned up.*/

    Display *display;			/* Display containing widget; needed,
					 * among other things, to release
					 * resources after tkwin has already
					 * gone away. */

    Tcl_Interp *interp;			/* Interpreter associated with
					 * widget. */

    Tcl_Command cmdToken;		/* Token for widget's command. */

    unsigned int flags;			/* For bitfield definitions, see
					 * below */

    short int inset;			/* Total width of all borders,
					 * including traversal highlight and
					 * 3-D border.  Indicates how much
					 * interior stuff must be offset from
					 * outside edges to leave room for
					 * borders. */

    short int inset2;			/* Total width of 3-D folder border +
					 * corner, Indicates how much interior
					 * stuff  must be offset from outside
					 * edges of folder.*/

    short int ySelectPad2;		/* Extra offset for selected tab. Only
					 * for single tiers. */

    short int pageTop;			/* Offset from top of tabset to the
					 * start of the page. */
    short int xOffset, yOffset;		/* Offset of pixmap buffer to top of
					 * window. */

    Blt_Painter painter;

    Tk_Cursor cursor;			/* X Cursor */

    Blt_Background bg;		        /* 3D border surrounding the
					 * window. */
    int borderWidth;			/* Width of 3D border. */
    int relief;				/* 3D border relief. */
    XColor *shadowColor;		/* Shadow color around folder. */

    int justify;
    int iconPos;

    float angle;			/* Angle to rotate tab.  This includes
					 * the icon, text, and close
					 * buttons. The tab can only be rotated
					 * at right angles: 0, 90, 180, 270,
					 * etc. */
    int quad;
    /*
     * Focus highlight ring
     */
    int highlightWidth;			/* Width in pixels of highlight to
					 * draw around widget when it has the
					 * focus.  <= 0 means don't draw a
					 * highlight. */
    XColor *highlightBg;		/* Color for drawing traversal
					 * highlight area when highlight is
					 * off. */
    XColor *highlightColor;		/* Color for drawing traversal
					 * highlight. */

    GC highlightGC;			/* GC for focus highlight. */

    const char *takeFocus;		/* Says whether to select this widget
					 * during tab traveral operations.
					 * This value isn't used in C code,
					 * but for the widget's Tcl
					 * bindings. */


    int side;				/* Orientation of the tabset: either
					 * SIDE_LEFT, SIDE_RIGHT, SIDE_TOP, or
					 * SIDE_BOTTOM. */
    int reqSlant;			/* Determines slant on either side
					 * of tab. */
    int overlap;			/* Amount of  */
    int gap;
    int reqTabWidth;			/* Requested tab size. */
    short int tabWidth, tabHeight;
    int xSelectPad, ySelectPad;		/* Padding around label of the
					 * selected tab. */
    int outerPad;			/* Padding around the exterior of the
					 * tabset and folder. */

    Button closeButton;			/* Close tab button drawn on right
					 * side of a tab. */
    Tcl_Obj *closeObjPtr;		/* Command to be executed when the tab
					 * is closed. */

    TabStyle defStyle;			/* Global attribute information
					 * specific to tabs. */

    int reqWidth, reqHeight;		/* Requested dimensions of the tabset
					 * window. */
    int pageWidth, pageHeight;		/* Dimensions of a page in the
					 * folder. */
    int reqPageWidth, reqPageHeight;	/* Requested dimensions of a page. */

    int lastX, lastY;

    /*
     * Scrolling information:
     */
    int worldWidth;
    int scrollOffset;			/* Offset of viewport in world
					 * coordinates. */
    Tcl_Obj *scrollCmdObjPtr;		/* Command strings to control
					 * scrollbar.*/
    int scrollUnits;			/* Smallest unit of scrolling for
					 * tabs. */

    /*
     * Scanning information:
     */
    int scanAnchor;			/* Scan anchor in screen coordinates. */
    int scanOffset;			/* Offset of the start of the scan in
					 * world coordinates.*/
    int corner;				/* Number of pixels to offset next
					 * point when drawing corners of the
					 * folder. */
    int reqTiers;			/* Requested number of tiers. Zero
					 * means to dynamically scroll if
					 * there are * too many tabs to be
					 * display on a single * tier. */
    int nTiers;				/* Actual number of tiers. */
    Blt_HashTable iconTable;
    Tab *plusPtr;			/* Special tab always at end of tab
					 * set. */
    Tab *selectPtr;			/* The currently selected tab.
					 * (i.e. its page is displayed). */
    Tab *activePtr;			/* Tab last located under the pointer.
					 * It is displayed with its active
					 * foreground / background
					 * colors.  */
    Tab *activeButtonPtr;		/* Tab where to pointer is located
					 * over the close button.  The button
					 * is displayed with its active
					 * foreground / background colors.  */
    Tab *focusPtr;			/* Tab currently receiving focus. */
    Tab *startPtr;			/* The first tab on the first tier. */
    Blt_Chain chain;			/* List of tab entries. Used to
					 * arrange placement of tabs. */
    Blt_HashTable tabTable;		/* Hash table of tab entries. Used for
					 * lookups of tabs by name. */
    int nextId;
    int nVisible;			/* Number of tabs that are currently
					 * visible in the view port. */
    Blt_BindTable bindTable;		/* Tab binding information */
    Blt_HashTable tagTable;		/* Table of tags. */
    Blt_HashTable bindTagTable;		/* Table of binding tags. */
};

static Blt_ConfigSpec configSpecs[] =
{
    {BLT_CONFIG_BACKGROUND, "-activebackground", "activeBackground", 
	"activeBackground", DEF_ACTIVEBACKGROUND, 
	Blt_Offset(Tabset, defStyle.activeBg), 0},
    {BLT_CONFIG_COLOR, "-activeforeground", "activeForeground",
	"activeForeground", DEF_ACTIVEFOREGROUND, 
	Blt_Offset(Tabset, defStyle.activeFg), 0},
    {BLT_CONFIG_BACKGROUND, "-background", "background", "Background",
	DEF_BACKGROUND, Blt_Offset(Tabset, defStyle.bg), 0},
    {BLT_CONFIG_SYNONYM, "-bd", "borderWidth", (char *)NULL, (char *)NULL, 0,0},
    {BLT_CONFIG_SYNONYM, "-bg", "background", (char *)NULL, (char *)NULL, 0, 0},
    {BLT_CONFIG_PIXELS_NNEG, "-borderwidth", "borderWidth", "BorderWidth",
	DEF_BORDERWIDTH, Blt_Offset(Tabset, defStyle.borderWidth),
	BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_BITMASK, "-closebutton", "closeButton", "CloseButton", 
	DEF_CLOSEBUTTON, Blt_Offset(Tabset, flags), BLT_CONFIG_DONT_SET_DEFAULT,
	(Blt_CustomOption *)CLOSE_NEEDED},
    {BLT_CONFIG_OBJ, "-closecommand", "closeCommand", "CloseCommand",
	DEF_CLOSECOMMAND, Blt_Offset(Tabset, closeObjPtr),
	BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_ACTIVE_CURSOR, "-cursor", "cursor", "Cursor",
	DEF_CURSOR, Blt_Offset(Tabset, cursor), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_DASHES, "-dashes", "dashes", "Dashes", DEF_DASHES, 
	Blt_Offset(Tabset, defStyle.dashes), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_SYNONYM, "-fg", "foreground", (char *)NULL, (char *)NULL, 
	0, 0},
    {BLT_CONFIG_COLOR, "-foreground", "foreground", "Foreground",
	DEF_FOREGROUND, Blt_Offset(Tabset, defStyle.textColor), 0},
    {BLT_CONFIG_FONT, "-font", "font", "Font",
	DEF_FONT, Blt_Offset(Tabset, defStyle.font), 0},
    {BLT_CONFIG_PIXELS_NNEG, "-gap", "gap", "Gap", DEF_GAP, 
	Blt_Offset(Tabset, gap), BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_PIXELS_NNEG, "-height", "height", "Height", DEF_HEIGHT, 
	Blt_Offset(Tabset, reqHeight), BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_COLOR, "-highlightbackground", "highlightBackground",
	"HighlightBackground", DEF_HIGHLIGHTBACKGROUND, 
	Blt_Offset(Tabset, highlightBg), 0},
    {BLT_CONFIG_COLOR, "-highlightcolor", "highlightColor", "HighlightColor",
	DEF_HIGHLIGHTCOLOR, Blt_Offset(Tabset, highlightColor), 0},
    {BLT_CONFIG_PIXELS_NNEG, "-highlightthickness", "highlightThickness",
	"HighlightThickness", DEF_HIGHLIGHTTHICKNESS, 
	Blt_Offset(Tabset, highlightWidth), BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_SIDE, "-iconposition", "iconPosition", "IconPosition", 
	DEF_ICONPOSITION, Blt_Offset(Tabset, iconPos),
        BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_JUSTIFY, "-justify", "Justify", "Justify", DEF_JUSTIFY, 
	Blt_Offset(Tabset, justify), BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_PIXELS_NNEG, "-outerborderwidth", "outerBorderWidth", 
	"OuterBorderWidth", DEF_BORDERWIDTH, Blt_Offset(Tabset, borderWidth),
	BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_PIXELS_NNEG, "-outerpad", "outerPad", "OuterPad", DEF_OUTERPAD,
	 Blt_Offset(Tabset, outerPad), BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_RELIEF, "-outerrelief", "outerRelief", "OuterRelief", 
	DEF_RELIEF, Blt_Offset(Tabset, relief), 0},
    {BLT_CONFIG_PIXELS_NNEG, "-pageheight", "pageHeight", "PageHeight",
	DEF_PAGEHEIGHT, Blt_Offset(Tabset, reqPageHeight),
	BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_PIXELS_NNEG, "-pagewidth", "pageWidth", "PageWidth",
	DEF_PAGEWIDTH, Blt_Offset(Tabset, reqPageWidth),
	BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_OBJ, "-perforationcommand", "perforationcommand", 
	"PerforationCommand", DEF_TAB_PERFORATIONCOMMAND, 
	Blt_Offset(Tabset, defStyle.perfCmdObjPtr), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_RELIEF, "-relief", "relief", "Relief",
	DEF_TABRELIEF, Blt_Offset(Tabset, defStyle.relief), 0},
    {BLT_CONFIG_FLOAT, "-rotate", "rotate", "Rotate", DEF_ROTATE, 
	Blt_Offset(Tabset, angle), BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_CUSTOM, "-tabwidth", "tabWidth", "TabWidth",
	DEF_TABWIDTH, Blt_Offset(Tabset, reqTabWidth),
	BLT_CONFIG_DONT_SET_DEFAULT, &tabWidthOption},
    {BLT_CONFIG_OBJ, "-scrollcommand", "scrollCommand", "ScrollCommand",
	(char *)NULL, Blt_Offset(Tabset, scrollCmdObjPtr),BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_PIXELS_POS, "-scrollincrement", "scrollIncrement",
	"ScrollIncrement", DEF_SCROLLINCREMENT, 
        Blt_Offset(Tabset, scrollUnits), BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_BITMASK, "-scrolltabs", "scrollTabs", "ScrollTabs", 
	DEF_SCROLLTABS, Blt_Offset(Tabset, flags), 
	BLT_CONFIG_DONT_SET_DEFAULT, (Blt_CustomOption *)SCROLL_TABS},
    {BLT_CONFIG_BACKGROUND, "-selectbackground", "selectBackground", 
	"Foreground", DEF_SELECTBACKGROUND, Blt_Offset(Tabset, defStyle.selBg),
	0},
    {BLT_CONFIG_OBJ, "-selectcommand", "selectCommand", "SelectCommand",
	DEF_SELECTCOMMAND, Blt_Offset(Tabset, defStyle.cmdObjPtr),
	BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_COLOR, "-selectforeground", "selectForeground", "Background",
	DEF_SELECTFOREGROUND, Blt_Offset(Tabset, defStyle.selColor), 0},
    {BLT_CONFIG_PIXELS_NNEG, "-selectpadx", "selectPadX", "SelectPadX",
	DEF_SELECTPADX, Blt_Offset(Tabset, xSelectPad),
	BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_PIXELS_NNEG, "-selectpady", "selectPad", "SelectPad",
	DEF_SELECTPADY, Blt_Offset(Tabset, ySelectPad),
	BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_COLOR, "-shadowcolor", "shadowColor", "ShadowColor",
	DEF_SHADOWCOLOR, Blt_Offset(Tabset, shadowColor), 0},
    {BLT_CONFIG_BITMASK, "-showsingletab", "showSingleTab", "ShowSingleTab", 
	DEF_SHOWSINGLETAB, Blt_Offset(Tabset, flags), 
	BLT_CONFIG_DONT_SET_DEFAULT, (Blt_CustomOption *)SHOW_SINGLE_TAB},
    {BLT_CONFIG_SIDE, "-side", "side", "side", DEF_SIDE, 
	Blt_Offset(Tabset, side), BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_CUSTOM, "-slant", "slant", "Slant", DEF_SLANT, 
	Blt_Offset(Tabset, reqSlant), BLT_CONFIG_DONT_SET_DEFAULT,
	&slantOption},
    {BLT_CONFIG_STRING, "-takefocus", "takeFocus", "TakeFocus",
	DEF_TAKEFOCUS, Blt_Offset(Tabset, takeFocus), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_BITMASK, "-tearoff", "tearoff", "Tearoff", DEF_TEAROFF, 
	Blt_Offset(Tabset, flags), BLT_CONFIG_DONT_SET_DEFAULT, 
	(Blt_CustomOption *)TEAROFF},
    {BLT_CONFIG_INT_POS, "-tiers", "tiers", "Tiers", DEF_TIERS, 
	Blt_Offset(Tabset, reqTiers), BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_BACKGROUND, "-troughcolor", "troughColor", "TroughColor",
	DEF_TROUGHCOLOR, Blt_Offset(Tabset, bg), 0},
    {BLT_CONFIG_PIXELS_NNEG, "-width", "width", "Width", DEF_WIDTH, 
	Blt_Offset(Tabset, reqWidth), BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_END, (char *)NULL, (char *)NULL, (char *)NULL,
	(char *)NULL, 0, 0}
};

/*
 * TabIterator --
 *
 *	Tabs may be tagged with strings.  A tab may have many tags.  The
 *	same tag may be used for many tabs.
 *	
 */
typedef enum { 
    ITER_SINGLE, ITER_ALL, ITER_TAG, ITER_PATTERN, 
} IteratorType;

typedef struct _Iterator {
    Tabset *setPtr;		       /* Tabset that we're iterating over. */

    IteratorType type;			/* Type of iteration:
					 * ITER_TAG	 By item tag.
					 * ITER_ALL      By every item.
					 * ITER_SINGLE   Single item: either 
					 *               tag or index.
					 * ITER_PATTERN  Over a consecutive 
					 *               range of indices.
					 */

    Tab *startPtr;			/* Starting item.  Starting point of
					 * search, saved if iterator is reused.
					 * Used for ITER_ALL and ITER_SINGLE
					 * searches. */
    Tab *endPtr;			/* Ending item (inclusive). */
    Tab *nextPtr;			/* Next item. */
					/* For tag-based searches. */
    char *tagName;			/* If non-NULL, is the tag that we are
					 * currently iterating over. */
    Blt_HashTable *tablePtr;		/* Pointer to tag hash table. */
    Blt_HashSearch cursor;		/* Search iterator for tag hash
					 * table. */
    Blt_ChainLink link;
} TabIterator;

/* Forward Declarations */
static Blt_BindPickProc PickTabProc;
static Blt_BindTagProc GetTagsProc;
static Tcl_CmdDeleteProc TabsetInstDeletedCmd;
static Tcl_FreeProc DestroyTabset;
static Tcl_FreeProc DestroyTearoff;
static Tcl_IdleProc AdoptWindow;
static Tcl_IdleProc DisplayTabset;
static Tcl_IdleProc DisplayTearoff;
static Tcl_ObjCmdProc TabsetCmd;
static Tcl_ObjCmdProc TabsetInstCmd;
static Tk_EventProc EmbeddedWidgetEventProc;
static Tk_EventProc TabsetEventProc;
static Tk_EventProc TearoffEventProc;
static Tk_ImageChangedProc IconChangedProc;

static void DrawLabel(Tabset *setPtr, Tab *tabPtr, Drawable drawable);
static void DrawFolder(Tabset *setPtr, Tab *tabPtr, Drawable drawable);

static void GetWindowRectangle(Tab *tabPtr, Tk_Window parent, int hasTearOff, 
	XRectangle *rectPtr);
static void ArrangeWindow(Tk_Window tkwin, XRectangle *rectPtr, int force);
static void EventuallyRedraw(Tabset *setPtr);
static void EventuallyRedrawTearoff(Tab *tabPtr);
static void ComputeLayout(Tabset *setPtr);
static void DrawOuterBorders(Tabset *setPtr, Drawable drawable);

static int GetTabIterator(Tcl_Interp *interp, Tabset *setPtr, Tcl_Obj *objPtr, 
	TabIterator *iterPtr);
static int GetTabFromObj(Tcl_Interp *interp, Tabset *setPtr, Tcl_Obj *objPtr, 
	Tab **tabPtrPtr);
static void ComputeLabelOffsets(Tabset *setPtr, Tab *tabPtr);

typedef int (TabsetCmdProc)(Tabset *setPtr, Tcl_Interp *interp, int objc, 
	Tcl_Obj *const *objv);

/*
 *---------------------------------------------------------------------------
 *
 * WorldToScreen --
 *
 *	Converts world coordinates to screen coordinates. Note that the world
 *	view is always tabs side top.
 *
 * Results:
 *	The screen coordinates are returned via *xScreenPtr and *yScreenPtr.
 *
 *---------------------------------------------------------------------------
 */
static void
WorldToScreen(Tabset *setPtr, int x, int y, int *xScreenPtr, int *yScreenPtr)
{
    int sx, sy;

    sx = sy = 0;			/* Suppress compiler warning. */

    /* Translate world X-Y to screen coordinates */
    /*
     * Note that the world X-coordinate is translated by the selected label's
     * X padding. This is done only to keep the scroll range is between 0.0
     * and 1.0, rather adding/subtracting the pad in various locations.  It
     * may be changed back in the future.
     */
    x += setPtr->inset + setPtr->xSelectPad - setPtr->scrollOffset;
    y += setPtr->inset;
    if (setPtr->nTiers == 1) {
	y += setPtr->ySelectPad;
    }
    switch (setPtr->side) {
    case SIDE_TOP:
	sx = x, sy = y;			/* Do nothing */
	break;
    case SIDE_RIGHT:
	sx = Tk_Width(setPtr->tkwin) - y;
	sy = x;
	break;
    case SIDE_LEFT:
	sy = x; sx = y;			/* Flip coordinates */
	break;
    case SIDE_BOTTOM:
	sx = x;
	sy = Tk_Height(setPtr->tkwin) - y;
	break;
    }
    *xScreenPtr = sx;
    *yScreenPtr = sy;
}

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
 *	redisplays: the whole window will be redrawn.
 *
 *---------------------------------------------------------------------------
 */
static void
EventuallyRedraw(Tabset *setPtr)
{
    if ((setPtr->tkwin != NULL) && !(setPtr->flags & REDRAW_PENDING)) {
	setPtr->flags |= REDRAW_PENDING;
	Tcl_DoWhenIdle(DisplayTabset, setPtr);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * EventuallyRedrawTearoff --
 *
 *	Queues a request to redraw the tearoff at the next idle point.
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
EventuallyRedrawTearoff(Tab *tabPtr)
{
    if ((tabPtr->tkwin != NULL) && !(tabPtr->flags & TEAROFF_REDRAW)) {
	tabPtr->flags |= TEAROFF_REDRAW;
	Tcl_DoWhenIdle(DisplayTearoff, tabPtr);
    }
}

static void
FreeIcon(Tabset *setPtr, struct _Icon *iconPtr) 
{
    iconPtr->refCount--;
    if (iconPtr->refCount == 0) {
	Blt_DeleteHashEntry(&setPtr->iconTable, iconPtr->hashPtr);
	Tk_FreeImage(iconPtr->tkImage);
	if (iconPtr->picture != NULL) {
	    Blt_FreePicture(iconPtr->picture);
	}
	Blt_Free(iconPtr);
    }
}


/*
 *---------------------------------------------------------------------------
 *
 * IconChangedProc
 *
 *	This routine is called whenever an image displayed in a tab changes.
 *	In this case, we assume that everything will change and queue a
 *	request to re-layout and redraw the entire tabset.
 *
 * Results:
 *	None.
 *
 *---------------------------------------------------------------------------
 */
/* ARGSUSED */
static void
IconChangedProc(
    ClientData clientData,
    int x, int y,			/* Not used. */
    int width, int height,		/* Not used. */
    int imageWidth, int imageHeight)	/* Not used. */
{
    Tabset *setPtr = clientData;

    setPtr->flags |= (LAYOUT_PENDING | SCROLL_PENDING | REDRAW_ALL);
    EventuallyRedraw(setPtr);
}

/*
 *---------------------------------------------------------------------------
 *
 * GetIcon --
 *
 *	This is a wrapper procedure for Tk_GetImage. The problem is that if
 *	the same image is used repeatedly in the same widget, the separate
 *	instances are saved in a linked list.  This makes it especially slow
 *	to destroy the widget.  As a workaround, this routine hashes the image
 *	and maintains a reference count for it.
 *
 * Results:
 *	Returns a pointer to the new image.
 *
 *---------------------------------------------------------------------------
 */
static Icon
GetIcon(Tabset *setPtr, Tcl_Interp *interp, Tk_Window tkwin, const char *name)
{
    struct _Icon *iconPtr;
    int isNew;
    Blt_HashEntry *hPtr;

    hPtr = Blt_CreateHashEntry(&setPtr->iconTable, name, &isNew);
    if (isNew) {
	Tk_Image tkImage;
	int width, height;
	Blt_Picture picture;

	tkImage = Tk_GetImage(interp, tkwin, name, IconChangedProc, setPtr);
	if (tkImage == NULL) {
	    Blt_DeleteHashEntry(&setPtr->iconTable, hPtr);
	    return NULL;
	}
	Tk_SizeOfImage(tkImage, &width, &height);
	iconPtr = Blt_AssertMalloc(sizeof(struct _Icon));
	iconPtr->tkImage = tkImage;
	iconPtr->hashPtr = hPtr;
	iconPtr->refCount = 1;
	iconPtr->width = width;
	iconPtr->height = height;
	iconPtr->picture = picture;
	iconPtr->angle = 0.0;
	iconPtr->picture = NULL;
	Blt_SetHashValue(hPtr, iconPtr);
    } else {
	iconPtr = Blt_GetHashValue(hPtr);
	iconPtr->refCount++;
    }
    return iconPtr;
}

/*
 *---------------------------------------------------------------------------
 *
 * FreeIconProc --
 *
 *	Releases the image if it's not being used anymore by this widget.
 *	Note there may be several uses of the same image by many tabs.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The reference count is decremented and the image is freed is it's not
 *	being used anymore.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static void
FreeIconProc(ClientData clientData, Display *display, char *widgRec, int offset)
{
    Icon *iconPtr = (Icon *)(widgRec + offset);
    Tabset *setPtr = clientData;

    if (*iconPtr != NULL) {
	FreeIcon(setPtr, *iconPtr);
	*iconPtr = NULL;
    }
}

static Blt_HashTable *
GetTagTable(Tabset *setPtr, const char *tagName)
{
    Blt_HashEntry *hPtr;

    hPtr = Blt_FindHashEntry(&setPtr->tagTable, tagName);
    if (hPtr == NULL) {
	return NULL;			/* No tag by name. */
    }
    return Blt_GetHashValue(hPtr);
}

static int
HasTag(Tab *tabPtr, const char *tagName)
{
    Blt_HashEntry *hPtr;
    Blt_HashTable *tablePtr;

    if (strcmp(tagName, "all") == 0) {
	return TRUE;
    }
    tablePtr = GetTagTable(tabPtr->setPtr, tagName);
    if (tablePtr == NULL) {
	return FALSE;
    }
    hPtr = Blt_FindHashEntry(tablePtr, (char *)tabPtr);
    if (hPtr == NULL) {
	return FALSE;
    }
    return TRUE;
}

static Blt_HashTable *
AddTagTable(Tabset *setPtr, const char *tagName)
{
    Blt_HashEntry *hPtr;
    Blt_HashTable *tablePtr;
    int isNew;

    hPtr = Blt_CreateHashEntry(&setPtr->tagTable, tagName, &isNew);
    if (isNew) {
	tablePtr = Blt_AssertMalloc(sizeof(Blt_HashTable));
	Blt_InitHashTable(tablePtr, BLT_ONE_WORD_KEYS);
	Blt_SetHashValue(hPtr, tablePtr);
    } else {
	tablePtr = Blt_GetHashValue(hPtr);
    }
    return tablePtr;
}

static void
AddTag(Tabset *setPtr, Tab *tabPtr, const char *tagName)
{
    int isNew;
    Blt_HashEntry *hPtr;
    Blt_HashTable *tablePtr;

    tablePtr = AddTagTable(setPtr, tagName);
    hPtr = Blt_CreateHashEntry(tablePtr, (char *)tabPtr, &isNew);
    if (isNew) {
	Blt_SetHashValue(hPtr, tabPtr);
    }
}


static void
ForgetTag(Tabset *setPtr, const char *tagName)
{
    Blt_HashEntry *hPtr;
    Blt_HashTable *tablePtr;

    if (strcmp(tagName, "all") == 0) {
	return;				/* Can't remove tag "all". */
    }
    hPtr = Blt_FindHashEntry(&setPtr->tagTable, tagName);
    if (hPtr == NULL) {
	return;				/* No tag by name. */
    }
    tablePtr = Blt_GetHashValue(hPtr);
    Blt_DeleteHashTable(tablePtr);
    Blt_Free(tablePtr);
    Blt_DeleteHashEntry(&setPtr->tagTable, hPtr);
}

static void
DestroyTags(Tabset *setPtr)
{
    Blt_HashEntry *hPtr;
    Blt_HashSearch iter;

    for (hPtr = Blt_FirstHashEntry(&setPtr->tagTable, &iter); hPtr != NULL;
	 hPtr = Blt_NextHashEntry(&iter)) {
	Blt_HashTable *tablePtr;
	
	tablePtr = Blt_GetHashValue(hPtr);
	Blt_DeleteHashTable(tablePtr);
    }
}

static void
RemoveTag(Tab *tabPtr, const char *tagName)
{
    Blt_HashTable *tablePtr;
    Tabset *setPtr;

    setPtr = tabPtr->setPtr;
    tablePtr = GetTagTable(setPtr, tagName);
    if (tablePtr != NULL) {
	Blt_HashEntry *hPtr;

	hPtr = Blt_FindHashEntry(tablePtr, (char *)tabPtr);
	if (hPtr != NULL) {
	    Blt_DeleteHashEntry(tablePtr, hPtr);
	}
    }
}

static void
ClearTags(Tab *tabPtr)
{
    Blt_HashEntry *hPtr;
    Blt_HashSearch iter;
    Tabset *setPtr;

    setPtr = tabPtr->setPtr;
    for (hPtr = Blt_FirstHashEntry(&setPtr->tagTable, &iter); hPtr != NULL;
	 hPtr = Blt_NextHashEntry(&iter)) {
	Blt_HashTable *tablePtr;
	Blt_HashEntry *h2Ptr;
	
	tablePtr = Blt_GetHashValue(hPtr);
	h2Ptr = Blt_FindHashEntry(tablePtr, (char *)tabPtr);
	if (h2Ptr != NULL) {
	    Blt_DeleteHashEntry(tablePtr, h2Ptr);
	}
    }
}

static void
AppendTags(Tabset *setPtr, Tab *tabPtr, Blt_List list)
{
    Blt_HashEntry *hPtr;
    Blt_HashSearch iter;

    for (hPtr = Blt_FirstHashEntry(&setPtr->tagTable, &iter); hPtr != NULL;
	 hPtr = Blt_NextHashEntry(&iter)) {
	Blt_HashTable *tablePtr;
	
	tablePtr = Blt_GetHashValue(hPtr);
	if (Blt_FindHashEntry(tablePtr, (char *)tabPtr) != NULL) {
	    Blt_List_Append(list, Blt_GetHashKey(&setPtr->tagTable, hPtr), 0);
	}
    }
}

static ClientData
MakeBindTag(Tabset *setPtr, const char *tagName)
{
    Blt_HashEntry *hPtr;
    int isNew;

    hPtr = Blt_CreateHashEntry(&setPtr->bindTagTable, tagName, &isNew);
    return Blt_GetHashKey(&setPtr->bindTagTable, hPtr);
}


/*
 *---------------------------------------------------------------------------
 *
 * ObjToIconProc --
 *
 *	Converts an image name into a Tk image token.
 *
 * Results:
 *	If the string is successfully converted, TCL_OK is returned.
 *	Otherwise, TCL_ERROR is returned and an error message is left in
 *	interpreter's result field.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ObjToIconProc(
    ClientData clientData,	/* Contains a pointer to the tabset containing
				 * this image. */
    Tcl_Interp *interp,		/* Interpreter to send results back to */
    Tk_Window tkwin,		/* Window associated with the tabset. */
    Tcl_Obj *objPtr,		/* String representation */
    char *widgRec,		/* Widget record */
    int offset,			/* Offset to field in structure */
    int flags)	
{
    Tabset *setPtr = clientData;
    Icon *iconPtr = (Icon *) (widgRec + offset);
    Icon icon;
    const char *string;
    int length;

    icon = NULL;
    string = Tcl_GetStringFromObj(objPtr, &length);
    if (length > 0) {
	icon = GetIcon(setPtr, interp, tkwin, string);
	if (icon == NULL) {
	    return TCL_ERROR;
	}
    }
    *iconPtr = icon;
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * IconToObj --
 *
 *	Converts the Tk image back to a Tcl_Obj representation (i.e.  its
 *	name).
 *
 * Results:
 *	The name of the image is returned as a Tcl_Obj.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static Tcl_Obj *
IconToObjProc(
    ClientData clientData,	/* Pointer to tabset containing image. */
    Tcl_Interp *interp,
    Tk_Window tkwin,		/* Not used. */
    char *widgRec,		/* Widget record */
    int offset,			/* Offset to field in structure */
    int flags)	
{
    Tabset *setPtr = clientData;
    Icon *iconPtr = (Icon *) (widgRec + offset);
    Tcl_Obj *objPtr;

    if (*iconPtr == NULL) {
	objPtr = Tcl_NewStringObj("", -1);
    } else {
	const char *name;

	name = Blt_GetHashKey(&setPtr->iconTable, (*iconPtr)->hashPtr);
	objPtr = Tcl_NewStringObj(name, -1);
    }
    return objPtr;
}

/*
 *---------------------------------------------------------------------------
 *
 * ObjToSlantProc --
 *
 *	Converts the slant style string into its numeric representation.
 *
 *	Valid style strings are:
 *
 *	  "none"   Both sides are straight.
 * 	  "left"   Left side is slanted.
 *	  "right"  Right side is slanted.
 *	  "both"   Both sides are slanted.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ObjToSlantProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,			/* Interpreter to report results to */
    Tk_Window tkwin,			/* Not used. */
    Tcl_Obj *objPtr,			/* String representation of
					 * attribute. */
    char *widgRec,			/* Widget record */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    const char *string;
    char c;
    int *slantPtr = (int *)(widgRec + offset);
    int slant;
    int length;

    string = Tcl_GetStringFromObj(objPtr, &length);
    c = string[0];
    if ((c == 'n') && (strncmp(string, "none", length) == 0)) {
	slant = SLANT_NONE;
    } else if ((c == 'l') && (strncmp(string, "left", length) == 0)) {
	slant = SLANT_LEFT;
    } else if ((c == 'r') && (strncmp(string, "right", length) == 0)) {
	slant = SLANT_RIGHT;
    } else if ((c == 'b') && (strncmp(string, "both", length) == 0)) {
	slant = SLANT_BOTH;
    } else {
	Tcl_AppendResult(interp, "bad argument \"", string,
	    "\": should be \"none\", \"left\", \"right\", or \"both\"",
	    (char *)NULL);
	return TCL_ERROR;
    }
    *slantPtr &= ~SLANT_BOTH;
    *slantPtr |= slant;
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * SlantToObjProc --
 *
 *	Returns the slant style string based upon the slant flags.
 *
 * Results:
 *	The slant style string is returned.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static Tcl_Obj *
SlantToObjProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,
    Tk_Window tkwin,			/* Not used. */
    char *widgRec,			/* Widget structure record. */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    int slant = *(int *)(widgRec + offset);
    const char *string;

    switch (slant & SLANT_BOTH) {
    case SLANT_LEFT:	string = "left";	break;
    case SLANT_RIGHT:	string = "right";	break;
    case SLANT_NONE:	string = "none";	break;
    case SLANT_BOTH:	string = "both";	break;
    default:		string = "???";		break;
    }
    return Tcl_NewStringObj(string, -1);
}

/*
 *---------------------------------------------------------------------------
 *
 * ObjToChildProc --
 *
 *	Converts a window name into Tk window.
 *
 * Results:
 *	If the string is successfully converted, TCL_OK is returned.
 *	Otherwise, TCL_ERROR is returned and an error message is left
 *	in interpreter's result field.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ObjToChildProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,			/* Interpreter to report results. */
    Tk_Window parent,			/* Parent window */
    Tcl_Obj *objPtr,			/* String representation. */
    char *widgRec,			/* Widget record */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    Tab *tabPtr = (Tab *)widgRec;
    Tk_Window *tkwinPtr = (Tk_Window *)(widgRec + offset);
    Tk_Window old, tkwin;
    Tabset *setPtr;
    const char *string;

    old = *tkwinPtr;
    tkwin = NULL;
    setPtr = tabPtr->setPtr;
    string = Tcl_GetString(objPtr);
    if (string[0] != '\0') {
	tkwin = Tk_NameToWindow(interp, string, parent);
	if (tkwin == NULL) {
	    return TCL_ERROR;
	}
	if (tkwin == old) {
	    return TCL_OK;
	}
	/*
	 * Allow only widgets that are children of the tabset to be embedded
	 * into the page.  This way we can make assumptions about the window
	 * based upon its parent; either it's the tabset window or it has
	 * been torn off.
	 */
	parent = Tk_Parent(tkwin);
	if (parent != setPtr->tkwin) {
	    Tcl_AppendResult(interp, "can't manage \"", Tk_PathName(tkwin),
		"\" in tabset \"", Tk_PathName(setPtr->tkwin), "\"",
		(char *)NULL);
	    return TCL_ERROR;
	}
	Tk_ManageGeometry(tkwin, &tabMgrInfo, tabPtr);
	Tk_CreateEventHandler(tkwin, StructureNotifyMask, 
		EmbeddedWidgetEventProc, tabPtr);

	/*
	 * We need to make the window to exist immediately.  If the window is
	 * torn off (placed into another container window), the timing between
	 * the container and the its new child (this window) gets tricky.
	 * This should work for Tk 4.2.
	 */
	Tk_MakeWindowExist(tkwin);
    }
    if (old != NULL) {
	if (tabPtr->container != NULL) {
	    Tcl_EventuallyFree(tabPtr, DestroyTearoff);
	}
	Tk_DeleteEventHandler(old, StructureNotifyMask, 
	      EmbeddedWidgetEventProc, tabPtr);
	Tk_ManageGeometry(old, (Tk_GeomMgr *) NULL, tabPtr);
	Tk_UnmapWindow(old);
    }
    *tkwinPtr = tkwin;
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * ChildToObjProc --
 *
 *	Converts the Tk window back to a Tcl_Obj (i.e. its name).
 *
 * Results:
 *	The name of the window is returned.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static Tcl_Obj *
ChildToObjProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,
    Tk_Window parent,			/* Not used. */
    char *widgRec,			/* Widget record */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    Tk_Window tkwin = *(Tk_Window *)(widgRec + offset);
    Tcl_Obj *objPtr;

    if (tkwin == NULL) {
	objPtr = Tcl_NewStringObj("", -1);
    } else {
	objPtr = Tcl_NewStringObj(Tk_PathName(tkwin), -1);
    }
    return objPtr;
}

/*
 *---------------------------------------------------------------------------
 *
 * ObjToTabWidthProc --
 *
 *	Converts the tab width style string into its numeric representation.
 *
 *	Valid width strings are:
 *
 *	  "variable"	Tab width determined by text/image label.
 * 	  "same"	Tab width is max of all text/image labels.
 *	  "1i"		Tab width is set to 1 inch.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ObjToTabWidthProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,		        /* Interpreter to report results. */
    Tk_Window tkwin,			/* Not used. */
    Tcl_Obj *objPtr,			/* String representation of
					 * attribute. */
    char *widgRec,			/* Widget record */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    const char *string;
    char c;
    int *widthPtr = (int *)(widgRec + offset);
    int length;

    string = Tcl_GetStringFromObj(objPtr, &length);
    c = string[0];
    if ((c == 'v') && (strncmp(string, "variable", length) == 0)) {
	*widthPtr = TABWIDTH_VARIABLE;
    } else if ((c == 's') && (strncmp(string, "same", length) == 0)) {
	*widthPtr = TABWIDTH_SAME;
    } else if (Blt_GetPixelsFromObj(interp, tkwin, objPtr, PIXELS_POS, 
		widthPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * TabWidthToObjProc --
 *
 *	Returns the tabwidth string based upon the tabwidth.
 *
 * Results:
 *	The tabwidth string is returned.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static Tcl_Obj *
TabWidthToObjProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,
    Tk_Window tkwin,			/* Not used. */
    char *widgRec,			/* Widget structure record. */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    int width = *(int *)(widgRec + offset);

    switch (width) {
    case TABWIDTH_VARIABLE:
	return Tcl_NewStringObj("variable", 8);
    case TABWIDTH_SAME:
	return Tcl_NewStringObj("same", 4);
    default:
	return Tcl_NewIntObj(width);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * ObjToStateProc --
 *
 *	Convert the string representation of an tab state into a flag.
 *
 * Results:
 *	The return value is a standard TCL result.  The state flags are
 *	updated.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ObjToStateProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,			/* Interpreter to report results. */
    Tk_Window tkwin,			/* Not used. */
    Tcl_Obj *objPtr,			/* String representing state. */
    char *widgRec,			/* Widget record */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    Tab *tabPtr = (Tab *)(widgRec);
    unsigned int *flagsPtr = (unsigned int *)(widgRec + offset);
    char *string;
    Tabset *setPtr;
    int flag;

    string = Tcl_GetString(objPtr);
    if (strcmp(string, "active") == 0) {
	flag = ACTIVE;
    } else if (strcmp(string, "disabled") == 0) {
	flag = DISABLED;
    } else if (strcmp(string, "hidden") == 0) {
	flag = HIDE;
    } else if (strcmp(string, "normal") == 0) {
	flag = NORMAL;
    } else {
	Tcl_AppendResult(interp, "unknown state \"", string, 
		"\": should be active, disabled, hidden, or normal.", 
		(char *)NULL);
	return TCL_ERROR;
    }
    if (tabPtr->flags & flag) {
	return TCL_OK;			/* State is already set to value. */
    }
    setPtr = tabPtr->setPtr;
    if (setPtr->activePtr != tabPtr) {
	setPtr->activePtr = NULL;
    }
    *flagsPtr &= ~STATE_MASK;
    *flagsPtr |= flag;
    if (flag == ACTIVE) {
	setPtr->activePtr = tabPtr;
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * StateToObjProc --
 *
 *	Return the name of the style.
 *
 * Results:
 *	The name representing the style is returned.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static Tcl_Obj *
StateToObjProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,
    Tk_Window tkwin,			/* Not used. */
    char *widgRec,			/* Widget information record */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    unsigned int state = *(unsigned int *)(widgRec + offset);
    Tcl_Obj *objPtr;

    if (state & HIDE) {
	objPtr = Tcl_NewStringObj("hidden", -1);
    } else if (state & DISABLED) {
	objPtr = Tcl_NewStringObj("disabled", -1);
    } else if (state & ACTIVE) {
	objPtr = Tcl_NewStringObj("active", -1);
    } else {
	objPtr = Tcl_NewStringObj("normal", -1);
    }
    return objPtr;
}

static int
WorldY(Tab *tabPtr)
{
    int tier;

    tier = tabPtr->setPtr->nTiers - tabPtr->tier;
    return tier * tabPtr->setPtr->tabHeight;
}

static INLINE Tab *
FirstTab(Tabset *setPtr, unsigned int hateFlags)
{
    Blt_ChainLink link;

    for (link = Blt_Chain_FirstLink(setPtr->chain); link != NULL;
	 link = Blt_Chain_NextLink(link)) {
	Tab *tabPtr;

	tabPtr = Blt_Chain_GetValue(link);
	if ((tabPtr->flags & hateFlags) == 0) {
	    return tabPtr;
	}
    }
    return NULL;
}

static INLINE Tab *
LastTab(Tabset *setPtr, unsigned int hateFlags)
{
    Blt_ChainLink link;

    for (link = Blt_Chain_LastLink(setPtr->chain); link != NULL;
	 link = Blt_Chain_PrevLink(link)) {
	Tab *tabPtr;

	tabPtr = Blt_Chain_GetValue(link);
	if ((tabPtr->flags & hateFlags) == 0) {
	    return tabPtr;
	}
    }
    return NULL;
}


static Tab *
NextTab(Tab *tabPtr, unsigned int hateFlags)
{
    if (tabPtr != NULL) {
	Blt_ChainLink link;

	for (link = Blt_Chain_NextLink(tabPtr->link); link != NULL; 
	     link = Blt_Chain_NextLink(link)) {
	    tabPtr = Blt_Chain_GetValue(link);
	    if ((tabPtr->flags & hateFlags) == 0) {
		return tabPtr;
	    }
	}
    }
    return NULL;
}

static Tab *
PrevTab(Tab *tabPtr, unsigned int hateFlags)
{
    if (tabPtr != NULL) {
	Blt_ChainLink link;
	
	for (link = Blt_Chain_PrevLink(tabPtr->link); link != NULL; 
	     link = Blt_Chain_PrevLink(link)) {
	    tabPtr = Blt_Chain_GetValue(link);
	    if ((tabPtr->flags & hateFlags) == 0) {
		return tabPtr;
	    }
	}
    }
    return NULL;
}

static INLINE Tab *
BeginTab(Tabset *setPtr)
{
    Blt_ChainLink link;

    link = Blt_Chain_FirstLink(setPtr->chain); 
    if (link != NULL) {
	return Blt_Chain_GetValue(link);
    }
    return NULL;
}

static INLINE Tab *
EndTab(Tabset *setPtr)
{
    Blt_ChainLink link;

    link = Blt_Chain_LastLink(setPtr->chain); 
    if (link != NULL) {
	return Blt_Chain_GetValue(link);
    }
    return NULL;
}

static Tab *
StepTab(Tab *tabPtr)
{
    if (tabPtr != NULL) {
	Blt_ChainLink link;

	link = Blt_Chain_NextLink(tabPtr->link); 
	if (link != NULL) {
	    return Blt_Chain_GetValue(link);
	}
    }
    return NULL;
}


static void
ReindexTabs(Tabset *setPtr)
{
    int count;
    Tab *tabPtr;
    
    count = 0;
    for (tabPtr = FirstTab(setPtr, 0); tabPtr != NULL; 
	 tabPtr = NextTab(tabPtr, 0)) {
	tabPtr->index = count;
	count++;
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * RenumberTiers --
 *
 *	In multi-tier mode, we need to find the start of the tier containing
 *	the newly selected tab.
 *
 *	Tiers are draw from the last tier to the first, so that the the
 *	lower-tiered tabs will partially cover the bottoms of tab directly
 *	above it.  This simplifies the drawing of tabs because we don't worry
 *	how tabs are clipped by their neighbors.
 *
 *	In addition, tabs are re-marked with the correct tier number.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Renumbering the tab's tier will change the vertical placement
 *	of the tab (i.e. shift tiers).
 *
 *---------------------------------------------------------------------------
 */
static void
RenumberTiers(Tabset *setPtr, Tab *tabPtr)
{
    int tier;
    Blt_ChainLink link, last;

    setPtr->focusPtr = setPtr->selectPtr = tabPtr;
    Blt_SetFocusItem(setPtr->bindTable, setPtr->focusPtr, NULL);

    tier = tabPtr->tier;
    for (link = Blt_Chain_PrevLink(tabPtr->link); link != NULL; link = last) {
	Tab *prevPtr;

	last = Blt_Chain_PrevLink(link);
	prevPtr = Blt_Chain_GetValue(link);
	if ((prevPtr == NULL) || (prevPtr->tier != tier)) {
	    break;
	}
	tabPtr = prevPtr;
    }
    setPtr->startPtr = tabPtr;
    for (link = Blt_Chain_FirstLink(setPtr->chain); link != NULL;
	link = Blt_Chain_NextLink(link)) {
	tabPtr = Blt_Chain_GetValue(link);
	tabPtr->tier = (tabPtr->tier - tier + 1);
	if (tabPtr->tier < 1) {
	    tabPtr->tier += setPtr->nTiers;
	}
	tabPtr->worldY = WorldY(tabPtr);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * PickTabProc --
 *
 *	Searches the tab located within the given screen X-Y coordinates in
 *	the viewport.  Note that tabs overlap slightly, so that its important
 *	to search from the innermost tier out.
 *
 * Results:
 *	Returns the pointer to the tab.  If the pointer isn't contained by any
 *	tab, NULL is returned.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static ClientData
PickTabProc(ClientData clientData, int x, int y, ClientData *contextPtr)
{
    Tabset *setPtr = clientData;
    Tab *tabPtr;
    int xSelPad, ySelPad;

    if (contextPtr != NULL) {
	*contextPtr = NULL;
    }
    tabPtr = setPtr->selectPtr;
    if ((setPtr->flags & TEAROFF) && (tabPtr != NULL) && 
	(tabPtr->container == NULL) && (tabPtr->tkwin != NULL)) {
	int top, bottom, left, right;
	int sx, sy;

	/* Check first for perforation on the selected tab. */
	WorldToScreen(setPtr, tabPtr->worldX + 2, 
	      tabPtr->worldY + tabPtr->worldHeight + 4, &sx, &sy);
	if (setPtr->side & (SIDE_TOP|SIDE_BOTTOM)) {
	    left = sx - 2;
	    right = left + tabPtr->screenWidth;
	    top = sy - 4;
	    bottom = sy + 4;
	} else {
	    left = sx - 4;
	    right = sx + 4;
	    top = sy - 2;
	    bottom = top + tabPtr->screenHeight;
	}
	if ((x >= left) && (y >= top) && (x < right) && (y < bottom)) {
	    if (contextPtr != NULL) {
		*contextPtr = TAB_PERFORATION;
	    }
	    return setPtr->selectPtr;
	}
    } 
    /* Adjust the label's area according to the tab's slant. */
    if (setPtr->side & (SIDE_RIGHT | SIDE_LEFT)) {
	y -= (setPtr->flags & SLANT_LEFT) ? setPtr->tabHeight : setPtr->inset2;
    } else {
	x -= (setPtr->flags & SLANT_LEFT) ? setPtr->tabHeight : setPtr->inset2;
    }
    for (tabPtr = FirstTab(setPtr, 0); tabPtr != NULL;
	 tabPtr = NextTab(tabPtr, 0)) {
	GadgetRegion *rPtr;

	if ((tabPtr->flags & ONSCREEN) == 0) {
	    continue;
	}
	if ((x >= tabPtr->screenX) && (y >= tabPtr->screenY) &&
	    (x <= (tabPtr->screenX + tabPtr->screenWidth)) &&
	    (y < (tabPtr->screenY + tabPtr->screenHeight + 4 + 
		  setPtr->ySelectPad))) {
	    if (contextPtr != NULL) {
		*contextPtr = TAB_LABEL;
	    }
	    rPtr = &tabPtr->buttonRegion;
	    if ((tabPtr->flags & CLOSE_NEEDED) && 
		(x >= (tabPtr->screenX + rPtr->x)) && 
		 (x < (tabPtr->screenX + rPtr->x + rPtr->w)) && 
		 (y >= (tabPtr->screenY + rPtr->y)) && 
		 (y < (tabPtr->screenY + rPtr->y + rPtr->h))) {
		*contextPtr = TAB_BUTTON;
	    }
	    return tabPtr;
	}
    }
    return NULL;
}

static Tab *
TabLeft(Tab *tabPtr)
{
    Blt_ChainLink link;

    link = Blt_Chain_PrevLink(tabPtr->link);
    if (link != NULL) {
	Tab *newPtr;

	newPtr = Blt_Chain_GetValue(link);
	/* Move only if the next tab is the same tier. */
	if (newPtr->tier == tabPtr->tier) {
	    tabPtr = newPtr;
	}
    }
    return tabPtr;
}

static Tab *
TabRight(Tab *tabPtr)
{
    Blt_ChainLink link;

    link = Blt_Chain_NextLink(tabPtr->link);
    if (link != NULL) {
	Tab *newPtr;

	newPtr = Blt_Chain_GetValue(link);
	/* Move only if the next tab is on the same tier. */
	if (newPtr->tier == tabPtr->tier) {
	    tabPtr = newPtr;
	}
    }
    return tabPtr;
}

static Tab *
TabUp(Tab *tabPtr)
{
    if (tabPtr != NULL) {
	Tabset *setPtr;
	int x, y;
	int worldX, worldY;
	
	setPtr = tabPtr->setPtr;
	worldX = tabPtr->worldX + (tabPtr->worldWidth / 2);
	worldY = tabPtr->worldY - (setPtr->tabHeight / 2);
	WorldToScreen(setPtr, worldX, worldY, &x, &y);
	
	tabPtr = (Tab *)PickTabProc(setPtr, x, y, NULL);
	if (tabPtr == NULL) {
	    /*
	     * We might have inadvertly picked the gap between two tabs, so if
	     * the first pick fails, try again a little to the left.
	     */
	    WorldToScreen(setPtr, worldX + setPtr->gap, worldY, &x, &y);
	    tabPtr = (Tab *)PickTabProc(setPtr, x, y, NULL);
	}
	if ((tabPtr == NULL) &&
	    (setPtr->focusPtr->tier < (setPtr->nTiers - 1))) {
	    worldY -= setPtr->tabHeight;
	    WorldToScreen(setPtr, worldX, worldY, &x, &y);
	    tabPtr = (Tab *)PickTabProc(setPtr, x, y, NULL);
	}
	if (tabPtr == NULL) {
	    tabPtr = setPtr->focusPtr;
	}
    }
    return tabPtr;
}

static Tab *
TabDown(Tab *tabPtr)
{
    if (tabPtr != NULL) {
	Tabset *setPtr;
	int x, y;
	int worldX, worldY;

	setPtr = tabPtr->setPtr;
	worldX = tabPtr->worldX + (tabPtr->worldWidth / 2);
	worldY = tabPtr->worldY + (3 * setPtr->tabHeight) / 2;
	WorldToScreen(setPtr, worldX, worldY, &x, &y);
	tabPtr = (Tab *)PickTabProc(setPtr, x, y, NULL);
	if (tabPtr == NULL) {
	    /*
	     * We might have inadvertly picked the gap between two tabs, so if
	     * the first pick fails, try again a little to the left.
	     */
	    WorldToScreen(setPtr, worldX - setPtr->gap, worldY, &x, &y);
	    tabPtr = (Tab *)PickTabProc(setPtr, x, y, NULL);
	}
	if ((tabPtr == NULL) && (setPtr->focusPtr->tier > 2)) {
	    worldY += setPtr->tabHeight;
	    WorldToScreen(setPtr, worldX, worldY, &x, &y);
	    tabPtr = (Tab *)PickTabProc(setPtr, x, y, NULL);
	}
	if (tabPtr == NULL) {
	    tabPtr = setPtr->focusPtr;
	}
    }
    return tabPtr;
}

/*
 *---------------------------------------------------------------------------
 *
 * NextTaggedTab --
 *
 *	Returns the next tab derived from the given tag.
 *
 * Results:
 *	Returns the pointer to the next tab in the iterator.  If no more tabs
 *	are available, then NULL is returned.
 *
 *---------------------------------------------------------------------------
 */
static Tab *
NextTaggedTab(TabIterator *iterPtr)
{
    switch (iterPtr->type) {
    case ITER_TAG:
	{
	    Blt_HashEntry *hPtr;
	    
	    hPtr = Blt_NextHashEntry(&iterPtr->cursor); 
	    if (hPtr != NULL) {
		return Blt_GetHashValue(hPtr);
	    }
	    break;
	}
    case ITER_ALL:
	if (iterPtr->link != NULL) {
	    Tab *tabPtr;
	    
	    tabPtr = Blt_Chain_GetValue(iterPtr->link);
	    iterPtr->link = Blt_Chain_NextLink(iterPtr->link);
	    return tabPtr;
	}
	break;
    case ITER_PATTERN:
	{
	    Blt_ChainLink link;
	    
	    for (link = iterPtr->link; link != NULL; 
		 link = Blt_Chain_NextLink(link)) {
		Tab *tabPtr;
		
		tabPtr = Blt_Chain_GetValue(iterPtr->link);
		if (Tcl_StringMatch(tabPtr->text, iterPtr->tagName)) {
		    iterPtr->link = Blt_Chain_NextLink(link);
		    return tabPtr;
		}
	    }
	    break;
	}
    default:
	break;
    }	
    return NULL;
}

/*
 *---------------------------------------------------------------------------
 *
 * FirstTaggedTab --
 *
 *	Returns the first tab derived from the given tag.
 *
 * Results:
 *	Returns the first tab in the sequence.  If no more tabs are in
 *	the list, then NULL is returned.
 *
 *---------------------------------------------------------------------------
 */
static Tab *
FirstTaggedTab(TabIterator *iterPtr)
{
    switch (iterPtr->type) {
    case ITER_TAG:
	{
	    Blt_HashEntry *hPtr;
	    
	    hPtr = Blt_FirstHashEntry(iterPtr->tablePtr, &iterPtr->cursor);
	    if (hPtr != NULL) {
		return Blt_GetHashValue(hPtr);
	    }
	}

    case ITER_ALL:
	if (iterPtr->link != NULL) {
	    Tab *tabPtr;
	    
	    tabPtr = Blt_Chain_GetValue(iterPtr->link);
	    iterPtr->link = Blt_Chain_NextLink(iterPtr->link);
	    return tabPtr;
	}
	break;

    case ITER_PATTERN:
	{
	    Blt_ChainLink link;
	    
	    for (link = iterPtr->link; link != NULL; 
		 link = Blt_Chain_NextLink(link)) {
		Tab *tabPtr;
		
		tabPtr = Blt_Chain_GetValue(iterPtr->link);
		if (Tcl_StringMatch(tabPtr->text, iterPtr->tagName)) {
		    iterPtr->link = Blt_Chain_NextLink(link);
		    return tabPtr;
		}
	    }
	    break;
	}
    case ITER_SINGLE:
	return iterPtr->startPtr;
    } 
    return NULL;
}

/*
 *---------------------------------------------------------------------------
 *
 * GetTabFromObj --
 *
 *	Gets the tab associated the given index, tag, or label.  This routine
 *	is used when you want only one tab.  It's an error if more than one
 *	tab is specified (e.g. "all" tag or range "1:4").  It's also an error
 *	if the tag is empty (no tabs are currently tagged).
 *
 *---------------------------------------------------------------------------
 */
static int 
GetTabFromObj(Tcl_Interp *interp, Tabset *setPtr, Tcl_Obj *objPtr,
	      Tab **tabPtrPtr)
{
    TabIterator iter;
    Tab *firstPtr;

    if (GetTabIterator(interp, setPtr, objPtr, &iter) != TCL_OK) {
	return TCL_ERROR;
    }
    firstPtr = FirstTaggedTab(&iter);
    if (firstPtr != NULL) {
	Tab *nextPtr;

	nextPtr = NextTaggedTab(&iter);
	if (nextPtr != NULL) {
	    if (interp != NULL) {
		Tcl_AppendResult(interp, "multiple tabs specified by \"", 
			Tcl_GetString(objPtr), "\"", (char *)NULL);
	    }
	    return TCL_ERROR;
	}
    }
    *tabPtrPtr = firstPtr;
    return TCL_OK;
}

static int
GetTabByIndex(Tcl_Interp *interp, Tabset *setPtr, const char *string, 
	      int length, Tab **tabPtrPtr)
{
    Tab *tabPtr;
    char c;
    long pos;

    tabPtr = NULL;
    c = string[0];
    length = strlen(string);
    if (Blt_GetLong(NULL, string, &pos) == TCL_OK) {
	Blt_ChainLink link;

	link = Blt_Chain_GetNthLink(setPtr->chain, pos);
	if (link != NULL) {
	    tabPtr = Blt_Chain_GetValue(link);
	} 
	if (tabPtr == NULL) {
	    if (interp != NULL) {
		Tcl_AppendResult(interp, "can't find tab: bad index \"", 
			string, "\"", (char *)NULL);
	    }
	    return TCL_ERROR;
	}		
    } else if ((c == 'a') && (strncmp(string, "active", length) == 0)) {
	tabPtr = setPtr->activePtr;
    } else if ((c == 'c') && (strncmp(string, "current", length) == 0)) {
	tabPtr = (Tab *)Blt_GetCurrentItem(setPtr->bindTable);
    } else if ((c == 'd') && (strncmp(string, "down", length) == 0)) {
	switch (setPtr->side) {
	case SIDE_LEFT:
	case SIDE_RIGHT:
	    tabPtr = TabRight(setPtr->focusPtr);
	    break;
	    
	case SIDE_BOTTOM:
	    tabPtr = TabUp(setPtr->focusPtr);
	    break;
	    
	case SIDE_TOP:
	    tabPtr = TabDown(setPtr->focusPtr);
	    break;
	}
    } else if ((c == 'f') && (length > 1) && 
	       (strncmp(string, "focus", length) == 0)) {
	tabPtr = setPtr->focusPtr;
    } else if ((c == 'f') && (length > 1) && 
	       (strncmp(string, "first", length) == 0)) {
	tabPtr = FirstTab(setPtr, HIDE | DISABLED);
    } else if ((c == 's') && (strncmp(string, "selected", length) == 0)) {
	tabPtr = setPtr->selectPtr;
    } else if ((c == 'l') && (length > 1) && 
	       (strncmp(string, "last", length) == 0)) {
	tabPtr = LastTab(setPtr, HIDE | DISABLED);
    } else if ((c == 'l') && (length > 1) && 
	       (strncmp(string, "left", length) == 0)) {
	switch (setPtr->side) {
	case SIDE_LEFT:
	    tabPtr = TabUp(setPtr->focusPtr);
	    break;
	    
	case SIDE_RIGHT:
	    tabPtr = TabDown(setPtr->focusPtr);
	    break;
	    
	case SIDE_BOTTOM:
	case SIDE_TOP:
	    tabPtr = TabLeft(setPtr->focusPtr);
	    break;
	}
    } else if ((c == 'n') && (strncmp(string, "none", length) == 0)) {
	tabPtr = NULL;
    } else if ((c == 'r') && (strncmp(string, "right", length) == 0)) {
	switch (setPtr->side) {
	case SIDE_LEFT:
	    tabPtr = TabDown(setPtr->focusPtr);
	    break;
	    
	case SIDE_RIGHT:
	    tabPtr = TabUp(setPtr->focusPtr);
	    break;
	    
	case SIDE_BOTTOM:
	case SIDE_TOP:
	    tabPtr = TabRight(setPtr->focusPtr);
	    break;
	}
    } else if ((c == 'u') && (strncmp(string, "up", length) == 0)) {
	switch (setPtr->side) {
	case SIDE_LEFT:
	case SIDE_RIGHT:
	    tabPtr = TabLeft(setPtr->focusPtr);
	    break;
	    
	case SIDE_BOTTOM:
	    tabPtr = TabDown(setPtr->focusPtr);
	    break;
	    
	case SIDE_TOP:
	    tabPtr = TabUp(setPtr->focusPtr);
	    break;
	}
    } else if (c == '@') {
	int x, y;

	if (Blt_GetXY(interp, setPtr->tkwin, string, &x, &y) != TCL_OK) {
	    return TCL_ERROR;
	}
	tabPtr = (Tab *)PickTabProc(setPtr, x, y, NULL);
    } else {
	return TCL_CONTINUE;
    }
    *tabPtrPtr = tabPtr;
    return TCL_OK;
}

static Tab *
GetTabByName(Tabset *setPtr, const char *string)
{
    Blt_HashEntry *hPtr;
    
    hPtr = Blt_FindHashEntry(&setPtr->tabTable, string);
    if (hPtr == NULL) {
	return NULL;
    }
    return Blt_GetHashValue(hPtr);
}


/*
 *---------------------------------------------------------------------------
 *
 * GetTabIterator --
 *
 *	Converts a string representing a tab index into an tab pointer.  The
 *	index may be in one of the following forms:
 *
 *	 number		Tab at index in the list of tabs.
 *	 @x,y		Tab closest to the specified X-Y screen coordinates.
 *	 "active"	Tab where mouse pointer is located.
 *	 "posted"       Tab is the currently posted cascade tab.
 *	 "next"		Next tab from the focus tab.
 *	 "previous"	Previous tab from the focus tab.
 *	 "end"		Last tab.
 *	 "none"		No tab.
 *
 *	 number		Tab at position in the list of tabs.
 *	 @x,y		Tab closest to the specified X-Y screen coordinates.
 *	 "active"	Tab mouse is located over.
 *	 "focus"	Tab is the widget's focus.
 *	 "select"	Currently selected tab.
 *	 "right"	Next tab from the focus tab.
 *	 "left"		Previous tab from the focus tab.
 *	 "up"		Next tab from the focus tab.
 *	 "down"		Previous tab from the focus tab.
 *	 "end"		Last tab in list.
 *	"name:string"   Tab named "string".
 *	"index:number"  Tab at index number in list of tabs.
 *	"tag:string"	Tab(s) tagged by "string".
 *	"label:pattern"	Tab(s) with label matching "pattern".
 *	
 * Results:
 *	If the string is successfully converted, TCL_OK is returned.  The
 *	pointer to the node is returned via tabPtrPtr.  Otherwise, TCL_ERROR
 *	is returned and an error message is left in interpreter's result
 *	field.
 *
 *---------------------------------------------------------------------------
 */
static int
GetTabIterator(Tcl_Interp *interp, Tabset *setPtr, Tcl_Obj *objPtr,
	       TabIterator *iterPtr)
{
    Tab *tabPtr, *startPtr, *endPtr;
    Blt_HashTable *tablePtr;
    char *string;
    char c;
    int nBytes;
    int length;
    int result;

    iterPtr->setPtr = setPtr;
    iterPtr->type = ITER_SINGLE;
    iterPtr->tagName = Tcl_GetStringFromObj(objPtr, &nBytes);
    iterPtr->nextPtr = NULL;
    iterPtr->startPtr = iterPtr->endPtr = NULL;

    if (setPtr->focusPtr == NULL) {
	setPtr->focusPtr = setPtr->selectPtr;
	Blt_SetFocusItem(setPtr->bindTable, setPtr->focusPtr, NULL);
    }
    string = Tcl_GetStringFromObj(objPtr, &length);
    c = string[0];
    iterPtr->startPtr = iterPtr->endPtr = setPtr->activePtr;
    startPtr = endPtr = tabPtr = NULL;
    if (c == '\0') {
	startPtr = endPtr = NULL;
    } 
    iterPtr->type = ITER_SINGLE;
    result = GetTabByIndex(interp, setPtr, string, length, &tabPtr);
    if (result == TCL_ERROR) {
	return TCL_ERROR;
    }
    if (result == TCL_OK) {
	iterPtr->startPtr = iterPtr->endPtr = tabPtr;
	return TCL_OK;
    }
    if ((c == 'a') && (strcmp(iterPtr->tagName, "all") == 0)) {
	iterPtr->type  = ITER_ALL;
	iterPtr->link = Blt_Chain_FirstLink(setPtr->chain);
    } else if ((c == 'i') && (length > 6) && 
	       (strncmp(string, "index:", 6) == 0)) {
	if (GetTabByIndex(interp, setPtr, string + 6, length - 6, &tabPtr) 
	    != TCL_OK) {
	    return TCL_ERROR;
	}
	iterPtr->startPtr = iterPtr->endPtr = tabPtr;
    } else if ((c == 'n') && (length > 5) && 
	       (strncmp(string, "name:", 5) == 0)) {
	tabPtr = GetTabByName(setPtr, string + 5);
	if (tabPtr == NULL) {
	    if (interp != NULL) {
		Tcl_AppendResult(interp, "can't find a tab name \"", string + 5,
			"\" in \"", Tk_PathName(setPtr->tkwin), "\"",
			(char *)NULL);
	    }
	    return TCL_ERROR;
	}
	iterPtr->startPtr = iterPtr->endPtr = tabPtr;
    } else if ((c == 't') && (length > 4) && 
	       (strncmp(string, "tag:", 4) == 0)) {
	Blt_HashTable *tablePtr;

	tablePtr = GetTagTable(setPtr, string + 4);
	if (tablePtr == NULL) {
	    if (interp != NULL) {
		Tcl_AppendResult(interp, "can't find a tag \"", string + 5,
			"\" in \"", Tk_PathName(setPtr->tkwin), "\"",
			(char *)NULL);
	    }
	    return TCL_ERROR;
	}
	iterPtr->tagName = string + 4;
	iterPtr->tablePtr = tablePtr;
	iterPtr->type = ITER_TAG;
    } else if ((c == 'l') && (length > 6) && 
	       (strncmp(string, "label:", 6) == 0)) {
	iterPtr->link = Blt_Chain_FirstLink(setPtr->chain);
	iterPtr->tagName = string + 6;
	iterPtr->type = ITER_PATTERN;
    } else if ((tabPtr = GetTabByName(setPtr, string)) != NULL) {
	iterPtr->startPtr = iterPtr->endPtr = tabPtr;
    } else if ((tablePtr = GetTagTable(setPtr, string)) != NULL) {
	iterPtr->tagName = string;
	iterPtr->tablePtr = tablePtr;
	iterPtr->type = ITER_TAG;
    } else {
	if (interp != NULL) {
	    Tcl_AppendResult(interp, "can't find tab index, name, or tag \"", 
		string, "\" in \"", Tk_PathName(setPtr->tkwin), "\"", 
			     (char *)NULL);
	}
	return TCL_ERROR;
    }	
    return TCL_OK;
}

#ifdef notdef
/*
 *---------------------------------------------------------------------------
 *
 * GetTabFromObj --
 *
 *	Converts a string representing a tab index into a tab pointer.  The
 *	index may be in one of the following forms:
 *
 *	 number		Tab at position in the list of tabs.
 *	 @x,y		Tab closest to the specified X-Y screen coordinates.
 *	 "active"	Tab mouse is located over.
 *	 "focus"	Tab is the widget's focus.
 *	 "select"	Currently selected tab.
 *	 "right"	Next tab from the focus tab.
 *	 "left"		Previous tab from the focus tab.
 *	 "up"		Next tab from the focus tab.
 *	 "down"		Previous tab from the focus tab.
 *	 "end"		Last tab in list.
 *
 * Results:
 *	If the string is successfully converted, TCL_OK is returned.  The
 *	pointer to the node is returned via tabPtrPtr.  Otherwise, TCL_ERROR
 *	is returned and an error message is left in interpreter's result
 *	field.
 *
 *---------------------------------------------------------------------------
 */
static int
GetTabFromObj(Tabset *setPtr, Tcl_Obj *objPtr, Tab **tabPtrPtr, int allowNull)
{
    Tab *tabPtr;
    Blt_ChainLink link;
    int position;
    char c;
    const char *string;

    string = Tcl_GetString(objPtr);
    c = string[0];
    tabPtr = NULL;
    if (setPtr->focusPtr == NULL) {
	setPtr->focusPtr = setPtr->selectPtr;
	Blt_SetFocusItem(setPtr->bindTable, setPtr->focusPtr, NULL);
    }
    if ((isdigit(UCHAR(c))) &&
	(Tcl_GetIntFromObj(setPtr->interp, objPtr, &position) == TCL_OK)) {
	link = Blt_Chain_GetNthLink(setPtr->chain, position);
	if (link == NULL) {
	    Tcl_AppendResult(setPtr->interp, "can't find tab \"", string,
		"\" in \"", Tk_PathName(setPtr->tkwin), 
		"\": no such index", (char *)NULL);
	    return TCL_ERROR;
	}
	tabPtr = Blt_Chain_GetValue(link);
    } else if ((c == 'a') && (strcmp(string, "active") == 0)) {
	tabPtr = setPtr->activePtr;
    } else if ((c == 'c') && (strcmp(string, "current") == 0)) {
	tabPtr = (Tab *)Blt_GetCurrentItem(setPtr->bindTable);
    } else if ((c == 's') && (strcmp(string, "select") == 0)) {
	tabPtr = setPtr->selectPtr;
    } else if ((c == 'f') && (strcmp(string, "focus") == 0)) {
	tabPtr = setPtr->focusPtr;
    } else if ((c == 'u') && (strcmp(string, "up") == 0)) {
	switch (setPtr->side) {
	case SIDE_LEFT:
	case SIDE_RIGHT:
	    tabPtr = TabLeft(setPtr->focusPtr);
	    break;
	    
	case SIDE_BOTTOM:
	    tabPtr = TabDown(setPtr->focusPtr);
	    break;
	    
	case SIDE_TOP:
	    tabPtr = TabUp(setPtr->focusPtr);
	    break;
	}
    } else if ((c == 'd') && (strcmp(string, "down") == 0)) {
	switch (setPtr->side) {
	case SIDE_LEFT:
	case SIDE_RIGHT:
	    tabPtr = TabRight(setPtr->focusPtr);
	    break;
	    
	case SIDE_BOTTOM:
	    tabPtr = TabUp(setPtr->focusPtr);
	    break;
	    
	case SIDE_TOP:
	    tabPtr = TabDown(setPtr->focusPtr);
	    break;
	}
    } else if ((c == 'l') && (strcmp(string, "left") == 0)) {
	switch (setPtr->side) {
	case SIDE_LEFT:
	    tabPtr = TabUp(setPtr->focusPtr);
	    break;
	    
	case SIDE_RIGHT:
	    tabPtr = TabDown(setPtr->focusPtr);
	    break;
	    
	case SIDE_BOTTOM:
	case SIDE_TOP:
	    tabPtr = TabLeft(setPtr->focusPtr);
	    break;
	}
    } else if ((c == 'r') && (strcmp(string, "right") == 0)) {
	switch (setPtr->side) {
	case SIDE_LEFT:
	    tabPtr = TabDown(setPtr->focusPtr);
	    break;
	    
	case SIDE_RIGHT:
	    tabPtr = TabUp(setPtr->focusPtr);
	    break;
	    
	case SIDE_BOTTOM:
	case SIDE_TOP:
	    tabPtr = TabRight(setPtr->focusPtr);
	    break;
	}
    } else if ((c == 'e') && (strcmp(string, "end") == 0)) {
	tabPtr = LastTab(setPtr, 0);
    } else if (c == '@') {
	int x, y;

	if (Blt_GetXY(setPtr->interp, setPtr->tkwin, string, &x, &y) 
	    != TCL_OK) {
	    return TCL_ERROR;
	}
	tabPtr = (Tab *)PickTabProc(setPtr, x, y, NULL);
    } else {
	Blt_HashEntry *hPtr;

	hPtr = Blt_FindHashEntry(&setPtr->tabTable, string);
	if (hPtr != NULL) {
	    tabPtr = Blt_GetHashValue(hPtr);
	}
    }
    *tabPtrPtr = tabPtr;
    Tcl_ResetResult(setPtr->interp);

    if ((!allowNull) && (tabPtr == NULL)) {
	Tcl_AppendResult(setPtr->interp, "can't find tab \"", string,
	    "\" in \"", Tk_PathName(setPtr->tkwin), "\"", (char *)NULL);
	return TCL_ERROR;
    }	
    return TCL_OK;
}
#endif

static Tab *
NextOrLastTab(Tab *tabPtr)
{
    if (tabPtr->link != NULL) {
	Blt_ChainLink link;

	link = Blt_Chain_NextLink(tabPtr->link);
	if (link == NULL) {
	    link = Blt_Chain_PrevLink(tabPtr->link);
	}
	if (link != NULL) {
	    return Blt_Chain_GetValue(link);
	}
    }
    return NULL;
}

static Tab *
PreviousOrFirstTab(Tab *tabPtr)
{
    if (tabPtr->link != NULL) {
	Blt_ChainLink link;

	link = Blt_Chain_PrevLink(tabPtr->link);
	if (link == NULL) {
	    link = Blt_Chain_NextLink(tabPtr->link);
	}
	if (link != NULL) {
	    return Blt_Chain_GetValue(link);
	}
    }
    return NULL;
}

/*
 *---------------------------------------------------------------------------
 *
 * EmbeddedWidgetEventProc --
 *
 * 	This procedure is invoked by the Tk dispatcher for various events on
 * 	embedded widgets contained in the tabset.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	When an embedded widget gets deleted, internal structures get cleaned
 *	up.  When it gets resized, the tabset is redisplayed.
 *
 *---------------------------------------------------------------------------
 */
static void
EmbeddedWidgetEventProc(ClientData clientData, XEvent *eventPtr)
{
    Tab *tabPtr = clientData;

    if ((tabPtr == NULL) || (tabPtr->tkwin == NULL)) {
	return;
    }
    switch (eventPtr->type) {
    case ConfigureNotify:
	/*
	 * If the window's requested size changes, redraw the window.  But
	 * only if it's currently the selected page.
	 */
	if ((tabPtr->container == NULL) && (Tk_IsMapped(tabPtr->tkwin)) &&
	    (tabPtr->setPtr->selectPtr == tabPtr)) {
	    tabPtr->setPtr->flags |= REDRAW_ALL;
	    EventuallyRedraw(tabPtr->setPtr);
	}
	break;

    case DestroyNotify:
	/*
	 * Mark the tab as deleted by dereferencing the Tk window
	 * pointer. Redraw the window only if the tab is currently visible.
	 */
	if ((Tk_IsMapped(tabPtr->tkwin)) &&
	    (tabPtr->setPtr->selectPtr == tabPtr)) {
	    tabPtr->setPtr->flags |= REDRAW_ALL;
	    EventuallyRedraw(tabPtr->setPtr);
	}
	Tk_DeleteEventHandler(tabPtr->tkwin, StructureNotifyMask,
	    EmbeddedWidgetEventProc, tabPtr);
	tabPtr->tkwin = NULL;
	break;

    }
}

/*
 *---------------------------------------------------------------------------
 *
 * EmbeddedWidgetCustodyProc --
 *
 *	This procedure is invoked when a tab window has been stolen by another
 *	geometry manager.  The information and memory associated with the tab
 *	window is released.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Arranges for the widget formerly associated with the tab window to
 *	have its layout re-computed and arranged at the next idle point.
 *
 *---------------------------------------------------------------------------
 */
 /* ARGSUSED */
static void
EmbeddedWidgetCustodyProc(ClientData clientData, Tk_Window tkwin)
{
    Tab *tabPtr = clientData;
    Tabset *setPtr;

    if ((tabPtr == NULL) || (tabPtr->tkwin == NULL)) {
	return;
    }
    setPtr = tabPtr->setPtr;
    if (tabPtr->container != NULL) {
	Tcl_EventuallyFree(tabPtr, DestroyTearoff);
    }
    /*
     * Mark the tab as deleted by dereferencing the Tk window pointer. Redraw
     * the window only if the tab is currently visible.
     */
    if (tabPtr->tkwin != NULL) {
	if (Tk_IsMapped(tabPtr->tkwin) && (setPtr->selectPtr == tabPtr)) {
	    setPtr->flags |= (LAYOUT_PENDING | SCROLL_PENDING | REDRAW_ALL);
	    EventuallyRedraw(setPtr);
	}
	Tk_DeleteEventHandler(tabPtr->tkwin, StructureNotifyMask,
	    EmbeddedWidgetEventProc, tabPtr);
	tabPtr->tkwin = NULL;
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * EmbeddedWidgetGeometryProc --
 *
 *	This procedure is invoked by Tk_GeometryRequest for tab windows
 *	managed by the widget.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Arranges for tkwin, and all its managed siblings, to be repacked and
 *	drawn at the next idle point.
 *
 *---------------------------------------------------------------------------
 */
 /* ARGSUSED */
static void
EmbeddedWidgetGeometryProc(ClientData clientData, Tk_Window tkwin)
{
    Tab *tabPtr = clientData;

    if ((tabPtr == NULL) || (tabPtr->tkwin == NULL)) {
	fprintf(stderr, "%s: line %d \"tkwin is null\"", __FILE__, __LINE__);
	return;
    }
    tabPtr->setPtr->flags |= (LAYOUT_PENDING | SCROLL_PENDING | REDRAW_ALL);
    EventuallyRedraw(tabPtr->setPtr);
}

/*
 *---------------------------------------------------------------------------
 *
 * DestroyTab --
 *
 *---------------------------------------------------------------------------
 */
static void
DestroyTab(Tabset *setPtr, Tab *tabPtr)
{
    iconOption.clientData = setPtr;
    Blt_FreeOptions(tabSpecs, (char *)tabPtr, setPtr->display, 0);
    ClearTags(tabPtr);
    if (tabPtr->flags & TEAROFF_REDRAW) {
	Tcl_CancelIdleCall(DisplayTearoff, tabPtr);
    }
    if (tabPtr->container != NULL) {
	Tk_DestroyWindow(tabPtr->container);
    }
    if (tabPtr == setPtr->plusPtr) {
	setPtr->plusPtr = NULL;		/* Indicate that the plus tab has now
					 * been deleted. */
    }
    if (tabPtr->tkwin != NULL) {
	Tk_ManageGeometry(tabPtr->tkwin, (Tk_GeomMgr *)NULL, tabPtr);
	Tk_DeleteEventHandler(tabPtr->tkwin, StructureNotifyMask, 
		EmbeddedWidgetEventProc, tabPtr);
	if (Tk_IsMapped(tabPtr->tkwin)) {
	    Tk_UnmapWindow(tabPtr->tkwin);
	}
    }
    if (tabPtr == setPtr->activePtr) {
	setPtr->activePtr = NULL;
    }
    if (tabPtr == setPtr->selectPtr) {
	setPtr->selectPtr = PreviousOrFirstTab(tabPtr);
    }
    if (tabPtr == setPtr->focusPtr) {
	setPtr->focusPtr = setPtr->selectPtr;
	Blt_SetFocusItem(setPtr->bindTable, setPtr->focusPtr, NULL);
    }
    if (tabPtr == setPtr->startPtr) {
	setPtr->startPtr = NULL;
    }
    if (tabPtr->text != NULL) {
	Blt_Free(tabPtr->text);
    }
    if (tabPtr->textGC != NULL) {
	Tk_FreeGC(setPtr->display, tabPtr->textGC);
    }
    if (tabPtr->hashPtr != NULL) {
	Blt_DeleteHashEntry(&setPtr->tabTable, tabPtr->hashPtr);
    }
    if (tabPtr->backGC != NULL) {
	Tk_FreeGC(setPtr->display, tabPtr->backGC);
    }
    if (tabPtr->link != NULL) {
	Blt_Chain_DeleteLink(setPtr->chain, tabPtr->link);
    }
    if (tabPtr->layoutPtr != NULL) {
	Blt_Free(tabPtr->layoutPtr);
    }
    Blt_DeleteBindings(setPtr->bindTable, tabPtr);
    Blt_Free(tabPtr);
}

/*
 *---------------------------------------------------------------------------
 *
 * NewTab --
 *
 *	Creates a new tab structure.  A tab contains information about the
 *	state of the tab and its embedded window.
 *
 * Results:
 *	Returns a pointer to the new tab structure.
 *
 *---------------------------------------------------------------------------
 */
static Tab *
NewTab(Tcl_Interp *interp, Tabset *setPtr, const char *tabName)
{
    Tab *tabPtr;
    Blt_HashEntry *hPtr;
    int isNew;
    char string[200];

    if (tabName == NULL) {
	sprintf_s(string, 200, "tab%d", setPtr->nextId++);
	tabName = string;
    }
    hPtr = Blt_CreateHashEntry(&setPtr->tabTable, tabName, &isNew);
    if (!isNew) {
	if (interp != NULL) {
	    Tcl_AppendResult(interp, "a tab \"", tabName, 
		"\" already exists in \"", Tk_PathName(setPtr->tkwin), "\".",
		(char *)NULL);
	}
	return NULL;
    }
    tabPtr = Blt_AssertCalloc(1, sizeof(Tab));
    tabPtr->setPtr = setPtr;
    if (strcmp(tabName, "+") == 0) {
	setPtr->plusPtr = tabPtr;
    }
    tabPtr->text = Blt_AssertStrdup(tabName);
    tabPtr->fill = FILL_NONE;
    tabPtr->anchor = TK_ANCHOR_CENTER;
    tabPtr->container = NULL;
    tabPtr->flags = NORMAL | CLOSE_NEEDED;
    tabPtr->name = Blt_GetHashKey(&setPtr->tabTable, hPtr);
    Blt_SetHashValue(hPtr, tabPtr);
    tabPtr->hashPtr = hPtr;
    return tabPtr;
}

/*
 *---------------------------------------------------------------------------
 *
 * BackgroundChangedProc
 *
 *	Stub for image change notifications.  Since we immediately draw the
 *	image into a pixmap, we don't really care about image changes.
 *
 *	It would be better if Tk checked for NULL proc pointers.
 *
 * Results:
 *	None.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static void
BackgroundChangedProc(ClientData clientData)
{
    Tabset *setPtr = clientData;

    if (setPtr->tkwin != NULL) {
	setPtr->flags |= REDRAW_ALL;
	EventuallyRedraw(setPtr);
    }
}

static int
ConfigureTab(Tabset *setPtr, Tab *tabPtr)
{
    Blt_Background bg;
    Blt_Font font;
    GC newGC;
    XGCValues gcValues;
    unsigned long gcMask;
	
    font = GETATTR(tabPtr, font);
    newGC = NULL;
    if (tabPtr->text != NULL) {
	XColor *colorPtr;

	gcMask = GCForeground | GCFont;
	colorPtr = GETATTR(tabPtr, textColor);
	gcValues.foreground = colorPtr->pixel;
	gcValues.font = Blt_FontId(font);
	newGC = Tk_GetGC(setPtr->tkwin, gcMask, &gcValues);
    }
    if (tabPtr->textGC != NULL) {
	Tk_FreeGC(setPtr->display, tabPtr->textGC);
    }
    tabPtr->textGC = newGC;

    gcMask = GCForeground | GCStipple | GCFillStyle;
    gcValues.fill_style = FillStippled;
    bg = GETATTR(tabPtr, bg);
    gcValues.foreground = Blt_BackgroundBorderColor(bg)->pixel;
    gcValues.stipple = tabPtr->stipple;
    newGC = Tk_GetGC(setPtr->tkwin, gcMask, &gcValues);
    if (tabPtr->backGC != NULL) {
	Tk_FreeGC(setPtr->display, tabPtr->backGC);
    }
    tabPtr->backGC = newGC;

    if (tabPtr->bg != NULL) {
	Blt_SetBackgroundChangedProc(tabPtr->bg, BackgroundChangedProc, setPtr);
    }
    if (Blt_ConfigModified(tabSpecs, "-image", "-*pad*", "-state",
			   "-text", "-window*", (char *)NULL)) {
	setPtr->flags |= (LAYOUT_PENDING | SCROLL_PENDING | REDRAW_ALL);
    }
    if (tabPtr->flags & HIDE) {
	if (setPtr->selectPtr == tabPtr) {
	    setPtr->selectPtr = FirstTab(setPtr, HIDE | DISABLED);
	}
	if (setPtr->activePtr == tabPtr) {
	    setPtr->activePtr = NULL;
	}
    }
    EventuallyRedraw(setPtr);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * ConfigureButton --
 *
 * 	This procedure is called to process an objv/objc list, plus the Tk
 * 	option database, in order to configure (or reconfigure) the widget.
 *
 * Results:

 *	The return value is a standard TCL result.  If TCL_ERROR is returned,
 *	then interp->result contains an error message.
 *
 * Side Effects:
 *	Configuration information, such as text string, colors, font, etc. get
 *	set for setPtr; old resources get freed, if there were any.  The widget
 *	is redisplayed.
 *
 *---------------------------------------------------------------------------
 */
static void
DestroyButton(Tabset *setPtr, Button *butPtr)
{
    iconOption.clientData = setPtr;
    Blt_FreeOptions(buttonSpecs, (char *)butPtr, setPtr->display, 0);
    if (butPtr->active != butPtr->active0) {
	Blt_FreePicture(butPtr->active);
    }
    if (butPtr->normal != butPtr->normal0) {
	Blt_FreePicture(butPtr->normal);
    }
    if (butPtr->active0 != NULL) {
	Blt_FreePicture(butPtr->active0);
    }
    if (butPtr->normal0 != NULL) {
	Blt_FreePicture(butPtr->normal0);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * ConfigureButton --
 *
 * 	This procedure is called to process an objv/objc list, plus the Tk
 * 	option database, in order to configure (or reconfigure) the widget.
 *
 * Results:

 *	The return value is a standard TCL result.  If TCL_ERROR is returned,
 *	then interp->result contains an error message.
 *
 * Side Effects:
 *	Configuration information, such as text string, colors, font, etc. get
 *	set for setPtr; old resources get freed, if there were any.  The widget
 *	is redisplayed.
 *
 *---------------------------------------------------------------------------
 */
static int
ConfigureButton(
    Tcl_Interp *interp,			/* Interpreter to report errors. */
    Tabset *setPtr,			/* Information about widget; may or
					 * may not already have values for some
					 * fields. */
    int objc,
    Tcl_Obj *const *objv,
    int flags)
{
    Button *butPtr = &setPtr->closeButton;

    iconOption.clientData = setPtr;
    if (Blt_ConfigureWidgetFromObj(interp, setPtr->tkwin, buttonSpecs, 
	objc, objv, (char *)butPtr, flags) != TCL_OK) {
	return TCL_ERROR;
    }
    setPtr->flags |= (LAYOUT_PENDING | SCROLL_PENDING);
#ifdef notdef
    if ((setPtr->reqHeight > 0) && (setPtr->reqWidth > 0)) {
	Tk_GeometryRequest(setPtr->tkwin, setPtr->reqWidth, setPtr->reqHeight);
    }
#endif
    setPtr->flags |= REDRAW_ALL;
    EventuallyRedraw(setPtr);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * TearoffEventProc --
 *
 * 	This procedure is invoked by the Tk dispatcher for various events on
 * 	the tearoff widget.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	When the tearoff gets deleted, internal structures get cleaned up.
 *	When it gets resized or exposed, it's redisplayed.
 *
 *---------------------------------------------------------------------------
 */
static void
TearoffEventProc(ClientData clientData, XEvent *eventPtr)
{
    Tab *tabPtr = clientData;

    if ((tabPtr == NULL) || (tabPtr->tkwin == NULL) ||
	(tabPtr->container == NULL)) {
	return;
    }
    switch (eventPtr->type) {
    case Expose:
	if (eventPtr->xexpose.count == 0) {
	    EventuallyRedrawTearoff(tabPtr);
	}
	break;
    case ConfigureNotify:
	EventuallyRedrawTearoff(tabPtr);
	break;
    case DestroyNotify:
	if (tabPtr->flags & TEAROFF_REDRAW) {
	    tabPtr->flags &= ~TEAROFF_REDRAW;
	    Tcl_CancelIdleCall(DisplayTearoff, clientData);
	}
	Tk_DestroyWindow(tabPtr->container);
	tabPtr->container = NULL;
	break;
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * GetReqWidth --
 *
 *	Returns the width requested by the embedded tab window and any
 *	requested padding around it. This represents the requested width of
 *	the page.
 *
 * Results:
 *	Returns the requested width of the page.
 *
 *---------------------------------------------------------------------------
 */
static int
GetReqWidth(Tab *tabPtr)
{
    int width;
    
    if (tabPtr->reqSlaveWidth > 0) {
	width = tabPtr->reqSlaveWidth;
    } else {
	width = Tk_ReqWidth(tabPtr->tkwin);
    }
    width += PADDING(tabPtr->xPad) + 
	2 * Tk_Changes(tabPtr->tkwin)->border_width;
    if (width < 1) {
	width = 1;
    }
    return width;
}

/*
 *---------------------------------------------------------------------------
 *
 * GetReqHeight --
 *
 *	Returns the height requested by the window and padding around the
 *	window. This represents the requested height of the page.
 *
 * Results:
 *	Returns the requested height of the page.
 *
 *---------------------------------------------------------------------------
 */
static int
GetReqHeight(Tab *tabPtr)
{
    int height;

    if (tabPtr->reqSlaveHeight > 0) {
	height = tabPtr->reqSlaveHeight;
    } else {
	height = Tk_ReqHeight(tabPtr->tkwin);
    }
    height += PADDING(tabPtr->yPad) +
	2 * Tk_Changes(tabPtr->tkwin)->border_width;
    if (height < 1) {
	height = 1;
    }
    return height;
}

/*
 *---------------------------------------------------------------------------
 *
 * TranslateAnchor --
 *
 * 	Translate the coordinates of a given bounding box based upon the
 * 	anchor specified.  The anchor indicates where the given xy position
 * 	is in relation to the bounding box.
 *
 *  		nw --- n --- ne
 *  		|            |     x,y ---+
 *  		w   center   e      |     |
 *  		|            |      +-----+
 *  		sw --- s --- se
 *
 * Results:
 *	The translated coordinates of the bounding box are returned.
 *
 *---------------------------------------------------------------------------
 */
static void
TranslateAnchor(int dx, int dy, Tk_Anchor anchor, int *xPtr, int *yPtr)
{
    int x, y;

    x = y = 0;
    switch (anchor) {
    case TK_ANCHOR_NW:		/* Upper left corner */
	break;
    case TK_ANCHOR_W:		/* Left center */
	y = (dy / 2);
	break;
    case TK_ANCHOR_SW:		/* Lower left corner */
	y = dy;
	break;
    case TK_ANCHOR_N:		/* Top center */
	x = (dx / 2);
	break;
    case TK_ANCHOR_CENTER:	/* Centered */
	x = (dx / 2);
	y = (dy / 2);
	break;
    case TK_ANCHOR_S:		/* Bottom center */
	x = (dx / 2);
	y = dy;
	break;
    case TK_ANCHOR_NE:		/* Upper right corner */
	x = dx;
	break;
    case TK_ANCHOR_E:		/* Right center */
	x = dx;
	y = (dy / 2);
	break;
    case TK_ANCHOR_SE:		/* Lower right corner */
	x = dx;
	y = dy;
	break;
    }
    *xPtr = (*xPtr) + x;
    *yPtr = (*yPtr) + y;
}

static void
GetWindowRectangle(Tab *tabPtr, Tk_Window parent, int hasTearOff, 
		   XRectangle *rectPtr)
{
    int pad;
    Tabset *setPtr;
    int cavityWidth, cavityHeight;
    int width, height;
    int dx, dy;
    int x, y;

    setPtr = tabPtr->setPtr;
    pad = setPtr->inset + setPtr->inset2;

    x = y = 0; 			/* Suppress compiler warning. */
    if (!hasTearOff) {
	switch (setPtr->side) {
	case SIDE_RIGHT:
	case SIDE_BOTTOM:
	    x = setPtr->inset + setPtr->inset2;
	    y = setPtr->inset + setPtr->inset2;
	    break;

	case SIDE_LEFT:
	    x = setPtr->pageTop;
	    y = setPtr->inset + setPtr->inset2;
	    break;

	case SIDE_TOP:
	    x = setPtr->inset + setPtr->inset2;
	    y = setPtr->pageTop;
	    break;
	}

	if (setPtr->side & (SIDE_LEFT | SIDE_RIGHT)) {
	    cavityWidth = Tk_Width(setPtr->tkwin) - (setPtr->pageTop + pad);
	    cavityHeight = Tk_Height(setPtr->tkwin) - (2 * pad);
	} else {
	    cavityWidth = Tk_Width(setPtr->tkwin) - (2 * pad);
	    cavityHeight = Tk_Height(setPtr->tkwin) - (setPtr->pageTop + pad);
	}

    } else {
	x = setPtr->inset + setPtr->inset2;
#define TEAR_OFF_TAB_SIZE	5
	y = setPtr->inset + setPtr->inset2 + setPtr->outerPad + 
	    TEAR_OFF_TAB_SIZE;
	if (setPtr->nTiers == 1) {
	    y += setPtr->ySelectPad;
	}
	cavityWidth = Tk_Width(parent) - (2 * pad);
	cavityHeight = Tk_Height(parent) - (y + pad);
    }
    cavityWidth -= PADDING(tabPtr->xPad);
    cavityHeight -= PADDING(tabPtr->yPad);
    if (cavityWidth < 1) {
	cavityWidth = 1;
    }
    if (cavityHeight < 1) {
	cavityHeight = 1;
    }
    width = GetReqWidth(tabPtr);
    height = GetReqHeight(tabPtr);

    /*
     * Resize the embedded window is of the following is true:
     *
     *	1) It's been torn off.
     *  2) The -fill option (horizontal or vertical) is set.
     *  3) the window is bigger than the cavity.
     */
    if ((hasTearOff) || (cavityWidth < width) || (tabPtr->fill & FILL_X)) {
	width = cavityWidth;
    }
    if ((hasTearOff) || (cavityHeight < height) || (tabPtr->fill & FILL_Y)) {
	height = cavityHeight;
    }
    dx = (cavityWidth - width);
    dy = (cavityHeight - height);
    if ((dx > 0) || (dy > 0)) {
	TranslateAnchor(dx, dy, tabPtr->anchor, &x, &y);
    }
    /* Remember that X11 windows must be at least 1 pixel. */
    if (width < 1) {
	width = 1;
    }
    if (height < 1) {
	height = 1;
    }
    rectPtr->x = (short)(x + tabPtr->padLeft);
    rectPtr->y = (short)(y + tabPtr->padTop);
    rectPtr->width = (short)width;
    rectPtr->height = (short)height;
}

static void
ArrangeWindow(Tk_Window tkwin, XRectangle *rectPtr, int force)
{
    if ((force) ||
	(rectPtr->x != Tk_X(tkwin)) || 
	(rectPtr->y != Tk_Y(tkwin)) ||
	(rectPtr->width != Tk_Width(tkwin)) ||
	(rectPtr->height != Tk_Height(tkwin))) {
	Tk_MoveResizeWindow(tkwin, rectPtr->x, rectPtr->y, 
			    rectPtr->width, rectPtr->height);
    }
    if (!Tk_IsMapped(tkwin)) {
	Tk_MapWindow(tkwin);
    }
}


/*ARGSUSED*/
static void
GetTagsProc(Blt_BindTable table, ClientData object, ClientData context, 
	    Blt_List list)
{
    Tab *tabPtr = (Tab *)object;
    Tabset *setPtr;

    setPtr = table->clientData;
    if (context == TAB_PERFORATION) {
	Blt_List_Append(list, MakeBindTag(setPtr, "Perforation"), 0);
    } else if (context == TAB_BUTTON) {
	ClientData tag;

	Blt_List_Append(list, MakeBindTag(setPtr, "Button"), 0);
	tag = MakeBindTag(setPtr, tabPtr->name);
	Blt_List_Append(list, tag, 0);
    } else if (context == TAB_LABEL) {
	ClientData tag;

	tag = MakeBindTag(setPtr, tabPtr->name);
	Blt_List_Append(list, tag, 0);
	AppendTags(setPtr, tabPtr, list);
	Blt_List_Append(list, MakeBindTag(setPtr, "all"), 0);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * TabsetEventProc --
 *
 * 	This procedure is invoked by the Tk dispatcher for various events on
 * 	tabset widgets.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	When the window gets deleted, internal structures get cleaned up.
 *	When it gets exposed, it is redisplayed.
 *
 *---------------------------------------------------------------------------
 */
static void
TabsetEventProc(ClientData clientData, XEvent *eventPtr)
{
    Tabset *setPtr = clientData;

    switch (eventPtr->type) {
    case Expose:
	setPtr->flags |= REDRAW_ALL;
	if (eventPtr->xexpose.count == 0) {
	    EventuallyRedraw(setPtr);
	}
	break;

    case ConfigureNotify:
	setPtr->flags |= REDRAW_ALL;
	setPtr->flags |= (LAYOUT_PENDING | SCROLL_PENDING);
	EventuallyRedraw(setPtr);
	break;

    case FocusIn:
    case FocusOut:
	if (eventPtr->xfocus.detail != NotifyInferior) {
	    if (eventPtr->type == FocusIn) {
		setPtr->flags |= FOCUS;
	    } else {
		setPtr->flags &= ~FOCUS;
	    }
	    EventuallyRedraw(setPtr);
	}
	break;

    case DestroyNotify:
	if (setPtr->tkwin != NULL) {
	    setPtr->tkwin = NULL;
	    Tcl_DeleteCommandFromToken(setPtr->interp, setPtr->cmdToken);
	}
	if (setPtr->flags & REDRAW_PENDING) {
	    Tcl_CancelIdleCall(DisplayTabset, setPtr);
	}
	Tcl_EventuallyFree(setPtr, DestroyTabset);
	break;

    }
}

/*
 *---------------------------------------------------------------------------
 *
 * DestroyTabset --
 *
 * 	This procedure is invoked by Tcl_EventuallyFree or Tcl_Release to
 * 	clean up the internal structure of the widget at a safe time (when
 * 	no-one is using it anymore).
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Everything associated with the widget is freed up.
 *
 *---------------------------------------------------------------------------
 */
static void
DestroyTabset(DestroyData dataPtr)
{
    Tabset *setPtr = (Tabset *)dataPtr;
    Tab *tabPtr;
    Blt_ChainLink link, next;

    if (setPtr->flags & REDRAW_PENDING) {
	Tcl_CancelIdleCall(DisplayTabset, setPtr);
    }
    iconOption.clientData = setPtr;
    Blt_FreeOptions(configSpecs, (char *)setPtr, setPtr->display, 0);
    if (setPtr->highlightGC != NULL) {
	Tk_FreeGC(setPtr->display, setPtr->highlightGC);
    }
    if (setPtr->defStyle.activeGC != NULL) {
	Blt_FreePrivateGC(setPtr->display, setPtr->defStyle.activeGC);
    }
    if (setPtr->painter != NULL) {
	Blt_FreePainter(setPtr->painter);
    }
    for (link = Blt_Chain_FirstLink(setPtr->chain); link != NULL; link = next) {
	next = Blt_Chain_NextLink(link);
	tabPtr = Blt_Chain_GetValue(link);
	tabPtr->link = NULL;
	tabPtr->hashPtr = NULL;
	DestroyTab(setPtr, tabPtr);
    }
    DestroyTags(setPtr);
    DestroyButton(setPtr, &setPtr->closeButton);
    Blt_Chain_Destroy(setPtr->chain);
    Blt_DestroyBindingTable(setPtr->bindTable);
    Blt_DeleteHashTable(&setPtr->iconTable);
    Blt_DeleteHashTable(&setPtr->tagTable);
    Blt_DeleteHashTable(&setPtr->bindTagTable);
    Blt_Free(setPtr);
}

/*
 *---------------------------------------------------------------------------
 *
 * NewTabset --
 *
 *---------------------------------------------------------------------------
 */
static Tabset *
NewTabset(Tcl_Interp *interp, Tk_Window tkwin)
{
    Tabset *setPtr;

    setPtr = Blt_AssertCalloc(1, sizeof(Tabset));
    Tk_SetClass(tkwin, "Tabset");
    setPtr->borderWidth = setPtr->highlightWidth = 0;
    setPtr->corner = CORNER_OFFSET;
    setPtr->defStyle.borderWidth = 1;
    setPtr->defStyle.relief = TK_RELIEF_RAISED;
    setPtr->iconPos = SIDE_LEFT;
    setPtr->angle = 0.0f;
    setPtr->justify = TK_JUSTIFY_CENTER;
    setPtr->reqTabWidth = TABWIDTH_SAME;
    setPtr->reqTiers = 1;
    setPtr->reqSlant = SLANT_NONE;
    setPtr->display = Tk_Display(tkwin);
    setPtr->flags |= LAYOUT_PENDING | SCROLL_PENDING;
    setPtr->gap = GAP;
    setPtr->interp = interp;
    setPtr->relief = TK_RELIEF_FLAT;
    setPtr->scrollUnits = 2;
    setPtr->side = SIDE_TOP;
    setPtr->tkwin = tkwin;
    setPtr->closeButton.borderWidth = 0;
    setPtr->xSelectPad = SELECT_PADX;
    setPtr->ySelectPad = SELECT_PADY;
    setPtr->bindTable = Blt_CreateBindingTable(interp, tkwin, setPtr, 
	PickTabProc, GetTagsProc);
    setPtr->chain = Blt_Chain_Create();
    Blt_InitHashTable(&setPtr->tabTable, BLT_STRING_KEYS);
    Blt_InitHashTable(&setPtr->iconTable, BLT_STRING_KEYS);
    Blt_InitHashTable(&setPtr->tagTable, BLT_STRING_KEYS);
    Blt_InitHashTable(&setPtr->bindTagTable, BLT_STRING_KEYS);
    Blt_SetWindowInstanceData(tkwin, setPtr);
    return setPtr;
}

/*
 *---------------------------------------------------------------------------
 *
 * ConfigureTabset --
 *
 * 	This procedure is called to process an objv/objc list, plus the Tk
 * 	option database, in order to configure (or reconfigure) the widget.
 *
 * Results:

 *	The return value is a standard TCL result.  If TCL_ERROR is returned,
 *	then interp->result contains an error message.
 *
 * Side Effects:
 *	Configuration information, such as text string, colors, font, etc. get
 *	set for setPtr; old resources get freed, if there were any.  The widget
 *	is redisplayed.
 *
 *---------------------------------------------------------------------------
 */
static int
ConfigureTabset(
    Tcl_Interp *interp,		/* Interpreter to report errors. */
    Tabset *setPtr,		/* Information about widget; may or may not
			         * already have values for some fields. */
    int objc,
    Tcl_Obj *const *objv,
    int flags)
{
    XGCValues gcValues;
    unsigned long gcMask;
    GC newGC;
    int slantLeft, slantRight;

    iconOption.clientData = setPtr;
    if (Blt_ConfigureWidgetFromObj(interp, setPtr->tkwin, configSpecs, 
	   objc, objv, (char *)setPtr, flags) != TCL_OK) {
	return TCL_ERROR;
    }
    if (Blt_ConfigModified(configSpecs, "-width", "-height", "-side", "-gap",
	"-slant", "-iconposition", "-rotate", "-tiers", "-tabwidth", 
	"-scrolltabs", "-showsingletab", "-closebutton", "-justify",
	"-iconposition", (char *)NULL)) {
	setPtr->flags |= (LAYOUT_PENDING | SCROLL_PENDING);
    }
    if ((setPtr->reqHeight > 0) && (setPtr->reqWidth > 0)) {
	Tk_GeometryRequest(setPtr->tkwin, setPtr->reqWidth, 
		setPtr->reqHeight);
    }
    /*
     * GC for focus highlight.
     */
    gcMask = GCForeground;
    gcValues.foreground = setPtr->highlightColor->pixel;
    newGC = Tk_GetGC(setPtr->tkwin, gcMask, &gcValues);
    if (setPtr->highlightGC != NULL) {
	Tk_FreeGC(setPtr->display, setPtr->highlightGC);
    }
    setPtr->highlightGC = newGC;

    if (setPtr->bg != NULL) {
	Blt_SetBackgroundChangedProc(setPtr->bg, BackgroundChangedProc, setPtr);
    }
    /*
     * GC for active line.
     */
    gcMask = GCForeground | GCLineWidth | GCLineStyle | GCCapStyle;
    gcValues.foreground = setPtr->defStyle.textColor->pixel;
    gcValues.line_width = 0;
    gcValues.cap_style = CapProjecting;
    gcValues.line_style = (LineIsDashed(setPtr->defStyle.dashes))
	? LineOnOffDash : LineSolid;

    newGC = Blt_GetPrivateGC(setPtr->tkwin, gcMask, &gcValues);
    if (LineIsDashed(setPtr->defStyle.dashes)) {
	setPtr->defStyle.dashes.offset = 2;
	Blt_SetDashes(setPtr->display, newGC, &setPtr->defStyle.dashes);
    }
    if (setPtr->defStyle.activeGC != NULL) {
	Blt_FreePrivateGC(setPtr->display, setPtr->defStyle.activeGC);
    }
    setPtr->defStyle.activeGC = newGC;

    setPtr->angle = FMOD(setPtr->angle, 360.0);
    if (setPtr->angle < 0.0) {
	setPtr->angle += 360.0;
    }
    setPtr->quad = (int)(setPtr->angle / 90.0);
    setPtr->inset = setPtr->highlightWidth + setPtr->borderWidth + 
	setPtr->outerPad;
#ifndef notdef
    if (Blt_ConfigModified(configSpecs, "-font", "-*foreground", "-rotate",
		"-*background", "-side", "-iconposition", "-tiers", "-tabwidth",
		(char *)NULL)) {
	Tab *tabPtr;

	for (tabPtr = FirstTab(setPtr, 0); tabPtr != NULL;
	     tabPtr = NextTab(tabPtr, 0)) {
	    ConfigureTab(setPtr, tabPtr);
	}
	setPtr->flags |= (LAYOUT_PENDING | SCROLL_PENDING | REDRAW_ALL);
    }
#endif
    /* Swap slant flags if side is left. */
    slantLeft = slantRight = FALSE;
    if (setPtr->reqSlant & SLANT_LEFT) {
	slantLeft = TRUE;
    }
    if (setPtr->reqSlant & SLANT_RIGHT) {
	slantRight = TRUE;
    }
    if (setPtr->side & SIDE_LEFT) {
	SWAP(slantLeft, slantRight);
    }
    setPtr->flags &= ~SLANT_BOTH;
    if (slantLeft) {
	setPtr->flags |= SLANT_LEFT;
    }
    if (slantRight) {
	setPtr->flags |= SLANT_RIGHT;
    }
    setPtr->inset2 = setPtr->defStyle.borderWidth + setPtr->corner;
    EventuallyRedraw(setPtr);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * Tabset operations
 *
 *---------------------------------------------------------------------------
 */
/*
 *---------------------------------------------------------------------------
 *
 * ActivateOp --
 *
 *	Selects the tab to appear active.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ActivateOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tab *tabPtr;
    const char *string;

    string = Tcl_GetString(objv[2]);
    if (string[0] == '\0') {
	tabPtr = NULL;
    } else if (GetTabFromObj(interp, setPtr, objv[2], &tabPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if ((tabPtr != NULL) && (tabPtr->flags & (HIDE|DISABLED))) {
	tabPtr = NULL;
    }
    if (tabPtr != setPtr->activePtr) {
	setPtr->activePtr = tabPtr;
	EventuallyRedraw(setPtr);
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * AddOp --
 *
 *	Adds a new tab to the tabset widget.  The tab is automatically
 *	placed on the end of the tab list.
 *
 *	.t add ?label? ?option-value...?
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
AddOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tab *tabPtr;
    const char *string;

    string = NULL;
    if (objc > 2) {
	const char *name;

	name = Tcl_GetString(objv[2]);
	if (name[0] != '-') {
	    string = name;
	    objc--, objv++;
	}
    } 
    tabPtr = NewTab(interp, setPtr, string);
    if (tabPtr == NULL) {
	return TCL_ERROR;
    }
    iconOption.clientData = setPtr;
    if (Blt_ConfigureComponentFromObj(interp, setPtr->tkwin, tabPtr->name, 
	"Tab", tabSpecs, objc-2, objv+2, (char *)tabPtr, 0) != TCL_OK) {
	DestroyTab(setPtr, tabPtr);
	return TCL_ERROR;
    }
    if (ConfigureTab(setPtr, tabPtr) != TCL_OK) {
	DestroyTab(setPtr, tabPtr);
	return TCL_ERROR;
    }
    tabPtr->link = Blt_Chain_Append(setPtr->chain, tabPtr);
    if (setPtr->plusPtr != NULL) {
	Blt_ChainLink link;

	/* Move plus tab to the end. */
	link = setPtr->plusPtr->link;
	Blt_Chain_UnlinkLink(setPtr->chain, link);
	Blt_Chain_AppendLink(setPtr->chain, link);
    }
    ReindexTabs(setPtr);
    setPtr->flags |= (LAYOUT_PENDING | SCROLL_PENDING | REDRAW_ALL);
    EventuallyRedraw(setPtr);
    Tcl_SetStringObj(Tcl_GetObjResult(interp), tabPtr->name, -1);
    return TCL_OK;

}

/*
 *---------------------------------------------------------------------------
 *
 * BindOp --
 *
 *	  .t bind index sequence command
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
BindOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    ClientData tag;

    if (objc == 2) {
	Blt_HashEntry *hPtr;
	Blt_HashSearch cursor;
	Tcl_Obj *listObjPtr, *objPtr;

	listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
	for (hPtr = Blt_FirstHashEntry(&setPtr->tagTable, &cursor);
	    hPtr != NULL; hPtr = Blt_NextHashEntry(&cursor)) {
	    objPtr = Blt_GetHashValue(hPtr);
	    Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	}
	Tcl_SetObjResult(interp, listObjPtr);
	return TCL_OK;
    }
    tag = MakeBindTag(setPtr, Tcl_GetString(objv[2]));
    return Blt_ConfigureBindingsFromObj(interp, setPtr->bindTable, tag, 
	objc - 3, objv + 3);
}

/*
 *---------------------------------------------------------------------------
 *
 * ButtonActivateOp --
 *
 * 	This procedure is called to highlight the button.
 *
 *	  .h button activate tab 
 *
 * Results:
 *	A standard TCL result.  If TCL_ERROR is returned, then interp->result
 *	contains an error message.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ButtonActivateOp(Tabset *setPtr, Tcl_Interp *interp, int objc, 
		 Tcl_Obj *const *objv)
{
    Tab *tabPtr;
    const char *string;

    string = Tcl_GetString(objv[3]);
    if (string[0] == '\0') {
	tabPtr = NULL;
    } else if (GetTabFromObj(interp, setPtr, objv[3], &tabPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if ((tabPtr != NULL) && (tabPtr->flags & (HIDE|DISABLED))) {
	tabPtr = NULL;
    }
    if (tabPtr != setPtr->activeButtonPtr) {
	setPtr->activeButtonPtr = tabPtr;
	EventuallyRedraw(setPtr);
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * ButtonCgetOp --
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ButtonCgetOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    iconOption.clientData = setPtr;
    return Blt_ConfigureValueFromObj(interp, setPtr->tkwin, buttonSpecs,
	(char *)&setPtr->closeButton, objv[2], 0);
}

/*
 *---------------------------------------------------------------------------
 *
 * ButtonConfigureOp --
 *
 * 	This procedure is called to process an objv/objc list, plus the Tk
 * 	option database, in order to configure (or reconfigure) the widget.
 *
 * Results:
 *	A standard TCL result.  If TCL_ERROR is returned, then interp->result
 *	contains an error message.
 *
 * Side Effects:
 *	Configuration information, such as text string, colors, font, etc. get
 *	set for setPtr; old resources get freed, if there were any.  The widget
 *	is redisplayed.
 *
 *---------------------------------------------------------------------------
 */
static int
ButtonConfigureOp(Tabset *setPtr, Tcl_Interp *interp, int objc, 
		  Tcl_Obj *const *objv)
{
    iconOption.clientData = setPtr;
    if (objc == 2) {
	return Blt_ConfigureInfoFromObj(interp, setPtr->tkwin, buttonSpecs,
	    (char *)&setPtr->closeButton, (Tcl_Obj *)NULL, 0);
    } else if (objc == 3) {
	return Blt_ConfigureInfoFromObj(interp, setPtr->tkwin, buttonSpecs,
	    (char *)&setPtr->closeButton, objv[2], 0);
    }
    if (ConfigureButton(interp, setPtr, objc - 3, objv + 3, 
			BLT_CONFIG_OBJV_ONLY) != TCL_OK) {
	return TCL_ERROR;
    }
    setPtr->flags |= REDRAW_ALL;
    EventuallyRedraw(setPtr);
    return TCL_OK;
}


/*
 *---------------------------------------------------------------------------
 *
 * ButtonOp --
 *
 *	This procedure handles tab operations.
 *
 * Results:
 *	A standard TCL result.
 *
 *---------------------------------------------------------------------------
 */
static Blt_OpSpec buttonOps[] =
{
    {"activate",  1, ButtonActivateOp,  4, 4, "tab" }, 
    {"cget",      2, ButtonCgetOp,      4, 4, "option",},
    {"configure", 2, ButtonConfigureOp, 3, 0, "?option value?...",},
};
static int nButtonOps = sizeof(buttonOps) / sizeof(Blt_OpSpec);

static int
ButtonOp(Tabset *setPtr, Tcl_Interp *interp, int objc, 
	      Tcl_Obj *const *objv)
{
    TabsetCmdProc *proc;
    int result;

    proc = Blt_GetOpFromObj(interp, nButtonOps, buttonOps, 
	BLT_OP_ARG2, objc, objv, 0);
    if (proc == NULL) {
	return TCL_ERROR;
    }
    result = (*proc) (setPtr, interp, objc, objv);
    return result;
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
CgetOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    iconOption.clientData = setPtr;
    return Blt_ConfigureValueFromObj(interp, setPtr->tkwin, configSpecs,
	(char *)setPtr, objv[2], 0);
}

/*
 *---------------------------------------------------------------------------
 *
 * CloseOp --
 *
 * 	Invokes a TCL command when a tab is closed.
 *
 *	  .t close tab
 *
 * Results:
 *	A standard TCL result.  If TCL_ERROR is returned, then
 *	interp->result contains an error message.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
CloseOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tab *tabPtr;
    Tcl_Obj *cmdObjPtr;

    if (GetTabFromObj(interp, setPtr, objv[2], &tabPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if ((tabPtr != NULL) && (tabPtr->flags & (HIDE|DISABLED))) {
	return TCL_OK;
    }
    cmdObjPtr = (tabPtr->closeObjPtr == NULL) 
	? setPtr->closeObjPtr : tabPtr->closeObjPtr;
    if (cmdObjPtr != NULL) {
	int result;

	cmdObjPtr = Tcl_DuplicateObj(cmdObjPtr);
	Tcl_ListObjAppendElement(interp, cmdObjPtr, 
		Tcl_NewIntObj(tabPtr->index));
	Tcl_IncrRefCount(cmdObjPtr);
	result = Tcl_EvalObjEx(interp, cmdObjPtr, TCL_EVAL_GLOBAL);
	Tcl_DecrRefCount(cmdObjPtr);
	return result;
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * ConfigureOp --
 *
 * 	This procedure is called to process an objv/objc list, plus the Tk
 * 	option database, in order to configure (or reconfigure) the widget.
 *
 * Results:
 *	A standard TCL result.  If TCL_ERROR is returned, then interp->result
 *	contains an error message.
 *
 * Side Effects:
 *	Configuration information, such as text string, colors, font, etc. get
 *	set for setPtr; old resources get freed, if there were any.  The widget
 *	is redisplayed.
 *
 *---------------------------------------------------------------------------
 */
static int
ConfigureOp(Tabset *setPtr, Tcl_Interp *interp, int objc, 
	    Tcl_Obj *const *objv)
{
    iconOption.clientData = setPtr;
    if (objc == 2) {
	return Blt_ConfigureInfoFromObj(interp, setPtr->tkwin, configSpecs,
	    (char *)setPtr, (Tcl_Obj *)NULL, 0);
    } else if (objc == 3) {
	return Blt_ConfigureInfoFromObj(interp, setPtr->tkwin, configSpecs,
	    (char *)setPtr, objv[2], 0);
    }
    if (ConfigureTabset(interp, setPtr, objc - 2, objv + 2,
	    BLT_CONFIG_OBJV_ONLY) != TCL_OK) {
	return TCL_ERROR;
    }
    setPtr->flags |= REDRAW_ALL;
    EventuallyRedraw(setPtr);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * DeleteOp --
 *
 *	Deletes tab from the set. Deletes either a range of tabs or a single
 *	node.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
DeleteOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Blt_HashTable delTable;
    int i;

    Blt_InitHashTable(&delTable, BLT_ONE_WORD_KEYS);
    for (i = 2; i < objc; i++) {
	TabIterator iter;
	Tab *tabPtr;

	if (GetTabIterator(interp, setPtr, objv[i], &iter) != TCL_OK) {
	    return TCL_ERROR;
	}
	for (tabPtr = FirstTaggedTab(&iter); tabPtr != NULL; 
	     tabPtr = NextTaggedTab(&iter)) {
	    Blt_HashEntry *hPtr;
	    int isNew;

	    hPtr = Blt_CreateHashEntry(&delTable, tabPtr, &isNew);
	    Blt_SetHashValue(hPtr, tabPtr);
	}
    }
    if (delTable.numEntries > 0) {
	Blt_HashSearch iter;
	Blt_HashEntry *hPtr;

	for (hPtr = Blt_FirstHashEntry(&delTable, &iter); hPtr != NULL;
	     hPtr = Blt_NextHashEntry(&iter)) {
	    Tab *tabPtr;

	    tabPtr = Blt_GetHashValue(hPtr);
	    DestroyTab(setPtr, tabPtr);
	}
	ReindexTabs(setPtr);
	setPtr->flags |= (LAYOUT_PENDING | SCROLL_PENDING | REDRAW_ALL);
	EventuallyRedraw(setPtr);
    }
    Blt_DeleteHashTable(&delTable);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * DockallOp --
 *
 *	  .h dockall
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
DockallOp(Tabset *bookPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Blt_ChainLink link;

    for (link = Blt_Chain_FirstLink(bookPtr->chain); link != NULL;
	 link = Blt_Chain_NextLink(link)) {
	Tab *tabPtr;

	tabPtr = Blt_Chain_GetValue(link);
	if (tabPtr->container != NULL) {
	    Tcl_EventuallyFree(tabPtr, DestroyTearoff);
	}
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * IndexOp --
 *
 *	Converts a string representing a tab index.
 *
 * Results:
 *	A standard TCL result.  Interp->result will contain the identifier of
 *	each index found. If an index could not be found, then the serial
 *	identifier will be the empty string.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ExistsOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tab *tabPtr;
    int state;

    state = FALSE;
    if (GetTabFromObj(NULL, setPtr, objv[2], &tabPtr) == TCL_OK) {
	if (tabPtr != NULL) {
	    state = TRUE;
	}
    }
    Tcl_SetBooleanObj(Tcl_GetObjResult(interp), state);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * ExtentsOp --
 *
 *	Returns the extents of the tab in root coordinates.  
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ExtentsOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tab *tabPtr;

    if (GetTabFromObj(interp, setPtr, objv[2], &tabPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if (tabPtr == NULL) {
	Tcl_AppendResult(interp, "can't find a tab \"", 
		Tcl_GetString(objv[2]), "\" in \"", Tk_PathName(setPtr->tkwin), 
		"\"", (char *)NULL);
	return TCL_ERROR;
    }
    if (tabPtr->flags & ONSCREEN) {
	Tcl_Obj *listObjPtr, *objPtr;
	int rootX, rootY;
	
	listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
	Tk_GetRootCoords(setPtr->tkwin, &rootX, &rootY);
	objPtr = Tcl_NewIntObj(tabPtr->screenX + rootX);
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	objPtr = Tcl_NewIntObj(tabPtr->screenY + rootY);
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	objPtr = Tcl_NewIntObj(tabPtr->screenX + rootX + tabPtr->screenWidth);
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	objPtr = Tcl_NewIntObj(tabPtr->screenY + rootY + tabPtr->screenHeight);
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	Tcl_SetObjResult(interp, listObjPtr);
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * FocusOp --
 *
 *	Sets focus on the specified tab.  A dotted outline will be drawn
 *	around this tab.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
FocusOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tab *tabPtr;
    long index;

    if (objc == 3) {
	if (GetTabFromObj(interp, setPtr, objv[2], &tabPtr) != TCL_OK) {
	    return TCL_ERROR;
	}
	if ((tabPtr != NULL) && ((tabPtr->flags & (DISABLED|HIDE)) == 0)) {
	    setPtr->focusPtr = tabPtr;
	    Blt_SetFocusItem(setPtr->bindTable, setPtr->focusPtr, NULL);
	    EventuallyRedraw(setPtr);
	}
    }
    index = -1;
    if (setPtr->focusPtr != NULL) {
	index = setPtr->focusPtr->index;
    }
    Tcl_SetLongObj(Tcl_GetObjResult(interp), index);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * IndexOp --
 *
 *	Converts a string representing a tab index.
 *
 * Results:
 *	A standard TCL result.  Interp->result will contain the identifier of
 *	each index found. If an index could not be found, then the serial
 *	identifier will be the empty string.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
IndexOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tab *tabPtr;
    int index;

    index = -1;
    if (GetTabFromObj(NULL, setPtr, objv[2], &tabPtr) == TCL_OK) {
	if (tabPtr != NULL) {
	    index = tabPtr->index;
	}
    }
    Tcl_SetIntObj(Tcl_GetObjResult(interp), index);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * IdOp --
 *
 *	Converts a tab index into the tab identifier.
 *
 * Results:
 *	A standard TCL result.  Interp->result will contain the identifier of
 *	each index found. If an index could not be found, then the serial
 *	identifier will be the empty string.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
IdOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tab *tabPtr;

    if (GetTabFromObj(interp, setPtr, objv[2], &tabPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if (tabPtr == NULL) {
	Tcl_AppendResult(interp, "can't find a tab \"", 
		Tcl_GetString(objv[2]), "\" in \"", Tk_PathName(setPtr->tkwin), 
		"\"", (char *)NULL);
	return TCL_ERROR;
    }
    Tcl_SetStringObj(Tcl_GetObjResult(interp), tabPtr->name, -1);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * InsertOp --
 *
 *	Add new entries into a tab set.
 *
 *	.t insert position ?label? option-value label option-value...
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
InsertOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tab *tabPtr;
    Blt_ChainLink link, before;
    char c;
    const char *string;

    string = Tcl_GetString(objv[2]);
    c = string[0];
    if ((c == 'e') && (strcmp(string, "end") == 0)) {
	before = NULL;
    } else if (isdigit(UCHAR(c))) {
	int pos;

	if (Tcl_GetIntFromObj(interp, objv[2], &pos) != TCL_OK) {
	    return TCL_ERROR;
	}
	if (pos < 0) {
	    before = Blt_Chain_FirstLink(setPtr->chain);
	} else if (pos > Blt_Chain_GetLength(setPtr->chain)) {
	    before = NULL;
	} else {
	    before = Blt_Chain_GetNthLink(setPtr->chain, pos);
	}
    } else {
	Tab *beforePtr;

	if (GetTabFromObj(interp, setPtr, objv[2], &beforePtr) != TCL_OK) {
	    return TCL_ERROR;
	}
	if (beforePtr == NULL) {
	    Tcl_AppendResult(interp, "can't find a tab \"", 
		Tcl_GetString(objv[2]), "\" in \"", Tk_PathName(setPtr->tkwin), 
		"\"", (char *)NULL);
	    return TCL_ERROR;
	}
	before = beforePtr->link;
    }
    string = NULL;
    if (objc > 3) {
	const char *name;

	name = Tcl_GetString(objv[3]);
	if (name[0] != '-') {
	    string = name;
	    objc--, objv++;
	}
    } 
    tabPtr = NewTab(interp, setPtr, string);
    if (tabPtr == NULL) {
	return TCL_ERROR;
    }
    setPtr->flags |= (LAYOUT_PENDING | SCROLL_PENDING | REDRAW_ALL);
    EventuallyRedraw(setPtr);
    iconOption.clientData = setPtr;
    if (Blt_ConfigureComponentFromObj(interp, setPtr->tkwin, tabPtr->name, "Tab",
	tabSpecs, objc - 3, objv + 3, (char *)tabPtr, 0) != TCL_OK) {
	DestroyTab(setPtr, tabPtr);
	return TCL_ERROR;
    }
    if (ConfigureTab(setPtr, tabPtr) != TCL_OK) {
	DestroyTab(setPtr, tabPtr);
	return TCL_ERROR;
    }
    link = Blt_Chain_NewLink();
    if (before != NULL) {
	Blt_Chain_LinkBefore(setPtr->chain, link, before);
    } else {
	Blt_Chain_AppendLink(setPtr->chain, link);
    }
    tabPtr->link = link;
    Blt_Chain_SetValue(link, tabPtr);
    if (setPtr->plusPtr != NULL) {
	/* Move plus tab to the end. */
	link = setPtr->plusPtr->link;
	Blt_Chain_UnlinkLink(setPtr->chain, link);
	Blt_Chain_AppendLink(setPtr->chain, link);
    }
    ReindexTabs(setPtr);
    Tcl_SetStringObj(Tcl_GetObjResult(interp), tabPtr->name, -1);
    return TCL_OK;

}

/*
 *---------------------------------------------------------------------------
 *
 * InvokeOp --
 *
 * 	This procedure is called to invoke a selection command.
 *
 *	  .h invoke index
 *
 * Results:
 *	A standard TCL result.  If TCL_ERROR is returned, then interp->result
 *	contains an error message.
 *
 * Side Effects:
 *	Configuration information, such as text string, colors, font, etc. get
 *	set; old resources get freed, if there were any.  The widget is
 *	redisplayed if needed.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
InvokeOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tab *tabPtr;
    Tcl_Obj *cmdObjPtr;

    if (GetTabFromObj(interp, setPtr, objv[2], &tabPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if ((tabPtr == NULL) || (tabPtr->flags & (DISABLED|HIDE))) {
	return TCL_OK;
    }
    cmdObjPtr = GETATTR(tabPtr, cmdObjPtr);
    if (cmdObjPtr != NULL) {
	Tcl_Obj **args;
	Tcl_Obj **cmdv;
	int cmdc;
	int i;
	int result;

	if (Tcl_ListObjGetElements(interp, cmdObjPtr, &cmdc, &cmdv) != TCL_OK) {
	    return TCL_ERROR;
	}
	args = Blt_AssertMalloc(sizeof(Tcl_Obj *) * (cmdc + 1));
	for (i = 0; i < cmdc; i++) {
	    args[i] = cmdv[i];
	}
	args[i] = Tcl_NewIntObj(tabPtr->index);
	result = Blt_GlobalEvalObjv(interp, cmdc + 1, args);
	Blt_Free(args);
	if (result != TCL_OK) {
	    return TCL_ERROR;
	}
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * MoveOp --
 *
 *	Moves a tab to a new location.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
MoveOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tab *tabPtr, *fromPtr;
    char c;
    const char *string;
    int isBefore;
    int length;

    if (GetTabFromObj(interp, setPtr, objv[2], &tabPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if ((tabPtr == NULL) || (tabPtr->flags & DISABLED)) {
	return TCL_OK;
    }
    string = Tcl_GetStringFromObj(objv[3], &length);
    c = string[0];
    if ((c == 'b') && (strncmp(string, "before", length) == 0)) {
	isBefore = TRUE;
    } else if ((c == 'a') && (strncmp(string, "after", length) == 0)) {
	isBefore = FALSE;
    } else {
	Tcl_AppendResult(interp, "bad key word \"", string,
	    "\": should be \"after\" or \"before\"", (char *)NULL);
	return TCL_ERROR;
    }
    if (GetTabFromObj(interp, setPtr, objv[4], &fromPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if (fromPtr == NULL) {
	Tcl_AppendResult(interp, "can't find a tab \"", 
		Tcl_GetString(objv[4]), "\" in \"", Tk_PathName(setPtr->tkwin), 
		"\"", (char *)NULL);
	return TCL_ERROR;
    }
    if (tabPtr == fromPtr) {
	return TCL_OK;
    }
    Blt_Chain_UnlinkLink(setPtr->chain, tabPtr->link);
    if (isBefore) {
	Blt_Chain_LinkBefore(setPtr->chain, tabPtr->link, fromPtr->link);
    } else {
	Blt_Chain_LinkAfter(setPtr->chain, tabPtr->link, fromPtr->link);
    }
    setPtr->flags |= (LAYOUT_PENDING | SCROLL_PENDING | REDRAW_ALL);
    EventuallyRedraw(setPtr);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * NamesOp --
 *
 *	  .h names pattern
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
NamesOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)	
{
    Tcl_Obj *listObjPtr;

    listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
    if (objc == 2) {
	Tab *tabPtr;

	for (tabPtr = FirstTab(setPtr, 0); tabPtr != NULL;
	     tabPtr = NextTab(tabPtr, 0)) {
	    Tcl_Obj *objPtr;
	    
	    objPtr = Tcl_NewStringObj(tabPtr->name, -1);
	    Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	}
    } else {
	Tab *tabPtr;

	for (tabPtr = FirstTab(setPtr, 0); tabPtr != NULL;
	     tabPtr = NextTab(tabPtr, 0)) {
	    int i;

	    for (i = 2; i < objc; i++) {
		if (Tcl_StringMatch(tabPtr->name, Tcl_GetString(objv[i]))) {
		    Tcl_Obj *objPtr;

		    objPtr = Tcl_NewStringObj(tabPtr->name, -1);
		    Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
		    break;
		}
	    }
	}
    }
    Tcl_SetObjResult(interp, listObjPtr);
    return TCL_OK;
}

/*ARGSUSED*/
static int
NearestOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    int x, y;			/* Screen coordinates of the test point. */
    Tab *tabPtr;

    if ((Tk_GetPixelsFromObj(interp, setPtr->tkwin, objv[2], &x) != TCL_OK) ||
	(Tk_GetPixelsFromObj(interp, setPtr->tkwin, objv[3], &y) != TCL_OK)) {
	return TCL_ERROR;
    }
    if (setPtr->nVisible > 0) {
	tabPtr = (Tab *)PickTabProc(setPtr, x, y, NULL);
	if ((tabPtr != NULL) && ((tabPtr->flags & DISABLED) == 0)) {
	    Tcl_SetStringObj(Tcl_GetObjResult(interp), tabPtr->name, -1);
	}
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * SelectOp --
 *
 * 	This procedure is called to select a tab.
 *
 *	  .h select index
 *
 * Results:
 *	A standard TCL result.  If TCL_ERROR is returned, then
 *	interp->result contains an error message.
 *
 * Side Effects:
 *	Configuration information, such as text string, colors, font,
 * 	etc. get set;  old resources get freed, if there were any.
 * 	The widget is redisplayed if needed.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
SelectOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tab *tabPtr;

    if (GetTabFromObj(interp, setPtr, objv[2], &tabPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if ((tabPtr == NULL) || (tabPtr->flags & (HIDE|DISABLED))) {
	return TCL_OK;
    }
    if ((setPtr->selectPtr != NULL) && (setPtr->selectPtr != tabPtr) &&
	(setPtr->selectPtr->tkwin != NULL)) {
	if (setPtr->selectPtr->container == NULL) {
	    if (Tk_IsMapped(setPtr->selectPtr->tkwin)) {
		Tk_UnmapWindow(setPtr->selectPtr->tkwin);
	    }
	} else {
	    /* Redraw now unselected container. */
	    EventuallyRedrawTearoff(setPtr->selectPtr);
	}
    }
    setPtr->selectPtr = tabPtr;
    if ((setPtr->nTiers > 1) && (tabPtr->tier != setPtr->startPtr->tier)) {
	RenumberTiers(setPtr, tabPtr);
	Blt_PickCurrentItem(setPtr->bindTable);
    }
    setPtr->flags |= SCROLL_PENDING;
    if (tabPtr->container != NULL) {
	EventuallyRedrawTearoff(tabPtr);
    }
    EventuallyRedraw(setPtr);
    return TCL_OK;
}

static int
ViewOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    int width;

    width = VPORTWIDTH(setPtr);
    if (objc == 2) {
	double fract;
	Tcl_Obj *listObjPtr, *objPtr;

	/* Report first and last fractions */
	listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
	/*
	 * Note: we are bounding the fractions between 0.0 and 1.0 to support
	 * the "canvas"-style of scrolling.
	 */
	fract = (double)setPtr->scrollOffset / setPtr->worldWidth;
	objPtr = Tcl_NewDoubleObj(FCLAMP(fract));
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	fract = (double)(setPtr->scrollOffset + width) / setPtr->worldWidth;
	objPtr = Tcl_NewDoubleObj(FCLAMP(fract));
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	Tcl_SetObjResult(interp, listObjPtr);
	return TCL_OK;
    }
    if (Blt_GetScrollInfoFromObj(interp, objc - 2, objv + 2, 
		&setPtr->scrollOffset, setPtr->worldWidth, width, 
		setPtr->scrollUnits, BLT_SCROLL_MODE_HIERBOX) != TCL_OK) {
	return TCL_ERROR;
    }
    setPtr->flags |= SCROLL_PENDING;
    EventuallyRedraw(setPtr);
    return TCL_OK;
}


static void
AdoptWindow(ClientData clientData)
{
    Tab *tabPtr = clientData;
    int x, y;
    Tabset *setPtr = tabPtr->setPtr;

    x = setPtr->inset + setPtr->inset2 + tabPtr->padLeft;
#define TEAR_OFF_TAB_SIZE	5
    y = setPtr->inset + setPtr->inset2 + setPtr->outerPad + 
	TEAR_OFF_TAB_SIZE + tabPtr->padTop;
    if (setPtr->nTiers == 1) {
	y += setPtr->ySelectPad;
    }
    Blt_RelinkWindow(tabPtr->tkwin, tabPtr->container, x, y);
    Tk_MapWindow(tabPtr->tkwin);
}

static void
DestroyTearoff(DestroyData dataPtr)
{
    Tab *tabPtr = (Tab *)dataPtr;

    if (tabPtr->container != NULL) {
	Tabset *setPtr;
	Tk_Window tkwin;
	setPtr = tabPtr->setPtr;

	tkwin = tabPtr->container;
	if (tabPtr->flags & TEAROFF_REDRAW) {
	    Tcl_CancelIdleCall(DisplayTearoff, tabPtr);
	}
	Tk_DeleteEventHandler(tkwin, StructureNotifyMask, TearoffEventProc,
	    tabPtr);
	if (tabPtr->tkwin != NULL) {
	    XRectangle rect;

	    GetWindowRectangle(tabPtr, setPtr->tkwin, FALSE, &rect);
	    Blt_RelinkWindow(tabPtr->tkwin, setPtr->tkwin, rect.x, rect.y);
	    if (tabPtr == setPtr->selectPtr) {
		ArrangeWindow(tabPtr->tkwin, &rect, TRUE);
	    } else {
		Tk_UnmapWindow(tabPtr->tkwin);
	    }
	}
	Tk_DestroyWindow(tkwin);
	tabPtr->container = NULL;
    }
}

static int
NewTearoff(Tabset *setPtr, Tcl_Obj *objPtr, Tab *tabPtr)
{
    Tk_Window tkwin;
    const char *name;
    int w, h;

    name = Tcl_GetString(objPtr);
    tkwin = Tk_CreateWindowFromPath(setPtr->interp, setPtr->tkwin, name,
	(char *)NULL);
    if (tkwin == NULL) {
	return TCL_ERROR;
    }
    tabPtr->container = tkwin;
    if (Tk_WindowId(tkwin) == None) {
	Tk_MakeWindowExist(tkwin);
    }
    Tk_SetClass(tkwin, "Tearoff");
    Tk_CreateEventHandler(tkwin, (ExposureMask | StructureNotifyMask),
	TearoffEventProc, tabPtr);
    if (Tk_WindowId(tabPtr->tkwin) == None) {
	Tk_MakeWindowExist(tabPtr->tkwin);
    }
    w = Tk_Width(tabPtr->tkwin);
    if (w < 2) {
	w = (tabPtr->reqSlaveWidth > 0) 
	    ? tabPtr->reqSlaveWidth : Tk_ReqWidth(tabPtr->tkwin);
    }
    w += PADDING(tabPtr->xPad) + 2 * Tk_Changes(tabPtr->tkwin)->border_width;
    w += 2 * (setPtr->inset2 + setPtr->inset);
#define TEAR_OFF_TAB_SIZE	5
    h = Tk_Height(tabPtr->tkwin);
    if (h < 2) {
	h = (tabPtr->reqSlaveHeight > 0)
	    ? tabPtr->reqSlaveHeight : Tk_ReqHeight(tabPtr->tkwin);
    }
    h += PADDING(tabPtr->yPad) + 2 * Tk_Changes(tabPtr->tkwin)->border_width;
    h += setPtr->inset + setPtr->inset2 + TEAR_OFF_TAB_SIZE + setPtr->outerPad;
    if (setPtr->nTiers == 1) {
	h += setPtr->ySelectPad;
    }
    Tk_GeometryRequest(tkwin, w, h);
    Tk_UnmapWindow(tabPtr->tkwin);
    /* Tk_MoveWindow(tabPtr->tkwin, 0, 0); */
#ifdef WIN32
    AdoptWindow(tabPtr);
#else
    Tcl_DoWhenIdle(AdoptWindow, tabPtr);
#endif
    Tcl_SetStringObj(Tcl_GetObjResult(setPtr->interp), Tk_PathName(tkwin), -1);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * TabCgetOp --
 *
 *	  .h tab cget index option
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
TabCgetOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tab *tabPtr;

    if (GetTabFromObj(interp, setPtr, objv[3], &tabPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if (tabPtr == NULL) {
	Tcl_AppendResult(interp, "can't find a tab \"", 
		Tcl_GetString(objv[3]), "\" in \"", Tk_PathName(setPtr->tkwin), 
			 "\"", (char *)NULL);
	return TCL_ERROR;
    }
    iconOption.clientData = setPtr;
    return Blt_ConfigureValueFromObj(interp, setPtr->tkwin, tabSpecs,
	(char *)tabPtr, objv[4], 0);
}

/*
 *---------------------------------------------------------------------------
 *
 * TabConfigureOp --
 *
 * 	This procedure is called to process a list of configuration options
 * 	database, in order to reconfigure the options for one or more tabs in
 * 	the widget.
 *
 *	  .h tab configure index ?index...? ?option value?...
 *
 * Results:
 *	A standard TCL result.  If TCL_ERROR is returned, then interp->result
 *	contains an error message.
 *
 * Side Effects:
 *	Configuration information, such as text string, colors, font, etc. get
 *	set; old resources get freed, if there were any.  The widget is
 *	redisplayed if needed.
 *
 *---------------------------------------------------------------------------
 */
static int
TabConfigureOp(Tabset *setPtr, Tcl_Interp *interp, int objc, 
	       Tcl_Obj *const *objv)
{
    Tab *tabPtr;
    TabIterator iter;

    iconOption.clientData = setPtr;
    if ((objc == 4) || (objc == 5)) {
	if (GetTabFromObj(interp, setPtr, objv[3], &tabPtr) != TCL_OK) {
	    return TCL_ERROR;	/* Can't find node. */
	}
	if (tabPtr == NULL) {
	    Tcl_AppendResult(interp, "can't find a tab \"", 
		Tcl_GetString(objv[3]), "\" in \"", 
			     Tk_PathName(setPtr->tkwin), 
			     "\"", (char *)NULL);
	    return TCL_ERROR;
	}
	if (objc == 4) {
	    return Blt_ConfigureInfoFromObj(interp, setPtr->tkwin, tabSpecs, 
		(char *)tabPtr, (Tcl_Obj *)NULL, 0);
	} else if (objc == 5) {
	    return Blt_ConfigureInfoFromObj(interp, setPtr->tkwin, tabSpecs, 
		(char *)tabPtr, objv[4], 0);
	}
    }
    if (GetTabIterator(interp, setPtr, objv[3], &iter) != TCL_OK) {
	return TCL_ERROR;	/* Can't find node. */
    }
    for (tabPtr = FirstTaggedTab(&iter); tabPtr != NULL; 
	 tabPtr = NextTaggedTab(&iter)) {
	int result;

	Tcl_Preserve(tabPtr);
	result = Blt_ConfigureWidgetFromObj(interp, setPtr->tkwin, tabSpecs, 
		objc - 4, objv + 4, (char *)tabPtr, BLT_CONFIG_OBJV_ONLY);
	Tcl_Release(tabPtr);
	if (result == TCL_ERROR) {
	    return TCL_ERROR;
	}
	if (ConfigureTab(setPtr, tabPtr) != TCL_OK) {
	    return TCL_ERROR;
	}
    }
    return TCL_OK;
}


/*
 *---------------------------------------------------------------------------
 *
 * TabOp --
 *
 *	This procedure handles tab operations.
 *
 * Results:
 *	A standard TCL result.
 *
 *---------------------------------------------------------------------------
 */
static Blt_OpSpec tabOps[] =
{
    {"cget",      2, TabCgetOp,	     5, 5, "tab option",},
    {"configure", 2, TabConfigureOp, 4, 0, "tab ?option value?...",},
};

static int nTabOps = sizeof(tabOps) / sizeof(Blt_OpSpec);

static int
TabOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    TabsetCmdProc *proc;
    int result;

    proc = Blt_GetOpFromObj(interp, nTabOps, tabOps, BLT_OP_ARG2, 
		    objc, objv, 0);
    if (proc == NULL) {
	return TCL_ERROR;
    }
    result = (*proc) (setPtr, interp, objc, objv);
    return result;
}

/*
 *---------------------------------------------------------------------------
 *
 * PerforationActivateOp --
 *
 * 	This procedure is called to highlight the perforation.
 *
 *	  .h perforation highlight boolean
 *
 * Results:
 *	A standard TCL result.  If TCL_ERROR is returned, then interp->result
 *	contains an error message.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
PerforationActivateOp(
    Tabset *setPtr,
    Tcl_Interp *interp,		/* Not used. */
    int objc,
    Tcl_Obj *const *objv)
{
    int bool;

    if (Tcl_GetBooleanFromObj(interp, objv[3], &bool) != TCL_OK) {
	return TCL_ERROR;
    }
    if (bool) {
	setPtr->flags |= ACTIVE_PERFORATION;
    } else {
	setPtr->flags &= ~ACTIVE_PERFORATION;
    }
    EventuallyRedraw(setPtr);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * PerforationInvokeOp --
 *
 * 	This procedure is called to invoke a perforation command.
 *
 *	  .t perforation invoke
 *
 * Results:
 *	A standard TCL result.  If TCL_ERROR is returned, then
 *	interp->result contains an error message.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
PerforationInvokeOp(Tabset *setPtr, Tcl_Interp *interp, int objc, 
		    Tcl_Obj *const *objv)
{
    Tcl_Obj *objPtr;
    Tab *tabPtr;

    if (setPtr->selectPtr == NULL) {
	return TCL_OK;
    }
    tabPtr = setPtr->selectPtr;
    objPtr = GETATTR(tabPtr, perfCmdObjPtr);
    if (objPtr != NULL) {
	Tcl_Obj **args;
	Tcl_Obj **cmdv;
	int cmdc;
	int i;
	int result;

	if (Tcl_ListObjGetElements(interp, objPtr, &cmdc, &cmdv) != TCL_OK) {
	    return TCL_ERROR;
	}
	args = Blt_AssertMalloc(sizeof(Tcl_Obj *) * (cmdc + 1));
	for (i = 0; i < cmdc; i++) {
	    args[i] = cmdv[i];
	}
	args[i] = Tcl_NewIntObj(tabPtr->index);
	result = Blt_GlobalEvalObjv(interp, cmdc + 1, args);
	Blt_Free(args);
	if (result != TCL_OK) {
	    return TCL_ERROR;
	}
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * PerforationOp --
 *
 *	This procedure handles tab operations.
 *
 * Results:
 *	A standard TCL result.
 *
 *---------------------------------------------------------------------------
 */
static Blt_OpSpec perforationOps[] =
{
    {"activate", 1, PerforationActivateOp, 4, 4, "boolean" }, 
    {"invoke",   1, PerforationInvokeOp,   3, 3, "",},
};

static int nPerforationOps = sizeof(perforationOps) / sizeof(Blt_OpSpec);

static int
PerforationOp(Tabset *setPtr, Tcl_Interp *interp, int objc, 
	      Tcl_Obj *const *objv)
{
    TabsetCmdProc *proc;
    int result;

    proc = Blt_GetOpFromObj(interp, nPerforationOps, perforationOps, 
	BLT_OP_ARG2, objc, objv, 0);
    if (proc == NULL) {
	return TCL_ERROR;
    }
    result = (*proc) (setPtr, interp, objc, objv);
    return result;
}

/*
 *---------------------------------------------------------------------------
 *
 * ScanOp --
 *
 *	Implements the quick scan.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ScanOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    char c;
    const char *string;
    int length;
    int oper;
    int x, y;

#define SCAN_MARK	1
#define SCAN_DRAGTO	2
    string = Tcl_GetStringFromObj(objv[2], &length);
    c = string[0];
    if ((c == 'm') && (strncmp(string, "mark", length) == 0)) {
	oper = SCAN_MARK;
    } else if ((c == 'd') && (strncmp(string, "dragto", length) == 0)) {
	oper = SCAN_DRAGTO;
    } else {
	Tcl_AppendResult(interp, "bad scan operation \"", string,
	    "\": should be either \"mark\" or \"dragto\"", (char *)NULL);
	return TCL_ERROR;
    }
    if ((Tk_GetPixelsFromObj(interp, setPtr->tkwin, objv[3], &x) != TCL_OK) ||
	(Tk_GetPixelsFromObj(interp, setPtr->tkwin, objv[4], &y) != TCL_OK)) {
	return TCL_ERROR;
    }
    if (oper == SCAN_MARK) {
	if (setPtr->side & (SIDE_LEFT | SIDE_RIGHT)) {
	    setPtr->scanAnchor = y;
	} else {
	    setPtr->scanAnchor = x;
	}
	setPtr->scanOffset = setPtr->scrollOffset;
    } else {
	int offset, delta;

	if (setPtr->side & (SIDE_LEFT | SIDE_RIGHT)) {
	    delta = setPtr->scanAnchor - y;
	} else {
	    delta = setPtr->scanAnchor - x;
	}
	offset = setPtr->scanOffset + (10 * delta);
	offset = Blt_AdjustViewport(offset, setPtr->worldWidth,
	    VPORTWIDTH(setPtr), setPtr->scrollUnits, BLT_SCROLL_MODE_HIERBOX);
	setPtr->scrollOffset = offset;
	setPtr->flags |= SCROLL_PENDING;
	EventuallyRedraw(setPtr);
    }
    return TCL_OK;
}

/*ARGSUSED*/
static int
SeeOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tab *tabPtr;

    if (GetTabFromObj(interp, setPtr, objv[2], &tabPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if (tabPtr != NULL) {
	int left, right, width;

	width = VPORTWIDTH(setPtr);
	left = setPtr->scrollOffset + setPtr->xSelectPad;
	right = setPtr->scrollOffset + width - setPtr->xSelectPad;

	/* If the tab is partially obscured, scroll so that it's
	 * entirely in view. */
	if (tabPtr->worldX < left) {
	    setPtr->scrollOffset = tabPtr->worldX;
	    if (tabPtr->index > 0) {
		setPtr->scrollOffset -= TAB_SCROLL_OFFSET;
	    }
	} else if ((tabPtr->worldX + tabPtr->worldWidth) >= right) {
	    Blt_ChainLink link;

	    setPtr->scrollOffset = tabPtr->worldX + tabPtr->worldWidth -
		(width - 2 * setPtr->xSelectPad);
	    link = Blt_Chain_NextLink(tabPtr->link); 
	    if (link != NULL) {
		Tab *nextPtr;

		nextPtr = Blt_Chain_GetValue(link);
		if (nextPtr->tier == tabPtr->tier) {
		    setPtr->scrollOffset += TAB_SCROLL_OFFSET;
		}
	    }
	}
	setPtr->flags |= SCROLL_PENDING;
	EventuallyRedraw(setPtr);
    }
    return TCL_OK;
}

/*ARGSUSED*/
static int
SizeOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    int nTabs;

    nTabs = Blt_Chain_GetLength(setPtr->chain);
    Tcl_SetIntObj(Tcl_GetObjResult(interp), nTabs);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * TagAddOp --
 *
 *	.t tag add tagName tab1 tab2 tab2 tab4
 *
 *---------------------------------------------------------------------------
 */
static int
TagAddOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    const char *tag;
    long tagId;

    tag = Tcl_GetString(objv[3]);
    if (Tcl_GetLongFromObj(NULL, objv[3], &tagId) == TCL_OK) {
	Tcl_AppendResult(interp, "bad tag \"", tag, 
		 "\": can't be a number.", (char *)NULL);
	return TCL_ERROR;
    }
    if (strcmp(tag, "all") == 0) {
	Tcl_AppendResult(interp, "can't add reserved tag \"", tag, "\"", 
			 (char *)NULL);
	return TCL_ERROR;
    }
    if (objc == 4) {
	/* No nodes specified.  Just add the tag. */
	AddTag(setPtr, NULL, tag);
    } else {
	int i;

	for (i = 4; i < objc; i++) {
	    Tab *tabPtr;
	    TabIterator iter;
	    
	    if (GetTabIterator(interp, setPtr, objv[i], &iter) != TCL_OK) {
		return TCL_ERROR;
	    }
	    for (tabPtr = FirstTaggedTab(&iter); tabPtr != NULL; 
		 tabPtr = NextTaggedTab(&iter)) {
		AddTag(setPtr, tabPtr, tag);
	    }
	}
    }
    return TCL_OK;
}


/*
 *---------------------------------------------------------------------------
 *
 * TagDeleteOp --
 *
 *	.t delete tagName tab1 tab2 tab3
 *
 *---------------------------------------------------------------------------
 */
static int
TagDeleteOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    const char *tag;
    Blt_HashTable *tablePtr;
    long tagId;

    tag = Tcl_GetString(objv[3]);
    if (Tcl_GetLongFromObj(NULL, objv[3], &tagId) == TCL_OK) {
	Tcl_AppendResult(interp, "bad tag \"", tag, 
		 "\": can't be a number.", (char *)NULL);
	return TCL_ERROR;
    }
    if (strcmp(tag, "all") == 0) {
	Tcl_AppendResult(interp, "can't delete reserved tag \"", tag, "\"", 
			 (char *)NULL);
        return TCL_ERROR;
    }
    tablePtr = GetTagTable(setPtr, tag);
    if (tablePtr != NULL) {
        int i;
      
        for (i = 4; i < objc; i++) {
	    Tab *tabPtr;
	    TabIterator iter;

	    if (GetTabIterator(interp, setPtr, objv[i], &iter) != TCL_OK) {
	        return TCL_ERROR;
	    }
	    for (tabPtr = FirstTaggedTab(&iter); tabPtr != NULL; 
		 tabPtr = NextTaggedTab(&iter)) {
		Blt_HashEntry *hPtr;

	        hPtr = Blt_FindHashEntry(tablePtr, (char *)tabPtr);
	        if (hPtr != NULL) {
		    Blt_DeleteHashEntry(tablePtr, hPtr);
	        }
	   }
       }
    }
    return TCL_OK;
}


/*
 *---------------------------------------------------------------------------
 *
 * TagExistsOp --
 *
 *	Returns the existence of the one or more tags in the given node.  If
 *	the node has any the tags, true is return in the interpreter.
 *
 *	.t tag exists tab tag1 tag2 tag3...
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
TagExistsOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    int i;
    TabIterator iter;

    if (GetTabIterator(interp, setPtr, objv[3], &iter) != TCL_OK) {
	return TCL_ERROR;
    }
    for (i = 4; i < objc; i++) {
	const char *tag;
	Tab *tabPtr;

	tag = Tcl_GetString(objv[i]);
	for (tabPtr = FirstTaggedTab(&iter); tabPtr != NULL; 
	     tabPtr = NextTaggedTab(&iter)) {
	    if (HasTag(tabPtr, tag)) {
		Tcl_SetBooleanObj(Tcl_GetObjResult(interp), TRUE);
		return TCL_OK;
	    }
	}
    }
    Tcl_SetBooleanObj(Tcl_GetObjResult(interp), FALSE);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * TagForgetOp --
 *
 *	Removes the given tags from all tabs.
 *
 *	.ts tab forget tag1 tag2 tag3...
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
TagForgetOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    int i;

    for (i = 3; i < objc; i++) {
	const char *tag;
	long tagId;

	tag = Tcl_GetString(objv[i]);
	if (Tcl_GetLongFromObj(NULL, objv[i], &tagId) == TCL_OK) {
	    Tcl_AppendResult(interp, "bad tag \"", tag, 
			     "\": can't be a number.", (char *)NULL);
	    return TCL_ERROR;
	}
	ForgetTag(setPtr, tag);
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * TagGetOp --
 *
 *	Returns tag names for a given node.  If one of more pattern arguments
 *	are provided, then only those matching tags are returned.
 *
 *	.t tag get tab pat1 pat2...
 *
 *---------------------------------------------------------------------------
 */
static int
TagGetOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tab *tabPtr; 
    TabIterator iter;
    Tcl_Obj *listObjPtr;

    if (GetTabIterator(interp, setPtr, objv[3], &iter) != TCL_OK) {
	return TCL_ERROR;
    }
    listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **) NULL);
    for (tabPtr = FirstTaggedTab(&iter); tabPtr != NULL; 
	 tabPtr = NextTaggedTab(&iter)) {
	if (objc == 4) {
	    Blt_HashEntry *hPtr;
	    Blt_HashSearch hiter;

	    for (hPtr = Blt_FirstHashEntry(&setPtr->tagTable, &hiter); 
		 hPtr != NULL; hPtr = Blt_NextHashEntry(&hiter)) {
		Blt_HashTable *tablePtr;

		tablePtr = Blt_GetHashValue(hPtr);
		if (Blt_FindHashEntry(tablePtr, (char *)tabPtr) != NULL) {
		    const char *tag;
		    Tcl_Obj *objPtr;

		    tag = Blt_GetHashKey(&setPtr->tagTable, hPtr);
		    objPtr = Tcl_NewStringObj(tag, -1);
		    Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
		}
	    }
	    Tcl_ListObjAppendElement(interp, listObjPtr, 
				     Tcl_NewStringObj("all", 3));
	} else {
	    int i;
	    
	    /* Check if we need to add the special tags "all" */
	    for (i = 4; i < objc; i++) {
		const char *pattern;

		pattern = Tcl_GetString(objv[i]);
		if (Tcl_StringMatch("all", pattern)) {
		    Tcl_Obj *objPtr;

		    objPtr = Tcl_NewStringObj("all", 3);
		    Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
		    break;
		}
	    }
	    /* Now process any standard tags. */
	    for (i = 4; i < objc; i++) {
		Blt_HashEntry *hPtr;
		Blt_HashSearch hiter;
		const char *pattern;
		
		pattern = Tcl_GetString(objv[i]);
		for (hPtr = Blt_FirstHashEntry(&setPtr->tagTable, &hiter); 
		     hPtr != NULL; hPtr = Blt_NextHashEntry(&hiter)) {
		    const char *tag;
		    Blt_HashTable *tablePtr;

		    tablePtr = Blt_GetHashValue(hPtr);
		    tag = Blt_GetHashKey(&setPtr->tagTable, hPtr);
		    if (!Tcl_StringMatch(tag, pattern)) {
			continue;
		    }
		    if (Blt_FindHashEntry(tablePtr, (char *)tabPtr) != NULL) {
			Tcl_Obj *objPtr;

			objPtr = Tcl_NewStringObj(tag, -1);
			Tcl_ListObjAppendElement(interp, listObjPtr,objPtr);
		    }
		}
	    }
	}    
    }
    Tcl_SetObjResult(interp, listObjPtr);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * TagNamesOp --
 *
 *	Returns the names of all the tags in the tabset.  If one of more node
 *	arguments are provided, then only the tags found in those nodes are
 *	returned.
 *
 *	.t tag names tab tab tab...
 *
 *---------------------------------------------------------------------------
 */
static int
TagNamesOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tcl_Obj *listObjPtr, *objPtr;

    listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **) NULL);
    objPtr = Tcl_NewStringObj("all", -1);
    Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
    if (objc == 3) {
	Blt_HashEntry *hPtr;
	Blt_HashSearch iter;

	for (hPtr = Blt_FirstHashEntry(&setPtr->tagTable, &iter); hPtr != NULL; 
	     hPtr = Blt_NextHashEntry(&iter)) {
	    const char *tag;
	    tag = Blt_GetHashKey(&setPtr->tagTable, hPtr);
	    objPtr = Tcl_NewStringObj(tag, -1);
	    Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	}
    } else {
	Blt_HashTable uniqTable;
	int i;

	Blt_InitHashTable(&uniqTable, BLT_STRING_KEYS);
	for (i = 3; i < objc; i++) {
	    TabIterator iter;
	    Tab *tabPtr;

	    if (GetTabIterator(interp, setPtr, objPtr, &iter) != TCL_OK) {
		goto error;
	    }
	    for (tabPtr = FirstTaggedTab(&iter); tabPtr != NULL; 
		 tabPtr = NextTaggedTab(&iter)) {
		Blt_HashEntry *hPtr;
		Blt_HashSearch hiter;
		for (hPtr = Blt_FirstHashEntry(&setPtr->tagTable, &hiter); 
		     hPtr != NULL; hPtr = Blt_NextHashEntry(&hiter)) {
		    const char *tag;
		    Blt_HashTable *tablePtr;

		    tag = Blt_GetHashKey(&setPtr->tagTable, hPtr);
		    tablePtr = Blt_GetHashValue(hPtr);
		    if (Blt_FindHashEntry(tablePtr, tabPtr) != NULL) {
			int isNew;

			Blt_CreateHashEntry(&uniqTable, tag, &isNew);
		    }
		}
	    }
	}
	{
	    Blt_HashEntry *hPtr;
	    Blt_HashSearch hiter;

	    for (hPtr = Blt_FirstHashEntry(&uniqTable, &hiter); hPtr != NULL;
		 hPtr = Blt_NextHashEntry(&hiter)) {
		objPtr = Tcl_NewStringObj(Blt_GetHashKey(&uniqTable, hPtr), -1);
		Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	    }
	}
	Blt_DeleteHashTable(&uniqTable);
    }
    Tcl_SetObjResult(interp, listObjPtr);
    return TCL_OK;
 error:
    Tcl_DecrRefCount(listObjPtr);
    return TCL_ERROR;
}

/*
 *---------------------------------------------------------------------------
 *
 * TagIndicesOp --
 *
 *	Returns the indices associated with the given tags.  The indices
 *	returned will represent the union of tabs for all the given tags.
 *
 *	.t tag indices tag1 tag2 tag3...
 *
 *---------------------------------------------------------------------------
 */
static int
TagIndicesOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Blt_HashTable tabTable;
    int i;
	
    Blt_InitHashTable(&tabTable, BLT_ONE_WORD_KEYS);
    for (i = 3; i < objc; i++) {
	const char *tag;
	long tagId;

	tag = Tcl_GetString(objv[i]);
	if (Tcl_GetLongFromObj(NULL, objv[i], &tagId) == TCL_OK) {
	    Tcl_AppendResult(interp, "bad tag \"", tag, 
			     "\": can't be a number.", (char *)NULL);
	    goto error;
	}
	if (strcmp(tag, "all") == 0) {
	    break;
	} else {
	    Blt_HashTable *tablePtr;
	    
	    tablePtr = GetTagTable(setPtr, tag);
	    if (tablePtr != NULL) {
		Blt_HashEntry *hPtr;
		Blt_HashSearch iter;

		for (hPtr = Blt_FirstHashEntry(tablePtr, &iter); 
		     hPtr != NULL; hPtr = Blt_NextHashEntry(&iter)) {
		    Tab *tabPtr;
		    int isNew;

		    tabPtr = Blt_GetHashValue(hPtr);
		    if (tabPtr != NULL) {
			Blt_CreateHashEntry(&tabTable, (char *)tabPtr, &isNew);
		    }
		}
		continue;
	    }
	}
	Tcl_AppendResult(interp, "can't find a tag \"", tag, "\"",
			 (char *)NULL);
	goto error;
    }
    {
	Blt_HashEntry *hPtr;
	Blt_HashSearch iter;
	Tcl_Obj *listObjPtr;

	listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **) NULL);
	for (hPtr = Blt_FirstHashEntry(&tabTable, &iter); hPtr != NULL; 
	     hPtr = Blt_NextHashEntry(&iter)) {
	    Tab *tabPtr;
	    Tcl_Obj *objPtr;

	    tabPtr = (Tab *)Blt_GetHashKey(&tabTable, hPtr);
	    objPtr = Tcl_NewLongObj(tabPtr->index);
	    Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	}
	Tcl_SetObjResult(interp, listObjPtr);
    }
    Blt_DeleteHashTable(&tabTable);
    return TCL_OK;

 error:
    Blt_DeleteHashTable(&tabTable);
    return TCL_ERROR;
}

/*
 *---------------------------------------------------------------------------
 *
 * TagSetOp --
 *
 *	Sets one or more tags for a given tab.  Tag names can't start with a
 *	digit (to distinquish them from node ids) and can't be a reserved tag
 *	("all").
 *
 *	.t tag set tab tag1 tag2...
 *
 *---------------------------------------------------------------------------
 */
static int
TagSetOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    int i;
    TabIterator iter;

    if (GetTabIterator(interp, setPtr, objv[3], &iter) != TCL_OK) {
	return TCL_ERROR;
    }
    for (i = 4; i < objc; i++) {
	const char *tag;
	long tagId;
	Tab *tabPtr;

	tag = Tcl_GetString(objv[i]);
	if (Tcl_GetLongFromObj(NULL, objv[i], &tagId) == TCL_OK) {
	    Tcl_AppendResult(interp, "bad tag \"", tag, 
			     "\": can't be a number.", (char *)NULL);
	    return TCL_ERROR;
	}
	if (strcmp(tag, "all") == 0) {
	    Tcl_AppendResult(interp, "can't add reserved tag \"", tag, "\"",
			     (char *)NULL);	
	    return TCL_ERROR;
	}
	for (tabPtr = FirstTaggedTab(&iter); tabPtr != NULL; 
	     tabPtr = NextTaggedTab(&iter)) {
	    AddTag(setPtr, tabPtr, tag);
	}    
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * TagUnsetOp --
 *
 *	Removes one or more tags from a given tab. If a tag doesn't exist or
 *	is a reserved tag ("all"), nothing will be done and no error
 *	message will be returned.
 *
 *	.t tag unset tab tag1 tag2...
 *
 *---------------------------------------------------------------------------
 */
static int
TagUnsetOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tab *tabPtr;
    TabIterator iter;

    if (GetTabIterator(interp, setPtr, objv[3], &iter) != TCL_OK) {
	return TCL_ERROR;
    }
    for (tabPtr = FirstTaggedTab(&iter); tabPtr != NULL; 
	 tabPtr = NextTaggedTab(&iter)) {
	int i;
	for (i = 4; i < objc; i++) {
	    RemoveTag(tabPtr, Tcl_GetString(objv[i]));
	}    
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * TagOp --
 *
 * 	This procedure is invoked to process tag operations.
 *
 * Results:
 *	A standard TCL result.
 *
 * Side Effects:
 *	See the user documentation.
 *
 *---------------------------------------------------------------------------
 */
static Blt_OpSpec tagOps[] =
{
    {"add",     1, TagAddOp,      4, 0, "tab ?tag...?",},
    {"delete",  1, TagDeleteOp,   4, 0, "tab ?tag...?",},
    {"exists",  1, TagExistsOp,   4, 0, "tab ?tag...?",},
    {"forget",  1, TagForgetOp,   3, 0, "?tag...?",},
    {"get",     1, TagGetOp,      4, 0, "tab ?pattern...?",},
    {"indices", 1, TagIndicesOp,  3, 0, "?tag...?",},
    {"names",   2, TagNamesOp,    3, 0, "?tab...?",},
    {"set",     1, TagSetOp,      4, 0, "tab ?tag...",},
    {"unset",   1, TagUnsetOp,    4, 0, "tab ?tag...",},
};

static int nTagOps = sizeof(tagOps) / sizeof(Blt_OpSpec);

static int
TagOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    TabsetCmdProc *proc;
    int result;

    proc = Blt_GetOpFromObj(interp, nTagOps, tagOps, BLT_OP_ARG2,
	objc, objv, 0);
    if (proc == NULL) {
	return TCL_ERROR;
    }
    result = (*proc)(setPtr, interp, objc, objv);
    return result;
}

/*
 *---------------------------------------------------------------------------
 *
 * TearoffOp --
 *
 *	  .h tearoff index ?title?
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
TearoffOp(Tabset *setPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tab *tabPtr;
    Tk_Window tkwin;
    const char *string;
    int result;

    if (GetTabFromObj(interp, setPtr, objv[2], &tabPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if ((tabPtr == NULL) || (tabPtr->tkwin == NULL) || 
	(tabPtr->flags & (DISABLED|HIDE))) {
	return TCL_OK;		/* No-op */
    }
    if (objc == 3) {
	Tk_Window parent;

	parent = (tabPtr->container == NULL) ? setPtr->tkwin : tabPtr->container;
	Tcl_SetStringObj(Tcl_GetObjResult(interp), Tk_PathName(parent), -1);
	return TCL_OK;
    }
    Tcl_Preserve(tabPtr);
    result = TCL_OK;

    string = Tcl_GetString(objv[3]);
    tkwin = Tk_NameToWindow(interp, string, setPtr->tkwin);
    Tcl_ResetResult(interp);

    if (tabPtr->container != NULL) {
	Tcl_EventuallyFree(tabPtr, DestroyTearoff);
    }
    if ((tkwin != setPtr->tkwin) && (tabPtr->container == NULL)) {
	result = NewTearoff(setPtr, objv[3], tabPtr);
    }
    Tcl_Release(tabPtr);
    EventuallyRedraw(setPtr);
    return result;
}

static void
ComputeTabGeometry(Tabset *setPtr, Tab *tabPtr)
{
    Blt_Font font;
    int iconWidth0, iconHeight0;
    unsigned int w, h;
	
    font = GETATTR(tabPtr, font);
    w = h = 0;
    if (tabPtr->text != NULL) {
	TextStyle ts;

	Blt_Ts_InitStyle(ts);
	Blt_Ts_SetFont(ts, font);
	Blt_Ts_SetPadding(ts, 2, 2, 0, 0);
	if (tabPtr->layoutPtr != NULL) {
	    Blt_Free(tabPtr->layoutPtr);
	}
	tabPtr->layoutPtr = Blt_Ts_CreateLayout(tabPtr->text, -1, &ts);
	tabPtr->textWidth0  = ODD(tabPtr->layoutPtr->width);
	tabPtr->textHeight0 = ODD(tabPtr->layoutPtr->height);
    } else {
	tabPtr->textWidth0  = tabPtr->textHeight0 = 0;
    }
    if (tabPtr->icon != NULL) {
	iconWidth0  = IconWidth(tabPtr->icon);
	iconHeight0 = IconHeight(tabPtr->icon);
    } else {
	iconWidth0 = iconHeight0 = 0;
    }
    w = iconWidth0 + tabPtr->textWidth0 + PADDING(tabPtr->iPadX);
    if ((iconWidth0 > 0) && (tabPtr->textWidth0 > 0)) {
	w += LABEL_PAD;
    }
    h = MAX(iconHeight0, tabPtr->textHeight0) + PADDING(tabPtr->iPadY);
    if ((setPtr->flags & CLOSE_NEEDED) && (setPtr->plusPtr != tabPtr)) {
	w += CLOSE_WIDTH + LABEL_PAD + 2 * setPtr->closeButton.borderWidth;
    }
    tabPtr->labelWidth0  = w;
    tabPtr->labelHeight0 = h;
}


/*
 *---------------------------------------------------------------------------
 *
 * ComputeWorldGeometry --
 *
 *	Compute the sizes of the tabset and each tab in world coordinates.
 *	World coordinates are not rotated according to the side the widget 
 *	where the tabs are located.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ComputeWorldGeometry(Tabset *setPtr)
{
    int count;
    int maxPageWidth, maxPageHeight;
    int maxTabWidth,  maxTabHeight;
    Tab *tabPtr;

    maxPageWidth = maxPageHeight = 0;
    maxTabWidth = maxTabHeight = 0;
    count = 0;

    /*
     * Step 1:  Figure out the maximum area needed for a label and a
     *		page.  Both the label and page dimensions are adjusted
     *		for orientation.  In addition, reset the visibility
     *		flags and reorder the tabs.
     */
    for (tabPtr = FirstTab(setPtr, 0); tabPtr != NULL; 
	 tabPtr = NextTab(tabPtr, 0)) {

	/* Reset visibility flag and order of tabs. */
	tabPtr->flags &= ~ONSCREEN;
	if (tabPtr->flags & HIDE) {
	    continue;
	}
	ComputeTabGeometry(setPtr, tabPtr);
	count++;
	if (tabPtr->tkwin != NULL) {
	    int w, h;

	    w = GetReqWidth(tabPtr);
	    if (maxPageWidth < w) {
		maxPageWidth = w;
	    }
	    h = GetReqHeight(tabPtr);
	    if (maxPageHeight < h) {
		maxPageHeight = h;
	    }
	}
	if (maxTabWidth < tabPtr->labelWidth0) {
	    maxTabWidth = tabPtr->labelWidth0;
	}
	if (maxTabHeight < tabPtr->labelHeight0) {
	    maxTabHeight = tabPtr->labelHeight0;
	}
    }
    setPtr->overlap = 0;
    /*
     * Step 2:	Set the sizes for each tab.  This is different
     *		for constant and variable width tabs.  Add the extra space
     *		needed for slanted tabs, now that we know maximum tab
     *		height.
     */
    if (setPtr->reqTabWidth != TABWIDTH_VARIABLE) {
	int slant;
	Tab *tabPtr;
	int w, h;
	
	w = (setPtr->reqTabWidth > 0) ? setPtr->reqTabWidth : maxTabWidth;
	h = maxTabHeight;
	if ((setPtr->quad == ROTATE_90) || (setPtr->quad == ROTATE_270)) {
	    SWAP(w, h);
	}
	if (setPtr->side & (SIDE_LEFT | SIDE_RIGHT)) {
	    SWAP(w, h);
	}
	slant = h;
	w += (setPtr->flags & SLANT_LEFT)  ? slant : setPtr->inset2;
	w += (setPtr->flags & SLANT_RIGHT) ? slant : setPtr->inset2;
	if (setPtr->flags & SLANT_LEFT) {
	    setPtr->overlap += slant / 2;
	}
	if (setPtr->flags & SLANT_RIGHT) {
	    setPtr->overlap += slant / 2;
	}
	setPtr->tabWidth  = w;
	setPtr->tabHeight = h;
	for (tabPtr = FirstTab(setPtr, HIDE); tabPtr != NULL; 
	     tabPtr = NextTab(tabPtr, HIDE)) {
	    if (setPtr->plusPtr == tabPtr) {
		tabPtr->worldWidth = tabPtr->labelWidth0;
		tabPtr->worldWidth += (setPtr->flags & SLANT_LEFT)  
		    ? slant : setPtr->inset2;
		tabPtr->worldWidth += (setPtr->flags & SLANT_RIGHT) 
		    ? slant : setPtr->inset2;
	    } else {
		tabPtr->worldWidth = w;
	    }   
	    tabPtr->worldHeight = h;
	}
    } else {				/* Variable width tabs. */
	int slant;
	Tab *tabPtr;
	int tabWidth, tabHeight;
	int w, h;

	tabWidth = tabHeight = 0;
	for (tabPtr = FirstTab(setPtr, HIDE); tabPtr != NULL;
	     tabPtr = NextTab(tabPtr, HIDE)) {

	    w = tabPtr->labelWidth0;
	    h = maxTabHeight;
	    if ((setPtr->quad == ROTATE_90) || (setPtr->quad == ROTATE_270)) {
		SWAP(w, h);
	    }
	    if (setPtr->side & (SIDE_LEFT | SIDE_RIGHT)) {
		SWAP(w, h);
	    }
	    slant = h;
	    w += (setPtr->flags & SLANT_LEFT)  ? slant : setPtr->inset2;
	    w += (setPtr->flags & SLANT_RIGHT) ? slant : setPtr->inset2;
	    tabPtr->worldWidth = w;
	    tabPtr->worldHeight = h;
	    if (tabWidth < w) {
		tabWidth = w;
	    }
	    if (tabHeight < h) {
		tabHeight = h;
	    }
	}
	if (setPtr->flags & SLANT_LEFT) {
	    setPtr->overlap += tabHeight / 2;
	}
	if (setPtr->flags & SLANT_RIGHT) {
	    setPtr->overlap += tabHeight / 2;
	}
	setPtr->tabWidth  = tabWidth;
	setPtr->tabHeight = tabHeight;
    }


    /*
     * Let the user override any page dimension.
     */
    setPtr->pageWidth = maxPageWidth;
    setPtr->pageHeight = maxPageHeight;
    if (setPtr->reqPageWidth > 0) {
	setPtr->pageWidth = setPtr->reqPageWidth;
    }
    if (setPtr->reqPageHeight > 0) {
	setPtr->pageHeight = setPtr->reqPageHeight;
    }
    return count;
}

#ifdef notdef
static int 
CompareTabSizes(const void *a, const void *b)
{
    Tab *tab1Ptr, *tab2Ptr;

    tab1Ptr = *(Tab **)a;
    tab2Ptr = *(Tab **)b;
    if (tab1Ptr == setPtr->plusPtr) {
	return -1;
    }
    if (tab2Ptr == setPtr->plusPtr) {
	return 1;
    }
    return tab1Ptr->worldWidth - tab2Ptr->worldWidth;
}
    
/* 
 * Two pass shrink.  
 *	1) Any space beyond the normal size.
 *	2) Any space beyong the defined minimum.		
 */
static void
ShrinkTabs2(Tabset *setPtr, Tab *startPtr, int nTabs, int adjustment)
{
    int x;
    int i;
    Tab *tabPtr;

    /* Sort tabs according to size. */
    tabs = Blt_AssertMalloc(nTabs * sizeof(Tab *));
    for (tabPtr = startPtr, i = 0; (tabPtr != NULL) && (i < nTabs); 
	 tabPtr = NextTab(tabPtr, HIDE), i++) {
	tabs[i] = tabPtr;
    }
    qsort(tabs, nTabs, sizeof(Tab *), CompareTabSizes);
    for (i = 1; i < tabIndex; i++) {
	avail = (tabs[i-1].worldWidth - tabs[i].worldWidth) * i;
	if (avail > adjustment) {
	    avail = adjustment;
	}
	ration = (avail+(i-1))/ i;
	for (j = 0; j < i; j++) {
	    if (adjustment > ration) {
		ration = adjustment;
	    }
	    tabs[j].worldWidth -= ration;
	    adjustment -= ration;
	}

	accum += tabs[i].worldWidth - tabs[tabIndex].worldWidth;
	if (accum >= adjustment) {
	    break;			/* Have enough room. */
	}
    }
    
    x = startPtr->tier;
    while (adjustment > 0) {
	int count;
	int ration;
	Tab *tabPtr;

	ration = adjustment / count;
	if (ration == 0) {
	    ration = 1;
	}
	count = 0;
	for (i = 0; (i < nTabs) && (adjustment > 0); i++) {
	    tabPtr = tabs[i];
	    if (tabPtr->worldWidth)

	     tabPtr = NextTab(tabPtr, HIDE), i++) {
	    if (tabPtr != setPtr->plusPtr) {
		count++;
	    }
	}
	ration = adjustment / count;
	if (ration == 0) {
	    ration = 1;
	}
	
	for (tabPtr = startPtr, i = 0; 
	     (tabPtr != NULL) && (i < nTabs) && (adjustment > 0); 
	     tabPtr = NextTab(tabPtr, HIDE), i++) {
	    if (tabPtr != setPtr->plusPtr) {
		adjustment -= ration;
		tabPtr->worldWidth -= ration;
		assert(x == tabPtr->tier);
	    }
	}
    }
    /*
     * Go back and reset the world X-coordinates of the tabs,
     * now that their widths have changed.
     */
    x = 0;
    for (tabPtr = startPtr, i = 0; (i < nTabs) && (tabPtr != NULL); 
	 tabPtr = NextTab(tabPtr, HIDE), i++) {
	tabPtr->worldX = x;
	x += tabPtr->worldWidth + setPtr->gap - setPtr->overlap;
    }
}
#endif

static void
ShrinkTabs(Tabset *setPtr, Tab *startPtr, int nTabs, int adjustment)
{
    int x;
    int i;
    Tab *tabPtr;

    x = startPtr->tier;
    while (adjustment > 0) {
	int count;
	int ration;
	Tab *tabPtr;

	count = 0;
	for (tabPtr = startPtr, i = 0; 
	     (tabPtr != NULL) && (i < nTabs) && (adjustment > 0); 
	     tabPtr = NextTab(tabPtr, HIDE), i++) {
	    if (tabPtr != setPtr->plusPtr) {
		count++;
	    }
	}
	ration = adjustment / count;
	if (ration == 0) {
	    ration = 1;
	}
	
	for (tabPtr = startPtr, i = 0; 
	     (tabPtr != NULL) && (i < nTabs) && (adjustment > 0); 
	     tabPtr = NextTab(tabPtr, HIDE), i++) {
	    if (tabPtr != setPtr->plusPtr) {
		adjustment -= ration;
		tabPtr->worldWidth -= ration;
		assert(x == tabPtr->tier);
	    }
	}
    }
    /*
     * Go back and reset the world X-coordinates of the tabs,
     * now that their widths have changed.
     */
    x = 0;
    for (tabPtr = startPtr, i = 0; (i < nTabs) && (tabPtr != NULL); 
	 tabPtr = NextTab(tabPtr, HIDE), i++) {
	tabPtr->worldX = x;
	x += tabPtr->worldWidth + setPtr->gap - setPtr->overlap;
    }
}

static void
GrowTabs(Tabset *setPtr, Tab *startPtr, int nTabs, int adjustment)
{
    int x;
    int i;
    Tab *tabPtr;

    x = startPtr->tier;
    while (adjustment > 0) {
	int count;
	int ration;
	Tab *tabPtr;

	count = 0;
	for (tabPtr = startPtr, i = 0; 
	     (tabPtr != NULL) && (i < nTabs) && (adjustment > 0); 
	     tabPtr = NextTab(tabPtr, HIDE), i++) {
	    if (tabPtr != setPtr->plusPtr) {
		count++;
	    }
	}
	ration = adjustment / count;
	if (ration == 0) {
	    ration = 1;
	}
	
	for (tabPtr = startPtr, i = 0; 
	     (tabPtr != NULL) && (i < nTabs) && (adjustment > 0); 
	     tabPtr = NextTab(tabPtr, HIDE), i++) {
	    if (tabPtr != setPtr->plusPtr) {
		adjustment -= ration;
		tabPtr->worldWidth += ration;
		assert(x == tabPtr->tier);
	    }
	}
    }
    /*
     * Go back and reset the world X-coordinates of the tabs,
     * now that their widths have changed.
     */
    x = 0;
    for (tabPtr = startPtr, i = 0; (i < nTabs) && (tabPtr != NULL); 
	 tabPtr = NextTab(tabPtr, HIDE), i++) {
	tabPtr->worldX = x;
	x += tabPtr->worldWidth + setPtr->gap - setPtr->overlap;
    }
}

static void
AdjustTabSizes(Tabset *setPtr, int nTabs)
{
    int tabsPerTier;
    int total, count, extra, plus;
    Tab *startPtr, *nextPtr;
    Blt_ChainLink link;
    Tab *tabPtr;
    int x, maxWidth;

    tabsPerTier = (nTabs + (setPtr->nTiers - 1)) / setPtr->nTiers;
    x = 0;
    link = NULL;
    maxWidth = 0;
    if (setPtr->reqTabWidth != TABWIDTH_VARIABLE) {
	link = Blt_Chain_FirstLink(setPtr->chain);
	count = 1;
	while (link != NULL) {
	    int i;

	    for (i = 0; i < tabsPerTier; i++) {
		tabPtr = Blt_Chain_GetValue(link);
		if ((tabPtr->flags & HIDE) == 0) {
		    tabPtr->tier = count;
		    tabPtr->worldX = x;
		    x += tabPtr->worldWidth + setPtr->gap - setPtr->overlap;
		    if (x > maxWidth) {
			maxWidth = x;
		    }
		}
		link = Blt_Chain_NextLink(link);
		if (link == NULL) {
		    goto done;
		}
	    }
	    count++;
	    x = 0;
	}
    }
  done:
    /* Add to tab widths to fill out row. */
    if (((nTabs % tabsPerTier) != 0) && 
	(setPtr->reqTabWidth != TABWIDTH_VARIABLE)) {
	return;
    }
    startPtr = NULL;
    count = total = 0;
    plus = 0;
#ifndef notdef
    if (setPtr->plusPtr != NULL) {
	plus += setPtr->inset2 * 2;
    }
#endif
    for (tabPtr = FirstTab(setPtr, HIDE); tabPtr != NULL;
	 tabPtr = NextTab(tabPtr, HIDE)) {
	if (startPtr == NULL) {
	    startPtr = tabPtr;
	}
	count++;
	total += tabPtr->worldWidth + setPtr->gap - setPtr->overlap;
	link = Blt_Chain_NextLink(tabPtr->link);
	if (link != NULL) {
	    nextPtr = Blt_Chain_GetValue(link);
	    if (tabPtr->tier == nextPtr->tier) {
		continue;
	    }
	}
	total += setPtr->overlap;
	
	extra = setPtr->worldWidth - plus - total;
	assert(count > 0);
	if ((extra > 0) && (setPtr->nTiers > 1)) {
	    GrowTabs(setPtr, startPtr, count, extra);
	} else if (extra < 0) {
	    ShrinkTabs(setPtr, startPtr, count, -extra);
	}
	count = total = 0;
	startPtr = NULL;
    }
}

/*
 *
 * tabWidth = textWidth0 + gap + (2 * (pad + outerBW));
 *
 * tabHeight = textHeight0 + 2 * (pad + outerBW) + topMargin;
 *
 */
static void
ComputeLayout(Tabset *setPtr)
{
    int width;
    Blt_ChainLink link;
    int x, extra;
    int nTiers, nTabs;

    setPtr->nTiers = 0;
    setPtr->pageTop = 0;
    setPtr->worldWidth = 1;

    nTabs = ComputeWorldGeometry(setPtr);
    if (nTabs == 0) {
	return;
    }
    /* Reset the pointers to the selected and starting tab. */
    if (setPtr->selectPtr == NULL) {
	link = Blt_Chain_FirstLink(setPtr->chain);
	if (link != NULL) {
	    setPtr->selectPtr = Blt_Chain_GetValue(link);
	}
    }
    if (setPtr->startPtr == NULL) {
	setPtr->startPtr = setPtr->selectPtr;
    }
    if (setPtr->focusPtr == NULL) {
	setPtr->focusPtr = setPtr->selectPtr;
	Blt_SetFocusItem(setPtr->bindTable, setPtr->focusPtr, NULL);
    }

    if (setPtr->side & (SIDE_LEFT | SIDE_RIGHT)) {
        width = Tk_ReqHeight(setPtr->tkwin) - 2 * 
	    (setPtr->inset2 + setPtr->xSelectPad);
    } else {
        width = Tk_ReqWidth(setPtr->tkwin) - (2 * setPtr->inset) -
		setPtr->xSelectPad - setPtr->inset2;
    }
    setPtr->flags &= ~SCROLLING;
    if (setPtr->reqTiers > 1) {
	int total, maxWidth;
	Tab *tabPtr;

	/* Static multiple tier mode. */

	/* Sum tab widths and determine the number of tiers needed. */
	nTiers = 1;
	total = x = 0;
	for (tabPtr = FirstTab(setPtr, HIDE); tabPtr != NULL;
	     tabPtr = NextTab(tabPtr, HIDE)) {
	    if ((x + tabPtr->worldWidth) > width) {
		nTiers++;
		x = 0;
	    }
	    tabPtr->worldX = x;
	    tabPtr->tier = nTiers;
	    extra = tabPtr->worldWidth + setPtr->gap - setPtr->overlap;
	    total += extra, x += extra;
	}
	maxWidth = width;

	if (nTiers > setPtr->reqTiers) {
	    Tab *tabPtr;
	    /*
	     * The tabs do not fit into the requested number of tiers.
             * Go into scrolling mode.
	     */
	    width = ((total + setPtr->tabWidth) / setPtr->reqTiers);
	    x = 0;
	    nTiers = 1;
	    for (tabPtr = FirstTab(setPtr, HIDE); tabPtr != NULL;
		 tabPtr = NextTab(tabPtr, HIDE)) {
		tabPtr->tier = nTiers;
		/*
		 * Keep adding tabs to a tier until we overfill it.
		 */
		tabPtr->worldX = x;
		x += tabPtr->worldWidth + setPtr->gap - setPtr->overlap;
		if (x > width) {
		    nTiers++;
		    if (x > maxWidth) {
			maxWidth = x;
		    }
		    x = 0;
		}
	    }
	    setPtr->flags |= SCROLLING;
	}
	setPtr->worldWidth = maxWidth;
	setPtr->nTiers = nTiers;

	if (nTiers > 1) {
	    AdjustTabSizes(setPtr, nTabs);
	}
	if ((setPtr->flags & (SCROLLING|SCROLL_TABS)) == 
	    (SCROLLING|SCROLL_TABS)) {
	    /* Do you add an offset ? */
	    setPtr->worldWidth += (setPtr->xSelectPad + setPtr->inset2);
	    setPtr->worldWidth += setPtr->overlap;
	} else {
	    if (VPORTWIDTH(setPtr) > 1) {
		setPtr->worldWidth = VPORTWIDTH(setPtr) - 
		    (setPtr->xSelectPad + setPtr->inset2);
	    }
	}
	if (setPtr->selectPtr != NULL) {
	    RenumberTiers(setPtr, setPtr->selectPtr);
	}
    } else {
	Tab *tabPtr;
	/*
	 * Scrollable single tier mode.
	 */
	nTiers = 1;
	x = 0;
	for (tabPtr = FirstTab(setPtr, HIDE); tabPtr != NULL;
	     tabPtr = NextTab(tabPtr, HIDE)) {
	    tabPtr->tier = nTiers;
	    tabPtr->worldX = x;
	    tabPtr->worldY = 0;
	    x += tabPtr->worldWidth + setPtr->gap - setPtr->overlap;
	}
	/* Subtract off the last gap. */
	setPtr->worldWidth = x + setPtr->inset2 - setPtr->gap +
	    setPtr->xSelectPad + setPtr->overlap;
	setPtr->flags |= SCROLLING;
    }
    setPtr->nTiers = nTiers;
    if (nTiers == 1) {
	/* We only need the extra space at top of the widget for selected tab
	 * if there's only one tier. */
	if ((setPtr->flags & (SCROLLING|SCROLL_TABS)) == SCROLLING) {
	    if (VPORTWIDTH(setPtr) > 1) {
		setPtr->worldWidth = VPORTWIDTH(setPtr) - 
		    (setPtr->xSelectPad + setPtr->inset2);
	    }
	    AdjustTabSizes(setPtr, nTabs);
	}
    }
    setPtr->nTiers = nTiers;
    setPtr->pageTop = setPtr->inset + setPtr->inset2 + 
	(setPtr->nTiers * setPtr->tabHeight);
    if (setPtr->nTiers == 1) {
	setPtr->pageTop += setPtr->ySelectPad;
    }
    if (setPtr->side & (SIDE_LEFT | SIDE_RIGHT)) {
	Tab *tabPtr;

	for (tabPtr = FirstTab(setPtr, HIDE); tabPtr != NULL;
	     tabPtr = NextTab(tabPtr, HIDE)) {
	    tabPtr->screenWidth = (short int)setPtr->tabHeight;
	    tabPtr->screenHeight = (short int)tabPtr->worldWidth;
	}
    } else {
	Tab *tabPtr;

	for (tabPtr = FirstTab(setPtr, HIDE); tabPtr != NULL;
	     tabPtr = NextTab(tabPtr, HIDE)) {
	    tabPtr->screenWidth = (short int)tabPtr->worldWidth;
	    tabPtr->screenHeight = (short int)setPtr->tabHeight;
	}
    }
}

static void
ComputeVisibleTabs(Tabset *setPtr)
{
    int nVisibleTabs;
    Tab *tabPtr;

    setPtr->nVisible = 0;
    if (Blt_Chain_GetLength(setPtr->chain) == 0) {
	return;
    }
    nVisibleTabs = 0;
    if (setPtr->flags & SCROLLING) {
	int width, offset;
	Tab *tabPtr;

	/*
	 * Scrollable (single or multiple) tier mode.
	 */
	offset = setPtr->scrollOffset - (setPtr->outerPad + setPtr->xSelectPad);
	width = VPORTWIDTH(setPtr) + setPtr->scrollOffset +
	    2 * setPtr->outerPad;
	for (tabPtr = FirstTab(setPtr, 0); tabPtr != NULL;
	     tabPtr = NextTab(tabPtr, 0)) {
	    if (tabPtr->flags & HIDE) {
		tabPtr->flags &= ~ONSCREEN;
		continue;
	    }
	    if ((tabPtr->worldX >= width) ||
		((tabPtr->worldX + tabPtr->worldWidth) < offset)) {
		tabPtr->flags &= ~ONSCREEN;
	    } else {
		tabPtr->flags |= ONSCREEN;
		nVisibleTabs++;
	    }
	}
    } else {
	Tab *tabPtr;
	/* Static multiple tier mode. */

	for (tabPtr = FirstTab(setPtr, HIDE); tabPtr != NULL;
	     tabPtr = NextTab(tabPtr, HIDE)) {
	    tabPtr->flags |= ONSCREEN;
	    nVisibleTabs++;
	}
    }
    for (tabPtr = FirstTab(setPtr, HIDE); tabPtr != NULL;
	 tabPtr = NextTab(tabPtr, HIDE)) {
	tabPtr->screenX = tabPtr->screenY = -1000;
	if (tabPtr->flags & ONSCREEN) {
	    WorldToScreen(setPtr, tabPtr->worldX, tabPtr->worldY,
		&tabPtr->screenX, &tabPtr->screenY);
	    switch (setPtr->side) {
	    case SIDE_RIGHT:
		tabPtr->screenX -= setPtr->tabHeight;
		break;

	    case SIDE_BOTTOM:
		tabPtr->screenY -= setPtr->tabHeight;
		break;
	    }
	}
    }
    setPtr->nVisible = nVisibleTabs;
    Blt_PickCurrentItem(setPtr->bindTable);
}


static void
Draw3dFolder(Tabset *setPtr, Tab *tabPtr, Drawable drawable, int side,
	     XPoint *points, int nPoints)
{
    int relief, borderWidth;
    Blt_Background bg;

    if (tabPtr == setPtr->selectPtr) {
	bg = GETATTR(tabPtr, selBg);
    } else if ((tabPtr == setPtr->activePtr) || 
	       (tabPtr == setPtr->activeButtonPtr)) {
	bg = GETATTR(tabPtr, activeBg);
    } else if (tabPtr->bg != NULL) {
	bg = tabPtr->bg;
    } else {
	bg = setPtr->defStyle.bg;
    }
    relief = setPtr->defStyle.relief;
    if ((side == SIDE_RIGHT) || (side == SIDE_TOP)) {
	borderWidth = -setPtr->defStyle.borderWidth;
	if (relief == TK_RELIEF_SUNKEN) {
	    relief = TK_RELIEF_RAISED;
	} else if (relief == TK_RELIEF_RAISED) {
	    relief = TK_RELIEF_SUNKEN;
	}
    } else {
	borderWidth = setPtr->defStyle.borderWidth;
    }
    Blt_FillBackgroundPolygon(setPtr->tkwin, drawable, bg, points, nPoints,
	    borderWidth, relief);
}

static void
DrawPerforation(Tabset *setPtr, Tab *tabPtr, Drawable drawable)
{
    int x, y;
    int segmentWidth, max;
    Blt_Background bg, perfBg;

    if ((tabPtr->container != NULL) || (tabPtr->tkwin == NULL)) {
	return;
    }
    WorldToScreen(setPtr, tabPtr->worldX + 2, 
	  tabPtr->worldY + tabPtr->worldHeight + 2, &x, &y);
    x += setPtr->xOffset;
    y += setPtr->yOffset;
    bg = GETATTR(tabPtr, selBg);
    segmentWidth = 3;
    if (setPtr->flags & ACTIVE_PERFORATION) {
	perfBg = GETATTR(tabPtr, activeBg);
    } else {
	perfBg = GETATTR(tabPtr, selBg);
    }	
    if (setPtr->side & (SIDE_TOP|SIDE_BOTTOM)) {
	XPoint points[2];

	points[0].x = x;
	points[0].y = points[1].y = y;
	max = tabPtr->screenX + setPtr->xOffset + tabPtr->screenWidth - 2;
	Blt_FillBackgroundRectangle(setPtr->tkwin, drawable, perfBg, x-2, y-4, 
		tabPtr->screenWidth, 8, 0, TK_RELIEF_FLAT);
	while (points[0].x < max) {
	    points[1].x = points[0].x + segmentWidth;
	    if (points[1].x > max) {
		points[1].x = max;
	    }
	    Blt_DrawBackgroundPolygon(setPtr->tkwin, drawable, bg, points, 
		2, 1, TK_RELIEF_RAISED);
	    points[0].x += 2 * segmentWidth;
	}
    } else {
	XPoint points[2];

	points[0].x = points[1].x = x;
	points[0].y = y;
	max  = tabPtr->screenY + tabPtr->screenHeight - 2;
	Blt_FillBackgroundRectangle(setPtr->tkwin, drawable, perfBg,
	       x - 4, y - 2, 8, tabPtr->screenHeight, 0, TK_RELIEF_FLAT);
	while (points[0].y < max) {
	    points[1].y = points[0].y + segmentWidth;
	    if (points[1].y > max) {
		points[1].y = max;
	    }
	    Blt_DrawBackgroundPolygon(setPtr->tkwin, drawable, bg, points, 
		2, 1, TK_RELIEF_RAISED);
	    points[0].y += 2 * segmentWidth;
	}
    }
}

#define NextPoint(px, py) \
	pointPtr->x = (px), pointPtr->y = (py), pointPtr++, nPoints++
#define EndPoint(px, py) \
	pointPtr->x = (px), pointPtr->y = (py), nPoints++

#define BottomLeft(px, py) \
	NextPoint((px) + setPtr->corner, (py)), \
	NextPoint((px), (py) - setPtr->corner)

#define TopLeft(px, py) \
	NextPoint((px), (py) + setPtr->corner), \
	NextPoint((px) + setPtr->corner, (py))

#define TopRight(px, py) \
	NextPoint((px) - setPtr->corner, (py)), \
	NextPoint((px), (py) + setPtr->corner)

#define BottomRight(px, py) \
	NextPoint((px), (py) - setPtr->corner), \
	NextPoint((px) - setPtr->corner, (py))

/*
 * From the left edge:
 *
 *   |a|b|c|d|e| f |d|e|g|h| i |h|g|e|d|f|    j    |e|d|c|b|a|
 *
 *	a. highlight ring
 *	b. tabset 3D border
 *	c. outer gap
 *      d. page border
 *	e. page corner
 *	f. gap + select pad
 *	g. label pad x (worldX)
 *	h. internal pad x
 *	i. label width
 *	j. rest of page width
 *
 *  worldX, worldY
 *          |
 *          |
 *          * 4+ . . +5
 *          3+         +6
 *           .         .
 *           .         .
 *   1+. . .2+         +7 . . . .+8
 * 0+                              +9
 *  .                              .
 *  .                              .
 *13+                              +10
 *  12+-------------------------+11
 *
 */
static void
DrawFolder(Tabset *setPtr, Tab *tabPtr, Drawable drawable)
{
    XPoint points[16];
    XPoint *pointPtr;
    int width, height;
    int left, bottom, right, top, yBot, yTop;
    int x, y;
    int i;
    int nPoints;
    int ySelectPad;

    width = VPORTWIDTH(setPtr);
    height = VPORTHEIGHT(setPtr);

    x = tabPtr->worldX;
    y = tabPtr->worldY;

    nPoints = 0;
    pointPtr = points;

    ySelectPad = 0;
    if (setPtr->nTiers == 1) {
	ySelectPad = setPtr->ySelectPad;
    }

    /* Remember these are all world coordinates. */
    /*
     *          x,y
     *           |
     *           * + . . + 
     *           +         +
     *           .         .
     *  left     .         .
     *    +. . .2+---------+7 . . . .+8
     * 0+                              +9
     * x	Left side of tab.
     * y	Top of tab.
     * yTop	Top of folder.
     * yBot	Bottom of the tab.
     * left	Left side of the folder.
     * right	Right side of the folder.
     * top	Top of folder.
     * bottom	Bottom of folder.
     */
    left = setPtr->scrollOffset - setPtr->xSelectPad;
    right = left + width;
    yTop = y + tabPtr->worldHeight;
    yBot = setPtr->pageTop - (setPtr->inset + ySelectPad) + 1;
    top = yBot - setPtr->inset2 /* - 4 */;

    bottom = MAX(height - ySelectPad, yBot);
    if (setPtr->pageHeight == 0) {
	top = yBot - 1;
	yTop = bottom - setPtr->corner;
	yBot = bottom;
    } 
    if (tabPtr != setPtr->selectPtr) {

	/*
	 * Case 1: Unselected tab
	 *
	 * * 2+ . . +3
	 * 1+         +4
	 *  .         .
	 * 0+-------- +5
	 *
	 */
	
	if (setPtr->flags & SLANT_LEFT) {
	    NextPoint(x, yBot);
	    NextPoint(x, yTop);
	    NextPoint(x + setPtr->tabHeight, y);
	} else {
	    NextPoint(x, yBot);
	    TopLeft(x, y);
	}
	x += tabPtr->worldWidth;
	if (setPtr->flags & SLANT_RIGHT) {
	    NextPoint(x - setPtr->tabHeight, y);
	    NextPoint(x, yTop);
	    NextPoint(x, yBot);
	} else {
	    TopRight(x, y);
	    NextPoint(x, yBot);
	}
    } else if ((tabPtr->flags & ONSCREEN) == 0) {
	/*
	 * Case 2: Selected tab not visible in viewport.  Draw folder only.
	 *
	 * * 2+ . . +3
	 * 1+         +4
	 *  .         .
	 * 0+-------- +5
	 */

	TopLeft(left, top);
	TopRight(right, top);
	NextPoint(right, bottom);
	NextPoint(left, bottom);
    } else {
	int flags;
	int tabWidth;

	x -= setPtr->xSelectPad;
	y -= setPtr->ySelectPad;
	tabWidth = tabPtr->worldWidth + 2 * setPtr->xSelectPad;

#define CLIP_NONE	0
#define CLIP_LEFT	(1<<0)
#define CLIP_RIGHT	(1<<1)
	flags = 0;
	if (x < left) {
	    flags |= CLIP_LEFT;
	}
	if ((x + tabWidth) > right) {
	    flags |= CLIP_RIGHT;
	}
	switch (flags) {
	case CLIP_NONE:

	    /*
	     *  worldX, worldY
	     *          |
	     *          * 4+ . . +5
	     *          3+         +6
	     *           .         .
	     *           .         .
	     *   1+. . .2+---------+7 . . . .+8
	     * 0+                              +9
	     *  .                              .
	     *  .                              .
	     *  .                              .
	     *11+ . . . . . . . . . . . . .  . +10
	     */

	    if (x < (left + setPtr->corner)) {
		NextPoint(left, top);
	    } else {
		TopLeft(left, top);
	    }
	    if (setPtr->flags & SLANT_LEFT) {
		NextPoint(x, yTop);
		NextPoint(x + setPtr->tabHeight + ySelectPad, y);
	    } else {
		NextPoint(x, top);
		TopLeft(x, y);
	    }
	    x += tabWidth;
	    if (setPtr->flags & SLANT_RIGHT) {
		NextPoint(x - setPtr->tabHeight - ySelectPad, y);
		NextPoint(x, yTop);
	    } else {
		TopRight(x, y);
		NextPoint(x, top);
	    }
	    if (x > (right - setPtr->corner)) {
		NextPoint(right, top + setPtr->corner);
	    } else {
		TopRight(right, top);
	    }
	    NextPoint(right, bottom);
	    NextPoint(left, bottom);
	    break;

	case CLIP_LEFT:

	    /*
	     *  worldX, worldY
	     *          |
	     *          * 4+ . . +5
	     *          3+         +6
	     *           .         .
	     *           .         .
	     *          2+--------+7 . . . .+8
	     *            1+ . . . +0          +9
	     *                     .           .
	     *                     .           .
	     *                     .           .
	     *                   11+ . . . . . +10
	     */

	    NextPoint(left, yBot);
	    if (setPtr->flags & SLANT_LEFT) {
		NextPoint(x, yBot);
		NextPoint(x, yTop);
		NextPoint(x + setPtr->tabHeight + ySelectPad, y);
	    } else {
		BottomLeft(x, yBot);
		TopLeft(x, y);
	    }

	    x += tabWidth;
	    if (setPtr->flags & SLANT_RIGHT) {
		NextPoint(x - setPtr->tabHeight - ySelectPad, y);
		NextPoint(x, yTop);
		NextPoint(x, top);
	    } else {
		TopRight(x, y);
		NextPoint(x, top);
	    }
	    if (x > (right - setPtr->corner)) {
		NextPoint(right, top + setPtr->corner);
	    } else {
		TopRight(right, top);
	    }
	    NextPoint(right, bottom);
	    NextPoint(left, bottom);
	    break;

	case CLIP_RIGHT:

	    /*
	     *              worldX, worldY
	     *                     |
	     *                     * 7+ . . +8
	     *                     6+         +9
	     *                      .         .
	     *                      .         .
	     *           4+ . . . .5+---------+10
	     *         3+          0+ . . . +11
	     *          .           .
	     *          .           .
	     *          .           .
	     *         2+ . . . . . +1
	     */

	    NextPoint(right, yBot);
	    NextPoint(right, bottom);
	    NextPoint(left, bottom);
	    if (x < (left + setPtr->corner)) {
		NextPoint(left, top);
	    } else {
		TopLeft(left, top);
	    }
	    NextPoint(x, top);

	    if (setPtr->flags & SLANT_LEFT) {
		NextPoint(x, yTop);
		NextPoint(x + setPtr->tabHeight + ySelectPad, y);
	    } else {
		TopLeft(x, y);
	    }
	    x += tabWidth;
	    if (setPtr->flags & SLANT_RIGHT) {
		NextPoint(x - setPtr->tabHeight - ySelectPad, y);
		NextPoint(x, yTop);
		NextPoint(x, yBot);
	    } else {
		TopRight(x, y);
		BottomRight(x, yBot);
	    }
	    break;

	case (CLIP_LEFT | CLIP_RIGHT):

	    /*
	     *  worldX, worldY
	     *     |
	     *     * 4+ . . . . . . . . +5
	     *     3+                     +6
	     *      .                     .
	     *      .                     .
	     *     1+---------------------+7
	     *       2+ 0+          +9 .+8
	     *           .          .
	     *           .          .
	     *           .          .
	     *         11+ . . . . .+10
	     */

	    NextPoint(left, yBot);
	    if (setPtr->flags & SLANT_LEFT) {
		NextPoint(x, yBot);
		NextPoint(x, yTop);
		NextPoint(x + setPtr->tabHeight + ySelectPad, y);
	    } else {
		BottomLeft(x, yBot);
		TopLeft(x, y);
	    }
	    x += tabPtr->worldWidth;
	    if (setPtr->flags & SLANT_RIGHT) {
		NextPoint(x - setPtr->tabHeight - ySelectPad, y);
		NextPoint(x, yTop);
		NextPoint(x, yBot);
	    } else {
		TopRight(x, y);
		BottomRight(x, yBot);
	    }
	    NextPoint(right, yBot);
	    NextPoint(right, bottom);
	    NextPoint(left, bottom);
	    break;
	}
    }
    EndPoint(points[0].x, points[0].y);
    for (i = 0; i < nPoints; i++) {
	WorldToScreen(setPtr, points[i].x, points[i].y, &x, &y);
	points[i].x = x + setPtr->xOffset;
	points[i].y = y + setPtr->yOffset;
    }
    Draw3dFolder(setPtr, tabPtr, drawable, setPtr->side, points, nPoints);
    DrawLabel(setPtr, tabPtr, drawable);
    if (tabPtr->container != NULL) {
	XRectangle rect;

	/* Draw a rectangle covering the spot representing the window  */
	GetWindowRectangle(tabPtr, setPtr->tkwin, FALSE, &rect);
	XFillRectangles(setPtr->display, drawable, tabPtr->backGC,
	    &rect, 1);
    }
}

static void
DrawOuterBorders(Tabset *setPtr, Drawable drawable)
{
    /*
     * Draw 3D border just inside of the focus highlight ring.  We draw the
     * border even if the relief is flat so that any tabs that hang over the
     * edge will be clipped.
     */
    if (setPtr->borderWidth > 0) {
	Blt_DrawBackgroundRectangle(setPtr->tkwin, drawable, setPtr->bg,
		setPtr->highlightWidth + setPtr->xOffset, 
		setPtr->highlightWidth + setPtr->yOffset,
		Tk_Width(setPtr->tkwin) - 2 * setPtr->highlightWidth,
		Tk_Height(setPtr->tkwin) - 2 * setPtr->highlightWidth,
		setPtr->borderWidth, setPtr->relief);
    }
    /* Draw focus highlight ring. */
    if (setPtr->highlightWidth > 0) {
	XColor *color;
	GC gc;

	color = (setPtr->flags & FOCUS)
	    ? setPtr->highlightColor : setPtr->highlightBg;
	gc = Tk_GCForColor(color, drawable);
	Tk_DrawFocusHighlight(setPtr->tkwin, gc, setPtr->highlightWidth, 
	      drawable);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * DisplayTabset --
 *
 * 	This procedure is invoked to display the widget.
 *
 *      Recomputes the layout of the widget if necessary. This is necessary if
 *      the world coordinate system has changed.  Sets the vertical and
 *      horizontal scrollbars.  This is done here since the window width and
 *      height are needed for the scrollbar calculations.
 *
 * Results:
 *	None.
 *
 * Side effects:
 * 	The widget is redisplayed.
 *
 *---------------------------------------------------------------------------
 */
static void
DisplayTabset(ClientData clientData)	/* Information about widget. */
{
    Tabset *setPtr = clientData;
    Pixmap pixmap;
    int width, height;
    int redrawAll;
    
    redrawAll = setPtr->flags & REDRAW_ALL;
    setPtr->flags &= ~(REDRAW_PENDING | REDRAW_ALL);
    if (setPtr->tkwin == NULL) {
	return;				/* Window has been destroyed. */
    }
    if (setPtr->flags & LAYOUT_PENDING) {
	ComputeLayout(setPtr);
	setPtr->flags &= ~LAYOUT_PENDING;
    }
    if ((setPtr->reqHeight == 0) || (setPtr->reqWidth == 0)) {
	width = height = 0;
	if (setPtr->side & (SIDE_LEFT | SIDE_RIGHT)) {
	    height = setPtr->worldWidth;
	} else {
	    width = setPtr->worldWidth;
	}
	if (setPtr->reqWidth > 0) {
	    width = setPtr->reqWidth;
	} else if (setPtr->pageWidth > 0) {
	    width = setPtr->pageWidth;
	}
	if (setPtr->reqHeight > 0) {
	    height = setPtr->reqHeight;
	} else if (setPtr->pageHeight > 0) {
	    height = setPtr->pageHeight;
	}
	if (setPtr->side & (SIDE_LEFT | SIDE_RIGHT)) {
#ifdef notdef
	    width += setPtr->pageTop + setPtr->inset + setPtr->inset2;
	    height += setPtr->inset + setPtr->inset2;
#else 
	    width += 2 * setPtr->inset + setPtr->pageTop + setPtr->inset2;
	    height += 2 * setPtr->inset;
#endif
	} else {
	    height += 2 * setPtr->inset + setPtr->pageTop + setPtr->inset2;
	    width += 2 * setPtr->inset;
	}
	if ((Tk_ReqWidth(setPtr->tkwin) != width) ||
	    (Tk_ReqHeight(setPtr->tkwin) != height)) {
	    Tk_GeometryRequest(setPtr->tkwin, width, height);
	}
    }
    if (setPtr->flags & SCROLL_PENDING) {
	width = VPORTWIDTH(setPtr);
	setPtr->scrollOffset = Blt_AdjustViewport(setPtr->scrollOffset,
		setPtr->worldWidth, width, setPtr->scrollUnits, 
		BLT_SCROLL_MODE_HIERBOX);
	if (setPtr->scrollCmdObjPtr != NULL) {
	    Blt_UpdateScrollbar(setPtr->interp, setPtr->scrollCmdObjPtr,
		setPtr->scrollOffset, setPtr->scrollOffset + width,
		setPtr->worldWidth);
	}
	ComputeVisibleTabs(setPtr);
	setPtr->flags &= ~SCROLL_PENDING;
    }
    if (!Tk_IsMapped(setPtr->tkwin)) {
	return;
    }
    width = Tk_Width(setPtr->tkwin);
    height = Tk_Height(setPtr->tkwin);
    setPtr->xOffset = setPtr->yOffset = 0;  /* Offset of the window origin
					     * from the pixmap created
					     * below. */
    if (!redrawAll) {
	/* Create a pixmap only the size of the tab region. This saves the X
	 * server from rendering the entire folder background polygon each
	 * time. This is good for scrolling and active tabs. */
	switch (setPtr->side) {
	case SIDE_TOP:
	    height = setPtr->pageTop + setPtr->inset + setPtr->inset2; 
	    break;
	case SIDE_BOTTOM:
	    setPtr->yOffset = setPtr->pageTop - height;
	    height = setPtr->pageTop + setPtr->inset + setPtr->inset2; 
	    break;
	case SIDE_LEFT:
	    width = setPtr->pageTop + setPtr->inset + setPtr->inset2; 
	    break;
	case SIDE_RIGHT:
	    setPtr->xOffset = setPtr->pageTop - width;
	    width = setPtr->pageTop + setPtr->inset + setPtr->inset2; 
	    break;
	}
    }
    pixmap = Tk_GetPixmap(setPtr->display, Tk_WindowId(setPtr->tkwin),
	width, height, Tk_Depth(setPtr->tkwin));
    /*
     * Clear the background either by tiling a pixmap or filling with a solid
     * color. Tiling takes precedence.
     */
    Blt_FillBackgroundRectangle(setPtr->tkwin, pixmap, setPtr->bg, 
	setPtr->xOffset, setPtr->yOffset, 
	Tk_Width(setPtr->tkwin), Tk_Height(setPtr->tkwin), 
	0, TK_RELIEF_FLAT);

    if (setPtr->nVisible > 0) {
	int i;
	Tab *tabPtr;
	Blt_ChainLink link;

	link = setPtr->startPtr->link;
	for (i = 0; i < Blt_Chain_GetLength(setPtr->chain); i++) {
	    link = Blt_Chain_PrevLink(link);
	    if (link == NULL) {
		link = Blt_Chain_LastLink(setPtr->chain);
	    }
	    tabPtr = Blt_Chain_GetValue(link);
	    if ((tabPtr != setPtr->selectPtr) && (tabPtr->flags & ONSCREEN)) {
		DrawFolder(setPtr, tabPtr, pixmap);
	    }
	}
	DrawFolder(setPtr, setPtr->selectPtr, pixmap);
	if (setPtr->flags & TEAROFF) {
	    DrawPerforation(setPtr, setPtr->selectPtr, pixmap);
	}

	if ((setPtr->selectPtr->tkwin != NULL) &&
	    (setPtr->selectPtr->container == NULL)) {
	    XRectangle rect;

	    GetWindowRectangle(setPtr->selectPtr, setPtr->tkwin, FALSE, &rect);
	    ArrangeWindow(setPtr->selectPtr->tkwin, &rect, 0);
	}
    }
    DrawOuterBorders(setPtr, pixmap);
    XCopyArea(setPtr->display, pixmap, Tk_WindowId(setPtr->tkwin),
	setPtr->highlightGC, 0, 0, width, height, -setPtr->xOffset, 
	      -setPtr->yOffset);
    Tk_FreePixmap(setPtr->display, pixmap);
}

/*
 * From the left edge:
 *
 *   |a|b|c|d|e| f |d|e|g|h| i |h|g|e|d|f|    j    |e|d|c|b|a|
 *
 *	a. highlight ring
 *	b. tabset 3D border
 *	c. outer gap
 *      d. page border
 *	e. page corner
 *	f. gap + select pad
 *	g. label pad x (worldX)
 *	h. internal pad x
 *	i. label width
 *	j. rest of page width
 *
 *  worldX, worldY
 *          |
 *          |
 *          * 4+ . . +5
 *          3+         +6
 *           .         .
 *           .         .
 *   1+. . .2+         +7 . . . .+8
 * 0+                              +9
 *  .                              .
 *  .                              .
 *  .                              .
 *11+------------------------------+10
 *
 */
static void
DisplayTearoff(ClientData clientData)
{
    Tabset *setPtr;
    Tab *tabPtr;
    Drawable drawable;
    XPoint points[16];
    XPoint *pointPtr;
    int width, height;
    int left, bottom, right, top;
    int x, y;
    int nPoints;
    Tk_Window tkwin;
    Tk_Window parent;
    XRectangle rect;

    tabPtr = clientData;
    if (tabPtr == NULL) {
	return;
    }
    tabPtr->flags &= ~TEAROFF_REDRAW;
    setPtr = tabPtr->setPtr;
    if (setPtr->tkwin == NULL) {
	return;
    }
    tkwin = tabPtr->container;
    drawable = Tk_WindowId(tkwin);

    Blt_FillBackgroundRectangle(tkwin, drawable, setPtr->bg, 0, 0, 
	Tk_Width(tkwin), Tk_Height(tkwin), 0, TK_RELIEF_FLAT);

    width = Tk_Width(tkwin) - 2 * setPtr->inset;
    height = Tk_Height(tkwin) - 2 * setPtr->inset;
    x = setPtr->inset + setPtr->gap + setPtr->corner;
    y = setPtr->inset;

    left = setPtr->inset;
    right = setPtr->inset + width;
    top = setPtr->inset + setPtr->corner + setPtr->xSelectPad;
    bottom = setPtr->inset + height;

    /*
     *  worldX, worldY
     *          |
     *          * 4+ . . +5
     *          3+         +6
     *           .         .
     *           .         .
     *   1+. . .2+         +7 . . . .+8
     * 0+                              +9
     *  .                              .
     *  .                              .
     *  .                              .
     *11+------------------------------+10
     */

    nPoints = 0;
    pointPtr = points;

    TopLeft(left, top);
    NextPoint(x, top);
    TopLeft(x, y);
    x += tabPtr->worldWidth;
    TopRight(x, y);
    NextPoint(x, top);
    TopRight(right, top);
    NextPoint(right, bottom);
    NextPoint(left, bottom);
    EndPoint(points[0].x, points[0].y);
    Draw3dFolder(setPtr, tabPtr, drawable, SIDE_TOP, points, nPoints);

    parent = (tabPtr->container == NULL) ? setPtr->tkwin : tabPtr->container;
    GetWindowRectangle(tabPtr, parent, TRUE, &rect);
    ArrangeWindow(tabPtr->tkwin, &rect, TRUE);

    /* Draw 3D border. */
    if ((setPtr->borderWidth > 0) && (setPtr->relief != TK_RELIEF_FLAT)) {
	Blt_DrawBackgroundRectangle(tkwin, drawable, setPtr->bg, 0, 0,
	    Tk_Width(tkwin), Tk_Height(tkwin), setPtr->borderWidth,
	    setPtr->relief);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * TabsetCmd --
 *
 * 	This procedure is invoked to process the "tabset" command.  See the
 * 	user documentation for details on what it does.
 *
 * Results:
 *	A standard TCL result.
 *
 * Side effects:
 *	See the user documentation.
 *
 *---------------------------------------------------------------------------
 */
static Blt_OpSpec tabsetOps[] =
{
    {"activate",    2, ActivateOp,    3, 3, "tab",},
    {"add",         2, AddOp,         2, 0, "?label? ?option-value..?",},
    {"bind",        2, BindOp,	      2, 5, "tab ?sequence command?",},
    {"button",      2, ButtonOp,      2, 0, "args",},
    {"cget",        2, CgetOp,	      3, 3, "option",},
    {"close",       2, CloseOp,       3, 3, "tab",},
    {"configure",   2, ConfigureOp,   2, 0, "?option value?...",},
    {"delete",      2, DeleteOp,      2, 0, "?tab...?",},
    {"dockall",     2, DockallOp,     2, 2, "" }, 
    {"exists",      3, ExistsOp,      3, 3, "tab",},
    {"extents",     1, ExtentsOp,     3, 3, "tab",},
    {"focus",       1, FocusOp,	      2, 3, "?tab?",},
    {"highlight",   1, ActivateOp,    3, 3, "tab",},
    {"id",          2, IdOp,	      3, 3, "tab",},
    {"index",       3, IndexOp,	      3, 3, "tab",},
    {"insert",      3, InsertOp,      3, 0, "position ?option value?",},
    {"invoke",      3, InvokeOp,      3, 3, "tab",},
    {"move",        1, MoveOp,	      5, 5, "tab after|before tab",},
    {"names",       2, NamesOp,       2, 0, "?pattern...?",},
    {"nearest",     2, NearestOp,     4, 4, "x y",},
    {"perforation", 1, PerforationOp, 2, 0, "args",},
    {"scan",        2, ScanOp,	      5, 5, "dragto|mark x y",},
    {"see",         3, SeeOp,	      3, 3, "tab",},
    {"select",      3, SelectOp,      3, 3, "tab",},
    {"size",        2, SizeOp,	      2, 2, "",},
    {"tab",         2, TabOp,	      2, 0, "oper args",},
    {"tag",         2, TagOp,	      2, 0, "oper args",},
    {"tearoff",     2, TearoffOp,     3, 4, "tab ?parent?",},
    {"view",        1, ViewOp,	      2, 5, 
	"?moveto fract? ?scroll number what?",},
};

static int nTabsetOps = sizeof(tabsetOps) / sizeof(Blt_OpSpec);

static int
TabsetInstCmd(
    ClientData clientData,		/* Information about the widget. */
    Tcl_Interp *interp,			/* Interpreter to report errors. */
    int objc,				/* # of arguments. */
    Tcl_Obj *const *objv)		/* Vector of argument strings. */
{
    TabsetCmdProc *proc;
    Tabset *setPtr = clientData;
    int result;

    proc = Blt_GetOpFromObj(interp, nTabsetOps, tabsetOps, BLT_OP_ARG1, 
	objc, objv, 0);
    if (proc == NULL) {
	return TCL_ERROR;
    }
    Tcl_Preserve(setPtr);
    result = (*proc) (setPtr, interp, objc, objv);
    Tcl_Release(setPtr);
    return result;
}

/*
 *---------------------------------------------------------------------------
 *
 * TabsetInstDeletedCmd --
 *
 *	This procedure can be called if the window was destroyed (tkwin will
 *	be NULL) and the command was deleted automatically.  In this case, we
 *	need to do nothing.
 *
 *	Otherwise this routine was called because the command was deleted.
 *	Then we need to clean-up and destroy the widget.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The widget is destroyed.
 *
 *---------------------------------------------------------------------------
 */
static void
TabsetInstDeletedCmd(ClientData clientData)
{
    Tabset *setPtr = clientData;

    if (setPtr->tkwin != NULL) {
	Tk_Window tkwin;

	tkwin = setPtr->tkwin;
	setPtr->tkwin = NULL;
	Tk_DestroyWindow(tkwin);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * TabsetCmd --
 *
 * 	This procedure is invoked to process the TCL command that corresponds
 * 	to a widget managed by this module. See the user documentation for
 * 	details on what it does.
 *
 * Results:
 *	A standard TCL result.
 *
 * Side Effects:
 *	See the user documentation.
 *
 *
 *	blt::tabset pathName ?option value?...
 *
 *---------------------------------------------------------------------------
 */
/* ARGSUSED */
static int
TabsetCmd(
    ClientData clientData,	/* Main window associated with interpreter. */
    Tcl_Interp *interp,		/* Current interpreter. */
    int objc,			/* Number of arguments. */
    Tcl_Obj *const *objv)	/* Argument strings. */
{
    Tabset *setPtr;
    Tk_Window tkwin;
    unsigned int mask;
    Tcl_CmdInfo cmdInfo;
    const char *pathName;

    if (objc < 2) {
	Tcl_AppendResult(interp, "wrong # args: should be \"", 
		Tcl_GetString(objv[0]), " pathName ?option value?...\"", 
		(char *)NULL);
	return TCL_ERROR;
    }
    pathName = Tcl_GetString(objv[1]);
    tkwin = Tk_CreateWindowFromPath(interp, Tk_MainWindow(interp), pathName,
	(char *)NULL);
    if (tkwin == NULL) {
	return TCL_ERROR;
    }
    /*
     * Try to invoke a procedure to initialize various bindings on tabs.
     * Source the file containing the procedure now if the procedure isn't
     * currently defined.  We deferred this to now so that the user could set
     * the variable "blt_library" within the script.
     */
    if (!Tcl_GetCommandInfo(interp, "::blt::Tabset::Init", &cmdInfo)) {
	static char initCmd[] = 
	    "source [file join $blt_library tabset.tcl]";
 
	if (Tcl_GlobalEval(interp, initCmd) != TCL_OK) {
	    char info[200];

	    sprintf_s(info, 200, "\n    (while loading bindings for %s)", 
		Tcl_GetString(objv[0]));
	    Tcl_AddErrorInfo(interp, info);
	    Tk_DestroyWindow(setPtr->tkwin);
	    return TCL_ERROR;
	}
    }
    setPtr = NewTabset(interp, tkwin);
    if (ConfigureTabset(interp, setPtr, objc - 2, objv + 2, 0) != TCL_OK) {
	Tk_DestroyWindow(setPtr->tkwin);
	return TCL_ERROR;
    }
    if (ConfigureButton(interp, setPtr, 0, NULL, 0) != TCL_OK) {
	Tk_DestroyWindow(setPtr->tkwin);
	return TCL_ERROR;
    }
    mask = (ExposureMask | StructureNotifyMask | FocusChangeMask);
    Tk_CreateEventHandler(tkwin, mask, TabsetEventProc, setPtr);
    setPtr->cmdToken = Tcl_CreateObjCommand(interp, pathName, TabsetInstCmd, 
	setPtr, TabsetInstDeletedCmd);
	
    if (Tcl_VarEval(interp, "::blt::Tabset::Init ", 
		Tk_PathName(setPtr->tkwin), (char *)NULL) != TCL_OK) {
	Tk_DestroyWindow(setPtr->tkwin);
	return TCL_ERROR;
    }
    Tcl_SetStringObj(Tcl_GetObjResult(interp), pathName, -1);
    return TCL_OK;
}

int
Blt_TabsetCmdInitProc(Tcl_Interp *interp)
{
    static Blt_InitCmdSpec cmdSpecs[2] = { 
	{ "tabset", TabsetCmd, },
	{ "tabnotebook", TabsetCmd, },
    };
    return Blt_InitCmds(interp, "::blt", cmdSpecs, 2);
}

#endif /* NO_TABSET */

static GadgetRegion
RotateRegion(Tab *tabPtr, int x, int y, unsigned int w, unsigned int h)
{
    Tabset *setPtr;
    GadgetRegion r;

    setPtr = tabPtr->setPtr;
    if (setPtr->quad == ROTATE_90) {
	r.x = y;
	r.y = tabPtr->rotWidth - (x + w);
	r.w = h;
	r.h = w;
    } else if (setPtr->quad == ROTATE_270) {
	r.x = tabPtr->rotHeight - (y + h);
	r.y = x;
	r.w = h;
	r.h = w;
    } else {
	r.x = x;
	r.y = y;
	r.w = w, r.h = h;
    }
    return r;
}

/*
 * Computes the location and dimensions of the 
 *	
 *	1. icon 
 *	2. text or image
 *	3. close button.
 *	4. focus rectangle
 *	5. 
 *   x,y
 *    |1|2|3| 4 |5|  4  |3|2|1|
 *
 *   1. tab borderwidth
 *   2. corner offset or slant
 *   3. label pad
 *   4. label or text width
 *   5. pad
 */
static void
ComputeLabelOffsets(Tabset *setPtr, Tab *tabPtr)
{
    int w, h;
    int x1, x2, y1, y2;
    int tx, ty, tw, th, maxLength;
    int ix, iy, iw, ih;
    int fx, fy, fw, fh;
    int worldWidth, worldHeight, labelWidth;
    int xSelPad, ySelPad;

    worldWidth = tabPtr->worldWidth;
    worldHeight = setPtr->tabHeight + setPtr->inset2;

    /* The world width of tab has to be fixed to remove the extra padding for
     * the slant/corner and the rotation based upon the side. */
    worldWidth -= (setPtr->flags & SLANT_LEFT) 
	? tabPtr->worldHeight : setPtr->inset2;
    worldWidth -= (setPtr->flags & SLANT_RIGHT) 
	? tabPtr->worldHeight : setPtr->inset2;
    
    xSelPad = ySelPad = 0;
    if (tabPtr == setPtr->selectPtr) {
	worldWidth += setPtr->xSelectPad;
	xSelPad = setPtr->xSelectPad / 2;
	ySelPad = setPtr->ySelectPad / 2;
    }
    if ((setPtr->quad == ROTATE_90) || (setPtr->quad == ROTATE_270)) {
	SWAP(worldWidth, worldHeight);
    }
    if (setPtr->side & (SIDE_RIGHT | SIDE_LEFT)) {
	SWAP(worldWidth, worldHeight);
    } 
    tabPtr->rotWidth  = worldWidth;
    tabPtr->rotHeight = worldHeight;

    x1 = y1 = 0;
    x2 = x1 + tabPtr->rotWidth;
    y2 = y1 + tabPtr->rotHeight;

#if DEBUG1
    fprintf(stderr, "ComputeLabelOffset: -1. tab=%s x1=%d,y1=%d,x2=%d,y2=%d,w=%d,h=%d, w0=%d h0=%d\n",
		tabPtr->text, x1, y1, x2, y2, w, h, tabPtr->rotWidth, 
		tabPtr->rotHeight);
#endif

    /* Compute the positions of the tab in world coordinates (rotated 0
     * degrees). */
    
    /* Start with the upper/left and lower/right corners of the label inside of
     * the tab.  This excludes the tab's borderwidth. */
    
    /* This is the available area for the label. */
    w = x2 - x1;
    h = y2 - y1;

    if ((w < 0) || (h < 0)) {
	return;
    }
#if DEBUG1
    fprintf(stderr, "ComputeLabelOffset: 0. tab=%s x1=%d,y1=%d,x2=%d,y2=%d,w=%d,h=%d, w0=%d h0=%d\n",
		tabPtr->text, x1, y1, x2, y2, w, h, tabPtr->rotWidth, 
		tabPtr->rotHeight);
#endif

    /* Focus dashed rectangle. */
    {
	fx = x1;
	fy = y1;
	fw = ODD(w);
	fh = ODD(h);
	tabPtr->focusRegion = RotateRegion(tabPtr, fx, fy, fw, fh);
    }

    /* Close button geometry. */
    if ((setPtr->plusPtr != tabPtr) && (setPtr->flags & CLOSE_NEEDED)) {
	int bx, by, bw, bh;

	/* Close button is always located on the right side of the tab,
	 * it's height is centered. */
	bx = x2 - CLOSE_WIDTH - setPtr->closeButton.borderWidth;
	by = y1;
	bw = CLOSE_WIDTH;
	bh = CLOSE_HEIGHT;
	if (h > bh) {
	    by += (h - bh) / 2;
	} else {
	    bh = h;
	}
	if (w < bw) {
	    bw = w;
	}
	if ((setPtr->quad == ROTATE_0) || (setPtr->quad == ROTATE_180)) {
	    bx += 2 * xSelPad;
	}
	tabPtr->buttonRegion = RotateRegion(tabPtr, bx, by, bw, bh);
#if DEBUG1
	fprintf(stderr, "ComputeLabelOffset: button tab=%s x=%d,y=%d,w=%d,h=%d => x=%d,y=%d w=%d,h=%d\n",
		tabPtr->text, bx, by, bw, bh, tabPtr->buttonRegion.x, 
		tabPtr->buttonRegion.y, tabPtr->buttonRegion.width, 
		tabPtr->buttonRegion.height);
#endif
	x2 -= bw + LABEL_PAD + 2 * setPtr->closeButton.borderWidth;
    }

    /* Label/image and icon. Their positioning is related because of
     * the -iconposition option.  */

    w = x2 - x1;
    h = y2 - y1;

    if (tabPtr->icon != NULL) {
	iw = IconWidth(tabPtr->icon);
	ih = IconHeight(tabPtr->icon);
    } else {
	iw = ih = 0;
    }
    if (iw > w) {
	iw = w;
    }
    w = x2 - x1;
    h = y2 - y1;
    
    labelWidth = tabPtr->labelWidth0;
    if ((tabPtr != setPtr->plusPtr) && (setPtr->flags & CLOSE_NEEDED)) {
	labelWidth -= CLOSE_WIDTH + 2 * setPtr->closeButton.borderWidth;
    }
    if (w > labelWidth) {
	if (setPtr->justify == TK_JUSTIFY_CENTER) {
	    x1 += (w - labelWidth) / 2;
	} else if (setPtr->justify == TK_JUSTIFY_RIGHT) {
	    x1 += (w - labelWidth);
	}
    }
    if (tabPtr->text != NULL) {
	tw = tabPtr->textWidth0;
	th = tabPtr->textHeight0;
    } else {
	tw = th = 0;
    }
    w = x2 - x1;
    h = y2 - y1;
#if DEBUG1
	fprintf(stderr, "ComputeLabelOffset: 1 tab=%s x=%d,y=%d,w=%d,h=%d, ww=%d wh=%d tabLabelWidth=%d lw=%d\n",
		tabPtr->text, x1, y1, w, h, tabPtr->worldWidth, 
		tabPtr->worldHeight, tabPtr->labelWidth0, labelWidth);
#endif
    maxLength = x2 - x1;

    if (tw > w) {
	tw = w; 
    }

    /* Now compute the text/image and icon positions according to the text
     * side. Don't use the text/image width/height to compute the position of
     * the icon because the text will shrink with the available room.  */
    switch (setPtr->iconPos) {
    case SIDE_LEFT:
	if (iw > w) {			/* Not enough space for icon. */
	    iw = w;
	    w = 0;
	} else {
	    w -= iw;			/* Subtract space taken by icon. */
	}
	if (tw > w) {			/* Not enough space for text. */
	    tw = w;
	    w = 0;
	} else {
	    w -= tw;			/* Subtract space taken by text. */
	}
	if (w < 0) {
	    w = 0;
	}
	/* The text/image is to the right of the icon. */
	ix = x1;
	iy = y1;
	if (h > ih) {
	    iy += (h - ih) / 2;
	}
	tx = ix + iw;
	if ((iw > 0) && (tw > 0))  {
	    tx += LABEL_PAD;
	}
	ty = y1;
	if (h > th) {
	    ty += (h - th) / 2;
	}
#if DEBUG1
	fprintf(stderr, "tab=%s textWidth=%d, textHeight=%d => %d,%d %dx%d iw=%d ih=%d\n", 
		tabPtr->text, tabPtr->textWidth0, tabPtr->textHeight0, tx, ty, tw, th,
		iw, ih);
#endif
	break;

    case SIDE_RIGHT:
	/* The text/image is to the left of the icon. */
	tx = x1;
	ty = y1 + (h - th) / 2;
	ix = x2 - iw;
	iy = y1 + (h - ih) / 2;
	if ((iw > 0) && (tw > 0))  {
	    ix += LABEL_PAD;
	}
	break;
    }
    tabPtr->iconRegion = RotateRegion(tabPtr, ix, iy, iw, ih);
#ifdef DEBUG
	fprintf(stderr, "ComputeLabelOffset: icon tab=%s x=%d,y=%d,w=%d,h=%d => x=%d,y=%d w=%d,h=%d\n",
		tabPtr->text, ix, iy, iw, ih, tabPtr->iconRegion.x, 
		tabPtr->iconRegion.y, tabPtr->iconRegion.width, 
		tabPtr->iconRegion.height);
#endif
    tabPtr->textRegion = RotateRegion(tabPtr, tx, ty, ODD(tw), ODD(th));
#if DEBUG1
	fprintf(stderr, "ComputeLabelOffset: text tab=%s x=%d,y=%d,w=%d,h=%d => x=%d,y=%d w=%d,h=%d\n",
		tabPtr->text, tx, ty, tw, th, tabPtr->textRegion.x, 
		tabPtr->textRegion.y, tabPtr->textRegion.width, 
		tabPtr->textRegion.height);
#endif
    /* Focus dashed rectangle. */
    {
	fx = tx;
	fy = ty;
	fw = ODD(tw);
	fh = ODD(th);
	tabPtr->focusRegion = RotateRegion(tabPtr, fx, fy, fw, fh);
    }

}


static void
DrawButtonPictures(Tabset *setPtr)
{
    Button *butPtr = &setPtr->closeButton;

    if (butPtr->active0 == NULL) {
	butPtr->active0 = Blt_PaintDelete(CLOSE_WIDTH, CLOSE_HEIGHT, 
		butPtr->activeBg, butPtr->activeFg);
    } 
    if ((butPtr->active != NULL) && 
	(butPtr->active != butPtr->active0)) {
	Blt_FreePicture(butPtr->active);
    }
    if (setPtr->angle == 0.0) {
	butPtr->active = butPtr->active0;
    } else {
	butPtr->active = Blt_RotatePicture(butPtr->active0, setPtr->angle);
    }
    if (butPtr->normal0 == NULL) {
	butPtr->normal0 = Blt_PaintDelete(CLOSE_WIDTH, CLOSE_HEIGHT, 
		butPtr->normalBg, butPtr->normalFg);
    } 
    if ((butPtr->normal != NULL) && 
	(butPtr->normal != butPtr->normal0)) {
	Blt_FreePicture(butPtr->normal);
    }
    if (setPtr->angle == 0.0) {
	butPtr->normal = butPtr->normal0;
    } else {
	butPtr->normal = Blt_RotatePicture(butPtr->normal0, setPtr->angle);
    }
}

/*
 *   x,y
 *    |1|2|3| 4 |5|  4  |3|2|1|
 *
 *   1. tab borderwidth
 *   2. corner offset or slant
 *   3. label pad
 *   4. label or text width
 *   5. pad
 */
static void
DrawLabel(Tabset *setPtr, Tab *tabPtr, Drawable drawable)
{
    int x, y;
    int maxLength;
    XColor *bgColor;
    Blt_Background bg;
    TabStyle *stylePtr;
    int xSelPad, ySelPad;
    GadgetRegion *rPtr;

    if ((tabPtr->flags & ONSCREEN) == 0) {
	return;
    }

    ComputeLabelOffsets(setPtr, tabPtr);

    /* Get origin of tab. */
    WorldToScreen(setPtr, tabPtr->worldX, tabPtr->worldY, &x, &y);
    x += setPtr->xOffset;		/* Adjust for pixmap offsets. */
    y += setPtr->yOffset;

    /* Adjust according the side. */
    if (setPtr->side & SIDE_BOTTOM) {
	y -= setPtr->tabHeight + tabPtr->padTop;
    } else if (setPtr->side & SIDE_LEFT) {
	/* 	y -= tabPtr->worldWidth; */
    } else if (setPtr->side & SIDE_RIGHT) {
	x -= setPtr->tabHeight + tabPtr->padTop;
    }
    /* Adjust the label's area according to the tab's slant. */
    if (setPtr->side & (SIDE_RIGHT | SIDE_LEFT)) {
	y += (setPtr->flags & SLANT_LEFT) ? setPtr->tabHeight : setPtr->inset2;
    } else {
	x += (setPtr->flags & SLANT_LEFT) ? setPtr->tabHeight : setPtr->inset2;
    }

#if DEBUG0
    fprintf(stderr, "DrawLabel: tab=%s x=%d,y=%d wx=%d,wy=%d,ww=%d,wh=%d\n",
	    tabPtr->text, x, y, tabPtr->worldX, tabPtr->worldY, 
	    tabPtr->worldWidth, tabPtr->worldHeight);
#endif
    stylePtr = &setPtr->defStyle;
    bg = GETATTR(tabPtr, bg);
    xSelPad = ySelPad = 0;
    if (tabPtr == setPtr->selectPtr) {
	x -= setPtr->xSelectPad / 2;
	if (setPtr->side & SIDE_TOP) {
	    y -= setPtr->ySelectPad;
	}
	if (setPtr->side & SIDE_BOTTOM) {
	    y += setPtr->ySelectPad;
	}
	xSelPad = setPtr->xSelectPad / 2;
	ySelPad = setPtr->ySelectPad / 2;
	bg = GETATTR(tabPtr, selBg);
    }
    bgColor = Blt_BackgroundBorderColor(bg);
    if ((tabPtr == setPtr->activePtr) || (tabPtr == setPtr->activeButtonPtr)) {
	Blt_Background activeBg;

	activeBg = GETATTR(tabPtr, activeBg);
	bgColor = Blt_BackgroundBorderColor(activeBg);
    }
    rPtr = &tabPtr->buttonRegion;
    if ((setPtr->plusPtr != tabPtr) && (setPtr->flags & CLOSE_NEEDED) &&
	(tabPtr->flags & CLOSE_NEEDED) && (rPtr->w > 0) && (rPtr->h > 0)) {
	Button *butPtr = &setPtr->closeButton;
	Blt_Picture picture;
	int bx, by;

	DrawButtonPictures(setPtr);
	picture = (setPtr->activeButtonPtr == tabPtr) 
	    ? butPtr->active : butPtr->normal;
	if (setPtr->painter == NULL) {
	    setPtr->painter = Blt_GetPainter(setPtr->tkwin, 1.0);
	}
	
	bx = x + rPtr->x;
	by = y + rPtr->y;
	Blt_PaintPictureWithBlend(setPtr->painter, drawable, picture, 0, 0, 
		rPtr->w, rPtr->h, bx, by, 0, 1.0);
    }

    rPtr = &tabPtr->iconRegion;
    if ((tabPtr->icon != NULL) && (rPtr->w > 0) && (rPtr->h > 0)) {
	Tk_Image tkImage;
	int maxLength;

	maxLength = 10000;
	tkImage = IconBits(tabPtr->icon);
	if (setPtr->angle == 0.0) {
 	    Tk_RedrawImage(tkImage, 0, 0, rPtr->w, rPtr->h, drawable, 
		x + rPtr->x, y + rPtr->y);
	} else {
	    struct _Icon *iconPtr;
	    
	    iconPtr = tabPtr->icon;
	    if (iconPtr->angle != setPtr->angle) {
		int isPhoto;
		Blt_Picture picture, rotated;

		if (iconPtr->picture != NULL) {
		    Blt_FreePicture(iconPtr->picture);
		}
		picture = Blt_GetPictureFromImage(setPtr->interp, tkImage,
			&isPhoto);
		rotated = Blt_RotatePicture(picture, setPtr->angle);
		iconPtr->picture = rotated;
		iconPtr->angle = setPtr->angle;
		if (isPhoto) {
		    Blt_FreePicture(picture);
		}
	    }
	    if (setPtr->painter == NULL) {
		setPtr->painter = Blt_GetPainter(setPtr->tkwin, 1.0);
	    }
	    Blt_PaintPictureWithBlend(setPtr->painter, drawable, 
		iconPtr->picture, 0, 0, rPtr->w, rPtr->h, x + rPtr->x, 
		y + rPtr->y, 0, 1.0);
	}
    }
    rPtr = &tabPtr->textRegion;
    if ((tabPtr->text != NULL) && (rPtr->w > 0) && (rPtr->h > 0)) {
	TextStyle ts;
	XColor *fgColor;
	Blt_Font font;
	int maxLength = -1;

	font = GETATTR(tabPtr, font);
	if (tabPtr == setPtr->selectPtr) {
	    fgColor = GETATTR(tabPtr, selColor);
	} else if ((tabPtr == setPtr->activePtr) || 
		   (tabPtr == setPtr->activeButtonPtr)) {
	    fgColor = GETATTR(tabPtr, activeFg);
	} else {
	    fgColor = GETATTR(tabPtr, textColor);
	}
	Blt_Ts_InitStyle(ts);
	Blt_Ts_SetAngle(ts, setPtr->angle);
	Blt_Ts_SetBackground(ts, bg);
	Blt_Ts_SetFont(ts, font);
	Blt_Ts_SetPadding(ts, 2, 2, 0, 0);
	if (tabPtr->flags & DISABLED) {
	    Blt_Ts_SetState(ts, STATE_DISABLED);
	} else if (tabPtr->flags & ACTIVE) {
	    Blt_Ts_SetState(ts, STATE_ACTIVE);
	}
	Blt_Ts_SetForeground(ts, fgColor);
	if ((setPtr->quad == ROTATE_90) || (setPtr->quad == ROTATE_270)) {
	    maxLength = rPtr->h;
	} else {
	    maxLength = rPtr->w;
	}
	if (tabPtr == setPtr->selectPtr) {
	    maxLength += setPtr->xSelectPad;
	}
#if DEBUG0
	fprintf(stderr, "DrawLayout: text tab=%s coords=%d,%d text=%dx%d ml=%d => region: x=%d,y=%d w=%d,h=%d\n",
		tabPtr->text, x, y, tabPtr->textWidth0, tabPtr->textHeight0, 
		maxLength, rPtr->x, rPtr->y, rPtr->w, rPtr->h);
#endif
	Blt_Ts_SetMaxLength(ts, maxLength);
	Blt_Ts_DrawLayout(setPtr->tkwin, drawable, tabPtr->layoutPtr, &ts, 
			  x + rPtr->x, y + rPtr->y);
    }
    rPtr = &tabPtr->focusRegion;
    if ((setPtr->flags & FOCUS) && (setPtr->focusPtr == tabPtr) && 
	(rPtr->w > 0) && (rPtr->h > 0)) {
	XColor *fg;

	if (tabPtr == setPtr->selectPtr) {
	    fg = GETATTR(tabPtr, selColor);
	} else if (tabPtr == setPtr->activePtr) {
	    fg = GETATTR(tabPtr, activeFg);
	} else {
	    fg = GETATTR(tabPtr, textColor);
	}
	XSetForeground(setPtr->display, stylePtr->activeGC, fg->pixel);
	maxLength = rPtr->w + xSelPad;
	if ((setPtr->quad == ROTATE_0) || (setPtr->quad == ROTATE_180)) {
	XDrawRectangle(setPtr->display, drawable, stylePtr->activeGC,
		x + rPtr->x - 1, y + rPtr->y, maxLength + 1, rPtr->h);
	} else {
	XDrawRectangle(setPtr->display, drawable, stylePtr->activeGC,
		x + rPtr->x, y + rPtr->y - 1, maxLength, rPtr->h + 1);
	}
    }
}
