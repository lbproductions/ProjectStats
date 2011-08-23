#ifndef DATABASE_DATABASE_H
#define DATABASE_DATABASE_H

#include <QObject>
#include <Misc/singleton.h>

#include <QSqlDatabase>
#include <QFile>
#include <QPointer>
#include <QMutex>

namespace Database {

class TableBase;

//! Repräsentiert eine komplette Datenbank.
/*!
  Hier werden alle enthaltenen Tabellen verwaltet. Zu diesem Zweck müssen sich alle Tabellen bei der Datenbank registrieren.<br>
  Dabei geht es vor allem um das Erstellen der jeweiligen Table-Objekte und Aufrufen der zugehörigen Methoden Table::initializeTableIfNotExists() und Table::initializeData().<br>
  Anschließend wird durch diese Klasse nur noch einfacher Zugriff auf die Tabellen geboten.
  */
class Database : public QObject
{
    Q_OBJECT

    DECLARE_SINGLETON(Database)
public:
    explicit Database();

    /*!
      Öffnet eine gegebene Datenbankdatei.
      Existiert die Datei nicht, wird die Datenbank und alle zugehoerigen Tabellen neu erstellt.
      */
    void initialize(const QFile &databaseFile);

    /*!
      Gibt die zu Grunde liegende QSqlDatabase zurueck und sperrt diese für weitere Zugriffe.<br>
      Muss später mit releaseDatabase() wieder freigegeben werden.

      \return die zu Grunde liegende QSqlDatabase.
      */
    QSqlDatabase sqlDatabaseLocked();

    /*!
      Gibt die Datenbank wieder frei, falls diese gesperrt wurde.
      */
    void releaseDatabaseLock();

    /*!
      Schließt die QSqlDatabase.
      */
    ~Database();

    QList<QPointer<TableBase> > tables() const;

private:
    friend class TableRegistrar;

    /*!
      Registriert die Tabelle \p table bei der Datenbank. Keine Tabelle muss diese Methode per Hand aufrufen, sondern stattdessen das Macro REGISTER_TABLE(Tabelle) verwenden.
      */
    void registerTable(TableBase *table);

    /*!
      Erstellt alle Tabellen neu, falls sie nicht existieren und initialisiert ihre caches.
      */
    void createTables();

    QString m_databaseFilename; //!< Die Datenbankdatei
    QList<QPointer<TableBase> > m_tables; //!< Alle registrierten Tabellen
    QSqlDatabase m_sqlDatabase; //!< Die eigentliche Datenbank
    QMutex m_databaseLock; //!< Wird gesperrt, wenn jemand die Datenbank exklusiv haben will.
};

//! Diese Klasse wird vom Macro REGISTER_TABLE() verwendet um Tabellen bei der Datenbank zu registrieren.
/*!
  Eine Tabelle kann sich also bei der Datenbank registrieren, indem sie im namespace Database REGISTER_TABLE(<Klassenname der Tabelle>) aufruft.
  */
class TableRegistrar
{
public:
    /*!
      Registriert die Tabelle \p table bei der Datenbank.
      */
    TableRegistrar(TableBase *table);
};

/*!
  Mit Hilfe dieses Macros registrieren sich Tabellen bei der Datenbank.<br>
  Authoren von Tabellen müssen nur noch irgendwo im namespace Database REGISTER_TABLE(<Klassenname der Tabelle>) aufrufen.
  */
#define REGISTER_TABLE(classname) \
    TableRegistrar _register_ ## classname(classname::instance());

} // namespace Database

#endif // DATABASE_DATABASE_H
