#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H

#include <QObject>

#include "database.h"
#include "attribute.h"
#include "row.h"

#include <QPointer>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>

namespace Database {

class Database;

//! Dieses Interface dient dazu, der template-Klasse Table signals und slots, sowie ein Dasein als QObject zu ermöglichen.
/*!
  In Qt ist es nicht möglich dass template-Klassen QObjects sind oder mit Hilfe des Q_OBJECT Macros über signals und slots verfügen. Aus diesem Grund haben wir diese Elternklasse, von der Table erben kann, die diese Funktionalitäten enthält und damit auch für seine Kindklasse bereitstellt.
  */
class TableInterface : public QObject
{
    Q_OBJECT
public:
    /*!
     \return Den Namen der Tabelle.
      */
    virtual QString name() const = 0;

    /*!
      Diese Methode übernimmt lästige Überprüfungen beim Ausführen eines Queries in der Tabelle, wie das Checken, ob die Datenbank null ist.<br>
      Anschließen wird ein QSqlQuery Objekt zurückgegeben, welches zuvor schon mit exec() ausgeführt wurde.<br>
      Dieses Objekt sollte in jedem Fall nach Benutzung mit finish() beendet werden.

      \param queryString Der Query, der ausgeführt werden soll.
      \return Ein QSqlQuery Objekt, welches den gegebenen Query repräsentiert.
      */
    virtual QSqlQuery query(const QString &queryString) const = 0;

    virtual void registerRowType(Row *row) = 0;

protected:
    friend class Database;

    /*!
      Erstellt die Tabelle in der Datenbank.
      */
    virtual void createTableIfNotExists() = 0;

    /*!
      Überprueft, ob die Tabelle in der Datenbank existiert und erstellt sie gegebenenfalls (durch initializeTable()). Wird von Database aufgerufen.
      */
    virtual void createTable() = 0;

    /*!
      */
    virtual void alterTableToContainAllAttributes() = 0;

    /*!
      Befüllt die Liste aller in der Tabelle enthaltenen Rows. Wird von Database nach createTableIfNotExists() aufgerufen.
      */
    virtual void initializeCache() = 0;
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
    QList<RowType*> allRows();

    /*!
      Gibt die Row mit der ID \p id zurück, oder 0, falls die Row nicht in dieser Tabelle existiert.

      \return die Row mit der ID \p id, oder 0, falls die Row nicht in dieser Tabelle existiert.
      */
    QPointer<RowType> rowById(int id);

    /*!
      Gibt alle Elemente dieser Tabelle zurück, die die SQL-Condition \a condition erfüllen. Diese erhalten den Typen des Templatearguments.

      \param condition Eine SQL-Condition, die die Elemente der Tabelle filtert.
      \return Eine Liste aller Objekte in dieser Tabelle.
      */
    QList<RowType *> rowsBySqlCondition(const QString &condition);

    /*!
      Fügt die Row \p row der Datenbank hinzu.<br>
      Diese Row sollte eine nicht valide Row mit ID = 0 sein, mit korrektem Typ und allen entscheidenden Attributen gesetzt.
      */
    void insertRow(RowType *row);

    /*!

      */
    void registerRowType(Row *row);

protected:
    /*!
      Erstellt ein Tabellen-Objekt mit Namen \a name, in der Datenbank \a database.

      \param name Der Name dieser Tabelle in der Datenbank.
      \param database Die Datenbank, die diese Tabelle enthält.
      */
    Table(const QString &name);

    /*!
      Factory-Methode zum Erstellen der korrekten Row-Instanzen. In dieser Standardimplementierung wird immer eine Row vom template-Typ RowTyp erstellt.<br>
      Tabellen können diese Methode reimplementieren, um verschiedene Instanzen von Rows zu erstellen (z.B. Game, LiveGame, DokoLiveGame, ...).
      */
    virtual QPointer<RowType> createRowInstance(int id);

    QString m_name; //!< Der Name der Tabelle.
    QHash<int, RowType* > m_rows; //!< Alle Rows gecacht
    static QHash<QString, AttributeInterface*> *registeredAttributes();

private:
    /*!
      Überprueft, ob die Tabelle in der Datenbank existiert und erstellt sie gegebenenfalls (durch initializeTable()). Wird von Database aufgerufen.
      */
    void createTableIfNotExists();

    /*!
      Erstellt die Tabelle in der Datenbank.
      */
    void createTable();

    void alterTableToContainAllAttributes();

    void addColumn(AttributeInterface* attribute);

    /*!
      Befüllt die Liste aller in der Tabelle enthaltenen Rows. Wird von Database nach createTableIfNotExists() aufgerufen.
      */
    void initializeCache();
};

//! Diese Klasse wird vom Macro REGISTER_ASROWTYPE() verwendet um Rows (bzw. deren Attribute) bei einer Tabelle zu registrieren.
/*!
  Eine Row kann ihre Attribute also bei einer Tabelle registrieren, indem sie REGISTER_ASROWTYPE(<Klassenname der Oberklasse>, <Klassenname des Rowtyps>) aufruft.
  */
class RowRegistrar
{
public:
    /*!
      Registriert die Row \p row bei der Tabelle \table.
      */
    RowRegistrar(TableInterface* table, Row *row);
};

/*!
  Mit Hilfe dieses Macros registrieren sich Tabellen bei der Datenbank.<br>
  Authoren von Tabellen müssen nur noch irgendwo im namespace Database REGISTER_TABLE(<Klassenname der Tabelle>) aufrufen.
  */
#define REGISTER_ASROWTYPE(Classname, BaseClassname) \
    RowRegistrar _register_ ## Classname(BaseClassname ## s::instance(), new Classname());

template<class RowType>
QHash<QString, AttributeInterface*> *Table<RowType>::registeredAttributes()
{
    static QHash<QString, AttributeInterface*> *attributes = new QHash<QString, AttributeInterface*>();
    return attributes;
}

template<class RowType>
Table<RowType>::Table(const QString &name) :
    TableInterface(),
    m_name(name),
    m_rows(QHash<int, RowType* >())
{
}

template<class RowType>
void Table<RowType>::createTableIfNotExists()
{
    QSqlQuery select(Database::instance()->sqlDatabaseLocked());

    //Prüfe, ob der Name dieser Tabelle in der Datenbank existiert...
    QString query = "SELECT name FROM sqlite_master WHERE name='" + m_name + "';";
    select.exec(query);
    Database::instance()->releaseDatabaseLock();

    select.first();

    //... falls nicht muss die Tabelle initialisiert werden.
    if(select.lastError().isValid() || !select.value(0).isValid())
    {
        qDebug() << "Table::Table: Table does not exist: " << m_name;
        createTable();
    }
    select.finish();
}


template<class RowType>
void Table<RowType>::createTable()
{
    qDebug() << "Table<RowType>::createTable: Creating table" << m_name;

    QString createQuery = "CREATE TABLE "+m_name+" (id INTEGER PRIMARY KEY";

    foreach(AttributeInterface *attribute, *registeredAttributes())
    {
        createQuery += ", " + attribute->name() + " " + attribute->sqlType();
    }

    createQuery += ")";

    QSqlQuery create(Database::instance()->sqlDatabaseLocked());
    create.exec(createQuery);
    Database::instance()->releaseDatabaseLock();

    create.finish();
    if(create.lastError().isValid())
    {
        qWarning() << "Table<RowType>::createTable: " << create.lastError();
    }
}

template<class RowType>
void Table<RowType>::alterTableToContainAllAttributes()
{
    QSqlQuery pragma(Database::instance()->sqlDatabaseLocked());

    //Prüfe, ob der Name dieser Tabelle in der Datenbank existiert...
    QString query = "PRAGMA table_info(" + m_name + ")";
    pragma.exec(query);
    Database::instance()->releaseDatabaseLock();

    pragma.first();

    if(pragma.lastError().isValid() || !pragma.value(0).isValid())
    {
        qDebug() << "Table::Table: Pragma failed for table" << m_name;
    }

    QHash<QString, AttributeInterface*> unknownAttributes = *registeredAttributes();

    while(pragma.next())
    {
        unknownAttributes.remove(pragma.value(1).toString());
    }

    foreach(AttributeInterface * attribute, unknownAttributes.values())
    {
        addColumn(attribute);
    }

    pragma.finish();
}

template<class RowType>
void Table<RowType>::addColumn(AttributeInterface * attribute)
{
    qDebug() << "Table::addcolumn: Adding new column" << attribute->name() << "to table" << m_name;
    QSqlQuery alter(Database::instance()->sqlDatabaseLocked());

    QString query = "ALTER TABLE " + m_name + " ADD " + attribute->name() + " " + attribute->sqlType();
    qDebug() << query;
    alter.exec(query);
    Database::instance()->releaseDatabaseLock();

    alter.first();

    if(alter.lastError().isValid())
    {
        qDebug() << "Table::addColumn: Alter failed for table" << m_name;
        qDebug() << "Table::addColumn:" << alter.lastError();
    }
}

template<class RowType>
void Table<RowType>::initializeCache()
{
    QSqlQuery select = QSqlQuery(Database::instance()->sqlDatabaseLocked());
    QString query("SELECT id FROM "+m_name);

    select.exec(query);
    Database::instance()->releaseDatabaseLock();

    if(select.lastError().isValid())
    {
        qWarning() << "Table::initializeCache: Could not read the whole table "<< m_name <<".";
        qWarning() << "Table::initializeCache: " << select.lastError();
        qWarning() << "Table::initializeCache: " << select.lastQuery();
    }

    int id = 0;
    while(select.next())
    {
        id = select.value(0).toInt();
        m_rows.insert(id, createRowInstance(id));
    }
    select.finish();
}

template<class RowType>
QPointer<RowType> Table<RowType>::createRowInstance(int id)
{
    return new RowType(id,this);
}

template<class RowType>
QString Table<RowType>::name() const
{
    return m_name;
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
    QSqlQuery query(Database::instance()->sqlDatabaseLocked());
    query.exec(queryString);
    Database::instance()->releaseDatabaseLock();

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
QList<RowType*> Table<RowType>::allRows()
{
    return m_rows.values();
}

template<class RowType>
QList<RowType*> Table<RowType>::rowsBySqlCondition(const QString &condition)
{
    QList<RowType*> list;

    QSqlQuery select = QSqlQuery(Database::instance()->sqlDatabaseLocked());
    QString query = "SELECT id FROM "+m_name+" "+condition;
    select.exec(query);
    Database::instance()->releaseDatabaseLock();

    if(select.lastError().isValid())
    {
        qWarning() << "Table::getAll: Could not read the whole table "<< m_name <<".";
        qWarning() << "Table::getAll: " << select.lastError();
        qWarning() << "Table::getAll: " << select.lastQuery();
        return list;
    }

    while(select.next())
    {
        list.insert(list.size(), createRowInstance(select.value(0).toInt()));
    }
    select.finish();

    return list;
}

template<class RowType>
QPointer<RowType> Table<RowType>::rowById(int id)
{
    return m_rows.value(id,0);
}

template<class RowType>
void Table<RowType>::insertRow(RowType *row)
{
    qDebug() << "Table<RowType>::insertRow: Inserting row";

    QSqlQuery create = QSqlQuery(Database::instance()->sqlDatabaseLocked());

    QString queryString =   "INSERT INTO "+m_name+" (id";
    foreach(AttributeInterface *attribute, row->databaseAttributes())
    {
        queryString += ", "+attribute->name();
    }
    queryString += ") VALUES            (null";
    for(int i = 0; i < row->databaseAttributes().size(); ++i)
    {
        queryString += ", ?";
    }
    queryString += ")";

    create.prepare(queryString);

    foreach(AttributeInterface *attribute, row->databaseAttributes())
    {
        create.addBindValue(attribute->stringValue());
    }

    create.exec();
    Database::instance()->releaseDatabaseLock();
    int id = create.lastInsertId().toInt();
    row->setId(id);
    create.finish();

    if(create.lastError().isValid())
    {
        qWarning() << "Table::insertRow: " << create.lastError();
    }
}

template<class RowType>
void Table<RowType>::registerRowType(Row *row)
{
    foreach(AttributeInterface *attribute, row->databaseAttributes())
    {
        qDebug() << "Table::registerRowType: Attribute" << attribute->name() << "registered at table" << m_name;
        registeredAttributes()->insert(attribute->name(), attribute);
    }
}

} // namespace Database

#define STRINGIZE(s) # s
#define XSTR(s) STRINGIZE(s)

#define DECLARE_TABLE( RowClassname ) \
    namespace Database { \
    class RowClassname ## s : public Table<RowClassname>, public Singleton<RowClassname ## s> \
    { \
    public: \
    RowClassname ## s(); \
    }; \
    } // namespace Database

#define IMPLEMENT_TABLE( RowClassname ) \
    namespace Database { \
    RowClassname ## s::RowClassname ## s() : \
    Table<RowClassname>(QString(XSTR(RowClassname ## s) "").toLower()), \
        Singleton<RowClassname ## s>() \
    { \
    } \
    REGISTER_TABLE(RowClassname ## s) \
    } // namespace Database

#endif // DATABASE_TABLE_H
