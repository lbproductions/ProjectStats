#include "database.h"

#include "table.h"

#include <QDebug>
#include <QSqlError>

namespace Database {

IMPLEMENT_SINGLETON(Database)

Database::Database() :
    m_databaseFilename(QString()),
    m_tables(QList<QPointer<TableBase> >()),
    m_sqlDatabase(QSqlDatabase()),
    m_databaseLock(QMutex::Recursive)
{

}

Database::~Database()
{
    m_sqlDatabase.close();
}

QList<QPointer<TableBase> > Database::tables() const
{
    return m_tables;
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
    foreach(QPointer<TableBase> table, m_tables)
    {
        Q_ASSERT(!table.isNull());

        table->createTableIfNotExists();
        table->alterTableToContainAllAttributes();
    }

    foreach(QPointer<TableBase> table, m_tables)
    {
        Q_ASSERT(!table.isNull());

        qDebug() << "Database::createTables: Initializing cache for table " << table->name();

        table->initializeCache();
    }
}

void Database::registerTable(TableBase *table)
{
    m_tables.append(table);
    qDebug() << "Database::registerTable: Table " << table->name() << " registered";
}

QSqlDatabase Database::sqlDatabaseLocked()
{
    m_databaseLock.lock();
    return m_sqlDatabase;
}

void Database::releaseDatabaseLock()
{
    m_databaseLock.unlock();
}

TableRegistrar::TableRegistrar(TableBase *table)
{
    Database::instance()->registerTable(table);
}

} // namespace Database
