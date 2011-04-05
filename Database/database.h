#ifndef DATABASE_DATABASE_H
#define DATABASE_DATABASE_H

#include <QObject>

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
class Database : public QObject
{
    Q_OBJECT
public:
    static Database *instance();

    /*!
      Öffnet eine gegebene Datenbankdatei.
      Existiert die Datei nicht, wird die Datenbank und alle zugehoerigen Tabellen neu erstellt.
      */
    void initialize(const QFile &databaseFile);

    QSqlDatabase sqlDatabase() const;

    /*!
      Schließt die QSqlDatabase.
      */
    ~Database();

private:
    class Guard
    {
    public:
        ~Guard();
    };
    friend class Guard;

    friend class TableRegistrar;
    void registerTable(TableInterface *table);

    /*!
      Erstellt alle Tabellen neu, falls sie nicht existieren und initialisiert ihre caches.
      */
    void createTables();

    QString m_databaseFilename; //!< Die Datenbankdatei
    QList<QPointer<TableInterface> > m_tables; //!< Alle registrierten Tabellen
    QSqlDatabase m_sqlDatabase; //!< Die eigentliche Datenbank
    static QPointer<Database> m_instance; //!< Die eine Instanz der Datenbank
};

class TableRegistrar
{
public:
    TableRegistrar(TableInterface *table);
};

#define REGISTER_TABLE(classname) \
    TableRegistrar _register_ ## classname(classname::instance());

} // namespace Database

#endif // DATABASE_DATABASE_H
