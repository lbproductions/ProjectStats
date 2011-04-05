#include "database.h"

#include "table.h"

#include <QDebug>
#include <QSqlError>

namespace Database {

Database::Database(const QString &databaseFilename, QObject *parent) :
    QObject(parent)
{
    const QFile databaseFile(databaseFilename);
    initialize(databaseFile);
}

Database::Database(const QFile &databaseFile, QObject *parent) :
    QObject(parent)
{
    initialize(databaseFile);
}

Database::~Database()
{
    m_database.close();
}

void Database::initialize(const QFile &databaseFile)
{
    qDebug() << "Database::loadFile: Opening database file " << databaseFile.fileName();

    m_databaseFilename = databaseFile.fileName();

    //Erstelle die Datenbank
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName(databaseFile.fileName());

    //Oeffne datenbank
    if(!m_database.open("projectstats","projectstats"))
    {
        qCritical() << "Database::loadFile: Could not open database file " << databaseFile.fileName();
        qCritical() << "Database::loadFile: " << m_database.lastError();
        return;
    }

    createTables();
}

void Database::createTables()
{
    //m_players->initializeTableIfNotExists();

    //m_players->initializeData();
}


} // namespace Database
