#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H

#include <QObject>

#include "database.h"
#include "attribute.h"
#include "row.h"

#include <Models/tablemodel.h>

#include <QPointer>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>
#include <QMap>
#include <QElapsedTimer>

namespace Database {

class Database;

//! Dieses Interface dient dazu, der template-Klasse Table signals und slots, sowie ein Dasein als QObject zu ermöglichen.
/*!
  In Qt ist es nicht möglich dass template-Klassen QObjects sind oder mit Hilfe des Q_OBJECT Macros über signals und slots verfügen. Aus diesem Grund haben wir diese Elternklasse, von der Table erben kann, die diese Funktionalitäten enthält und damit auch für seine Kindklasse bereitstellt.
  */
class TableBase : public AttributeOwner
{
    Q_OBJECT
public:
    /*!
      Erstellt ein Tabellen-Objekt mit Namen \a name, in der Datenbank \a database.

      \param name Der Name dieser Tabelle in der Datenbank.
      \param database Die Datenbank, die diese Tabelle enthält.
      */
    TableBase(const QString &name);

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

    virtual void registerRowType(Row *row) = 0;

    void addColumn(AttributeBase * attribute);

    /*!
      Gibt alle Attribute dieser Row zurück.

      \return Alle Attribute dieser Row
      */
    QList<AttributeBase*> attributes() const;

    /*!
      Gibt das Attribut mit dem Namen \p name oder 0 zurück, falls es dieses nicht gibt.

      \return das Attribut mit dem Namen \p name oder 0, falls es dieses nicht gibt.
      */
    AttributeBase *attribute(const QString &name) const;

    virtual Models::TableModelBase *model() const = 0;

    void deleteRow(Row *row);

    virtual void insertRow(Row *row) = 0;

protected:
    friend class Database;

    /*!
      Erstellt die Tabelle in der Datenbank.
      */
    void createTableIfNotExists();

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

    QString m_name; //!< Der Name der Tabelle.
};

//! Repräsentiert eine Tabelle in der Datenbank.
/*!
  Von dieser Klasse erben alle anderen Tabellen. Nur die Klasse Database selber kann Tabellen erstellen und verwalten.
  */
template <class RowType>
class Table : public TableBase
{
public:
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
    void insertRow(Row *row);

    void registerRowType(Row *row);

    void addDependingAttributeToRows(AttributeBase* parent, AttributeBase* child);

    Models::TableModel<RowType, Table<RowType> > *model() const;

    Attribute<QMap<int, RowType* >, Table<RowType>, Table<RowType> > *rows() const;

    static QMap<QString, AttributeBase*> *registeredAttributes();

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

    Attribute<QMap<int, RowType* >, Table<RowType>, Table<RowType> > *m_rows; //!< Alle Rows gecacht
    Models::TableModel<RowType, Table<RowType> > *m_model;
    static QMap<QString, AttributeBase*> *registeredDatabaseAttributes();

private:
    /*!
      Erstellt die Tabelle in der Datenbank.
      */
    void createTable();

    void alterTableToContainAllAttributes();

    /*!
      Befüllt die Liste aller in der Tabelle enthaltenen Rows. Wird von Database nach createTableIfNotExists() aufgerufen.
      */
    void initializeCache();

    void initializeRowCaches();
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
    RowRegistrar(TableBase* table, Row *row);
};

/*!
  Mit Hilfe dieses Macros registrieren sich Tabellen bei der Datenbank.<br>
  Authoren von Tabellen müssen nur noch irgendwo im namespace Database REGISTER_TABLE(<Klassenname der Tabelle>) aufrufen.
  */
#define REGISTER_ASROWTYPE(Classname, BaseClassname) \
    RowRegistrar _register_ ## Classname(BaseClassname ## s::instance(), new Classname());

template<class RowType>
QMap<QString, AttributeBase*> *Table<RowType>::registeredDatabaseAttributes()
{
    static QMap<QString, AttributeBase*> *attributes = new QMap<QString, AttributeBase*>();
    return attributes;
}

template<class RowType>
QMap<QString, AttributeBase*> *Table<RowType>::registeredAttributes()
{
    static QMap<QString, AttributeBase*> *attributes = new QMap<QString, AttributeBase*>();
    return attributes;
}

template<class RowType>
Table<RowType>::Table(const QString &name) :
    TableBase(name),
    m_rows(new Attribute<QMap<int, RowType* >, Table<RowType>, Table<RowType> >("rows", "rows", this)),
    m_model(0)
{
}

template<class RowType>
Models::TableModel<RowType, Table<RowType> > *Table<RowType>::model() const
{
    return m_model;
}

template<class RowType>
Attribute<QMap<int, RowType* >, Table<RowType>, Table<RowType> > *Table<RowType>::rows() const
{
    return m_rows;
}

template<class RowType>
void Table<RowType>::createTable()
{
    qDebug() << "Table<RowType>::createTable: Creating table" << m_name;

    QString createQuery = "CREATE TABLE "+m_name+" (id INTEGER PRIMARY KEY";

    foreach(AttributeBase *attribute, *registeredDatabaseAttributes())
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
	qWarning() << "Table<RowType>::createTable: " << createQuery;
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

    QMap<QString, AttributeBase*> unknownAttributes = *registeredDatabaseAttributes();

    while(pragma.next())
    {
	unknownAttributes.remove(pragma.value(1).toString());
    }

    foreach(AttributeBase * attribute, unknownAttributes.values())
    {
	addColumn(attribute);
    }

    if(pragma.lastError().isValid())
    {
	qDebug() << "Table::Table: Pragma failed for table" << m_name;
    }

    pragma.finish();
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
        RowType *rowInstance = createRowInstance(id);

        if(rowInstance)
        {
            m_rows->value().insert(id, rowInstance);
        }
    }
    select.finish();

    initializeRowCaches();

    m_model = new Models::TableModel<RowType, Table<RowType> >(this);
}

template<class RowType>
void Table<RowType>::initializeRowCaches()
{
    QString queryString("SELECT id");

    foreach(AttributeBase *attribute, *registeredDatabaseAttributes())
    {
	queryString += ", "+attribute->name();
    }

    queryString += " FROM "+m_name;

    QSqlQuery select = QSqlQuery(Database::instance()->sqlDatabaseLocked());
    select.exec(queryString);
    Database::instance()->releaseDatabaseLock();

    if(select.lastError().isValid())
    {
	qWarning() << "Table::initializeRowCaches: Could not read the whole table "<< m_name <<".";
	qWarning() << "Table::initializeRowCaches: " << select.lastError();
	qWarning() << "Table::initializeRowCaches: " << select.lastQuery();
    }

    while(select.next())
    {
	QList<AttributeBase*> databaseAttributes = registeredDatabaseAttributes()->values();
	for(int i = 0; i < databaseAttributes.size(); ++i)
	{
	    AttributeBase *attribute = databaseAttributes.at(i);
	    Row *row = m_rows->value().value(select.value(0).toInt());

            if(attribute && row)
            {
                QString name = attribute->name();
                AttributeBase *rowAttribute = row->attribute(name);
                if(rowAttribute != 0)
                {
                    rowAttribute->changeValue(select.value(i+1),false);
                }
            }
	}
    }
}

template<class RowType>
QPointer<RowType> Table<RowType>::createRowInstance(int id)
{
    return new RowType(id,this);
}


template<class RowType>
QList<RowType*> Table<RowType>::allRows()
{
    return m_rows->value().values();
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
	list.insert(list.size(), rowById(select.value(0).toInt()));
    }
    select.finish();

    return list;
}

template<class RowType>
QPointer<RowType> Table<RowType>::rowById(int id)
{
    return m_rows->value().value(id,0);
}

template<class RowType>
void Table<RowType>::insertRow(Row *row)
{
    QSqlQuery create = QSqlQuery(Database::instance()->sqlDatabaseLocked());

    QString queryString =   "INSERT INTO "+m_name+" (id";
    foreach(AttributeBase *attribute, row->databaseAttributes())
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

    foreach(AttributeBase *attribute, row->databaseAttributes())
    {
	create.addBindValue(attribute->toString());
    }

    create.exec();
    Database::instance()->releaseDatabaseLock();
    int id = create.lastInsertId().toInt();
    row->setId(id);

    m_model->beginInsertRows(QModelIndex(),m_rows->value().size(),m_rows->value().size());
    m_rows->value().insert(id,static_cast<RowType*>(row));
    m_rows->emitChanged();

    foreach(Row *childRow, row->childRows())
    {
	childRow->table()->insertRow(childRow);
    }

    m_model->updateData();

    foreach(AttributeBase *attribute, row->attributes())
    {
	connect(attribute,SIGNAL(changed()),m_model,SLOT(on_attribute_changed()));
    }

    m_model->endInsertRows();

    create.finish();

    if(create.lastError().isValid())
    {
	qWarning() << "Table::insertRow: " << create.lastError();
    }
}

template<class RowType>
void Table<RowType>::registerRowType(Row *row)
{
    foreach(AttributeBase *attribute, row->attributes())
    {
	//qDebug() << "Table::registerRowType: Attribute" << attribute->name() << "registered at table" << m_name;
	registeredAttributes()->insert(attribute->name(), attribute);
    }
    foreach(AttributeBase *attribute, row->databaseAttributes())
    {
	//qDebug() << "Table::registerRowType: Databaseattribute" << attribute->name() << "registered at table" << m_name;
	registeredDatabaseAttributes()->insert(attribute->name(), attribute);
    }
}

template<class RowType>
void Table<RowType>::addDependingAttributeToRows(AttributeBase* parent, AttributeBase* child)
{
    foreach(RowType* type,this->allRows()){
	//type->parent->addDependingAttribute(child);
    }
}

} // namespace Database

#define STRINGIZE(s) # s
#define XSTR(s) STRINGIZE(s)

#define START_TABLE_DECLARATION( RowClassname ) \
    namespace Database { \
    class RowClassname ## s : public Table<RowClassname> \
    { \
    DECLARE_SINGLETON( RowClassname ## s ) \
    public: \
    RowClassname ## s();

#define END_TABLE_DECLARATION() \
    }; \
    } // namespace Database

#define START_TABLE_IMPLEMENTATION( RowClassname ) \
    namespace Database { \
    IMPLEMENT_SINGLETON( RowClassname ## s ) \
    RowClassname ## s::RowClassname ## s() : \
    Table<RowClassname>(QString(XSTR(RowClassname ## s) "").toLower()) \
    { \
    } \
    REGISTER_TABLE(RowClassname ## s)


#define END_TABLE_IMPLEMENTATION() } // namespace Database

#endif // DATABASE_TABLE_H
