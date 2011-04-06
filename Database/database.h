#ifndef DATABASE_DATABASE_H
#define DATABASE_DATABASE_H

#include <QObject>
#include <singleton.h>

#include <QSqlDatabase>
#include <QFile>
#include <QPointer>

namespace Database {

class TableInterface;

//! Repräsentiert eine komplette Datenbank.
/*!
  Hier werden alle enthaltenen Tabellen verwaltet. Zu diesem Zweck müssen sich alle Tabellen bei der Datenbank registrieren.<br>
  Dabei geht es vor allem um das Erstellen der jeweiligen Table-Objekte und Aufrufen der zugehörigen Methoden Table::initializeTableIfNotExists() und Table::initializeData().<br>
  Anschließend wird durch diese Klasse nur noch einfacher Zugriff auf die Tabellen geboten.
  */
class Database : public QObject, public Singleton<Database>
{
    Q_OBJECT
public:
    /*!
      Öffnet eine gegebene Datenbankdatei.
      Existiert die Datei nicht, wird die Datenbank und alle zugehoerigen Tabellen neu erstellt.
      */
    void initialize(const QFile &databaseFile);

    /*!
      Gibt die zu Grunde liegende QSqlDatabase zurueck.

      \return die zu Grunde liegende QSqlDatabase.
      */
    QSqlDatabase sqlDatabase() const;

    /*!
      Schließt die QSqlDatabase.
      */
    ~Database();

private:
    friend class TableRegistrar;
    /*!
      Registriert die Tabelle \p table bei der Datenbank. Keine Tabelle muss diese Methode per Hand aufrufen, sondern stattdessen das Macro REGISTER_TABLE(Tabelle) verwenden.
      */
    void registerTable(TableInterface *table);

    /*!
      Erstellt alle Tabellen neu, falls sie nicht existieren und initialisiert ihre caches.
      */
    void createTables();

    QString m_databaseFilename; //!< Die Datenbankdatei
    QList<QPointer<TableInterface> > m_tables; //!< Alle registrierten Tabellen
    QSqlDatabase m_sqlDatabase; //!< Die eigentliche Datenbank
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
    TableRegistrar(TableInterface *table);
};

/*!
  Mit Hilfe dieses Macros registrieren sich Tabellen bei der Datenbank.<br>
  Authoren von Tabellen müssen nur noch irgendwo im namespace Database REGISTER_TABLE(<Klassenname der Tabelle>) aufrufen.
  */
#define REGISTER_TABLE(classname) \
    TableRegistrar _register_ ## classname(classname::instance());

} // namespace Database

#endif // DATABASE_DATABASE_H
