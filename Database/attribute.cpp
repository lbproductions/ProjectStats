#include "attribute.h"

#include "row.h"

namespace Database {

AttributeInterface::AttributeInterface(Row *row) :
    QObject(row),
    m_row(row)
{
}

} // namespace Database
