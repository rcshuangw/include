﻿#ifndef HGRIDCTRLDEF_H_
#define HGRIDCTRLDEF_H_
//c++
#include <exception>
using namespace std;
//qt define
#include <QApplication>
#include <QtGlobal>
#include <QObject>
#include <QWidget>
#include <QAbstractScrollArea>
#include <QColor>
#include <QRgb>
#include <QFont>
#include <QSize>
#include <QMap>
#include <QPainter>
#include <QKeyEvent>
#include <QClipboard>
#include <QScrollBar>
#include <QLineEdit>
#include <QMimeData>
#include <math.h>
#include <iterator>
#include "hcellrange.h"
typedef unsigned int HWPARAM;
typedef qlonglong HLPARAM; //统一64位平台

const int ROWMAX_COUNT = 999;
const int COLMAX_COUNT = 999;
//颜色定义 参考windos系统
/*
 * 基础颜色参考windows系统，防止与windows已有定义冲突，所有在原定义前面加入Q
*/
const Q_DECL_UNUSED QRgb  QCLR_NONE                         = 0xFFFFFFFFL; //no
const Q_DECL_UNUSED QRgb  QCLR_DEFAULT                      = 0xFF000000L; //no
const Q_DECL_UNUSED QRgb  QCOLOR_SCROLLBAR                  = 0xC8C8C8;    // Scrollbar ok
const Q_DECL_UNUSED QRgb  QCOLOR_BACKGROUND                 = 0x000000;    //Background ok
const Q_DECL_UNUSED QRgb  QCOLOR_ACTIVECAPTION              = 0x99B4D1;    //ActiveTitle ok
const Q_DECL_UNUSED QRgb  QCOLOR_INACTIVECAPTION            = 0xBFCDDB;    //InactiveTitle ok
const Q_DECL_UNUSED QRgb  QCOLOR_MENU                       = 0xF0F0F0;    //Menu ok
const Q_DECL_UNUSED QRgb  QCOLOR_WINDOW                     = 0xFFFFFF;    //Window ok
const Q_DECL_UNUSED QRgb  QCOLOR_WINDOWFRAME                = 0x646464;    //WindowFrame ok
const Q_DECL_UNUSED QRgb  QCOLOR_MENUTEXT                   = 0x000000;    //MenuText ok
const Q_DECL_UNUSED QRgb  QCOLOR_WINDOWTEXT                 = 0x000000;    //WindowText ok
const Q_DECL_UNUSED QRgb  QCOLOR_CAPTIONTEXT                = 0x000000;    //TitleText ok
const Q_DECL_UNUSED QRgb  QCOLOR_ACTIVEBORDER               = 0xB4B4B4;    //ActiveBorder  ok
const Q_DECL_UNUSED QRgb  QCOLOR_INACTIVEBORDER             = 0xF4F7FC;    //InactiveBorder ok
const Q_DECL_UNUSED QRgb  QCOLOR_APPWORKSPACE               = 0xABABAB;    //AppWorkspace ok
const Q_DECL_UNUSED QRgb  QCOLOR_HIGHLIGHT                  = 0x0078D7;    //Highlight ok
const Q_DECL_UNUSED QRgb  QCOLOR_HIGHLIGHTTEXT              = 0xFFFFFF;    //HighlightText ok
const Q_DECL_UNUSED QRgb  QCOLOR_BTNFACE                    = 0xF0F0F0;    //ButtonFace ok
const Q_DECL_UNUSED QRgb  QCOLOR_BTNSHADOW                  = 0xA0A0A0;    //ButtonShadow ok
const Q_DECL_UNUSED QRgb  QCOLOR_GRAYTEXT                   = 0x6D6D6D;    //GrayText ok
const Q_DECL_UNUSED QRgb  QCOLOR_BTNTEXT                    = 0x000000;    //ButtonText ok
const Q_DECL_UNUSED QRgb  QCOLOR_INACTIVECAPTIONTEXT        = 0x000000;    //InactiveTitleText ok
const Q_DECL_UNUSED QRgb  QCOLOR_BTNHIGHLIGHT               = 0xFFFFFF;    //ButtonHighlight ok
const Q_DECL_UNUSED QRgb  QCOLOR_3DDKSHADOW                 = 0x696969;    //ButtonDkShadow ok
const Q_DECL_UNUSED QRgb  QCOLOR_3DLIGHT                    = 0xE3E3E3;    //ButtonLight ok
const Q_DECL_UNUSED QRgb  QCOLOR_INFOTEXT                   = 0x000000;    //InfoText ok
const Q_DECL_UNUSED QRgb  QCOLOR_INFOBK                     = 0xFFFFE1;    //InfoWindow ok
const Q_DECL_UNUSED QRgb  QCOLOR_HOTLIGHT                   = 0x0066CC;    //HotTrackingColor ok
const Q_DECL_UNUSED QRgb  QCOLOR_GRADIENTACTIVECAPTION      = 0xB9D1EA;    //GradientActiveTitle ok
const Q_DECL_UNUSED QRgb  QCOLOR_GRADIENTINACTIVECAPTION    = 0xD7E4F2;    //GradientInactiveTitle ok
const Q_DECL_UNUSED QRgb  QCOLOR_MENUHILIGHT                = 0x3399FF;    //MenuHilight 0k
const Q_DECL_UNUSED QRgb  QCOLOR_MENUBAR                    = 0xF0F0F0;    //MenuBar ok
const Q_DECL_UNUSED QRgb  QCOLOR_3DHIGHLIGHT                = QCOLOR_BTNHIGHLIGHT;    //ButtonHighlight
const Q_DECL_UNUSED QRgb  QCOLOR_3DHILIGHT                  = QCOLOR_BTNHIGHLIGHT;    //ButtonHighlight
const Q_DECL_UNUSED QRgb  QCOLOR_3DSHADOW                   = QCOLOR_BTNSHADOW;    //ButtonShadow
const Q_DECL_UNUSED QRgb  QCOLOR_3DFACE                     = QCOLOR_BTNFACE;


enum eMouseModes { MOUSE_NOTHING, MOUSE_SELECT_ALL, MOUSE_SELECT_COL, MOUSE_SELECT_ROW,
                   MOUSE_SELECT_CELLS, MOUSE_SCROLLING_CELLS,
                   MOUSE_OVER_ROW_DIVIDE, MOUSE_SIZING_ROW,
                   MOUSE_OVER_COL_DIVIDE, MOUSE_SIZING_COL,
                   MOUSE_PREPARE_EDIT,
#ifndef GRIDCONTROL_NO_DRAGDROP
                   MOUSE_PREPARE_DRAG, MOUSE_DRAGGING
#endif
};

//比较函数
typedef int (*QPFNLVCOMPARE)(HLPARAM, HLPARAM, HLPARAM);
//相关列表定义
typedef  QList<QImage*>  QImageList;

///////////////////////////////////////////////////
///单元格状态
//////////////////////////////////////////////////
#define GVIS_FOCUSED            0x0001
#define GVIS_SELECTED           0x0002
#define GVIS_DROPHILITED        0x0004
#define GVIS_READONLY           0x0008
#define GVIS_FIXED              0x0010
#define GVIS_FIXEDROW           0x0020
#define GVIS_FIXEDCOL           0x0040
#define GVIS_MODIFIED           0x0080

////////////////////////////////////////////////////////
//单元格掩码
///////////////////////////////////////////////////////
#define GVIF_TEXT               0x0001
#define GVIF_IMAGE              0x0002
#define GVIF_PARAM              0x0004
#define GVIF_STATE              0x0008
#define GVIF_BKCLR              0x0010
#define GVIF_FGCLR              0x0020
#define GVIF_FORMAT             0x0040
#define GVIF_FONT               0x0080
#define GVIF_MARGIN             0x0100
#define GVIF_BORDER             0x0200
#define GVIF_MERGE              0x0400
#define GVIF_ALL                (GVIF_TEXT|GVIF_IMAGE|GVIF_PARAM|GVIF_STATE|GVIF_BKCLR|GVIF_FGCLR| \
                                 GVIF_FORMAT|GVIF_FONT|GVIF_MARGIN|GVIF_BORDER|GVIF_MERGE)

/////////////////////////////////////////////////////////////
/// 定义单元格内容
/////////////////////////////////////////////////////////////
/*
 * 备注：为什么要采用这种方式？读取和保存表格的时候，如果读取和保存都放在HGridCtrl和HGridCell里面
 * 那么就需要每次创建表格的时候(特别是读取)才能操作表格。如果多个表格进行切换的时候，就需要每次都要创建新表格
 * ，然后再读取内容，这种操作也行，但是效率上就可能不高。所以就采用表格数据独立出来，保存和读取放在外面，这样
 * 切换的时候可以直接清除原来表格内容，将新的表格内容重新设置即可。而且能做到一个文件就是一个完整的表格。
*/
typedef struct _GV_ITEM {
    int        row,col;     // Row and Column of item
    uint       mask;        // Mask for use in getting/setting cell data
    uint       nState;      // cell state (focus/hilighted etc)
    quint32    nFormat;     // Format of cell 表示网格格式：边框，单选，Alignment等
    int        nImage;      // index of the list view item icon
    QColor     crBkClr;     // Background colour (or CLR_DEFAULT)
    QColor     crFgClr;     // Forground colour (or CLR_DEFAULT)
    quint32    lParam;      // 32-bit value to associate with item 数据
    QFont      lfFont;      // Cell font
    uint       nMargin;     // Internal cell margin
    QString    strText;     // Text in cell

    //边框部分
    bool        bLeftBorder;         //设置左边框
    short       nLeftBorderStyle;    //设置左边框类型
    QColor      crLeftBoderClr;      //边框颜色
    bool        bTopBorder;          //设置上边框
    short       nTopBorderStyle;     //设置上边框类型
    QColor      crTopBoderClr;       //上边框颜色
    bool        bRightBorder;        //设置右边框
    short       nRightBorderStyle;   //设置右边框类型
    QColor      crRightBoderClr;     //右边框颜色
    bool        bBottomBorder;       //设置左边框
    short       nBottomBorderStyle;  //设置左边框类型
    QColor      crBottomBoderClr;    //边框颜色

    //合并部分
    bool bShow;
    HCellRange MergeRange;
    HCellID MergeCellID;

} GV_ITEM;

//表格边框结构
typedef struct _GV_BORDER_ITEM {
    bool        bBorderOutSide;
    bool        bBorderLeft;
    bool        bBorderTop;
    bool        bBorderRight;
    bool        bBorderBottom;
    short       nLeftBorderStyle;
    QString     strLeftBoderClr;
    short       nRightBorderStyle;
    QString     strRightBoderClr;
    short       nTopBorderStyle;
    QString     strTopBoderClr;
    short       nBottomBorderStyle;
    QString     strBottomBoderClr;
}GV_BORDER_ITEM;

//单元格数据值
#define QMAKELONG(a, b) ((long)(((ushort)(((ulong)(a)) & 0xffff)) | ((quint32)((ushort)(((quint32)(b)) & 0xffff))) << 16))

///////////////////////////////////////////////////////////////
///定义滚动条信息
///////////////////////////////////////////////////////////////
//定义滚动条相关信息
#define QWM_HSCROLL                      0x0114
#define QWM_VSCROLL                      0x0115

//滚动条常量
#define QSB_HORZ             0
#define QSB_VERT             1
#define QSB_CTL              2
#define QSB_BOTH             3

//滚动条命令
#define QSB_LINEUP           0
#define QSB_LINELEFT         0
#define QSB_LINEDOWN         1
#define QSB_LINERIGHT        1
#define QSB_PAGEUP           2
#define QSB_PAGELEFT         2
#define QSB_PAGEDOWN         3
#define QSB_PAGERIGHT        3
#define QSB_THUMBPOSITION    4
#define QSB_THUMBTRACK       5
#define QSB_TOP              6
#define QSB_LEFT             6
#define QSB_BOTTOM           7
#define QSB_RIGHT            7
#define QSB_ENDSCROLL        8

///////////////////////////////////////////////////////////////////////////////////
// Structures
///////////////////////////////////////////////////////////////////////////////////
/*
// This structure sent to Grid's parent in a WM_NOTIFY message
typedef struct tagNM_GRIDVIEW {
    NMHDR hdr;
    int   iRow;
    int   iColumn;
} NM_GRIDVIEW;

// This is sent to the Grid from child in-place edit controls
typedef struct tagGV_DISPINFO {
    NMHDR   hdr;
    GV_ITEM item;
} GV_DISPINFO;

// This is sent to the Grid from child in-place edit controls
typedef struct tagGV_CACHEHINT {
    NMHDR      hdr;
    HCellRange range;
} GV_CACHEHINT;
*/
// storage typedef for each row in the grid
//typedef CTypedPtrArray<CObArray, CGridCellBase*> GRID_ROW;
//typedef QList<HGridCellBase*> GRID_ROW;


// For virtual mode callback
//typedef bool (*GRIDCALLBACK)(GV_DISPINFO *, LPARAM);

///////////////////////////////////////////////////////////////////////////////////
// 定义文字排列方式
///////////////////////////////////////////////////////////////////////////////////
#define QDT_TOP                      Qt::AlignTop
#define QDT_LEFT                     Qt::AlignLeft
#define QDT_HCENTER                  Qt::AlignHCenter
#define QDT_CENTER                   QDT_HCENTER|QDT_VCENTER
#define QDT_RIGHT                    Qt::AlignRight
#define QDT_VCENTER                  Qt::AlignVCenter
#define QDT_BOTTOM                   Qt::AlignBottom
#define QDT_WORDBREAK                Qt::TextWordWrap
#define QDT_SINGLELINE               Qt::TextSingleLine
#define QDT_EXPANDTABS               Qt::TextExpandTabs
#define QDT_NOPREFIX                 Qt::TextHideMnemonic

// Grid line/scrollbar selection
#define GVL_NONE                0L      // Neither
#define GVL_HORZ                1L      // Horizontal line or scrollbar
#define GVL_VERT                2L      // Vertical line or scrollbar
#define GVL_BOTH                3L      // Both

// Autosizing option
#define GVS_DEFAULT             0
#define GVS_HEADER              1       // Size using column fixed cells data only
#define GVS_DATA                2       // Size using column non-fixed cells data only
#define GVS_BOTH                3       // Size using column fixed and non-fixed

// Cell Searching options
#define GVNI_FOCUSED            0x0001
#define GVNI_SELECTED           0x0002
#define GVNI_DROPHILITED        0x0004
#define GVNI_READONLY           0x0008
#define GVNI_FIXED              0x0010
#define GVNI_MODIFIED           0x0020

#define GVNI_ABOVE              0x0100
#define GVNI_BELOW              0x0200
#define GVNI_TOLEFT             0x0400
#define GVNI_TORIGHT            0x0800
#define GVNI_ALL                (GVNI_BELOW|GVNI_TORIGHT|GVNI_TOLEFT)
#define GVNI_AREA               (GVNI_BELOW|GVNI_TORIGHT)

// Hit test values (not yet implemented)
#define GVHT_DATA               0x0000
#define GVHT_TOPLEFT            0x0001
#define GVHT_COLHDR             0x0002
#define GVHT_ROWHDR             0x0004
#define GVHT_COLSIZER           0x0008
#define GVHT_ROWSIZER           0x0010
#define GVHT_LEFT               0x0020
#define GVHT_RIGHT              0x0040
#define GVHT_ABOVE              0x0080
#define GVHT_BELOW              0x0100

//////////////////////////////////////////////////////////////////////////////
/// 定义画笔类型
//////////////////////////////////////////////////////////////////////////////
#define QPS_NOPEN           Qt::NoPen
#define QPS_SOLIDLINE       Qt::SolidLine
#define QPS_DASHLINE        Qt::DashLine
#define QPS_DOTLINE         Qt::DotLine
#define QPS_DASHDOTLINE     Qt::DashDotLine
#define QPS_DASHDOTDOTLINE  Qt::DashDotDotLine
#define QPS_CUSTOMDASHLINE  Qt::CustomDashLine

/////////////////////////////////////////////////////
#define GRIDREPORT_TYPE_EDITOR   0x01 //编辑框
#define GRIDREPORT_TYPE_BROWSER  0x02 //浏览框

//定义表头的26字母
const char ascii[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
#endif
