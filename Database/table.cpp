#include "table.h"

#include "database.h"

#include <QSqlError>
#include <QVariant>
#include <QDebug>

namespace Database {

Table::Table(const QString &name, Database *database) :
    QObject(database),
    m_name(name),
    m_database(database)
{
}

void Table::initializeTableIfNotExists()
{
    QSqlQuery select(Database::instance()->sqlDatabase());

    //Prüfe, ob der Name dieser Tabelle in der Datenbank existiert...
    QString query = "SELECT name FROM sqlite_master WHERE name='" + m_name + "';";
    select.exec(query);

    select.first();

    //... falls nicht muss die Tabelle initialisiert werden.
    if(select.lastError().isValid() || !select.value(0).isValid())
    {
        qDebug() << "Table::Table: Table does not exist: " << m_name;
        initializeTable();
    }
    select.finish();
}

int Table::rowCount() const
{
    QSqlQuery q = query("SELECT COUNT(id) FROM "+m_name);
    q.first();
    int count = q.value(0).toInt();
    q.finish();
    return count;
}

QSqlQuery Table::query(const QString &queryString) const
{
    QSqlQuery query(Database::instance()->sqlDatabase());
    query.exec(queryString);

    if(query.lastError().isValid())
    {
        qWarning() << "Table::query: Could not run query.";
        qWarning() << "Table::query: " << query.lastError();
        qWarning() << "Table::query: " << queryString;
        return QSqlQuery();
    }

    return query;
}

void Table::initializeTable()
{
}

} // namespace Database
