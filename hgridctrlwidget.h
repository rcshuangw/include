#ifndef HREPORTWIDGET_H
#define HREPORTWIDGET_H

#include <QWidget>
#include "hgridglobal.h"
#include "hgridcelldef.h"
class HGridCtrl;
class QLabel;
class QLineEdit;
class HCellID;

//tab页的具体内容
class  GRIDCTRL_EXPORT HGridCtrlWidget : public QWidget
{
    Q_OBJECT
public:
    HGridCtrlWidget(QWidget* parent = 0);
    ~HGridCtrlWidget();

public:
    void reset();
    bool load(const QString& strFile);
    bool save(const QString& strFile);
public:
    void initReportWidget();
    void refreshGridCtrl();
public:
    //
    void setMaxRowCol(int rowMax,int colMax);
    void selectedRowCol(int& row1,int& col1,int& row2,int& col2);
    void setSelectedRowCol(int row1,int col1,int row2,int col2);
    void selectedRect(QRect& rect);
    void setFocusCell(int row,int col);
    void setTextColor(int row,int col,const QColor& clr);
    void enableOnlyRead(int row,int col,bool bRead = false);

    //单元格操作
    void setText(int row,int col,const QString&);
    void setFormat(quint32 f);
    quint32 format();

    void setBorder(GV_BORDER_ITEM* item);
    void getBorder(GV_BORDER_ITEM*);

    //清除
    void enableResetFormat(bool);
    void enableResetText(bool);
    void enableResetAllFormat(bool);

    //字体
    void setFont(const QFont& font);
    QFont font();

    //颜色
    void setTextColor(const QString&);
    QString textColor();
    void setTextBkColor(const QString&);
    QString textBkColor();

    //属性
    void setVirtualMode(bool);
    void enableShowEditBar(bool);
    void enableShowTab(bool);
    void enableHorizontalHeader(bool bEnable = true);
    void enableVerticalHeader(bool bEnable = true);
    void enablePrintColour(bool);
    void enableShowGrids(bool);
    void rowColRefresh();

    //操作
    bool mergeCell();
    bool isMergeCell();
    bool splitCell();
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
public:
    HGridCtrl* gridCtrl() {return m_pGridCtrl;}

signals:
    void gridcellclicked();
public slots:
    void gridCell_clicked(HCellID);
    void lineedit_textEdited(const QString &text);

private:
    bool m_bEnableShowEditBar;
    bool m_bEnableShowTab;
    bool m_bEnableVirtualMode;
    bool m_bHorizontalHeader;
    bool m_bVerticalHeader;
    bool m_bShowGrids;
    bool m_bPrintColour;
private:
    HGridCtrl* m_pGridCtrl;
    long m_nNumSheets;
    QLabel* m_rowColLabel;
    QLineEdit* m_inputLineEdit;
};

#endif // HREPORTWIDGET_H
