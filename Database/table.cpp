#include "table.h"

namespace Database {

RowRegistrar::RowRegistrar(TableInterface* table, Row *row)
{
    table->registerRowType(row);
}

} // namespace Database
