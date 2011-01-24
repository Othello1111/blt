
/*
 * bltComboMenu.c --
 *
 * This module implements a combomenu widget for the BLT toolkit.
 *
 *	Copyright 2006 George A Howlett.
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
#include "bltOp.h"
#include "bltBind.h"
#include "bltImage.h"
#include "bltPicture.h"
#include "bltFont.h"
#include "bltText.h"
#include "bltChain.h"
#include "bltHash.h"
#include "bltBgStyle.h"
#include "bltPainter.h"
#include "bltSwitch.h"

static const char emptyString[] = "";

#define MAXSCROLLBARTHICKNESS	100

#define REDRAW_PENDING		(1<<0)
#define LAYOUT_PENDING		(1<<1)
#define UPDATE_PENDING		(1<<2)
#define FOCUS			(1<<3)
#define SCROLLX			(1<<4)
#define SCROLLY			(1<<5)
#define SCROLL_PENDING		(SCROLLX|SCROLLY)

#define INSTALL_XSCROLLBAR	(1<<8)
#define INSTALL_YSCROLLBAR	(1<<9)

#define RESTRICT_MIN		(1<<10)
#define RESTRICT_MAX		(1<<11)
#define RESTRICT_NONE		(0)

#define VAR_FLAGS (TCL_GLOBAL_ONLY|TCL_TRACE_WRITES|TCL_TRACE_UNSETS)

#define PIXMAPX(cm, wx)	((wx) - (cm)->xOffset)
#define PIXMAPY(cm, wy)	((wy) - (cm)->yOffset)

#define SCREENX(cm, wx)	((wx) - (cm)->xOffset + (cm)->borderWidth)
#define SCREENY(cm, wy)	((wy) - (cm)->yOffset + (cm)->borderWidth)

#define WORLDX(cm, sx)	((sx) - (cm)->borderWidth + (cm)->xOffset)
#define WORLDY(cm, sy)	((sy) - (cm)->borderWidth + (cm)->yOffset)

#define VPORTWIDTH(cm)	\
    (Tk_Width((cm)->tkwin) - 2 * (cm)->borderWidth - (cm)->yScrollbarWidth)
#define VPORTHEIGHT(cm) \
    (Tk_Height((cm)->tkwin) - 2 * (cm)->borderWidth - (cm)->xScrollbarHeight)

#define FCLAMP(x)	((((x) < 0.0) ? 0.0 : ((x) > 1.0) ? 1.0 : (x)))
#define CLAMP(x,min,max) ((((x) < (min)) ? (min) : ((x) > (max)) ? (max) : (x)))

#define ITEM_IPAD	   3
#define ITEM_XPAD	   2
#define ITEM_YPAD	   1
#define ITEM_SEP_HEIGHT	   6
#define ITEM_L_IND_WIDTH  19
#define ITEM_L_IND_HEIGHT 19
#define ITEM_R_IND_WIDTH  13
#define ITEM_R_IND_HEIGHT 13

#define ITEM_MAP	  (1<<1)	/* Item needs to be remapped  */
#define ITEM_REDRAW	  (1<<2)	/* Item needs to be redrawn. */
#define ITEM_SELECTED	  (1<<4)	/* Radiobutton/checkbutton is
					 * selected. */

/* Item state. */
#define ITEM_NORMAL	  (1<<5)	/* Draw item normally. */
#define ITEM_DISABLED	  (1<<6)	/* Item is disabled. */
#define ITEM_STATE_MASK   ((ITEM_DISABLED)|(ITEM_NORMAL))

/* Item type. */
#define ITEM_BUTTON	  (1<<9)	/* Item is command button. */
#define ITEM_RADIOBUTTON  (1<<10)	/* Item is radiobutton. */
#define ITEM_CHECKBUTTON  (1<<11)	/* Item is checkbutton. */
#define ITEM_CASCADE	  (1<<12)	/* Item is cascade. */
#define ITEM_SEPARATOR	  (1<<13)	/* Item is separator. */
#define ITEM_TYPE_MASK    ((ITEM_BUTTON)|(ITEM_RADIOBUTTON)|(ITEM_CHECKBUTTON)|\
			   (ITEM_CASCADE)|(ITEM_SEPARATOR))

#define DEF_COMBO_BORDERWIDTH	    "1"
#define DEF_COMBO_CURSOR            ((char *)NULL)
#define DEF_COMBO_HEIGHT	    "0"
#define DEF_COMBO_ICON_VARIABLE	    ((char *)NULL)
#define DEF_COMBO_POSTCOMMAND	    ((char *)NULL)
#define DEF_COMBO_RELIEF	    "solid"
#define DEF_COMBO_SCROLLBAR	    ((char *)NULL)
#define DEF_COMBO_SCROLL_CMD	    ((char *)NULL)
#define DEF_COMBO_SCROLL_INCR	    "2"
#define DEF_COMBO_TAKE_FOCUS        "1"
#define DEF_COMBO_TEXT_VARIABLE	    ((char *)NULL)
#define DEF_COMBO_UNPOSTCOMMAND	    ((char *)NULL)
#define DEF_COMBO_WIDTH             "0"
#define	DEF_COMBO_CHECKBUTTON_FILL_COLOR	(char *)NULL
#define	DEF_COMBO_CHECKBUTTON_OUTLINE_COLOR	(char *)NULL
#define	DEF_COMBO_CHECKBUTTON_COLOR		STD_INDICATOR_COLOR
#define DEF_COMBO_CHECKBUTTON_SIZE		"12"
#define DEF_COMBO_RADIOBUTTON_FILL_COLOR	RGB_WHITE
#define	DEF_COMBO_RADIOBUTTON_OUTLINE_COLOR	RGB_BLACK
#define DEF_COMBO_RADIOBUTTON_COLOR		STD_INDICATOR_COLOR
#define DEF_COMBO_RADIOBUTTON_SIZE		"12"

#define DEF_ITEM_ACCELERATOR	    ((char *)NULL)
#define DEF_ITEM_BITMAP             ((char *)NULL)
#define DEF_ITEM_COMMAND	    ((char *)NULL)
#define DEF_ITEM_DATA		    ((char *)NULL)
#define DEF_ITEM_ICON               ((char *)NULL)
#define DEF_ITEM_IMAGE              ((char *)NULL)
#define DEF_ITEM_INDENT		    "0"
#define DEF_ITEM_MENU               ((char *)NULL)
#define DEF_ITEM_OFF_VALUE          "0"
#define DEF_ITEM_ON_VALUE           "1"
#define DEF_ITEM_STATE		    "normal"
#define DEF_ITEM_STYLE		    "default"
#define DEF_ITEM_TAGS		    ((char *)NULL)
#define DEF_ITEM_TEXT               ((char *)NULL)
#define DEF_ITEM_TIP		    ((char *)NULL)
#define DEF_ITEM_TYPE		    "command"
#define DEF_ITEM_UNDERLINE	    "-1"
#define DEF_ITEM_VALUE              ((char *)NULL)
#define DEF_ITEM_VARIABLE	    ((char *)NULL)
#define DEF_STYLE_ACCEL_ACTIVE_FG   RGB_WHITE
#define DEF_STYLE_ACCEL_FG	    RGB_BLACK
#define DEF_STYLE_ACCEL_FONT	    STD_FONT_SMALL
#define DEF_STYLE_ACTIVE_BG	    RGB_SKYBLUE4
#define DEF_STYLE_ACTIVE_FG	    RGB_WHITE
#define DEF_STYLE_ACTIVE_RELIEF	    "flat"
#define DEF_STYLE_BG		    RGB_WHITE
#define DEF_STYLE_BORDERWIDTH	    "0"
#define DEF_STYLE_DISABLED_ACCEL_FG STD_DISABLED_FOREGROUND
#define DEF_STYLE_DISABLED_BG       DISABLED_BACKGROUND
#define DEF_STYLE_DISABLED_FG       DISABLED_FOREGROUND
#define DEF_STYLE_FG                RGB_BLACK
#define DEF_STYLE_FONT		    STD_FONT_SMALL
#define DEF_STYLE_IND_FILL_COLOR    (char *)NULL
#define DEF_STYLE_IND_OUTLINE_COLOR (char *)NULL
#define DEF_STYLE_IND_COLOR	    (char *)NULL
#define DEF_STYLE_IND_SIZE	    "12"
#define DEF_STYLE_RELIEF	    "flat"
#define DISABLED_BACKGROUND	    RGB_GREY90
#define DISABLED_FOREGROUND         RGB_GREY70


static Blt_OptionFreeProc FreeStyleProc;
static Blt_OptionParseProc ObjToStyleProc;
static Blt_OptionPrintProc StyleToObjProc;
static Blt_CustomOption styleOption = {
    ObjToStyleProc, StyleToObjProc, FreeStyleProc, (ClientData)0
};

static Blt_OptionFreeProc FreeTagsProc;
static Blt_OptionParseProc ObjToTagsProc;
static Blt_OptionPrintProc TagsToObjProc;
static Blt_CustomOption tagsOption = {
    ObjToTagsProc, TagsToObjProc, FreeTagsProc, (ClientData)0
};

static Blt_OptionParseProc ObjToTypeProc;
static Blt_OptionPrintProc TypeToObjProc;
static Blt_CustomOption typeOption = {
    ObjToTypeProc, TypeToObjProc, NULL, (ClientData)0
};

static Blt_OptionFreeProc FreeLabelProc;
static Blt_OptionParseProc ObjToLabelProc;
static Blt_OptionPrintProc LabelToObjProc;
static Blt_CustomOption labelOption = {
    ObjToLabelProc, LabelToObjProc, FreeLabelProc, (ClientData)0
};

static Blt_OptionFreeProc FreeIconProc;
static Blt_OptionParseProc ObjToIconProc;
static Blt_OptionPrintProc IconToObjProc;
static Blt_CustomOption iconOption = {
    ObjToIconProc, IconToObjProc, FreeIconProc, (ClientData)0
};

static Blt_OptionFreeProc FreeTraceVarProc;
static Blt_OptionParseProc ObjToTraceVarProc;
static Blt_OptionPrintProc TraceVarToObjProc;
static Blt_CustomOption traceVarOption = {
    ObjToTraceVarProc, TraceVarToObjProc, FreeTraceVarProc, (ClientData)0
};

static Blt_OptionParseProc ObjToStateProc;
static Blt_OptionPrintProc StateToObjProc;
static Blt_CustomOption stateOption = {
    ObjToStateProc, StateToObjProc, NULL, (ClientData)0
};

static Blt_OptionParseProc ObjToRestrictProc;
static Blt_OptionPrintProc RestrictToObjProc;
static Blt_CustomOption restrictOption = {
    ObjToRestrictProc, RestrictToObjProc, NULL, (ClientData)0
};

extern Blt_CustomOption bltLimitsOption;

typedef struct _ComboMenu ComboMenu;

/*
 * Icon --
 *
 *	Since instances of the same Tk image can be displayed in different
 *	windows with possibly different color palettes, Tk internally stores
 *	each instance in a linked list.  But if the instances are used in the
 *	same widget and therefore use the same color palette, this adds a lot
 *	of overhead, especially when deleting instances from the linked list.
 *
 *	For the combomenu widget, we never need more than a single instance of
 *	an image, regardless of how many times it's used.  Cache the image,
 *	maintaining a reference count for each image used in the widget.  It's
 *	likely that the combomenu widget will use many instances of the same
 *	image.
 */

typedef struct _Icon {
    Tk_Image tkImage;			/* The Tk image being cached. */
    Blt_HashEntry *hPtr;		/* Hash table pointer to the image. */
    int refCount;			/* Reference count for this image. */
    short int width, height;		/* Dimensions of the cached image. */
} *Icon;

#define IconHeight(i)	((i)->height)
#define IconWidth(i)	((i)->width)
#define IconImage(i)	((i)->tkImage)
#define IconName(i)	(Blt_Image_Name(IconImage(i)))

typedef struct {
    const char *name;
    Blt_HashEntry *hPtr;
    ComboMenu *comboPtr;
    int refCount;			/* Indicates if the style is currently
					 * in use in the combomenu. */
    int borderWidth;
    int relief;
    int activeRelief;
    int reqIndWidth;

    Blt_Background normalBg;
    Blt_Background activeBg;
    Blt_Background disabledBg;

    XColor *normalFgColor;
    XColor *activeFgColor;
    XColor *disabledFgColor;

    Blt_Font accelFont;			/* Font of accelerator text. */
    XColor *accelNormalColor;		/* Color of accelerator text. */
    XColor *accelDisabledColor;		/* Color of accelerator text. */
    XColor *accelActiveColor;		/* Color of accelerator background. */

    Blt_Font labelFont;			/* Font of the label */
    XColor *labelNormalColor;		/* Color of label text. */
    XColor *labelDisabledColor;		/* Color of label background. */
    XColor *labelActiveColor;		/* Color of label background. */

    /* Radiobuttons, checkbuttons, and cascades. */
    Blt_Picture radiobutton[3];
    Blt_Picture checkbutton[3];

    XColor *indOutlineColor;
    XColor *indFillColor;
    XColor *indColor;
    
    GC accelActiveGC;
    GC accelDisabledGC;
    GC accelNormalGC;
    GC labelActiveGC;
    GC labelDisabledGC;
    GC labelNormalGC;
} Style;

static Blt_ConfigSpec styleConfigSpecs[] =
{
    {BLT_CONFIG_FONT, "-acceleratorfont", (char *)NULL, (char *)NULL, 
	DEF_STYLE_ACCEL_FONT, Blt_Offset(Style, accelFont), 0},
    {BLT_CONFIG_COLOR, "-acceleratorforeground", (char *)NULL, (char *)NULL, 
	DEF_STYLE_ACCEL_FG, Blt_Offset(Style, accelNormalColor), 0},
    {BLT_CONFIG_COLOR, "-activeacceleratorforeground", (char *)NULL, 
	(char *)NULL, DEF_STYLE_ACCEL_ACTIVE_FG, 
	Blt_Offset(Style, accelActiveColor), 0},
    {BLT_CONFIG_BACKGROUND, "-activebackground", (char *)NULL, (char *)NULL, 
	DEF_STYLE_ACTIVE_BG, Blt_Offset(Style, activeBg), 0},
    {BLT_CONFIG_COLOR, "-activeforeground", (char *)NULL, (char *)NULL, 
	DEF_STYLE_ACTIVE_FG, Blt_Offset(Style, labelActiveColor), 0},
    {BLT_CONFIG_RELIEF, "-activerelief", (char *)NULL, (char *)NULL, 
	DEF_STYLE_ACTIVE_RELIEF, Blt_Offset(Style, activeRelief), 
	BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_BACKGROUND, "-background", (char *)NULL, (char *)NULL,
	DEF_STYLE_BG, Blt_Offset(Style, normalBg), 0},
    {BLT_CONFIG_SYNONYM, "-bd", "borderWidth", (char *)NULL, (char *)NULL, 0,0},
    {BLT_CONFIG_SYNONYM, "-bg", (char *)NULL, (char *)NULL, (char *)NULL, 0, 0},
    {BLT_CONFIG_PIXELS_NNEG, "-borderwidth", (char *)NULL, (char *)NULL,
	DEF_STYLE_BORDERWIDTH, Blt_Offset(Style, borderWidth),
	BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_COLOR, "-disabledacceleratorforeground", (char *)NULL, 
	(char *)NULL, DEF_STYLE_DISABLED_ACCEL_FG, 
	Blt_Offset(Style, accelDisabledColor), 0},
    {BLT_CONFIG_BACKGROUND, "-disabledbackground", (char *)NULL, (char *)NULL, 
	DEF_STYLE_DISABLED_BG, Blt_Offset(Style, disabledBg), 0},
    {BLT_CONFIG_COLOR, "-disabledforeground", (char *)NULL, (char *)NULL, 
	DEF_STYLE_DISABLED_FG, Blt_Offset(Style, labelDisabledColor), 0},
    {BLT_CONFIG_SYNONYM, "-fg", (char *)NULL, (char *)NULL, (char *)NULL, 0, 0},
    {BLT_CONFIG_COLOR, "-foreground", (char *)NULL, (char *)NULL, DEF_STYLE_FG, 
	Blt_Offset(Style, labelNormalColor), 0},
    {BLT_CONFIG_FONT, "-font", (char *)NULL, (char *)NULL, DEF_STYLE_FONT, 
        Blt_Offset(Style, labelFont), 0},
    {BLT_CONFIG_COLOR, "-indicatorfillcolor", (char *)NULL, (char *)NULL, 
        DEF_STYLE_IND_FILL_COLOR, Blt_Offset(Style, indFillColor), 
        BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_COLOR, "-indicatoroutlinecolor", (char *)NULL, (char *)NULL, 
	DEF_STYLE_IND_OUTLINE_COLOR, Blt_Offset(Style, indOutlineColor), 
        BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_COLOR, "-indicatorcolor", (char *)NULL, (char *)NULL, 
	DEF_STYLE_IND_COLOR, Blt_Offset(Style, indColor), 
        BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_PIXELS_NNEG, "-indicatorsize", (char *)NULL, (char *)NULL, 
	DEF_STYLE_IND_SIZE, Blt_Offset(Style, reqIndWidth), 
        BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_RELIEF, "-relief", (char *)NULL, (char *)NULL, 
	DEF_STYLE_RELIEF, Blt_Offset(Style, relief), 
        BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_END, (char *)NULL, (char *)NULL, (char *)NULL, (char *)NULL, 
	0, 0}
};

/*
 *
 *  [left indicator] [icon] [label] [right indicator/accel] [scrollbar]
 *   
 * left indicator:	checkbutton or radiobutton entries.
 * icon:		all entries.
 * label:		all entries.
 * accel:		checkbutton, radiobutton, or button entries.
 * right indicator:     cascade item only.
 */
typedef struct  {
    ComboMenu *comboPtr;		/* Combomenu containing this item. */
    long index;				/* Index of the item (numbered from 0)*/
    int xWorld, yWorld;			/* Upper left world-coordinate of item
					 * in menu. */
    Style *stylePtr;			/* Style used by this item. */
    unsigned int flags;			/* Contains various bits of
					 * information about the item, such as
					 * type, state. */
    Blt_ChainLink link;
    int relief;
    int underline;			/* Underlined character. */
    int indent;				/* # of pixels to indent the icon. */
    Icon image;				/* If non-NULL, image to be displayed
					 * instead of text label. */
    Icon icon;				/* Button, RadioButton, and
					 * CheckButton entries. */
    const char *label;			/* Label to be displayed. */
    const char *accel;			/* Accelerator text. May be NULL.*/
    Tcl_Obj *cmdObjPtr;			/* Command to be invoked when item is
					 * clicked. */
    Tcl_Obj *dataObjPtr;		/* User-data associated with this
					 * item. */
    Tcl_Obj *variableObjPtr;		/* Name of TCL variable.  If non-NULL,
					 * this variable will be set to the
					 * value string of the selected
					 * item. */
    Tcl_Obj *valueObjPtr;		/* Radiobutton value. */

    /* Checkbutton on and off values. */
    Tcl_Obj *onValueObjPtr;		/* Checkbutton on-value. */
    Tcl_Obj *offValueObjPtr;		/* Checkbutton off-value. */

    /* Cascade menu. */
    Tcl_Obj *menuObjPtr;		/* Name of the sub-menu. */

    Tcl_Obj *tagsObjPtr;

    Tcl_Obj *tipObjPtr;

    short int labelWidth, labelHeight;
    short int iconWidth, iconHeight;
    short int leftIndWidth, leftIndHeight;
    short int rightIndWidth, rightIndHeight;
    short int width, height;

} Item;

static Blt_ConfigSpec itemConfigSpecs[] =
{
    {BLT_CONFIG_STRING, "-accelerator", (char *)NULL, (char *)NULL, 
	DEF_ITEM_ACCELERATOR, Blt_Offset(Item, accel), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_OBJ, "-command", (char *)NULL, (char *)NULL, DEF_ITEM_COMMAND, 
	Blt_Offset(Item, cmdObjPtr), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_OBJ, "-data", (char *)NULL, (char *)NULL, DEF_ITEM_DATA, 
	Blt_Offset(Item, dataObjPtr), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_CUSTOM, "-icon", (char *)NULL, (char *)NULL, DEF_ITEM_ICON, 
	Blt_Offset(Item, icon), BLT_CONFIG_NULL_OK, &iconOption},
    {BLT_CONFIG_CUSTOM, "-image", (char *)NULL, (char *)NULL, DEF_ITEM_IMAGE, 
	Blt_Offset(Item, image), BLT_CONFIG_NULL_OK, &iconOption},
    {BLT_CONFIG_PIXELS_NNEG, "-indent", (char *)NULL, (char *)NULL, 
	DEF_ITEM_INDENT, Blt_Offset(Item, indent), BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_OBJ, "-menu", (char *)NULL, (char *)NULL, DEF_ITEM_MENU, 
	Blt_Offset(Item, menuObjPtr), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_OBJ, "-offvalue", (char *)NULL, (char *)NULL, 
	DEF_ITEM_OFF_VALUE, Blt_Offset(Item, offValueObjPtr), 
	BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_OBJ, "-onvalue", (char *)NULL, (char *)NULL, DEF_ITEM_ON_VALUE, 
	Blt_Offset(Item, onValueObjPtr), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_CUSTOM, "-state", (char *)NULL, (char *)NULL, DEF_ITEM_STATE, 
	Blt_Offset(Item, flags), BLT_CONFIG_DONT_SET_DEFAULT, &stateOption},
    {BLT_CONFIG_CUSTOM, "-style", (char *)NULL, (char *)NULL, DEF_ITEM_STYLE, 
	Blt_Offset(Item, stylePtr), 0, &styleOption},
     {BLT_CONFIG_CUSTOM, "-tags", (char *)NULL, (char *)NULL,
        DEF_ITEM_TAGS, 0, BLT_CONFIG_NULL_OK, &tagsOption},
    {BLT_CONFIG_CUSTOM, "-text", (char *)NULL, (char *)NULL, DEF_ITEM_TEXT, 
        Blt_Offset(Item, label), BLT_CONFIG_NULL_OK, &labelOption},
    {BLT_CONFIG_OBJ, "-tooltip", (char *)NULL, (char *)NULL, DEF_ITEM_TIP, 
         Blt_Offset(Item, tipObjPtr), BLT_CONFIG_NULL_OK},
     {BLT_CONFIG_CUSTOM, "-type", (char *)NULL, (char *)NULL, DEF_ITEM_TYPE, 
	Blt_Offset(Item, flags), BLT_CONFIG_DONT_SET_DEFAULT, &typeOption},
    {BLT_CONFIG_INT, "-underline", (char *)NULL, (char *)NULL, 
	DEF_ITEM_UNDERLINE, Blt_Offset(Item, underline), 
	BLT_CONFIG_DONT_SET_DEFAULT },
    {BLT_CONFIG_OBJ, "-value", (char *)NULL, (char *)NULL, DEF_ITEM_VALUE, 
         Blt_Offset(Item, valueObjPtr), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_CUSTOM, "-variable", (char *)NULL, (char *)NULL, 
	DEF_ITEM_VARIABLE, Blt_Offset(Item, variableObjPtr), BLT_CONFIG_NULL_OK,
	&traceVarOption},
    {BLT_CONFIG_END, (char *)NULL, (char *)NULL, (char *)NULL, (char *)NULL, 
	0, 0}
};

struct _ComboMenu {

    /*
     * This works around a bug in the Tk API.  Under Win32, Tk tries to
     * read the widget record of toplevel windows (TopLevel or Frame widget),
     * to get its menu name field.  What this means is that we must carefully
     * arrange the fields of this widget so that the menuName field is at the
     * same offset in the structure.
     */

    Tk_Window tkwin;			/* Window that embodies the frame.
					 * NULL means that the window has been
					 * destroyed but the data structures
					 * haven't yet been cleaned up. */
    Display *display;			/* Display containing widget.  Used,
					 * among other things, so that
					 * resources can be freed even after
					 * tkwin has gone away. */
    Tcl_Interp *interp;			/* Interpreter associated with widget.
					 * Used to delete widget command. */
    Tcl_Command cmdToken;		/* Token for widget's command. */
    Tcl_Obj *postCmdObjPtr;		/* If non-NULL, command to be executed
					 * when this menu is posted. */
    Tcl_Obj *unpostCmdObjPtr;		/* If non-NULL, command to be executed
					 * when this menu is posted. */
    unsigned int flags;
    Tcl_Obj *iconVarObjPtr;		/* Name of TCL variable.  If non-NULL,
					 * this variable will be set to the
					 * name of the Tk image representing
					 * the icon of the selected item.  */
    Tcl_Obj *textVarObjPtr;		/* Name of TCL variable.  If non-NULL,
					 * this variable will be set to the
					 * text string of the label of the
					 * selected item. */
    Tcl_Obj *takeFocusObjPtr;		/* Value of -takefocus option; not
					 * used in the C code, but used by
					 * keyboard * traversal scripts. */
    char *menuName;			/* Textual description of menu to use
					 * for menubar. Malloc-ed, may be
					 * NULL. */
    Tk_Cursor cursor;			/* Current cursor for window or None. */

    Tk_Anchor anchor;

    Blt_Limits reqWidth, reqHeight;     
    int relief;
    int borderWidth;

    Style defStyle;			/* Default style. */

    int parentWidth;
    int normalWidth, normalHeight;

    int xScrollUnits, yScrollUnits;

    /* Names of scrollbars to embed into the widget window. */
    Tcl_Obj *xScrollbarObjPtr, *yScrollbarObjPtr;

    /* Commands to control horizontal and vertical scrollbars. */
    Tcl_Obj *xScrollCmdObjPtr, *yScrollCmdObjPtr;

    Blt_HashTable tagTable;		/* Table of tags. */
    Blt_HashTable labelTable;		/* Table of labels (hashtables). */
    Blt_HashTable iconTable;		/* Table of icons. */

    Blt_Chain chain;

    Item *activePtr;			/* If non-NULL, item that is currently
					 * active.  If a cascade item, a
					 * submenu may be posted. */
    Item *postedPtr;

    Item *firstPtr, *lastPtr;		/* Defines the range of visible
					 * items. */

    int xOffset, yOffset;		/* Scroll offsets of viewport in
					 * world. */ 
    int worldWidth, worldHeight;	/* Dimension of entire menu. */

    Tk_Window xScrollbar;		/* Horizontal scrollbar to be used if
					 * necessary. If NULL, no x-scrollbar
					 * is used. */
    Tk_Window yScrollbar;		/* Vertical scrollbar to be used if
					 * necessary. If NULL, no y-scrollbar
					 * is used. */

    short int yScrollbarWidth, xScrollbarHeight;
    short int leftIndWidth, rightIndWidth;
    short int labelWidth, iconWidth;

    Blt_HashTable styleTable;		/* Table of styles used. */

    Icon rbIcon;	
    Icon cbIcon;	
    Icon casIcon;	

    XColor *checkButtonFillColor;
    XColor *checkButtonOutlineColor;
    XColor *checkButtonColor;
    int checkButtonReqSize;

    XColor *radioButtonFillColor;
    XColor *radioButtonOutlineColor;
    XColor *radioButtonColor;
    int radioButtonReqSize;

    /*
     * Scanning Information:
     */
    int scanAnchorX;			/* Horizontal scan anchor in screen
					 * x-coordinates. */
    int scanX;				/* x-offset of the start of the
					 * horizontal scan in world
					 * coordinates.*/
    int scanAnchorY;			/* Vertical scan anchor in screen
					 * y-coordinates. */
    int scanY;				/* y-offset of the start of the
					 * vertical scan in world
					 * coordinates.*/
    short int width, height;
    Blt_Painter painter;
};

static Blt_ConfigSpec comboConfigSpecs[] =
{
    {BLT_CONFIG_FONT, "-acceleratorfont", "acceleratorFont", "AcceleratorFont", 
	DEF_STYLE_ACCEL_FONT, Blt_Offset(ComboMenu, defStyle.accelFont), 0},
    {BLT_CONFIG_COLOR, "-acceleratorforeground", "acceleratorForeground", 
	"AcceleratorForeground", DEF_STYLE_ACCEL_FG, 
	Blt_Offset(ComboMenu, defStyle.accelNormalColor), 0},
    {BLT_CONFIG_COLOR, "-activeacceleratorforeground", 
	"activeAcceleratorForeground", "ActiveAcceleratorForeground", 
	DEF_STYLE_ACCEL_ACTIVE_FG, 
	Blt_Offset(ComboMenu, defStyle.accelActiveColor), 0},
    {BLT_CONFIG_BACKGROUND, "-activebackground", "activeBackground",
	"ActiveBackground", DEF_STYLE_ACTIVE_BG, 
	Blt_Offset(ComboMenu, defStyle.activeBg), 0},
    {BLT_CONFIG_COLOR, "-activeforeground", "activeForeground",
	"ActiveForeground", DEF_STYLE_ACTIVE_FG, 
	Blt_Offset(ComboMenu, defStyle.labelActiveColor), 0},
    {BLT_CONFIG_RELIEF, "-activerelief", "activeRelief", "ActiveRelief", 
	DEF_STYLE_ACTIVE_RELIEF, Blt_Offset(ComboMenu, defStyle.activeRelief), 
	BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_BACKGROUND, "-background", "background", "Background",
	DEF_STYLE_BG, Blt_Offset(ComboMenu, defStyle.normalBg), 0},
    {BLT_CONFIG_SYNONYM, "-bd", "borderWidth", (char *)NULL, (char *)NULL, 0,0},
    {BLT_CONFIG_SYNONYM, "-bg", "background", (char *)NULL, (char *)NULL, 0, 0},
    {BLT_CONFIG_PIXELS_NNEG, "-borderwidth", "borderWidth", "BorderWidth",
	DEF_COMBO_BORDERWIDTH, Blt_Offset(ComboMenu, borderWidth), 
	BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_ACTIVE_CURSOR, "-cursor", "cursor", "Cursor", DEF_COMBO_CURSOR, 
	Blt_Offset(ComboMenu, cursor), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_COLOR, "-disabledacceleratorforeground", 
	"disabledAcceleratorForeground", "DisabledAcceleratorForeground", 
	DEF_STYLE_DISABLED_ACCEL_FG, 
	Blt_Offset(ComboMenu, defStyle.accelDisabledColor), 0},
    {BLT_CONFIG_BACKGROUND, "-disabledbackground", "disabledBackground",
	"DisabledBackground", DEF_STYLE_DISABLED_BG, 
        Blt_Offset(ComboMenu, defStyle.disabledBg), 0},
    {BLT_CONFIG_COLOR, "-disabledforeground", "disabledForeground",
	"DisabledForeground", DEF_STYLE_DISABLED_FG, 
	Blt_Offset(ComboMenu, defStyle.labelDisabledColor), 0},
    {BLT_CONFIG_SYNONYM, "-fg", "foreground", (char *)NULL, (char *)NULL, 0, 0},
    {BLT_CONFIG_COLOR, "-foreground", "foreground", "Foreground",
	DEF_STYLE_FG, Blt_Offset(ComboMenu, defStyle.labelNormalColor), 0},
    {BLT_CONFIG_FONT, "-font", "font", "Font", DEF_STYLE_FONT, 
	Blt_Offset(ComboMenu, defStyle.labelFont), 0},
    {BLT_CONFIG_CUSTOM, "-height", "height", "Height", DEF_COMBO_HEIGHT, 
	Blt_Offset(ComboMenu, reqHeight), BLT_CONFIG_DONT_SET_DEFAULT,
	&bltLimitsOption},
    {BLT_CONFIG_OBJ, "-iconvariable", "iconVariable", "IconVariable", 
	DEF_COMBO_ICON_VARIABLE, Blt_Offset(ComboMenu, iconVarObjPtr), 
        BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_PIXELS_NNEG, "-itemborderwidth", "itemBorderWidth", 
	"ItemBorderWidth", DEF_STYLE_BORDERWIDTH, 
	Blt_Offset(ComboMenu, defStyle.borderWidth), 
	BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_OBJ, "-postcommand", "postCommand", "PostCommand", 
	DEF_COMBO_POSTCOMMAND, Blt_Offset(ComboMenu, postCmdObjPtr), 
	BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_RELIEF, "-relief", "relief", "Relief", DEF_COMBO_RELIEF, 
	Blt_Offset(ComboMenu, relief), BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_CUSTOM, "-restrictwidth", "restrictWidth", "RestrictWidth", 
	(char *)NULL, Blt_Offset(ComboMenu, flags), BLT_CONFIG_DONT_SET_DEFAULT,
	&restrictOption},
    {BLT_CONFIG_OBJ, "-textvariable", "textVariable", "TextVariable", 
	DEF_COMBO_TEXT_VARIABLE, Blt_Offset(ComboMenu, textVarObjPtr), 
        BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_OBJ, "-xscrollbar", "xScrollbar", "Scrollbar", 
	DEF_COMBO_SCROLLBAR, Blt_Offset(ComboMenu, xScrollbarObjPtr), 
	BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_OBJ, "-xscrollcommand", "xScrollCommand", "ScrollCommand",
        DEF_COMBO_SCROLL_CMD, Blt_Offset(ComboMenu, xScrollCmdObjPtr), 
	BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_PIXELS_POS, "-xscrollincrement", "xScrollIncrement",
	"ScrollIncrement", DEF_COMBO_SCROLL_INCR, 
         Blt_Offset(ComboMenu, xScrollUnits), BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_OBJ, "-yscrollbar", "yScrollbar", "Scrollbar", 
	DEF_COMBO_SCROLLBAR, Blt_Offset(ComboMenu, yScrollbarObjPtr), 
	BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_OBJ, "-yscrollcommand", "yScrollCommand", "ScrollCommand",
        DEF_COMBO_SCROLL_CMD, Blt_Offset(ComboMenu, yScrollCmdObjPtr), 
	BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_PIXELS_POS, "-yscrollincrement", "yScrollIncrement",
	"ScrollIncrement", DEF_COMBO_SCROLL_INCR, 
         Blt_Offset(ComboMenu, yScrollUnits),BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_OBJ, "-takefocus", "takeFocus", "TakeFocus",
	DEF_COMBO_TAKE_FOCUS, Blt_Offset(ComboMenu, takeFocusObjPtr), 
	BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_OBJ, "-unpostcommand", "unpostCommand", "UnpostCommand", 
	DEF_COMBO_UNPOSTCOMMAND, Blt_Offset(ComboMenu, unpostCmdObjPtr), 
	BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_CUSTOM, "-width", "width", "Width", DEF_COMBO_WIDTH, 
	Blt_Offset(ComboMenu, reqWidth), BLT_CONFIG_DONT_SET_DEFAULT,
	&bltLimitsOption},
#ifdef notdef
    {BLT_CONFIG_CUSTOM, "-radioimage", (char *)NULL, (char *)NULL, 
	DEF_ITEM_IMAGE, Blt_Offset(ComboMenu, rbIcon), BLT_CONFIG_NULL_OK, 
        &iconOption},
    {BLT_CONFIG_CUSTOM, "-checkimage", (char *)NULL, (char *)NULL, 
	DEF_ITEM_IMAGE, Blt_Offset(ComboMenu, cbIcon), BLT_CONFIG_NULL_OK, 
        &iconOption},
    {BLT_CONFIG_CUSTOM, "-cascadeimage", (char *)NULL, (char *)NULL, 
	DEF_ITEM_IMAGE, Blt_Offset(ComboMenu, casIcon), BLT_CONFIG_NULL_OK,
        &iconOption},
#endif
    {BLT_CONFIG_COLOR, "-checkbuttonfillcolor", (char *)NULL, (char *)NULL, 
	DEF_COMBO_CHECKBUTTON_FILL_COLOR, 
        Blt_Offset(ComboMenu, checkButtonFillColor), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_COLOR, "-checkbuttonoutlinecolor", (char *)NULL, (char *)NULL, 
	DEF_COMBO_CHECKBUTTON_OUTLINE_COLOR,
	Blt_Offset(ComboMenu, checkButtonOutlineColor), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_COLOR, "-checkbuttoncolor", (char *)NULL, (char *)NULL, 
	DEF_COMBO_CHECKBUTTON_COLOR, Blt_Offset(ComboMenu, checkButtonColor),0},
    {BLT_CONFIG_PIXELS_NNEG, "-checkbuttonsize", (char *)NULL, (char *)NULL, 
	DEF_COMBO_CHECKBUTTON_SIZE, Blt_Offset(ComboMenu, checkButtonReqSize), 
        BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_COLOR, "-radiobuttonfillcolor", (char *)NULL, (char *)NULL, 
	DEF_COMBO_RADIOBUTTON_FILL_COLOR, 
        Blt_Offset(ComboMenu, radioButtonFillColor), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_COLOR, "-radiobuttonoutlinecolor", (char *)NULL, (char *)NULL, 
	DEF_COMBO_RADIOBUTTON_OUTLINE_COLOR, 
        Blt_Offset(ComboMenu, radioButtonOutlineColor), BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_COLOR, "-radiobuttoncolor", (char *)NULL, (char *)NULL, 
	DEF_COMBO_RADIOBUTTON_COLOR, Blt_Offset(ComboMenu, radioButtonColor),0},
    {BLT_CONFIG_PIXELS_NNEG, "-radiobuttonsize", (char *)NULL, (char *)NULL, 
	DEF_COMBO_RADIOBUTTON_SIZE, Blt_Offset(ComboMenu, radioButtonReqSize), 
        BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_END, (char *)NULL, (char *)NULL, (char *)NULL, (char *)NULL, 
	0, 0}
};

/*
 * ItemIterator --
 *
 *	Items may be tagged with strings.  An item may have many tags.  The
 *	same tag may be used for many items.
 *	
 */

typedef enum { 
    ITER_SINGLE, ITER_ALL, ITER_TAG, ITER_TYPE, ITER_PATTERN
} IteratorType;

typedef struct _Iterator {
    ComboMenu *comboPtr;		/* ComboMenu that we're iterating
					 * over. */

    IteratorType type;			/* Type of iteration:
					 * ITER_TAG	By item tag.
					 * ITER_ALL	By every item.
					 * ITER_SINGLE	Single item: either 
					 *		tag or index.
					 * ITER_TYPE	Over a single item 
					 *		type.
					 */

    Item *startPtr, *last;		/* Starting and ending item.  Starting
					 * point of search, saved if iterator
					 * is reused.  Used for ITER_ALL and
					 * ITER_SINGLE searches. */
    Item *endPtr;			/* Ending item (inclusive). */
    Item *nextPtr;			/* Next item. */
    int itemType;			/* For tag-based searches. */
    char *tagName;			/* If non-NULL, is the tag that we are
					 * currently iterating over. */

    Blt_HashTable *tablePtr;		/* Pointer to tag hash table. */

    Blt_HashSearch cursor;		/* Search iterator for tag hash
					 * table. */
    Blt_ChainLink link;
} ItemIterator;

static Tk_GeomRequestProc ScrollbarGeometryProc;
static Tk_GeomLostSlaveProc ScrollbarCustodyProc;
static Tk_GeomMgr comboMgrInfo = {
    (char *)"combomenu",		/* Name of geometry manager used by
					 * winfo. */
    ScrollbarGeometryProc,		/* Procedure to for new geometry
					 * requests. */
    ScrollbarCustodyProc,		/* Procedure when scrollbar is taken
					 * away. */
};

static Blt_SwitchParseProc TypeSwitch;
static Blt_SwitchCustom typeSwitch = {
    TypeSwitch, NULL, NULL,
};
static Blt_SwitchParseProc ItemSwitch;
static Blt_SwitchCustom itemSwitch = {
    ItemSwitch, NULL, NULL,
};

#define FIND_DECREASING	(1<<0)
#define FIND_UNDERLINE	(1<<1)
#define FIND_GLOB	1
#define FIND_REGEXP	2

typedef struct {
    unsigned int mask;
    int search;
    int type;
    Item *fromPtr;
} FindSwitches;

static Blt_SwitchSpec findSwitches[] = 
{
    {BLT_SWITCH_CUSTOM, "-from", "item",
	Blt_Offset(FindSwitches, fromPtr), 0, 0, &itemSwitch},
    {BLT_SWITCH_BITMASK, "-decreasing", "",
	Blt_Offset(FindSwitches, mask), 0, FIND_DECREASING},
    {BLT_SWITCH_VALUE, "-glob", "",
	Blt_Offset(FindSwitches, search), 0, FIND_GLOB},
    {BLT_SWITCH_VALUE, "-regexp", "",
	Blt_Offset(FindSwitches, search), 0, FIND_REGEXP},
    {BLT_SWITCH_CUSTOM, "-type", "type",
	Blt_Offset(FindSwitches, type), 0, 0, &typeSwitch},
    {BLT_SWITCH_BITMASK, "-underline", "",
	Blt_Offset(FindSwitches, mask), 0, FIND_UNDERLINE},
    {BLT_SWITCH_END}
};

typedef int (ComboMenuCmdProc)(ComboMenu *comboPtr, Tcl_Interp *interp, 
	int objc, Tcl_Obj *const *objv);
static int GetItemIterator(Tcl_Interp *interp, ComboMenu *comboPtr,
	Tcl_Obj *objPtr, ItemIterator *iterPtr);
static int GetItemFromObj(Tcl_Interp *interp, ComboMenu *comboPtr,
	Tcl_Obj *objPtr, Item **itemPtrPtr);

static Tcl_IdleProc ConfigureScrollbarsProc;
static Tcl_IdleProc DisplayItem;
static Tcl_IdleProc DisplayComboMenu;
static Tcl_FreeProc DestroyComboMenu;
static Tk_EventProc ScrollbarEventProc;
static Tk_EventProc ComboMenuEventProc;
static Tcl_ObjCmdProc ComboMenuInstCmdProc;
static Tcl_CmdDeleteProc ComboMenuInstCmdDeletedProc;
static Tcl_VarTraceProc ItemVarTraceProc;
static Tk_ImageChangedProc IconChangedProc;

/*
 *---------------------------------------------------------------------------
 *
 * EventuallyRedraw --
 *
 *	Tells the Tk dispatcher to call the combomenu display routine at the
 *	next idle point.  This request is made only if the window is displayed
 *	and no other redraw request is pending.
 *
 * Results: None.
 *
 * Side effects:
 *	The window is eventually redisplayed.
 *
 *---------------------------------------------------------------------------
 */
static void
EventuallyRedraw(ComboMenu *comboPtr) 
{
    if ((comboPtr->tkwin != NULL) && !(comboPtr->flags & REDRAW_PENDING)) {
	Tcl_DoWhenIdle(DisplayComboMenu, comboPtr);
	comboPtr->flags |= REDRAW_PENDING;
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * EventuallyRedrawItem --
 *
 *	Tells the Tk dispatcher to call the combomenu display routine at the
 *	next idle point.  This request is made only if the window is displayed
 *	and no other redraw request is pending.
 *
 * Results: None.
 *
 * Side effects:
 *	The window is eventually redisplayed.
 *
 *---------------------------------------------------------------------------
 */
static void
EventuallyRedrawItem(Item *itemPtr) 
{
    ComboMenu *comboPtr;

    comboPtr = itemPtr->comboPtr;
    if ((comboPtr->tkwin != NULL) && 
	((comboPtr->flags & REDRAW_PENDING) == 0) &&
	((itemPtr->flags & ITEM_REDRAW) == 0)) {
	Tcl_DoWhenIdle(DisplayItem, itemPtr);
	itemPtr->flags |= ITEM_REDRAW;
    }
}

static void
ConfigureScrollbarsProc(ClientData clientData)
{
    ComboMenu *comboPtr = clientData;
    Tcl_Interp *interp;

    interp = comboPtr->interp;
    /* 
     * Execute the initialization procedure on this widget.
     */
    comboPtr->flags &= ~UPDATE_PENDING;
    if (Tcl_VarEval(interp, "::blt::ComboMenu::ConfigureScrollbars ", 
	Tk_PathName(comboPtr->tkwin), (char *)NULL) != TCL_OK) {
	Tcl_BackgroundError(interp);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * ReleaseTags --
 *
 *	Releases the tags used by this item.  
 *
 *---------------------------------------------------------------------------
 */
static void
ReleaseTags(ComboMenu *comboPtr, Item *itemPtr)
{
    Blt_HashEntry *hPtr;
    Blt_HashSearch iter;

    for (hPtr = Blt_FirstHashEntry(&comboPtr->tagTable, &iter); hPtr != NULL;
	 hPtr = Blt_NextHashEntry(&iter)) {
	Blt_HashTable *tagTablePtr;
	Blt_HashEntry *h2Ptr;

	tagTablePtr = Blt_GetHashValue(hPtr); 
	h2Ptr = Blt_FindHashEntry(tagTablePtr, (char *)itemPtr->index);
	if (h2Ptr != NULL) {
	    Blt_DeleteHashEntry(tagTablePtr, h2Ptr);
	}
    }
}

static void
DestroyItem(Item *itemPtr)
{
    ComboMenu *comboPtr = itemPtr->comboPtr;

    ReleaseTags(comboPtr, itemPtr);
    iconOption.clientData = comboPtr;
    Blt_FreeOptions(itemConfigSpecs, (char *)itemPtr, comboPtr->display, 0);
    if (comboPtr->activePtr == itemPtr) {
	comboPtr->activePtr = NULL;
    }
    if (comboPtr->postedPtr == itemPtr) {
	comboPtr->postedPtr = NULL;
    }
    Blt_Chain_DeleteLink(comboPtr->chain, itemPtr->link);
}

static void
DestroyItems(ComboMenu *comboPtr)
{
    Blt_ChainLink link, next;

    for (link = Blt_Chain_FirstLink(comboPtr->chain); link != NULL; 
	 link = next) {
	Item *itemPtr;

	next = Blt_Chain_NextLink(link);
	itemPtr = Blt_Chain_GetValue(link);
	DestroyItem(itemPtr);
    }
    Blt_Chain_Destroy(comboPtr->chain);
}

static Item *
NewItem(ComboMenu *comboPtr)
{
    Item *itemPtr;
    Blt_ChainLink link;

    link = Blt_Chain_AllocLink(sizeof(Item));
    itemPtr = Blt_Chain_GetValue(link);
    itemPtr->comboPtr = comboPtr;
    itemPtr->flags |= (ITEM_BUTTON | ITEM_NORMAL);
    itemPtr->link = link;
    itemPtr->index = Blt_Chain_GetLength(comboPtr->chain);
    Blt_Chain_LinkAfter(comboPtr->chain, link, NULL);
    itemPtr->label = emptyString;
    itemPtr->underline = -1;
    return itemPtr;
}

static INLINE Item *
FindItemByIndex(ComboMenu *comboPtr, long index)
{
    Blt_ChainLink link;

    if ((index < 1) || (index > Blt_Chain_GetLength(comboPtr->chain))) {
	return NULL;
    }
    link = Blt_Chain_GetNthLink(comboPtr->chain, index - 1);
    return Blt_Chain_GetValue(link);
}

static INLINE Item *
FirstItem(ComboMenu *comboPtr)
{
    Blt_ChainLink link;

    for (link = Blt_Chain_FirstLink(comboPtr->chain); link != NULL;
	 link = Blt_Chain_NextLink(link)) {
	Item *itemPtr;

	itemPtr = Blt_Chain_GetValue(link);
	if ((itemPtr->flags & ITEM_DISABLED) == 0) {
	    return itemPtr;
	}
    }
    return NULL;
}

static INLINE Item *
LastItem(ComboMenu *comboPtr)
{
    Blt_ChainLink link;

    for (link = Blt_Chain_LastLink(comboPtr->chain); link != NULL;
	 link = Blt_Chain_PrevLink(link)) {
	Item *itemPtr;

	itemPtr = Blt_Chain_GetValue(link);
	if ((itemPtr->flags & ITEM_DISABLED) == 0) {
	    return itemPtr;
	}
    }
    return NULL;
}


static Item *
NextItem(Item *itemPtr)
{
    if (itemPtr != NULL) {
	Blt_ChainLink link;

	for (link = Blt_Chain_NextLink(itemPtr->link); link != NULL; 
	     link = Blt_Chain_NextLink(link)) {
	    itemPtr = Blt_Chain_GetValue(link);
	    if ((itemPtr->flags & (ITEM_SEPARATOR|ITEM_DISABLED)) == 0) {
		return itemPtr;
	    }
	}
    }
    return NULL;
}

static INLINE Item *
PrevItem(Item *itemPtr)
{
    if (itemPtr != NULL) {
	Blt_ChainLink link;
	
	for (link = Blt_Chain_PrevLink(itemPtr->link); link != NULL; 
	     link = Blt_Chain_PrevLink(link)) {
	    itemPtr = Blt_Chain_GetValue(link);
	    if ((itemPtr->flags & (ITEM_SEPARATOR|ITEM_DISABLED)) == 0) {
		return itemPtr;
	    }
	}
    }
    return NULL;
}

static INLINE Item *
BeginItem(ComboMenu *comboPtr)
{
    Blt_ChainLink link;

    link = Blt_Chain_FirstLink(comboPtr->chain); 
    if (link != NULL) {
	return Blt_Chain_GetValue(link);
    }
    return NULL;
}

static INLINE Item *
EndItem(ComboMenu *comboPtr)
{
    Blt_ChainLink link;

    link = Blt_Chain_LastLink(comboPtr->chain); 
    if (link != NULL) {
	return Blt_Chain_GetValue(link);
    }
    return NULL;
}

static Item *
StepItem(Item *itemPtr)
{
    if (itemPtr != NULL) {
	Blt_ChainLink link;

	link = Blt_Chain_NextLink(itemPtr->link); 
	if (link != NULL) {
	    return Blt_Chain_GetValue(link);
	}
    }
    return NULL;
}

static int
SelectItem(Tcl_Interp *interp, ComboMenu *comboPtr, Item *itemPtr, int newState)
{
    int result;

    if (itemPtr->flags & (ITEM_CASCADE|ITEM_SEPARATOR)) {
	return TCL_OK;
    }

    result = TCL_OK;
    if (newState == -1) {
	newState = (itemPtr->flags & ITEM_SELECTED) == 0;
    }
    if ((comboPtr->iconVarObjPtr != NULL) && (itemPtr->icon != NULL)) {
	Tcl_Obj *objPtr;
	
	objPtr = Tcl_NewStringObj(IconName(itemPtr->icon), -1);
	if (Tcl_ObjSetVar2(interp, comboPtr->iconVarObjPtr, NULL, objPtr, 
			   TCL_GLOBAL_ONLY|TCL_LEAVE_ERR_MSG) == NULL) {
	    return TCL_ERROR;
	}
    }
    if ((comboPtr->textVarObjPtr != NULL) && (itemPtr->label != emptyString)) {
	Tcl_Obj *objPtr;
	
	objPtr = Tcl_NewStringObj(itemPtr->label, -1);
	if (Tcl_ObjSetVar2(interp, comboPtr->textVarObjPtr, NULL, objPtr, 
			   TCL_GLOBAL_ONLY|TCL_LEAVE_ERR_MSG) == NULL) {
	    return TCL_ERROR;
	}
    }
    if (itemPtr->variableObjPtr != NULL) {
	Tcl_Obj *objPtr;
	
	objPtr = NULL;
	if (itemPtr->flags & ITEM_CHECKBUTTON) {
	    objPtr = (newState) ? 
		itemPtr->onValueObjPtr : itemPtr->offValueObjPtr;
	} else {
	    objPtr = itemPtr->valueObjPtr;
	    if (objPtr == NULL) {
		objPtr = Tcl_NewStringObj(itemPtr->label, -1);
	    }
	}
	if (objPtr != NULL) {
	    Tcl_IncrRefCount(objPtr);
	    if (Tcl_ObjSetVar2(interp, itemPtr->variableObjPtr, NULL, objPtr, 
			       TCL_GLOBAL_ONLY|TCL_LEAVE_ERR_MSG) == NULL) {
		result = TCL_ERROR;
	    }
	    Tcl_DecrRefCount(objPtr);
	}
    }
    return result;
}

/*
 *---------------------------------------------------------------------------
 *
 * ActivateItem --
 *
 *	Marks the designated item as active.  The item is redrawn with its
 *	active colors.  The previously active item is deactivated.  If the new
 *	item is NULL, then this means that no new item is to be activated.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Menu items may be scheduled to be drawn.
 *
 *---------------------------------------------------------------------------
 */
static void
ActivateItem(ComboMenu *comboPtr, Item *itemPtr) 
{
    if ((comboPtr->activePtr == itemPtr) && (itemPtr != NULL)) {
	return;		/* Item is already active. */
    }
    if (comboPtr->activePtr != NULL) {
	EventuallyRedrawItem(comboPtr->activePtr);
    }
    comboPtr->activePtr = itemPtr;
    if (itemPtr != NULL) {
	EventuallyRedrawItem(itemPtr);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * GetBoundedWidth --
 *
 *	Bounds a given width value to the limits described in the limit
 *	structure.  The initial starting value may be overridden by the nominal
 *	value in the limits.
 *
 * Results:
 *	Returns the constrained value.
 *
 *---------------------------------------------------------------------------
 */
static int
GetBoundedWidth(ComboMenu *comboPtr, int w)	
{
    /*
     * Check widgets for requested width values;
     */
    if (comboPtr->reqWidth.flags & LIMITS_NOM_SET) {
	w = comboPtr->reqWidth.nom;	/* Override initial value */
    }
    if (w < comboPtr->reqWidth.min) {
	w = comboPtr->reqWidth.min;	/* Bounded by minimum value */
    }
    if (w > comboPtr->reqWidth.max) {
	w = comboPtr->reqWidth.max;	/* Bounded by maximum value */
    }
    if (comboPtr->flags & (RESTRICT_MIN|RESTRICT_MAX)) {
	Tk_Window parent;

	parent = Tk_Parent(comboPtr->tkwin);
	if ((comboPtr->flags & RESTRICT_MIN) && (w < Tk_Width(parent))) {
	    w = Tk_Width(parent);
	}
	if ((comboPtr->flags & RESTRICT_MAX) && (w > Tk_Width(parent))) {
	    w = Tk_Width(parent);
	}
    }
    {
	int screenWidth, screenHeight;

	Blt_SizeOfScreen(comboPtr->tkwin, &screenWidth, &screenHeight);
	if (w > screenWidth) {
	    w = screenWidth;
	}
    }
    return w;
}

/*
 *---------------------------------------------------------------------------
 *
 * GetBoundedHeight --
 *
 *	Bounds a given value to the limits described in the limit structure.
 *	The initial starting value may be overridden by the nominal value in
 *	the limits.
 *
 * Results:
 *	Returns the constrained value.
 *
 *---------------------------------------------------------------------------
 */
static int
GetBoundedHeight(ComboMenu *comboPtr, int h)	
{
    /*
     * Check widgets for requested height values;
     */
    if (comboPtr->reqHeight.flags & LIMITS_NOM_SET) {
	h = comboPtr->reqHeight.nom;	/* Override initial value */
    }
    if (h < comboPtr->reqHeight.min) {
	h = comboPtr->reqHeight.min;	/* Bounded by minimum value */
    }
    if (h > comboPtr->reqHeight.max) {
	h = comboPtr->reqHeight.max;	/* Bounded by maximum value */
    }
    if (h > HeightOfScreen(Tk_Screen(comboPtr->tkwin))) {
	h = HeightOfScreen(Tk_Screen(comboPtr->tkwin));
    }
    return h;
}

static void
FixMenuCoords(ComboMenu *comboPtr, Tk_Window parent, int *xPtr, int *yPtr)
{
    int x, y, w, h, pw, ph;
    int screenWidth, screenHeight;

    Blt_SizeOfScreen(comboPtr->tkwin, &screenWidth, &screenHeight);
    x = *xPtr, y = *yPtr;

    /* Determine the size of the menu. */
    w = Tk_ReqWidth(comboPtr->tkwin);
    h = Tk_ReqHeight(comboPtr->tkwin);
    if (parent == comboPtr->tkwin) {	/* This is a popup. */
	pw = w;
	ph = h;
    } else {
	pw = Tk_Width(parent);
	ph = Tk_Height(parent);
    }
    if ((y + h) > screenHeight) {
	y -= (ph + h);			/* Flip to show menu above. */
	if (y < 0) {
	    y = 0;
	}
    }
    if ((x + w) > screenWidth) {
	x -= pw;			/* Flip to show menu on left side. */
	if (x < 0) {
	    x = 0;
	}
    }
    *xPtr = x;
    *yPtr = y;
}

static void
ComputeItemGeometry(ComboMenu *comboPtr, Item *itemPtr)
{

    /* Determine the height of the item.  It's the maximum height of all it's
     * components: left gadget (radiobutton or checkbutton), icon, label,
     * right gadget (cascade), and accelerator. */
    itemPtr->labelWidth = itemPtr->labelHeight = 0;
    itemPtr->leftIndWidth = itemPtr->leftIndHeight = 0;
    itemPtr->rightIndWidth = itemPtr->rightIndHeight = 0;
    itemPtr->iconWidth = itemPtr->iconHeight = 0;
    itemPtr->width = itemPtr->height = 0;
    if (itemPtr->flags & ITEM_SEPARATOR) {
	itemPtr->height = ITEM_SEP_HEIGHT;
	itemPtr->width = 0;
	if (itemPtr->image != NULL) {
	    itemPtr->labelWidth = IconWidth(itemPtr->image);
	    itemPtr->labelHeight = IconHeight(itemPtr->image);
	    if (itemPtr->height < itemPtr->labelHeight) {
		itemPtr->height = itemPtr->labelHeight;
	    }
	} else if (itemPtr->label != emptyString) {
	    unsigned int w, h;
	    
	    Blt_GetTextExtents(itemPtr->stylePtr->labelFont, 0, itemPtr->label,
		 -1, &w, &h);
	    itemPtr->labelWidth = w;
	    itemPtr->labelHeight = h;
	    if (itemPtr->height < itemPtr->labelHeight) {
		itemPtr->height = itemPtr->labelHeight;
	    }
	}
	if (itemPtr->labelWidth > 0) {
	    itemPtr->width += itemPtr->labelWidth + ITEM_IPAD;
	}
    } else {
	if (itemPtr->flags & (ITEM_RADIOBUTTON | ITEM_CHECKBUTTON)) {
	    Blt_FontMetrics fm;
	    size_t reqSize;

	    Blt_GetFontMetrics(itemPtr->stylePtr->labelFont, &fm);
	    itemPtr->leftIndWidth = itemPtr->leftIndHeight =
		(fm.linespace) + 4 * ITEM_YPAD;
#ifdef notdef
	    itemPtr->leftIndWidth = ITEM_L_IND_WIDTH;
	    itemPtr->leftIndHeight = ITEM_L_IND_HEIGHT;
#endif
	    reqSize = itemPtr->stylePtr->reqIndWidth;
	    if (reqSize == 0) { 
		reqSize = (itemPtr->flags & ITEM_RADIOBUTTON) ?
		    comboPtr->radioButtonReqSize : comboPtr->checkButtonReqSize;
	    }
	    if (reqSize > 0) {
		itemPtr->leftIndWidth = itemPtr->leftIndHeight = 
		    reqSize + 2*ITEM_YPAD;
	    }
	    if (itemPtr->height < itemPtr->leftIndHeight) {
		itemPtr->height = itemPtr->leftIndHeight;
	    }
	    itemPtr->width += itemPtr->leftIndWidth + 2 * ITEM_IPAD;
	}

	if (itemPtr->icon != NULL) {
	    itemPtr->iconWidth = IconWidth(itemPtr->icon);
	    itemPtr->iconHeight = IconHeight(itemPtr->icon);
	    if (itemPtr->height < IconHeight(itemPtr->icon)) {
		itemPtr->height = IconHeight(itemPtr->icon);
	    }
	    itemPtr->width += itemPtr->iconWidth + ITEM_IPAD;
	}

	if (itemPtr->image != NULL) {
	    itemPtr->labelWidth = IconWidth(itemPtr->image);
	    itemPtr->labelHeight = IconHeight(itemPtr->image);
	    if (itemPtr->height < itemPtr->labelHeight) {
		itemPtr->height = itemPtr->labelHeight;
	    }
	} else if (itemPtr->label != emptyString) {
	    unsigned int w, h;
	    
	    Blt_GetTextExtents(itemPtr->stylePtr->labelFont, 0, itemPtr->label,
		 -1, &w, &h);
	    itemPtr->labelWidth = w;
	    itemPtr->labelHeight = h;
	    if (itemPtr->height < itemPtr->labelHeight) {
		itemPtr->height = itemPtr->labelHeight;
	    }
	}

	if (itemPtr->labelWidth > 0) {
	    itemPtr->width += itemPtr->labelWidth + ITEM_IPAD;
	}

	if (itemPtr->flags & ITEM_CASCADE) {
	    itemPtr->rightIndWidth = ITEM_R_IND_WIDTH;
	    itemPtr->rightIndHeight = ITEM_R_IND_HEIGHT;
	} else if (itemPtr->accel != NULL) {
	    unsigned int w, h;
	    
	    Blt_GetTextExtents(itemPtr->stylePtr->accelFont, 0, itemPtr->accel,
		 -1, &w, &h);
	    itemPtr->rightIndWidth = w;
	    itemPtr->rightIndHeight = h;
	}
	if (itemPtr->height < itemPtr->rightIndHeight) {
	    itemPtr->height = itemPtr->rightIndHeight;
	}
    }
    itemPtr->width += 2 * itemPtr->stylePtr->borderWidth;
    itemPtr->height += 2 * (ITEM_XPAD + itemPtr->stylePtr->borderWidth);
#ifdef notdef
    fprintf(stderr, "%s= w=%d,h=%d leftInd w=%d,h=%d icon w=%d,h=%d label w=%d,h=%d rightInd w=%d,h=%d\n", 
	    itemPtr->label, itemPtr->width, itemPtr->height, 
	    itemPtr->leftIndWidth, itemPtr->leftIndHeight, 
	    itemPtr->iconWidth, itemPtr->iconHeight, itemPtr->labelWidth,
	    itemPtr->labelHeight, itemPtr->rightIndWidth, 
	    itemPtr->rightIndHeight);
#endif
}

/*
 *---------------------------------------------------------------------------
 *
 * SearchForItem --
 *
 *	Performs a binary search for the item at the given y-offset in world
 *	coordinates.  The range of items is specified by menu indices (high
 *	and low).  The item must be (visible) in the viewport.
 *
 * Results:
 *	Returns 0 if no item is found, other the index of the item (menu
 *	indices start from 1).
 *
 *---------------------------------------------------------------------------
 */
static Item *
SearchForItem(ComboMenu *comboPtr, Item *firstPtr, Item *lastPtr, int yOffset)
{
    Blt_ChainLink first, last, link, next;

    first = (firstPtr == NULL) ? 
	Blt_Chain_FirstLink(comboPtr->chain): firstPtr->link;
    last = (lastPtr == NULL) ? 
	Blt_Chain_LastLink(comboPtr->chain) : lastPtr->link;

    for (link = first; link != NULL; link = next) {
	Item *itemPtr;

	next = Blt_Chain_NextLink(link);
	itemPtr = Blt_Chain_GetValue(link);
	if ((yOffset >= itemPtr->yWorld) && 
	    (yOffset < (itemPtr->yWorld + itemPtr->height))) {
	    return itemPtr;
	}
	if (link == last) {
	    break;
	}
    }
    return NULL;
}

static void
ComputeVisibleItems(ComboMenu *comboPtr)
{
    Item *itemPtr;
    int cavityWidth, cavityHeight;

    if (Blt_Chain_GetLength(comboPtr->chain) == 0) {
	comboPtr->firstPtr = comboPtr->lastPtr = NULL;
	return;
    }
    cavityWidth = Tk_Width(comboPtr->tkwin);
    cavityHeight = Tk_Height(comboPtr->tkwin);
    comboPtr->xScrollbarHeight = comboPtr->yScrollbarWidth = 0;
    if ((comboPtr->xScrollbar != NULL) && (comboPtr->worldWidth > cavityWidth)){
	comboPtr->xScrollbarHeight = Tk_ReqHeight(comboPtr->xScrollbar);
	if (comboPtr->xScrollbarHeight > MAXSCROLLBARTHICKNESS) {
	    comboPtr->xScrollbarHeight = MAXSCROLLBARTHICKNESS;
	}
	cavityHeight -= comboPtr->xScrollbarHeight;
    } 
    if ((comboPtr->yScrollbar != NULL) && (comboPtr->worldHeight>cavityHeight)){
	comboPtr->yScrollbarWidth = Tk_ReqWidth(comboPtr->yScrollbar);
	if (comboPtr->yScrollbarWidth > MAXSCROLLBARTHICKNESS) {
	    comboPtr->yScrollbarWidth = MAXSCROLLBARTHICKNESS;
	}
	cavityWidth -= comboPtr->yScrollbarWidth;
    }
    if ((comboPtr->xScrollbar != NULL) && (comboPtr->xScrollbarHeight == 0) && 
	(comboPtr->worldWidth > cavityWidth)) {
	comboPtr->xScrollbarHeight = Tk_ReqHeight(comboPtr->xScrollbar);
	if (comboPtr->xScrollbarHeight > MAXSCROLLBARTHICKNESS) {
	    comboPtr->xScrollbarHeight = MAXSCROLLBARTHICKNESS;
	}
	cavityHeight -= comboPtr->xScrollbarHeight;
    }
    if ((comboPtr->yScrollbar != NULL) && (comboPtr->yScrollbarWidth == 0) && 
	(comboPtr->worldHeight > cavityHeight)) {
	comboPtr->yScrollbarWidth = Tk_ReqWidth(comboPtr->yScrollbar);
	if (comboPtr->yScrollbarWidth > MAXSCROLLBARTHICKNESS) {
	    comboPtr->yScrollbarWidth = MAXSCROLLBARTHICKNESS;
	}
	cavityWidth -= comboPtr->yScrollbarWidth;
    }
    comboPtr->width = cavityWidth;
    comboPtr->height = cavityHeight;
    itemPtr = SearchForItem(comboPtr, NULL, NULL, comboPtr->yOffset);
    if (itemPtr == NULL) {
	Blt_ChainLink link;

	link = Blt_Chain_LastLink(comboPtr->chain);
	comboPtr->firstPtr = comboPtr->lastPtr = Blt_Chain_GetValue(link);
	return;
    }
    comboPtr->firstPtr = itemPtr;

    itemPtr = SearchForItem(comboPtr, comboPtr->firstPtr, NULL, 
			    comboPtr->yOffset + VPORTHEIGHT(comboPtr)); 
    if (itemPtr == NULL) {
	Blt_ChainLink link;

	link = Blt_Chain_LastLink(comboPtr->chain);
	comboPtr->lastPtr = Blt_Chain_GetValue(link);
	return;
    } 
    comboPtr->lastPtr = itemPtr;
}

/*
 *---------------------------------------------------------------------------
 *
 * NearestItem --
 *
 *	Find the item closest to the x-y screen coordinate given.  The item
 *	must be (visible) in the viewport.
 *
 * Results:
 *	Returns the closest item.  If selectOne is set, then always returns an
 *	item (unless the menu is empty).  Otherwise, NULL is returned is the
 *	pointer is not over an item.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static Item *
NearestItem(ComboMenu *comboPtr, int x, int y, int selectOne)
{
    Item *itemPtr;

    if (comboPtr->firstPtr == NULL) {
	return NULL;			/* No visible entries. */
    }
    if ((x < 0) || (x >= Tk_Width(comboPtr->tkwin)) || 
	(y < 0) || (y >= Tk_Height(comboPtr->tkwin))) {
	return NULL;			/* Screen coordinates are outside of
					 * menu. */
    }
    /*
     * Item positions are saved in world coordinates. Convert the text point
     * screen y-coordinate to a world coordinate.
     */
    itemPtr = SearchForItem(comboPtr, comboPtr->firstPtr, comboPtr->lastPtr, 
	WORLDY(comboPtr, y));
    if (itemPtr == NULL) {
	if (!selectOne) {
	    return NULL;
	}
	if (y < comboPtr->borderWidth) {
	    return FirstItem(comboPtr);
	}
	return LastItem(comboPtr);
    }
    return itemPtr;
}

static void
ComputeCascadeMenuCoords(ComboMenu *comboPtr, Item *itemPtr, Tk_Window menuWin, 
			 int *xPtr, int *yPtr)
{
    int rootX, rootY, x, y;
    int screenWidth, screenHeight;

    x = Tk_Width(comboPtr->tkwin);
    y = SCREENY(comboPtr, itemPtr->yWorld);
    Blt_SizeOfScreen(comboPtr->tkwin, &screenWidth, &screenHeight);
    Tk_GetRootCoords(comboPtr->tkwin, &rootX, &rootY);
    if (rootX < 0) {
	rootX = 0;
    }
    if (rootY < 0) {
	rootY = 0;
    }
    x += rootX, y += rootY;
    if ((y + Tk_ReqHeight(menuWin)) > screenHeight) {
	/* If we go offscreen on the bottom, raised the menu. */
	y = screenHeight - Tk_ReqHeight(menuWin) - 10;
	if (y < 0) {
	    y = 0;
	}
    }
    if ((x + Tk_ReqWidth(menuWin)) > screenWidth) {
	/* If we go offscreen on the bottom, try the menu on the other side. */
	x = rootX - Tk_ReqWidth(menuWin);
	if (x < 0) {
	    x = 0;
	}
    }
    *xPtr = x;
    *yPtr = y;
}

/*
 *---------------------------------------------------------------------------
 *
 * UnpostCascade --
 *
 *	This procedure arranges for the currently active item's cascade menu
 *	to be unposted (i.e. the submenu is unmapped).  Only the active item
 *	can have it's submenu unposted.
 *
 * Results:
 *	A standard TCL return result.  Errors may occur in the TCL commands
 *	generated to unpost submenus.
 *
 * Side effects:
 *	The currently active item's submenu is unposted.
 *
 *---------------------------------------------------------------------------
 */
static int
UnpostCascade(
    Tcl_Interp *interp,			/* Used for invoking "unpost" commands
					 * and reporting errors. */
    ComboMenu *comboPtr)		/* Information about the menu. */
{
    Item *itemPtr = comboPtr->postedPtr;
    char *menuName;
    Tk_Window menuWin;

    if ((itemPtr == NULL) || (itemPtr->menuObjPtr == NULL)) {
	return TCL_OK;			/* No item currenly posted or no menu
					 * designated for cascade item. */
    }
    comboPtr->postedPtr = NULL;
    assert((itemPtr != NULL) && (itemPtr->flags & ITEM_CASCADE));
    menuName = Tcl_GetString(itemPtr->menuObjPtr);
    menuWin = Tk_NameToWindow(interp, menuName, comboPtr->tkwin);
    if (menuWin == NULL) {
	return TCL_ERROR;
    }
    if (Tk_Parent(menuWin) != comboPtr->tkwin) {
	if (interp != NULL) {
	    Tcl_AppendResult(interp, "can't unpost \"", Tk_PathName(menuWin), 
			"\": it isn't a descendant of ", 
			Tk_PathName(comboPtr->tkwin), (char *)NULL);
	}
	return TCL_ERROR;
    }
    Blt_UnmapToplevelWindow(menuWin);
    /*
     * Note: when unposting a submenu, we have to redraw the entire
     * parent menu.  This is because of a combination of the following
     * things:
     * (a) the submenu partially overlaps the parent.
     * (b) the submenu specifies "save under", which causes the X
     *     server to make a copy of the information under it when it
     *     is posted.  When the submenu is unposted, the X server
     *     copies this data back and doesn't generate any Expose
     *     events for the parent.
     * (c) the parent may have redisplayed itself after the submenu
     *     was posted, in which case the saved information is no
     *     longer correct.
     * The simplest solution is just force a complete redisplay of
     * the parent.
     */
    
    EventuallyRedraw(comboPtr);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * PostCascade --
 *
 *	This procedure arranges for the currently active item's cascade menu
 *	to be posted.  Only the active item can have it's submenu posted.
 *
 * Results:
 *	A standard TCL return result.  Errors may occur in the TCL commands
 *	generated to post submenus.
 *
 * Side effects:
 *	The new submenu is posted.
 *
 *---------------------------------------------------------------------------
 */
static int
PostCascade(
    Tcl_Interp *interp,			/* Used for invoking "post" command
					 * and reporting errors. */
    ComboMenu *comboPtr,		/* Information about the menu. */
    Item *itemPtr)			/* Cascade item   */
{
    char *menuName;
    Tk_Window menuWin;

    assert((itemPtr != NULL) && (itemPtr->flags & ITEM_CASCADE));
    if (itemPtr->menuObjPtr == NULL) {
	return TCL_OK;			/* No menu was designated for this
					 * cascade item. */
    }
    if (comboPtr->postedPtr == itemPtr) {
#ifdef notdef
	fprintf(stderr, "postcascade: %s is already posted\n",
		Tcl_GetString(itemPtr->menuObjPtr));
#endif
	return TCL_OK;			/* Item is already posted. */
    }
    menuName = Tcl_GetString(itemPtr->menuObjPtr);
    menuWin = Tk_NameToWindow(interp, menuName, comboPtr->tkwin);
    if (menuWin == NULL) {
	return TCL_ERROR;
    }
    if (Tk_Parent(menuWin) != comboPtr->tkwin) {
	Tcl_AppendResult(interp, "can't post \"", Tk_PathName(menuWin), 
		"\": it isn't a descendant of ", Tk_PathName(comboPtr->tkwin),
		(char *)NULL);
	return TCL_ERROR;
    }
    if (Tk_IsMapped(comboPtr->tkwin)) {
	Tcl_Obj *objv[4];
	int result, x, y;

	/*
	 * Position the cascade with its upper left corner slightly below and
	 * to the left of the upper right corner of the menu entry (this is an
	 * attempt to match Motif behavior).
	 *
	 * The menu has to redrawn so that the entry can change relief.
	 */
	ComputeCascadeMenuCoords(comboPtr, itemPtr, menuWin, &x, &y);
	objv[0] = itemPtr->menuObjPtr;
	objv[1] = Tcl_NewStringObj("post", 4);
	objv[2] = Tcl_NewIntObj(x);
	objv[3] = Tcl_NewIntObj(y);
	result = Blt_GlobalEvalObjv(interp, 4, objv);
	if (result != TCL_OK) {
	    return result;
	}
	EventuallyRedrawItem(itemPtr);
    }
    comboPtr->postedPtr = itemPtr;
    return TCL_OK;
}

static void
ComputeComboGeometry(ComboMenu *comboPtr)
{
    int xWorld, yWorld;
    Blt_ChainLink link;
    int w, h;
    int reqWidth, reqHeight;

    /* 
     * Step 1.  Collect the maximum widths of the items in their individual
     *		columns.
     */
    comboPtr->worldHeight = 0;
    comboPtr->width = comboPtr->height = 0;
    comboPtr->leftIndWidth = comboPtr->rightIndWidth = 0;
    comboPtr->iconWidth = comboPtr->labelWidth = 0;
    xWorld = yWorld = 0;
    for (link = Blt_Chain_FirstLink(comboPtr->chain); link != NULL;
	 link = Blt_Chain_NextLink(link)) {
	Item *itemPtr;

	itemPtr = Blt_Chain_GetValue(link);
	ComputeItemGeometry(comboPtr, itemPtr);
	if (itemPtr->leftIndWidth > comboPtr->leftIndWidth) {
	    comboPtr->leftIndWidth = itemPtr->leftIndWidth;
	}
	if (itemPtr->iconWidth > comboPtr->iconWidth) {
	    comboPtr->iconWidth = itemPtr->iconWidth;
	}
	if (itemPtr->labelWidth > comboPtr->labelWidth) {
	    comboPtr->labelWidth = itemPtr->labelWidth;
	}
	if (itemPtr->rightIndWidth > comboPtr->rightIndWidth) {
	    comboPtr->rightIndWidth = itemPtr->rightIndWidth;
	}
	comboPtr->worldHeight += itemPtr->height;
	itemPtr->xWorld = xWorld, itemPtr->yWorld = yWorld;
	yWorld += itemPtr->height;
    }
    comboPtr->worldWidth = comboPtr->leftIndWidth + comboPtr->iconWidth + 
	comboPtr->labelWidth + comboPtr->rightIndWidth;
    if (comboPtr->leftIndWidth > 0) {
	comboPtr->worldWidth += ITEM_IPAD;
    }
    if (comboPtr->iconWidth > 0) {
	comboPtr->worldWidth += ITEM_IPAD;
    }
    if (comboPtr->labelWidth > 0) {
	comboPtr->worldWidth += ITEM_IPAD;
    }
    if (comboPtr->rightIndWidth > 0) {
	comboPtr->worldWidth += 4 * ITEM_IPAD;
    }
    comboPtr->worldWidth += ITEM_IPAD;
    comboPtr->xScrollbarHeight = comboPtr->yScrollbarWidth = 0;

    /* Figure out the requested size of the widget.  This will also tell us if
     * we need scrollbars. */
 
    reqWidth = comboPtr->worldWidth + 2 * comboPtr->borderWidth;
    reqHeight = comboPtr->worldHeight + 2 * comboPtr->borderWidth;

    w = GetBoundedWidth(comboPtr, reqWidth);
    h = GetBoundedHeight(comboPtr, reqHeight);


    if ((reqWidth > w) && (comboPtr->xScrollbar != NULL)) {
	comboPtr->xScrollbarHeight = Tk_ReqHeight(comboPtr->xScrollbar);
	h = GetBoundedHeight(comboPtr, reqHeight + comboPtr->xScrollbarHeight);
    }
    if ((reqHeight > h) && (comboPtr->yScrollbar != NULL)) {
	comboPtr->yScrollbarWidth = Tk_ReqWidth(comboPtr->yScrollbar);
	w = GetBoundedWidth(comboPtr, reqWidth + comboPtr->yScrollbarWidth);
    }
    /* Save the computed width so that we only override the menu width if the
     * parent (combobutton/comboentry) width is greater than the normal size
     * of the menu.  */
    comboPtr->normalWidth = w;
    comboPtr->normalHeight = h;
    if (h < 20) {
	h = 20;
    }
    if (w < comboPtr->parentWidth) {
	w = comboPtr->parentWidth;
    }
    comboPtr->width = w;
    comboPtr->height = h;
#ifdef notdef
    fprintf(stderr, "%s= w=%d leftInd w=%d icon w=%d label w=%d rightInd w=%d\n", 
	    Tk_PathName(comboPtr->tkwin), comboPtr->width, 
	    comboPtr->leftIndWidth, comboPtr->iconWidth, comboPtr->labelWidth,
	    comboPtr->rightIndWidth);
#endif
    if (w != Tk_ReqWidth(comboPtr->tkwin)) {
	comboPtr->xOffset = 0;
    }
    if (h != Tk_ReqHeight(comboPtr->tkwin)) {
	comboPtr->yOffset = 0;
    }

    if ((w != Tk_ReqWidth(comboPtr->tkwin)) || 
	(h != Tk_ReqHeight(comboPtr->tkwin))) {
	Tk_GeometryRequest(comboPtr->tkwin, w, h);
    }
    comboPtr->flags |= SCROLL_PENDING | LAYOUT_PENDING;
}

static void
DestroyStyle(Style *stylePtr)
{
    ComboMenu *comboPtr;
    int i;

    stylePtr->refCount--;
    if (stylePtr->refCount > 0) {
	return;
    }
    comboPtr = stylePtr->comboPtr;
    iconOption.clientData = comboPtr;
    Blt_FreeOptions(styleConfigSpecs, (char *)stylePtr, comboPtr->display, 0);
    if (stylePtr->labelActiveGC != NULL) {
	Tk_FreeGC(comboPtr->display, stylePtr->labelActiveGC);
    }
    if (stylePtr->labelDisabledGC != NULL) {
	Tk_FreeGC(comboPtr->display, stylePtr->labelDisabledGC);
    }
    if (stylePtr->labelNormalGC != NULL) {
	Tk_FreeGC(comboPtr->display, stylePtr->labelNormalGC);
    }
    if (stylePtr->accelActiveGC != NULL) {
	Tk_FreeGC(comboPtr->display, stylePtr->accelActiveGC);
    }
    if (stylePtr->accelDisabledGC != NULL) {
	Tk_FreeGC(comboPtr->display, stylePtr->accelDisabledGC);
    }
    if (stylePtr->accelNormalGC != NULL) {
	Tk_FreeGC(comboPtr->display, stylePtr->accelNormalGC);
    }
    if (stylePtr->hPtr != NULL) {
	Blt_DeleteHashEntry(&stylePtr->comboPtr->styleTable, stylePtr->hPtr);
    }
    for (i = 0; i < 3; i++) {
	if (stylePtr->radiobutton[i] != NULL) {
	    Blt_FreePicture(stylePtr->radiobutton[i]);
	}
	if (stylePtr->checkbutton[i] != NULL) {
	    Blt_FreePicture(stylePtr->checkbutton[i]);
	}
    }
    if (stylePtr != &stylePtr->comboPtr->defStyle) {
	Blt_Free(stylePtr);
    }
	
}

static Style *
AddDefaultStyle(Tcl_Interp *interp, ComboMenu *comboPtr)
{
    Blt_HashEntry *hPtr;
    int isNew;
    Style *stylePtr;

    hPtr = Blt_CreateHashEntry(&comboPtr->styleTable, "default", &isNew);
    if (!isNew) {
	Tcl_AppendResult(interp, "combomenu style \"", "default", 
		"\" already exists.", (char *)NULL);
	return NULL;
    }
    stylePtr = &comboPtr->defStyle;
    assert(stylePtr);
    stylePtr->refCount = 1;
    stylePtr->name = Blt_GetHashKey(&comboPtr->styleTable, hPtr);
    stylePtr->hPtr = hPtr;
    stylePtr->comboPtr = comboPtr;
    stylePtr->borderWidth = 0;
    stylePtr->activeRelief = TK_RELIEF_FLAT;
    Blt_SetHashValue(hPtr, stylePtr);
    return TCL_OK;
}

static void
DestroyStyles(ComboMenu *comboPtr)
{
    Blt_HashEntry *hPtr;
    Blt_HashSearch iter;

    for (hPtr = Blt_FirstHashEntry(&comboPtr->styleTable, &iter); 
	 hPtr != NULL; hPtr = Blt_NextHashEntry(&iter)) {
	Style *stylePtr;

	stylePtr = Blt_GetHashValue(hPtr);
	stylePtr->hPtr = NULL;
	stylePtr->refCount = 0;
	DestroyStyle(stylePtr);
    }
    Blt_DeleteHashTable(&comboPtr->styleTable);
}

/*
 *---------------------------------------------------------------------------
 *
 * GetStyleFromObj --
 *
 *	Gets the style associated with the given name.  
 *
 *---------------------------------------------------------------------------
 */
static int 
GetStyleFromObj(Tcl_Interp *interp, ComboMenu *comboPtr, Tcl_Obj *objPtr,
		Style **stylePtrPtr)
{
    Blt_HashEntry *hPtr;

    hPtr = Blt_FindHashEntry(&comboPtr->styleTable, Tcl_GetString(objPtr));
    if (hPtr == NULL) {
	if (interp != NULL) {
	    Tcl_AppendResult(interp, "can't find style \"", 
		Tcl_GetString(objPtr), "\" in combomenu \"", 
		Tk_PathName(comboPtr->tkwin), "\"", (char *)NULL);
	}
	return TCL_ERROR;
    }
    *stylePtrPtr = Blt_GetHashValue(hPtr);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * SetTag --
 *
 *	Associates a tag with a given row.  Individual row tags are
 *	stored in hash tables keyed by the tag name.  Each table is in
 *	turn stored in a hash table keyed by the row location.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	A tag is stored for a particular row.
 *
 *---------------------------------------------------------------------------
 */
static int
SetTag(Tcl_Interp *interp, Item *itemPtr, const char *tagName)
{
    Blt_HashEntry *hPtr;
    Blt_HashTable *tagTablePtr;
    ComboMenu *comboPtr;
    int isNew;
    long dummy;
    
    if ((strcmp(tagName, "all") == 0) || (strcmp(tagName, "end") == 0)) {
	return TCL_OK;			/* Don't need to create reserved
					 * tags. */
    }
    if (tagName[0] == '\0') {
	if (interp != NULL) {
	    Tcl_AppendResult(interp, "tag \"", tagName, "\" can't be empty.", 
		(char *)NULL);
	}
	return TCL_ERROR;
    }
    if (tagName[0] == '-') {
	if (interp != NULL) {
	    Tcl_AppendResult(interp, "tag \"", tagName, 
		"\" can't start with a '-'.", (char *)NULL);
	}
	return TCL_ERROR;
    }
    if (Blt_GetLong(NULL, (char *)tagName, &dummy) == TCL_OK) {
	if (interp != NULL) {
	    Tcl_AppendResult(interp, "tag \"", tagName, "\" can't be a number.",
			     (char *)NULL);
	}
	return TCL_ERROR;
    }
    comboPtr = itemPtr->comboPtr;
    hPtr = Blt_CreateHashEntry(&comboPtr->tagTable, tagName, &isNew);
    if (hPtr == NULL) {
	if (interp != NULL) {
	    Tcl_AppendResult(interp, "can't add tag \"", tagName, 
			 "\": out of memory", (char *)NULL);
	}
	return TCL_ERROR;
    }
    if (isNew) {
	tagTablePtr = Blt_AssertMalloc(sizeof(Blt_HashTable));
	Blt_InitHashTable(tagTablePtr, BLT_ONE_WORD_KEYS);
	Blt_SetHashValue(hPtr, tagTablePtr);
    } else {
	tagTablePtr = Blt_GetHashValue(hPtr);
    }
    hPtr = Blt_CreateHashEntry(tagTablePtr, (char *)itemPtr->index, &isNew);
    if (isNew) {
	Blt_SetHashValue(hPtr, itemPtr);
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * GetTagTable --
 *
 *	Returns the hash table containing row indices for a tag.
 *
 * Results:
 *	Returns a pointer to the hash table containing indices for the
 *	given tag.  If the row has no tags, then NULL is returned.
 *
 *---------------------------------------------------------------------------
 */
static Blt_HashTable *
GetTagTable(ComboMenu *comboPtr, const char *tagName)		
{
    Blt_HashEntry *hPtr;

    hPtr = Blt_FindHashEntry(&comboPtr->tagTable, tagName);
    if (hPtr == NULL) {
	return NULL;			/* No tag by that name. */
    }
    return Blt_GetHashValue(hPtr);
}


static void
UnmanageScrollbar(ComboMenu *comboPtr, Tk_Window scrollbar)
{
    if (scrollbar != NULL) {
	Tk_DeleteEventHandler(scrollbar, StructureNotifyMask,
	      ScrollbarEventProc, comboPtr);
	Tk_ManageGeometry(scrollbar, (Tk_GeomMgr *)NULL, comboPtr);
	if (Tk_IsMapped(scrollbar)) {
	    Tk_UnmapWindow(scrollbar);
	}
    }
}

static void
ManageScrollbar(ComboMenu *comboPtr, Tk_Window scrollbar)
{
    if (scrollbar != NULL) {
	Tk_CreateEventHandler(scrollbar, StructureNotifyMask, 
		ScrollbarEventProc, comboPtr);
	Tk_ManageGeometry(scrollbar, &comboMgrInfo, comboPtr);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * InstallScrollbar --
 *
 *	Convert the string representation of a color into a XColor pointer.
 *
 * Results:
 *	The return value is a standard TCL result.  The color pointer is
 *	written into the widget record.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static void
InstallScrollbar(
    Tcl_Interp *interp,			/* Interpreter to send results back
					 * to */
    ComboMenu *comboPtr,
    Tcl_Obj *objPtr,			/* String representing scrollbar
					 * window. */
    Tk_Window *tkwinPtr)
{
    Tk_Window tkwin;

    if (objPtr == NULL) {
	*tkwinPtr = NULL;
	return;
    }
    tkwin = Tk_NameToWindow(interp, Tcl_GetString(objPtr), comboPtr->tkwin);
    if (tkwin == NULL) {
	Tcl_BackgroundError(interp);
	return;
    }
    if (Tk_Parent(tkwin) != comboPtr->tkwin) {
	Tcl_AppendResult(interp, "scrollbar \"", Tk_PathName(tkwin), 
			 "\" must be a child of combomenu.", (char *)NULL);
	Tcl_BackgroundError(interp);
	return;
    }
    ManageScrollbar(comboPtr, tkwin);
    *tkwinPtr = tkwin;
    return;
}

static void
InstallXScrollbar(ClientData clientData)
{
    ComboMenu *comboPtr = clientData;

    comboPtr->flags &= ~INSTALL_XSCROLLBAR;
    InstallScrollbar(comboPtr->interp, comboPtr, comboPtr->xScrollbarObjPtr,
		     &comboPtr->xScrollbar);
}

static void
InstallYScrollbar(ClientData clientData)
{
    ComboMenu *comboPtr = clientData;

    comboPtr->flags &= ~INSTALL_YSCROLLBAR;
    InstallScrollbar(comboPtr->interp, comboPtr, comboPtr->yScrollbarObjPtr,
		     &comboPtr->yScrollbar);
}


static int
GetIconFromObj(Tcl_Interp *interp, ComboMenu *comboPtr, Tcl_Obj *objPtr, 
	       Icon *iconPtr)
{
    Blt_HashEntry *hPtr;
    struct _Icon *iPtr;
    int isNew;
    const char *iconName;

    iconName = Tcl_GetString(objPtr);
    if (iconName[0] == '\0') {
	*iconPtr = NULL;
	return TCL_OK;
    }
    hPtr = Blt_CreateHashEntry(&comboPtr->iconTable, iconName, &isNew);
    if (isNew) {
	Tk_Image tkImage;
	int w, h;

	tkImage = Tk_GetImage(interp, comboPtr->tkwin, (char *)iconName, 
		IconChangedProc, comboPtr);
	if (tkImage == NULL) {
	    Blt_DeleteHashEntry(&comboPtr->iconTable, hPtr);
	    return TCL_ERROR;
	}
	Tk_SizeOfImage(tkImage, &w, &h);
	iPtr = Blt_AssertMalloc(sizeof(struct _Icon ));
	iPtr->tkImage = tkImage;
	iPtr->hPtr = hPtr;
	iPtr->refCount = 1;
	iPtr->width = w;
	iPtr->height = h;
	Blt_SetHashValue(hPtr, iPtr);
    } else {
	iPtr = Blt_GetHashValue(hPtr);
	iPtr->refCount++;
    }
    *iconPtr = iPtr;
    return TCL_OK;
}

static void
FreeIcon(ComboMenu *comboPtr, struct _Icon *iPtr)
{
    iPtr->refCount--;
    if (iPtr->refCount == 0) {
	Blt_DeleteHashEntry(&comboPtr->iconTable, iPtr->hPtr);
	Tk_FreeImage(iPtr->tkImage);
	Blt_Free(iPtr);
    }
}

static void
DestroyIcons(ComboMenu *comboPtr)
{
    Blt_HashEntry *hPtr;
    Blt_HashSearch iter;

    for (hPtr = Blt_FirstHashEntry(&comboPtr->iconTable, &iter);
	 hPtr != NULL; hPtr = Blt_NextHashEntry(&iter)) {
	Icon icon;

	icon = Blt_GetHashValue(hPtr);
	Tk_FreeImage(IconImage(icon));
	Blt_Free(icon);
    }
    Blt_DeleteHashTable(&comboPtr->iconTable);
}

static INLINE Item *
FindItemByLabel(ComboMenu *comboPtr, const char *label)
{
    Blt_HashEntry *hPtr;

    hPtr = Blt_FindHashEntry(&comboPtr->labelTable, label);
    if (hPtr != NULL) {
	Blt_HashTable *tablePtr;
	Blt_HashEntry *h2Ptr;
	Blt_HashSearch iter;

	tablePtr = Blt_GetHashValue(hPtr);
	h2Ptr = Blt_FirstHashEntry(tablePtr, &iter);
	if (h2Ptr != NULL) {
	    return Blt_GetHashValue(h2Ptr);
	}
    }
    return NULL;
}

static char *
NewLabel(Item *itemPtr, const char *label)
{
    Blt_HashEntry *hPtr, *h2Ptr;
    Blt_HashTable *tablePtr;
    int isNew;
    ComboMenu *comboPtr;

    comboPtr = itemPtr->comboPtr;
    hPtr = Blt_CreateHashEntry(&comboPtr->labelTable, label, &isNew);
    if (isNew) {
	tablePtr = Blt_AssertMalloc(sizeof(Blt_HashTable));
	Blt_InitHashTable(tablePtr, BLT_ONE_WORD_KEYS);
	Blt_SetHashValue(hPtr, tablePtr);
    } else {
	tablePtr = Blt_GetHashValue(hPtr);
    }
    h2Ptr = Blt_CreateHashEntry(tablePtr, (char *)itemPtr, &isNew);
    Blt_SetHashValue(h2Ptr, itemPtr);
    return Blt_GetHashKey(&comboPtr->labelTable, hPtr);
}

static void
RemoveLabel(ComboMenu *comboPtr, Item *itemPtr)
{
    Blt_HashEntry *hPtr;
	
    hPtr = Blt_FindHashEntry(&comboPtr->labelTable, itemPtr->label);
    if (hPtr != NULL) {
	Blt_HashTable *tablePtr;
	Blt_HashEntry *h2Ptr;
	
	tablePtr = Blt_GetHashValue(hPtr);
	h2Ptr = Blt_FindHashEntry(tablePtr, (char *)itemPtr);
	if (h2Ptr != NULL) {
	    itemPtr->label = emptyString;
	    Blt_DeleteHashEntry(tablePtr, h2Ptr);
	    if (tablePtr->numEntries == 0) {
		Blt_DeleteHashEntry(&comboPtr->labelTable, hPtr);
		Blt_DeleteHashTable(tablePtr);
		Blt_Free(tablePtr);
	    }
	}
    }
}

static void
DestroyLabels(ComboMenu *comboPtr)
{
    Blt_HashEntry *hPtr;
    Blt_HashSearch iter;

    for (hPtr = Blt_FirstHashEntry(&comboPtr->labelTable, &iter); 
	 hPtr != NULL; hPtr = Blt_NextHashEntry(&iter)) {
	Blt_HashTable *tablePtr;
	
	tablePtr = Blt_GetHashValue(hPtr);
	Blt_DeleteHashTable(tablePtr);
	Blt_Free(tablePtr);
    }
    Blt_DeleteHashTable(&comboPtr->labelTable);
}

static void
MoveItem(ComboMenu *comboPtr, Item *itemPtr, int dir, Item *wherePtr)
{
    if (Blt_Chain_GetLength(comboPtr->chain) == 1) {
	return;				/* Can't rearrange one item. */
    }
    Blt_Chain_UnlinkLink(comboPtr->chain, itemPtr->link);
    switch(dir) {
    case 0:				/* After */
	Blt_Chain_LinkAfter(comboPtr->chain, itemPtr->link, wherePtr->link);
	break;
    case 1:				/* At */
	Blt_Chain_LinkAfter(comboPtr->chain, itemPtr->link, wherePtr->link);
	break;
    default:
    case 2:				/* Before */
	Blt_Chain_LinkBefore(comboPtr->chain, itemPtr->link, wherePtr->link);
	break;
    }
    {
	Blt_ChainLink link;
	long count;

	for (count = 0, link = Blt_Chain_FirstLink(comboPtr->chain); 
	     link != NULL; link = Blt_Chain_NextLink(link), count++) {
	    itemPtr = Blt_Chain_GetValue(link);
	    itemPtr->index = count;
	}
    }
}

static int 
GetTypeFromObj(Tcl_Interp *interp, Tcl_Obj *objPtr, int *typePtr)
{
    char *string;
    int length, flag;
    char c;

    string = Tcl_GetStringFromObj(objPtr, &length);
    c = string[0];
    if ((c == 'r') && (length > 1) && 
	(strncmp(string, "radiobutton", length) == 0)) {
	flag = ITEM_RADIOBUTTON;
    } else if ((c == 'c') && (length > 1) && 
	(strncmp(string, "command", length) == 0)) {
	flag = ITEM_BUTTON;
    } else if ((c == 'c') && (length > 1) && 
	(strncmp(string, "cascade", length) == 0)) {
	flag = ITEM_CASCADE;
    } else if ((c == 'c') && (length > 1) && 
	(strncmp(string, "checkbutton", length) == 0)) {
	flag = ITEM_CHECKBUTTON;
    } else if ((c == 's') && (length > 1) && 
	(strncmp(string, "separator", length) == 0)) {
	flag = ITEM_SEPARATOR;
    } else {
	if (interp != NULL) {
	    Tcl_AppendResult(interp, "unknown item type \"", string, 
			     "\": should be command, checkbutton, cascade, ",
			     "radiobutton, or separator.", (char *)NULL);
	}
	return TCL_ERROR;
    }
    *typePtr = flag;
    return TCL_OK;
}


static const char *
NameOfType(unsigned int flags)
{
    if (flags & ITEM_BUTTON) {
	return "command";
    }
    if (flags & ITEM_RADIOBUTTON) {
	return "radiobutton";
    }
    if (flags & ITEM_CHECKBUTTON) {
	return "checkbutton";
    }
    if (flags & ITEM_CASCADE) {
	return "cascade";
    }
    if (flags & ITEM_SEPARATOR) {
	return "separator";
    }
    return "???";
}	

/*
 *---------------------------------------------------------------------------
 *
 * NextTaggedItem --
 *
 *	Returns the next item derived from the given tag.
 *
 * Results:
 *	Returns the row location of the first item.  If no more rows can be
 *	found, then NULL is returned.
 *
 *---------------------------------------------------------------------------
 */
static Item *
NextTaggedItem(ItemIterator *iterPtr)
{
    Item *itemPtr;

    switch (iterPtr->type) {
    case ITER_TAG:
	{
	    Blt_HashEntry *hPtr;
	    
	    hPtr = Blt_NextHashEntry(&iterPtr->cursor); 
	    if (hPtr != NULL) {
		return Blt_GetHashValue(hPtr);
	    }
	}
	break;
    case ITER_TYPE:
	itemPtr = iterPtr->nextPtr;
	if (itemPtr == NULL) {
	    return itemPtr;
	}
	while (itemPtr != iterPtr->endPtr) {
	    if (itemPtr->flags & iterPtr->itemType) {
		break;
	    }
	    itemPtr = StepItem(itemPtr);
	}
	if (itemPtr == iterPtr->endPtr) {
	    iterPtr->nextPtr = NULL;
	} else {
	    iterPtr->nextPtr = StepItem(itemPtr);
	}
	return itemPtr;

    case ITER_ALL:
	if (iterPtr->link != NULL) {
	    itemPtr = Blt_Chain_GetValue(iterPtr->link);
	    iterPtr->link = Blt_Chain_NextLink(iterPtr->link);
	    return itemPtr;
	}
	break;

    case ITER_PATTERN:
	{
	    Blt_ChainLink link;
	    
	    for (link = iterPtr->link; link != NULL; 
		 link = Blt_Chain_NextLink(link)) {
		Item *itemPtr;
		
		itemPtr = Blt_Chain_GetValue(iterPtr->link);
		if (Tcl_StringMatch(itemPtr->label, iterPtr->tagName)) {
		    iterPtr->link = Blt_Chain_NextLink(link);
		    return itemPtr;
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
 * FirstTaggedItem --
 *
 *	Returns the first item derived from the given tag.
 *
 * Results:
 *	Returns the row location of the first item.  If no more rows can be
 *	found, then -1 is returned.
 *
 *---------------------------------------------------------------------------
 */
static Item *
FirstTaggedItem(ItemIterator *iterPtr)
{
    Item *itemPtr;
	    
    switch (iterPtr->type) {
    case ITER_TAG: 
	{
	    Blt_HashEntry *hPtr;
	    
	    hPtr = Blt_FirstHashEntry(iterPtr->tablePtr, &iterPtr->cursor);
	    if (hPtr == NULL) {
		return NULL;
	    }
	    return Blt_GetHashValue(hPtr);
	}
	break;

    case ITER_ALL:
	if (iterPtr->link != NULL) {
	    itemPtr = Blt_Chain_GetValue(iterPtr->link);
	    iterPtr->link = Blt_Chain_NextLink(iterPtr->link);
	    return itemPtr;
	}
	break;

    case ITER_PATTERN:
	{
	    Blt_ChainLink link;
	    
	    for (link = iterPtr->link; link != NULL; 
		 link = Blt_Chain_NextLink(link)) {
		Item *itemPtr;
		
		itemPtr = Blt_Chain_GetValue(iterPtr->link);
		if (Tcl_StringMatch(itemPtr->label, iterPtr->tagName)) {
		    iterPtr->link = Blt_Chain_NextLink(link);
		    return itemPtr;
		}
	    }
	}
	break;

    case ITER_TYPE:
	itemPtr = iterPtr->startPtr;
	if (itemPtr == NULL) {
	    return itemPtr;
	}
	while (itemPtr != iterPtr->endPtr) {
	    if (itemPtr->flags & iterPtr->itemType) {
		break;
	    }
	    itemPtr = StepItem(itemPtr);
	}
	if (itemPtr == iterPtr->endPtr) {
	    iterPtr->nextPtr = NULL;
	} else {
	    iterPtr->nextPtr = StepItem(itemPtr);
	}
	return itemPtr;

    case ITER_SINGLE:
	itemPtr = iterPtr->startPtr;
	iterPtr->nextPtr = NextTaggedItem(iterPtr);
	return itemPtr;
    } 
    return NULL;
}

/*
 *---------------------------------------------------------------------------
 *
 * GetItemFromObj --
 *
 *	Get the item associated the given index, tag, or label.  This routine
 *	is used when you want only one item.  It's an error if more than one
 *	item is specified (e.g. "all" tag).  It's also an error if the tag is
 *	empty (no items are currently tagged).
 *
 *---------------------------------------------------------------------------
 */
static int 
GetItemFromObj(Tcl_Interp *interp, ComboMenu *comboPtr, Tcl_Obj *objPtr,
	      Item **itemPtrPtr)
{
    ItemIterator iter;
    Item *firstPtr;

    if (GetItemIterator(interp, comboPtr, objPtr, &iter) != TCL_OK) {
	return TCL_ERROR;
    }
    firstPtr = FirstTaggedItem(&iter);
    if (firstPtr != NULL) {
	Item *nextPtr;

	nextPtr = NextTaggedItem(&iter);
	if (nextPtr != NULL) {
	    if (interp != NULL) {
		Tcl_AppendResult(interp, "multiple items specified by \"", 
			Tcl_GetString(objPtr), "\"", (char *)NULL);
	    }
	    return TCL_ERROR;
	}
    }
    *itemPtrPtr = firstPtr;
    return TCL_OK;
}

static int
GetItemByIndex(Tcl_Interp *interp, ComboMenu *comboPtr, const char *string, 
	      int length, Item **itemPtrPtr)
{
    Item *itemPtr;
    char c;
    long pos;

    itemPtr = NULL;
    c = string[0];
    if ((isdigit(c)) && (Blt_GetLong(NULL, string, &pos) == TCL_OK)) {
	Blt_ChainLink link;

	link = Blt_Chain_GetNthLink(comboPtr->chain, pos);
	if (link != NULL) {
	    itemPtr = Blt_Chain_GetValue(link);
	} 
	if (itemPtr == NULL) {
	    if (interp != NULL) {
		Tcl_AppendResult(interp, "can't find item: bad index \"", 
			string, "\"", (char *)NULL);
	    }
	    return TCL_ERROR;
	}		
    } else if ((c == 'n') && (strcmp(string, "next") == 0)) {
	itemPtr = NextItem(comboPtr->activePtr);
	if (itemPtr == NULL) {
	    itemPtr = comboPtr->activePtr;
	}
    } else if ((c == 'p') && (strcmp(string, "previous") == 0)) {
	itemPtr = PrevItem(comboPtr->activePtr);
	if (itemPtr == NULL) {
	    itemPtr = comboPtr->activePtr;
	}
    } else if ((c == 'e') && (strcmp(string, "end") == 0)) {
	itemPtr = LastItem(comboPtr);
    } else if ((c == 'f') && (strcmp(string, "first") == 0)) {
	itemPtr = FirstItem(comboPtr);
    } else if ((c == 'l') && (strcmp(string, "last") == 0)) {
	itemPtr = LastItem(comboPtr);
    } else if ((c == 'v') && (strcmp(string, "view.top") == 0)) {
	itemPtr = comboPtr->firstPtr;
    } else if ((c == 'v') && (strcmp(string, "view.bottom") == 0)) {
	itemPtr = comboPtr->lastPtr;
    } else if ((c == 'n') && (strcmp(string, "none") == 0)) {
	itemPtr = NULL;
    } else if ((c == 'a') && (strcmp(string, "active") == 0)) {
	itemPtr = comboPtr->activePtr;
#ifdef notdef
    } else if ((c == 'f') && (strcmp(string, "focus") == 0)) {
	itemPtr = comboPtr->focusPtr;
#endif
    } else if (c == '@') {
	int x, y;

	if (Blt_GetXY(comboPtr->interp, comboPtr->tkwin, string, &x, &y) 
	    != TCL_OK) {
	    return TCL_ERROR;
	}
	itemPtr = NearestItem(comboPtr, x, y, TRUE);
#ifdef notdef
	if ((itemPtr != NULL) && (itemPtr->flags & ITEM_DISABLED)) {
	    itemPtr = NextItem(itemPtr);
	}
#endif
    } else {
	return TCL_CONTINUE;
    }
    *itemPtrPtr = itemPtr;
    return TCL_OK;
}

static Item *
GetItemByLabel(ComboMenu *comboPtr, const char *string)
{
    Blt_HashEntry *hPtr;
    
    hPtr = Blt_FindHashEntry(&comboPtr->labelTable, string);
    if (hPtr != NULL) {
	Blt_HashTable *tablePtr;
	Blt_HashEntry *h2Ptr;
	Blt_HashSearch iter;

	tablePtr = Blt_GetHashValue(hPtr);
	h2Ptr = Blt_FirstHashEntry(tablePtr, &iter);
	if (h2Ptr != NULL) {
	    return Blt_GetHashValue(h2Ptr);
	}
    }
    return NULL;
}


/*
 *---------------------------------------------------------------------------
 *
 * GetItemIterator --
 *
 *	Converts a string representing a item index into an item pointer.  The
 *	index may be in one of the following forms:
 *
 *	 number		Item at index in the list of items.
 *	 @x,y		Item closest to the specified X-Y screen coordinates.
 *	 "active"	Item where mouse pointer is located.
 *	 "posted"       Item is the currently posted cascade item.
 *	 "next"		Next item from the focus item.
 *	 "previous"	Previous item from the focus item.
 *	 "end"		Last item.
 *	 "none"		No item.
 *
 *	 number		Item at position in the list of items.
 *	 @x,y		Item closest to the specified X-Y screen coordinates.
 *	 "active"	Item mouse is located over.
 *	 "focus"	Item is the widget's focus.
 *	 "select"	Currently selected item.
 *	 "right"	Next item from the focus item.
 *	 "left"		Previous item from the focus item.
 *	 "up"		Next item from the focus item.
 *	 "down"		Previous item from the focus item.
 *	 "end"		Last item in list.
 *	"index:number"  Item at index number in list of items.
 *	"tag:string"	Item(s) tagged by "string".
 *	"label:pattern"	Item(s) with label matching "pattern".
 *	
 * Results:
 *	If the string is successfully converted, TCL_OK is returned.  The
 *	pointer to the node is returned via itemPtrPtr.  Otherwise, TCL_ERROR
 *	is returned and an error message is left in interpreter's result
 *	field.
 *
 *---------------------------------------------------------------------------
 */
static int
GetItemIterator(Tcl_Interp *interp, ComboMenu *comboPtr, Tcl_Obj *objPtr,
	       ItemIterator *iterPtr)
{
    Item *itemPtr, *startPtr, *endPtr;
    Blt_HashTable *tablePtr;
    char *string;
    char c;
    int nBytes;
    int length;
    int result;

    iterPtr->comboPtr = comboPtr;
    iterPtr->type = ITER_SINGLE;
    iterPtr->tagName = Tcl_GetStringFromObj(objPtr, &nBytes);
    iterPtr->nextPtr = NULL;
    iterPtr->startPtr = iterPtr->endPtr = NULL;

    if (comboPtr->flags & LAYOUT_PENDING) {
	ComputeComboGeometry(comboPtr);
    }
    if (comboPtr->flags & SCROLL_PENDING) {
	ComputeVisibleItems(comboPtr);
    } 
    string = Tcl_GetStringFromObj(objPtr, &length);
    c = string[0];
    iterPtr->startPtr = iterPtr->endPtr = comboPtr->activePtr;
    startPtr = endPtr = itemPtr = NULL;
    if (c == '\0') {
	startPtr = endPtr = NULL;
    } 
    iterPtr->type = ITER_SINGLE;
    result = GetItemByIndex(interp, comboPtr, string, length, &itemPtr);
    if (result == TCL_ERROR) {
	return TCL_ERROR;
    }
    if (result == TCL_OK) {
	iterPtr->startPtr = iterPtr->endPtr = itemPtr;
	return TCL_OK;
    }
    if ((c == 'a') && (strcmp(iterPtr->tagName, "all") == 0)) {
	iterPtr->type  = ITER_ALL;
	iterPtr->link = Blt_Chain_FirstLink(comboPtr->chain);
    } else if ((c == 'i') && (length > 6) && 
	       (strncmp(string, "index:", 6) == 0)) {
	if (GetItemByIndex(interp, comboPtr, string + 6, length - 6, &itemPtr) 
	    != TCL_OK) {
	    return TCL_ERROR;
	}
	iterPtr->startPtr = iterPtr->endPtr = itemPtr;
    } else if ((c == 't') && (length > 4) && 
	       (strncmp(string, "tag:", 4) == 0)) {
	Blt_HashTable *tablePtr;

	tablePtr = GetTagTable(comboPtr, string + 4);
	if (tablePtr == NULL) {
	    Tcl_AppendResult(interp, "can't find a tag \"", string + 5,
			"\" in \"", Tk_PathName(comboPtr->tkwin), "\"",
			(char *)NULL);
	    return TCL_ERROR;
	}
	iterPtr->tagName = string + 4;
	iterPtr->tablePtr = tablePtr;
	iterPtr->type = ITER_TAG;
    } else if ((c == 'l') && (length > 6) && 
	       (strncmp(string, "label:", 6) == 0)) {
	iterPtr->link = Blt_Chain_FirstLink(comboPtr->chain);
	iterPtr->tagName = string + 6;
	iterPtr->type = ITER_PATTERN;
    } else if ((itemPtr = GetItemByLabel(comboPtr, string)) != NULL) {
	iterPtr->startPtr = iterPtr->endPtr = itemPtr;
    } else if ((tablePtr = GetTagTable(comboPtr, string)) != NULL) {
	iterPtr->tagName = string;
	iterPtr->tablePtr = tablePtr;
	iterPtr->type = ITER_TAG;
    } else {
	if (interp != NULL) {
	    Tcl_AppendResult(interp, "can't find item index, label, or tag \"", 
		string, "\" in \"", Tk_PathName(comboPtr->tkwin), "\"", 
			     (char *)NULL);
	}
	return TCL_ERROR;
    }	
    return TCL_OK;
}
    
static int
ConfigureItem(
    Tcl_Interp *interp,
    Item *itemPtr,
    int objc,
    Tcl_Obj *const *objv,
    int flags)
{
    ComboMenu *comboPtr;

    comboPtr = itemPtr->comboPtr;
    iconOption.clientData = comboPtr;
    if (Blt_ConfigureWidgetFromObj(interp, comboPtr->tkwin, itemConfigSpecs, 
	objc, objv, (char *)itemPtr, flags) != TCL_OK) {
	return TCL_ERROR;
    }
    ComputeItemGeometry(comboPtr, itemPtr);
    return TCL_OK;
}

static int
ConfigureStyle(Tcl_Interp *interp, Style *stylePtr, int objc, 
	       Tcl_Obj *const *objv, int flags)
{
    ComboMenu *comboPtr = stylePtr->comboPtr;
    unsigned int gcMask;
    XGCValues gcValues;
    GC newGC;

    if (Blt_ConfigureWidgetFromObj(interp, comboPtr->tkwin, styleConfigSpecs, 
	objc, objv, (char *)stylePtr, flags) != TCL_OK) {
	return TCL_ERROR;
    }
    /* Normal label */
    gcMask = GCForeground | GCFont | GCLineWidth;
    gcValues.line_width = 0;
    gcValues.foreground = stylePtr->labelNormalColor->pixel;
    gcValues.font = Blt_FontId(stylePtr->labelFont);
    newGC = Tk_GetGC(comboPtr->tkwin, gcMask, &gcValues);
    if (stylePtr->labelNormalGC != NULL) {
	Tk_FreeGC(comboPtr->display, stylePtr->labelNormalGC);
    }
    stylePtr->labelNormalGC = newGC;
	
    /* Disabled label */
    gcMask = GCForeground | GCFont;
    gcValues.foreground = stylePtr->labelDisabledColor->pixel;
    gcValues.font = Blt_FontId(stylePtr->labelFont);
    newGC = Tk_GetGC(comboPtr->tkwin, gcMask, &gcValues);
    if (stylePtr->labelDisabledGC != NULL) {
	Tk_FreeGC(comboPtr->display, stylePtr->labelDisabledGC);
    }
    stylePtr->labelDisabledGC = newGC;
	
    /* Active label */
    gcMask = GCForeground | GCFont;
    gcValues.foreground = stylePtr->labelActiveColor->pixel;
    gcValues.font = Blt_FontId(stylePtr->labelFont);
    newGC = Tk_GetGC(comboPtr->tkwin, gcMask, &gcValues);
    if (stylePtr->labelActiveGC != NULL) {
	Tk_FreeGC(comboPtr->display, stylePtr->labelActiveGC);
    }
    stylePtr->labelActiveGC = newGC;

    /* Normal accelerator */
    gcMask = GCForeground | GCFont;
    gcValues.foreground = stylePtr->accelNormalColor->pixel;
    gcValues.font = Blt_FontId(stylePtr->accelFont);
    newGC = Tk_GetGC(comboPtr->tkwin, gcMask, &gcValues);
    if (stylePtr->accelNormalGC != NULL) {
	Tk_FreeGC(comboPtr->display, stylePtr->accelNormalGC);
    }
    stylePtr->accelNormalGC = newGC;
	
    /* Disabled accelerator */
    gcMask = GCForeground | GCFont;
    gcValues.foreground = stylePtr->accelDisabledColor->pixel;
    gcValues.font = Blt_FontId(stylePtr->accelFont);
    newGC = Tk_GetGC(comboPtr->tkwin, gcMask, &gcValues);
    if (stylePtr->accelDisabledGC != NULL) {
	Tk_FreeGC(comboPtr->display, stylePtr->accelDisabledGC);
    }
    stylePtr->accelDisabledGC = newGC;
	
    /* Active accelerator */
    gcMask = GCForeground | GCFont;
    gcValues.foreground = stylePtr->accelActiveColor->pixel;
    gcValues.font = Blt_FontId(stylePtr->accelFont);
    newGC = Tk_GetGC(comboPtr->tkwin, gcMask, &gcValues);
    if (stylePtr->accelActiveGC != NULL) {
	Tk_FreeGC(comboPtr->display, stylePtr->accelActiveGC);
    }
    stylePtr->accelActiveGC = newGC;

#ifdef notdef
    if (itemPtr->flags & (ITEM_RADIOBUTTON | ITEM_CHECKBUTTON)) {
	itemPtr->leftIndWidth = ITEM_L_IND_WIDTH + 2 * ITEM_IPAD;
	itemPtr->leftIndHeight = ITEM_L_IND_HEIGHT;
    }
#endif
    return TCL_OK;
}

static int
ConfigureComboMenu(Tcl_Interp *interp, ComboMenu *comboPtr, int objc,
		   Tcl_Obj *const *objv, int flags)
{
    int updateNeeded;

    if (Blt_ConfigureWidgetFromObj(interp, comboPtr->tkwin, comboConfigSpecs, 
	objc, objv, (char *)comboPtr, flags) != TCL_OK) {
	return TCL_ERROR;
    }
    if (ConfigureStyle(interp, &comboPtr->defStyle, 0, NULL, 
		       BLT_CONFIG_OBJV_ONLY) != TCL_OK) {
	return TCL_ERROR;
    }	

    updateNeeded = FALSE;
    /* Install the embedded scrollbars as needed.  We defer installing the
     * scrollbars so the scrollbar widgets don't have to exist when they are
     * specified by the -xscrollbar and -yscrollbar options respectively. The
     * down-side is that errors found in the scrollbar name will be
     * backgrounded. */
    if (Blt_ConfigModified(comboConfigSpecs, "-xscrollbar", (char *)NULL)) {
	if (comboPtr->xScrollbar != NULL) {
	    UnmanageScrollbar(comboPtr, comboPtr->xScrollbar);
	    comboPtr->xScrollbar = NULL;
	}
	if ((comboPtr->flags & INSTALL_XSCROLLBAR) == 0) {
	    Tcl_DoWhenIdle(InstallXScrollbar, comboPtr);
	    comboPtr->flags |= INSTALL_XSCROLLBAR;
	}	    
	updateNeeded = TRUE;
    }
    if (Blt_ConfigModified(comboConfigSpecs, "-yscrollbar", (char *)NULL)) {
	if (comboPtr->yScrollbar != NULL) {
	    UnmanageScrollbar(comboPtr, comboPtr->yScrollbar);
	    comboPtr->yScrollbar = NULL;
	}
	if ((comboPtr->flags & INSTALL_YSCROLLBAR) == 0) {
	    Tcl_DoWhenIdle(InstallYScrollbar, comboPtr);
	    comboPtr->flags |= INSTALL_YSCROLLBAR;
	}	    
	updateNeeded = TRUE;
    }
    if (updateNeeded) {
	if ((comboPtr->flags & UPDATE_PENDING) == 0) {
	    Tcl_DoWhenIdle(ConfigureScrollbarsProc, comboPtr);
	    comboPtr->flags |= UPDATE_PENDING;
	}	    
    }
    return TCL_OK;
}

/* Widget Callbacks */

/*
 *---------------------------------------------------------------------------
 *
 * ComboMenuEventProc --
 *
 * 	This procedure is invoked by the Tk dispatcher for various events on
 * 	comboentry widgets.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	When the window gets deleted, internal structures get cleaned up.
 *	When it gets exposed, it is redisplayed.
 *
 *---------------------------------------------------------------------------
 */
static void
ComboMenuEventProc(ClientData clientData, XEvent *eventPtr)
{
    ComboMenu *comboPtr = clientData;

    if (eventPtr->type == Expose) {
	if (eventPtr->xexpose.count == 0) {
	    EventuallyRedraw(comboPtr);
	}
    } else if (eventPtr->type == UnmapNotify) {
	if (comboPtr->lastPtr != NULL) {
	    UnpostCascade((Tcl_Interp *)NULL, comboPtr);
	    EventuallyRedraw(comboPtr);
	}
    } else if (eventPtr->type == ConfigureNotify) {
	comboPtr->flags |= (SCROLL_PENDING | LAYOUT_PENDING);
	EventuallyRedraw(comboPtr);
    } else if ((eventPtr->type == FocusIn) || (eventPtr->type == FocusOut)) {
	if (eventPtr->xfocus.detail == NotifyInferior) {
	    return;
	}
	if (eventPtr->type == FocusIn) {
	    comboPtr->flags |= FOCUS;
	} else {
	    comboPtr->flags &= ~FOCUS;
	}
	EventuallyRedraw(comboPtr);
    } else if (eventPtr->type == DestroyNotify) {
	if (comboPtr->tkwin != NULL) {
	    comboPtr->tkwin = NULL; 
	}
	if (comboPtr->flags & REDRAW_PENDING) {
	    Tcl_CancelIdleCall(DisplayComboMenu, comboPtr);
	}
	Tcl_EventuallyFree(comboPtr, DestroyComboMenu);
    }
}


/*
 *---------------------------------------------------------------------------
 *
 * ScrollbarEventProc --
 *
 *	This procedure is invoked by the Tk event handler when StructureNotify
 *	events occur in a scrollbar managed by the widget.
 *
 * Results:
 *	None.
 *
 *---------------------------------------------------------------------------
 */
static void
ScrollbarEventProc(
    ClientData clientData,		/* Pointer to Entry structure for
					 * widget referred to by eventPtr. */
    XEvent *eventPtr)			/* Describes what just happened. */
{
    ComboMenu *comboPtr = clientData;

    if (eventPtr->type == ConfigureNotify) {
	EventuallyRedraw(comboPtr);
    } else if (eventPtr->type == DestroyNotify) {
	if (eventPtr->xany.window == Tk_WindowId(comboPtr->yScrollbar)) {
	    comboPtr->yScrollbar = NULL;
	} else if (eventPtr->xany.window == Tk_WindowId(comboPtr->xScrollbar)) {
	    comboPtr->xScrollbar = NULL;
	} 
	comboPtr->flags |= LAYOUT_PENDING;;
	EventuallyRedraw(comboPtr);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * ScrollbarCustodyProc --
 *
 * 	This procedure is invoked when a scrollbar has been stolen by another
 * 	geometry manager.
 *
 * Results:
 *	None.
 *
 * Side effects:
  *	Arranges for the combomenu to have its layout re-arranged at the next
 *	idle point.
 *
 *---------------------------------------------------------------------------
 */
/* ARGSUSED */
static void
ScrollbarCustodyProc(
    ClientData clientData,		/* Information about the combomenu. */
    Tk_Window tkwin)			/* Scrollbar stolen by another geometry
					 * manager. */
{
    ComboMenu *comboPtr = (ComboMenu *)clientData;

    if (tkwin == comboPtr->yScrollbar) {
	comboPtr->yScrollbar = NULL;
	comboPtr->yScrollbarWidth = 0;
    } else if (tkwin == comboPtr->xScrollbar) {
	comboPtr->xScrollbar = NULL;
	comboPtr->xScrollbarHeight = 0;
    } else {
	return;		
    }
    Tk_UnmaintainGeometry(tkwin, comboPtr->tkwin);
    comboPtr->flags |= LAYOUT_PENDING;
    EventuallyRedraw(comboPtr);
}

/*
 *---------------------------------------------------------------------------
 *
 * ScrollbarGeometryProc --
 *
 *	This procedure is invoked by Tk_GeometryRequest for scrollbars managed
 *	by the combomenu.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Arranges for the combomenu to have its layout re-computed and
 *	re-arranged at the next idle point.
 *
 * -------------------------------------------------------------------------- */
/* ARGSUSED */
static void
ScrollbarGeometryProc(
    ClientData clientData,		/* ComboMenu widget record.  */
    Tk_Window tkwin)			/* Scrollbar whose geometry has
					 * changed. */
{
    ComboMenu *comboPtr = (ComboMenu *)clientData;

    comboPtr->flags |= LAYOUT_PENDING;
    EventuallyRedraw(comboPtr);
}

/*
 *---------------------------------------------------------------------------
 * 
 * ItemVarTraceProc --
 *
 *	This procedure is invoked when someone changes the state variable
 *	associated with a radiobutton or checkbutton entry.  The entry's
 *	selected state is set to match the value of the variable.
 *
 * Results:
 *	NULL is always returned.
 *
 * Side effects:
 *	The combobox entry may become selected or deselected.
 *
 *---------------------------------------------------------------------------
 */
static char *
ItemVarTraceProc(
    ClientData clientData,		/* Information about the item. */
    Tcl_Interp *interp,			/* Interpreter containing variable. */
    const char *name1,			/* First part of variable's name. */
    const char *name2,			/* Second part of variable's name. */
    int flags)				/* Describes what just happened. */
{
    Item *itemPtr = clientData;
    Tcl_Obj *objPtr;
    int bool;

    assert(itemPtr->variableObjPtr != NULL);
    if (flags & TCL_INTERP_DESTROYED) {
    	return NULL;			/* Interpreter is going away. */

    }
    /*
     * If the variable is being unset, then re-establish the trace.
     */
    if (flags & TCL_TRACE_UNSETS) {
	itemPtr->flags &= ~ITEM_SELECTED;
	if (flags & TCL_TRACE_DESTROYED) {
	    char *varName;

	    varName = Tcl_GetString(itemPtr->variableObjPtr);
	    Tcl_TraceVar(interp, varName, VAR_FLAGS, ItemVarTraceProc, 
		clientData);
	}
	goto done;
    }

    if ((itemPtr->flags & (ITEM_RADIOBUTTON|ITEM_CHECKBUTTON|ITEM_BUTTON))==0) {
	return NULL;		       /* Not a radiobutton or checkbutton. */
    }

    /*
     * Use the value of the variable to update the selected status of the
     * item.
     */
    objPtr = Tcl_ObjGetVar2(interp, itemPtr->variableObjPtr, NULL, 
			    TCL_GLOBAL_ONLY);
    if (objPtr == NULL) {
	return NULL;			/* Can't get value of variable. */
    }
    bool = 0;
    if (itemPtr->flags & (ITEM_BUTTON|ITEM_RADIOBUTTON)) {
	const char *string;

	if (itemPtr->valueObjPtr == NULL) {
	    string = itemPtr->label;
	} else {
	    string = Tcl_GetString(itemPtr->valueObjPtr);
	}
	if (string == NULL) {
	    return NULL;
	}
	bool = (strcmp(string, Tcl_GetString(objPtr)) == 0);
    } else if (itemPtr->flags & ITEM_CHECKBUTTON) {
	if (itemPtr->onValueObjPtr == NULL) {
	    if (Tcl_GetBooleanFromObj(NULL, objPtr, &bool) != TCL_OK) {
		return NULL;
	    }
	} else {
	    bool =  (strcmp(Tcl_GetString(objPtr), 
			    Tcl_GetString(itemPtr->onValueObjPtr)) == 0);
	}
    }
    if (bool) {
	ComboMenu *comboPtr;

	if (itemPtr->flags & ITEM_SELECTED) {
	    return NULL;			/* Already selected. */
	}
	comboPtr = itemPtr->comboPtr;
	if ((comboPtr->textVarObjPtr != NULL) && 
	    (itemPtr->label != emptyString)) {
	    Tcl_Obj *objPtr;
	    
	    objPtr = Tcl_NewStringObj(itemPtr->label, -1);
	    if (Tcl_ObjSetVar2(interp, comboPtr->textVarObjPtr, NULL, objPtr, 
			       TCL_GLOBAL_ONLY|TCL_LEAVE_ERR_MSG) == NULL) {
		return NULL;
	    }
	}
	itemPtr->flags |= ITEM_SELECTED;
    } else if (itemPtr->flags & ITEM_SELECTED) {
	itemPtr->flags &= ~ITEM_SELECTED;
    } else {
	return NULL;			/* Already deselected. */
    }
 done:
    EventuallyRedraw(itemPtr->comboPtr);
    return NULL;			/* Done. */
}

/*ARGSUSED*/
static void
FreeTraceVarProc(ClientData clientData, Display *display, char *widgRec, 
		 int offset)
{
    Item *itemPtr = (Item *)(widgRec);

    if (itemPtr->variableObjPtr != NULL) {
	const char *varName;
	ComboMenu *comboPtr;

	comboPtr = itemPtr->comboPtr;
	varName = Tcl_GetString(itemPtr->variableObjPtr);
	Tcl_UntraceVar(comboPtr->interp, varName, VAR_FLAGS, ItemVarTraceProc, 
		itemPtr);
	Tcl_DecrRefCount(itemPtr->variableObjPtr);
	itemPtr->variableObjPtr = NULL;
    }
}

/*
 *---------------------------------------------------------------------------

 * ObjToTraceVarProc --
 *
 *	Convert the string representation of a color into a XColor pointer.
 *
 * Results:
 *	The return value is a standard TCL result.  The color pointer is
 *	written into the widget record.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ObjToTraceVarProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,			/* Interpreter to send results back
					 * to */
    Tk_Window tkwin,			/* Not used. */
    Tcl_Obj *objPtr,			/* String representing style. */
    char *widgRec,			/* Widget record */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    Item *itemPtr = (Item *)(widgRec);
    const char *varName;

    /* Remove the current trace on the variable. */
    if (itemPtr->variableObjPtr != NULL) {
	varName = Tcl_GetString(itemPtr->variableObjPtr);
	Tcl_UntraceVar(interp, varName, VAR_FLAGS, ItemVarTraceProc, itemPtr);
	Tcl_DecrRefCount(itemPtr->variableObjPtr);
	itemPtr->variableObjPtr = NULL;
    }
    varName = Tcl_GetString(objPtr);
    if ((varName[0] == '\0') && (flags & BLT_CONFIG_NULL_OK)) {
	return TCL_OK;
    }
    itemPtr->variableObjPtr = objPtr;
    Tcl_IncrRefCount(objPtr);
    Tcl_TraceVar(interp, varName, VAR_FLAGS, ItemVarTraceProc, itemPtr);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * TraceVarToObjProc --
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
TraceVarToObjProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,
    Tk_Window tkwin,			/* Not used. */
    char *widgRec,			/* Widget information record */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    Item *itemPtr = (Item *)(widgRec);
    Tcl_Obj *objPtr;

    if (itemPtr->variableObjPtr == NULL) {
	objPtr = Tcl_NewStringObj("", -1);
    } else {
	objPtr = itemPtr->variableObjPtr;
    }
    return objPtr;
}

/*ARGSUSED*/
static void
FreeStyleProc(ClientData clientData, Display *display, char *widgRec, 
	      int offset)
{
    Style *stylePtr = *(Style **)(widgRec + offset);

    if ((stylePtr != NULL) && (stylePtr != &stylePtr->comboPtr->defStyle)) {
	DestroyStyle(stylePtr);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * ObjToStyleProc --
 *
 *	Convert the string representation of a color into a XColor pointer.
 *
 * Results:
 *	The return value is a standard TCL result.  The color pointer is
 *	written into the widget record.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ObjToStyleProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,			/* Interpreter to send results back
					 * to */
    Tk_Window tkwin,			/* Not used. */
    Tcl_Obj *objPtr,			/* String representing style. */
    char *widgRec,			/* Widget record */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    ComboMenu *comboPtr;
    Item *itemPtr = (Item *)widgRec;
    Style **stylePtrPtr = (Style **)(widgRec + offset);
    Style *stylePtr;
    char *string;

    string = Tcl_GetString(objPtr);
    comboPtr = itemPtr->comboPtr;
    if ((string[0] == '\0') && (flags & BLT_CONFIG_NULL_OK)) {
	stylePtr = NULL;
    } else if (GetStyleFromObj(interp, comboPtr, objPtr, &stylePtr) != TCL_OK) {
	return TCL_ERROR;
    }
    /* Release the old style. */
    if ((*stylePtrPtr != NULL) && (*stylePtrPtr != &comboPtr->defStyle)) {
	DestroyStyle(*stylePtrPtr);
    }
    stylePtr->refCount++;
    *stylePtrPtr = stylePtr;
    return TCL_OK;
}


/*
 *---------------------------------------------------------------------------
 *
 * StyleToObjProc --
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
StyleToObjProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,
    Tk_Window tkwin,			/* Not used. */
    char *widgRec,			/* Widget information record */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    Style *stylePtr = *(Style **)(widgRec + offset);
    Tcl_Obj *objPtr;

    if (stylePtr == NULL) {
	objPtr = Tcl_NewStringObj("", -1);
    } else {
	objPtr = Tcl_NewStringObj(stylePtr->name, -1);
    }
    return objPtr;
}

/*
 *---------------------------------------------------------------------------
 *
 * ObjToRestrictProc --
 *
 *	Convert the string representation of an item state into a flag.
 *
 * Results:
 *	The return value is a standard TCL result.  The state flags are
 *	updated.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ObjToRestrictProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,			/* Interpreter to send results back
					 * to */
    Tk_Window tkwin,			/* Not used. */
    Tcl_Obj *objPtr,			/* String representing state. */
    char *widgRec,			/* Widget record */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    unsigned int *flagsPtr = (unsigned int *)(widgRec + offset);
    char *string;
    int flag;

    string = Tcl_GetString(objPtr);
    if (strcmp(string, "min") == 0) {
	flag = RESTRICT_MIN;
    } else if (strcmp(string, "max") == 0) {
	flag = RESTRICT_MAX;
    } else if (strcmp(string, "both") == 0) {
	flag = RESTRICT_MIN|RESTRICT_MAX;
    } else if (strcmp(string, "none") == 0) {
	flag = 0;
    } else {
	Tcl_AppendResult(interp, "unknown state \"", string, 
		"\": should be active, disabled, or normal.", (char *)NULL);
	return TCL_ERROR;
    }
    *flagsPtr &= ~(RESTRICT_MIN|RESTRICT_MAX);
    *flagsPtr |= flag;
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * RestrictToObjProc --
 *
 *	Return the string representation of the restrict flags.
 *
 * Results:
 *	The name representing the style is returned.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static Tcl_Obj *
RestrictToObjProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,
    Tk_Window tkwin,			/* Not used. */
    char *widgRec,			/* Widget information record */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    unsigned int *flagsPtr = (unsigned int *)(widgRec + offset);
    int xrestrict; /* restrict is a reserved word in clang */

    xrestrict = *flagsPtr & (RESTRICT_MIN|RESTRICT_MAX);
    switch (xrestrict) {
    case RESTRICT_MIN:
	return Tcl_NewStringObj("min", -1);	
    case RESTRICT_MAX:
	return Tcl_NewStringObj("max", -1);
    case (RESTRICT_MIN|RESTRICT_MAX):
	return Tcl_NewStringObj("both", -1);
    case RESTRICT_NONE:
	return Tcl_NewStringObj("none", -1);
    }
    return NULL;
}

/*
 *---------------------------------------------------------------------------
 *
 * ObjToStateProc --
 *
 *	Convert the string representation of an item state into a flag.
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
    Tcl_Interp *interp,			/* Interpreter to send results back
					 * to */
    Tk_Window tkwin,			/* Not used. */
    Tcl_Obj *objPtr,			/* String representing state. */
    char *widgRec,			/* Widget record */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    Item *itemPtr = (Item *)(widgRec);
    unsigned int *flagsPtr = (unsigned int *)(widgRec + offset);
    char *string;
    ComboMenu *comboPtr;
    int flag;

    string = Tcl_GetString(objPtr);
    if (strcmp(string, "disabled") == 0) {
	flag = ITEM_DISABLED;
    } else if (strcmp(string, "normal") == 0) {
	flag = ITEM_NORMAL;
    } else {
	Tcl_AppendResult(interp, "unknown state \"", string, 
		"\": should be active, disabled, or normal.", (char *)NULL);
	return TCL_ERROR;
    }
    if (itemPtr->flags & flag) {
	return TCL_OK;			/* State is already set to value. */
    }
    comboPtr = itemPtr->comboPtr;
    if (comboPtr->activePtr != itemPtr) {
	ActivateItem(comboPtr, NULL);
	comboPtr->activePtr = NULL;
    }
    *flagsPtr &= ~ITEM_STATE_MASK;
    *flagsPtr |= flag;
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

    if (state & ITEM_NORMAL) {
	objPtr = Tcl_NewStringObj("normal", -1);
    } else if (state & ITEM_DISABLED) {
	objPtr = Tcl_NewStringObj("disabled", -1);
    } else {
	objPtr = Tcl_NewStringObj("???", -1);
    }
    return objPtr;
}


/*ARGSUSED*/
static void
FreeTagsProc(
    ClientData clientData,
    Display *display,		/* Not used. */
    char *widgRec,
    int offset)
{
    ComboMenu *comboPtr;
    Item *itemPtr = (Item *)widgRec;

    comboPtr = itemPtr->comboPtr;
    ReleaseTags(comboPtr, itemPtr);
}

/*
 *---------------------------------------------------------------------------
 *
 * ObjToTagsProc --
 *
 *	Convert the string representation of a list of tags.
 *
 * Results:
 *	The return value is a standard TCL result.  The tags are
 *	save in the widget.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ObjToTagsProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,			/* Interpreter to send results back
					 * to */
    Tk_Window tkwin,			/* Not used. */
    Tcl_Obj *objPtr,			/* String representing style. */
    char *widgRec,			/* Widget record */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    ComboMenu *comboPtr;
    Item *itemPtr = (Item *)widgRec;
    int i;
    char *string;
    int objc;
    Tcl_Obj **objv;

    comboPtr = itemPtr->comboPtr;
    ReleaseTags(comboPtr, itemPtr);
    string = Tcl_GetString(objPtr);
    if ((string[0] == '\0') && (flags & BLT_CONFIG_NULL_OK)) {
	return TCL_OK;
    }
    if (Tcl_ListObjGetElements(interp, objPtr, &objc, &objv) != TCL_OK) {
	return TCL_ERROR;
    }
    for (i = 0; i < objc; i++) {
	SetTag(interp, itemPtr, Tcl_GetString(objv[i]));
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * TagsToObjProc --
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
TagsToObjProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,
    Tk_Window tkwin,			/* Not used. */
    char *widgRec,			/* Widget information record */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    Blt_HashEntry *hPtr;
    Blt_HashSearch iter;
    ComboMenu *comboPtr;
    Item *itemPtr = (Item *)widgRec;
    Tcl_Obj *listObjPtr;

    comboPtr = itemPtr->comboPtr;
    listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
    for (hPtr = Blt_FirstHashEntry(&comboPtr->tagTable, &iter); hPtr != NULL;
	 hPtr = Blt_NextHashEntry(&iter)) {
	Blt_HashTable *tagTablePtr;
	Blt_HashEntry *h2Ptr;

	tagTablePtr = Blt_GetHashValue(hPtr); 
	h2Ptr = Blt_FindHashEntry(tagTablePtr, (char *)itemPtr->index);
	if (h2Ptr != NULL) {
	    Tcl_Obj *objPtr;
	    const char *name;

	    name = Tcl_GetHashKey(&comboPtr->tagTable, hPtr);
	    objPtr = Tcl_NewStringObj(name, -1);
	    Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	}
    }
    return listObjPtr;
}

/*
 *---------------------------------------------------------------------------
 *
 * IconChangedProc
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
    int x, int y, int w, int h,		/* Not used. */
    int imageWidth, int imageHeight)	/* Not used. */
{
    ComboMenu *comboPtr = clientData;

    comboPtr->flags |= (LAYOUT_PENDING | SCROLL_PENDING);
    EventuallyRedraw(comboPtr);
}

/*
 *---------------------------------------------------------------------------
 *
 * ObjToIconProc --
 *
 *	Convert a image into a hashed icon.
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
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,			/* Interpreter to send results back
					 * to */
    Tk_Window tkwin,			/* Not used. */
    Tcl_Obj *objPtr,			/* Tcl_Obj representing the new
					 * value. */
    char *widgRec,
    int offset,				/* Offset to field in structure */
    int flags)	
{
    ComboMenu *comboPtr = clientData;
    Icon *iconPtr = (Icon *)(widgRec + offset);
    Icon icon;

    if (GetIconFromObj(interp, comboPtr, objPtr, &icon) != TCL_OK) {
	return TCL_ERROR;
    }
    if (*iconPtr != NULL) {
	FreeIcon(comboPtr, *iconPtr);
    }
    *iconPtr = icon;
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * IconToObjProc --
 *
 *	Converts the icon into its string representation (its name).
 *
 * Results:
 *	The name of the icon is returned.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static Tcl_Obj *
IconToObjProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,
    Tk_Window tkwin,			/* Not used. */
    char *widgRec,
    int offset,				/* Offset to field in structure */
    int flags)	
{
    Icon icon = *(Icon *)(widgRec + offset);
    Tcl_Obj *objPtr;

    if (icon == NULL) {
	objPtr = Tcl_NewStringObj("", 0);
    } else {
	objPtr =Tcl_NewStringObj(Blt_Image_Name(IconImage(icon)), -1);
    }
    return objPtr;
}

/*ARGSUSED*/
static void
FreeIconProc(
    ClientData clientData,
    Display *display,			/* Not used. */
    char *widgRec,
    int offset)
{
    Icon *iconPtr = (Icon *)(widgRec + offset);

    if (*iconPtr != NULL) {
	ComboMenu *comboPtr = clientData;

	FreeIcon(comboPtr, *iconPtr);
	*iconPtr = NULL;
    }
}

/*ARGSUSED*/
static void
FreeLabelProc(
    ClientData clientData,
    Display *display,			/* Not used. */
    char *widgRec,
    int offset)
{
    Item *itemPtr = (Item *)widgRec;

    if (itemPtr->label != emptyString) {
	RemoveLabel(itemPtr->comboPtr, itemPtr);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * ObjToLabelProc --
 *
 *	Save the label and add the item to the label hashtable.
 *
 * Results:
 *	A standard TCL result. 
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ObjToLabelProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,			/* Interpreter to send results back
					 * to */
    Tk_Window tkwin,			/* Not used. */
    Tcl_Obj *objPtr,			/* String representing style. */
    char *widgRec,			/* Widget record */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    Item *itemPtr = (Item *)(widgRec);
    char *string;

    if (itemPtr->label != emptyString) {
	RemoveLabel(itemPtr->comboPtr, itemPtr);
    }
    string = Tcl_GetString(objPtr);
    if ((string[0] == '\0') && (flags & BLT_CONFIG_NULL_OK)) {
	return TCL_OK;
    }
    itemPtr->label = NewLabel(itemPtr, string);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * LabelToObjProc --
 *
 *	Return the label of the item.
 *
 * Results:
 *	The label is returned.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static Tcl_Obj *
LabelToObjProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,
    Tk_Window tkwin,			/* Not used. */
    char *widgRec,			/* Widget information record */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    Item *itemPtr = (Item *)(widgRec);
    Tcl_Obj *objPtr;

    if (itemPtr->label == emptyString) {
	objPtr = Tcl_NewStringObj("", -1);
    } else {
	objPtr = Tcl_NewStringObj(itemPtr->label, -1);
    }
    return objPtr;
}

/*
 *---------------------------------------------------------------------------
 *
 * ObjToTypeProc --
 *
 *	Convert the string representation of an item into a value.
 *
 * Results:
 *	A standard TCL result.  The type pointer is written into the
 *	widget record.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ObjToTypeProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,			/* Interpreter to send results back
					 * to */
    Tk_Window tkwin,			/* Not used. */
    Tcl_Obj *objPtr,			/* String representing type. */
    char *widgRec,			/* Widget record */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    unsigned int *typePtr = (unsigned int *)(widgRec + offset);
    int flag;

    if (GetTypeFromObj(interp, objPtr, &flag) != TCL_OK) {
	return TCL_ERROR;
    }
    *typePtr &= ~ITEM_TYPE_MASK;
    *typePtr |= flag;
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * TypeToObjProc --
 *
 *	Return the name of the type.
 *
 * Results:
 *	The name representing the style is returned.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static Tcl_Obj *
TypeToObjProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,
    Tk_Window tkwin,			/* Not used. */
    char *widgRec,			/* Widget information record */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    int type = *(int *)(widgRec + offset);
    
    return Tcl_NewStringObj(NameOfType(type), -1);
}

/*
 *---------------------------------------------------------------------------
 *
 * TypeSwitch --
 *
 *	Convert a string representing an item type into its integer value.
 *
 * Results:
 *	The return value is a standard TCL result.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
TypeSwitch(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,			/* Not used. */
    const char *switchName,		/* Not used. */
    Tcl_Obj *objPtr,			/* String representation */
    char *record,			/* Structure record */
    int offset,				/* Offset to field in structure */
    int flags)				/* Not used. */
{
    unsigned int *typePtr = (unsigned int *)(record + offset);
    int flag;

    if (GetTypeFromObj(interp, objPtr, &flag) != TCL_OK) {
	return TCL_ERROR;
    }
    *typePtr &= ~ITEM_TYPE_MASK;
    *typePtr |= flag;
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * ItemSwitch --
 *
 *	Convert a string representing an item into its pointer.
 *
 * Results:
 *	The return value is a standard TCL result.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ItemSwitch(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,			/* Not used. */
    const char *switchName,		/* Not used. */
    Tcl_Obj *objPtr,			/* String representation */
    char *record,			/* Structure record */
    int offset,				/* Offset to field in structure */
    int flags)				/* Not used. */
{
    Item **itemPtrPtr = (Item **)(record + offset);
    ComboMenu *comboPtr = clientData;
    Item *itemPtr;

    if (GetItemFromObj(NULL, comboPtr, objPtr, &itemPtr) != TCL_OK) {
	return TCL_ERROR;
    } 
    *itemPtrPtr = itemPtr;
    return TCL_OK;
}


/* Widget Operations */

/*
 *---------------------------------------------------------------------------
 *
 * ActivateOp --
 *
 * Results:
 *	Standard TCL result.
 *
 * Side effects:
 *	Commands may get excecuted; variables may get set; sub-menus may
 *	get posted.
 *
 *	.cm activate item
 *
 *---------------------------------------------------------------------------
 */
static int
ActivateOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, 
	   Tcl_Obj *const *objv)
{
    Item *itemPtr;

    if (GetItemFromObj(NULL, comboPtr, objv[2], &itemPtr) != TCL_OK) {
	return TCL_ERROR;
    } 
    if (comboPtr->activePtr == itemPtr) {
	return TCL_OK;			/* Item is already active. */
    }
    ActivateItem(comboPtr, NULL);
    comboPtr->activePtr = NULL;
    if ((itemPtr != NULL) && 
	((itemPtr->flags & (ITEM_DISABLED|ITEM_SEPARATOR)) == 0)) {
	ActivateItem(comboPtr, itemPtr);
	comboPtr->activePtr = itemPtr;
    }
    return TCL_OK;
}


/*
 *---------------------------------------------------------------------------
 *
 * AddOp --
 *
 *	Appends a new item to the combomenu.
 *
 * Results:
 *	NULL is always returned.
 *
 * Side effects:
 *	The combomenu entry may become selected or deselected.
 *
 *   .cm add radiobutton -text "fred" -tags ""
 *
 *---------------------------------------------------------------------------
 */
static int
AddOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Item *itemPtr;

    itemPtr = NewItem(comboPtr);
    if (ConfigureItem(interp, itemPtr, objc - 2, objv + 2, 0) != TCL_OK) {
	DestroyItem(itemPtr);
	return TCL_ERROR;		/* Error configuring the entry. */
    }
    EventuallyRedraw(comboPtr);
    Tcl_SetLongObj(Tcl_GetObjResult(interp), itemPtr->index);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * AddListOp --
 *
 *	Appends a list of items to the combomenu.
 *
 * Results:
 *	A standard TCL result.
 *
 * Side effects:
 *	New items are added to the combomenu.
 *
 *   .cm add labelList -type radiobutton -text "fred" -tags ""
 *
 *---------------------------------------------------------------------------
 */
static int
AddListOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, 
	  Tcl_Obj *const *objv)
{
    int i;
    int iobjc;
    Tcl_Obj **iobjv;
    Tcl_Obj *listObjPtr;

    if (Tcl_ListObjGetElements(interp, objv[2], &iobjc, &iobjv) != TCL_OK) {
	return TCL_ERROR;
    }
    listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
    for (i = 0; i < iobjc; i++) {
	Tcl_Obj *objPtr;
	Item *itemPtr;

	itemPtr = NewItem(comboPtr);
	if (ConfigureItem(interp, itemPtr, objc - 3, objv + 3, 0) != TCL_OK) {
	    DestroyItem(itemPtr);
	    return TCL_ERROR;	
	}
	itemPtr->label = NewLabel(itemPtr, Tcl_GetString(iobjv[i]));
	objPtr = Tcl_NewLongObj(itemPtr->index);
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
    }
    EventuallyRedraw(comboPtr);
    Tcl_SetObjResult(interp, listObjPtr);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * ConfigureOp --
 *
 * Results:
 *	Standard TCL result.
 *
 * Side effects:
 *	Commands may get excecuted; variables may get set; sub-menus may
 *	get posted.
 *
 *	.cm configure ?option value?...
 *
 *---------------------------------------------------------------------------
 */
static int
ConfigureOp(
    ComboMenu *comboPtr, 
    Tcl_Interp *interp, 
    int objc, 
    Tcl_Obj *const *objv)
{
    int result;

    iconOption.clientData = comboPtr;
    if (objc == 2) {
	return Blt_ConfigureInfoFromObj(interp, comboPtr->tkwin, 
		comboConfigSpecs, (char *)comboPtr, (Tcl_Obj *)NULL,  0);
    } else if (objc == 3) {
	return Blt_ConfigureInfoFromObj(interp, comboPtr->tkwin, 
		comboConfigSpecs, (char *)comboPtr, objv[2], 0);
    }
    Tcl_Preserve(comboPtr);
    result = ConfigureComboMenu(interp, comboPtr, objc - 2, objv + 2, 
		BLT_CONFIG_OBJV_ONLY);
    Tcl_Release(comboPtr);
    if (result == TCL_ERROR) {
	return TCL_ERROR;
    }
    comboPtr->flags |= (LAYOUT_PENDING | SCROLL_PENDING);
    EventuallyRedraw(comboPtr);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * CgetOp --
 *
 * Results:
 *	Standard TCL result.
 *
 * Side effects:
 *	Commands may get excecuted; variables may get set; sub-menus may
 *	get posted.
 *
 *	.cm cget option
 *
 *---------------------------------------------------------------------------
 */
static int
CgetOp(
    ComboMenu *comboPtr, 
    Tcl_Interp *interp, 
    int objc, 
    Tcl_Obj *const *objv)
{
    iconOption.clientData = comboPtr;
    return Blt_ConfigureValueFromObj(interp, comboPtr->tkwin, comboConfigSpecs,
	(char *)comboPtr, objv[2], 0);
}

/*
 *---------------------------------------------------------------------------
 *
 * DeleteOp --
 *
 * Results:
 *	Standard TCL result.
 *
 * Side effects:
 *	Commands may get excecuted; variables may get set; sub-menus may
 *	get posted.
 *
 *	.cm delete item...
 *
 *---------------------------------------------------------------------------
 */
static int
DeleteOp(
    ComboMenu *comboPtr, 
    Tcl_Interp *interp, 
    int objc, 
    Tcl_Obj *const *objv)
{
    int i;

    for (i = 2; i < objc; i++) {
	ItemIterator iter;
	Item *itemPtr, *nextPtr;

	if (GetItemIterator(interp, comboPtr, objv[i], &iter) != TCL_OK) {
	    return TCL_ERROR;
	}
	for (itemPtr = FirstTaggedItem(&iter); itemPtr != NULL; 
	     itemPtr = nextPtr) {
	    nextPtr = NextTaggedItem(&iter);
	    DestroyItem(itemPtr);
	}
    }
    EventuallyRedraw(comboPtr);
    return TCL_OK;
}


/*
 *---------------------------------------------------------------------------
 *
 * ExistsOp --
 *
 * Results:
 *	Standard TCL result.
 *
 * Side effects:
 *	Commands may get excecuted; variables may get set; sub-menus may
 *	get posted.
 *
 *	.cm exists item 
 *
 *---------------------------------------------------------------------------
 */
static int
ExistsOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Item *itemPtr;
    int bool;

    bool = FALSE;
    if (GetItemFromObj(NULL, comboPtr, objv[2], &itemPtr) == TCL_OK) {
	if (itemPtr != NULL) {
	    bool = TRUE;
	}
    }
    Tcl_SetBooleanObj(Tcl_GetObjResult(interp), bool);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * FindOp --
 *
 *	Search for an item according to the string given.
 *
 * Results:
 *	The index of the found item is returned.  If no item is found
 *	-1 is returned.
 *
 *    .cm find string -from active -previous -underline -type separator 
 *
 *---------------------------------------------------------------------------
 */
static int
FindOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    long index;
    FindSwitches switches;
    const char *pattern;

    /* Process switches  */
    pattern = Tcl_GetString(objv[2]);
    switches.mask = 0;
    switches.type = 0;
    itemSwitch.clientData = comboPtr;

    switches.fromPtr = comboPtr->activePtr;
    if (Blt_ParseSwitches(interp, findSwitches, objc - 3, objv + 3, &switches,
	BLT_SWITCH_DEFAULTS) < 0) {
	return TCL_ERROR;
    }
    index = -1;
    if (switches.mask & FIND_UNDERLINE) {
	Tcl_UniChar want;
	Item *itemPtr;
	
	itemPtr = switches.fromPtr;
	itemPtr = (itemPtr == NULL) ? FirstItem(comboPtr) : NextItem(itemPtr);
	want = Tcl_UniCharAtIndex(pattern, 0);
	want = Tcl_UniCharToLower(want);
	for (/*empty*/; itemPtr != NULL; itemPtr = NextItem(itemPtr)) {
	    if (itemPtr->underline >= 0) {
		Tcl_UniChar have;
		
		have = Tcl_UniCharAtIndex(itemPtr->label, itemPtr->underline);
		have = Tcl_UniCharToLower(have);
		if (want == have) {
		    index = itemPtr->index;
		    break;
		}
	    }
	}
	if (itemPtr == NULL) {
	    for (itemPtr = FirstItem(comboPtr); itemPtr != NULL; 
		 itemPtr = NextItem(itemPtr)) {
		if (itemPtr->underline >= 0) {
		    Tcl_UniChar have;
		    
		    have = Tcl_UniCharAtIndex(itemPtr->label, 
					      itemPtr->underline);
		    have = Tcl_UniCharToLower(have);
		    if (want == have) {
			index = itemPtr->index;
			break;
		    }
		}
		if (itemPtr == comboPtr->activePtr) {
		    break;
		}
	    }
	}
    } else if (switches.mask & FIND_DECREASING) {
	Item *itemPtr;

	itemPtr = switches.fromPtr;
	itemPtr = (itemPtr == NULL) ? LastItem(comboPtr) : PrevItem(itemPtr);
	for (/*empty*/; itemPtr != NULL; itemPtr = PrevItem(itemPtr)) {
	    int found;

	    if ((switches.type > 0) && ((switches.type & itemPtr->flags)==0)) {
		continue;
	    }
	    if (switches.mask & FIND_GLOB) {
		found = Tcl_StringMatch(itemPtr->label, pattern);
	    } else if (switches.mask & FIND_REGEXP) {
		found = Tcl_RegExpMatch(NULL, itemPtr->label, pattern); 
	    } else {
		found = (strcmp(itemPtr->label, pattern) == 0);
	    }
	    if (found) {
		index = itemPtr->index;
		break;
	    }
	}
    } else {
	Blt_ChainLink link;
	Item *itemPtr;

	itemPtr = switches.fromPtr;
	itemPtr = (itemPtr == NULL) ? FirstItem(comboPtr) : NextItem(itemPtr);
	for (link = itemPtr->link; link != NULL; 
	     link = Blt_Chain_NextLink(link)) {
	    int found;
	    
	    itemPtr = Blt_Chain_GetValue(link);
	    if ((switches.type > 0) && ((switches.type & itemPtr->flags)==0)) {
		continue;
	    }
	    if (switches.search == FIND_GLOB) {
		found = Tcl_StringMatch(itemPtr->label, pattern);
	    } else if (switches.search == FIND_REGEXP) {
		found = Tcl_RegExpMatch(NULL, itemPtr->label, pattern); 
	    } else {
		found = (strcmp(itemPtr->label, pattern) == 0);
	    }
	    if (found) {
		index = itemPtr->index;
		break;
	    }
	}
    }
    Tcl_SetLongObj(Tcl_GetObjResult(interp), index);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * IndexOp --
 *
 * Results:
 *	Standard TCL result.
 *
 * Side effects:
 *	Commands may get excecuted; variables may get set; sub-menus may
 *	get posted.
 *
 *	.cm index item 
 *
 *---------------------------------------------------------------------------
 */
static int
IndexOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Item *itemPtr;
    int index;

    index = -1;
    if (GetItemFromObj(NULL, comboPtr, objv[2], &itemPtr) == TCL_OK) {
	if (itemPtr != NULL) {
	    index = itemPtr->index;
	}
    }
    Tcl_SetLongObj(Tcl_GetObjResult(interp), index);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * InvokeOp --
 *
 * Results:
 *	Standard TCL result.
 *
 * Side effects:
 *	Commands may get excecuted; variables may get set; sub-menus may
 *	get posted.
 *
 *  .cm invoke item 
 *
 *---------------------------------------------------------------------------
 */
static int
InvokeOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, 
	 Tcl_Obj *const *objv)
{
    int result;
    Item *itemPtr;

    if (GetItemFromObj(interp, comboPtr, objv[2], &itemPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if ((itemPtr == NULL) || (itemPtr->flags & ITEM_DISABLED)) {
	return TCL_OK;		/* Item is currently disabled. */
    }
    result = TCL_OK;
    Tcl_Preserve(itemPtr);
    result = SelectItem(interp, comboPtr, itemPtr, -1);
    /*
     * We check nItems in addition to whether the item has a command because
     * that goes to zero if the combomenu is deleted (e.g., during command
     * evaluation).
     */
    if ((Blt_Chain_GetLength(comboPtr->chain) > 0) && (result == TCL_OK) && 
	(itemPtr->cmdObjPtr != NULL)) {
	Tcl_IncrRefCount(itemPtr->cmdObjPtr);
	result = Tcl_EvalObjEx(interp, itemPtr->cmdObjPtr, TCL_EVAL_GLOBAL);
	Tcl_DecrRefCount(itemPtr->cmdObjPtr);
    }
    Tcl_Release(itemPtr);
    return result;
}

/*
 *---------------------------------------------------------------------------
 *
 * InsertOp --
 *
 *	Inserts a new item into the combomenu at the given index.
 *
 * Results:
 *	NULL is always returned.
 *
 * Side effects:
 *	The combomenu gets a new item.
 *
 *   .cm insert before 0 after 1 -text label 
 *
 *---------------------------------------------------------------------------
 */
static int
InsertOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, 
	 Tcl_Obj *const *objv)
{
    Item *itemPtr, *wherePtr;
    int dir;
    static const char *dirs[] = { "after", "at", "before" , NULL};

    if (Tcl_GetIndexFromObj(interp, objv[2], dirs, "key", 0, &dir) != TCL_OK) {
	return TCL_ERROR;
    }
    if (GetItemFromObj(interp, comboPtr, objv[3], &wherePtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if (wherePtr == NULL) {
	Tcl_AppendResult(interp, "can't insert item: no index \"", 
			 Tcl_GetString(objv[3]), "\"", (char *)NULL);
    	return TCL_ERROR;		/* No item. */
    }
    itemPtr = NewItem(comboPtr);
    if (ConfigureItem(interp, itemPtr, objc - 4, objv + 4, 0) != TCL_OK) {
	DestroyItem(itemPtr);
	return TCL_ERROR;		/* Error configuring the entry. */
    }
    MoveItem(comboPtr, itemPtr, dir, wherePtr);
    EventuallyRedraw(comboPtr);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * ItemConfigureOp --
 *
 *	This procedure handles item operations.
 *
 * Results:
 *	A standard TCL result.
 *
 *	.cm item configure item ?option value?...
 *
 *---------------------------------------------------------------------------
 */
static int
ItemConfigureOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, 
		Tcl_Obj *const *objv)
{
    Item *itemPtr;
    ItemIterator iter;

    if (GetItemIterator(interp, comboPtr, objv[3], &iter) != TCL_OK) {
	return TCL_ERROR;
    }
    iconOption.clientData = comboPtr;
    for (itemPtr = FirstTaggedItem(&iter); itemPtr != NULL; 
	 itemPtr = NextTaggedItem(&iter)) {
	int result;
	unsigned int flags;

	flags = BLT_CONFIG_OBJV_ONLY;
	if (objc == 4) {
	    return Blt_ConfigureInfoFromObj(interp, comboPtr->tkwin, 
		itemConfigSpecs, (char *)itemPtr, (Tcl_Obj *)NULL, flags);
	} else if (objc == 5) {
	    return Blt_ConfigureInfoFromObj(interp, comboPtr->tkwin, 
		itemConfigSpecs, (char *)itemPtr, objv[4], flags);
	}
	Tcl_Preserve(itemPtr);
	result = ConfigureItem(interp, itemPtr, objc - 4, objv + 4,  flags);
	Tcl_Release(itemPtr);
	if (result == TCL_ERROR) {
	    return TCL_ERROR;
	}
    }
    comboPtr->flags |= (LAYOUT_PENDING | SCROLL_PENDING);
    EventuallyRedraw(comboPtr);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * ItemCgetOp --
 *
 *	This procedure handles item operations.
 *
 * Results:
 *	A standard TCL result.
 *
 *	.cm item cget item option
 *
 *---------------------------------------------------------------------------
 */
static int
ItemCgetOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, 
	   Tcl_Obj *const *objv)
{
    Item *itemPtr;

    if (GetItemFromObj(interp, comboPtr, objv[3], &itemPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if (itemPtr == NULL) {
	Tcl_AppendResult(interp, "can't retrieve item \"", 
			 Tcl_GetString(objv[3]), "\"", (char *)NULL);
	return TCL_ERROR;
    }
    iconOption.clientData = comboPtr;
    return Blt_ConfigureValueFromObj(interp, comboPtr->tkwin, itemConfigSpecs,
	(char *)itemPtr, objv[4], 0);
}

/*
 *---------------------------------------------------------------------------
 *
 * ItemOp --
 *
 *	This procedure handles item operations.
 *
 * Results:
 *	A standard TCL result.
 *
 *---------------------------------------------------------------------------
 */
static Blt_OpSpec itemOps[] = {
    {"cget",      2, ItemCgetOp,      5, 5, "item option",},
    {"configure", 2, ItemConfigureOp, 4, 0, "item ?option value?...",},
};
    
static int nItemOps = sizeof(itemOps) / sizeof(Blt_OpSpec);

static int
ItemOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    ComboMenuCmdProc *proc;
    int result;

    proc = Blt_GetOpFromObj(interp, nItemOps, itemOps, BLT_OP_ARG2, objc, objv, 
		0);
    if (proc == NULL) {
	return TCL_ERROR;
    }
    result = (*proc) (comboPtr, interp, objc, objv);
    return result;
}

/*
 *---------------------------------------------------------------------------
 *
 * NamesOp --
 *
 *	.cm names pattern...
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
NamesOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tcl_Obj *listObjPtr;
    int i;

    listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
    for (i = 2; i < objc; i++) {
	const char *pattern;
	Blt_ChainLink link;

	pattern = Tcl_GetString(objv[i]);
	for (link = Blt_Chain_FirstLink(comboPtr->chain); link != NULL; 
	     link = Blt_Chain_NextLink(link)) {
	    Item *itemPtr;
	    Tcl_Obj *objPtr;

	    itemPtr = Blt_Chain_GetValue(link);
	    if (Tcl_StringMatch(itemPtr->label, pattern)) {
		if (itemPtr->label == emptyString) {
		    objPtr = Tcl_NewStringObj("", -1);
		} else {
		    objPtr = Tcl_NewStringObj(itemPtr->label, -1);
		}
		Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	    }
	}
    }
    Tcl_SetObjResult(interp, listObjPtr);
    return TCL_OK;
}

/*ARGSUSED*/
static int
NearestOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, 
	  Tcl_Obj *const *objv)
{
    int x, y;			
    int wx, wy;			
    Item *itemPtr;
    int isRoot;
    char *string;

    isRoot = FALSE;
    string = Tcl_GetString(objv[2]);
    if (strcmp("-root", string) == 0) {
	isRoot = TRUE;
	objv++, objc--;
    } 
    if (objc < 4) {
	Tcl_AppendResult(interp, "wrong # args: should be \"", 
		Tcl_GetString(objv[0]), " ", Tcl_GetString(objv[1]), 
		" ?-root? x y\"", (char *)NULL);
	return TCL_ERROR;
			 
    }
    if ((Tk_GetPixelsFromObj(interp, comboPtr->tkwin, objv[2], &x) != TCL_OK) ||
	(Tk_GetPixelsFromObj(interp, comboPtr->tkwin, objv[3], &y) != TCL_OK)) {
	return TCL_ERROR;
    }
    if (isRoot) {
	int rootX, rootY;

	Tk_GetRootCoords(comboPtr->tkwin, &rootX, &rootY);
	x -= rootX;
	y -= rootY;
    }
    itemPtr = NearestItem(comboPtr, x, y, TRUE);
    if (itemPtr == NULL) {
	return TCL_OK;
    }
    x = WORLDX(comboPtr, x);
    y = WORLDY(comboPtr, y);
    wx = itemPtr->xWorld + ITEM_XPAD;
    wy = itemPtr->xWorld + ITEM_XPAD;
    if (objc > 4) {
	const char *where;

	where = "";
	if (itemPtr->flags & (ITEM_RADIOBUTTON | ITEM_CHECKBUTTON)) {
	    int bx, by, bw, bh;

	    bx = wx;
	    by = wy;
	    if (itemPtr->flags & ITEM_RADIOBUTTON) {
		bw = IconWidth(comboPtr->rbIcon);
		bh = IconHeight(comboPtr->rbIcon);
	    } else {
		bw = IconWidth(comboPtr->cbIcon);
		bh = IconHeight(comboPtr->cbIcon);
	    }
	    wx += comboPtr->leftIndWidth + ITEM_IPAD;
	    if ((x >= bx) && (x < (bx + bw)) && (y >= by) && (y < (by + bh))) {
		if (itemPtr->flags & ITEM_RADIOBUTTON) {
		    where = "radiobutton";
		} else {
		    where = "checkbutton";
		}		    
		goto done;
	    }
	} 
	if (itemPtr->icon != NULL) {
	    int ix, iy, iw, ih;
	    
	    ih = IconHeight(itemPtr->icon);
	    iw = IconWidth(itemPtr->icon);
	    ix = wx;
	    iy = wy;
	    wx += comboPtr->iconWidth + ITEM_IPAD;
	    if ((x >= ix) && (x <= (ix + iw)) && (y >= iy) && (y < (iy + ih))) {
		where = "icon";
		goto done;
	    }
	}
	if ((itemPtr->label != emptyString) || (itemPtr->image != NULL)) {
	    int lx, ly;

	    lx = wx;
	    ly = wy;

	    wx += comboPtr->labelWidth + ITEM_IPAD;
	    if ((x >= lx) && (x < (lx + itemPtr->labelWidth)) &&
		(y >= ly) && (y < (ly + itemPtr->labelHeight))) {
		where = "label";
		goto done;
	    }
	}
	if ((itemPtr->accel != NULL) || (itemPtr->flags & ITEM_CASCADE)) {
	    int ax, ay, aw, ah;

	    ax = wx;
	    ay = wy;
	    aw = itemPtr->rightIndWidth;
	    ah = itemPtr->rightIndHeight;
	    if ((x >= ax) && (x < (ax + aw)) && (y >= ay) && (y < (ay + ah))) {
		if (itemPtr->flags & ITEM_CASCADE) {
		    where = "cascade";
		} else {
		    where = "accelerator";
		}
		goto done;
	    }

	}
    done:
	if (Tcl_SetVar(interp, Tcl_GetString(objv[4]), where, 
		TCL_LEAVE_ERR_MSG) == NULL) {
	    return TCL_ERROR;
	}
    }
    Tcl_SetLongObj(Tcl_GetObjResult(interp), itemPtr->index);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * NextOp --
 *
 * Results:
 *	Standard TCL result.
 *
 * Side effects:
 *	Commands may get excecuted; variables may get set; sub-menus may
 *	get posted.
 *
 *	.cm next item 
 *
 *---------------------------------------------------------------------------
 */
static int
NextOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Item *itemPtr;
    int index;

    index = -1;
    if (GetItemFromObj(NULL, comboPtr, objv[2], &itemPtr) == TCL_OK) {
	itemPtr = NextItem(itemPtr);
	if (itemPtr != NULL) {
	    index = itemPtr->index;
	}
    }
    Tcl_SetLongObj(Tcl_GetObjResult(interp), index);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * PostOp --
 *
 *	Posts this menu at the given root screen coordinates.
 *
 *  .cm post ?switches?
 *
 *	-anchor ne -fill yes -width 80 -x -y 
 *	.cm post -x 0 -y 0 -reqwidth -reqheight -anchor -fill yes 
 *---------------------------------------------------------------------------
 */
static int
PostOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    int x, y;
    Tk_Window parent;
    int menuWidth;

    if ((Tcl_GetIntFromObj(interp, objv[2], &x) != TCL_OK) || 
	(Tcl_GetIntFromObj(interp, objv[3], &y) != TCL_OK)) {
	return TCL_ERROR;
    } 
    parent = Tk_Parent(comboPtr->tkwin);
    comboPtr->parentWidth = 0;
    menuWidth = comboPtr->normalWidth;
    if (menuWidth < Tk_Width(parent)) {
	menuWidth = Tk_Width(parent);
    }
    if (objc == 5) {
	const char *string;

	string = Tcl_GetString(objv[4]);
	if (strcmp(string, "left") == 0) {
	    /* Do nothing. */
	} else if (strcmp(string, "right") == 0) {
	    x -= menuWidth;
	} else if (strcmp(string, "center") == 0) {
	    x -= menuWidth / 2;
	} else if (strcmp(string, "popup") == 0) {
	    /* Do nothing. */
	    parent = comboPtr->tkwin;
	} else {
	    Tcl_AppendResult(interp, "bad alignment value \"", string, 
		"\": should be left, right, or center.", (char *)NULL);
	    return TCL_ERROR;
	}
	comboPtr->parentWidth = Tk_Width(parent);
    }
    if (comboPtr->flags & LAYOUT_PENDING) {
	ComputeComboGeometry(comboPtr);
    }
    FixMenuCoords(comboPtr, parent, &x, &y);
    /*
     * If there is a post command for the menu, execute it.  This may change
     * the size of the menu, so be sure to recompute the menu's geometry if
     * needed.
     */
    if (comboPtr->postCmdObjPtr != NULL) {
	int result;

	Tcl_IncrRefCount(comboPtr->postCmdObjPtr);
	result = Tcl_EvalObjEx(interp, comboPtr->postCmdObjPtr, 
		TCL_EVAL_GLOBAL);
	Tcl_DecrRefCount(comboPtr->postCmdObjPtr);
	if (result != TCL_OK) {
	    return result;
	}
	/*
	 * The post commands could have deleted the menu, which means we are
	 * dead and should go away.
	 */
	if (comboPtr->tkwin == NULL) {
	    return TCL_OK;
	}
	if (comboPtr->flags & LAYOUT_PENDING) {
	    ComputeComboGeometry(comboPtr);
	}
    }

    /*
     * Adjust the position of the menu if necessary to keep it visible on the
     * screen.  There are two special tricks to make this work right:
     *
     * 1. If a virtual root window manager is being used then
     *    the coordinates are in the virtual root window of
     *    menuPtr's parent;  since the menu uses override-redirect
     *    mode it will be in the *real* root window for the screen,
     *    so we have to map the coordinates from the virtual root
     *    (if any) to the real root.  Can't get the virtual root
     *    from the menu itself (it will never be seen by the wm)
     *    so use its parent instead (it would be better to have an
     *    an option that names a window to use for this...).
     * 2. The menu may not have been mapped yet, so its current size
     *    might be the default 1x1.  To compute how much space it
     *    needs, use its requested size, not its actual size.
     *
     * Note that this code assumes square screen regions and all positive
     * coordinates. This does not work on a Mac with multiple monitors. But
     * then again, Tk has other problems with this.
     */
    {
	int vx, vy, vw, vh;
	int tmp;
	int screenWidth, screenHeight;

	Blt_SizeOfScreen(comboPtr->tkwin, &screenWidth, &screenHeight);
	Tk_GetVRootGeometry(parent, &vx, &vy, &vw, &vh);
	x += vx;
	y += vy;
	tmp = screenWidth - Tk_Width(comboPtr->tkwin);
	if (x > tmp) {
	    x = tmp;
	}
	if (x < 0) {
	    x = 0;
	}
	tmp = screenHeight - Tk_Height(comboPtr->tkwin);
	if (y > tmp) {
	    y = tmp;
	}
	if (y < 0) {
	    y = 0;
	}
	Tk_MoveToplevelWindow(comboPtr->tkwin, x, y);
	if (!Tk_IsMapped(comboPtr->tkwin)) {
	    Tk_MapWindow(comboPtr->tkwin);
	}
	Blt_MapToplevelWindow(comboPtr->tkwin);
	Blt_RaiseToplevelWindow(comboPtr->tkwin);
#ifdef notdef
	TkWmRestackToplevel(comboPtr->tkwin, Above, NULL);
#endif
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * PostCascadeOp --
 *
 *	Posts the menu of a cascade item.  If the item is a cascade menu, then
 *	the submenu is requested to be posted.
 *
 * Results: 
 *	A standard TCL result.
 *
 * Side effects:  
 *	The item's submenu may be posted.
 *
 *  .cm postcascade item
 *
 *---------------------------------------------------------------------------
 */
static int
PostCascadeOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, 
	      Tcl_Obj *const *objv)
{
    Item *itemPtr;
    char *string;

    string = Tcl_GetString(objv[2]);
    if (GetItemFromObj(interp, comboPtr, objv[2], &itemPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if (itemPtr == comboPtr->postedPtr) {
	return TCL_OK;			/* Nothing to do, submenu is already
					 * posted. */
    }
    if (UnpostCascade(interp, comboPtr) != TCL_OK) {
	return TCL_ERROR;		/* Error unposting submenu. */
    }
    if ((itemPtr != NULL) && (itemPtr->menuObjPtr != NULL) && 
	((itemPtr->flags & (ITEM_CASCADE|ITEM_DISABLED)) == ITEM_CASCADE)) {
	return PostCascade(interp, comboPtr, itemPtr);
    }
    return TCL_OK;			/* No menu to post. */
}

/*
 *---------------------------------------------------------------------------
 *
 * PreviousOp --
 *
 * Results:
 *	Standard TCL result.
 *
 * Side effects:
 *	Commands may get excecuted; variables may get set; sub-menus may
 *	get posted.
 *
 *	.cm previous item 
 *
 *---------------------------------------------------------------------------
 */
static int
PreviousOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, 
	   Tcl_Obj *const *objv)
{
    Item *itemPtr;
    int index;

    index = -1;
    if (GetItemFromObj(NULL, comboPtr, objv[2], &itemPtr) == TCL_OK) {
	itemPtr = PrevItem(itemPtr);
	if (itemPtr != NULL) {
	    index = itemPtr->index;
	}
    }
    Tcl_SetLongObj(Tcl_GetObjResult(interp), index);
    return TCL_OK;
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
ScanOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    int oper;
    int x, y;

#define SCAN_MARK	1
#define SCAN_DRAGTO	2
    {
	char *string;
	char c;
	int length;
	
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
    }
    if ((Blt_GetPixelsFromObj(interp, comboPtr->tkwin, objv[3], PIXELS_ANY, &x) 
	 != TCL_OK) ||
	(Blt_GetPixelsFromObj(interp, comboPtr->tkwin, objv[4], PIXELS_ANY, &y) 
	 != TCL_OK)) {
	return TCL_ERROR;
    }
    if (oper == SCAN_MARK) {
	comboPtr->scanAnchorX = x;
	comboPtr->scanAnchorY = y;
	comboPtr->scanX = comboPtr->xOffset;
	comboPtr->scanY = comboPtr->yOffset;
    } else {
	int xWorld, yWorld;
	int viewWidth, viewHeight;
	int dx, dy;

	dx = comboPtr->scanAnchorX - x;
	dy = comboPtr->scanAnchorY - y;
	xWorld = comboPtr->scanX + (10 * dx);
	yWorld = comboPtr->scanY + (10 * dy);

	viewWidth = VPORTWIDTH(comboPtr);
	if (xWorld > (comboPtr->worldWidth - viewWidth)) {
	    xWorld = comboPtr->worldWidth - viewWidth;
	}
	if (xWorld < 0) {
	    xWorld = 0;
	}
	viewHeight = VPORTHEIGHT(comboPtr);
	if (yWorld > (comboPtr->worldHeight - viewHeight)) {
	    yWorld = comboPtr->worldHeight - viewHeight;
	}
	if (yWorld < 0) {
	    yWorld = 0;
	}
	comboPtr->xOffset = xWorld;
	comboPtr->yOffset = yWorld;
	comboPtr->flags |= SCROLL_PENDING;
	EventuallyRedraw(comboPtr);
    }
    return TCL_OK;
}


/*ARGSUSED*/
static int
SeeOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Item *itemPtr;
    int x, y, w, h;
    Tk_Anchor anchor;
    int left, right, top, bottom;
    char *string;

    string = Tcl_GetString(objv[2]);
    anchor = TK_ANCHOR_W;		/* Default anchor is West */
    if ((string[0] == '-') && (strcmp(string, "-anchor") == 0)) {
	if (objc == 3) {
	    Tcl_AppendResult(interp, "missing \"-anchor\" argument",
		(char *)NULL);
	    return TCL_ERROR;
	}
	if (Tk_GetAnchorFromObj(interp, objv[3], &anchor) != TCL_OK) {
	    return TCL_ERROR;
	}
	objc -= 2, objv += 2;
    }
    if (objc == 2) {
	Tcl_AppendResult(interp, "wrong # args: should be \"", objv[0],
	    "see ?-anchor anchor? item\"", (char *)NULL);
	return TCL_ERROR;
    }
    if (GetItemFromObj(interp, comboPtr, objv[2], &itemPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if (itemPtr == NULL) {
	return TCL_OK;
    }

    w = VPORTWIDTH(comboPtr);
    h = VPORTHEIGHT(comboPtr);

    /*
     * XVIEW:	If the entry is left or right of the current view, adjust
     *		the offset.  If the entry is nearby, adjust the view just
     *		a bit.  Otherwise, center the entry.
     */
    left = comboPtr->xOffset;
    right = comboPtr->xOffset + w;

    switch (anchor) {
    case TK_ANCHOR_W:
    case TK_ANCHOR_NW:
    case TK_ANCHOR_SW:
	x = 0;
	break;
    case TK_ANCHOR_E:
    case TK_ANCHOR_NE:
    case TK_ANCHOR_SE:
	x = itemPtr->xWorld + itemPtr->width - w;
	break;
    default:
	if (itemPtr->xWorld < left) {
	    x = itemPtr->xWorld;
	} else if ((itemPtr->xWorld + itemPtr->width) > right) {
	    x = itemPtr->xWorld + itemPtr->width - w;
	} else {
	    x = comboPtr->xOffset;
	}
	break;
    }

    /*
     * YVIEW:	If the entry is above or below the current view, adjust
     *		the offset.  If the entry is nearby, adjust the view just
     *		a bit.  Otherwise, center the entry.
     */
    top = comboPtr->yOffset;
    bottom = comboPtr->yOffset + h;

    switch (anchor) {
    case TK_ANCHOR_N:
	y = comboPtr->yOffset;
	break;
    case TK_ANCHOR_NE:
    case TK_ANCHOR_NW:
	y = itemPtr->yWorld - (h / 2);
	break;
    case TK_ANCHOR_S:
    case TK_ANCHOR_SE:
    case TK_ANCHOR_SW:
	y = itemPtr->yWorld + itemPtr->height - h;
	break;
    default:
	if (itemPtr->yWorld < top) {
	    y = itemPtr->yWorld;
	} else if ((itemPtr->yWorld + itemPtr->height) > bottom) {
	    y = itemPtr->yWorld + itemPtr->height - h;
	} else {
	    y = comboPtr->yOffset;
	}
	break;
    }
    if ((y != comboPtr->yOffset) || (x != comboPtr->xOffset)) {
	comboPtr->xOffset = x;
	comboPtr->yOffset = y;
	comboPtr->flags |= SCROLL_PENDING;
    }
    EventuallyRedraw(comboPtr);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * InvokeOp --
 *
 * Results:
 *	Standard TCL result.
 *
 * Side effects:
 *	Commands may get excecuted; variables may get set; sub-menus may
 *	get posted.
 *
 *  .cm select item 
 *
 *---------------------------------------------------------------------------
 */
static int
SelectOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, 
	 Tcl_Obj *const *objv)
{
    Item *itemPtr;
    const char *cmd;
    int result;

    if (GetItemFromObj(interp, comboPtr, objv[2], &itemPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if ((itemPtr == NULL) || (itemPtr->flags & ITEM_DISABLED)) {
	return TCL_OK;			/* Item is currently disabled. */
    }
    cmd = Tcl_GetString(objv[1]);
    Tcl_Preserve(itemPtr);
    result = SelectItem(interp, comboPtr, itemPtr, cmd[0] == 's');
    Tcl_Release(itemPtr);
    return result;
}

/*ARGSUSED*/
static int
SizeOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Tcl_SetLongObj(Tcl_GetObjResult(interp), 
		   Blt_Chain_GetLength(comboPtr->chain));
    return TCL_OK;
}

/* .m style create name option value option value */
    
static int
StyleCreateOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, 
	      Tcl_Obj *const *objv)
{
    Style *stylePtr;
    Blt_HashEntry *hPtr;
    int isNew;

    hPtr = Blt_CreateHashEntry(&comboPtr->styleTable, Tcl_GetString(objv[3]),
		&isNew);
    if (!isNew) {
	Tcl_AppendResult(interp, "combomenu style \"", Tcl_GetString(objv[3]),
		"\" already exists.", (char *)NULL);
	return TCL_ERROR;
    }
    stylePtr = Blt_AssertCalloc(1, sizeof(Style));
    stylePtr->name = Blt_GetHashKey(&comboPtr->styleTable, hPtr);
    stylePtr->hPtr = hPtr;
    stylePtr->comboPtr = comboPtr;
    stylePtr->borderWidth = 0;
    stylePtr->activeRelief = TK_RELIEF_RAISED;
    Blt_SetHashValue(hPtr, stylePtr);
    iconOption.clientData = comboPtr;
    if (ConfigureStyle(interp, stylePtr, objc - 4, objv + 4, 0) != TCL_OK) {
	DestroyStyle(stylePtr);
	return TCL_ERROR;
    }
    return TCL_OK;
}

static int
StyleCgetOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, 
	    Tcl_Obj *const *objv)
{
    Style *stylePtr;

    if (GetStyleFromObj(interp, comboPtr, objv[3], &stylePtr) != TCL_OK) {
	return TCL_ERROR;
    }
    iconOption.clientData = comboPtr;
    return Blt_ConfigureValueFromObj(interp, comboPtr->tkwin, styleConfigSpecs,
	(char *)stylePtr, objv[4], 0);
}

static int
StyleConfigureOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, 
		 Tcl_Obj *const *objv)
{
    int result, flags;
    Style *stylePtr;

    if (GetStyleFromObj(interp, comboPtr, objv[3], &stylePtr) != TCL_OK) {
	return TCL_ERROR;
    }
    iconOption.clientData = comboPtr;
    flags = BLT_CONFIG_OBJV_ONLY;
    if (objc == 1) {
	return Blt_ConfigureInfoFromObj(interp, comboPtr->tkwin, 
		styleConfigSpecs, (char *)stylePtr, (Tcl_Obj *)NULL, flags);
    } else if (objc == 2) {
	return Blt_ConfigureInfoFromObj(interp, comboPtr->tkwin, 
		styleConfigSpecs, (char *)stylePtr, objv[2], flags);
    }
    Tcl_Preserve(stylePtr);
    result = ConfigureStyle(interp, stylePtr, objc - 4, objv + 4, flags);
    Tcl_Release(stylePtr);
    if (result == TCL_ERROR) {
	return TCL_ERROR;
    }
    comboPtr->flags |= (LAYOUT_PENDING | SCROLL_PENDING);
    EventuallyRedraw(comboPtr);
    return TCL_OK;
}

static int
StyleDeleteOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, 
	      Tcl_Obj *const *objv)
{
    Style *stylePtr;

    if (GetStyleFromObj(interp, comboPtr, objv[3], &stylePtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if (stylePtr->refCount > 0) {
	Tcl_AppendResult(interp, "can't destroy combomenu style \"", 
			 stylePtr->name, "\": style in use.", (char *)NULL);
	return TCL_ERROR;
    }
    DestroyStyle(stylePtr);
    return TCL_OK;
}

static int
StyleNamesOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, 
	     Tcl_Obj *const *objv)
{
    Blt_HashEntry *hPtr;
    Blt_HashSearch iter;
    Tcl_Obj *listObjPtr;

    listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
    for (hPtr = Blt_FirstHashEntry(&comboPtr->styleTable, &iter); 
	 hPtr != NULL; hPtr = Blt_NextHashEntry(&iter)) {
	Style *stylePtr;
	int found;
	int i;

	found = TRUE;
	stylePtr = Blt_GetHashValue(hPtr);
	for (i = 3; i < objc; i++) {
	    const char *pattern;

	    pattern = Tcl_GetString(objv[i]);
	    found = Tcl_StringMatch(stylePtr->name, pattern);
	    if (found) {
		break;
	    }
	}
	if (found) {
	    Tcl_ListObjAppendElement(interp, listObjPtr,
		Tcl_NewStringObj(stylePtr->name, -1));
	}
    }
    Tcl_SetObjResult(interp, listObjPtr);
    return TCL_OK;
}

static Blt_OpSpec styleOps[] =
{
    {"cget",        2, StyleCgetOp,        5, 5, "name option",},
    {"configure",   2, StyleConfigureOp,   4, 0, "name ?option value?...",},
    {"create",      2, StyleCreateOp,      4, 0, "name ?option value?...",},
    {"delete",      1, StyleDeleteOp,      3, 0, "?name...?",},
    {"names",       1, StyleNamesOp,       3, 0, "?pattern...?",},
};

static int nStyleOps = sizeof(styleOps) / sizeof(Blt_OpSpec);

static int
StyleOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    ComboMenuCmdProc *proc;
    int result;

    proc = Blt_GetOpFromObj(interp, nStyleOps, styleOps, BLT_OP_ARG2, 
	objc, objv, 0);
    if (proc == NULL) {
	return TCL_ERROR;
    }
    result = (*proc) (comboPtr, interp, objc, objv);
    return result;
}

static int
TypeOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    Item *itemPtr;

    if (GetItemFromObj(interp, comboPtr, objv[2], &itemPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if (itemPtr != NULL) {
	const char *name;

	name = NameOfType(itemPtr->flags);
	Tcl_SetStringObj(Tcl_GetObjResult(interp), name, -1);
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * UnpostOp --
 *
 *	Unposts this menu.
 *
 *  .cm post 
 *
 *---------------------------------------------------------------------------
 */
static int
UnpostOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, 
	 Tcl_Obj *const *objv)
{
    if (!Tk_IsMapped(comboPtr->tkwin)) {
	return TCL_OK;		/* This menu is already unposted. */
    }
    /* Deactivate the current item. */
    if (comboPtr->postedPtr != NULL) {
	if (UnpostCascade(interp, comboPtr) != TCL_OK) {
	    return TCL_ERROR;
	}
	comboPtr->postedPtr = NULL;
    }
    if (Tk_IsMapped(comboPtr->tkwin)) {
	Tk_UnmapWindow(comboPtr->tkwin);
    }
    /*
     * If there is a post command for the menu, execute it.  This may change
     * the size of the menu, so be sure to recompute the menu's geometry if
     * needed.
     */
    if (comboPtr->unpostCmdObjPtr != NULL) {
	int result;

	Tcl_IncrRefCount(comboPtr->unpostCmdObjPtr);
	result = Tcl_EvalObjEx(interp, comboPtr->unpostCmdObjPtr, 
		TCL_EVAL_GLOBAL);
	Tcl_DecrRefCount(comboPtr->unpostCmdObjPtr);
	if (result != TCL_OK) {
	    return TCL_ERROR;
	}
    }
    return TCL_OK;
}

static int
XpositionOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, 
	    Tcl_Obj *const *objv)
{
    Item *itemPtr;

    if (GetItemFromObj(interp, comboPtr, objv[3], &itemPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if (itemPtr == NULL) {
	Tcl_AppendResult(interp, "can't get x-position of item: no item \"", 
			 Tcl_GetString(objv[3]), "\"", (char *)NULL);
	return TCL_ERROR;
    }
    Tcl_SetIntObj(Tcl_GetObjResult(interp), itemPtr->xWorld-comboPtr->xOffset);
    return TCL_OK;
}

static int
XviewOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, Tcl_Obj *const *objv)
{
    int w;

    w = VPORTWIDTH(comboPtr);
    if (objc == 2) {
	double fract;
	Tcl_Obj *listObjPtr, *objPtr;

	/* Report first and last fractions */
	listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
	/*
	 * Note: we are bounding the fractions between 0.0 and 1.0 to support
	 * the "canvas"-style of scrolling.
	 */
	fract = (double)comboPtr->xOffset / (comboPtr->worldWidth+1);
	objPtr = Tcl_NewDoubleObj(FCLAMP(fract));
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	fract = (double)(comboPtr->xOffset + w) / (comboPtr->worldWidth+1);
	objPtr = Tcl_NewDoubleObj(FCLAMP(fract));
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	Tcl_SetObjResult(interp, listObjPtr);
	return TCL_OK;
    }
    if (Blt_GetScrollInfoFromObj(interp, objc - 2, objv + 2, &comboPtr->xOffset,
	comboPtr->worldWidth, w, comboPtr->xScrollUnits, 
	BLT_SCROLL_MODE_HIERBOX) != TCL_OK) {
	return TCL_ERROR;
    }
    comboPtr->flags |= SCROLL_PENDING;
    EventuallyRedraw(comboPtr);
    return TCL_OK;
}

static int
YpositionOp(ComboMenu *comboPtr, Tcl_Interp *interp, int objc, 
	    Tcl_Obj *const *objv)
{
    Item *itemPtr;

    if (GetItemFromObj(interp, comboPtr, objv[3], &itemPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if (itemPtr == NULL) {
	Tcl_AppendResult(interp, "can't get y-position of item: such index \"", 
			 Tcl_GetString(objv[3]), "\"", (char *)NULL);
	return TCL_ERROR;
    }
    Tcl_SetIntObj(Tcl_GetObjResult(interp), itemPtr->yWorld-comboPtr->yOffset);
    return TCL_OK;
}

static int
YviewOp(
    ComboMenu *comboPtr,
    Tcl_Interp *interp,
    int objc,
    Tcl_Obj *const *objv)
{
    int height;

    height = VPORTHEIGHT(comboPtr);
    if (objc == 2) {
	double fract;
	Tcl_Obj *listObjPtr, *objPtr;

	/* Report first and last fractions */
	listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
	/*
	 * Note: we are bounding the fractions between 0.0 and 1.0 to support
	 * the "canvas"-style of scrolling.
	 */
	fract = (double)comboPtr->yOffset / (comboPtr->worldHeight+1);
	objPtr = Tcl_NewDoubleObj(FCLAMP(fract));
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	fract = (double)(comboPtr->yOffset + height) /(comboPtr->worldHeight+1);
	objPtr = Tcl_NewDoubleObj(FCLAMP(fract));
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	Tcl_SetObjResult(interp, listObjPtr);
	return TCL_OK;
    }
    if (Blt_GetScrollInfoFromObj(interp, objc - 2, objv + 2, &comboPtr->yOffset,
	comboPtr->worldHeight, height, comboPtr->yScrollUnits, 
	BLT_SCROLL_MODE_HIERBOX) != TCL_OK) {
	return TCL_ERROR;
    }
    comboPtr->flags |= SCROLL_PENDING;
    EventuallyRedraw(comboPtr);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * DestroyComboMenu --
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
DestroyComboMenu(DestroyData dataPtr)	/* Pointer to the widget record. */
{
    ComboMenu *comboPtr = (ComboMenu *)dataPtr;

    if (comboPtr->flags & REDRAW_PENDING) {
	Tcl_CancelIdleCall(DisplayComboMenu, comboPtr);
    }
    if (comboPtr->flags & INSTALL_XSCROLLBAR) {
	Tcl_CancelIdleCall(InstallXScrollbar, comboPtr);
    }	    
    if (comboPtr->flags & INSTALL_YSCROLLBAR) {
	Tcl_CancelIdleCall(InstallYScrollbar, comboPtr);
    }	    
    if (comboPtr->flags & UPDATE_PENDING) {
	Tcl_CancelIdleCall(ConfigureScrollbarsProc, comboPtr);
    }
    DestroyItems(comboPtr);
    DestroyStyles(comboPtr);
    DestroyLabels(comboPtr);
    Blt_DeleteHashTable(&comboPtr->tagTable);
    DestroyIcons(comboPtr);
    if (comboPtr->painter != NULL) {
	Blt_FreePainter(comboPtr->painter);
    }
    iconOption.clientData = comboPtr;
    Blt_FreeOptions(comboConfigSpecs, (char *)comboPtr, comboPtr->display, 0);
    Tcl_DeleteCommandFromToken(comboPtr->interp, comboPtr->cmdToken);
    Blt_Free(comboPtr);
}

/*
 *---------------------------------------------------------------------------
 *
 * NewComboMenu --
 *
 *---------------------------------------------------------------------------
 */
static ComboMenu *
NewComboMenu(Tcl_Interp *interp, Tk_Window tkwin)
{
    ComboMenu *comboPtr;

    comboPtr = Blt_AssertCalloc(1, sizeof(ComboMenu));

    Tk_SetClass(tkwin, "ComboMenu");

    comboPtr->tkwin = tkwin;
    comboPtr->display = Tk_Display(tkwin);
    comboPtr->interp = interp;
    comboPtr->flags |= LAYOUT_PENDING | SCROLL_PENDING;
    comboPtr->relief = TK_RELIEF_SOLID;
    comboPtr->xScrollUnits = 2;
    comboPtr->yScrollUnits = 2;
    comboPtr->borderWidth = 1;
    comboPtr->chain = Blt_Chain_Create();
    comboPtr->painter = Blt_GetPainter(tkwin, 1.0);
    Blt_ResetLimits(&comboPtr->reqWidth);
    Blt_ResetLimits(&comboPtr->reqHeight);
    Blt_InitHashTable(&comboPtr->iconTable,  BLT_STRING_KEYS);
    Blt_InitHashTable(&comboPtr->labelTable, BLT_STRING_KEYS);
    Blt_InitHashTable(&comboPtr->styleTable, BLT_STRING_KEYS);
    Blt_InitHashTable(&comboPtr->tagTable, BLT_STRING_KEYS);
    AddDefaultStyle(interp, comboPtr);
    Blt_SetWindowInstanceData(tkwin, comboPtr);
    return comboPtr;
}

/*
 *---------------------------------------------------------------------------
 *
 * ComboMenuCmd --
 *
 * 	This procedure is invoked to process the "combomenu" command.  See the
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
static Blt_OpSpec menuOps[] =
{
    {"activate",    2, ActivateOp,    3, 3, "item",},
    {"add",         2, AddOp,         2, 0, "?option value?",},
    {"cget",        2, CgetOp,        3, 3, "option",},
    {"configure",   2, ConfigureOp,   2, 0, "?option value?...",},
    {"delete",      3, DeleteOp,      2, 0, "items...",},
    {"deselect",    3, SelectOp,      3, 3, "item",},
    {"exists",      3, ExistsOp,      3, 3, "item",},
    {"find",        1, FindOp,        3, 0, "string ?switches?",},
    {"index",       3, IndexOp,       3, 3, "item",},
    {"insert",      3, InsertOp,      3, 0, 
	"after|at|before index ?option value?",},
    {"invoke",      3, InvokeOp,      3, 3, "item",},
    {"item",        2, ItemOp,        2, 0, "oper args",},
    {"listadd",     1, AddListOp,     3, 0, "labelList ?option value?",},
    {"names",       2, NamesOp,       2, 0, "?pattern...?",},
    {"nearest",     3, NearestOp,     4, 4, "x y",},
    {"next",        3, NextOp,        3, 3, "item",},
    {"post",        4, PostOp,        4, 5, "x y ?align?",},
    {"postcascade", 5, PostCascadeOp, 3, 3, "item",},
    {"previous",    2, PreviousOp,    3, 3, "item",},
    {"scan",        2, ScanOp,        5, 5, "dragto|mark x y",},
    {"see",         3, SeeOp,         3, 5, "item",},
    {"select",      3, SelectOp,      3, 3, "item",},
    {"size",        2, SizeOp,        2, 2, "",},
    {"style",       2, StyleOp,       2, 0, "op ?args...?",},
    {"type",        1, TypeOp,        3, 3, "item",},
    {"unpost",      1, UnpostOp,      2, 2, "",},
    {"xposition",   2, XpositionOp,   3, 3, "item",},
    {"xview",       2, XviewOp,       2, 5, 
	"?moveto fract? ?scroll number what?",},
    {"yposition",   2, YpositionOp,   3, 3, "item",},
    {"yview",       2, YviewOp,       2, 5, 
	"?moveto fract? ?scroll number what?",},
};

static int nMenuOps = sizeof(menuOps) / sizeof(Blt_OpSpec);

typedef int (ComboInstOp)(ComboMenu *comboPtr, Tcl_Interp *interp, int objc,
			  Tcl_Obj *const *objv);

static int
ComboMenuInstCmdProc(
    ClientData clientData,		/* Information about the widget. */
    Tcl_Interp *interp,			/* Interpreter to report errors back
					 * to. */
    int objc,				/* # of arguments. */
    Tcl_Obj *const *objv)		/* Argument vector. */
{
    ComboInstOp *proc;
    ComboMenu *comboPtr = clientData;
    int result;

    proc = Blt_GetOpFromObj(interp, nMenuOps, menuOps, BLT_OP_ARG1, objc, objv,
	0);
    if (proc == NULL) {
	return TCL_ERROR;
    }
    Tcl_Preserve(comboPtr);
    result = (*proc) (comboPtr, interp, objc, objv);
    Tcl_Release(comboPtr);
    return result;
}

/*
 *---------------------------------------------------------------------------
 *
 * ComboMenuInstCmdDeletedProc --
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
ComboMenuInstCmdDeletedProc(ClientData clientData)
{
    ComboMenu *comboPtr = clientData;	/* Pointer to widget record. */

    if (comboPtr->tkwin != NULL) {
	Tk_Window tkwin;

	tkwin = comboPtr->tkwin;
	comboPtr->tkwin = NULL;
	Tk_DestroyWindow(tkwin);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * ComboMenuCmd --
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
 *---------------------------------------------------------------------------
 */
/* ARGSUSED */
static int
ComboMenuCmd(
    ClientData clientData,		/* Main window associated with
					 * interpreter. */
    Tcl_Interp *interp,			/* Current interpreter. */
    int objc,				/* Number of arguments. */
    Tcl_Obj *const *objv)		/* Argument strings. */
{
    ComboMenu *comboPtr;
    Tcl_CmdInfo cmdInfo;
    Tk_Window tkwin;
    XSetWindowAttributes attrs;
    char *path;
    unsigned int mask;

    if (objc < 2) {
	Tcl_AppendResult(interp, "wrong # args: should be \"", 
		Tcl_GetString(objv[0]), " pathName ?option value?...\"", 
		(char *)NULL);
	return TCL_ERROR;
    }
    /*
     * First time in this interpreter, invoke a procedure to initialize
     * various bindings on the combomenu widget.  If the procedure doesn't
     * already exist, source it from "$blt_library/combomenu.tcl".  We
     * deferred sourcing the file until now so that the variable $blt_library
     * could be set within a script.
     */
    if (!Tcl_GetCommandInfo(interp, "::blt::ComboMenu::PostMenu", &cmdInfo)) {
	if (Tcl_GlobalEval(interp, 
		"source [file join $blt_library combomenu.tcl]") != TCL_OK) {
	    char info[200];
	    sprintf_s(info, 200, "\n    (while loading bindings for %.50s)", 
		    Tcl_GetString(objv[0]));
	    Tcl_AddErrorInfo(interp, info);
	    return TCL_ERROR;
	}
    }
    path = Tcl_GetString(objv[1]);
#define TOP_LEVEL_SCREEN ""
    tkwin = Tk_CreateWindowFromPath(interp, Tk_MainWindow(interp), path, 
	TOP_LEVEL_SCREEN);
    if (tkwin == NULL) {
	return TCL_ERROR;
    }
    comboPtr = NewComboMenu(interp, tkwin);
    if (ConfigureComboMenu(interp, comboPtr, objc - 2, objv + 2, 0) != TCL_OK) {
	Tk_DestroyWindow(comboPtr->tkwin);
	return TCL_ERROR;
    }
    mask = (ExposureMask | StructureNotifyMask | FocusChangeMask);
    Tk_CreateEventHandler(tkwin, mask, ComboMenuEventProc, comboPtr);
    comboPtr->cmdToken = Tcl_CreateObjCommand(interp, path, 
	ComboMenuInstCmdProc, comboPtr, ComboMenuInstCmdDeletedProc);

    attrs.override_redirect = True;
    attrs.backing_store = WhenMapped;
    attrs.save_under = True;
    mask = (CWOverrideRedirect | CWSaveUnder | CWBackingStore);
    Tk_ChangeWindowAttributes(tkwin, mask, &attrs);

    Tk_MakeWindowExist(tkwin);
    Tcl_SetObjResult(interp, objv[1]);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * ComboViewCmd --
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
 *---------------------------------------------------------------------------
 */
/* ARGSUSED */
static int
ComboViewCmd(
    ClientData clientData,		/* Main window associated with
					 * interpreter. */
    Tcl_Interp *interp,			/* Current interpreter. */
    int objc,				/* # of arguments. */
    Tcl_Obj *const *objv)		/* Argument strings. */
{
    ComboMenu *comboPtr;
    Tcl_CmdInfo cmdInfo;
    Tk_Window tkwin;
    char *path;
    unsigned int mask;

    if (objc < 2) {
	Tcl_AppendResult(interp, "wrong # args: should be \"", 
		Tcl_GetString(objv[0]), " pathName ?option value?...\"", 
		(char *)NULL);
	return TCL_ERROR;
    }
    /*
     * First time in this interpreter, invoke a procedure to initialize
     * various bindings on the combomenu widget.  If the procedure doesn't
     * already exist, source it from "$blt_library/combomenu.tcl".  We
     * deferred sourcing the file until now so that the variable $blt_library
     * could be set within a script.
     */
    if (!Tcl_GetCommandInfo(interp, "::blt::ComboMenu::PostMenu", &cmdInfo)) {
	if (Tcl_GlobalEval(interp, 
		"source [file join $blt_library combomenu.tcl]") != TCL_OK) {
	    char info[200];
	    sprintf_s(info, 200, "\n    (while loading bindings for %.50s)", 
		    Tcl_GetString(objv[0]));
	    Tcl_AddErrorInfo(interp, info);
	    return TCL_ERROR;
	}
    }
    path = Tcl_GetString(objv[1]);
    tkwin = Tk_CreateWindowFromPath(interp, Tk_MainWindow(interp), path, NULL);
    if (tkwin == NULL) {
	return TCL_ERROR;
    }
    comboPtr = NewComboMenu(interp, tkwin);
    if (ConfigureComboMenu(interp, comboPtr, objc - 2, objv + 2, 0) != TCL_OK) {
	Tk_DestroyWindow(comboPtr->tkwin);
	return TCL_ERROR;
    }
    mask = (ExposureMask | StructureNotifyMask | FocusChangeMask);
    Tk_CreateEventHandler(tkwin, mask, ComboMenuEventProc, comboPtr);
    comboPtr->cmdToken = Tcl_CreateObjCommand(interp, path, 
	ComboMenuInstCmdProc, comboPtr, ComboMenuInstCmdDeletedProc);

    Tcl_SetObjResult(interp, objv[1]);
    return TCL_OK;
}

int
Blt_ComboMenuInitProc(Tcl_Interp *interp)
{
    static Blt_InitCmdSpec cmdSpec[2] = { 
	{ "combomenu", ComboMenuCmd }, 
	{ "comboview", ComboViewCmd }, 
    };
    return Blt_InitCmds(interp, "::blt", cmdSpec, 2);
}


static void
DrawItemBackground(Item *itemPtr, Drawable drawable, int x, int y)
{
    Blt_Background bg;
    Style *stylePtr;
    ComboMenu *comboPtr;    
    int relief;
    int w, h;

    stylePtr = itemPtr->stylePtr;
    comboPtr = itemPtr->comboPtr;
    relief = itemPtr->relief;
    if ((itemPtr->flags & (ITEM_DISABLED|ITEM_SEPARATOR)) == ITEM_DISABLED) {
	bg = stylePtr->disabledBg;
    } else if (comboPtr->activePtr == itemPtr) {
	bg = stylePtr->activeBg;
	relief = stylePtr->activeRelief;
    } else {
	bg = stylePtr->normalBg;
    }	    
    w = VPORTWIDTH(comboPtr);
    w = MAX(comboPtr->worldWidth, w);
    h = itemPtr->height;
#ifndef notdef
    if (y == 0) {
	int xOrigin, yOrigin;
	int px, py;

	px = PIXMAPX(comboPtr, itemPtr->xWorld);
	py = PIXMAPY(comboPtr, itemPtr->yWorld);
	Blt_GetBackgroundOrigin(bg, &xOrigin, &yOrigin);
	Blt_SetBackgroundOrigin(comboPtr->tkwin, bg, px, py);
	Blt_FillBackgroundRectangle(comboPtr->tkwin, drawable, bg, x, y, 
		w, h, stylePtr->borderWidth, relief);
	Blt_SetBackgroundOrigin(comboPtr->tkwin, bg, xOrigin, yOrigin);
    } else {
	Blt_FillBackgroundRectangle(comboPtr->tkwin, drawable, bg, x, y, 
		w, h, stylePtr->borderWidth, relief);
    }	
#else
    Blt_FillBackgroundRectangle(comboPtr->tkwin, drawable, bg, x, y, w, h,
	stylePtr->borderWidth, relief);
#endif
}

static void
DrawSeparator(Item *itemPtr, Drawable drawable, int x, int y, int w, int h)
{
    XPoint points[2];
    Tk_3DBorder border;
    ComboMenu *comboPtr;    
    Style *stylePtr;

    comboPtr = itemPtr->comboPtr;
    stylePtr = itemPtr->stylePtr;
    border = Blt_BackgroundBorder(stylePtr->normalBg);
    points[0].x = x + ITEM_XPAD;
    points[0].y = y + h / 2;
    points[1].x = w - 2 * ITEM_XPAD;
    points[1].y = points[0].y;
    Tk_Draw3DPolygon(comboPtr->tkwin, drawable, border, points, 2, 1, 
		     TK_RELIEF_SUNKEN);
}

static void
DrawCheckButton(Item *itemPtr, Drawable drawable, int x, int y, int w, int h)
{
    Style *stylePtr;
    Display *display;
    ComboMenu *comboPtr;
    XColor *outlineColor, *fillColor, *checkColor;

    comboPtr = itemPtr->comboPtr;
    Blt_Picture picture;
    int on;
    stylePtr = itemPtr->stylePtr;
    display = itemPtr->comboPtr->display;
    on = (itemPtr->flags & ITEM_SELECTED);
    fillColor = (stylePtr->indFillColor) 
	? stylePtr->indFillColor : comboPtr->checkButtonFillColor;
    outlineColor = (stylePtr->indOutlineColor) 
	? stylePtr->indOutlineColor : comboPtr->checkButtonOutlineColor;
    checkColor = (stylePtr->indColor) 
	? stylePtr->indColor : comboPtr->checkButtonColor;
    if (itemPtr->flags & ITEM_DISABLED) {
	if (stylePtr->checkbutton[0] == NULL) {
	    if (fillColor != NULL) {
		fillColor = Blt_BackgroundBorderColor(stylePtr->disabledBg);
	    }
	    if (outlineColor != NULL) {
		outlineColor = stylePtr->labelDisabledColor;
	    }
	    stylePtr->checkbutton[0] = 
		Blt_PaintCheckbox(w, h, fillColor, outlineColor,
			Blt_BackgroundBorderColor(stylePtr->disabledBg),
			FALSE);
	} 
	picture = stylePtr->checkbutton[0];
    } else {
	Blt_Picture *picturePtr;

	picturePtr = (on) ? stylePtr->checkbutton + 1 :
	    stylePtr->checkbutton + 2;
	if (*picturePtr == NULL) {
	    *picturePtr = Blt_PaintCheckbox(w, h, fillColor, outlineColor, 
		checkColor, on);
	}
	picture = *picturePtr;
    }
    Blt_PaintPicture(comboPtr->painter, drawable, picture, 0, 0, w, h, x, y, 0);
}

static void
DrawRadioButton(Item *itemPtr, Drawable drawable, int x, int y, int w, int h)
{
    Style *stylePtr;
    Display *display;
    ComboMenu *comboPtr;
    Blt_Picture picture;
    int on;

    comboPtr = itemPtr->comboPtr;
    stylePtr = itemPtr->stylePtr;
    display = itemPtr->comboPtr->display;

    on = (itemPtr->flags & ITEM_SELECTED);
    if (itemPtr->flags & ITEM_DISABLED) {
	picture = stylePtr->radiobutton[0];
	if (picture == NULL) {
	    picture = Blt_PaintRadioButton(w, h, 
		Blt_BackgroundBorderColor(stylePtr->disabledBg),
		stylePtr->labelDisabledColor,
		stylePtr->labelDisabledColor,
		FALSE);
	    stylePtr->radiobutton[0] = picture;
	} 
    } else {
	Blt_Picture *picturePtr;

	picturePtr = (on) ? stylePtr->radiobutton + 1 :
	    stylePtr->radiobutton + 2;
	if (*picturePtr == NULL) {
	    XColor *fillColor, *circleColor, *outlineColor;

	    fillColor = (stylePtr->indFillColor) 
		? stylePtr->indFillColor : comboPtr->radioButtonFillColor;
	    outlineColor = (stylePtr->indOutlineColor) 
		? stylePtr->indOutlineColor : comboPtr->radioButtonOutlineColor;
	    circleColor = (stylePtr->indColor) 
		? stylePtr->indColor : comboPtr->radioButtonColor;
	    *picturePtr = Blt_PaintRadioButton(w, h, fillColor, outlineColor, 
		circleColor, on);
	}
	picture = *picturePtr;
    }
    Blt_PaintPicture(comboPtr->painter, drawable, picture, 0, 0, w, h, x, y, 0);
}

static void
DrawItem(Item *itemPtr, Drawable drawable, int x, int y)
{
    ComboMenu *comboPtr;    
    Style *stylePtr;
    int x0, w, h;

    itemPtr->flags &= ~ITEM_REDRAW;
    stylePtr = itemPtr->stylePtr;
    comboPtr = itemPtr->comboPtr;
    x0 = x;
    w = VPORTWIDTH(comboPtr) - 2 * stylePtr->borderWidth;
    x += stylePtr->borderWidth + comboPtr->borderWidth;
    h = itemPtr->height - 2 * stylePtr->borderWidth;
    y += stylePtr->borderWidth;
    if (itemPtr->flags & ITEM_SEPARATOR) {
	DrawSeparator(itemPtr, drawable, x, y, w, h);
	y += ITEM_SEP_HEIGHT;
    } else {	    
	x += ITEM_IPAD;
	/* Radiobutton or checkbutton. */
	if (itemPtr->flags & (ITEM_RADIOBUTTON | ITEM_CHECKBUTTON)) {
	    if (itemPtr->flags & ITEM_RADIOBUTTON) {
		DrawRadioButton(itemPtr, drawable, x,
			  y + (h - itemPtr->leftIndHeight) / 2,
			  itemPtr->leftIndWidth, itemPtr->leftIndHeight);
	    } else if (itemPtr->flags & ITEM_CHECKBUTTON) {
		DrawCheckButton(itemPtr, drawable, x, 
			  y + (h - itemPtr->leftIndHeight) / 2,
			  itemPtr->leftIndWidth, itemPtr->leftIndHeight);
	    }		
	}
	x += itemPtr->indent;
	if (comboPtr->leftIndWidth > 0) {
	    x += comboPtr->leftIndWidth + ITEM_IPAD;
	}
	/* Icon. */
	if (itemPtr->icon != NULL) {
	    if ((Blt_IsPicture(IconImage(itemPtr->icon))) && 
		(itemPtr->flags & ITEM_DISABLED)) {
		Blt_Picture picture;
		Blt_Painter painter;
		
		painter = Blt_GetPainter(comboPtr->tkwin, 1.0);
		picture = Blt_GetPictureFromPictureImage(comboPtr->interp,
			IconImage(itemPtr->icon));
		picture = Blt_GreyscalePicture(picture);
		Blt_PaintPicture(painter, drawable, picture, 0, 0, 
			IconWidth(itemPtr->icon), IconHeight(itemPtr->icon), 
			x + (comboPtr->iconWidth - itemPtr->iconWidth) / 2, 
			y + (h - IconHeight(itemPtr->icon)) / 2, 0);
		Blt_FreePicture(picture);
	    } else {
		Tk_RedrawImage(IconImage(itemPtr->icon), 0, 0, 
			IconWidth(itemPtr->icon), IconHeight(itemPtr->icon), 
			drawable, 
			x + (comboPtr->iconWidth - itemPtr->iconWidth) / 2, 
			y + (h - IconHeight(itemPtr->icon)) / 2);
	    }
	    if (comboPtr->iconWidth > 0) {
		x += comboPtr->iconWidth + ITEM_IPAD;
	    }
	}
	/* Image or label. */
	if (itemPtr->image != NULL) {
	    Tk_RedrawImage(IconImage(itemPtr->image), 0, 0, 
		IconWidth(itemPtr->image), IconHeight(itemPtr->image), 
		drawable, x, y + (h - IconHeight(itemPtr->image)) / 2);
	} else if (itemPtr->label != emptyString) {
	    TextStyle ts;
	    XColor *fg;
	    
	    if (itemPtr->flags & ITEM_DISABLED) {
		fg = stylePtr->labelDisabledColor;
	    } else if (comboPtr->activePtr == itemPtr) {
		fg = stylePtr->labelActiveColor;
	    } else {
		fg = stylePtr->labelNormalColor;
	    }
	    Blt_Ts_InitStyle(ts);
	    Blt_Ts_SetFont(ts, stylePtr->labelFont);
	    Blt_Ts_SetForeground(ts, fg);
	    Blt_Ts_SetAnchor(ts, TK_ANCHOR_NW);
	    Blt_Ts_SetUnderline(ts, itemPtr->underline);
	    Blt_Ts_SetJustify(ts, TK_JUSTIFY_LEFT);
	    Blt_DrawText(comboPtr->tkwin, drawable, (char *)itemPtr->label, &ts,
		x, y + (h - itemPtr->labelHeight) / 2);
	}
	x = x0 + MAX(comboPtr->worldWidth, VPORTWIDTH(comboPtr)) - 2*ITEM_IPAD;
	/* Accelerator or submenu arrow. */
	if (itemPtr->flags & ITEM_CASCADE) {
	    XColor *color;

	    if (itemPtr->flags & ITEM_DISABLED) {
		color = stylePtr->labelDisabledColor;
	    } else if (comboPtr->activePtr == itemPtr) {
		color = stylePtr->labelActiveColor;
	    } else {
		color = stylePtr->labelNormalColor;
	    }
	    x -= ITEM_R_IND_WIDTH;
	    Blt_DrawArrow(comboPtr->display, drawable, color, x + ITEM_IPAD, y, 
		ITEM_R_IND_WIDTH, h, 1, ARROW_RIGHT);
	} else if (itemPtr->accel != NULL) {
	    TextStyle ts;
	    XColor *fg;
	    
	    if (itemPtr->flags & ITEM_DISABLED) {
		fg = stylePtr->accelDisabledColor;
	    } else if (comboPtr->activePtr == itemPtr) {
		fg = stylePtr->accelActiveColor;
	    } else {
		fg = stylePtr->accelNormalColor;
	    }
	    Blt_Ts_InitStyle(ts);
	    Blt_Ts_SetForeground(ts, fg);
	    Blt_Ts_SetFont(ts, stylePtr->accelFont);
	    Blt_Ts_SetAnchor(ts, TK_ANCHOR_NW);
	    Blt_Ts_SetJustify(ts, TK_JUSTIFY_LEFT);
	    x -= itemPtr->rightIndWidth;
	    Blt_DrawText(comboPtr->tkwin, drawable, (char *)itemPtr->accel, &ts,
		x, y + (h - itemPtr->rightIndHeight) / 2);
	}
    }
}

    
static void
DrawComboMenu(ComboMenu *comboPtr, Drawable drawable)
{
    /* Draw each visible item. */
    if (comboPtr->firstPtr != NULL) {
	Blt_ChainLink first, last, link;

	first = comboPtr->firstPtr->link;
	last = comboPtr->lastPtr->link;
	for (link = first; link != NULL; link = Blt_Chain_NextLink(link)) {
	    int x, y;
	    Item *itemPtr;

	    itemPtr = Blt_Chain_GetValue(link);
	    x = PIXMAPX(comboPtr, itemPtr->xWorld);
	    y = PIXMAPY(comboPtr, itemPtr->yWorld);
	    DrawItemBackground(itemPtr, drawable, x, y);
	    DrawItem(itemPtr, drawable, x, y);
	    if (link == last) {
		break;
	    }
	}
    }
    /* Manage the geometry of the scrollbars. */
    if (comboPtr->yScrollbarWidth > 0) {
	int x, y;
	int yScrollbarHeight;

	x = Tk_Width(comboPtr->tkwin) - comboPtr->borderWidth -
	    comboPtr->yScrollbarWidth;
	y = comboPtr->borderWidth;
	yScrollbarHeight = Tk_Height(comboPtr->tkwin) - 
	    comboPtr->xScrollbarHeight - 2 * comboPtr->borderWidth;
	if ((Tk_Width(comboPtr->yScrollbar) != comboPtr->yScrollbarWidth) ||
	    (Tk_Height(comboPtr->yScrollbar) != yScrollbarHeight) ||
	    (x != Tk_X(comboPtr->yScrollbar)) || 
	    (y != Tk_Y(comboPtr->yScrollbar))) {
	    Tk_MoveResizeWindow(comboPtr->yScrollbar, x, y, 
		comboPtr->yScrollbarWidth, yScrollbarHeight);
	}
	if (!Tk_IsMapped(comboPtr->yScrollbar)) {
	    Tk_MapWindow(comboPtr->yScrollbar);
	}
    } else if ((comboPtr->yScrollbar != NULL) &&
	       (Tk_IsMapped(comboPtr->yScrollbar))) {
	Tk_UnmapWindow(comboPtr->yScrollbar);
    }
    if (comboPtr->xScrollbarHeight > 0) {
	int x, y;
	int xScrollbarWidth;

	x = comboPtr->borderWidth;
	y = Tk_Height(comboPtr->tkwin) - comboPtr->xScrollbarHeight - 
	    comboPtr->borderWidth;
	xScrollbarWidth = Tk_Width(comboPtr->tkwin) - 
	    comboPtr->yScrollbarWidth - 2 * comboPtr->borderWidth;
	if ((Tk_Width(comboPtr->xScrollbar) != xScrollbarWidth) ||
	    (Tk_Height(comboPtr->xScrollbar) != comboPtr->xScrollbarHeight) ||
	    (x != Tk_X(comboPtr->xScrollbar)) || 
	    (y != Tk_Y(comboPtr->xScrollbar))) {
	    Tk_MoveResizeWindow(comboPtr->xScrollbar, x, y, xScrollbarWidth,
		comboPtr->xScrollbarHeight);
	}
	if (!Tk_IsMapped(comboPtr->xScrollbar)) {
	    Tk_MapWindow(comboPtr->xScrollbar);
	}
    } else if ((comboPtr->xScrollbar != NULL) && 
	       (Tk_IsMapped(comboPtr->xScrollbar))) {
	Tk_UnmapWindow(comboPtr->xScrollbar);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * DisplayItem --
 *
 *	This procedure is invoked to display an item in the combomenu widget.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Commands are output to X to display the item.
 *
 *---------------------------------------------------------------------------
 */
static void
DisplayItem(ClientData clientData)
{
    Item *itemPtr = clientData;
    int x, y, w, h, d, sy;
    Pixmap drawable;
    ComboMenu *comboPtr;

    /*
     * Create a pixmap the size of the item for double buffering.
     */
    comboPtr = itemPtr->comboPtr;
    h = itemPtr->height;
    w = VPORTWIDTH(comboPtr);
    drawable = Tk_GetPixmap(comboPtr->display, Tk_WindowId(comboPtr->tkwin),
	w, h, Tk_Depth(comboPtr->tkwin));
#ifdef WIN32
    assert(drawable != None);
#endif
    DrawItemBackground(itemPtr, drawable, -comboPtr->xOffset, 0);
    DrawItem(itemPtr, drawable, -comboPtr->xOffset, 0);
    x = PIXMAPX(comboPtr, itemPtr->xWorld) + comboPtr->borderWidth;
    y = PIXMAPY(comboPtr, itemPtr->yWorld) + comboPtr->borderWidth;
    sy = 0;
    d = comboPtr->borderWidth - y;
    if (d > 0) {
	h -= d;
	sy = d;
	y += d;
    }
    d = (y + h) - (Tk_Height(comboPtr->tkwin) - comboPtr->borderWidth);
    if (d > 0) {
	h -= d;
    }
    XCopyArea(comboPtr->display, drawable, Tk_WindowId(comboPtr->tkwin),
	comboPtr->defStyle.labelNormalGC, 0, sy, w, h, comboPtr->borderWidth,y);
    Tk_FreePixmap(comboPtr->display, drawable);
}

/*
 *---------------------------------------------------------------------------
 *
 * DisplayComboMenu --
 *
 *	This procedure is invoked to display a combomenu widget.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Commands are output to X to display the menu.
 *
 *---------------------------------------------------------------------------
 */
static void
DisplayComboMenu(ClientData clientData)
{
    ComboMenu *comboPtr = clientData;
    Pixmap drawable;
    int w, h;				/* Window width and height. */
    int screenWidth, screenHeight;

    comboPtr->flags &= ~REDRAW_PENDING;
    if (comboPtr->tkwin == NULL) {
	return;				/* Window destroyed (should not get
					 * here) */
    }
#ifdef notdef
    fprintf(stderr, "Calling DisplayComboMenu(%s) w=%d h=%d\n", 
	    Tk_PathName(comboPtr->tkwin), Tk_Width(comboPtr->tkwin),
	    Tk_Height(comboPtr->tkwin));
#endif
    if (comboPtr->flags & LAYOUT_PENDING) {
	ComputeComboGeometry(comboPtr);
    }
    if ((Tk_Width(comboPtr->tkwin) <= 1) || (Tk_Height(comboPtr->tkwin) <= 1)){
	/* Don't bother computing the layout until the window size is
	 * something reasonable. */
	return;
    }
    if (!Tk_IsMapped(comboPtr->tkwin)) {
	/* The menu's window isn't displayed, so don't bother drawing
	 * anything.  By getting this far, we've at least computed the
	 * coordinates of the combomenu's new layout.  */
	return;
    }
    if (comboPtr->flags & SCROLL_PENDING) {
	int vw, vh;			/* Viewport width and height. */
	/* 
	 * The view port has changed. The visible items need to be recomputed
	 * and the scrollbars updated.
	 */
	ComputeVisibleItems(comboPtr);
	vw = VPORTWIDTH(comboPtr);
	vh = VPORTHEIGHT(comboPtr);
	if ((comboPtr->xScrollCmdObjPtr != NULL) &&
	    (comboPtr->flags & SCROLLX)) {
	    Blt_UpdateScrollbar(comboPtr->interp, comboPtr->xScrollCmdObjPtr,
		comboPtr->xOffset, comboPtr->xOffset + vw, comboPtr->worldWidth);
	}
	if ((comboPtr->yScrollCmdObjPtr != NULL) && 
	    (comboPtr->flags & SCROLLY)) {
	    Blt_UpdateScrollbar(comboPtr->interp, comboPtr->yScrollCmdObjPtr,
		comboPtr->yOffset, comboPtr->yOffset+vh, comboPtr->worldHeight);
	}
	comboPtr->flags &= ~SCROLL_PENDING;
    }
    /*
     * Create a pixmap the size of the window for double buffering.
     */
    w = Tk_Width(comboPtr->tkwin) - 2 * comboPtr->borderWidth - 
	comboPtr->yScrollbarWidth;
    h = Tk_Height(comboPtr->tkwin) - 2 * comboPtr->borderWidth - 
	comboPtr->xScrollbarHeight;
    Blt_SizeOfScreen(comboPtr->tkwin, &screenWidth, &screenHeight);
    w = CLAMP(w, 1, screenWidth);
    h = CLAMP(h, 1, screenHeight);
    drawable = Tk_GetPixmap(comboPtr->display, Tk_WindowId(comboPtr->tkwin),
	w, h, Tk_Depth(comboPtr->tkwin));
#ifdef WIN32
    assert(drawable != None);
#endif
    if (comboPtr->activePtr == NULL) {
	ActivateItem(comboPtr, comboPtr->firstPtr);
    }
    /* 
     * Shadowed menu.  Request window size slightly bigger than menu.  Get
     * snapshot of background from root menu.
     */
    /* Background */
    Blt_FillBackgroundRectangle(comboPtr->tkwin, drawable, 
	comboPtr->defStyle.normalBg, 0, 0, w, h, 0, TK_RELIEF_FLAT);
    DrawComboMenu(comboPtr, drawable);
    XCopyArea(comboPtr->display, drawable, Tk_WindowId(comboPtr->tkwin),
	comboPtr->defStyle.labelNormalGC, 0, 0, w, h, 
	      comboPtr->borderWidth, comboPtr->borderWidth);
    Tk_FreePixmap(comboPtr->display, drawable);
    if ((comboPtr->xScrollbarHeight > 0) && (comboPtr->yScrollbarWidth > 0)) {
	/* Draw the empty corner. */
	Blt_FillBackgroundRectangle(comboPtr->tkwin, 
		Tk_WindowId(comboPtr->tkwin), comboPtr->defStyle.disabledBg, 
		w + comboPtr->borderWidth, h + comboPtr->borderWidth, 
		comboPtr->yScrollbarWidth, comboPtr->xScrollbarHeight,
		0, TK_RELIEF_FLAT);
    }
    Blt_DrawBackgroundRectangle(comboPtr->tkwin, Tk_WindowId(comboPtr->tkwin), 
	comboPtr->defStyle.normalBg, 0, 0, Tk_Width(comboPtr->tkwin), 
	Tk_Height(comboPtr->tkwin), comboPtr->borderWidth, comboPtr->relief);
}
