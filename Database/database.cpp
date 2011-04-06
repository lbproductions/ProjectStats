#include "database.h"

#include "table.h"

#include <QDebug>
#include <QSqlError>

namespace Database {

Database::~Database()
{
    m_sqlDatabase.close();
}

void Database::initialize(const QFile &databaseFile)
{
    qDebug() << "Database::loadFile: Opening database file " << databaseFile.fileName();

    m_databaseFilename = databaseFile.fileName();

    //Erstelle die Datenbank
    m_sqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
    m_sqlDatabase.setDatabaseName(databaseFile.fileName());

    //Oeffne datenbank
    if(!m_sqlDatabase.open("projectstats","projectstats"))
    {
        qCritical() << "Database::loadFile: Could not open database file " << databaseFile.fileName();
        qCritical() << "Database::loadFile: " << m_sqlDatabase.lastError();
        return;
    }

    createTables();
}

void Database::createTables()
{
    foreach(QPointer<TableInterface> table, m_tables)
    {
        Q_ASSERT(!table.isNull());

        table->createTableIfNotExists();
    }
}

void Database::registerTable(TableInterface *table)
{
    m_tables.append(table);
}

QSqlDatabase Database::Database::sqlDatabase() const
{
    return m_sqlDatabase;
}

TableRegistrar::TableRegistrar(TableInterface *table)
{
    Database::instance()->registerTable(table);
}

} // namespace Database
