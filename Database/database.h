#ifndef DATABASE_DATABASE_H
#define DATABASE_DATABASE_H

#include <QObject>

#include <QSqlDatabase>
#include <QFile>

namespace Database {

class Table;

//! Repräsentiert eine komplette Datenbank.
/*!
  Hier werden alle enthaltenen Tabellen verwaltet. Zu diesem Zweck müssen sich alle Tabellen bei der Datenbank registrieren.<br>
  Dabei geht es vor allem um das Erstellen der jeweiligen Table-Objekte und Aufrufen der zugehörigen Methoden Table::initializeTableIfNotExists() und Table::initializeData().<br>
  Anschließend wird durch diese Klasse nur noch einfacher Zugriff auf die Tabellen geboten.
  */
class Database : public QObject
{
    Q_OBJECT
public:
    /*!
      Öffnet eine gegebene Datenbankdatei.
      Existiert die Datei nicht, wird die Datenbank und alle zugehoerigen Tabellen neu erstellt.

      \see ::Database(const QFile &databaseFile, QObject *parent)
      */
    explicit Database(const QString &databaseFilename, QObject *parent = 0);

    /*!
      Öffnet eine gegebene Datenbankdatei.
      Existiert die Datei nicht, wird die Datenbank und alle zugehoerigen Tabellen neu erstellt.

      \see ::initialize(const QFile&);
      */
    explicit Database(const QFile &databaseFile, QObject *parent = 0);

    /*!
      Schließt die QSqlDatabase.
      */
    ~Database();

private:
    /*!
      Übernimmt die Arbeit der Konstruktoren.<br>
      Öffnet eine gegebene Datenbankdatei. Existiert die Datei nicht, wird die Datenbank und alle zugehörigen Tabellen neu erstellt.
      */
    void initialize(const QFile &databaseFile);

    /*!
      Erstellt alle Tabellen neu, falls sie nicht existieren und initialisiert ihre caches.
      */
    void createTables();

    QString m_databaseFilename; //!< Die Datenbankdatei
    QList<Table> m_tables; //!< Alle registrierten Tabellen
    QSqlDatabase m_database; //!< Die eigentliche Datenbank
};

} // namespace Database

#endif // DATABASE_DATABASE_H
