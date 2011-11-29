#include "database.h"

#include "table.h"

#include <QDebug>
#include <QSqlError>
#include <QElapsedTimer>

#include "game.h"

namespace Database {

IMPLEMENT_SINGLETON(Database)

Database::Database() :
    m_databaseFilename(QString()),
    m_tables(QList<TableBase* >()),
    m_sqlDatabase(QSqlDatabase()),
    m_databaseLock(QMutex::Recursive)
{

}

Database::~Database()
{
    m_sqlDatabase.close();
}

QList<TableBase* > Database::tables() const
{
    return m_tables;
}

void Database::initialize(const QFile &databaseFile)
{
    qDebug() << "Database::loadFile: Opening database file " << databaseFile.fileName();

    QElapsedTimer timer;
    timer.start();

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

    qDebug() << "Database::loadFile: Opening database file took" << timer.elapsed() << "ms";
}

void Database::createTables()
{
    qDebug() << "Database::createTables: Creating " << m_tables.count() << " tables";
    qDebug() << this;
    foreach(TableBase* table, m_tables)
    {
        table->createTableIfNotExists();
        table->alterTableToContainAllAttributes();
    }

    QElapsedTimer timer;
    timer.start();

    static_cast<TableBase*>(Places::instance())->initializeCache();
    static_cast<TableBase*>(Games::instance())->initializeCache();

    qDebug() << "Database::createTables: Initializing caches for Games took" << timer.restart() << "ms";
    foreach(TableBase* table, m_tables)
    {
        table->initializeCache();

        qDebug() << "Database::createTables: Initializing cache for" <<  table->name() << "took" << timer.restart() << "ms";
    }

    foreach(TableBase* table, m_tables)
    {
        table->initializeRowCaches();

        qDebug() << "Database::createTables: Initializing attributes for" <<  table->name() << "took" << timer.restart() << "ms";
    }


}

void Database::registerTable(TableBase *table)
{
    m_tables.append(table);
    qDebug() << "Database::registerTable: Table " << table->name() << " registered.";
    qDebug() << this;
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
