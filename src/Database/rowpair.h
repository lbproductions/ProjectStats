#ifndef ROWPAIR_H
#define ROWPAIR_H

#include <QObject>

namespace Database {

class Row;


class RowPair
{
public:
    explicit RowPair();

    explicit RowPair(Row* first, Row* second);

    void setRows(Row* first, Row* second);

    Row* first() const;

    Row* second() const;
    
signals:
    
public slots:

private:

    Row* m_rowOne;
    Row* m_rowTwo;
};
}

#endif // ROWPAIR_H
