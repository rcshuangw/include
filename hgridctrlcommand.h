#ifndef HGRIDCTRLCOMMAND_H
#define HGRIDCTRLCOMMAND_H
///////////////////////////////////////
//撤销、删除类
///////////////////////////////////////
#include <QUndoCommand>
#include "hgridctrl.h"
class HUndoCommand : public QUndoCommand
{
public:
    enum Type{
        Color    = 0,   //颜色
        Border   = 1,   //边框
        Font     = 2,   //字体
        Format   = 3,   //格式
        Merge    = 4,   //合并
        Split    = 5,   //拆分
        Paste    = 6,   //粘贴
        Delete   = 7,   //删除
        Resize   = 8,   //改变大小
    };

    HUndoCommand();
    ~HUndoCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
    //virtual void notify();
protected:
    bool bFirstTime;
};

//删除
class HDelUndoCommand : public HUndoCommand
{
public:
    HDelUndoCommand(HGridCtrl* pGridCtrl,const HCellRange& range,QString strText);
    ~HDelUndoCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    HCellRange cellRange;
    QString strDeleteText;
    HGridCtrl* m_pGridCtrl;
};

//粘贴
class HPasteUndoCommand : public HUndoCommand
{
public:
    HPasteUndoCommand(HGridCtrl* pGridCtrl,const HCellRange& range,QString strNewText,QString strOldText);
    ~HPasteUndoCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    HCellRange cellRange;
    QString strNewText;
    QString strOldText;
    HGridCtrl* m_pGridCtrl;
};


//字体
class HFontUndoCommand : public HUndoCommand
{
public:
    HFontUndoCommand(HGridCtrl* pGridCtrl,const HCellRange& range,const QFont& newFont,const QFont& oldFont);
    ~HFontUndoCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    HCellRange m_cellRange;
    QFont m_newFont;
    QFont m_oldFont;
    HGridCtrl* m_pGridCtrl;
};

#endif // HGRIDCTRLCOMMAND_H
