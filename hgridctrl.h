﻿/////////////////////////////////////////////////////////////////////////////
// HGridCtrl.h : header file
//
// Grid Control - main header
// Qt表格文件
//原表格文件支持windows平台，采用MFC机制编写，不过其中很多部分都是独立实现的
//但这些在Qt中有部分支持的不是很好，所以要改用Qt本身支持方式会比较好.
//原来的表格仅对表格中文字采取操作，但实际上类似excel还要对文字格式等进行操作
//此表格满足基本要求，对类似execl稍微复杂一点的可能不支持，更别说高级功能的支持。
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDCTRL_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_GRIDCTRL_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_

#include "hgridglobal.h"
#include "hcellrange.h"
#include "hgridcell.h"
#include "hgridcelldef.h"
typedef QList<HGridCellBase*> GRID_ROW;
class HGridCtrl;

/////////////////////////////////////////////////////////////////////////////
class GRIDCTRL_EXPORT HGridCtrl :public QAbstractScrollArea
{
    Q_OBJECT
    friend class HGridCell;
    friend class HGridCellBase;

// 构造、析构函数
public:
    HGridCtrl(int nRows = 0, int nCols = 0, int nFixedRows = 0, int nFixedCols = 0,QWidget *parent = Q_NULLPTR);
    virtual ~HGridCtrl();

public:
    void initGridCtrl();
///////////////////////////////////////////////////////////////////////////////////
// 属性操作
///////////////////////////////////////////////////////////////////////////////////
public:

    //行、列数目  Fixed 表头的行数和列数  ok
    int  rowCount() const                                  { return m_nRows; }
    int  columnCount() const                               { return m_nCols; }
    int  fixedRowCount() const                             { return m_nFixedRows; }
    int  fixedColumnCount() const                          { return m_nFixedCols; }
    bool setRowCount(int nRows = 10);
    bool setColumnCount(int nCols = 10);
    bool setFixedRowCount(int nFixedRows = 1);
    bool setFixedColumnCount(int nFixedCols = 1);

    //行高、列宽
    int  rowHeight(int nRow) const;
    bool setRowHeight(int row, int height);
    int  columnWidth(int nCol) const;
    bool setColumnWidth(int col, int width);

    //获取单元格的左上角位置或者矩形区域
    bool cellOrigin(int nRow, int nCol, QPoint& p);
    bool cellOrigin(const HCellID& cell, QPoint& p);
    bool cellRect(int nRow, int nCol, QRect& pRect);
    bool cellRect(const HCellID& cell, QRect& pRect);

    //获取文字矩形
    bool textRect(const HCellID& cell, QRect& pRect);
    bool textRect(int nRow, int nCol, QRect& pRect);

    //获取point点的行列号。如果true是固定行列，如果是false则是开始到point的行列等...... mid--huangw
    HCellID cellFromPt(const QPoint& point, bool bAllowFixedCellCheck = true);

    //获取固定行的行高 固定列的列宽
    int  fixedRowHeight() const;
    int  fixedColumnWidth() const;

    //获取所有行行高，所有列列宽 打印部分 ok ---huangw
    long virtualWidth() const;
    long virtualHeight() const;

    //获取行列单元格字符串的宽度 ok
    QSize textExtent(int nRow, int nCol,const QString& str);
    inline QSize cellTextExtent(int nRow, int nCol)  { return textExtent(nRow, nCol, itemText(nRow,nCol)); }// EFW - Get extent of current text in cell

    //设置网格背景颜色、网格线颜色 ok
    void     setGridBkColor(const QColor& clr)                                  { m_crGridBkColour = clr;       }
    QColor   gridBkColor() const                                                { return m_crGridBkColour;      }
    void     setGridLineColor(const QColor& clr)                                { m_crGridLineColour = clr;     }
    QColor   gridLineColor() const                                              { return m_crGridLineColour;    }

    //提示窗口背景颜色、提示文字颜色 ok
    void	 setTitleTipBackClr(const QColor& clr = QColor(QCLR_DEFAULT))       { m_crTTipBackClr = clr;        }
    QColor   titleTipBackClr()				                                    { return m_crTTipBackClr;       }
    void	 setTitleTipTextClr(const QColor& clr = QColor(QCLR_DEFAULT))       { m_crTTipTextClr = clr;        }
    QColor   titleTipTextClr()				                                    { return m_crTTipTextClr;       }

    //设置默认表格属性
    void   setTextColor(const QColor& clr)           { m_cellDefault.setTextClr(clr);           }
    QColor textColor()                               { return m_cellDefault.textClr();          }
    void   setTextBkColor(const QColor& clr)         { m_cellDefault.setBackClr(clr);           }
    QColor textBkColor()                             { return m_cellDefault.backClr();          }
    void   setFixedTextColor(const QColor& clr)      { m_cellFixedRowDef.setTextClr(clr);
                                                       m_cellFixedColDef.setTextClr(clr);
                                                       m_cellFixedRowColDef.setTextClr(clr);    }
    QColor fixedTextColor() const                    { return m_cellFixedRowDef.textClr();      }
    void   setFixedBkColor(const QColor& clr)        { m_cellFixedRowDef.setBackClr(clr);
                                                         m_cellFixedColDef.setBackClr(clr);
                                                         m_cellFixedRowColDef.setBackClr(clr);  }
    QColor fixedBkColor() const                      { return m_cellFixedRowDef.backClr();      }
    void   setGridColor(const QColor& clr)           { setGridLineColor(clr);                   }
    QColor gridColor()                                 { return gridLineColor();                }
    void   setBkColor(const QColor& clr)             { setGridBkColor(clr);                     }
    QColor bkColor()                                 { return gridBkColor();                    }

    void     setDefCellMargin( int nMargin)          { m_cellDefault.setMargin(nMargin);
                                                       m_cellFixedRowDef.setMargin(nMargin);
                                                       m_cellFixedColDef.setMargin(nMargin);
                                                       m_cellFixedRowColDef.setMargin(nMargin); }
    int      defCellMargin() const                   { return m_cellDefault.margin();           }

    int      defCellHeight() const                   { return m_cellDefault.height();           }
    void     setDefCellHeight(int nHeight)           { m_cellDefault.setHeight(nHeight);
                                                       m_cellFixedRowDef.setHeight(nHeight);
                                                       m_cellFixedColDef.setHeight(nHeight);
                                                       m_cellFixedRowColDef.setHeight(nHeight); }
    int      defCellWidth() const                    { return m_cellDefault.width();            }
    void     setDefCellWidth(int nWidth)             { m_cellDefault.setWidth(nWidth);
                                                       m_cellFixedRowDef.setWidth(nWidth);
                                                       m_cellFixedColDef.setWidth(nWidth);
                                                       m_cellFixedRowColDef.setWidth(nWidth);   }

    // ***************************************************************************** //
    //设置表格相关标志
    //设置焦点 主要是重绘操作  mid
    HCellID setFocusCell(HCellID cell);
    HCellID setFocusCell(int nRow, int nCol);
    HCellID focusCell() const                     { return m_idCurrentCell;           }

   //设置为打印模式 ok
    void setVirtualMode(bool bVirtual);
    bool isVirtualMode() const                    { return m_bVirtualMode;            }

    //回调函数  lParam --huangw
    /*
    void setCallbackFunc(GRIDCALLBACK pCallback,
                         LPARAM lParam)           { m_pfnCallback = pCallback; m_lParam = lParam; }
    GRIDCALLBACK callbackFunc()                   { return m_pfnCallback;             }
*/
    //网格设置图片 ok
    void setImageList(QImageList* pList)          { m_pImageList = pList;             }
    QImageList* imageList() const                 { return m_pImageList;              }

    //设置网格线类型 ok
    void setGridLines(int nWhichLines = GVL_BOTH);
    int  gridLines() const                        { return m_nGridLines;              }
    void setShowGrid(bool bShowGrid = true)       { m_bShowGrid = bShowGrid;          }
    bool isShowGrid()                             { return m_bShowGrid;               }

    //设置可编辑  ok
    void setEditable(bool bEditable = true)       { m_bEditable = bEditable;          }
    bool isEditable() const                       { return m_bEditable;               }
    void setListMode(bool bEnableListMode = true);
    bool isListMode() const                       { return m_bListMode;               }

    //获取固定选择行 ok
    int selectedCount() const                     { return (int)m_SelectedCellMap.count(); }

    //单行、单列选择 ok
    void setSingleRowSelection(bool bSing = true) { m_bSingleRowSelection = bSing;    }
    bool isSingleRowSelection()                   { return m_bSingleRowSelection & m_bListMode; }
    void setSingleColSelection(bool bSing = true) { m_bSingleColSelection = bSing;    }
    bool isSingleColSelection()                   { return m_bSingleColSelection;     }

    //设置可选择 ok
    void enableSelection(bool bEnable = true)     { resetSelectedRange(); m_bEnableSelection = bEnable; resetSelectedRange(); }
    bool isSelectable() const                     { return m_bEnableSelection;        }

    //设置表头行列选择 ok
    void setFixedColumnSelection(bool bSelect)    { m_bFixedColumnSelection = bSelect;}
    bool isFixedColumnSelection()                 { return m_bFixedColumnSelection;   }
    void setFixedRowSelection(bool bSelect)       { m_bFixedRowSelection = bSelect;   }
    bool isFixedRowSelection()                    { return m_bFixedRowSelection;      }

    //允许拖拽 ok
    void enableDragAndDrop(bool bAllow = true)    { m_bAllowDragAndDrop = bAllow;     }
    bool isDragAndDrop() const                    { return m_bAllowDragAndDrop;       }

    //允许调整行列大小 ok
    void setRowResize(bool bResize = true)        { m_bAllowRowResize = bResize;      }
    bool isRowResize() const                      { return m_bAllowRowResize;         }
    void setColumnResize(bool bResize = true)     { m_bAllowColumnResize = bResize;   }
    bool isColumnResize() const                   { return m_bAllowColumnResize;      }

    //设置表头按照鼠标点击排序 ok
    void setHeaderSort(bool bSortOnClick = true)  { m_bSortOnClick = bSortOnClick;    }
    bool isHeaderSort() const                     { return m_bSortOnClick;            }

    //设置Tab键处理 按Tab键后选择表格往后移动一格 ok
    void setHandleTabKey(bool bHandleTab = true)  { m_bHandleTabKey = bHandleTab;     }
    bool isHandleTabKey() const                   { return m_bHandleTabKey;           }

    //设置双缓冲绘制方法
    //void SetDoubleBuffering(bool bBuffer = true)  { m_bDoubleBuffer = bBuffer;        }
    //bool GetDoubleBuffering() const               { return m_bDoubleBuffer;           }

    //允许提示
    void enableTitleTips(bool bEnable = true)     { m_bTitleTips = bEnable;           }
    bool isTitleTips()                            { return m_bTitleTips;              }

    //设置列排序 这种方法？？？
    void setSortColumn(int nCol);
    int  sortColumn() const                       { return m_nSortColumn;             }

    //设置降序升序
    void setSortAscending(bool bAscending)        { m_bAscending = bAscending;        }
    bool isSortAscending() const                  { return m_bAscending;              }

    //设置跟踪??? 没用到
    void setTrackFocusCell(bool bTrack)           { m_bTrackFocusCell = bTrack;       }
    bool isTrackFocusCell()                       { return m_bTrackFocusCell;         }

    //设置框架焦点 没用到
    void setFrameFocusCell(bool bFrame)              { m_bFrameFocus = bFrame;           }
    bool isFrameFocusCell()                          { return m_bFrameFocus;             }

    //设置自动调整大小 没用到
    void setAutoSizeStyle(int nStyle = GVS_BOTH)     { m_nAutoSizeColumnStyle = nStyle;  }
    int  autoSizeStyle()                             { return m_nAutoSizeColumnStyle; }

    //设置忽略隐藏列 忽略隐藏的列并向左看第一个可见列
    void enableHiddenColUnhide(bool bEnable = true)  { m_bHiddenColUnhide = bEnable;     }
    bool hiddenColUnhide()                           { return m_bHiddenColUnhide;        }
    void enableHiddenRowUnhide(bool bEnable = true)  { m_bHiddenRowUnhide = bEnable;     }
    bool hiddenRowUnhide()                           { return m_bHiddenRowUnhide;        }

    //允许行列隐藏 如当鼠标移动列，如果允许隐藏列，则列宽为0，如果不允许则列宽是最小是1
    void enableColumnHide(bool bEnable = true)       { m_bAllowColHide = bEnable;        }
    bool isColumnHide()                              { return m_bAllowColHide;           }
    void enableRowHide(bool bEnable = true)          { m_bAllowRowHide = bEnable;        }
    bool isRowHide()                                 { return m_bAllowRowHide;           }

///////////////////////////////////////////////////////////////////////////////////
// default Grid cells. Use these for setting default values such as colors and fonts
///////////////////////////////////////////////////////////////////////////////////
public:
    HGridCellBase* defaultCell(bool bFixedRow, bool bFixedCol) const;

///////////////////////////////////////////////////////////////////////////////////
// Grid cell Attributes 表格属性
///////////////////////////////////////////////////////////////////////////////////
public:
    HGridCellBase* getCell(int nRow, int nCol) const;   // Get the actual cell!
    HGridCellBase* getCell(HCellID cell)       const;
    //设置表格是否修改标志 ok
    void setModified(bool bModified = true, int nRow = -1, int nCol = -1);
    bool isModified(int nRow = -1, int nCol = -1);

    //设置行列是否是固定行列 ok
    bool isCellFixed(int nRow, int nCol);

    //通过行列结构方式设置行列信息 ok
    bool   setItem(const GV_ITEM* pItem);
    bool   item(GV_ITEM* pItem);
    bool   setItemText(int nRow, int nCol, const QString& str);
    QString itemText(int nRow, int nCol) const; //原代码有注释
/*
    // EFW - 06/13/99 - Added to support printf-style formatting codes.
    // Also supports use with a string resource ID
#if !defined(_WIN32_WCE) || (_WIN32_WCE >= 210) //win ce环境不能用
    //格式化相关字符串 类似printf,使用setItemTextFmt(0,0,"%s,%d","abc",1);
    bool   setItemTextFmt(int nRow, int nCol, const char *szFmt, ...); /////////////修改
    bool   setItemTextFmtID(int nRow, int nCol, uint nID, ...);
#endif
*/
    //设置行列Data ok
    bool   setItemData(int nRow, int nCol, const quint32& lParam);
    quint32 itemData(int nRow, int nCol) const;

    //设置行列图片 ok
    bool   setItemImage(int nRow, int nCol, int nImage);
    int    itemImage(int nRow, int nCol) const;

    //设置行列状态 ok
    bool   setItemState(int nRow, int nCol, uint state);
    uint   itemState(int nRow, int nCol) const;

    //设置格式，居中，对齐等 ok
    bool   setItemFormat(int nRow, int nCol, uint nFormat);
    uint   itemFormat(int nRow, int nCol) const;

    //设置背景颜色 ok
    bool   setItemBkColour(int nRow, int nCol, QColor& cr = QColor(QCLR_DEFAULT));
    QColor itemBkColour(int nRow, int nCol) const;

    //设置前景颜色 就是文字颜色 ok
    bool   setItemFgColour(int nRow, int nCol, QColor& cr = QColor(QCLR_DEFAULT));
    QColor itemFgColour(int nRow, int nCol) const;

    //设置字体 ok
    bool  setItemFont(int nRow, int nCol, const QFont& lf);
    QFont itemFont(int nRow, int nCol);

    //设置边框
    bool setItemBorder(int nRow,int nCol,const GV_BORDER_ITEM* pItem);
    bool itemBorder(int nRow,int nCol,GV_BORDER_ITEM* pItem);

    //是否编辑 ok
    bool isItemEditing(int nRow, int nCol);

    //单元格显示不同类型控件，如果checkbox,button等
    //
     // 比如创建button,首先button必须是HGridCellBase子类，如HGridCellButton
     // 然后setCellType(0,0,RUNTIME_CLASS(HGridCellButton));然后创建了一个button
    //
    /*
    bool setCellType(int nRow, int nCol, QObject* pRuntimeClass);
    bool setDefaultCellType( QObject* pRuntimeClass);
*/
///////////////////////////////////////////////////////////////////////////////////
// Operations
///////////////////////////////////////////////////////////////////////////////////
public:
    //插入行列，在原有的基础上再插入
    int  insertColumn(const QString& strHeading, quint32 nFormat = 0,int nColumn = -1);//format huangw
    int  insertRow(const QString& strHeading, int nRow = -1);

    //删除行列
    bool deleteColumn(int nColumn);
    bool deleteRow(int nRow);
    bool deleteNonFixedRows();
    bool deleteAllItems();

    //刷新行列头
    void autoRowHeader();
    void autoColumnHeader();

    //清除表格范围(所有，格式，文字）
    void clearCells(HCellRange Selection);
    void clearFormats(HCellRange Selection);
    void clearFormatting(HCellRange Selection);

    //自动调整行列，扩展行列到合适位置
    bool autoSizeRow(int nRow, bool bResetScroll = true);
    bool autoSizeColumn(int nCol, uint nAutoSizeStyle = GVS_DEFAULT, bool bResetScroll = true);
    void autoSizeRows();
    void autoSizeColumns(uint nAutoSizeStyle = GVS_DEFAULT);
    void autoSize(uint nAutoSizeStyle = GVS_DEFAULT);
    void expandColumnsToFit(bool bExpandFixed = true);
    void expandLastColumn();
    void expandRowsToFit(bool bExpandFixed = true);
    void expandToFit(bool bExpandFixed = true);

    //自动填充
    void refresh();
/*    void autoFill();   // Fill grid with blank cells*/

    //可视化
    void ensureVisible(HCellID &cell)       { ensureVisible(cell.row, cell.col); }
    void ensureVisible(int nRow, int nCol);
    bool isCellVisible(int nRow, int nCol);
    bool isCellVisible(const HCellID& cell);

    //可编辑和可选择
    bool isCellEditable(int nRow, int nCol) const;
    bool isCellEditable(HCellID &cell) const;
    bool isCellSelected(int nRow, int nCol) const;
    bool isCellSelected(HCellID &cell) const;


    // SetRedraw stops/starts redraws on things like changing the # rows/columns
    // and autosizing, but not for user-intervention such as resizes
    //重绘操作
    void setRedraw(bool bAllowDraw, bool bResetScrollBars = false);
    bool redrawCell(int nRow, int nCol, QPainter* painter = NULL);
    bool redrawCell(const HCellID& cell, QPainter* painter = NULL);
    bool redrawRow(int row);
    bool redrawColumn(int col);

    //表格存储 ???
    void load(int v,QDataStream* ds);
    void save(int v,QDataStream* ds);

///////////////////////////////////////////////////////////////////////////////////
// Cell Ranges
///////////////////////////////////////////////////////////////////////////////////
 public:

    //多表格(区域表格)操作 ok
    HCellRange cellRange() const;
    HCellRange selectedCellRange();
    void setSelectedRange(const HCellRange& Range, bool bForceRepaint = false, bool bselectCells = true);
    void setSelectedRange(int nMinRow, int nMinCol, int nMaxRow, int nMaxCol,
                          bool bForceRepaint = false, bool bselectCells = true);
    void resetSelectedRange();

    bool cellRangeRect(const HCellRange& cellRange, QRect& lpRect);
    bool isValid(int nRow, int nCol) const;
    bool isValid(const HCellID& cell) const;
    bool isValid(const HCellRange& range) const;

///////////////////////////////////////////////////////////////////////////////////
// Clipboard, drag and drop, and cut n' paste operations
// 剪切 拖拽等操作
///////////////////////////////////////////////////////////////////////////////////
#ifndef QT_NO_CLIPBOARD
    virtual QString getClipboardFile();
    virtual void cutSelectedText();
    virtual void copyTextFromGrid();
    virtual bool pasteTextToGrid(HCellID& cell, bool bSelectPastedCells=true);
#endif

/*
#ifndef GRIDCONTROL_NO_DRAGDROP
 public:

    virtual void OnBeginDrag();
    virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
    virtual void OnDragLeave();
    virtual bool OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);

    //拖拽
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dragLeaveEvent(QDragLeaveEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent *event);
    virtual void dropEvent(QDropEvent *event);

#endif
*/

/*
///////////////////////////////////////////////////////////////////////////////////
// Misc.排序 比较等
///////////////////////////////////////////////////////////////////////////////////
public:
    HCellID getNextItem(HCellID& cell, int nFlags) const;

    bool sortItems(int nCol, bool bAscending, const QVariant& data = QVariant());
    bool sortTextItems(int nCol, bool bAscending, const QVariant& data = QVariant());
    bool sortItems(QPFNLVCOMPARE pfnCompare, int nCol, bool bAscending, const QVariant& data = QVariant());

    void setCompareFunction(QPFNLVCOMPARE pfnCompare);

	// in-built sort functions
    static int CALLBACK qPfnCellTextCompare(HLPARAM lParam1, HLPARAM lParam2, HLPARAM lParamSort);
    static int CALLBACK qPfnCellNumericCompare(HLPARAM lParam1, HLPARAM lParam2, HLPARAM lParamSort);
*/
///////////////////////////////////////////////////////////////////////////////////
// Printing
///////////////////////////////////////////////////////////////////////////////////
public:
    //void Print(CPrintDialog* pPrntDialog = NULL);

    // EFW - New printing support functions
    //void EnableWysiwygPrinting(bool bEnable = true) { m_bWysiwygPrinting = bEnable;     }
    //bool GetWysiwygPrinting()                       { return m_bWysiwygPrinting;        }

    void SetShadedPrintOut(bool bEnable = true)     {   m_bShadedPrintOut = bEnable;    }
    bool GetShadedPrintOut(void)                    {   return m_bShadedPrintOut;       }

    // Use -1 to have it keep the existing value
    void setPrintMarginInfo(int nHeaderHeight, int nFooterHeight,
        int nLeftMargin, int nRightMargin, int nTopMargin,
        int nBottomMargin, int nGap);

    void printMarginInfo(int &nHeaderHeight, int &nFooterHeight,
        int &nLeftMargin, int &nRightMargin, int &nTopMargin,
        int &nBottomMargin, int &nGap);

    void setPrintHeadFoot(QString strHead,QString strFoot);
    void printHeadFoot(QString& strHead,QString& strFoot);

    void setPrintOther(bool bHorizontalHeader,bool bVerticalHeader, bool bShowGrids,bool bPrintColour);
    void printOther(bool& bHorizontalHeader,bool& bVerticalHeader, bool& bShowGrids,bool& bPrintColour);
    bool isPrintColour() {return m_bPrintColour;}
    bool isPrintShowGrids() {return m_bPrintShowGrids;}

///////////////////////////////////////////////////////////////////////////////////
// Printing overrides for derived classes
///////////////////////////////////////////////////////////////////////////////////
// Implementation
public:
    //Merge the selected cells    合并单元格
    //查看单元格是否属于合并单元格，如果是合并单元格则返回合并单元格第1个行列
    HCellID mergeCellID(HCellID cell);
    //取消合并单元格
    void setSplitSelectedCells();
    //合并选择的单元格
    void setMergeSelectedCells();
    //取消合并单元格
    void setSplitCells(int nStartRow, int nStartCol, int nEndRow, int nEndCol);
    //合并单元格
    void setMergeCells(int nStartRow, int nStartCol, int nEndRow, int nEndCol);
    int  mergeCellWidth(HCellID cell);
    int  mergeCellHeight(HCellID cell);
    bool cellOriginNoMerge(int nRow, int nCol, QPoint& p);
    bool cellOriginNoMerge(const HCellID& cell, QPoint& p);


protected:
    //设置默认单元格
    void setupDefaultCells(); //
/*
    LRESULT SendMessageToParent(int nRow, int nCol, int nMessage) const;
    LRESULT SendDisplayRequestToParent(GV_DISPINFO* pDisplayInfo) const;
    LRESULT SendCacheHintToParent(const HCellRange& range) const;
*/
    bool invalidateCellRect(const int row, const int col);
    bool invalidateCellRect(const HCellID& cell);
    bool invalidateCellRect(const HCellRange& cellRange);
    void eraseBkgnd(QPainter* pDC);

    int  setMouseMode(int nMode) { int nOldMode = m_MouseMode; m_MouseMode = nMode; return nOldMode; }
    int  mouseMode() const       { return m_MouseMode; }

    bool mouseOverRowResizeArea(QPoint& point);
    bool mouseOverColumnResizeArea(QPoint& point);

    HCellID topleftNonFixedCell(bool bForceRecalculation = false);
    HCellRange unobstructedNonFixedCellRange(bool bForceRecalculation = false);
    HCellRange visibleNonFixedCellRange(QRect& pRect = QRect(), bool bForceRecalculation = false);

    bool isVisibleVScroll() { return ( (m_nBarState & GVL_VERT) > 0); }
    bool isVisibleHScroll() { return ( (m_nBarState & GVL_HORZ) > 0); }

    //设置滚动条位置
    void setScrollBarValue(uint Msg,HWPARAM wParam,HLPARAM IParam );
    void onHScroll(uint nSBCode, uint nPos, QScrollBar* pScrollBar);
    void onVScroll(uint nSBCode, uint nPos, QScrollBar* pScrollBar);
    int  scrollPos32(int nBar, bool bGetTrackPos = false);
    bool setScrollPos32(int nBar, int nPos, bool bRedraw = true);
    void resetScrollBars();


    QPoint pointClicked(int nRow, int nCol, const QPoint& point);
    /*void EnableScrollBars(int nBar, bool bEnable = true);


    bool SortTextItems(int nCol, bool bAscending, int low, int high);
    bool SortItems(PFNLVCOMPARE pfnCompare, int nCol, bool bAscending, LPARAM data,
                   int low, int high);



// Overrrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CGridCtrl)
    protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

protected:
#if !defined(_WIN32_WCE_NO_PRINTING) && !defined(GRIDCONTROL_NO_PRINTING)
    // Printing
	virtual void PrintFixedRowCells(int nStartColumn, int nStopColumn, int& row, CRect& rect,
                                    CDC *pDC, bool& bFirst);
    virtual void PrintColumnHeadings(CDC *pDC, CPrintInfo *pInfo);
    virtual void PrintHeader(CDC *pDC, CPrintInfo *pInfo);
    virtual void PrintFooter(CDC *pDC, CPrintInfo *pInfo);
    virtual void PrintRowButtons(CDC *pDC, CPrintInfo* pInfo);
#endif

#ifndef GRIDCONTROL_NO_DRAGDROP
    // Drag n' drop
    virtual CImageList* CreateDragImage(CPoint *pHotSpot);    // no longer necessary
#endif
*/
    // Mouse Clicks
    virtual void  onFixedColumnClick(HCellID& cell);
    virtual void  onFixedRowClick(HCellID& cell);

    // Editing
    virtual void  onEditCell(int nRow, int nCol, QPoint point);
    virtual bool  validateEdit(int nRow, int nCol, QString& str);
    virtual void  endEditing();

    // Drawing
    virtual void  onDraw(QPainter* painter);

    // CGridCellBase Creation and Cleanup
    virtual HGridCellBase* createCell(int nRow, int nCol);
    virtual void destroyCell(int nRow, int nCol);

protected:

    void selectAllCells();
    void selectColumns(HCellID currentCell, bool bForceRedraw=false, bool bselectCells=true);
    void selectRows(HCellID currentCell, bool bForceRedraw=false, bool bselectCells=true);
    void selectCells(HCellID currentCell, bool bForceRedraw=false, bool bselectCells=true);
    void onSelecting(const HCellID& currentCell);
    void validateAndModifyCellContents(int nRow, int nCol, const QString& strText);

    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void activated(const HCellID& cell);
    void clicked(const HCellID& cell);
    void doubleClicked(const HCellID& cell);
    void iconSizeChanged(const HCellID& cell,const QSize &size);
    void pressed(const HCellID& cell);

public slots:
    void  onEndEditCell(int nRow, int nCol, QString str);
    void  onHorizontalScrollBarChanged(int value);
    void  onVerticalScrollBarChanged(int value);
// Attributes
protected:
    // General attributes
    QColor    m_crFixedTextColour, m_crFixedBkColour;
    QColor    m_crGridBkColour, m_crGridLineColour;
    QColor    m_crWindowText, m_crWindowColour, m_cr3DFace,     // System colours
                m_crShadow;
    QColor    m_crTTipBackClr, m_crTTipTextClr;                 // Titletip colours - FNA
    
    bool        m_bVirtualMode;
    HLPARAM     m_lParam;                                           // lParam for callback
    //GRIDCALLBACK m_pfnCallback;                                     // The callback function

    int         m_nGridLines; //网格绘制类型
    bool        m_bShowGrid;  //显示网格
    bool        m_bEditable;  //允许编辑
    bool        m_bModified;  //是否修改
    bool        m_bAllowDragAndDrop;
    bool        m_bListMode;
    bool        m_bSingleRowSelection; //行选择
    bool        m_bSingleColSelection; //列选择
    bool        m_bAllowDraw;
    bool        m_bEnableSelection;    //允许选择单元格
    bool        m_bFixedRowSelection, m_bFixedColumnSelection;
    bool        m_bSortOnClick;
    bool        m_bHandleTabKey;
    bool        m_bDoubleBuffer;
    bool        m_bTitleTips;
    int         m_nBarState;
    bool        m_bWysiwygPrinting;
    bool        m_bHiddenColUnhide, m_bHiddenRowUnhide;
    bool        m_bAllowColHide, m_bAllowRowHide;
    bool        m_bAutoSizeSkipColHdr;
    bool        m_bTrackFocusCell;
    bool        m_bFrameFocus;
    uint        m_nAutoSizeColumnStyle;

    // Cell size details
    int            m_nRows, m_nFixedRows, m_nCols, m_nFixedCols;
    QVector<uint>  m_arRowHeights, m_arColWidths; //存储行高和列宽的
    int            m_nVScrollMax, m_nHScrollMax;

    // Fonts and images
    QObject*    m_pRtcDefault; // determines kind of Grid Cell created by default
    HGridDefaultCell   m_cellDefault;  // "default" cell. Contains default colours, font etc.
    HGridDefaultCell   m_cellFixedColDef, m_cellFixedRowDef, m_cellFixedRowColDef;
    QFont       m_PrinterFont;  // for the printer
    QImageList* m_pImageList;

    // Cell data
    //CTypedPtrArray<CObArray, GRID_ROW*> m_RowData;
    QList<GRID_ROW*> m_RowData;

    // Mouse operations such as cell selection
    int         m_MouseMode;
    bool        m_bLMouseButtonDown, m_bRMouseButtonDown;
    QPoint      m_LeftClickDownPoint, m_LastMousePoint,m_CurMousePoint;
    HCellID     m_LeftClickDownCell, m_SelectionStartCell;
    HCellID     m_idCurrentCell, m_idTopLeftCell;
    int         m_nTimerID;
    int         m_nTimerInterval;
    int         m_nResizeCaptureRange;
    bool        m_bAllowRowResize, m_bAllowColumnResize;
    int         m_nRowsPerWheelNotch;
    QMap<quint32,HCellID> m_SelectedCellMap, m_PrevSelectedCellMap;

#ifndef GRIDCONTROL_NO_TITLETIPS
    //CTitleTip   m_TitleTip;             // Title tips for cells
#endif

    // Drag and drop
    HCellID     m_LastDragOverCell;
#ifndef GRIDCONTROL_NO_DRAGDROP
    //CGridDropTarget m_DropTarget;       // OLE Drop target for the grid
#endif

    // Printing information
    QSize       m_CharSize;
    int         m_nPageHeight;
    QSize       m_LogicalPageSize,      // Page size in gridctrl units.
                m_PaperSize;            // Page size in device units.
    // additional properties to support Wysiwyg printing
    int         m_nPageWidth;
    int         m_nPrintColumn;
    int         m_nCurrPrintRow;
    int         m_nNumPages;
    int         m_nPageMultiplier;

    // sorting
    int          m_bAscending;
    int          m_nSortColumn;
    QPFNLVCOMPARE m_pfnCompare;

    // EFW - Added to support shaded/unshaded printout.  If true, colored
    // cells will print as-is.  If false, all text prints as black on white.
    bool        m_bShadedPrintOut;

    // EFW - Added support for user-definable margins.  Top and bottom are in 
    // lines.  Left, right, and gap are in characters (avg width is used).
    int         m_nHeaderHeight, m_nFooterHeight, m_nLeftMargin,
                m_nRightMargin, m_nTopMargin, m_nBottomMargin, m_nGap;
    QString m_strHead,m_strFoot;
    bool m_bHorizontalHeader,m_bVerticalHeader, m_bPrintShowGrids,m_bPrintColour;
public slots:
#ifndef QT_NO_CLIPBOARD
    //复制 剪切 拷贝
    virtual void onEditCut();
    virtual void onEditCopy();
    virtual void onEditPaste();
#endif
    // Ctrl+A 全选
    virtual void onEditSelectAll();
};

// Returns the default cell implementation for the given grid region

inline HGridCellBase* HGridCtrl::defaultCell(bool bFixedRow, bool bFixedCol) const
{ 
    if (bFixedRow && bFixedCol) return (HGridCellBase*) &m_cellFixedRowColDef;
    if (bFixedRow)              return (HGridCellBase*) &m_cellFixedRowDef;
    if (bFixedCol)              return (HGridCellBase*) &m_cellFixedColDef;
    return (HGridCellBase*) &m_cellDefault;
}

inline HGridCellBase* HGridCtrl::getCell(int nRow, int nCol) const
{
    if (nRow < 0 || nRow >= m_nRows || nCol < 0 || nCol >= m_nCols) 
        return NULL;

    if (isVirtualMode())
    {
        /*HGridCellBase* pCell = defaultCell(nRow < m_nFixedRows, nCol < m_nFixedCols);
        static GV_DISPINFO gvdi;
        gvdi.item.row     = nRow;
        gvdi.item.col     = nCol;
        gvdi.item.mask    = 0xFFFFFFFF;
        gvdi.item.nState  = 0;
        gvdi.item.nFormat = pCell->format();
        gvdi.item.nImage  = pCell->image();
        gvdi.item.crBkClr = pCell->backClr();
        gvdi.item.crFgClr = pCell->textClr();
        gvdi.item.lParam  = pCell->data();
        gvdi.item.lfFont  = pCell->font();
        gvdi.item.nMargin = pCell->margin();
        gvdi.item.strText = "";

        // Fix the state bits
        if (isCellSelected(nRow, nCol))          gvdi.item.nState |= GVIS_SELECTED;
        if (nRow < fixedRowCount())              gvdi.item.nState |= (GVIS_FIXED | GVIS_FIXEDROW);
        if (nCol < fixedColumnCount())           gvdi.item.nState |= (GVIS_FIXED | GVIS_FIXEDCOL);
        if (focusCell() == HCellID(nRow, nCol))  gvdi.item.nState |= GVIS_FOCUSED;
        
        if (m_pfnCallback)
            m_pfnCallback(&gvdi, m_lParam);
        else
        {
            //SendDisplayRequestToParent(&gvdi);
        }
        static HGridCell cell;
        cell.SetState(gvdi.item.nState);
        cell.SetFormat(gvdi.item.nFormat);
        cell.SetImage(gvdi.item.nImage);
        cell.SetBackClr(gvdi.item.crBkClr);
        cell.SetTextClr(gvdi.item.crFgClr);
        cell.SetData(gvdi.item.lParam);
        cell.SetFont(&(gvdi.item.lfFont));
        cell.SetMargin(gvdi.item.nMargin);
        cell.SetText(gvdi.item.strText);
        cell.SetGrid((CGridCtrl*)this);

        return (HGridCellBase*) &cell;*/
    }

    GRID_ROW* pRow = m_RowData[nRow];
    if (!pRow) return NULL;
    return pRow->at(nCol);
}

/*
inline bool HGridCtrl::setCell(int nRow, int nCol, HGridCellBase* pCell)
{
    if (isVirtualMode())
        return false;

    if (nRow < 0 || nRow >= m_nRows || nCol < 0 || nCol >= m_nCols) 
        return false;

    GRID_ROW* pRow = m_RowData[nRow];
    if (!pRow) return false;

    pCell->setCoords( nRow, nCol);
    pRow->insert(nCol, pCell);
    return true;
}*/

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDCTRL_H__519FA702_722C_11D1_ABBA_00A0243D1382__INCLUDED_)
