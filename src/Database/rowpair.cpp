#include "rowpair.h"

#include <Database/row.h>

using namespace Database;

RowPair::RowPair()
{
}

void RowPair::setRows(Row* first, Row* second)
{
    m_rowOne = first;
    m_rowTwo = second;
}

RowPair::RowPair(Row* first, Row* second)
{
    m_rowOne = first;
    m_rowTwo = second;
}

Row* RowPair::first() const
{
    return m_rowOne;
}

Row* RowPair::second() const
{
    return m_rowTwo;
}

