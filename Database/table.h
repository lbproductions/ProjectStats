#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H

#include <QObject>

#include <QPointer>
#include <QSqlQuery>

namespace Database {

class Database;

//! Repräsentiert eine Tabelle in der Datenbank.
/*!
  Von dieser Klasse erben alle anderen Tabellen. Nur die Klasse Database selber kann Tabellen erstellen und verwalten.
  */
class Table : public QObject
{
    Q_OBJECT
public:
    /*!
      \return Die Anzahl der Reihen in der Tabelle.
      */
    int rowCount() const;

    /*!
     \return Den Namen der Tabelle.
      */
    QString name() const;

    /*!
      Diese Methode übernimmt lästige Überprüfungen beim Ausführen eines Queries in der Tabelle, wie das Checken, ob die Datenbank null ist.<br>
      Anschließen wird ein QSqlQuery Objekt zurückgegeben, welches zuvor schon mit exec() ausgeführt wurde.<br>
      Dieses Objekt sollte in jedem Fall nach Benutzung mit finish() beendet werden.

      \param queryString Der Query, der ausgeführt werden soll.
      \return Ein QSqlQuery Objekt, welches den gegebenen Query repräsentiert.
      */
    QSqlQuery query(const QString &queryString) const;

protected:
    /*!
      Erstellt ein Tabellen-Objekt mit Namen \a name, in der Datenbank \a database.

      \param name Der Name dieser Tabelle in der Datenbank.
      \param database Die Datenbank, die diese Tabelle enthält.
      */
    Table(const QString &name, Database *database);

    void initializeTable();

    QString m_name; //!< Der Name der Tabelle.
    QPointer<Database> m_database; //!< Die Datenbank, in der die Tabelle liegt.
    QPointer<Table> m_tableInstance; //!< Die statische Instanz dieser Tabelle

private:
    friend class Database;

    /*!
      Überprueft, ob die Tabelle in der Datenbank existiert und erstellt sie gegebenenfalls (durch initializeTable()). Wird von Database aufgerufen.
      */
    void initializeTableIfNotExists();

};

} // namespace Database

#endif // DATABASE_TABLE_H
