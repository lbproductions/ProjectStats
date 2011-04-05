#include "table.h"

#include "database.h"

namespace Database {

Table::Table(const QString &name, Database *database) :
    QObject(database),
    m_name(name),
    m_database(database)
{
}

} // namespace Database
