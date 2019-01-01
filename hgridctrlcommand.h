#ifndef HGRIDCTRLCOMMAND_H
#define HGRIDCTRLCOMMAND_H
///////////////////////////////////////
//撤销、删除类
///////////////////////////////////////
#include <QUndoCommand>
#include "hgridcell.h"
class HUndoCommand : public QUndoCommand
{
public:
    enum Type{
        New = 0,            //新建
        Delete = 1,         //删除
        Paste = 2,          //粘贴
        Move = 3,           //移动
        Group = 4,          //组合
        UnGroup = 5,        //解除
        Rotate = 6,         //旋转
        Turn = 7,           //翻转
        Resize = 8,         //改变大小(包含手动改变大小，对齐，相等)
    };

    HUndoCommand();
    ~HUndoCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
    virtual void notify();
protected:
    bool bFirstTime;
};

//删除
class HDelUndoCommand : public HUndoCommand
{
public:
    HDelUndoCommand(const HCellRange& range,QString strText);
    ~HDelUndoCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    HCellRange cellRange;
    QString strDeleteText;
};

//粘贴
class HPasteUndoCommand : public HUndoCommand
{
public:
    HPasteUndoCommand(const HCellRange& range,QString strText);
    ~HPasteUndoCommand();
public:
    virtual int id() const;
    virtual void redo();
    virtual void undo();
protected:
    HCellRange cellRange;
    QString strPatstText;
};




#endif // HGRIDCTRLCOMMAND_H
