#ifndef HGRIDREPORTWIDGET_H
#define HGRIDREPORTWIDGET_H

#include <QWidget>
//此页面及其管理的页面都是属于表格控件内容
//管理多个HGridCtrlWidget具体tab页面的
#include <QTabWidget>
#include "hgridctrl.h"
class GRIDCTRL_EXPORT HGridReportWidget : public QWidget
{
    Q_OBJECT
public:
    HGridReportWidget(QWidget *parent = 0);
    ~HGridReportWidget();
public:
    void setEditorGridReportAttr();
    void setBrowserGridReportAttr();
public:
    void setReportFile(const QString& str);
    void init();
    void open();
    void update();
    void clear();
public:
///////////////////////////////////////////////////////////////////////////////
/// 文件
//////////////////////////////////////////////////////////////////////////////
    bool load(const QString& strFile);
    bool save(const QString& strFile);
///////////////////////////////////////////////////////////////////////////////
///////Tab属性
/// //////////////////////////////////////////////////////////////////////////
    QString tabName();
    void setTabName(const QString& tableName);
    QString sheetName(short nSheet);
    void setSheetName(short nSheet, const QString& lpszNewValue);
    void setNumSheet(long num);
    long numSheet();
    void setSheet(long index);
    long sheet();

///////////////////////////////////////////////////////////////////////////////
///////设置属性
/// //////////////////////////////////////////////////////////////////////////
    void setGridCtrlAttr(QWidget* w);
    void enableShowEditBar(bool);
    void enableShowTab(bool);
    void enableVritual(bool);
    void enableHorizontalHeader(bool bEnable = true);
    void enableVerticalHeader(bool bEnable = true);
    void enablePrintColour(bool);
    void enableShowGrids(bool);

///////////////////////////////////////////////////////////////////////////////
///////操作
/// //////////////////////////////////////////////////////////////////////////
    void setMaxRow(int row);
    void setMaxCol(int col);
    void selectedRowCol(int& row1,int& col1,int& row2,int& col2);
    void setSelectedRowCol(int row1,int col1,int row2,int col2);
    void selectedRect(QRect& rect);
    void setFocusCell(int row,int col);
    void setTextColor(int row,int col,const QColor& clr);
    void enableOnlyRead(int row,int col,bool bRead = false);

    void paste();
    void cut();
    void copy();

    void setText(int row,int col,const QString&);
    void setFormat(quint32 f);
    quint32 format();
    void setBorder(GV_BORDER_ITEM* item);
    void getBorder(GV_BORDER_ITEM*);
    void enableResetFormat(bool);
    void enableResetText(bool);
    void enableResetAllFormat(bool);
    void setFont(const QFont& font);
    QFont font();
    void setTextColor(const QString&);
    QString textColor();
    void setTextBkColor(const QString&);
    QString textBkColor();
    bool mergeCell();
    bool splitCell();
    bool isMerged();
    bool insertGridRow();
    bool insertGridColumn();
    bool removeGridRow();
    bool removeGridColumn();
    void autoSizeRows();
    void autoSizeColumns();
    bool setRowHeight(int height);
    bool setColumnWidth(int width);
    int  rowHeight();
    int  columnWidth();

    //打印
    void printPreview();
    void print();
    void setPrintMarginInfo(int nHeaderHeight, int nFooterHeight,
        int nLeftMargin, int nRightMargin, int nTopMargin,
        int nBottomMargin);
    void setPrintHeadFoot(QString strHead,QString strFoot);
    void printHeadFoot(QString& strHead,QString& strFoot);

    void setPrintOther(bool bHorizontalHeader,bool bVerticalHeader, bool bShowGrids,bool bPrintColour);
    void printOther(bool& bHorizontalHeader,bool& bVerticalHeader, bool& bShowGrids,bool& bPrintColour);


signals:
    void gridcellclicked();

public slots:
    void gridCell_clicked();

public:
    QTabWidget* m_tabWidget;
private:
    int m_nRow;
    int m_nCol;
    QString m_strGridCtrlFile;
    long m_nNumSheets;
    bool m_bEnableShowEditBar;
    bool m_bEnableShowTab;
    bool m_bEnableVirtual;
    bool m_bHorizontalHeader;
    bool m_bVerticalHeader;
    bool m_bShowGrids;
    bool m_bPrintColour;
};
#endif // HGRIDREPORTWIDGET_H
