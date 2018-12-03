#ifndef HREPORTWIDGET_H
#define HREPORTWIDGET_H

#include <QWidget>
#include "hgridcelldef.h"
#include "hgridglobal.h"
class HGridCtrl;
class QLabel;
class QLineEdit;
class HGridCtrlInfo;
class HGridCell;
//tab页的具体内容
class GRIDCTRL_EXPORT HGridCtrlWidget : public QWidget
{
    Q_OBJECT
public:
    HGridCtrlWidget(QWidget* parent = 0);

    void initReportWidget(quint8 type);
    void setGridCtrlItem(HGridCtrlInfo* pItem);
    void getGridCtrlItem(HGridCtrlInfo* pItem);

signals:
    void gridcellclickded(HGridCell*);
public slots:
    void gridCell_Clicked(HGridCell*);
private:
    HGridCtrl* m_pGridCtrl;
    long m_nNumSheets;
    QLabel* m_rowColLabel;
    QLineEdit* m_inputLineEdit;
    quint8 m_uGridReportType;
    HGridCtrlInfo* m_pGridCtrlInfo;
};

#endif // HREPORTWIDGET_H
