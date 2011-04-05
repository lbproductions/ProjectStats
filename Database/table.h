#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H

#include <QObject>

#include "database.h"

#include <QPointer>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>

namespace Database {

class Database;

class TableInterface : public QObject
{
    Q_OBJECT
protected:
    friend class Database;
    virtual void initializeTable() = 0;
    virtual void initializeTableIfNotExists() = 0;
};

//! Repräsentiert eine Tabelle in der Datenbank.
/*!
  Von dieser Klasse erben alle anderen Tabellen. Nur die Klasse Database selber kann Tabellen erstellen und verwalten.
  */
template <class RowType>
class Table : public TableInterface
{
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

    /*!
      Gibt alle Elemente dieser Tabelle zurück.
      \see getAll(const QString &condition)
      \return Eine Liste aller Objekte in dieser Tabelle.
      */
    QList<QPointer<RowType> > allRows();

    /*!
      Gibt alle Elemente dieser Tabelle zurück, die die SQL-Condition \a condition erfüllen. Diese erhalten den Typen des Templatearguments.

      \param condition Eine SQL-Condition, die die Elemente der Tabelle filtert.
      \return Eine Liste aller Objekte in dieser Tabelle.
      */
    QList<QPointer<RowType> > rowsBySqlCondition(const QString &condition);

protected:
    /*!
      Erstellt ein Tabellen-Objekt mit Namen \a name, in der Datenbank \a database.

      \param name Der Name dieser Tabelle in der Datenbank.
      \param database Die Datenbank, die diese Tabelle enthält.
      */
    Table(const QString &name);

    virtual QPointer<RowType> createRow(int id);

    QString m_name; //!< Der Name der Tabelle.

private:
    /*!
      Überprueft, ob die Tabelle in der Datenbank existiert und erstellt sie gegebenenfalls (durch initializeTable()). Wird von Database aufgerufen.
      */
    void initializeTableIfNotExists();

    void initializeTable();
};

template<class RowType>
Table<RowType>::Table(const QString &name) :
    TableInterface(),
    m_name(name)
{
}

template<class RowType>
void Table<RowType>::initializeTableIfNotExists()
{
    QSqlQuery select(Database::instance()->sqlDatabase());

    //Prüfe, ob der Name dieser Tabelle in der Datenbank existiert...
    QString query = "SELECT name FROM sqlite_master WHERE name='" + m_name + "';";
    select.exec(query);

    select.first();

    //... falls nicht muss die Tabelle initialisiert werden.
    if(select.lastError().isValid() || !select.value(0).isValid())
    {
        qDebug() << "Table::Table: Table does not exist: " << m_name;
        initializeTable();
    }
    select.finish();
}

template<class RowType>
int Table<RowType>::rowCount() const
{
    QSqlQuery q = query("SELECT COUNT(id) FROM "+m_name);
    q.first();
    int count = q.value(0).toInt();
    q.finish();
    return count;
}

template<class RowType>
QSqlQuery Table<RowType>::query(const QString &queryString) const
{
    QSqlQuery query(Database::instance()->sqlDatabase());
    query.exec(queryString);

    if(query.lastError().isValid())
    {
        qWarning() << "Table::query: Could not run query.";
        qWarning() << "Table::query: " << query.lastError();
        qWarning() << "Table::query: " << queryString;
        return QSqlQuery();
    }

    return query;
}

template<class RowType>
void Table<RowType>::initializeTable()
{
    //ein objekt vom Typ RowType erstellen
    //über alle seine attribute iterieren und die tabelle dementsprechend erstellen.
}

template<class RowType>
QList<QPointer<RowType> > Table<RowType>::allRows()
{
    return rowsBySqlCondition("");
}

template<class RowType>
QList<QPointer<RowType> > Table<RowType>::rowsBySqlCondition(const QString &condition)
{
    QList<QPointer<RowType> > list;

    QSqlQuery select = QSqlQuery(Database::instance()->sqlDatabase());
    QString query = "SELECT id FROM "+m_name+" "+condition;

    select.exec(query);

    if(select.lastError().isValid())
    {
        qWarning() << "Table::getAll: Could not read the whole table "<< m_name <<".";
        qWarning() << "Table::getAll: " << select.lastError();
        qWarning() << "Table::getAll: " << select.lastQuery();
        return list;
    }

    while(select.next())
    {
        list.insert(list.size(), createRow(select.value(0).toInt()));
    }
    select.finish();

    return list;
}

template<class RowType>
QPointer<RowType> Table<RowType>::createRow(int id)
{
    return new RowType(id,this);
}

} // namespace Database

#endif // DATABASE_TABLE_H
