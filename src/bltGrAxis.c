
/*
 * bltGrAxis.c --
 *
 *	This module implements coordinate axes for the BLT graph widget.
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

#include "bltGraph.h"
#include "bltOp.h"
#include "bltGrElem.h"
#include <X11/Xutil.h>

#define MAXTICKS	10001

#define FCLAMP(x)	((((x) < 0.0) ? 0.0 : ((x) > 1.0) ? 1.0 : (x)))

/*
 * Round x in terms of units
 */
#define UROUND(x,u)		(Round((x)/(u))*(u))
#define UCEIL(x,u)		(ceil((x)/(u))*(u))
#define UFLOOR(x,u)		(floor((x)/(u))*(u))

#define NUMDIGITS		15	/* Specifies the number of digits of
					 * accuracy used when outputting axis
					 * tick labels. */
enum TickRange {
    AXIS_TIGHT, AXIS_LOOSE, AXIS_ALWAYS_LOOSE
};

#define AXIS_PAD_TITLE		2	/* Padding for axis title. */

/* Axis flags: */

#define AXIS_AUTO_MAJOR		(1<<16) /* Auto-generate major ticks. */
#define AXIS_AUTO_MINOR		(1<<17) /* Auto-generate minor ticks. */
#define AXIS_USE		(1<<18)	/* Axis is displayed on the screen via
					 * the "use" operation */
#define AXIS_GRID		(1<<19)
#define AXIS_GRID_MINOR		(1<<20)
#define AXIS_TICKS		(1<<21)
#define AXIS_TICKS_INTERIOR	(1<<22)
#define AXIS_CHECK_LIMITS	(1<<23)

#define HORIZMARGIN(m)	(!((m)->site & 0x1))	/* Even sites are horizontal */

typedef struct {
    int axis;				/* Length of the axis.  */
    int t1;			        /* Length of a major tick (in
					 * pixels). */
    int t2;			        /* Length of a minor tick (in
					 * pixels). */
    int label;				/* Distance from axis to tick label. */
} AxisInfo;

typedef struct {
    const char *name;
    ClassId classId;
    int margin, invertMargin;
} AxisName;

static AxisName axisNames[] = { 
    { "x",  CID_AXIS_X, MARGIN_BOTTOM, MARGIN_LEFT   },
    { "y",  CID_AXIS_Y, MARGIN_LEFT,   MARGIN_BOTTOM },
    { "x2", CID_AXIS_X, MARGIN_TOP,    MARGIN_RIGHT  },
    { "y2", CID_AXIS_Y, MARGIN_RIGHT,  MARGIN_TOP    }
} ;
static int nAxisNames = sizeof(axisNames) / sizeof(AxisName);

static Blt_OptionParseProc ObjToLimitProc;
static Blt_OptionPrintProc LimitToObjProc;
static Blt_CustomOption limitOption = {
    ObjToLimitProc, LimitToObjProc, NULL, (ClientData)0
};

static Blt_OptionFreeProc  FreeTicksProc;
static Blt_OptionParseProc ObjToTicksProc;
static Blt_OptionPrintProc TicksToObjProc;
static Blt_CustomOption majorTicksOption = {
    ObjToTicksProc, TicksToObjProc, FreeTicksProc, (ClientData)AXIS_AUTO_MAJOR,
};
static Blt_CustomOption minorTicksOption = {
    ObjToTicksProc, TicksToObjProc, FreeTicksProc, (ClientData)AXIS_AUTO_MINOR,
};
static Blt_OptionFreeProc  FreeAxisProc;
static Blt_OptionPrintProc AxisToObjProc;
static Blt_OptionParseProc ObjToAxisProc;
Blt_CustomOption bltXAxisOption = {
    ObjToAxisProc, AxisToObjProc, FreeAxisProc, (ClientData)CID_AXIS_X
};
Blt_CustomOption bltYAxisOption = {
    ObjToAxisProc, AxisToObjProc, FreeAxisProc, (ClientData)CID_AXIS_Y
};

static Blt_OptionFreeProc  FreeFormatProc;
static Blt_OptionParseProc ObjToFormatProc;
static Blt_OptionPrintProc FormatToObjProc;
static Blt_CustomOption formatOption = {
    ObjToFormatProc, FormatToObjProc, FreeFormatProc, (ClientData)0,
};
static Blt_OptionParseProc ObjToLooseProc;
static Blt_OptionPrintProc LooseToObjProc;
static Blt_CustomOption looseOption = {
    ObjToLooseProc, LooseToObjProc, NULL, (ClientData)0,
};

static Blt_OptionParseProc ObjToUseProc;
static Blt_OptionPrintProc UseToObjProc;
static Blt_CustomOption useOption = {
    ObjToUseProc, UseToObjProc, NULL, (ClientData)0
};

#define DEF_AXIS_ACTIVE_BACKGROUND	STD_ACTIVE_BACKGROUND
#define DEF_AXIS_ACTIVE_FOREGROUND	STD_ACTIVE_FOREGROUND
#define DEF_AXIS_ACTIVE_RELIEF		"flat"
#define DEF_AXIS_ANGLE			"0.0"
#define DEF_AXIS_BACKGROUND		(char *)NULL
#define DEF_AXIS_BORDERWIDTH		"0"
#define DEF_AXIS_CHECKLIMITS		"0"
#define DEF_AXIS_COMMAND		(char *)NULL
#define DEF_AXIS_DESCENDING		"no"
#define DEF_AXIS_FOREGROUND		RGB_BLACK
#define DEF_AXIS_GRID_BARCHART		"yes"
#define DEF_AXIS_GRID_COLOR		RGB_GREY64
#define DEF_AXIS_GRID_DASHES		"dot"
#define DEF_AXIS_GRID_GRAPH		"no"
#define DEF_AXIS_GRID_LINE_WIDTH	"0"
#define DEF_AXIS_GRID_MINOR		"yes"
#define DEF_AXIS_GRID_MINOR_COLOR	RGB_GREY64
#define DEF_AXIS_HIDE			"no"
#define DEF_AXIS_JUSTIFY		"center"
#define DEF_AXIS_LIMITS_FORMAT	        (char *)NULL
#define DEF_AXIS_LINE_WIDTH		"1"
#define DEF_AXIS_LOGSCALE		"no"
#define DEF_AXIS_LOOSE			"no"
#define DEF_AXIS_RANGE			"0.0"
#define DEF_AXIS_RELIEF			"flat"
#define DEF_AXIS_SCROLL_INCREMENT 	"10"
#define DEF_AXIS_SHIFTBY		"0.0"
#define DEF_AXIS_SHOWTICKS		"yes"
#define DEF_AXIS_STEP			"0.0"
#define DEF_AXIS_STEP			"0.0"
#define DEF_AXIS_SUBDIVISIONS		"2"
#define DEF_AXIS_TAGS			"all"
#define DEF_AXIS_TICKS			"0"
#define DEF_AXIS_TICKS_INTERIOR		"no"
#define DEF_AXIS_TICK_ANCHOR		"c"
#define DEF_AXIS_TICK_FONT		STD_FONT_NUMBERS
#define DEF_AXIS_TICK_LENGTH		"8"
#define DEF_AXIS_TICK_NUM		"10"
#define DEF_AXIS_TITLE_ALTERNATE	"0"
#define DEF_AXIS_TITLE_FG		RGB_BLACK
#define DEF_AXIS_TITLE_FONT		"{Sans Serif} 10 bold"
#define DEF_AXIS_X_STEP_BARCHART	"1.0"
#define DEF_AXIS_X_SUBDIVISIONS_BARCHART "0"

static Blt_ConfigSpec configSpecs[] =
{
    {BLT_CONFIG_BACKGROUND, "-activebackground", "activeBackground", 
	"ActiveBackground", DEF_AXIS_ACTIVE_BACKGROUND, 
	Blt_Offset(Axis, activeBg), ALL_GRAPHS | BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_COLOR, "-activeforeground", "activeForeground",
	"ActiveForeground", DEF_AXIS_ACTIVE_FOREGROUND,
	Blt_Offset(Axis, activeFgColor), ALL_GRAPHS}, 
    {BLT_CONFIG_RELIEF, "-activerelief", "activeRelief", "Relief",
	DEF_AXIS_ACTIVE_RELIEF, Blt_Offset(Axis, activeRelief),
	ALL_GRAPHS | BLT_CONFIG_DONT_SET_DEFAULT}, 
    {BLT_CONFIG_DOUBLE, "-autorange", "autoRange", "AutoRange",
	DEF_AXIS_RANGE, Blt_Offset(Axis, windowSize),
        ALL_GRAPHS | BLT_CONFIG_DONT_SET_DEFAULT}, 
    {BLT_CONFIG_BACKGROUND, "-background", "background", "Background",
	DEF_AXIS_BACKGROUND, Blt_Offset(Axis, normalBg),
	ALL_GRAPHS | BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_SYNONYM, "-bg", "background", (char *)NULL, (char *)NULL, 0, 0},
    {BLT_CONFIG_LIST, "-bindtags", "bindTags", "BindTags", DEF_AXIS_TAGS, 
	Blt_Offset(Axis, obj.tags), ALL_GRAPHS | BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_SYNONYM, "-bd", "borderWidth", (char *)NULL, (char *)NULL, 
	0, ALL_GRAPHS},
    {BLT_CONFIG_PIXELS_NNEG, "-borderwidth", "borderWidth", "BorderWidth",
	DEF_AXIS_BORDERWIDTH, Blt_Offset(Axis, borderWidth),
	ALL_GRAPHS | BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_BITMASK, "-checklimits", "checkLimits", "CheckLimits", 
	DEF_AXIS_CHECKLIMITS, Blt_Offset(Axis, flags), 
	ALL_GRAPHS | BLT_CONFIG_DONT_SET_DEFAULT,
	(Blt_CustomOption *)AXIS_CHECK_LIMITS},
    {BLT_CONFIG_COLOR, "-color", "color", "Color",
	DEF_AXIS_FOREGROUND, Blt_Offset(Axis, tickColor), ALL_GRAPHS},
    {BLT_CONFIG_STRING, "-command", "command", "Command",
	DEF_AXIS_COMMAND, Blt_Offset(Axis, formatCmd),
	BLT_CONFIG_NULL_OK | ALL_GRAPHS},
    {BLT_CONFIG_BOOLEAN, "-descending", "descending", "Descending",
	DEF_AXIS_DESCENDING, Blt_Offset(Axis, descending),
	ALL_GRAPHS | BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_SYNONYM, "-fg", "color", (char *)NULL, 
        (char *)NULL, 0, ALL_GRAPHS},
    {BLT_CONFIG_SYNONYM, "-foreground", "color", (char *)NULL, 
        (char *)NULL, 0, ALL_GRAPHS},
    {BLT_CONFIG_BITMASK, "-grid", "grid", "Grid", DEF_AXIS_GRID_BARCHART, 
	Blt_Offset(Axis, flags), BARCHART, (Blt_CustomOption *)AXIS_GRID},
    {BLT_CONFIG_BITMASK, "-grid", "grid", "Grid", DEF_AXIS_GRID_GRAPH, 
	Blt_Offset(Axis, flags), GRAPH | STRIPCHART, 
	(Blt_CustomOption *)AXIS_GRID},
    {BLT_CONFIG_COLOR, "-gridcolor", "gridColor", "GridColor", 
	DEF_AXIS_GRID_COLOR, Blt_Offset(Axis, major.color), ALL_GRAPHS},
    {BLT_CONFIG_DASHES, "-griddashes", "gridDashes", "GridDashes", 
	DEF_AXIS_GRID_DASHES, Blt_Offset(Axis, major.dashes), 
	BLT_CONFIG_NULL_OK | ALL_GRAPHS},
    {BLT_CONFIG_PIXELS_NNEG, "-gridlinewidth", "gridLineWidth", 
	"GridLineWidth", DEF_AXIS_GRID_LINE_WIDTH, 
	Blt_Offset(Axis, major.lineWidth), 
        BLT_CONFIG_DONT_SET_DEFAULT | ALL_GRAPHS},
    {BLT_CONFIG_BITMASK, "-gridminor", "gridMinor", "GridMinor", 
	DEF_AXIS_GRID_MINOR, Blt_Offset(Axis, flags), 
	BLT_CONFIG_DONT_SET_DEFAULT | ALL_GRAPHS, 
	(Blt_CustomOption *)AXIS_GRID_MINOR},
    {BLT_CONFIG_COLOR, "-gridminorcolor", "gridMinorColor", "GridColor", 
	DEF_AXIS_GRID_MINOR_COLOR, Blt_Offset(Axis, minor.color), ALL_GRAPHS},
    {BLT_CONFIG_DASHES, "-gridminordashes", "gridMinorDashes", "GridDashes", 
	DEF_AXIS_GRID_DASHES, Blt_Offset(Axis, minor.dashes), 
	BLT_CONFIG_NULL_OK | ALL_GRAPHS},
    {BLT_CONFIG_PIXELS_NNEG, "-gridminorlinewidth", "gridMinorLineWidth", 
	"GridLineWidth", DEF_AXIS_GRID_LINE_WIDTH, 
	Blt_Offset(Axis, minor.lineWidth), 
        BLT_CONFIG_DONT_SET_DEFAULT | ALL_GRAPHS},
    {BLT_CONFIG_BITMASK, "-hide", "hide", "Hide", DEF_AXIS_HIDE, 
	Blt_Offset(Axis, flags), ALL_GRAPHS | BLT_CONFIG_DONT_SET_DEFAULT, 
        (Blt_CustomOption *)HIDE},
    {BLT_CONFIG_JUSTIFY, "-justify", "justify", "Justify",
	DEF_AXIS_JUSTIFY, Blt_Offset(Axis, titleJustify),
	ALL_GRAPHS | BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_BOOLEAN, "-labeloffset", "labelOffset", "LabelOffset",
        (char *)NULL, Blt_Offset(Axis, labelOffset), ALL_GRAPHS}, 
    {BLT_CONFIG_COLOR, "-limitscolor", "limitsColor", "Color",
	DEF_AXIS_FOREGROUND, Blt_Offset(Axis, limitsTextStyle.color), 
	ALL_GRAPHS},
    {BLT_CONFIG_FONT, "-limitsfont", "limitsFont", "Font",
	DEF_AXIS_TICK_FONT, Blt_Offset(Axis, limitsTextStyle.font), ALL_GRAPHS},
    {BLT_CONFIG_CUSTOM, "-limitsformat", "limitsFormat", "LimitsFormat",
        (char *)NULL, Blt_Offset(Axis, limitsFormats),
	BLT_CONFIG_NULL_OK | ALL_GRAPHS, &formatOption},
    {BLT_CONFIG_PIXELS_NNEG, "-linewidth", "lineWidth", "LineWidth",
	DEF_AXIS_LINE_WIDTH, Blt_Offset(Axis, lineWidth),
	ALL_GRAPHS | BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_BOOLEAN, "-logscale", "logScale", "LogScale",
	DEF_AXIS_LOGSCALE, Blt_Offset(Axis, logScale),
	ALL_GRAPHS | BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_CUSTOM, "-loose", "loose", "Loose", DEF_AXIS_LOOSE, 0, 
	ALL_GRAPHS | BLT_CONFIG_DONT_SET_DEFAULT, &looseOption},
    {BLT_CONFIG_CUSTOM, "-majorticks", "majorTicks", "MajorTicks",
	(char *)NULL, Blt_Offset(Axis, t1Ptr),
	BLT_CONFIG_NULL_OK | ALL_GRAPHS, &majorTicksOption},
    {BLT_CONFIG_CUSTOM, "-max", "max", "Max", (char *)NULL, 
	Blt_Offset(Axis, reqMax), ALL_GRAPHS, &limitOption},
    {BLT_CONFIG_CUSTOM, "-min", "min", "Min", (char *)NULL, 
	Blt_Offset(Axis, reqMin), ALL_GRAPHS, &limitOption},
    {BLT_CONFIG_CUSTOM, "-minorticks", "minorTicks", "MinorTicks",
	(char *)NULL, Blt_Offset(Axis, t2Ptr), 
	BLT_CONFIG_NULL_OK | ALL_GRAPHS, &minorTicksOption},
    {BLT_CONFIG_RELIEF, "-relief", "relief", "Relief",
	DEF_AXIS_RELIEF, Blt_Offset(Axis, relief), 
        ALL_GRAPHS | BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_FLOAT, "-rotate", "rotate", "Rotate", DEF_AXIS_ANGLE, 
	Blt_Offset(Axis, tickAngle), ALL_GRAPHS | BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_OBJ, "-scrollcommand", "scrollCommand", "ScrollCommand",
	(char *)NULL, Blt_Offset(Axis, scrollCmdObjPtr),
	ALL_GRAPHS | BLT_CONFIG_NULL_OK},
    {BLT_CONFIG_PIXELS_POS, "-scrollincrement", "scrollIncrement", 
	"ScrollIncrement", DEF_AXIS_SCROLL_INCREMENT, 
	Blt_Offset(Axis, scrollUnits), ALL_GRAPHS|BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_CUSTOM, "-scrollmax", "scrollMax", "ScrollMax", (char *)NULL, 
	Blt_Offset(Axis, reqScrollMax),  ALL_GRAPHS, &limitOption},
    {BLT_CONFIG_CUSTOM, "-scrollmin", "scrollMin", "ScrollMin", (char *)NULL, 
	Blt_Offset(Axis, reqScrollMin), ALL_GRAPHS, &limitOption},
    {BLT_CONFIG_DOUBLE, "-shiftby", "shiftBy", "ShiftBy",
	DEF_AXIS_SHIFTBY, Blt_Offset(Axis, shiftBy),
	ALL_GRAPHS | BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_BITMASK, "-showticks", "showTicks", "ShowTicks",
	DEF_AXIS_SHOWTICKS, Blt_Offset(Axis, flags), 
	ALL_GRAPHS | BLT_CONFIG_DONT_SET_DEFAULT,
	(Blt_CustomOption *)AXIS_TICKS},
    {BLT_CONFIG_DOUBLE, "-stepsize", "stepSize", "StepSize",
	DEF_AXIS_STEP, Blt_Offset(Axis, reqStep),
	ALL_GRAPHS | BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_INT, "-subdivisions", "subdivisions", "Subdivisions",
	DEF_AXIS_SUBDIVISIONS, Blt_Offset(Axis, reqNumMinorTicks), ALL_GRAPHS},
    {BLT_CONFIG_ANCHOR, "-tickanchor", "tickAnchor", "Anchor",
	DEF_AXIS_TICK_ANCHOR, Blt_Offset(Axis, reqTickAnchor), ALL_GRAPHS},
    {BLT_CONFIG_FONT, "-tickfont", "tickFont", "Font",
	DEF_AXIS_TICK_FONT, Blt_Offset(Axis, tickFont), ALL_GRAPHS},
    {BLT_CONFIG_PIXELS_NNEG, "-ticklength", "tickLength", "TickLength",
	DEF_AXIS_TICK_LENGTH, Blt_Offset(Axis, tickLength), ALL_GRAPHS},
    {BLT_CONFIG_BITMASK, "-tickinterior", "tickInterior", "TickInterior",
	DEF_AXIS_TICKS_INTERIOR, Blt_Offset(Axis, flags), ALL_GRAPHS, 
	(Blt_CustomOption *)AXIS_TICKS_INTERIOR},
    {BLT_CONFIG_INT, "-tickdefault", "tickDefault", "TickDefault",
	DEF_AXIS_TICK_NUM, Blt_Offset(Axis, reqNumMajorTicks),
	ALL_GRAPHS | BLT_CONFIG_DONT_SET_DEFAULT},
    {BLT_CONFIG_STRING, "-title", "title", "Title",
	(char *)NULL, Blt_Offset(Axis, title),
	BLT_CONFIG_DONT_SET_DEFAULT | BLT_CONFIG_NULL_OK | ALL_GRAPHS},
    {BLT_CONFIG_BOOLEAN, "-titlealternate", "titleAlternate", "TitleAlternate",
	DEF_AXIS_TITLE_ALTERNATE, Blt_Offset(Axis, titleAlternate),
	BLT_CONFIG_DONT_SET_DEFAULT | ALL_GRAPHS},
    {BLT_CONFIG_COLOR, "-titlecolor", "titleColor", "Color", 
	DEF_AXIS_FOREGROUND, Blt_Offset(Axis, titleColor), 	
	ALL_GRAPHS},
    {BLT_CONFIG_FONT, "-titlefont", "titleFont", "Font", DEF_AXIS_TITLE_FONT, 
	Blt_Offset(Axis, titleFont), ALL_GRAPHS},
    {BLT_CONFIG_CUSTOM, "-use", "use", "Use", (char *)NULL, 0, ALL_GRAPHS, 
	&useOption},
    {BLT_CONFIG_END, NULL, NULL, NULL, NULL, 0, 0}
};

/* Forward declarations */
static void DestroyAxis(Axis *axisPtr);
static Tcl_FreeProc FreeAxis;
static int GetAxisByClass(Tcl_Interp *interp, Graph *graphPtr, Tcl_Obj *objPtr,
	ClassId classId, Axis **axisPtrPtr);

static int lastMargin;
typedef int (GraphAxisProc)(Tcl_Interp *interp, Axis *axisPtr, int objc, 
	Tcl_Obj *const *objv);
typedef int (GraphVirtualAxisProc)(Tcl_Interp *interp, Graph *graphPtr, 
	int objc, Tcl_Obj *const *objv);

INLINE static double
Clamp(double x) 
{
    return (x < 0.0) ? 0.0 : (x > 1.0) ? 1.0 : x;
}

INLINE static int
Round(double x)
{
    return (int) (x + ((x < 0.0) ? -0.5 : 0.5));
}

static void
SetAxisRange(AxisRange *rangePtr, double min, double max)
{
    rangePtr->min = min;
    rangePtr->max = max;
    rangePtr->range = max - min;
    if (FABS(rangePtr->range) < DBL_EPSILON) {
	rangePtr->range = 1.0;
    }
    rangePtr->scale = 1.0 / rangePtr->range;
}

/*
 *---------------------------------------------------------------------------
 *
 * InRange --
 *
 *	Determines if a value lies within a given range.
 *
 *	The value is normalized and compared against the interval [0..1],
 *	where 0.0 is the minimum and 1.0 is the maximum.  DBL_EPSILON is the
 *	smallest number that can be represented on the host machine, such that
 *	(1.0 + epsilon) != 1.0.
 *
 *	Please note, *max* can't equal *min*.
 *
 * Results:
 *	If the value is within the interval [min..max], 1 is returned; 0
 *	otherwise.
 *
 *---------------------------------------------------------------------------
 */
INLINE static int
InRange(double x, AxisRange *rangePtr)
{
    if (rangePtr->range < DBL_EPSILON) {
	return (FABS(rangePtr->max - x) >= DBL_EPSILON);
    } else {
	double norm;

	norm = (x - rangePtr->min) * rangePtr->scale;
	return ((norm >= -DBL_EPSILON) && ((norm - 1.0) < DBL_EPSILON));
    }
}

INLINE static int
AxisIsHorizontal(Axis *axisPtr)
{
    Graph *graphPtr = axisPtr->obj.graphPtr;

    return ((axisPtr->obj.classId == CID_AXIS_Y) == graphPtr->inverted);
}


static void
ReleaseAxis(Axis *axisPtr)
{
    if (axisPtr != NULL) {
	axisPtr->refCount--;
	assert(axisPtr->refCount >= 0);
	if (axisPtr->refCount == 0) {
	    axisPtr->flags |= DELETE_PENDING;
	    Tcl_EventuallyFree(axisPtr, FreeAxis);
	}
    }
}

/*
 *-----------------------------------------------------------------------------
 * Custom option parse and print procedures
 *-----------------------------------------------------------------------------
 */

/*ARGSUSED*/
static void
FreeAxisProc(
    ClientData clientData,		/* Not used. */
    Display *display,			/* Not used. */
    char *widgRec,
    int offset)
{
    Axis **axisPtrPtr = (Axis **)(widgRec + offset);

    if (*axisPtrPtr != NULL) {
	ReleaseAxis(*axisPtrPtr);
	*axisPtrPtr = NULL;
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * ObjToAxisProc --
 *
 *	Converts the name of an axis to a pointer to its axis structure.
 *
 * Results:
 *	The return value is a standard TCL result.  The axis flags are written
 *	into the widget record.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ObjToAxisProc(
    ClientData clientData,		/* Class identifier of the type of 
					 * axis we are looking for. */
    Tcl_Interp *interp,			/* Interpreter to send results back
					 * to. */
    Tk_Window tkwin,			/* Used to look up pointer to graph. */
    Tcl_Obj *objPtr,			/* String representing new value. */
    char *widgRec,			/* Pointer to structure record. */
    int offset,				/* Offset to field in structure */
    int flags)	
{
    ClassId classId = (ClassId)clientData;
    Axis **axisPtrPtr = (Axis **)(widgRec + offset);
    Axis *axisPtr;
    Graph *graphPtr;

    if (flags & BLT_CONFIG_NULL_OK) {
	const char *string;

	string  = Tcl_GetString(objPtr);
	if (string[0] == '\0') {
	    ReleaseAxis(*axisPtrPtr);
	    *axisPtrPtr = NULL;
	    return TCL_OK;
	}
    }
    graphPtr = Blt_GetGraphFromWindowData(tkwin);
    assert(graphPtr);
    if (GetAxisByClass(interp, graphPtr, objPtr, classId, &axisPtr) 
	!= TCL_OK) {
	return TCL_ERROR;
    }
    ReleaseAxis(*axisPtrPtr);
    *axisPtrPtr = axisPtr;
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * AxisToObjProc --
 *
 *	Convert the window coordinates into a string.
 *
 * Results:
 *	The string representing the coordinate position is returned.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static Tcl_Obj *
AxisToObjProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,			/* Not used. */
    Tk_Window tkwin,			/* Not used. */
    char *widgRec,			/* Pointer to structure record .*/
    int offset,				/* Offset to field in structure */
    int flags)				/* Not used. */
{
    Axis *axisPtr = *(Axis **)(widgRec + offset);
    const char *name;

    name = (axisPtr == NULL) ? "" : axisPtr->obj.name;
    return Tcl_NewStringObj(name, -1);
}

/*ARGSUSED*/
static void
FreeFormatProc(
    ClientData clientData,		/* Not used. */
    Display *display,			/* Not used. */
    char *widgRec,
    int offset)				/* Not used. */
{
    Axis *axisPtr = (Axis *)(widgRec);

    if (axisPtr->limitsFormats != NULL) {
	Blt_Free(axisPtr->limitsFormats);
	axisPtr->limitsFormats = NULL;
    }
    axisPtr->nFormats = 0;
}


/*
 *---------------------------------------------------------------------------
 *
 * ObjToFormatProc --
 *
 *	Convert the name of virtual axis to an pointer.
 *
 * Results:
 *	The return value is a standard TCL result.  The axis flags are written
 *	into the widget record.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ObjToFormatProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,			/* Interpreter to send results back
					 * to. */
    Tk_Window tkwin,			/* Not used. */
    Tcl_Obj *objPtr,			/* String representing new value. */
    char *widgRec,			/* Pointer to structure record. */
    int offset,				/* Not used. */
    int flags)				/* Not used. */
{
    Axis *axisPtr = (Axis *)(widgRec);
    const char **argv;
    int argc;

    if (Tcl_SplitList(interp, Tcl_GetString(objPtr), &argc, &argv) != TCL_OK) {
	return TCL_ERROR;
    }
    if (argc > 2) {
	Tcl_AppendResult(interp, "too many elements in limits format list \"",
		Tcl_GetString(objPtr), "\"", (char *)NULL);
	Blt_Free(argv);
	return TCL_ERROR;
    }
    if (axisPtr->limitsFormats != NULL) {
	Blt_Free(axisPtr->limitsFormats);
    }
    axisPtr->limitsFormats = argv;
    axisPtr->nFormats = argc;
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * FormatToObjProc --
 *
 *	Convert the window coordinates into a string.
 *
 * Results:
 *	The string representing the coordinate position is returned.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static Tcl_Obj *
FormatToObjProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,			/* Not used. */
    Tk_Window tkwin,			/* Not used. */
    char *widgRec,			/* Widget record */
    int offset,				/* Not used. */
    int flags)				/* Not used. */
{
    Axis *axisPtr = (Axis *)(widgRec);
    Tcl_Obj *objPtr;

    if (axisPtr->nFormats == 0) {
	objPtr = Tcl_NewStringObj("", -1);
    } else {
	const char *string;

	string = Tcl_Merge(axisPtr->nFormats, axisPtr->limitsFormats); 
	objPtr = Tcl_NewStringObj(string, -1);
	Blt_Free(string);
    }
    return objPtr;
}

/*
 *---------------------------------------------------------------------------
 *
 * ObjToLimitProc --
 *
 *	Convert the string representation of an axis limit into its numeric
 *	form.
 *
 * Results:
 *	The return value is a standard TCL result.  The symbol type is written
 *	into the widget record.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ObjToLimitProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,			/* Interpreter to send results back
					 * to */
    Tk_Window tkwin,			/* Not used. */
    Tcl_Obj *objPtr,			/* String representing new value. */
    char *widgRec,			/* Pointer to structure record. */
    int offset,				/* Offset to field in structure */
    int flags)				/* Not used. */
{
    double *limitPtr = (double *)(widgRec + offset);
    const char *string;

    string = Tcl_GetString(objPtr);
    if (string[0] == '\0') {
	*limitPtr = Blt_NaN();
    } else if (Blt_ExprDoubleFromObj(interp, objPtr, limitPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * LimitToObjProc --
 *
 *	Convert the floating point axis limits into a string.
 *
 * Results:
 *	The string representation of the limits is returned.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static Tcl_Obj *
LimitToObjProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,			/* Not used. */
    Tk_Window tkwin,			/* Not used. */
    char *widgRec,			/* */
    int offset,				/* Offset to field in structure */
    int flags)				/* Not used. */
{
    double limit = *(double *)(widgRec + offset);
    Tcl_Obj *objPtr;

    if (DEFINED(limit)) {
	objPtr = Tcl_NewDoubleObj(limit);
    } else {
	objPtr = Tcl_NewStringObj("", -1);
    }
    return objPtr;
}

/*
 *---------------------------------------------------------------------------
 *
 * ObjToUseProc --
 *
 *	Convert the string representation of the margin to use into its 
 *	numeric form.
 *
 * Results:
 *	The return value is a standard TCL result.  The use type is written
 *	into the widget record.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ObjToUseProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,		        /* Interpreter to send results back
					 * to */
    Tk_Window tkwin,			/* Not used. */
    Tcl_Obj *objPtr,			/* String representing new value. */
    char *widgRec,			/* Pointer to structure record. */
    int offset,				/* Offset to field in structure */
    int flags)				/* Not used. */
{
    Axis *axisPtr = (Axis *)(widgRec);
    AxisName *p, *pend;
    Blt_Chain chain;
    Graph *graphPtr;
    const char *string;

    graphPtr = axisPtr->obj.graphPtr;
    if (axisPtr->refCount == 0) {
	/* Clear the axis class if it's not currently used by an element.*/
	Blt_GraphSetObjectClass(&axisPtr->obj, CID_NONE);
    }
    /* Remove the axis from the margin's use list and clear its use flag. */
    if (axisPtr->link != NULL) {
	Blt_Chain_UnlinkLink(axisPtr->chain, axisPtr->link);
    }
    axisPtr->flags &= ~AXIS_USE;

    string = Tcl_GetString(objPtr);
    if ((string == NULL) || (string[0] == '\0')) {
	goto done;
    }
    for (p = axisNames, pend = axisNames + nAxisNames; p < pend; p++) {
	if (strcmp(p->name, string) == 0) {
	    break;			/* Found the axis name. */
	}
    }
    if (p == pend) {
	Tcl_AppendResult(interp, "unknown axis type \"", string, "\": "
			 "should be x, y, x1, y2, or \"\".", (char *)NULL);
	return TCL_ERROR;
    }
    /* Check the axis class. Can't use the axis if it's already being used as
     * another type.  */
    if (axisPtr->obj.classId == CID_NONE) {
	Blt_GraphSetObjectClass(&axisPtr->obj, p->classId);
    } else if (axisPtr->obj.classId != p->classId) {
	Tcl_AppendResult(interp, "wrong type axis \"", 
		axisPtr->obj.name, "\": can't use ", 
		axisPtr->obj.className, " type axis.", (char *)NULL); 
	return TCL_ERROR;
    }
    chain = (graphPtr->inverted) ? graphPtr->margins[p->invertMargin].axes :
	graphPtr->margins[p->margin].axes;
    if (axisPtr->link != NULL) {
	/* Move the axis from the old margin's "use" list to the new. */
	Blt_Chain_AppendLink(chain, axisPtr->link);
    } else {
	axisPtr->link = Blt_Chain_Append(chain, axisPtr);
    }
    axisPtr->chain = chain;
    axisPtr->flags |= AXIS_USE;
 done:
    graphPtr->flags |= (GET_AXIS_GEOMETRY | LAYOUT_NEEDED | RESET_AXES);
    /* When any axis changes, we need to layout the entire graph.  */
    graphPtr->flags |= (MAP_WORLD | REDRAW_WORLD);
    Blt_EventuallyRedrawGraph(graphPtr);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * UseToObjProc --
 *
 *	Convert the floating point axis limits into a string.
 *
 * Results:
 *	The string representation of the limits is returned.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static Tcl_Obj *
UseToObjProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,			/* Not used. */
    Tk_Window tkwin,			/* Not used. */
    char *widgRec,			/* */
    int offset,				/* Offset to field in structure */
    int flags)				/* Not used. */
{
    Axis *axisPtr = (Axis *)(widgRec);
    return Tcl_NewStringObj(axisPtr->obj.className, -1);
}

/*ARGSUSED*/
static void
FreeTicksProc(
    ClientData clientData,		/* Either AXIS_AUTO_MAJOR or
					 * AXIS_AUTO_MINOR. */
    Display *display,			/* Not used. */
    char *widgRec,
    int offset)
{
    Axis *axisPtr = (Axis *)widgRec;
    Ticks **ticksPtrPtr = (Ticks **) (widgRec + offset);
    unsigned long mask = (unsigned long)clientData;

    axisPtr->flags |= mask;
    if (*ticksPtrPtr != NULL) {
	Blt_Free(*ticksPtrPtr);
    }
    *ticksPtrPtr = NULL;
}

/*
 *---------------------------------------------------------------------------
 *
 * ObjToTicksProc --
 *
 *
 * Results:
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ObjToTicksProc(
    ClientData clientData,		/* Either AXIS_AUTO_MAJOR or
					 * AXIS_AUTO_MINOR. */
    Tcl_Interp *interp,		        /* Interpreter to send results back
					 * to */
    Tk_Window tkwin,			/* Not used. */
    Tcl_Obj *objPtr,			/* String representing new value. */
    char *widgRec,			/* Pointer to structure record. */
    int offset,				/* Offset to field in structure */
    int flags)				/* Not used. */
{
    Axis *axisPtr = (Axis *)widgRec;
    Tcl_Obj **objv;
    Ticks **ticksPtrPtr = (Ticks **) (widgRec + offset);
    Ticks *ticksPtr;
    int objc;
    unsigned long mask = (unsigned long)clientData;

    if (Tcl_ListObjGetElements(interp, objPtr, &objc, &objv) != TCL_OK) {
	return TCL_ERROR;
    }
    axisPtr->flags |= mask;
    ticksPtr = NULL;
    if (objc > 0) {
	int i;

	ticksPtr = Blt_AssertMalloc(sizeof(Ticks) + (objc * sizeof(double)));
	for (i = 0; i < objc; i++) {
	    double value;

	    if (Blt_ExprDoubleFromObj(interp, objv[i], &value) != TCL_OK) {
		Blt_Free(ticksPtr);
		return TCL_ERROR;
	    }
	    ticksPtr->values[i] = value;
	}
    }
    ticksPtr->nTicks = objc;
    FreeTicksProc(clientData, Tk_Display(tkwin), widgRec, offset);
    axisPtr->flags &= ~mask;
    *ticksPtrPtr = ticksPtr;
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * TicksToObjProc --
 *
 *	Convert array of tick coordinates to a list.
 *
 * Results:
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static Tcl_Obj *
TicksToObjProc(
    ClientData clientData,		/* Either AXIS_AUTO_MAJOR or
					 * AXIS_AUTO_MINOR. */
    Tcl_Interp *interp,
    Tk_Window tkwin,			/* Not used. */
    char *widgRec,			/* */
    int offset,				/* Offset to field in structure */
    int flags)				/* Not used. */
{
    Ticks *ticksPtr = *(Ticks **) (widgRec + offset);
    Tcl_Obj *listObjPtr;

    listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
    if (ticksPtr != NULL) {
	unsigned int i;

	for (i = 0; i < ticksPtr->nTicks; i++) {
	    Tcl_Obj *objPtr;

	    objPtr = Tcl_NewDoubleObj(ticksPtr->values[i]);
	    Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	}
    }
    return listObjPtr;
}

/*
 *---------------------------------------------------------------------------
 *
 * ObjToLooseProc --
 *
 *	Convert a string to one of three values.
 *		0 - false, no, off
 *		1 - true, yes, on
 *		2 - always
 * Results:
 *	If the string is successfully converted, TCL_OK is returned.
 *	Otherwise, TCL_ERROR is returned and an error message is left in
 *	interpreter's result field.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ObjToLooseProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,		        /* Interpreter to send results back
					 * to */
    Tk_Window tkwin,			/* Not used. */
    Tcl_Obj *objPtr,			/* String representing new value. */
    char *widgRec,			/* Pointer to structure record. */
    int offset,				/* Not used. */
    int flags)				/* Not used. */
{
    Axis *axisPtr = (Axis *)(widgRec);
    Tcl_Obj **objv;
    int i;
    int objc;
    int values[2];

    if (Tcl_ListObjGetElements(interp, objPtr, &objc, &objv) != TCL_OK) {
	return TCL_ERROR;
    }
    if ((objc < 1) || (objc > 2)) {
	Tcl_AppendResult(interp, "wrong # elements in loose value \"",
	    Tcl_GetString(objPtr), "\"", (char *)NULL);
	return TCL_ERROR;
    }
    for (i = 0; i < objc; i++) {
	const char *string;

	string = Tcl_GetString(objv[i]);
	if ((string[0] == 'a') && (strcmp(string, "always") == 0)) {
	    values[i] = AXIS_LOOSE;
	} else {
	    int bool;

	    if (Tcl_GetBooleanFromObj(interp, objv[i], &bool) != TCL_OK) {
		return TCL_ERROR;
	    }
	    values[i] = bool;
	}
    }
    axisPtr->looseMin = axisPtr->looseMax = values[0];
    if (objc > 1) {
	axisPtr->looseMax = values[1];
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * LooseToObjProc --
 *
 * Results:
 *	The string representation of the auto boolean is returned.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static Tcl_Obj *
LooseToObjProc(
    ClientData clientData,		/* Not used. */
    Tcl_Interp *interp,
    Tk_Window tkwin,			/* Not used. */
    char *widgRec,			/* Widget record */
    int offset,				/* Not used. */
    int flags)				/* Not used. */
{
    Axis *axisPtr = (Axis *)widgRec;
    Tcl_Obj *listObjPtr;

    listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
    if (axisPtr->looseMin == AXIS_TIGHT) {
	Tcl_ListObjAppendElement(interp, listObjPtr, Tcl_NewBooleanObj(FALSE));
    } else if (axisPtr->looseMin == AXIS_LOOSE) {
	Tcl_ListObjAppendElement(interp, listObjPtr, Tcl_NewBooleanObj(TRUE));
    } else if (axisPtr->looseMin == AXIS_ALWAYS_LOOSE) {
	Tcl_ListObjAppendElement(interp, listObjPtr, 
		Tcl_NewStringObj("always", 6));
    }
    if (axisPtr->looseMin != axisPtr->looseMax) {
	if (axisPtr->looseMax == AXIS_TIGHT) {
	    Tcl_ListObjAppendElement(interp, listObjPtr, 
		Tcl_NewBooleanObj(FALSE));
	} else if (axisPtr->looseMax == AXIS_LOOSE) {
	    Tcl_ListObjAppendElement(interp, listObjPtr, 
		Tcl_NewBooleanObj(TRUE));
	} else if (axisPtr->looseMax == AXIS_ALWAYS_LOOSE) {
	    Tcl_ListObjAppendElement(interp, listObjPtr, 
		Tcl_NewStringObj("always", 6));
	}
    }
    return listObjPtr;
}

static void
FreeLabels(Blt_Chain chain)
{
    Blt_ChainLink link;

    for (link = Blt_Chain_FirstLink(chain); link != NULL; 
	 link = Blt_Chain_NextLink(link)) {
	TickLabel *labelPtr;

	labelPtr = Blt_Chain_GetValue(link);
	Blt_Free(labelPtr);
    }
    Blt_Chain_Reset(chain);
}

/*
 *---------------------------------------------------------------------------
 *
 * MakeLabel --
 *
 *	Converts a floating point tick value to a string to be used as its
 *	label.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Returns a new label in the string character buffer.  The formatted
 *	tick label will be displayed on the graph.
 *
 * -------------------------------------------------------------------------- 
 */
static TickLabel *
MakeLabel(Axis *axisPtr, double value)
{
#define TICK_LABEL_SIZE		200
    char string[TICK_LABEL_SIZE + 1];
    TickLabel *labelPtr;

    /* Generate a default tick label based upon the tick value.  */
    if (axisPtr->logScale) {
	sprintf_s(string, TICK_LABEL_SIZE, "1E%d", ROUND(value));
    } else {
	sprintf_s(string, TICK_LABEL_SIZE, "%.*g", NUMDIGITS, value);
    }

    if (axisPtr->formatCmd != NULL) {
	Graph *graphPtr;
	Tcl_Interp *interp;
	Tk_Window tkwin;
	
	graphPtr = axisPtr->obj.graphPtr;
	interp = graphPtr->interp;
	tkwin = graphPtr->tkwin;
	/*
	 * A TCL proc was designated to format tick labels. Append the path
	 * name of the widget and the default tick label as arguments when
	 * invoking it. Copy and save the new label from interp->result.
	 */
	Tcl_ResetResult(interp);
	if (Tcl_VarEval(interp, axisPtr->formatCmd, " ", Tk_PathName(tkwin),
		" ", string, (char *)NULL) != TCL_OK) {
	    Tcl_BackgroundError(interp);
	} else {
	    /* 
	     * The proc could return a string of any length, so arbitrarily
	     * limit it to what will fit in the return string.
	     */
	    strncpy(string, Tcl_GetStringResult(interp), TICK_LABEL_SIZE);
	    string[TICK_LABEL_SIZE] = '\0';
	    
	    Tcl_ResetResult(interp); /* Clear the interpreter's result. */
	}
    }
    labelPtr = Blt_AssertMalloc(sizeof(TickLabel) + strlen(string));
    strcpy(labelPtr->string, string);
    labelPtr->anchorPos.x = labelPtr->anchorPos.y = DBL_MAX;
    return labelPtr;
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_InvHMap --
 *
 *	Maps the given screen coordinate back to a graph coordinate.  Called
 *	by the graph locater routine.
 *
 * Results:
 *	Returns the graph coordinate value at the given window
 *	y-coordinate.
 *
 *---------------------------------------------------------------------------
 */
double
Blt_InvHMap(Axis *axisPtr, double x)
{
    double value;

    x = (double)(x - axisPtr->screenMin) * axisPtr->screenScale;
    if (axisPtr->descending) {
	x = 1.0 - x;
    }
    value = (x * axisPtr->axisRange.range) + axisPtr->axisRange.min;
    if (axisPtr->logScale) {
	value = EXP10(value);
    }
    return value;
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_InvVMap --
 *
 *	Maps the given screen y-coordinate back to the graph coordinate
 *	value. Called by the graph locater routine.
 *
 * Results:
 *	Returns the graph coordinate value for the given screen
 *	coordinate.
 *
 *---------------------------------------------------------------------------
 */
double
Blt_InvVMap(Axis *axisPtr, double y) /* Screen coordinate */
{
    double value;

    y = (double)(y - axisPtr->screenMin) * axisPtr->screenScale;
    if (axisPtr->descending) {
	y = 1.0 - y;
    }
    value = ((1.0 - y) * axisPtr->axisRange.range) + axisPtr->axisRange.min;
    if (axisPtr->logScale) {
	value = EXP10(value);
    }
    return value;
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_HMap --
 *
 *	Map the given graph coordinate value to its axis, returning a window
 *	position.
 *
 * Results:
 *	Returns a double precision number representing the window coordinate
 *	position on the given axis.
 *
 *---------------------------------------------------------------------------
 */
double
Blt_HMap(Axis *axisPtr, double x)
{
    if ((axisPtr->logScale) && (x != 0.0)) {
	x = log10(FABS(x));
    }
    /* Map graph coordinate to normalized coordinates [0..1] */
    x = (x - axisPtr->axisRange.min) * axisPtr->axisRange.scale;
    if (axisPtr->descending) {
	x = 1.0 - x;
    }
    return (x * axisPtr->screenRange + axisPtr->screenMin);
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_VMap --
 *
 *	Map the given graph coordinate value to its axis, returning a window
 *	position.
 *
 * Results:
 *	Returns a double precision number representing the window coordinate
 *	position on the given axis.
 *
 *---------------------------------------------------------------------------
 */
double
Blt_VMap(Axis *axisPtr, double y)
{
    if ((axisPtr->logScale) && (y != 0.0)) {
	y = log10(FABS(y));
    }
    /* Map graph coordinate to normalized coordinates [0..1] */
    y = (y - axisPtr->axisRange.min) * axisPtr->axisRange.scale;
    if (axisPtr->descending) {
	y = 1.0 - y;
    }
    return ((1.0 - y) * axisPtr->screenRange + axisPtr->screenMin);
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_Map2D --
 *
 *	Maps the given graph x,y coordinate values to a window position.
 *
 * Results:
 *	Returns a XPoint structure containing the window coordinates of
 *	the given graph x,y coordinate.
 *
 *---------------------------------------------------------------------------
 */
Point2d
Blt_Map2D(
    Graph *graphPtr,
    double x, double y,			/* Graph x and y coordinates */
    Axis2d *axesPtr)			/* Specifies which axes to use */
{
    Point2d point;

    if (graphPtr->inverted) {
	point.x = Blt_HMap(axesPtr->y, y);
	point.y = Blt_VMap(axesPtr->x, x);
    } else {
	point.x = Blt_HMap(axesPtr->x, x);
	point.y = Blt_VMap(axesPtr->y, y);
    }
    return point;
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_InvMap2D --
 *
 *	Maps the given window x,y coordinates to graph values.
 *
 * Results:
 *	Returns a structure containing the graph coordinates of the given
 *	window x,y coordinate.
 *
 *---------------------------------------------------------------------------
 */
Point2d
Blt_InvMap2D(
    Graph *graphPtr,
    double x, double y,			/* Window x and y coordinates */
    Axis2d *axesPtr)			/* Specifies which axes to use */
{
    Point2d point;

    if (graphPtr->inverted) {
	point.x = Blt_InvVMap(axesPtr->x, y);
	point.y = Blt_InvHMap(axesPtr->y, x);
    } else {
	point.x = Blt_InvHMap(axesPtr->x, x);
	point.y = Blt_InvVMap(axesPtr->y, y);
    }
    return point;
}


static void
GetDataLimits(Axis *axisPtr, double min, double max)
{
    if (axisPtr->valueRange.min > min) {
	axisPtr->valueRange.min = min;
    }
    if (axisPtr->valueRange.max < max) {
	axisPtr->valueRange.max = max;
    }
}

static void
FixAxisRange(Axis *axisPtr)
{
    double min, max;

    /*
     * When auto-scaling, the axis limits are the bounds of the element data.
     * If no data exists, set arbitrary limits (wrt to log/linear scale).
     */
    min = axisPtr->valueRange.min;
    max = axisPtr->valueRange.max;

    /* Check the requested axis limits. Can't allow -min to be greater
     * than -max, or have undefined log scale limits.  */
    if (((DEFINED(axisPtr->reqMin)) && (DEFINED(axisPtr->reqMax))) &&
	(axisPtr->reqMin >= axisPtr->reqMax)) {
	axisPtr->reqMin = axisPtr->reqMax = Blt_NaN();
    }
    if (axisPtr->logScale) {
	if ((DEFINED(axisPtr->reqMin)) && (axisPtr->reqMin <= 0.0)) {
	    axisPtr->reqMin = Blt_NaN();
	}
	if ((DEFINED(axisPtr->reqMax)) && (axisPtr->reqMax <= 0.0)) {
	    axisPtr->reqMax = Blt_NaN();
	}
    }

    if (min == DBL_MAX) {
	if (DEFINED(axisPtr->reqMin)) {
	    min = axisPtr->reqMin;
	} else {
	    min = (axisPtr->logScale) ? 0.001 : 0.0;
	}
    }
    if (max == -DBL_MAX) {
	if (DEFINED(axisPtr->reqMax)) {
	    max = axisPtr->reqMax;
	} else {
	    max = 1.0;
	}
    }
    if (min >= max) {
	/*
	 * There is no range of data (i.e. min is not less than max), so
	 * manufacture one.
	 */
	if (min == 0.0) {
	    min = 0.0, max = 1.0;
	} else {
	    max = min + (FABS(min) * 0.1);
	}
    }
    SetAxisRange(&axisPtr->valueRange, min, max);

    /*   
     * The axis limits are either the current data range or overridden by the
     * values selected by the user with the -min or -max options.
     */
    axisPtr->min = min;
    axisPtr->max = max;
    if (DEFINED(axisPtr->reqMin)) {
	axisPtr->min = axisPtr->reqMin;
    }
    if (DEFINED(axisPtr->reqMax)) { 
	axisPtr->max = axisPtr->reqMax;
    }
    if (axisPtr->max < axisPtr->min) {
	/*   
	 * If the limits still don't make sense, it's because one limit
	 * configuration option (-min or -max) was set and the other default
	 * (based upon the data) is too small or large.  Remedy this by making
	 * up a new min or max from the user-defined limit.
	 */
	if (!DEFINED(axisPtr->reqMin)) {
	    axisPtr->min = axisPtr->max - (FABS(axisPtr->max) * 0.1);
	}
	if (!DEFINED(axisPtr->reqMax)) {
	    axisPtr->max = axisPtr->min + (FABS(axisPtr->max) * 0.1);
	}
    }
    /* 
     * If a window size is defined, handle auto ranging by shifting the axis
     * limits.
     */
    if ((axisPtr->windowSize > 0.0) && 
	(!DEFINED(axisPtr->reqMin)) && (!DEFINED(axisPtr->reqMax))) {
	if (axisPtr->shiftBy < 0.0) {
	    axisPtr->shiftBy = 0.0;
	}
	max = axisPtr->min + axisPtr->windowSize;
	if (axisPtr->max >= max) {
	    if (axisPtr->shiftBy > 0.0) {
		max = UCEIL(axisPtr->max, axisPtr->shiftBy);
	    }
	    axisPtr->min = max - axisPtr->windowSize;
	}
	axisPtr->max = max;
    }
    if ((axisPtr->max != axisPtr->prevMax) || 
	(axisPtr->min != axisPtr->prevMin)) {
	/* Indicate if the axis limits have changed */
	axisPtr->flags |= DIRTY;
	/* and save the previous minimum and maximum values */
	axisPtr->prevMin = axisPtr->min;
	axisPtr->prevMax = axisPtr->max;
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * NiceNum --
 *
 *	Reference: Paul Heckbert, "Nice Numbers for Graph Labels",
 *		   Graphics Gems, pp 61-63.  
 *
 *	Finds a "nice" number approximately equal to x.
 *
 *---------------------------------------------------------------------------
 */
static double
NiceNum(
    double x,
    int round)				/* If non-zero, round. Otherwise take
					 * ceiling of value. */
{
    double expt;			/* Exponent of x */
    double frac;			/* Fractional part of x */
    double nice;			/* Nice, rounded fraction */

    expt = floor(log10(x));
    frac = x / EXP10(expt);		/* between 1 and 10 */
    if (round) {
	if (frac < 1.5) {
	    nice = 1.0;
	} else if (frac < 3.0) {
	    nice = 2.0;
	} else if (frac < 7.0) {
	    nice = 5.0;
	} else {
	    nice = 10.0;
	}
    } else {
	if (frac <= 1.0) {
	    nice = 1.0;
	} else if (frac <= 2.0) {
	    nice = 2.0;
	} else if (frac <= 5.0) {
	    nice = 5.0;
	} else {
	    nice = 10.0;
	}
    }
    return nice * EXP10(expt);
}

static Ticks *
GenerateTicks(TickSweep *sweepPtr)
{
    Ticks *ticksPtr;

    ticksPtr = Blt_AssertMalloc(sizeof(Ticks) + 
				(sweepPtr->nSteps * sizeof(double)));
    ticksPtr->nTicks = 0;

    if (sweepPtr->step == 0.0) { 
	/* Hack: A zero step indicates to use log values. */
	int i;
	/* Precomputed log10 values [1..10] */
	static double logTable[] = {
	    0.0, 
	    0.301029995663981, 
	    0.477121254719662, 
	    0.602059991327962, 
	    0.698970004336019, 
	    0.778151250383644, 
	    0.845098040014257,
	    0.903089986991944, 
	    0.954242509439325, 
	    1.0
	};
	for (i = 0; i < sweepPtr->nSteps; i++) {
	    ticksPtr->values[i] = logTable[i];
	}
    } else {
	double value;
	int i;
    
	value = sweepPtr->initial;	/* Start from smallest axis tick */
	for (i = 0; i < sweepPtr->nSteps; i++) {
	    value = UROUND(value, sweepPtr->step);
	    ticksPtr->values[i] = value;
	    value += sweepPtr->step;
	}
    }
    ticksPtr->nTicks = sweepPtr->nSteps;
    return ticksPtr;
}

/*
 *---------------------------------------------------------------------------
 *
 * LogScaleAxis --
 *
 * 	Determine the range and units of a log scaled axis.
 *
 * 	Unless the axis limits are specified, the axis is scaled
 * 	automatically, where the smallest and largest major ticks encompass
 * 	the range of actual data values.  When an axis limit is specified,
 * 	that value represents the smallest(min)/largest(max) value in the
 * 	displayed range of values.
 *
 * 	Both manual and automatic scaling are affected by the step used.  By
 * 	default, the step is the largest power of ten to divide the range in
 * 	more than one piece.
 *
 *	Automatic scaling:
 *	Find the smallest number of units which contain the range of values.
 *	The minimum and maximum major tick values will be represent the
 *	range of values for the axis. This greatest number of major ticks
 *	possible is 10.
 *
 * 	Manual scaling:
 *   	Make the minimum and maximum data values the represent the range of
 *   	the values for the axis.  The minimum and maximum major ticks will be
 *   	inclusive of this range.  This provides the largest area for plotting
 *   	and the expected results when the axis min and max values have be set
 *   	by the user (.e.g zooming).  The maximum number of major ticks is 20.
 *
 *   	For log scale, there's the possibility that the minimum and
 *   	maximum data values are the same magnitude.  To represent the
 *   	points properly, at least one full decade should be shown.
 *   	However, if you zoom a log scale plot, the results should be
 *   	predictable. Therefore, in that case, show only minor ticks.
 *   	Lastly, there should be an appropriate way to handle numbers
 *   	<=0.
 *
 *          maxY
 *            |    units = magnitude (of least significant digit)
 *            |    high  = largest unit tick < max axis value
 *      high _|    low   = smallest unit tick > min axis value
 *            |
 *            |    range = high - low
 *            |    # ticks = greatest factor of range/units
 *           _|
 *        U   |
 *        n   |
 *        i   |
 *        t  _|
 *            |
 *            |
 *            |
 *       low _|
 *            |
 *            |_minX________________maxX__
 *            |   |       |      |       |
 *     minY  low                        high
 *           minY
 *
 *
 * 	numTicks = Number of ticks
 * 	min = Minimum value of axis
 * 	max = Maximum value of axis
 * 	range    = Range of values (max - min)
 *
 * 	If the number of decades is greater than ten, it is assumed
 *	that the full set of log-style ticks can't be drawn properly.
 *
 * Results:
 *	None
 *
 * -------------------------------------------------------------------------- */
static void
LogScaleAxis(Axis *axisPtr, double min, double max)
{
    double range;
    double tickMin, tickMax;
    double majorStep, minorStep;
    int nMajor, nMinor;

    nMajor = nMinor = 0;
    /* Suppress compiler warnings. */
    majorStep = minorStep = 0.0;
    tickMin = tickMax = Blt_NaN();
    if (min < max) {
	min = (min != 0.0) ? log10(FABS(min)) : 0.0;
	max = (max != 0.0) ? log10(FABS(max)) : 1.0;

	tickMin = floor(min);
	tickMax = ceil(max);
	range = tickMax - tickMin;
	
	if (range > 10) {
	    /* There are too many decades to display a major tick at every
	     * decade.  Instead, treat the axis as a linear scale.  */
	    range = NiceNum(range, 0);
	    majorStep = NiceNum(range / axisPtr->reqNumMajorTicks, 1);
	    tickMin = UFLOOR(tickMin, majorStep);
	    tickMax = UCEIL(tickMax, majorStep);
	    nMajor = (int)((tickMax - tickMin) / majorStep) + 1;
	    minorStep = EXP10(floor(log10(majorStep)));
	    if (minorStep == majorStep) {
		nMinor = 4, minorStep = 0.2;
	    } else {
		nMinor = Round(majorStep / minorStep) - 1;
	    }
	} else {
	    if (tickMin == tickMax) {
		tickMax++;
	    }
	    majorStep = 1.0;
	    nMajor = (int)(tickMax - tickMin + 1); /* FIXME: Check this. */
	    
	    minorStep = 0.0;		/* This is a special hack to pass
					 * information to the GenerateTicks
					 * routine. An interval of 0.0 tells 1)
					 * this is a minor sweep and 2) the axis
					 * is log scale. */
	    nMinor = 10;
	}
	if ((axisPtr->looseMin == AXIS_TIGHT) || 
	    ((axisPtr->looseMin == AXIS_LOOSE) && 
	     (DEFINED(axisPtr->reqMin)))) {
	    tickMin = min;
	    nMajor++;
	}
	if ((axisPtr->looseMax == AXIS_TIGHT) || 
	    ((axisPtr->looseMax == AXIS_LOOSE) &&
	     (DEFINED(axisPtr->reqMax)))) {
	    tickMax = max;
	}
    }
    axisPtr->majorSweep.step = majorStep;
    axisPtr->majorSweep.initial = floor(tickMin);
    axisPtr->majorSweep.nSteps = nMajor;
    axisPtr->minorSweep.initial = axisPtr->minorSweep.step = minorStep;
    axisPtr->minorSweep.nSteps = nMinor;

    SetAxisRange(&axisPtr->axisRange, tickMin, tickMax);
}

/*
 *---------------------------------------------------------------------------
 *
 * LinearScaleAxis --
 *
 * 	Determine the units of a linear scaled axis.
 *
 *	The axis limits are either the range of the data values mapped
 *	to the axis (autoscaled), or the values specified by the -min
 *	and -max options (manual).
 *
 *	If autoscaled, the smallest and largest major ticks will
 *	encompass the range of data values.  If the -loose option is
 *	selected, the next outer ticks are choosen.  If tight, the
 *	ticks are at or inside of the data limits are used.
 *
 * 	If manually set, the ticks are at or inside the data limits
 * 	are used.  This makes sense for zooming.  You want the
 * 	selected range to represent the next limit, not something a
 * 	bit bigger.
 *
 *	Note: I added an "always" value to the -loose option to force
 *	      the manually selected axes to be loose. It's probably
 *	      not a good idea.
 *
 *          maxY
 *            |    units = magnitude (of least significant digit)
 *            |    high  = largest unit tick < max axis value
 *      high _|    low   = smallest unit tick > min axis value
 *            |
 *            |    range = high - low
 *            |    # ticks = greatest factor of range/units
 *           _|
 *        U   |
 *        n   |
 *        i   |
 *        t  _|
 *            |
 *            |
 *            |
 *       low _|
 *            |
 *            |_minX________________maxX__
 *            |   |       |      |       |
 *     minY  low                        high
 *           minY
 *
 * 	numTicks = Number of ticks
 * 	min = Minimum value of axis
 * 	max = Maximum value of axis
 * 	range    = Range of values (max - min)
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The axis tick information is set.  The actual tick values will
 *	be generated later.
 *
 *---------------------------------------------------------------------------
 */
static void
LinearScaleAxis(Axis *axisPtr, double min, double max)
{
    double step;
    double tickMin, tickMax;
    double axisMin, axisMax;
    unsigned int nTicks;

    nTicks = 0;
    step = 1.0;
    /* Suppress compiler warning. */
    axisMin = axisMax = tickMin = tickMax = Blt_NaN();
    if (min < max) {
	double range;

	range = max - min;
	/* Calculate the major tick stepping. */
	if (axisPtr->reqStep > 0.0) {
	    /* An interval was designated by the user.  Keep scaling it until
	     * it fits comfortably within the current range of the axis.  */
	    step = axisPtr->reqStep;
	    while ((2 * step) >= range) {
		step *= 0.5;
	    }
	} else {
	    range = NiceNum(range, 0);
	    step = NiceNum(range / axisPtr->reqNumMajorTicks, 1);
	}
	
	/* Find the outer tick values. Add 0.0 to prevent getting -0.0. */
	axisMin = tickMin = floor(min / step) * step + 0.0;
	axisMax = tickMax = ceil(max / step) * step + 0.0;
	
	nTicks = Round((tickMax - tickMin) / step) + 1;
    } 
    axisPtr->majorSweep.step = step;
    axisPtr->majorSweep.initial = tickMin;
    axisPtr->majorSweep.nSteps = nTicks;

    /*
     * The limits of the axis are either the range of the data ("tight") or at
     * the next outer tick interval ("loose").  The looseness or tightness has
     * to do with how the axis fits the range of data values.  This option is
     * overridden when the user sets an axis limit (by either -min or -max
     * option).  The axis limit is always at the selected limit (otherwise we
     * assume that user would have picked a different number).
     */
    if ((axisPtr->looseMin == AXIS_TIGHT) || 
	((axisPtr->looseMin == AXIS_LOOSE) &&
	 (DEFINED(axisPtr->reqMin)))) {
	axisMin = min;
    }
    if ((axisPtr->looseMax == AXIS_TIGHT) || 
	((axisPtr->looseMax == AXIS_LOOSE) &&
	 (DEFINED(axisPtr->reqMax)))) {
	axisMax = max;
    }
    SetAxisRange(&axisPtr->axisRange, axisMin, axisMax);

    /* Now calculate the minor tick step and number. */

    if ((axisPtr->reqNumMinorTicks > 0) && (axisPtr->flags & AXIS_AUTO_MAJOR)) {
	nTicks = axisPtr->reqNumMinorTicks - 1;
	step = 1.0 / (nTicks + 1);
    } else {
	nTicks = 0;			/* No minor ticks. */
	step = 0.5;			/* Don't set the minor tick interval to
					 * 0.0. It makes the GenerateTicks
					 * routine * create minor log-scale tick
					 * marks.  */
    }
    axisPtr->minorSweep.initial = axisPtr->minorSweep.step = step;
    axisPtr->minorSweep.nSteps = nTicks;
}


static void
SweepTicks(Axis *axisPtr)
{
    if (axisPtr->flags & AXIS_AUTO_MAJOR) {
	if (axisPtr->t1Ptr != NULL) {
	    Blt_Free(axisPtr->t1Ptr);
	}
	axisPtr->t1Ptr = GenerateTicks(&axisPtr->majorSweep);
    }
    if (axisPtr->flags & AXIS_AUTO_MINOR) {
	if (axisPtr->t2Ptr != NULL) {
	    Blt_Free(axisPtr->t2Ptr);
	}
	axisPtr->t2Ptr = GenerateTicks(&axisPtr->minorSweep);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_ResetAxes --
 *
 * Results:
 *	None.
 *
 *---------------------------------------------------------------------------
 */
void
Blt_ResetAxes(Graph *graphPtr)
{
    Blt_ChainLink link;
    Blt_HashEntry *hPtr;
    Blt_HashSearch cursor;

    /* FIXME: This should be called whenever the display list of
     *	      elements change. Maybe yet another flag INIT_STACKS to
     *	      indicate that the element display list has changed.
     *	      Needs to be done before the axis limits are set.
     */
    Blt_InitFreqTable(graphPtr);
    if ((graphPtr->mode == MODE_STACKED) && (graphPtr->nStacks > 0)) {
	Blt_ComputeStacks(graphPtr);
    }
    /*
     * Step 1:  Reset all axes. Initialize the data limits of the axis to
     *		impossible values.
     */
    for (hPtr = Blt_FirstHashEntry(&graphPtr->axes.table, &cursor);
	hPtr != NULL; hPtr = Blt_NextHashEntry(&cursor)) {
	Axis *axisPtr;

	axisPtr = Blt_GetHashValue(hPtr);
	axisPtr->min = axisPtr->valueRange.min = DBL_MAX;
	axisPtr->max = axisPtr->valueRange.max = -DBL_MAX;
    }

    /*
     * Step 2:  For each element that's to be displayed, get the smallest
     *		and largest data values mapped to each X and Y-axis.  This
     *		will be the axis limits if the user doesn't override them 
     *		with -min and -max options.
     */
    for (link = Blt_Chain_FirstLink(graphPtr->elements.displayList);
	 link != NULL; link = Blt_Chain_NextLink(link)) {
	Element *elemPtr;
	Region2d exts;

	elemPtr = Blt_Chain_GetValue(link);
	(*elemPtr->procsPtr->extentsProc) (elemPtr, &exts);
	GetDataLimits(elemPtr->axes.x, exts.left, exts.right);
	GetDataLimits(elemPtr->axes.y, exts.top, exts.bottom);
    }
    /*
     * Step 3:  Now that we know the range of data values for each axis,
     *		set axis limits and compute a sweep to generate tick values.
     */
    for (hPtr = Blt_FirstHashEntry(&graphPtr->axes.table, &cursor);
	 hPtr != NULL; hPtr = Blt_NextHashEntry(&cursor)) {
	Axis *axisPtr;
	double min, max;

	axisPtr = Blt_GetHashValue(hPtr);
	FixAxisRange(axisPtr);

	/* Calculate min/max tick (major/minor) layouts */
	min = axisPtr->min;
	max = axisPtr->max;
	if ((DEFINED(axisPtr->scrollMin)) && (min < axisPtr->scrollMin)) {
	    min = axisPtr->scrollMin;
	}
	if ((DEFINED(axisPtr->scrollMax)) && (max > axisPtr->scrollMax)) {
	    max = axisPtr->scrollMax;
	}
	if (axisPtr->logScale) {
	    LogScaleAxis(axisPtr, min, max);
	} else {
	    LinearScaleAxis(axisPtr, min, max);
	}

	if ((axisPtr->flags & (DIRTY|AXIS_USE)) == (DIRTY|AXIS_USE)) {
	    graphPtr->flags |= REDRAW_BACKING_STORE;
	}
    }

    graphPtr->flags &= ~RESET_AXES;

    /*
     * When any axis changes, we need to layout the entire graph.
     */
    graphPtr->flags |= (GET_AXIS_GEOMETRY | LAYOUT_NEEDED | MAP_ALL | 
			REDRAW_WORLD);
}

/*
 *---------------------------------------------------------------------------
 *
 * ResetTextStyles --
 *
 *	Configures axis attributes (font, line width, label, etc) and allocates
 *	a new (possibly shared) graphics context.  Line cap style is projecting.
 *	This is for the problem of when a tick sits directly at the end point of
 *	the axis.
 *
 * Results:
 *	The return value is a standard TCL result.
 *
 * Side Effects:
 *	Axis resources are allocated (GC, font). Axis layout is deferred until
 *	the height and width of the window are known.
 *
 *---------------------------------------------------------------------------
 */
static void
ResetTextStyles(Axis *axisPtr)
{
    Graph *graphPtr = axisPtr->obj.graphPtr;
    GC newGC;
    XGCValues gcValues;
    unsigned long gcMask;

    Blt_Ts_ResetStyle(graphPtr->tkwin, &axisPtr->limitsTextStyle);

    gcMask = (GCForeground | GCLineWidth | GCCapStyle);
    gcValues.foreground = axisPtr->tickColor->pixel;
    gcValues.font = Blt_FontId(axisPtr->tickFont);
    gcValues.line_width = LineWidth(axisPtr->lineWidth);
    gcValues.cap_style = CapProjecting;

    newGC = Tk_GetGC(graphPtr->tkwin, gcMask, &gcValues);
    if (axisPtr->tickGC != NULL) {
	Tk_FreeGC(graphPtr->display, axisPtr->tickGC);
    }
    axisPtr->tickGC = newGC;

    /* Assuming settings from above GC */
    gcValues.foreground = axisPtr->activeFgColor->pixel;
    newGC = Tk_GetGC(graphPtr->tkwin, gcMask, &gcValues);
    if (axisPtr->activeTickGC != NULL) {
	Tk_FreeGC(graphPtr->display, axisPtr->activeTickGC);
    }
    axisPtr->activeTickGC = newGC;

    gcValues.background = gcValues.foreground = axisPtr->major.color->pixel;
    gcValues.line_width = LineWidth(axisPtr->major.lineWidth);
    gcMask = (GCForeground | GCBackground | GCLineWidth);
    if (LineIsDashed(axisPtr->major.dashes)) {
	gcValues.line_style = LineOnOffDash;
	gcMask |= GCLineStyle;
    }
    newGC = Blt_GetPrivateGC(graphPtr->tkwin, gcMask, &gcValues);
    if (LineIsDashed(axisPtr->major.dashes)) {
	Blt_SetDashes(graphPtr->display, newGC, &axisPtr->major.dashes);
    }
    if (axisPtr->major.gc != NULL) {
	Blt_FreePrivateGC(graphPtr->display, axisPtr->major.gc);
    }
    axisPtr->major.gc = newGC;

    gcValues.background = gcValues.foreground = axisPtr->minor.color->pixel;
    gcValues.line_width = LineWidth(axisPtr->minor.lineWidth);
    gcMask = (GCForeground | GCBackground | GCLineWidth);
    if (LineIsDashed(axisPtr->minor.dashes)) {
	gcValues.line_style = LineOnOffDash;
	gcMask |= GCLineStyle;
    }
    newGC = Blt_GetPrivateGC(graphPtr->tkwin, gcMask, &gcValues);
    if (LineIsDashed(axisPtr->minor.dashes)) {
	Blt_SetDashes(graphPtr->display, newGC, &axisPtr->minor.dashes);
    }
    if (axisPtr->minor.gc != NULL) {
	Blt_FreePrivateGC(graphPtr->display, axisPtr->minor.gc);
    }
    axisPtr->minor.gc = newGC;
}

/*
 *---------------------------------------------------------------------------
 *
 * DestroyAxis --
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Resources (font, color, gc, labels, etc.) associated with the axis are
 *	deallocated.
 *
 *---------------------------------------------------------------------------
 */
static void
DestroyAxis(Axis *axisPtr)
{
    Graph *graphPtr = axisPtr->obj.graphPtr;
    int flags;

    flags = Blt_GraphType(graphPtr);
    Blt_FreeOptions(configSpecs, (char *)axisPtr, graphPtr->display, flags);
    if (graphPtr->bindTable != NULL) {
	Blt_DeleteBindings(graphPtr->bindTable, axisPtr);
    }
    if (axisPtr->link != NULL) {
	Blt_Chain_DeleteLink(axisPtr->chain, axisPtr->link);
    }
    if (axisPtr->obj.name != NULL) {
	Blt_Free(axisPtr->obj.name);
    }
    if (axisPtr->hashPtr != NULL) {
	Blt_DeleteHashEntry(&graphPtr->axes.table, axisPtr->hashPtr);
    }
    Blt_Ts_FreeStyle(graphPtr->display, &axisPtr->limitsTextStyle);

    if (axisPtr->tickGC != NULL) {
	Tk_FreeGC(graphPtr->display, axisPtr->tickGC);
    }
    if (axisPtr->activeTickGC != NULL) {
	Tk_FreeGC(graphPtr->display, axisPtr->activeTickGC);
    }
    if (axisPtr->major.gc != NULL) {
	Blt_FreePrivateGC(graphPtr->display, axisPtr->major.gc);
    }
    if (axisPtr->minor.gc != NULL) {
	Blt_FreePrivateGC(graphPtr->display, axisPtr->minor.gc);
    }
    FreeLabels(axisPtr->tickLabels);
    Blt_Chain_Destroy(axisPtr->tickLabels);
    if (axisPtr->segments != NULL) {
	Blt_Free(axisPtr->segments);
    }
    Blt_Free(axisPtr);
}

static void
FreeAxis(DestroyData data)
{
    Axis *axisPtr = (Axis *)data;
    DestroyAxis(axisPtr);
}

static double titleAngle[4] =		/* Rotation for each axis title */
{
    0.0, 90.0, 0.0, 270.0
};

/*
 *---------------------------------------------------------------------------
 *
 * AxisOffsets --
 *
 *	Determines the sites of the axis, major and minor ticks, and title of
 *	the axis.
 *
 * Results:
 *	None.
 *
 *---------------------------------------------------------------------------
 */
static void
AxisOffsets(
    Axis *axisPtr,
    int margin,
    int offset,
    AxisInfo *infoPtr)
{
    Graph *graphPtr = axisPtr->obj.graphPtr;
    Margin *marginPtr;
    int pad;				/* Offset of axis from interior
					 * region. This includes a possible
					 * border and the axis line width. */
    int axisline;
    int t1, t2, labelOffset;
    int inset, mark;
    int x, y;
    float fangle;

    axisPtr->titleAngle = titleAngle[margin];
    marginPtr = graphPtr->margins + margin;

    axisline = t1 = t2 = 0;
    labelOffset = AXIS_PAD_TITLE;
    if (axisPtr->lineWidth > 0) {
	if (axisPtr->flags & AXIS_TICKS) {
	    t1 = axisPtr->tickLength;
	    t2 = (t1 * 10) / 15;
	}
	labelOffset = t1 + AXIS_PAD_TITLE + axisPtr->lineWidth;
    }
    /* Adjust offset for the interior border width and the line width */

    pad = 1;
    if (graphPtr->plotBorderWidth > 0) {
	pad += graphPtr->plotBorderWidth + 1;
    }
    pad = 0;				/* FIXME: test */
    /*
     * Pre-calculate the x-coordinate positions of the axis, tick labels, and
     * the individual major and minor ticks.
     */
    inset = pad + axisPtr->lineWidth / 2;
    switch (margin) {
    case MARGIN_TOP:
	mark = graphPtr->top - offset - pad;
	axisline = mark - axisPtr->lineWidth / 2;
	axisPtr->tickAnchor = TK_ANCHOR_S;
	axisPtr->left = axisPtr->screenMin - inset - 2;
	axisPtr->right = axisPtr->screenMin + axisPtr->screenRange + inset - 1;
	if (graphPtr->stackAxes) {
	    axisPtr->top = mark - marginPtr->axesOffset;
	} else {
	    axisPtr->top = mark - axisPtr->height;
	}
	axisPtr->bottom = mark;
	if (axisPtr->titleAlternate) {
	    x = graphPtr->right + AXIS_PAD_TITLE;
	    y = mark - (axisPtr->height  / 2);
	    axisPtr->titleAnchor = TK_ANCHOR_W;
	} else {
	    x = (axisPtr->right + axisPtr->left) / 2;
	    if (graphPtr->stackAxes) {
		y = mark - marginPtr->axesOffset + AXIS_PAD_TITLE;
	    } else {
		y = mark - axisPtr->height + AXIS_PAD_TITLE;
	    }
	    axisPtr->titleAnchor = TK_ANCHOR_N;
	}
	axisPtr->titlePos.x = x;
	axisPtr->titlePos.y = y;
	break;

    case MARGIN_BOTTOM:
	/*
	 *  ----------- bottom + plot borderwidth
	 *      mark --------------------------------------------
	 *          ===================== axisline (linewidth)
	 *                   tick
	 *		    title
	 */
	mark = graphPtr->bottom + pad + offset;
	axisline = mark + axisPtr->lineWidth / 2;
	fangle = FMOD(axisPtr->tickAngle, 90.0);
	if (fangle == 0.0) {
	    axisPtr->tickAnchor = TK_ANCHOR_N;
	} else {
	    int quadrant;

	    quadrant = (int)(axisPtr->tickAngle / 90.0);
	    if ((quadrant == 0) || (quadrant == 2)) {
		axisPtr->tickAnchor = TK_ANCHOR_NE;
	    } else {
		axisPtr->tickAnchor = TK_ANCHOR_NW;
	    }
	}
	axisPtr->left = axisPtr->screenMin - inset - 2;
	axisPtr->right = axisPtr->screenMin + axisPtr->screenRange + inset - 1;
	axisPtr->top = axisline + labelOffset - t1;
	if (graphPtr->stackAxes) {
	    axisPtr->bottom = mark + marginPtr->axesOffset - 1;
	} else {
	    axisPtr->bottom = mark + axisPtr->height - 1;
	}
	if (axisPtr->titleAlternate) {
	    x = graphPtr->right + AXIS_PAD_TITLE;
	    y = mark + (axisPtr->height / 2);
	    axisPtr->titleAnchor = TK_ANCHOR_W; 
	} else {
	    x = (axisPtr->right + axisPtr->left) / 2;
	    if (graphPtr->stackAxes) {
		y = mark + marginPtr->axesOffset - AXIS_PAD_TITLE;
	    } else {
		y = mark + axisPtr->height - AXIS_PAD_TITLE;
	    }
	    axisPtr->titleAnchor = TK_ANCHOR_S; 
	}
	axisPtr->titlePos.x = x;
	axisPtr->titlePos.y = y;
	break;

    case MARGIN_LEFT:
	/*
	 *                    mark
	 *                  |  : 
	 *                  |  :      
	 *                  |  : 
	 *                  |  :
	 *                  |  : 
	 *     axisline
	 */
	mark = graphPtr->left - pad - offset;
	axisline = mark - axisPtr->lineWidth;
	axisPtr->tickAnchor = TK_ANCHOR_E;
	if (graphPtr->stackAxes) {
	    axisPtr->left = mark - marginPtr->axesOffset;
	} else {
	    axisPtr->left = mark - axisPtr->width;
	}
	axisPtr->right = mark - 3;
	axisPtr->top = axisPtr->screenMin - inset - 2;
	axisPtr->bottom = axisPtr->screenMin + axisPtr->screenRange + inset - 1;
	if (axisPtr->titleAlternate) {
	    x = mark - (axisPtr->width / 2);
	    y = graphPtr->top - AXIS_PAD_TITLE;
	    axisPtr->titleAnchor = TK_ANCHOR_SW; 
	} else {
	    if (graphPtr->stackAxes) {
		x = mark - marginPtr->axesOffset;
	    } else {
		x = mark - axisPtr->width + AXIS_PAD_TITLE;
	    }
	    y = (axisPtr->bottom + axisPtr->top) / 2;
	    axisPtr->titleAnchor = TK_ANCHOR_W; 
	} 
	axisPtr->titlePos.x = x;
	axisPtr->titlePos.y = y;
	break;

    case MARGIN_RIGHT:
	mark = graphPtr->right + offset + pad;
	axisline = mark + axisPtr->lineWidth / 2;
	axisPtr->tickAnchor = TK_ANCHOR_W;
	axisPtr->left = mark;
	if (graphPtr->stackAxes) {
	    axisPtr->right = mark + marginPtr->axesOffset - 1;
	} else {
	    axisPtr->right = mark + axisPtr->width - 1;
	}
	axisPtr->top = axisPtr->screenMin - inset - 2;
	axisPtr->bottom = axisPtr->screenMin + axisPtr->screenRange + inset -1;
	if (axisPtr->titleAlternate) {
	    x = mark + (axisPtr->width / 2);
	    y = graphPtr->top - AXIS_PAD_TITLE;
	    axisPtr->titleAnchor = TK_ANCHOR_SE; 
	} else {
	    if (graphPtr->stackAxes) {
		x = mark + marginPtr->axesOffset - AXIS_PAD_TITLE;
	    } else {
		x = mark + axisPtr->width - AXIS_PAD_TITLE;
	    }
	    y = (axisPtr->bottom + axisPtr->top) / 2;
	    axisPtr->titleAnchor = TK_ANCHOR_E;
	}
	axisPtr->titlePos.x = x;
	axisPtr->titlePos.y = y;
	break;

    case MARGIN_NONE:
	axisline = 0;
	break;
    }
    if ((margin == MARGIN_LEFT) || (margin == MARGIN_TOP)) {
	t1 = -t1, t2 = -t2;
	labelOffset = -labelOffset;
    }
    infoPtr->axis = axisline;
    infoPtr->t1 = axisline + t1;
    infoPtr->t2 = axisline + t2;
    infoPtr->label = axisline + labelOffset;

    if (axisPtr->flags & AXIS_TICKS_INTERIOR) {
	infoPtr->label = axisline + labelOffset - t1;
	infoPtr->t1 = axisline - t1;
	infoPtr->t2 = axisline - t2;
    } 
}

static void
MakeAxisLine(Axis *axisPtr, int line, Segment2d *sp)
{
    double min, max;

    min = axisPtr->axisRange.min;
    max = axisPtr->axisRange.max;
    if (axisPtr->logScale) {
	min = EXP10(min);
	max = EXP10(max);
    }
    if (AxisIsHorizontal(axisPtr)) {
	sp->p.x = Blt_HMap(axisPtr, min);
	sp->q.x = Blt_HMap(axisPtr, max);
	sp->p.y = sp->q.y = line;
    } else {
	sp->q.x = sp->p.x = line;
	sp->p.y = Blt_VMap(axisPtr, min);
	sp->q.y = Blt_VMap(axisPtr, max);
    }
}


static void
MakeTick(Axis *axisPtr, double value, int tick, int line, Segment2d *sp)
{
    if (axisPtr->logScale) {
	value = EXP10(value);
    }
    if (AxisIsHorizontal(axisPtr)) {
	sp->p.x = sp->q.x = Blt_HMap(axisPtr, value);
	sp->p.y = line;
	sp->q.y = tick;
    } else {
	sp->p.x = line;
	sp->p.y = sp->q.y = Blt_VMap(axisPtr, value);
	sp->q.x = tick;
    }
}

static void
MakeSegments(Axis *axisPtr, AxisInfo *infoPtr)
{
    int arraySize;
    int nMajorTicks, nMinorTicks;
    Segment2d *segments;
    Segment2d *sp;

    if (axisPtr->segments != NULL) {
	Blt_Free(axisPtr->segments);
    }
    nMajorTicks = nMinorTicks = 0;
    if (axisPtr->t1Ptr != NULL) {
	nMajorTicks = axisPtr->t1Ptr->nTicks;
    }
    if (axisPtr->t2Ptr != NULL) {
	nMinorTicks = axisPtr->t2Ptr->nTicks;
    }
    arraySize = 1 + (nMajorTicks * (nMinorTicks + 1));
    segments = Blt_AssertMalloc(arraySize * sizeof(Segment2d));
    sp = segments;
    if (axisPtr->lineWidth > 0) {
	/* Axis baseline */
	MakeAxisLine(axisPtr, infoPtr->axis, sp);
	sp++;
    }
    if ((axisPtr->flags & AXIS_TICKS) && (axisPtr->t1Ptr != NULL)) {
	Blt_ChainLink link;
	double labelPos;
	int i;
	int isHoriz;

	isHoriz = AxisIsHorizontal(axisPtr);
	for (i = 0; i < axisPtr->t1Ptr->nTicks; i++) {
	    double t1, t2;
	    int j;

	    t1 = axisPtr->t1Ptr->values[i];
	    /* Minor ticks */
	    for (j = 0; j < axisPtr->t2Ptr->nTicks; j++) {
		t2 = t1 + (axisPtr->majorSweep.step * 
			   axisPtr->t2Ptr->values[j]);
		if (InRange(t2, &axisPtr->axisRange)) {
		    MakeTick(axisPtr, t2, infoPtr->t2, infoPtr->axis, sp);
		    sp++;
		}
	    }
	    if (!InRange(t1, &axisPtr->axisRange)) {
		continue;
	    }
	    /* Major tick */
	    MakeTick(axisPtr, t1, infoPtr->t1, infoPtr->axis, sp);
	    sp++;
	}

	link = Blt_Chain_FirstLink(axisPtr->tickLabels);
	labelPos = (double)infoPtr->label;

	for (i = 0; i < axisPtr->t1Ptr->nTicks; i++) {
	    double t1;
	    TickLabel *labelPtr;
	    Segment2d seg;

	    t1 = axisPtr->t1Ptr->values[i];
	    if (axisPtr->labelOffset) {
		t1 += axisPtr->majorSweep.step * 0.5;
	    }
	    if (!InRange(t1, &axisPtr->axisRange)) {
		continue;
	    }
	    labelPtr = Blt_Chain_GetValue(link);
	    link = Blt_Chain_NextLink(link);
	    MakeTick(axisPtr, t1, infoPtr->t1, infoPtr->axis, &seg);
	    /* Save tick label X-Y position. */
	    if (isHoriz) {
		labelPtr->anchorPos.x = seg.p.x;
		labelPtr->anchorPos.y = labelPos;
	    } else {
		labelPtr->anchorPos.x = labelPos;
		labelPtr->anchorPos.y = seg.p.y;
	    }
	}
    }
    axisPtr->segments = segments;
    axisPtr->nSegments = sp - segments;
    assert(axisPtr->nSegments <= arraySize);
}

/*
 *---------------------------------------------------------------------------
 *
 * MapAxis --
 *
 *	Pre-calculates positions of the axis, ticks, and labels (to be used
 *	later when displaying the axis).  Calculates the values for each major
 *	and minor tick and checks to see if they are in range (the outer ticks
 *	may be outside of the range of plotted values).
 *
 *	Line segments for the minor and major ticks are saved into one XSegment
 *	array so that they can be drawn by a single XDrawSegments call. The
 *	positions of the tick labels are also computed and saved.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Line segments and tick labels are saved and used later to draw the axis.
 *
 *---------------------------------------------------------------------------
 */
static void
MapAxis(Axis *axisPtr, int offset, int margin)
{
    AxisInfo info;
    Graph *graphPtr = axisPtr->obj.graphPtr;

    if (AxisIsHorizontal(axisPtr)) {
	axisPtr->screenMin = graphPtr->hOffset;
	axisPtr->width = graphPtr->right - graphPtr->left;
	axisPtr->screenRange = graphPtr->hRange;
    } else {
	axisPtr->screenMin = graphPtr->vOffset;
	axisPtr->height = graphPtr->bottom - graphPtr->top;
	axisPtr->screenRange = graphPtr->vRange;
    }
    axisPtr->screenScale = 1.0 / axisPtr->screenRange;
    AxisOffsets(axisPtr, margin, offset, &info);
    MakeSegments(axisPtr, &info);
}

/*
 *---------------------------------------------------------------------------
 *
 * MapStackedAxis --
 *
 *	Pre-calculates positions of the axis, ticks, and labels (to be used
 *	later when displaying the axis).  Calculates the values for each major
 *	and minor tick and checks to see if they are in range (the outer ticks
 *	may be outside of the range of plotted values).
 *
 *	Line segments for the minor and major ticks are saved into one XSegment
 *	array so that they can be drawn by a single XDrawSegments call. The
 *	positions of the tick labels are also computed and saved.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Line segments and tick labels are saved and used later to draw the axis.
 *
 *---------------------------------------------------------------------------
 */
static void
MapStackedAxis(Axis *axisPtr, int count, int margin)
{
    AxisInfo info;
    Graph *graphPtr = axisPtr->obj.graphPtr;
    unsigned int slice, w, h;

    if (AxisIsHorizontal(axisPtr)) {
	slice = graphPtr->hRange / graphPtr->margins[margin].axes->nLinks;
	axisPtr->screenMin = graphPtr->hOffset;
	axisPtr->width = slice;
    } else {
	slice = graphPtr->vRange / graphPtr->margins[margin].axes->nLinks;
	axisPtr->screenMin = graphPtr->vOffset;
	axisPtr->height = slice;
    }
#define AXIS_PAD 2
    Blt_GetTextExtents(axisPtr->tickFont, 0, "0", 1, &w, &h);
    axisPtr->screenMin += (slice * count) + AXIS_PAD + h / 2;
    axisPtr->screenRange = slice - 2 * AXIS_PAD - h;
    axisPtr->screenScale = 1.0f / axisPtr->screenRange;
    AxisOffsets(axisPtr, margin, 0, &info);
    MakeSegments(axisPtr, &info);
}

/*
 *---------------------------------------------------------------------------
 *
 * AdjustViewport --
 *
 *	Adjusts the offsets of the viewport according to the scroll mode.  This
 *	is to accommodate both "listbox" and "canvas" style scrolling.
 *
 *	"canvas"	The viewport scrolls within the range of world
 *			coordinates.  This way the viewport always displays
 *			a full page of the world.  If the world is smaller
 *			than the viewport, then (bizarrely) the world and
 *			viewport are inverted so that the world moves up
 *			and down within the viewport.
 *
 *	"listbox"	The viewport can scroll beyond the range of world
 *			coordinates.  Every entry can be displayed at the
 *			top of the viewport.  This also means that the
 *			scrollbar thumb weirdly shrinks as the last entry
 *			is scrolled upward.
 *
 * Results:
 *	The corrected offset is returned.
 *
 *---------------------------------------------------------------------------
 */
static double
AdjustViewport(double offset, double windowSize)
{
    /*
     * Canvas-style scrolling allows the world to be scrolled within the window.
     */
    if (windowSize > 1.0) {
	if (windowSize < (1.0 - offset)) {
	    offset = 1.0 - windowSize;
	}
	if (offset > 0.0) {
	    offset = 0.0;
	}
    } else {
	if ((offset + windowSize) > 1.0) {
	    offset = 1.0 - windowSize;
	}
	if (offset < 0.0) {
	    offset = 0.0;
	}
    }
    return offset;
}

static int
GetAxisScrollInfo(
    Tcl_Interp *interp,
    int objc,
    Tcl_Obj *const *objv,
    double *offsetPtr,
    double windowSize,
    double scrollUnits,
    double scale)
{
    const char *string;
    char c;
    double offset;
    int length;

    offset = *offsetPtr;
    string = Tcl_GetStringFromObj(objv[0], &length);
    c = string[0];
    scrollUnits *= scale;
    if ((c == 's') && (strncmp(string, "scroll", length) == 0)) {
	int count;
	double fract;

	assert(objc == 3);
	/* Scroll number unit/page */
	if (Tcl_GetIntFromObj(interp, objv[1], &count) != TCL_OK) {
	    return TCL_ERROR;
	}
	string = Tcl_GetStringFromObj(objv[2], &length);
	c = string[0];
	if ((c == 'u') && (strncmp(string, "units", length) == 0)) {
	    fract = count * scrollUnits;
	} else if ((c == 'p') && (strncmp(string, "pages", length) == 0)) {
	    /* A page is 90% of the view-able window. */
	    fract = (int)(count * windowSize * 0.9 + 0.5);
	} else if ((c == 'p') && (strncmp(string, "pixels", length) == 0)) {
	    fract = count * scale;
	} else {
	    Tcl_AppendResult(interp, "unknown \"scroll\" units \"", string,
		"\"", (char *)NULL);
	    return TCL_ERROR;
	}
	offset += fract;
    } else if ((c == 'm') && (strncmp(string, "moveto", length) == 0)) {
	double fract;

	assert(objc == 2);
	/* moveto fraction */
	if (Tcl_GetDoubleFromObj(interp, objv[1], &fract) != TCL_OK) {
	    return TCL_ERROR;
	}
	offset = fract;
    } else {
	int count;
	double fract;

	/* Treat like "scroll units" */
	if (Tcl_GetIntFromObj(interp, objv[0], &count) != TCL_OK) {
	    return TCL_ERROR;
	}
	fract = (double)count * scrollUnits;
	offset += fract;
	/* CHECK THIS: return TCL_OK; */
    }
    *offsetPtr = AdjustViewport(offset, windowSize);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * DrawAxis --
 *
 *	Draws the axis, ticks, and labels onto the canvas.
 *
 *	Initializes and passes text attribute information through TextStyle
 *	structure.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Axis gets drawn on window.
 *
 *---------------------------------------------------------------------------
 */
static void
DrawAxis(Axis *axisPtr, Drawable drawable)
{
    Graph *graphPtr = axisPtr->obj.graphPtr;
    Blt_Background bg;
    int relief;

    if (axisPtr->flags & ACTIVE) {
	bg = axisPtr->activeBg;
	relief = axisPtr->activeRelief;
    } else {
	bg = axisPtr->normalBg;
	relief = axisPtr->relief;
    }
	bg = axisPtr->normalBg;
	relief = axisPtr->relief;
    if (bg != NULL) {
	Blt_FillBackgroundRectangle(graphPtr->tkwin, drawable, bg, 
		axisPtr->left, axisPtr->top, axisPtr->right - axisPtr->left, 
		axisPtr->bottom - axisPtr->top, axisPtr->borderWidth, relief);
    }
    if (axisPtr->title != NULL) {
	TextStyle ts;

	Blt_Ts_InitStyle(ts);
	Blt_Ts_SetAngle(ts, axisPtr->titleAngle);
	Blt_Ts_SetFont(ts, axisPtr->titleFont);
	Blt_Ts_SetPadding(ts, 1, 2, 0, 0);
	Blt_Ts_SetAnchor(ts, axisPtr->titleAnchor);
	Blt_Ts_SetJustify(ts, axisPtr->titleJustify);
	if (axisPtr->flags & ACTIVE) {
	    Blt_Ts_SetForeground(ts, axisPtr->activeFgColor);
	} else {
	    Blt_Ts_SetForeground(ts, axisPtr->titleColor);
	}
	Blt_Ts_SetForeground(ts, axisPtr->titleColor);
	Blt_DrawText(graphPtr->tkwin, drawable, axisPtr->title, &ts, 
		(int)axisPtr->titlePos.x, (int)axisPtr->titlePos.y);
    }
    if (axisPtr->scrollCmdObjPtr != NULL) {
	double viewWidth, viewMin, viewMax;
	double worldWidth, worldMin, worldMax;
	double fract;
	int isHoriz;

	worldMin = axisPtr->valueRange.min;
	worldMax = axisPtr->valueRange.max;
	if (DEFINED(axisPtr->scrollMin)) {
	    worldMin = axisPtr->scrollMin;
	}
	if (DEFINED(axisPtr->scrollMax)) {
	    worldMax = axisPtr->scrollMax;
	}
	viewMin = axisPtr->min;
	viewMax = axisPtr->max;
	if (viewMin < worldMin) {
	    viewMin = worldMin;
	}
	if (viewMax > worldMax) {
	    viewMax = worldMax;
	}
	if (axisPtr->logScale) {
	    worldMin = log10(worldMin);
	    worldMax = log10(worldMax);
	    viewMin = log10(viewMin);
	    viewMax = log10(viewMax);
	}
	worldWidth = worldMax - worldMin;	
	viewWidth = viewMax - viewMin;
	isHoriz = AxisIsHorizontal(axisPtr);

	if (isHoriz != axisPtr->descending) {
	    fract = (viewMin - worldMin) / worldWidth;
	} else {
	    fract = (worldMax - viewMax) / worldWidth;
	}
	fract = AdjustViewport(fract, viewWidth / worldWidth);

	if (isHoriz != axisPtr->descending) {
	    viewMin = (fract * worldWidth);
	    axisPtr->min = viewMin + worldMin;
	    axisPtr->max = axisPtr->min + viewWidth;
	    viewMax = viewMin + viewWidth;
	    if (axisPtr->logScale) {
		axisPtr->min = EXP10(axisPtr->min);
		axisPtr->max = EXP10(axisPtr->max);
	    }
	    Blt_UpdateScrollbar(graphPtr->interp, axisPtr->scrollCmdObjPtr,
		(viewMin / worldWidth), (viewMax / worldWidth));
	} else {
	    viewMax = (fract * worldWidth);
	    axisPtr->max = worldMax - viewMax;
	    axisPtr->min = axisPtr->max - viewWidth;
	    viewMin = viewMax + viewWidth;
	    if (axisPtr->logScale) {
		axisPtr->min = EXP10(axisPtr->min);
		axisPtr->max = EXP10(axisPtr->max);
	    }
	    Blt_UpdateScrollbar(graphPtr->interp, axisPtr->scrollCmdObjPtr,
		(viewMax / worldWidth), (viewMin / worldWidth));
	}
    }
    if (axisPtr->flags & AXIS_TICKS) {
	Blt_ChainLink link;
	TextStyle ts;

	Blt_Ts_InitStyle(ts);
	Blt_Ts_SetAngle(ts, axisPtr->tickAngle);
	Blt_Ts_SetFont(ts, axisPtr->tickFont);
	Blt_Ts_SetPadding(ts, 02, 0, 0, 0);
	Blt_Ts_SetAnchor(ts, axisPtr->tickAnchor);
	if (axisPtr->flags & ACTIVE) {
	    Blt_Ts_SetForeground(ts, axisPtr->activeFgColor);
	} else {
	    Blt_Ts_SetForeground(ts, axisPtr->tickColor);
	}
	    Blt_Ts_SetForeground(ts, axisPtr->tickColor);
	for (link = Blt_Chain_FirstLink(axisPtr->tickLabels); link != NULL;
	    link = Blt_Chain_NextLink(link)) {	
	    TickLabel *labelPtr;

	    labelPtr = Blt_Chain_GetValue(link);

	    /* Draw major tick labels */
	    Blt_DrawText(graphPtr->tkwin, drawable, labelPtr->string, &ts, 
		(int)labelPtr->anchorPos.x, (int)labelPtr->anchorPos.y);
	}
    }
    if ((axisPtr->nSegments > 0) && (axisPtr->lineWidth > 0)) {	
	GC gc;

	if (axisPtr->flags & ACTIVE) {
	    gc = axisPtr->activeTickGC;
	} else {
	    gc = axisPtr->tickGC;
	}
	/* Draw the tick marks and axis line. */
	Blt_Draw2DSegments(graphPtr->display, drawable, gc, axisPtr->segments, 
		axisPtr->nSegments);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * AxisToPostScript --
 *
 *	Generates PostScript output to draw the axis, ticks, and labels.
 *
 *	Initializes and passes text attribute information through TextStyle
 *	structure.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	PostScript output is left in graphPtr->interp->result;
 *
 *---------------------------------------------------------------------------
 */
/* ARGSUSED */
static void
AxisToPostScript(Blt_Ps ps, Axis *axisPtr)
{
    Blt_Background bg;
    int relief;

    Blt_Ps_Format(ps, "%% Axis \"%s\"\n", axisPtr->obj.name);
    if (axisPtr->flags & ACTIVE) {
	bg = axisPtr->activeBg;
	relief = axisPtr->activeRelief;
    } else {
	bg = axisPtr->normalBg;
	relief = axisPtr->relief;
    }
    if (bg != NULL) {
	Tk_3DBorder border;

	border = Blt_BackgroundBorder(bg);
	Blt_Ps_Fill3DRectangle(ps, border, 
		(double)axisPtr->left, 
		(double)axisPtr->top, 
		axisPtr->right - axisPtr->left,
		axisPtr->bottom - axisPtr->top, 
		axisPtr->borderWidth,
		relief);
    }
    if (axisPtr->title != NULL) {
	TextStyle ts;

	Blt_Ts_InitStyle(ts);
	Blt_Ts_SetAngle(ts, axisPtr->titleAngle);
	Blt_Ts_SetFont(ts, axisPtr->titleFont);
	Blt_Ts_SetPadding(ts, 1, 2, 0, 0);
	Blt_Ts_SetAnchor(ts, axisPtr->titleAnchor);
	Blt_Ts_SetJustify(ts, axisPtr->titleJustify);
	if (axisPtr->flags & ACTIVE) {
	    Blt_Ts_SetForeground(ts, axisPtr->activeFgColor);
	} else {
	    Blt_Ts_SetForeground(ts, axisPtr->titleColor);
	}
	Blt_Ps_DrawText(ps, axisPtr->title, &ts, axisPtr->titlePos.x, 
		axisPtr->titlePos.y);
    }
    if (axisPtr->flags & AXIS_TICKS) {
	Blt_ChainLink link;
	TextStyle ts;

	Blt_Ts_InitStyle(ts);
	Blt_Ts_SetAngle(ts, axisPtr->tickAngle);
	Blt_Ts_SetFont(ts, axisPtr->tickFont);
	Blt_Ts_SetPadding(ts, 2, 2, 0, 0);
	Blt_Ts_SetAnchor(ts, axisPtr->tickAnchor);
	Blt_Ts_SetForeground(ts, axisPtr->tickColor);

	for (link = Blt_Chain_FirstLink(axisPtr->tickLabels); link != NULL; 
	     link = Blt_Chain_NextLink(link)) {
	    TickLabel *labelPtr;

	    labelPtr = Blt_Chain_GetValue(link);
	    Blt_Ps_DrawText(ps, labelPtr->string, &ts, labelPtr->anchorPos.x, 
		labelPtr->anchorPos.y);
	}
    }
    if ((axisPtr->nSegments > 0) && (axisPtr->lineWidth > 0)) {
	Blt_Ps_XSetLineAttributes(ps, axisPtr->tickColor, axisPtr->lineWidth, 
		(Blt_Dashes *)NULL, CapButt, JoinMiter);
	Blt_Ps_Draw2DSegments(ps, axisPtr->segments, axisPtr->nSegments);
    }
}

static void
MakeGridLine(Axis *axisPtr, double value, Segment2d *sp)
{
    Graph *graphPtr = axisPtr->obj.graphPtr;

    if (axisPtr->logScale) {
	value = EXP10(value);
    }
    /* Grid lines run orthogonally to the axis */
    if (AxisIsHorizontal(axisPtr)) {
	sp->p.y = graphPtr->top;
	sp->q.y = graphPtr->bottom;
	sp->p.x = sp->q.x = Blt_HMap(axisPtr, value);
    } else {
	sp->p.x = graphPtr->left;
	sp->q.x = graphPtr->right;
	sp->p.y = sp->q.y = Blt_VMap(axisPtr, value);
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * MapGridlines --
 *
 *	Assembles the grid lines associated with an axis. Generates tick
 *	positions if necessary (this happens when the axis is not a logical axis
 *	too).
 *
 * Results:
 *	None.
 *
 *---------------------------------------------------------------------------
 */
static void
MapGridlines(Axis *axisPtr)
{
    Segment2d *s1, *s2;
    Ticks *t1Ptr, *t2Ptr;
    int needed;
    int i;

    if (axisPtr == NULL) {
	return;
    }
    t1Ptr = axisPtr->t1Ptr;
    if (t1Ptr == NULL) {
	t1Ptr = GenerateTicks(&axisPtr->majorSweep);
    }
    t2Ptr = axisPtr->t2Ptr;
    if (t2Ptr == NULL) {
	t2Ptr = GenerateTicks(&axisPtr->minorSweep);
    }
    needed = t1Ptr->nTicks;
    if (axisPtr->flags & AXIS_GRID_MINOR) {
	needed += (t1Ptr->nTicks * t2Ptr->nTicks);
    }
    if (needed == 0) {
	return;			
    }
    needed = t1Ptr->nTicks;
    if (needed != axisPtr->major.nAllocated) {
	if (axisPtr->major.segments != NULL) {
	    Blt_Free(axisPtr->major.segments);
	}
	axisPtr->major.segments = Blt_AssertMalloc(sizeof(Segment2d) * needed);
	axisPtr->major.nAllocated = needed;
    }
    needed = (t1Ptr->nTicks * t2Ptr->nTicks);
    if (needed != axisPtr->minor.nAllocated) {
	if (axisPtr->minor.segments != NULL) {
	    Blt_Free(axisPtr->minor.segments);
	}
	axisPtr->minor.segments = Blt_AssertMalloc(sizeof(Segment2d) * needed);
	axisPtr->minor.nAllocated = needed;
    }
    s1 = axisPtr->major.segments, s2 = axisPtr->minor.segments;
    for (i = 0; i < t1Ptr->nTicks; i++) {
	double value;

	value = t1Ptr->values[i];
	if (axisPtr->flags & AXIS_GRID_MINOR) {
	    int j;

	    for (j = 0; j < t2Ptr->nTicks; j++) {
		double subValue;

		subValue = value + (axisPtr->majorSweep.step * 
				    t2Ptr->values[j]);
		if (InRange(subValue, &axisPtr->axisRange)) {
		    MakeGridLine(axisPtr, subValue, s2);
		    s2++;
		}
	    }
	}
	if (InRange(value, &axisPtr->axisRange)) {
	    MakeGridLine(axisPtr, value, s1);
	    s1++;
	}
    }
    if (t1Ptr != axisPtr->t1Ptr) {
	Blt_Free(t1Ptr);		/* Free generated ticks. */
    }
    if (t2Ptr != axisPtr->t2Ptr) {
	Blt_Free(t2Ptr);		/* Free generated ticks. */
    }
    axisPtr->major.nUsed = s1 - axisPtr->major.segments;
    axisPtr->minor.nUsed = s2 - axisPtr->minor.segments;
}

/*
 *---------------------------------------------------------------------------
 *
 * GetAxisGeometry --
 *
 * Results:
 *	None.
 *
 *---------------------------------------------------------------------------
 */
static void
GetAxisGeometry(Axis *axisPtr)
{
    unsigned int y;

    FreeLabels(axisPtr->tickLabels);
    y = 0;

    if ((axisPtr->lineWidth > 0) && 
	(axisPtr->obj.graphPtr->plotRelief != TK_RELIEF_SOLID)) {
	/* Leave room for axis baseline (and pad) */
	y += axisPtr->lineWidth + 2;
    }
    if (axisPtr->flags & AXIS_TICKS) {
	unsigned int pad;
	unsigned int i, nLabels;
	unsigned int maxWidth, maxHeight;

	SweepTicks(axisPtr);
	
	assert (axisPtr->t1Ptr->nTicks <= MAXTICKS);
	
	maxHeight = maxWidth = 0;
	nLabels = 0;
	for (i = 0; i < axisPtr->t1Ptr->nTicks; i++) {
	    TickLabel *labelPtr;
	    double x, x2;
	    unsigned int lw, lh; /* Label width and height. */

	    x2 = x = axisPtr->t1Ptr->values[i];
	    if (axisPtr->labelOffset) {
		x2 += axisPtr->majorSweep.step * 0.5;
	    }
	    if (!InRange(x2, &axisPtr->axisRange)) {
		continue;
	    }
	    labelPtr = MakeLabel(axisPtr, x);
	    Blt_Chain_Append(axisPtr->tickLabels, labelPtr);
	    nLabels++;
	    /* 
	     * Get the dimensions of each tick label.  Remember tick labels can
	     * be multi-lined and/or rotated.
	     */
	    Blt_GetTextExtents(axisPtr->tickFont, 0, labelPtr->string, -1, 
		&lw, &lh);
	    labelPtr->width  = lw;
	    labelPtr->height = lh;

	    if (axisPtr->tickAngle != 0.0f) {
		double rlw, rlh;		/* Rotated label width and
						 * height. */
		Blt_GetBoundingBox(lw, lh, axisPtr->tickAngle, &rlw,&rlh, NULL);
		lw = ROUND(rlw), lh = ROUND(rlh);
	    }
	    if (maxWidth < lw) {
		maxWidth = lw;
	    }
	    if (maxHeight < lh) {
		maxHeight = lh;
	    }
	}
	assert(nLabels <= axisPtr->t1Ptr->nTicks);
	
	/* Because the axis cap style is "CapProjecting", we need to account
	 * for an extra 1.5 linewidth at the end of each line.  */

	pad = ((axisPtr->lineWidth * 12) / 8);
	
	if (AxisIsHorizontal(axisPtr)) {
	    y += maxHeight + pad;
	} else {
	    y += maxWidth + pad;
	    if (maxWidth > 0) {
		y += 5;			/* Pad either size of label. */
	    }  
	}
	y += 2 * AXIS_PAD_TITLE;
	if ((axisPtr->lineWidth > 0) &&
	    ((axisPtr->flags & AXIS_TICKS_INTERIOR) == 0)) {
	    /* Distance from axis line to tick label. */
	    y += axisPtr->tickLength;
	}
    }

    if (axisPtr->title != NULL) {
	if (axisPtr->titleAlternate) {
	    if (y < axisPtr->titleHeight) {
		y = axisPtr->titleHeight;
	    }
	} else {
	    y += axisPtr->titleHeight + AXIS_PAD_TITLE;
	}
    }

    /* Correct for orientation of the axis. */
    if (AxisIsHorizontal(axisPtr)) {
	axisPtr->height = y;
    } else {
	axisPtr->width = y;
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * GetMarginGeometry --
 *
 *	Examines all the axes in the given margin and determines the area
 *	required to display them.
 *
 *	Note: For multiple axes, the titles are displayed in another
 *	      margin. So we must keep track of the widest title.
 *	
 * Results:
 *	Returns the width or height of the margin, depending if it runs
 *	horizontally along the graph or vertically.
 *
 * Side Effects:
 *	The area width and height set in the margin.  Note again that this may
 *	be corrected later (mulitple axes) to adjust for the longest title in
 *	another margin.
 *
 *---------------------------------------------------------------------------
 */
static int
GetMarginGeometry(Graph *graphPtr, Margin *marginPtr)
{
    Blt_ChainLink link;
    unsigned int l, w, h;		/* Length, width, and height. */
    int isHoriz;
    unsigned int nVisible;

    isHoriz = HORIZMARGIN(marginPtr);

    /* Count the visible axes. */
    nVisible = 0;
    l = w = h = 0;
    if (graphPtr->stackAxes) {
	for (link = Blt_Chain_FirstLink(marginPtr->axes); link != NULL;
	     link = Blt_Chain_NextLink(link)) {
	    Axis *axisPtr;
	    
	    axisPtr = Blt_Chain_GetValue(link);
	    if ((axisPtr->flags & (HIDE|AXIS_USE)) == AXIS_USE) {
		nVisible++;
		if (graphPtr->flags & GET_AXIS_GEOMETRY) {
		    GetAxisGeometry(axisPtr);
		}
		if (isHoriz) {
		    if (h < axisPtr->height) {
			h = axisPtr->height;
		    }
		} else {
		    if (w < axisPtr->width) {
			w = axisPtr->width;
		    }
		}
	    }
	}
    } else {
	for (link = Blt_Chain_FirstLink(marginPtr->axes); link != NULL;
	     link = Blt_Chain_NextLink(link)) {
	    Axis *axisPtr;
	    
	    axisPtr = Blt_Chain_GetValue(link);
	    if ((axisPtr->flags & (HIDE|AXIS_USE)) == AXIS_USE) {
		nVisible++;
		if (graphPtr->flags & GET_AXIS_GEOMETRY) {
		    GetAxisGeometry(axisPtr);
		}
		if ((axisPtr->titleAlternate) && (l < axisPtr->titleWidth)) {
		    l = axisPtr->titleWidth;
		}
		if (isHoriz) {
		    h += axisPtr->height;
		} else {
		    w += axisPtr->width;
		}
	    }
	}
    }
    /* Enforce a minimum size for margins. */
    if (w < 3) {
	w = 3;
    }
    if (h < 3) {
	h = 3;
    }
    marginPtr->nAxes = nVisible;
    marginPtr->axesTitleLength = l;
    marginPtr->width = w;
    marginPtr->height = h;
    marginPtr->axesOffset = (isHoriz) ? h : w;
    return marginPtr->axesOffset;
}

/*
 *---------------------------------------------------------------------------
 *
 * ComputeMargins --
 *
 *	Computes the size of the margins and the plotting area.  We first
 *	compute the space needed for the axes in each margin.  Then how much
 *	space the legend will occupy.  Finally, if the user has requested a
 *	margin size, we override the computed value.
 *
 * Results:
 *
 *---------------------------------------------------------------------------
 */
static void
ComputeMargins(Graph *graphPtr)
{
    unsigned int l, r, t, b;
    unsigned int w, h;
    unsigned int insets;

    /* 
     * Step 1:  Compute the amount of space needed to display the axes
     *		(there many be zero or more) associated with the margin.
     */
    l = GetMarginGeometry(graphPtr, &graphPtr->leftMargin);
    r = GetMarginGeometry(graphPtr, &graphPtr->rightMargin);
    t = GetMarginGeometry(graphPtr, &graphPtr->topMargin);
    b = GetMarginGeometry(graphPtr, &graphPtr->bottomMargin);

    /* 
     * Step 2:  Add the graph title height to the top margin. 
     */
    if (graphPtr->title != NULL) {
	t += graphPtr->titleHeight;
    }
    insets = 2 * (graphPtr->inset + graphPtr->plotBorderWidth);

    /* 
     * Step 3: Use the current estimate of the plot area to compute the
     *	       legend size.  Add it to the proper margin.
     */
    w = graphPtr->width  - (insets + l + r);
    h = graphPtr->height - (insets + t + b);
    Blt_MapLegend(graphPtr->legend, w, h);
    if (!Blt_LegendIsHidden(graphPtr->legend)) {
	switch (Blt_LegendSite(graphPtr->legend)) {
	case LEGEND_RIGHT:
	    r += Blt_LegendWidth(graphPtr->legend) + 2;
	    break;
	case LEGEND_LEFT:
	    l += Blt_LegendWidth(graphPtr->legend) + 2;
	    break;
	case LEGEND_TOP:
	    t += Blt_LegendHeight(graphPtr->legend) + 2;
	    break;
	case LEGEND_BOTTOM:
	    b += Blt_LegendHeight(graphPtr->legend) + 2;
	    break;
	case LEGEND_XY:
	case LEGEND_PLOT:
	case LEGEND_WINDOW:
	    /* Do nothing. */
	    break;
	}
    }

    /* 
     * Recompute the plotarea, now accounting for the legend. 
     */
    w = graphPtr->width  - (insets + l + r);
    h = graphPtr->height - (insets + t + b);

    /*
     * Step 5: If necessary, correct for the requested plot area aspect
     *	       ratio.
     */
    if (graphPtr->aspect > 0.0f) {
	float ratio;

	/* 
	 * Shrink one dimension of the plotarea to fit the requested
	 * width/height aspect ratio.
	 */
	ratio = (float)w / (float)h;
	if (ratio > graphPtr->aspect) {
	    int scaledWidth;

	    /* Shrink the width. */
	    scaledWidth = (int)(h * graphPtr->aspect);
	    if (scaledWidth < 1) {
		scaledWidth = 1;
	    }
	    r += (w - scaledWidth); /* Add the difference to the right
				     * margin. */
	    /* CHECK THIS: w = scaledWidth; */
	} else {
	    int scaledHeight;

	    /* Shrink the height. */
	    scaledHeight = (int)(w / graphPtr->aspect);
	    if (scaledHeight < 1) {
		scaledHeight = 1;
	    }
	    t += (h - scaledHeight); /* Add the difference to the top
				      * margin. */
	    /* CHECK THIS: h = scaledHeight; */
	}
    }

    /* 
     * Step 6: If there's multiple axes in a margin, the axis titles will be
     *	       displayed in the adjoining margins.  Make sure there's room 
     *	       for the longest axis titles.
     */

    if (t < graphPtr->leftMargin.axesTitleLength) {
	t = graphPtr->leftMargin.axesTitleLength;
    }
    if (r < graphPtr->bottomMargin.axesTitleLength) {
	r = graphPtr->bottomMargin.axesTitleLength;
    }
    if (t < graphPtr->rightMargin.axesTitleLength) {
	t = graphPtr->rightMargin.axesTitleLength;
    }
    if (r < graphPtr->topMargin.axesTitleLength) {
	r = graphPtr->topMargin.axesTitleLength;
    }

    /* 
     * Step 7: Override calculated values with requested margin sizes.
     */

    graphPtr->leftMargin.width = l;
    graphPtr->rightMargin.width = r;
    graphPtr->topMargin.height =  t;
    graphPtr->bottomMargin.height = b;
	    
    if (graphPtr->leftMargin.reqSize > 0) {
	graphPtr->leftMargin.width = graphPtr->leftMargin.reqSize;
    }
    if (graphPtr->rightMargin.reqSize > 0) {
	graphPtr->rightMargin.width = graphPtr->rightMargin.reqSize;
    }
    if (graphPtr->topMargin.reqSize > 0) {
	graphPtr->topMargin.height = graphPtr->topMargin.reqSize;
    }
    if (graphPtr->bottomMargin.reqSize > 0) {
	graphPtr->bottomMargin.height = graphPtr->bottomMargin.reqSize;
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_LayoutMargins --
 *
 *	Calculate the layout of the graph.  Based upon the data, axis limits,
 *	X and Y titles, and title height, determine the cavity left which is
 *	the plotting surface.  The first step get the data and axis limits for
 *	calculating the space needed for the top, bottom, left, and right
 *	margins.
 *
 * 	1) The LEFT margin is the area from the left border to the Y axis 
 *	   (not including ticks). It composes the border width, the width an 
 *	   optional Y axis label and its padding, and the tick numeric labels. 
 *	   The Y axis label is rotated 90 degrees so that the width is the 
 *	   font height.
 *
 * 	2) The RIGHT margin is the area from the end of the graph
 *	   to the right window border. It composes the border width,
 *	   some padding, the font height (this may be dubious. It
 *	   appears to provide a more even border), the max of the
 *	   legend width and 1/2 max X tick number. This last part is
 *	   so that the last tick label is not clipped.
 *
 *           Window Width
 *      ___________________________________________________________
 *      |          |                               |               |
 *      |          |   TOP  height of title        |               |
 *      |          |                               |               |
 *      |          |           x2 title            |               |
 *      |          |                               |               |
 *      |          |        height of x2-axis      |               |
 *      |__________|_______________________________|_______________|  W
 *      |          | -plotpady                     |               |  i
 *      |__________|_______________________________|_______________|  n
 *      |          | top                   right   |               |  d
 *      |          |                               |               |  o
 *      |   LEFT   |                               |     RIGHT     |  w
 *      |          |                               |               |
 *      | y        |     Free area = 104%          |      y2       |  H
 *      |          |     Plotting surface = 100%   |               |  e
 *      | t        |     Tick length = 2 + 2%      |      t        |  i
 *      | i        |                               |      i        |  g
 *      | t        |                               |      t  legend|  h
 *      | l        |                               |      l   width|  t
 *      | e        |                               |      e        |
 *      |    height|                               |height         |
 *      |       of |                               | of            |
 *      |    y-axis|                               |y2-axis        |
 *      |          |                               |               |
 *      |          |origin 0,0                     |               |
 *      |__________|_left_________________bottom___|_______________|
 *      |          |-plotpady                      |               |
 *      |__________|_______________________________|_______________|
 *      |          | (xoffset, yoffset)            |               |
 *      |          |                               |               |
 *      |          |       height of x-axis        |               |
 *      |          |                               |               |
 *      |          |   BOTTOM   x title            |               |
 *      |__________|_______________________________|_______________|
 *
 * 3) The TOP margin is the area from the top window border to the top
 *    of the graph. It composes the border width, twice the height of
 *    the title font (if one is given) and some padding between the
 *    title.
 *
 * 4) The BOTTOM margin is area from the bottom window border to the
 *    X axis (not including ticks). It composes the border width, the height
 *    an optional X axis label and its padding, the height of the font
 *    of the tick labels.
 *
 * The plotting area is between the margins which includes the X and Y axes
 * including the ticks but not the tick numeric labels. The length of the
 * ticks and its padding is 5% of the entire plotting area.  Hence the entire
 * plotting area is scaled as 105% of the width and height of the area.
 *
 * The axis labels, ticks labels, title, and legend may or may not be
 * displayed which must be taken into account.
 *
 *
 *---------------------------------------------------------------------------
 */
void
Blt_LayoutMargins(Graph *graphPtr)
{
    unsigned int w, h;
    unsigned int titleY;
    unsigned int l, r, t, b;

    ComputeMargins(graphPtr);
    l = graphPtr->leftMargin.width + graphPtr->inset + 
	graphPtr->plotBorderWidth;
    r = graphPtr->rightMargin.width + graphPtr->inset + 
	graphPtr->plotBorderWidth;
    t = graphPtr->topMargin.height + graphPtr->inset + 
	graphPtr->plotBorderWidth;
    b = graphPtr->bottomMargin.height + graphPtr->inset + 
	graphPtr->plotBorderWidth;

    /* Based upon the margins, calculate the space left for the graph. */
    w = graphPtr->width  - (l + r);
    h = graphPtr->height - (t + b);
    if (w < 1) {
	w = 1;
    }
    if (h < 1) {
	h = 1;
    }
    graphPtr->left   = l;
    graphPtr->right  = l + w;
    graphPtr->top    = t;
    graphPtr->bottom = t + h;

    graphPtr->vOffset = t + graphPtr->padTop;
    graphPtr->vRange  = h - PADDING(graphPtr->yPad);
    graphPtr->hOffset = l + graphPtr->padLeft;
    graphPtr->hRange  = w - PADDING(graphPtr->xPad);

    if (graphPtr->vRange < 1) {
	graphPtr->vRange = 1;
    }
    if (graphPtr->hRange < 1) {
	graphPtr->hRange = 1;
    }
    graphPtr->hScale = 1.0f / (float)graphPtr->hRange;
    graphPtr->vScale = 1.0f / (float)graphPtr->vRange;

    /*
     * Calculate the placement of the graph title so it is centered within the
     * space provided for it in the top margin
     */
    titleY = graphPtr->titleHeight;
    graphPtr->titleY = (titleY / 2) + graphPtr->inset;
    graphPtr->titleX = (graphPtr->right + graphPtr->left) / 2;
}

/*
 *---------------------------------------------------------------------------
 *
 * ConfigureAxis --
 *
 *	Configures axis attributes (font, line width, label, etc).
 *
 * Results:
 *	The return value is a standard TCL result.
 *
 * Side Effects:
 *	Axis layout is deferred until the height and width of the window are
 *	known.
 *
 *---------------------------------------------------------------------------
 */

static int
ConfigureAxis(Axis *axisPtr)
{
    Graph *graphPtr = axisPtr->obj.graphPtr;
    float angle;

    /* Check the requested axis limits. Can't allow -min to be greater than
     * -max.  Do this regardless of -checklimits option. We want to always 
     * detect when the user has zoomed in beyond the precision of the data.*/
    if (((DEFINED(axisPtr->reqMin)) && (DEFINED(axisPtr->reqMax))) &&
	(axisPtr->reqMin >= axisPtr->reqMax)) {
	char msg[200];
	sprintf_s(msg, 200, 
		  "impossible axis limits (-min %g >= -max %g) for \"%s\"",
		  axisPtr->reqMin, axisPtr->reqMax, axisPtr->obj.name);
	Tcl_AppendResult(graphPtr->interp, msg, (char *)NULL);
	return TCL_ERROR;
    }
    axisPtr->scrollMin = axisPtr->reqScrollMin;
    axisPtr->scrollMax = axisPtr->reqScrollMax;
    if (axisPtr->logScale) {
	if (axisPtr->flags & AXIS_CHECK_LIMITS) {
	    /* Check that the logscale limits are positive.  */
	    if ((DEFINED(axisPtr->reqMin)) && (axisPtr->reqMin <= 0.0)) {
		Tcl_AppendResult(graphPtr->interp,"bad logscale -min limit \"", 
			Blt_Dtoa(graphPtr->interp, axisPtr->reqMin), 
			"\" for axis \"", axisPtr->obj.name, "\"", 
			(char *)NULL);
		return TCL_ERROR;
	    }
	}
	if ((DEFINED(axisPtr->scrollMin)) && (axisPtr->scrollMin <= 0.0)) {
	    axisPtr->scrollMin = Blt_NaN();
	}
	if ((DEFINED(axisPtr->scrollMax)) && (axisPtr->scrollMax <= 0.0)) {
	    axisPtr->scrollMax = Blt_NaN();
	}
    }
    if (axisPtr->reqNumMajorTicks <= 0) {
	axisPtr->reqNumMajorTicks = 4;
    }
    angle = FMOD(axisPtr->tickAngle, 360.0);
    if (angle < 0.0f) {
	angle += 360.0f;
    }
    if (axisPtr->normalBg != NULL) {
	Blt_SetBackgroundChangedProc(axisPtr->normalBg, Blt_UpdateGraph, 
		graphPtr);
    }
    if (axisPtr->activeBg != NULL) {
	Blt_SetBackgroundChangedProc(axisPtr->activeBg, Blt_UpdateGraph, 
		graphPtr);
    }
    axisPtr->tickAngle = angle;
    ResetTextStyles(axisPtr);

    axisPtr->titleWidth = axisPtr->titleHeight = 0;
    if (axisPtr->title != NULL) {
	unsigned int w, h;

	Blt_GetTextExtents(axisPtr->titleFont, 0, axisPtr->title, -1, &w, &h);
	axisPtr->titleWidth = (unsigned short int)w;
	axisPtr->titleHeight = (unsigned short int)h;
    }

    /* 
     * Don't bother to check what configuration options have changed.  Almost
     * every option changes the size of the plotting area (except for -color
     * and -titlecolor), requiring the graph and its contents to be completely
     * redrawn.
     *
     * Recompute the scale and offset of the axis in case -min, -max options
     * have changed.
     */
    graphPtr->flags |= REDRAW_WORLD;
    if (!Blt_ConfigModified(configSpecs, "-*color", "-background", "-bg",
		    (char *)NULL)) {
	graphPtr->flags |= (MAP_WORLD | RESET_AXES);
	axisPtr->flags |= DIRTY;
    }
    Blt_EventuallyRedrawGraph(graphPtr);

    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * CreateAxis --
 *
 *	Create and initialize a structure containing information to display
 *	a graph axis.
 *
 * Results:
 *	The return value is a pointer to an Axis structure.
 *
 *---------------------------------------------------------------------------
 */
static Axis *
CreateAxis(Graph *graphPtr, const char *name, int margin)
{
    Axis *axisPtr;
    Blt_HashEntry *hPtr;
    int isNew;

    if (name[0] == '-') {
	Tcl_AppendResult(graphPtr->interp, "name of axis \"", name, 
			 "\" can't start with a '-'", (char *)NULL);
	return NULL;
    }
    hPtr = Blt_CreateHashEntry(&graphPtr->axes.table, name, &isNew);
    if (!isNew) {
	axisPtr = Blt_GetHashValue(hPtr);
	if ((axisPtr->flags & DELETE_PENDING) == 0) {
	    Tcl_AppendResult(graphPtr->interp, "axis \"", name,
		"\" already exists in \"", Tk_PathName(graphPtr->tkwin), "\"",
		(char *)NULL);
	    return NULL;
	}
	axisPtr->flags &= ~DELETE_PENDING;
    } else {
	axisPtr = Blt_Calloc(1, sizeof(Axis));
	if (axisPtr == NULL) {
	    Tcl_AppendResult(graphPtr->interp, 
		"can't allocate memory for axis \"", name, "\"", (char *)NULL);
	    return NULL;
	}
	axisPtr->obj.name = Blt_AssertStrdup(name);
	axisPtr->hashPtr = hPtr;
	Blt_GraphSetObjectClass(&axisPtr->obj, CID_NONE);
	axisPtr->obj.graphPtr = graphPtr;
	axisPtr->looseMin = axisPtr->looseMax = AXIS_TIGHT;
	axisPtr->reqNumMinorTicks = 2;
	axisPtr->reqNumMajorTicks = 4 /*10*/;
	axisPtr->scrollUnits = 10;
	axisPtr->reqMin = axisPtr->reqMax = Blt_NaN();
	axisPtr->reqScrollMin = axisPtr->reqScrollMax = Blt_NaN();
	axisPtr->flags = (AXIS_TICKS|AXIS_GRID_MINOR|AXIS_AUTO_MAJOR|
			  AXIS_AUTO_MINOR);
	if (graphPtr->classId == CID_ELEM_BAR) {
	    axisPtr->flags |= AXIS_GRID;
	}
	if ((graphPtr->classId == CID_ELEM_BAR) && 
	    ((margin == MARGIN_TOP) || (margin == MARGIN_BOTTOM))) {
	    axisPtr->reqStep = 1.0;
	    axisPtr->reqNumMinorTicks = 0;
	} 
	if ((margin == MARGIN_RIGHT) || (margin == MARGIN_TOP)) {
	    axisPtr->flags |= HIDE;
	}
	Blt_Ts_InitStyle(axisPtr->limitsTextStyle);
	axisPtr->tickLabels = Blt_Chain_Create();
	axisPtr->lineWidth = 1;
	Blt_SetHashValue(hPtr, axisPtr);
    }
    return axisPtr;
}

static int
GetAxisFromObj(Tcl_Interp *interp, Graph *graphPtr, Tcl_Obj *objPtr, 
	       Axis **axisPtrPtr)
{
    Blt_HashEntry *hPtr;
    const char *name;

    *axisPtrPtr = NULL;
    name = Tcl_GetString(objPtr);
    hPtr = Blt_FindHashEntry(&graphPtr->axes.table, name);
    if (hPtr != NULL) {
	Axis *axisPtr;

	axisPtr = Blt_GetHashValue(hPtr);
	if ((axisPtr->flags & DELETE_PENDING) == 0) {
	    *axisPtrPtr = axisPtr;
	    return TCL_OK;
	}
    }
    if (interp != NULL) {
	Tcl_AppendResult(interp, "can't find axis \"", name, "\" in \"", 
		Tk_PathName(graphPtr->tkwin), "\"", (char *)NULL);
    }
    return TCL_ERROR;
}

static int
GetAxisByClass(Tcl_Interp *interp, Graph *graphPtr, Tcl_Obj *objPtr,
	       ClassId classId, Axis **axisPtrPtr)
{
    Axis *axisPtr;

    if (GetAxisFromObj(interp, graphPtr, objPtr, &axisPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if (classId != CID_NONE) {
	if ((axisPtr->refCount == 0) || (axisPtr->obj.classId == CID_NONE)) {
	    /* Set the axis type on the first use of it. */
	    Blt_GraphSetObjectClass(&axisPtr->obj, classId);
	} else if (axisPtr->obj.classId != classId) {
	    if (interp != NULL) {
  	        Tcl_AppendResult(interp, "axis \"", Tcl_GetString(objPtr),
		    "\" is already in use on an opposite ", 
			axisPtr->obj.className, "-axis", 
			(char *)NULL);
	    }
	    return TCL_ERROR;
	}
	axisPtr->refCount++;
    }
    *axisPtrPtr = axisPtr;
    return TCL_OK;
}

void
Blt_DestroyAxes(Graph *graphPtr)
{
    {
	Blt_HashEntry *hPtr;
	Blt_HashSearch cursor;

	for (hPtr = Blt_FirstHashEntry(&graphPtr->axes.table, &cursor);
	     hPtr != NULL; hPtr = Blt_NextHashEntry(&cursor)) {
	    Axis *axisPtr;
	    
	    axisPtr = Blt_GetHashValue(hPtr);
	    axisPtr->hashPtr = NULL;
	    DestroyAxis(axisPtr);
	}
    }
    Blt_DeleteHashTable(&graphPtr->axes.table);
    {
	int i;
	
	for (i = 0; i < 4; i++) {
	    Blt_Chain_Destroy(graphPtr->axisChain[i]);
	}
    }
    Blt_DeleteHashTable(&graphPtr->axes.tagTable);
    Blt_Chain_Destroy(graphPtr->axes.displayList);
}

int
Blt_DefaultAxes(Graph *graphPtr)
{
    int i;
    int flags;

    flags = Blt_GraphType(graphPtr);
    for (i = 0; i < 4; i++) {
	Blt_Chain chain;
	Axis *axisPtr;

	chain = Blt_Chain_Create();
	graphPtr->axisChain[i] = chain;

	/* Create a default axis for each chain. */
	axisPtr = CreateAxis(graphPtr, axisNames[i].name, i);
	if (axisPtr == NULL) {
	    return TCL_ERROR;
	}
	axisPtr->refCount = 1;	/* Default axes are assumed in use. */
	Blt_GraphSetObjectClass(&axisPtr->obj, axisNames[i].classId);
	axisPtr->flags |= AXIS_USE;

	/*
	 * Blt_ConfigureComponentFromObj creates a temporary child window 
	 * by the name of the axis.  It's used so that the Tk routines
	 * that access the X resource database can describe a single 
	 * component and not the entire graph.
	 */
 	if (Blt_ConfigureComponentFromObj(graphPtr->interp, graphPtr->tkwin,
		axisPtr->obj.name, "Axis", configSpecs, 0, (Tcl_Obj **)NULL,
		(char *)axisPtr, flags) != TCL_OK) {
	    return TCL_ERROR;
	}
	if (ConfigureAxis(axisPtr) != TCL_OK) {
	    return TCL_ERROR;
	}
	axisPtr->link = Blt_Chain_Append(chain, axisPtr);
	axisPtr->chain = chain;
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * ActivateOp --
 *
 * 	Activates the axis, drawing the axis with its -activeforeground,
 *	-activebackgound, -activerelief attributes.
 *
 * Results:
 *	A standard TCL result.
 *
 * Side Effects:
 *	Graph will be redrawn to reflect the new axis attributes.
 *
 *---------------------------------------------------------------------------
 */
static int
ActivateOp(Tcl_Interp *interp, Axis *axisPtr, int objc, Tcl_Obj *const *objv)
{
    Graph *graphPtr = axisPtr->obj.graphPtr;
    const char *string;

    string = Tcl_GetString(objv[2]);
    axisPtr->flags |= ACTIVE;
    if (string[0] == 'a') {
	axisPtr->flags |= ACTIVE;
    } else {
	axisPtr->flags &= ~ACTIVE;
    }
    if ((axisPtr->flags & (AXIS_USE|HIDE)) == AXIS_USE) {
	graphPtr->flags |= DRAW_MARGINS;
	Blt_EventuallyRedrawGraph(graphPtr);
    }
    return TCL_OK;
}

/*-------------------------------------------------------------------------------
 *
 * BindOp --
 *
 *    .g axis bind axisName sequence command
 *
 *---------------------------------------------------------------------------
 */
static int
BindOp(Tcl_Interp *interp, Axis *axisPtr, int objc, Tcl_Obj *const *objv)
{
    Graph *graphPtr = axisPtr->obj.graphPtr;

    return Blt_ConfigureBindingsFromObj(interp, graphPtr->bindTable,
          Blt_MakeAxisTag(graphPtr, axisPtr->obj.name), objc, objv);
}
          
/*
 *---------------------------------------------------------------------------
 *
 * CgetOp --
 *
 *	Queries axis attributes (font, line width, label, etc).
 *
 * Results:
 *	Return value is a standard TCL result.  If querying configuration
 *	values, interp->result will contain the results.
 *
 *---------------------------------------------------------------------------
 */
/* ARGSUSED */
static int
CgetOp(Tcl_Interp *interp, Axis *axisPtr, int objc, Tcl_Obj *const *objv)
{
    Graph *graphPtr = axisPtr->obj.graphPtr;

    return Blt_ConfigureValueFromObj(interp, graphPtr->tkwin, configSpecs,
	(char *)axisPtr, objv[0], Blt_GraphType(graphPtr));
}

/*
 *---------------------------------------------------------------------------
 *
 * ConfigureOp --
 *
 *	Queries or resets axis attributes (font, line width, label, etc).
 *
 * Results:
 *	Return value is a standard TCL result.  If querying configuration
 *	values, interp->result will contain the results.
 *
 * Side Effects:
 *	Axis resources are possibly allocated (GC, font). Axis layout is
 *	deferred until the height and width of the window are known.
 *
 *---------------------------------------------------------------------------
 */
static int
ConfigureOp(Tcl_Interp *interp, Axis *axisPtr, int objc, Tcl_Obj *const *objv)
{
    Graph *graphPtr = axisPtr->obj.graphPtr;
    int flags;

    flags = BLT_CONFIG_OBJV_ONLY | Blt_GraphType(graphPtr);
    if (objc == 0) {
	return Blt_ConfigureInfoFromObj(interp, graphPtr->tkwin, configSpecs,
	    (char *)axisPtr, (Tcl_Obj *)NULL, flags);
    } else if (objc == 1) {
	return Blt_ConfigureInfoFromObj(interp, graphPtr->tkwin, configSpecs,
	    (char *)axisPtr, objv[0], flags);
    }
    if (Blt_ConfigureWidgetFromObj(interp, graphPtr->tkwin, configSpecs, 
	objc, objv, (char *)axisPtr, flags) != TCL_OK) {
	return TCL_ERROR;
    }
    if (ConfigureAxis(axisPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if (axisPtr->flags & AXIS_USE) {
	if (!Blt_ConfigModified(configSpecs, "-*color", "-background", "-bg",
				(char *)NULL)) {
	    graphPtr->flags |= REDRAW_BACKING_STORE;
	}
	Blt_EventuallyRedrawGraph(graphPtr);
    }
    return TCL_OK;
}


/*
 *---------------------------------------------------------------------------
 *
 * LimitsOp --
 *
 *	This procedure returns a string representing the axis limits
 *	of the graph.  The format of the string is { left top right bottom}.
 *
 * Results:
 *	Always returns TCL_OK.  The interp->result field is
 *	a list of the graph axis limits.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
LimitsOp(Tcl_Interp *interp, Axis *axisPtr, int objc, Tcl_Obj *const *objv)
{
    Graph *graphPtr = axisPtr->obj.graphPtr;
    Tcl_Obj *listObjPtr;
    double min, max;

    if (graphPtr->flags & RESET_AXES) {
	Blt_ResetAxes(graphPtr);
    }
    if (axisPtr->logScale) {
	min = EXP10(axisPtr->axisRange.min);
	max = EXP10(axisPtr->axisRange.max);
    } else {
	min = axisPtr->axisRange.min;
	max = axisPtr->axisRange.max;
    }
    listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
    Tcl_ListObjAppendElement(interp, listObjPtr, Tcl_NewDoubleObj(min));
    Tcl_ListObjAppendElement(interp, listObjPtr, Tcl_NewDoubleObj(max));
    Tcl_SetObjResult(interp, listObjPtr);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * InvTransformOp --
 *
 *	Maps the given window coordinate into an axis-value.
 *
 * Results:
 *	Returns a standard TCL result.  interp->result contains
 *	the axis value. If an error occurred, TCL_ERROR is returned
 *	and interp->result will contain an error message.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
InvTransformOp(Tcl_Interp *interp, Axis *axisPtr, int objc, 
	       Tcl_Obj *const *objv)
{
    Graph *graphPtr = axisPtr->obj.graphPtr;
    double y;				/* Real graph coordinate */
    int sy;				/* Integer window coordinate*/

    if (graphPtr->flags & RESET_AXES) {
	Blt_ResetAxes(graphPtr);
    }
    if (Tcl_GetIntFromObj(interp, objv[0], &sy) != TCL_OK) {
	return TCL_ERROR;
    }
    /*
     * Is the axis vertical or horizontal?
     *
     * Check the site where the axis was positioned.  If the axis is
     * virtual, all we have to go on is how it was mapped to an
     * element (using either -mapx or -mapy options).  
     */
    if (AxisIsHorizontal(axisPtr)) {
	y = Blt_InvHMap(axisPtr, (double)sy);
    } else {
	y = Blt_InvVMap(axisPtr, (double)sy);
    }
    Tcl_SetDoubleObj(Tcl_GetObjResult(interp), y);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * TransformOp --
 *
 *	Maps the given axis-value to a window coordinate.
 *
 * Results:
 *	Returns a standard TCL result.  interp->result contains
 *	the window coordinate. If an error occurred, TCL_ERROR
 *	is returned and interp->result will contain an error
 *	message.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
TransformOp(Tcl_Interp *interp, Axis *axisPtr, int objc, Tcl_Obj *const *objv)
{
    Graph *graphPtr = axisPtr->obj.graphPtr;
    double x;

    if (graphPtr->flags & RESET_AXES) {
	Blt_ResetAxes(graphPtr);
    }
    if (Blt_ExprDoubleFromObj(interp, objv[0], &x) != TCL_OK) {
	return TCL_ERROR;
    }
    if (AxisIsHorizontal(axisPtr)) {
	x = Blt_HMap(axisPtr, x);
    } else {
	x = Blt_VMap(axisPtr, x);
    }
    Tcl_SetIntObj(Tcl_GetObjResult(interp), (int)x);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * UseOp --
 *
 *	Sets the default axis for a margin.
 *
 * Results:
 *	A standard TCL result.  If the named axis doesn't exist
 *	an error message is put in interp->result.
 *
 * .g xaxis use "abc def gah"
 * .g xaxis use [lappend abc [.g axis use]]
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
UseOp(Tcl_Interp *interp, Axis *axisPtr, int objc, Tcl_Obj *const *objv)
{
    Graph *graphPtr = axisPtr->obj.graphPtr;
    Blt_Chain chain;
    Blt_ChainLink link;
    Tcl_Obj **axisObjv;
    ClassId classId;
    int axisObjc;
    int i;

    chain = graphPtr->margins[lastMargin].axes;
    if (objc == 0) {
	Tcl_Obj *listObjPtr;

	listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
	for (link = Blt_Chain_FirstLink(chain); link != NULL;
	     link = Blt_Chain_NextLink(link)) {
	    axisPtr = Blt_Chain_GetValue(link);
	    Tcl_ListObjAppendElement(interp, listObjPtr,
		Tcl_NewStringObj(axisPtr->obj.name, -1));
	}
	Tcl_SetObjResult(interp, listObjPtr);
	return TCL_OK;
    }
    if ((lastMargin == MARGIN_BOTTOM) || (lastMargin == MARGIN_TOP)) {
	classId = (graphPtr->inverted) ? CID_AXIS_Y : CID_AXIS_X;
    } else {
	classId = (graphPtr->inverted) ? CID_AXIS_X : CID_AXIS_Y;
    }
    if (Tcl_ListObjGetElements(interp, objv[0], &axisObjc, &axisObjv) 
	!= TCL_OK) {
	return TCL_ERROR;
    }
    for (link = Blt_Chain_FirstLink(chain); link!= NULL; 
	 link = Blt_Chain_NextLink(link)) {
	axisPtr = Blt_Chain_GetValue(link);
	axisPtr->link = NULL;
	axisPtr->flags &= ~AXIS_USE;
	/* Clear the axis type if it's not currently used.*/
	if (axisPtr->refCount == 0) {
	    Blt_GraphSetObjectClass(&axisPtr->obj, CID_NONE);
	}
    }
    Blt_Chain_Reset(chain);
    for (i = 0; i < axisObjc; i++) {
	if (GetAxisFromObj(interp, graphPtr, axisObjv[i], &axisPtr) != TCL_OK){
	    return TCL_ERROR;
	}
	if (axisPtr->obj.classId == CID_NONE) {
	    Blt_GraphSetObjectClass(&axisPtr->obj, classId);
	} else if (axisPtr->obj.classId != classId) {
	    Tcl_AppendResult(interp, "wrong type axis \"", 
		axisPtr->obj.name, "\": can't use ", 
		axisPtr->obj.className, " type axis.", (char *)NULL); 
	    return TCL_ERROR;
	}
	if (axisPtr->link != NULL) {
	    /* Move the axis from the old margin's "use" list to the new. */
	    Blt_Chain_UnlinkLink(axisPtr->chain, axisPtr->link);
	    Blt_Chain_AppendLink(chain, axisPtr->link);
	} else {
	    axisPtr->link = Blt_Chain_Append(chain, axisPtr);
	}
	axisPtr->chain = chain;
	axisPtr->flags |= AXIS_USE;
    }
    graphPtr->flags |= (GET_AXIS_GEOMETRY | LAYOUT_NEEDED | RESET_AXES);
    /* When any axis changes, we need to layout the entire graph.  */
    graphPtr->flags |= (MAP_WORLD | REDRAW_WORLD);
    Blt_EventuallyRedrawGraph(graphPtr);
    return TCL_OK;
}

static int
ViewOp(Tcl_Interp *interp, Axis *axisPtr, int objc, Tcl_Obj *const *objv)
{
    Graph *graphPtr;
    double axisOffset, axisScale;
    double fract;
    double viewMin, viewMax, worldMin, worldMax;
    double viewWidth, worldWidth;

    graphPtr = axisPtr->obj.graphPtr;
    worldMin = axisPtr->valueRange.min;
    worldMax = axisPtr->valueRange.max;
    /* Override data dimensions with user-selected limits. */
    if (DEFINED(axisPtr->scrollMin)) {
	worldMin = axisPtr->scrollMin;
    }
    if (DEFINED(axisPtr->scrollMax)) {
	worldMax = axisPtr->scrollMax;
    }
    viewMin = axisPtr->min;
    viewMax = axisPtr->max;
    /* Bound the view within scroll region. */ 
    if (viewMin < worldMin) {
	viewMin = worldMin;
    } 
    if (viewMax > worldMax) {
	viewMax = worldMax;
    }
    if (axisPtr->logScale) {
	worldMin = log10(worldMin);
	worldMax = log10(worldMax);
	viewMin  = log10(viewMin);
	viewMax  = log10(viewMax);
    }
    worldWidth = worldMax - worldMin;
    viewWidth  = viewMax - viewMin;

    /* Unlike horizontal axes, vertical axis values run opposite of the
     * scrollbar first/last values.  So instead of pushing the axis minimum
     * around, we move the maximum instead. */
    if (AxisIsHorizontal(axisPtr) != axisPtr->descending) {
	axisOffset  = viewMin - worldMin;
	axisScale = graphPtr->hScale;
    } else {
	axisOffset  = worldMax - viewMax;
	axisScale = graphPtr->vScale;
    }
    if (objc == 4) {
	Tcl_Obj *listObjPtr;
	double first, last;

	first = Clamp(axisOffset / worldWidth);
	last = Clamp((axisOffset + viewWidth) / worldWidth);
	listObjPtr = Tcl_NewListObj(0, NULL);
	Tcl_ListObjAppendElement(interp, listObjPtr, Tcl_NewDoubleObj(first));
	Tcl_ListObjAppendElement(interp, listObjPtr, Tcl_NewDoubleObj(last));
	Tcl_SetObjResult(interp, listObjPtr);
	return TCL_OK;
    }
    fract = axisOffset / worldWidth;
    if (GetAxisScrollInfo(interp, objc, objv, &fract, 
	viewWidth / worldWidth, axisPtr->scrollUnits, axisScale) != TCL_OK) {
	return TCL_ERROR;
    }
    if (AxisIsHorizontal(axisPtr) != axisPtr->descending) {
	axisPtr->reqMin = (fract * worldWidth) + worldMin;
	axisPtr->reqMax = axisPtr->reqMin + viewWidth;
    } else {
	axisPtr->reqMax = worldMax - (fract * worldWidth);
	axisPtr->reqMin = axisPtr->reqMax - viewWidth;
    }
    if (axisPtr->logScale) {
	axisPtr->reqMin = EXP10(axisPtr->reqMin);
	axisPtr->reqMax = EXP10(axisPtr->reqMax);
    }
    graphPtr->flags |= (GET_AXIS_GEOMETRY | LAYOUT_NEEDED | RESET_AXES);
    Blt_EventuallyRedrawGraph(graphPtr);
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * AxisCreateOp --
 *
 *	Creates a new axis.
 *
 * Results:
 *	Returns a standard TCL result.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
AxisCreateOp(Tcl_Interp *interp, Graph *graphPtr, int objc, 
	     Tcl_Obj *const *objv)
{
    Axis *axisPtr;
    int flags;

    axisPtr = CreateAxis(graphPtr, Tcl_GetString(objv[3]), MARGIN_NONE);
    if (axisPtr == NULL) {
	return TCL_ERROR;
    }
    flags = Blt_GraphType(graphPtr);
    if ((Blt_ConfigureComponentFromObj(interp, graphPtr->tkwin, 
	axisPtr->obj.name, "Axis", configSpecs, objc - 4, objv + 4, 
	(char *)axisPtr, flags) != TCL_OK) || 
	(ConfigureAxis(axisPtr) != TCL_OK)) {
	DestroyAxis(axisPtr);
	return TCL_ERROR;
    }
    Tcl_SetStringObj(Tcl_GetObjResult(interp), axisPtr->obj.name, -1);
    return TCL_OK;
}
/*
 *---------------------------------------------------------------------------
 *
 * AxisActivateOp --
 *
 * 	Activates the axis, drawing the axis with its -activeforeground,
 *	-activebackgound, -activerelief attributes.
 *
 * Results:
 *	A standard TCL result.
 *
 * Side Effects:
 *	Graph will be redrawn to reflect the new axis attributes.
 *
 *---------------------------------------------------------------------------
 */
static int
AxisActivateOp(Tcl_Interp *interp, Graph *graphPtr, int objc, 
	       Tcl_Obj *const *objv)
{
    Axis *axisPtr;

    if (GetAxisFromObj(interp, graphPtr, objv[3], &axisPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    return ActivateOp(interp, axisPtr, objc, objv);
}


/*-------------------------------------------------------------------------------
 *
 * AxisBindOp --
 *
 *    .g axis bind axisName sequence command
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
AxisBindOp(Tcl_Interp *interp, Graph *graphPtr, int objc, 
	      Tcl_Obj *const *objv)
{
    if (objc == 3) {
	Blt_HashEntry *hPtr;
	Blt_HashSearch cursor;
	Tcl_Obj *listObjPtr;

	listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
	for (hPtr = Blt_FirstHashEntry(&graphPtr->axes.tagTable, &cursor);
	     hPtr != NULL; hPtr = Blt_NextHashEntry(&cursor)) {
	    const char *tagName;
	    Tcl_Obj *objPtr;

	    tagName = Blt_GetHashKey(&graphPtr->axes.tagTable, hPtr);
	    objPtr = Tcl_NewStringObj(tagName, -1);
	    Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	}
	Tcl_SetObjResult(interp, listObjPtr);
	return TCL_OK;
    }
    return Blt_ConfigureBindingsFromObj(interp, graphPtr->bindTable, 
	Blt_MakeAxisTag(graphPtr, Tcl_GetString(objv[3])), objc - 4, objv + 4);
}


/*
 *---------------------------------------------------------------------------
 *
 * AxisCgetOp --
 *
 *	Queries axis attributes (font, line width, label, etc).
 *
 * Results:
 *	Return value is a standard TCL result.  If querying configuration
 *	values, interp->result will contain the results.
 *
 *---------------------------------------------------------------------------
 */
/* ARGSUSED */
static int
AxisCgetOp(Tcl_Interp *interp, Graph *graphPtr, int objc, Tcl_Obj *const *objv)
{
    Axis *axisPtr;

    if (GetAxisFromObj(interp, graphPtr, objv[3], &axisPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    return CgetOp(interp, axisPtr, objc - 4, objv + 4);
}

/*
 *---------------------------------------------------------------------------
 *
 * AxisConfigureOp --
 *
 *	Queries or resets axis attributes (font, line width, label, etc).
 *
 * Results:
 *	Return value is a standard TCL result.  If querying configuration
 *	values, interp->result will contain the results.
 *
 * Side Effects:
 *	Axis resources are possibly allocated (GC, font). Axis layout is
 *	deferred until the height and width of the window are known.
 *
 *---------------------------------------------------------------------------
 */
static int
AxisConfigureOp(Tcl_Interp *interp, Graph *graphPtr, int objc, 
		Tcl_Obj *const *objv)
{
    Tcl_Obj *const *options;
    int i;
    int nNames, nOpts;

    /* Figure out where the option value pairs begin */
    objc -= 3;
    objv += 3;
    for (i = 0; i < objc; i++) {
	Axis *axisPtr;
	const char *string;

	string = Tcl_GetString(objv[i]);
	if (string[0] == '-') {
	    break;
	}
	if (GetAxisFromObj(interp, graphPtr, objv[i], &axisPtr) != TCL_OK) {
	    return TCL_ERROR;
	}
    }
    nNames = i;				/* Number of pen names specified */
    nOpts = objc - i;			/* Number of options specified */
    options = objv + i;			/* Start of options in objv  */

    for (i = 0; i < nNames; i++) {
	Axis *axisPtr;

	if (GetAxisFromObj(interp, graphPtr, objv[i], &axisPtr) != TCL_OK) {
	    return TCL_ERROR;
	}
	if (ConfigureOp(interp, axisPtr, nOpts, options) != TCL_OK) {
	    break;
	}
    }
    if (i < nNames) {
	return TCL_ERROR;
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * AxisDeleteOp --
 *
 *	Deletes one or more axes.  The actual removal may be deferred until the
 *	axis is no longer used by any element. The axis can't be referenced by
 *	its name any longer and it may be recreated.
 *
 * Results:
 *	Returns a standard TCL result.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
AxisDeleteOp(Tcl_Interp *interp, Graph *graphPtr, int objc, 
	     Tcl_Obj *const *objv)
{
    int i;

    for (i = 3; i < objc; i++) {
	Axis *axisPtr;

	if (GetAxisFromObj(interp, graphPtr, objv[i], &axisPtr) != TCL_OK) {
	    return TCL_ERROR;
	}
	axisPtr->flags |= DELETE_PENDING;
	if (axisPtr->refCount == 0) {
	    Tcl_EventuallyFree(axisPtr, FreeAxis);
	}
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * AxisFocusOp --
 *
 * 	Activates the axis, drawing the axis with its -activeforeground,
 *	-activebackgound, -activerelief attributes.
 *
 * Results:
 *	A standard TCL result.
 *
 * Side Effects:
 *	Graph will be redrawn to reflect the new axis attributes.
 *
 *---------------------------------------------------------------------------
 */
static int
AxisFocusOp(Tcl_Interp *interp, Graph *graphPtr, int objc, Tcl_Obj *const *objv)
{
    if (objc > 3) {
	Axis *axisPtr;
	const char *string;

	axisPtr = NULL;
	string = Tcl_GetString(objv[3]);
	if ((string[0] != '\0') && 
	    (GetAxisFromObj(interp, graphPtr, objv[3], &axisPtr) != TCL_OK)) {
	    return TCL_ERROR;
	}
	graphPtr->focusPtr = NULL;
	if ((axisPtr != NULL) && 
	    ((axisPtr->flags & (AXIS_USE|HIDE)) == AXIS_USE)) {
	    graphPtr->focusPtr = axisPtr;
	}
	Blt_SetFocusItem(graphPtr->bindTable, graphPtr->focusPtr, NULL);
    }
    /* Return the name of the axis that has focus. */
    if (graphPtr->focusPtr != NULL) {
	Tcl_SetStringObj(Tcl_GetObjResult(interp), 
		graphPtr->focusPtr->obj.name, -1);
    }
    return TCL_OK;
}


/*
 *---------------------------------------------------------------------------
 *
 * AxisGetOp --
 *
 *    Returns the name of the picked axis (using the axis bind operation).
 *    Right now, the only name accepted is "current".
 *
 * Results:
 *    A standard TCL result.  The interpreter result will contain the name of
 *    the axis.
 *
 *---------------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
AxisGetOp(Tcl_Interp *interp, Graph *graphPtr, int objc, Tcl_Obj *const *objv)
{
    Axis *axisPtr;

    axisPtr = Blt_GetCurrentItem(graphPtr->bindTable);
    /* Report only on axes. */
    if ((axisPtr != NULL) && 
	((axisPtr->obj.classId == CID_AXIS_X) || 
	 (axisPtr->obj.classId == CID_AXIS_Y) || 
	 (axisPtr->obj.classId == CID_NONE))) {
	char c;
	char  *string;

	string = Tcl_GetString(objv[3]);
	c = string[0];
	if ((c == 'c') && (strcmp(string, "current") == 0)) {
	    Tcl_SetStringObj(Tcl_GetObjResult(interp), axisPtr->obj.name,-1);
	} else if ((c == 'd') && (strcmp(string, "detail") == 0)) {
	    Tcl_SetStringObj(Tcl_GetObjResult(interp), axisPtr->detail, -1);
	}
    }
    return TCL_OK;
}

/*
 *---------------------------------------------------------------------------
 *
 * AxisInvTransformOp --
 *
 *	Maps the given window coordinate into an axis-value.
 *
 * Results:
 *	Returns a standard TCL result.  interp->result contains
 *	the axis value. If an error occurred, TCL_ERROR is returned
 *	and interp->result will contain an error message.
 *
 *---------------------------------------------------------------------------
 */
static int
AxisInvTransformOp(Tcl_Interp *interp, Graph *graphPtr, int objc, 
		   Tcl_Obj *const *objv)
{
    Axis *axisPtr;

    if (GetAxisFromObj(interp, graphPtr, objv[3], &axisPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    return InvTransformOp(interp, axisPtr, objc - 4, objv + 4);
}

/*
 *---------------------------------------------------------------------------
 *
 * AxisLimitsOp --
 *
 *	This procedure returns a string representing the axis limits of the
 *	graph.  The format of the string is { left top right bottom}.
 *
 * Results:
 *	Always returns TCL_OK.  The interp->result field is
 *	a list of the graph axis limits.
 *
 *---------------------------------------------------------------------------
 */
static int
AxisLimitsOp(Tcl_Interp *interp, Graph *graphPtr, int objc, 
	     Tcl_Obj *const *objv)
{
    Axis *axisPtr;

    if (GetAxisFromObj(interp, graphPtr, objv[3], &axisPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    return LimitsOp(interp, axisPtr, objc - 4, objv + 4);
}

/*
 *---------------------------------------------------------------------------
 *
 * AxisNamesOp --
 *
 *	Return a list of the names of all the axes.
 *
 * Results:
 *	Returns a standard TCL result.
 *
 *---------------------------------------------------------------------------
 */

/*ARGSUSED*/
static int
AxisNamesOp(Tcl_Interp *interp, Graph *graphPtr, int objc, Tcl_Obj *const *objv)
{
    Tcl_Obj *listObjPtr;

    listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
    if (objc == 3) {
	Blt_HashEntry *hPtr;
	Blt_HashSearch cursor;

	for (hPtr = Blt_FirstHashEntry(&graphPtr->axes.table, &cursor);
	     hPtr != NULL; hPtr = Blt_NextHashEntry(&cursor)) {
	    Axis *axisPtr;

	    axisPtr = Blt_GetHashValue(hPtr);
	    if (axisPtr->flags & DELETE_PENDING) {
		continue;
	    }
	    Tcl_ListObjAppendElement(interp, listObjPtr, 
		     Tcl_NewStringObj(axisPtr->obj.name, -1));
	}
    } else {
	Blt_HashEntry *hPtr;
	Blt_HashSearch cursor;

	for (hPtr = Blt_FirstHashEntry(&graphPtr->axes.table, &cursor);
	     hPtr != NULL; hPtr = Blt_NextHashEntry(&cursor)) {
	    Axis *axisPtr;
	    int i;

	    axisPtr = Blt_GetHashValue(hPtr);
	    for (i = 3; i < objc; i++) {
		const char *pattern;

		pattern = Tcl_GetString(objv[i]);
		if (Tcl_StringMatch(axisPtr->obj.name, pattern)) {
		    Tcl_ListObjAppendElement(interp, listObjPtr, 
			Tcl_NewStringObj(axisPtr->obj.name, -1));
		    break;
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
 * AxisTransformOp --
 *
 *	Maps the given axis-value to a window coordinate.
 *
 * Results:
 *	Returns the window coordinate via interp->result.  If an error occurred,
 *	TCL_ERROR is returned and interp->result will contain an error message.
 *
 *---------------------------------------------------------------------------
 */
static int
AxisTransformOp(Tcl_Interp *interp, Graph *graphPtr, int objc, 
		Tcl_Obj *const *objv)
{
    Axis *axisPtr;

    if (GetAxisFromObj(interp, graphPtr, objv[3], &axisPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    return TransformOp(interp, axisPtr, objc - 4, objv + 4);
}

static int
AxisViewOp(Tcl_Interp *interp, Graph *graphPtr, int objc, Tcl_Obj *const *objv)
{
    Axis *axisPtr;

    if (GetAxisFromObj(interp, graphPtr, objv[3], &axisPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    return ViewOp(interp, axisPtr, objc - 4, objv + 4);
}

static Blt_OpSpec virtAxisOps[] = {
    {"activate",     1, AxisActivateOp,     4, 4, "axisName"},
    {"bind",         1, AxisBindOp,         3, 6, "axisName sequence command"},
    {"cget",         2, AxisCgetOp,         5, 5, "axisName option"},
    {"configure",    2, AxisConfigureOp,    4, 0, "axisName ?axisName?... "
	"?option value?..."},
    {"create",       2, AxisCreateOp,       4, 0, "axisName ?option value?..."},
    {"deactivate",   3, AxisActivateOp,     4, 4, "axisName"},
    {"delete",       3, AxisDeleteOp,       3, 0, "?axisName?..."},
    {"focus",        1, AxisFocusOp,        3, 4, "?axisName?"},
    {"get",          1, AxisGetOp,          4, 4, "name"},
    {"invtransform", 1, AxisInvTransformOp, 5, 5, "axisName value"},
    {"limits",       1, AxisLimitsOp,       4, 4, "axisName"},
    {"names",        1, AxisNamesOp,        3, 0, "?pattern?..."},
    {"transform",    1, AxisTransformOp,    5, 5, "axisName value"},
    {"view",         1, AxisViewOp,         4, 7, "axisName ?moveto fract? "
	"?scroll number what?"},
};
static int nVirtAxisOps = sizeof(virtAxisOps) / sizeof(Blt_OpSpec);

int
Blt_VirtualAxisOp(Graph *graphPtr, Tcl_Interp *interp, int objc, 
		  Tcl_Obj *const *objv)
{
    GraphVirtualAxisProc *proc;
    int result;

    proc = Blt_GetOpFromObj(interp, nVirtAxisOps, virtAxisOps, BLT_OP_ARG2, 
	objc, objv, 0);
    if (proc == NULL) {
	return TCL_ERROR;
    }
    result = (*proc) (interp, graphPtr, objc, objv);
    return result;
}

static Blt_OpSpec axisOps[] = {
    {"activate",     1, ActivateOp,     3, 3, "",},
    {"bind",         1, BindOp,         2, 5, "sequence command",},
    {"cget",         2, CgetOp,         4, 4, "option",},
    {"configure",    2, ConfigureOp,    3, 0, "?option value?...",},
    {"deactivate",   1, ActivateOp,     3, 3, "",},
    {"invtransform", 1, InvTransformOp, 4, 4, "value",},
    {"limits",       1, LimitsOp,       3, 3, "",},
    {"transform",    1, TransformOp,    4, 4, "value",},
    {"use",          1, UseOp,          3, 4, "?axisName?",},
    {"view",         1, ViewOp,         3, 6, "?moveto fract? ",},
};

static int nAxisOps = sizeof(axisOps) / sizeof(Blt_OpSpec);

int
Blt_AxisOp(Tcl_Interp *interp, Graph *graphPtr, int margin, int objc,
	   Tcl_Obj *const *objv)
{
    int result;
    GraphAxisProc *proc;
    Axis *axisPtr;

    proc = Blt_GetOpFromObj(interp, nAxisOps, axisOps, BLT_OP_ARG2, objc, objv,
	0);
    if (proc == NULL) {
	return TCL_ERROR;
    }
    lastMargin = margin;		/* Set global variable to the margin in
					 * the argument list. Needed only for
					 * UseOp. */
    axisPtr = Blt_GetFirstAxis(graphPtr->margins[margin].axes);
    if (axisPtr == NULL) {
	Tcl_AppendResult(interp, "no axes used on ", Tcl_GetString(objv[1]),
			 (char *)NULL);
	return TCL_ERROR;
    }
    result = (*proc)(interp, axisPtr, objc - 3, objv + 3);
    return result;
}

void
Blt_MapAxes(Graph *graphPtr)
{
    int margin;
    
    for (margin = 0; margin < 4; margin++) {
	Blt_Chain chain;
	Blt_ChainLink link;
	int count, offset;

	chain = graphPtr->margins[margin].axes;
	count = offset = 0;
	for (link = Blt_Chain_FirstLink(chain); link != NULL; 
	     link = Blt_Chain_NextLink(link)) {
	    Axis *axisPtr;

	    axisPtr = Blt_Chain_GetValue(link);
	    if ((axisPtr->flags & (AXIS_USE|DELETE_PENDING)) != AXIS_USE) {
		continue;
	    }
	    if (graphPtr->stackAxes) {
		axisPtr->reqNumMajorTicks = 4;
		MapStackedAxis(axisPtr, count, margin);
	    } else {
		axisPtr->reqNumMajorTicks = 10;
		MapAxis(axisPtr, offset, margin);
	    }
	    if (axisPtr->flags & AXIS_GRID) {
		MapGridlines(axisPtr);
	    }
	    offset += (AxisIsHorizontal(axisPtr)) 
		? axisPtr->height : axisPtr->width;
	    count++;
	}
    }
}

void
Blt_DrawAxes(Graph *graphPtr, Drawable drawable)
{
    int i;

    for (i = 0; i < 4; i++) {
	Blt_ChainLink link;

	for (link = Blt_Chain_LastLink(graphPtr->margins[i].axes); 
	     link != NULL; link = Blt_Chain_PrevLink(link)) {
	    Axis *axisPtr;

	    axisPtr = Blt_Chain_GetValue(link);
	    if ((axisPtr->flags & (DELETE_PENDING|HIDE|AXIS_USE)) == AXIS_USE) {
		DrawAxis(axisPtr, drawable);
	    }
	}
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_DrawGrids --
 *
 *	Draws the grid lines associated with each axis.
 *
 * Results:
 *	None.
 *
 *---------------------------------------------------------------------------
 */
void
Blt_DrawGrids(Graph *graphPtr, Drawable drawable) 
{
    int i;

    for (i = 0; i < 4; i++) {
	Blt_ChainLink link;

	for (link = Blt_Chain_FirstLink(graphPtr->margins[i].axes); link != NULL;
	     link = Blt_Chain_NextLink(link)) {
	    Axis *axisPtr;

	    axisPtr = Blt_Chain_GetValue(link);
	    if (axisPtr->flags & (DELETE_PENDING|HIDE)) {
		continue;
	    }
	    if ((axisPtr->flags & AXIS_USE) && (axisPtr->flags & AXIS_GRID)) {
		Blt_Draw2DSegments(graphPtr->display, drawable, 
				   axisPtr->major.gc, axisPtr->major.segments, 
				   axisPtr->major.nUsed);
		if (axisPtr->flags & AXIS_GRID_MINOR) {
		    Blt_Draw2DSegments(graphPtr->display, drawable, 
			axisPtr->minor.gc, axisPtr->minor.segments, 
			axisPtr->minor.nUsed);
		}
	    }
	}
    }
}

/*
 *---------------------------------------------------------------------------
 *
 * Blt_GridsToPostScript --
 *
 *	Draws the grid lines associated with each axis.
 *
 * Results:
 *	None.
 *
 *---------------------------------------------------------------------------
 */
void
Blt_GridsToPostScript(Graph *graphPtr, Blt_Ps ps) 
{
    int i;

    for (i = 0; i < 4; i++) {
	Blt_ChainLink link;

	for (link = Blt_Chain_FirstLink(graphPtr->margins[i].axes); link != NULL;
	     link = Blt_Chain_NextLink(link)) {
	    Axis *axisPtr;

	    axisPtr = Blt_Chain_GetValue(link);
	    if ((axisPtr->flags & (DELETE_PENDING|HIDE|AXIS_USE|AXIS_GRID)) !=
		(AXIS_GRID|AXIS_USE)) {
		continue;
	    }
	    Blt_Ps_Format(ps, "%% Axis %s: grid line attributes\n",
		axisPtr->obj.name);
	    Blt_Ps_XSetLineAttributes(ps, axisPtr->major.color, 
		axisPtr->major.lineWidth, &axisPtr->major.dashes, CapButt, 
		JoinMiter);
	    Blt_Ps_Format(ps, "%% Axis %s: major grid line segments\n",
		axisPtr->obj.name);
	    Blt_Ps_Draw2DSegments(ps, axisPtr->major.segments, 
				  axisPtr->major.nUsed);
	    if (axisPtr->flags & AXIS_GRID_MINOR) {
		Blt_Ps_XSetLineAttributes(ps, axisPtr->minor.color, 
		    axisPtr->minor.lineWidth, &axisPtr->minor.dashes, CapButt, 
		    JoinMiter);
		Blt_Ps_Format(ps, "%% Axis %s: minor grid line segments\n",
			axisPtr->obj.name);
		Blt_Ps_Draw2DSegments(ps, axisPtr->minor.segments, 
			axisPtr->minor.nUsed);
	    }
	}
    }
}

void
Blt_AxesToPostScript(Graph *graphPtr, Blt_Ps ps) 
{
    int i;

    for (i = 0; i < 4; i++) {
	Blt_ChainLink link;

	for (link = Blt_Chain_FirstLink(graphPtr->margins[i].axes); 
	     link != NULL; link = Blt_Chain_NextLink(link)) {
	    Axis *axisPtr;

	    axisPtr = Blt_Chain_GetValue(link);
	    if (axisPtr->flags & (DELETE_PENDING|HIDE)) {
		continue;
	    }
	    if (axisPtr->flags & AXIS_USE) {
		AxisToPostScript(ps, axisPtr);
	    }
	}
    }
}


/*
 *---------------------------------------------------------------------------
 *
 * Blt_DrawAxisLimits --
 *
 *	Draws the min/max values of the axis in the plotting area.  The text
 *	strings are formatted according to the "sprintf" format descriptors in
 *	the limitsFormats array.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Draws the numeric values of the axis limits into the outer regions of
 *	the plotting area.
 *
 *---------------------------------------------------------------------------
 */
void
Blt_DrawAxisLimits(Graph *graphPtr, Drawable drawable)
{
    Blt_HashEntry *hPtr;
    Blt_HashSearch cursor;
    char minString[200], maxString[200];
    int vMin, hMin, vMax, hMax;

#define SPACING 8
    vMin = vMax = graphPtr->left + graphPtr->padLeft + 2;
    hMin = hMax = graphPtr->bottom - graphPtr->padBottom - 2;	/* Offsets */

    for (hPtr = Blt_FirstHashEntry(&graphPtr->axes.table, &cursor);
	hPtr != NULL; hPtr = Blt_NextHashEntry(&cursor)) {
	Axis *axisPtr;
	Dim2D textDim;
	const char *minFmt, *maxFmt;
	char *minPtr, *maxPtr;
	int isHoriz;

	axisPtr = Blt_GetHashValue(hPtr);
	if (axisPtr->flags & DELETE_PENDING) {
	    continue;
	} 
	if (axisPtr->nFormats == 0) {
	    continue;
	}
	isHoriz = AxisIsHorizontal(axisPtr);
	minPtr = maxPtr = NULL;
	minFmt = maxFmt = axisPtr->limitsFormats[0];
	if (axisPtr->nFormats > 1) {
	    maxFmt = axisPtr->limitsFormats[1];
	}
	if (minFmt[0] != '\0') {
	    minPtr = minString;
	    sprintf_s(minString, 200, minFmt, axisPtr->axisRange.min);
	}
	if (maxFmt[0] != '\0') {
	    maxPtr = maxString;
	    sprintf_s(maxString, 200, maxFmt, axisPtr->axisRange.max);
	}
	if (axisPtr->descending) {
	    char *tmp;

	    tmp = minPtr, minPtr = maxPtr, maxPtr = tmp;
	}
	if (maxPtr != NULL) {
	    if (isHoriz) {
		Blt_Ts_SetAngle(axisPtr->limitsTextStyle, 90.0);
		Blt_Ts_SetAnchor(axisPtr->limitsTextStyle, TK_ANCHOR_SE);
		Blt_DrawText2(graphPtr->tkwin, drawable, maxPtr,
		    &axisPtr->limitsTextStyle, graphPtr->right, hMax, &textDim);
		hMax -= (textDim.height + SPACING);
	    } else {
		Blt_Ts_SetAngle(axisPtr->limitsTextStyle, 0.0);
		Blt_Ts_SetAnchor(axisPtr->limitsTextStyle, TK_ANCHOR_NW);
		Blt_DrawText2(graphPtr->tkwin, drawable, maxPtr,
		    &axisPtr->limitsTextStyle, vMax, graphPtr->top, &textDim);
		vMax += (textDim.width + SPACING);
	    }
	}
	if (minPtr != NULL) {
	    Blt_Ts_SetAnchor(axisPtr->limitsTextStyle, TK_ANCHOR_SW);
	    if (isHoriz) {
		Blt_Ts_SetAngle(axisPtr->limitsTextStyle, 90.0);
		Blt_DrawText2(graphPtr->tkwin, drawable, minPtr,
		    &axisPtr->limitsTextStyle, graphPtr->left, hMin, &textDim);
		hMin -= (textDim.height + SPACING);
	    } else {
		Blt_Ts_SetAngle(axisPtr->limitsTextStyle, 0.0);
		Blt_DrawText2(graphPtr->tkwin, drawable, minPtr,
		    &axisPtr->limitsTextStyle, vMin, graphPtr->bottom, &textDim);
		vMin += (textDim.width + SPACING);
	    }
	}
    } /* Loop on axes */
}

void
Blt_AxisLimitsToPostScript(Graph *graphPtr, Blt_Ps ps)
{
    Blt_HashEntry *hPtr;
    Blt_HashSearch cursor;
    double vMin, hMin, vMax, hMax;
    char string[200];

#define SPACING 8
    vMin = vMax = graphPtr->left + graphPtr->padLeft + 2;
    hMin = hMax = graphPtr->bottom - graphPtr->padBottom - 2;	/* Offsets */
    for (hPtr = Blt_FirstHashEntry(&graphPtr->axes.table, &cursor);
	 hPtr != NULL; hPtr = Blt_NextHashEntry(&cursor)) {
	Axis *axisPtr;
	const char *minFmt, *maxFmt;
	unsigned int textWidth, textHeight;

	axisPtr = Blt_GetHashValue(hPtr);
	if (axisPtr->flags & DELETE_PENDING) {
	    continue;
	} 
	if (axisPtr->nFormats == 0) {
	    continue;
	}
	minFmt = maxFmt = axisPtr->limitsFormats[0];
	if (axisPtr->nFormats > 1) {
	    maxFmt = axisPtr->limitsFormats[1];
	}
	if (*maxFmt != '\0') {
	    sprintf_s(string, 200, maxFmt, axisPtr->axisRange.max);
	    Blt_GetTextExtents(axisPtr->tickFont, 0, string, -1, &textWidth,
		&textHeight);
	    if ((textWidth > 0) && (textHeight > 0)) {
		if (axisPtr->obj.classId == CID_AXIS_X) {
		    Blt_Ts_SetAngle(axisPtr->limitsTextStyle, 90.0);
		    Blt_Ts_SetAnchor(axisPtr->limitsTextStyle, TK_ANCHOR_SE);
		    Blt_Ps_DrawText(ps, string, &axisPtr->limitsTextStyle, 
			(double)graphPtr->right, hMax);
		    hMax -= (textWidth + SPACING);
		} else {
		    Blt_Ts_SetAngle(axisPtr->limitsTextStyle, 0.0);
		    Blt_Ts_SetAnchor(axisPtr->limitsTextStyle, TK_ANCHOR_NW);
		    Blt_Ps_DrawText(ps, string, &axisPtr->limitsTextStyle,
			vMax, (double)graphPtr->top);
		    vMax += (textWidth + SPACING);
		}
	    }
	}
	if (*minFmt != '\0') {
	    sprintf_s(string, 200, minFmt, axisPtr->axisRange.min);
	    Blt_GetTextExtents(axisPtr->tickFont, 0, string, -1, &textWidth,
		&textHeight);
	    if ((textWidth > 0) && (textHeight > 0)) {
		Blt_Ts_SetAnchor(axisPtr->limitsTextStyle, TK_ANCHOR_SW);
		if (axisPtr->obj.classId == CID_AXIS_X) {
		    Blt_Ts_SetAngle(axisPtr->limitsTextStyle, 90.0);
		    Blt_Ps_DrawText(ps, string, &axisPtr->limitsTextStyle, 
			(double)graphPtr->left, hMin);
		    hMin -= (textWidth + SPACING);
		} else {
		    Blt_Ts_SetAngle(axisPtr->limitsTextStyle, 0.0);
		    Blt_Ps_DrawText(ps, string, &axisPtr->limitsTextStyle, 
			vMin, (double)graphPtr->bottom);
		    vMin += (textWidth + SPACING);
		}
	    }
	}
    }
}

Axis *
Blt_GetFirstAxis(Blt_Chain chain)
{
    Blt_ChainLink link;

    link = Blt_Chain_FirstLink(chain);
    if (link == NULL) {
	return NULL;
    }
    return Blt_Chain_GetValue(link);
}

Axis *
Blt_NearestAxis(Graph *graphPtr, int x, int y)
{
    Blt_HashEntry *hPtr;
    Blt_HashSearch cursor;
    
    for (hPtr = Blt_FirstHashEntry(&graphPtr->axes.table, &cursor); 
	 hPtr != NULL; hPtr = Blt_NextHashEntry(&cursor)) {
	Axis *axisPtr;

	axisPtr = Blt_GetHashValue(hPtr);
	if ((axisPtr->flags & (DELETE_PENDING|HIDE|AXIS_USE)) != AXIS_USE) {
	    continue;
	}
	if (axisPtr->flags & AXIS_TICKS) {
	    Blt_ChainLink link;

	    for (link = Blt_Chain_FirstLink(axisPtr->tickLabels); link != NULL; 
		 link = Blt_Chain_NextLink(link)) {	
		TickLabel *labelPtr;
		Point2d t;
		double rw, rh;
		Point2d bbox[5];

		labelPtr = Blt_Chain_GetValue(link);
		Blt_GetBoundingBox(labelPtr->width, labelPtr->height, 
			axisPtr->tickAngle, &rw, &rh, bbox);
		t = Blt_AnchorPoint(labelPtr->anchorPos.x, 
			labelPtr->anchorPos.y, rw, rh, axisPtr->tickAnchor);
		t.x = x - t.x - (rw * 0.5);
		t.y = y - t.y - (rh * 0.5);

		bbox[4] = bbox[0];
		if (Blt_PointInPolygon(&t, bbox, 5)) {
		    axisPtr->detail = "label";
		    return axisPtr;
		}
	    }
	}
	if (axisPtr->title != NULL) {	/* and then the title string. */
	    Point2d bbox[5];
	    Point2d t;
	    double rw, rh;
	    unsigned int w, h;

	    Blt_GetTextExtents(axisPtr->titleFont, 0, axisPtr->title,-1,&w,&h);
	    Blt_GetBoundingBox(w, h, axisPtr->titleAngle, &rw, &rh, bbox);
	    t = Blt_AnchorPoint(axisPtr->titlePos.x, axisPtr->titlePos.y, 
		rw, rh, axisPtr->titleAnchor);
	    /* Translate the point so that the 0,0 is the upper left 
	     * corner of the bounding box.  */
	    t.x = x - t.x - (rw * 0.5);
	    t.y = y - t.y - (rh * 0.5);
	    
	    bbox[4] = bbox[0];
	    if (Blt_PointInPolygon(&t, bbox, 5)) {
		axisPtr->detail = "title";
		return axisPtr;
	    }
	}
	if (axisPtr->lineWidth > 0) {	/* Check for the axis region */
	    if ((x <= axisPtr->right) && (x >= axisPtr->left) && 
		(y <= axisPtr->bottom) && (y >= axisPtr->top)) {
		axisPtr->detail = "line";
		return axisPtr;
	    }
	}
    }
    return NULL;
}
 
ClientData
Blt_MakeAxisTag(Graph *graphPtr, const char *tagName)
{
    Blt_HashEntry *hPtr;
    int isNew;

    hPtr = Blt_CreateHashEntry(&graphPtr->axes.tagTable, tagName, &isNew);
    return Blt_GetHashKey(&graphPtr->axes.tagTable, hPtr);
}

