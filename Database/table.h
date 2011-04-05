#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H

#include <QObject>

#include <QPointer>

namespace Database {

class Database;

class Table : public QObject
{
    Q_OBJECT
protected:
    /*!
      Erstellt ein Tabellen-Objekt mit Namen \a name, in der Datenbank \a database.

      \param name Der Name dieser Tabelle in der Datenbank.
      \param database Die Datenbank, die diese Tabelle enthält.
      */
    Table(const QString &name, Database *database);

    QString m_name; //!< Der Name der Tabelle.
    QPointer<Database> m_database; //!< Die Datenbank, in der die Tabelle liegt.

private:
    friend class Database;

    /*!
      Überprueft, ob die Tabelle in der Datenbank existiert und erstellt sie gegebenenfalls (durch initializeTable()). Wird von Database aufgerufen.
      */
    void initializeTableIfNotExists();

};

} // namespace Database

#endif // DATABASE_TABLE_H
