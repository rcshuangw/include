#if !defined(HCELLRANGE_H_)
#define HCELLRANGE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// The code contained in this file is based on the original
// WorldCom Grid control written by Joe Willcoxson,
//      mailto:chinajoe@aol.com
//      http://users.aol.com/chinajoe

#include "hgridglobal.h"
//表格ID类，仿Qt风格编写
#include <QDataStream>
class GRIDCTRL_EXPORT HCellID
{    
// Attributes
public:
    int row, col;
// Operations
public:
    explicit HCellID(int nRow = -1, int nCol = -1) : row(nRow), col(nCol) {}

    int isValid() const { return (row >= 0 && col >= 0); }
    int operator==(const HCellID& rhs) const { return (row == rhs.row && col == rhs.col); }
    int operator!=(const HCellID& rhs) const { return !operator==(rhs); }
};

//表格范围类，用于单元格的合并
class GRIDCTRL_EXPORT HCellRange
{ 
public:
#ifndef QT_NO_DATASTREAM
    friend GRIDCTRL_EXPORT QDataStream &operator<<(QDataStream &s, const HCellRange &cellRange);
    friend GRIDCTRL_EXPORT QDataStream &operator>>(QDataStream &s, HCellRange &cellRange);
#endif
public:
    
    HCellRange(int nMinRow = -1, int nMinCol = -1, int nMaxRow = -1, int nMaxCol = -1)
    {
        set(nMinRow, nMinCol, nMaxRow, nMaxCol);
    }

    void set(int nMinRow = -1, int nMinCol = -1, int nMaxRow = -1, int nMaxCol = -1);
    
    int  isValid() const;
    int  inRange(int row, int col) const;
    int  inRange(const HCellID& cellID) const;
    int  count() { return (m_nMaxRow - m_nMinRow + 1) * (m_nMaxCol - m_nMinCol + 1); }
    
    HCellID  topLeft() const;
    HCellRange  intersect(const HCellRange& rhs) const;
    
    int minRow() const {return m_nMinRow;}
    void setMinRow(int minRow) {m_nMinRow = minRow;}
    
    int minCol() const {return m_nMinCol;}
    void setMinCol(int minCol) {m_nMinCol = minCol;}
    
    int maxRow() const {return m_nMaxRow;}
    void setMaxRow(int maxRow) {m_nMaxRow = maxRow;}
    
    int maxCol() const {return m_nMaxCol;}
    void setMaxCol(int maxCol) {m_nMaxCol = maxCol;}

    int rowSpan() const {return m_nMaxRow - m_nMinRow + 1;}
    int colSpan() const {return m_nMaxCol - m_nMinCol + 1;}
    
    void operator=(const HCellRange& rhs);
    int  operator==(const HCellRange& rhs);
    int  operator!=(const HCellRange& rhs);
    
protected:
    int m_nMinRow;
    int m_nMinCol;
    int m_nMaxRow;
    int m_nMaxCol;
};


#endif // !defined(HCELLRANGE_H_)
