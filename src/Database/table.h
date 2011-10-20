#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H

#include <QObject>

#include "database.h"
#include "mappingattribute.h"
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

//! Dieses Interface dient dazu, der template-Klasse Table signals und slots,
//! sowie ein Dasein als QObject zu ermöglichen.
/*!
    In Qt ist es nicht möglich dass template-Klassen QObjects sind oder mit
    Hilfe des Q_OBJECT Macros über signals und slots verfügen.

    Aus diesem Grund haben wir diese Elternklasse, von der Table erben kann, die
    diese Funktionalitäten enthält und damit auch für seine Kindklasse
    bereitstellt.
  */
class TableBase : public AttributeOwner
{
    Q_OBJECT
public:
    /*!
        Erstellt ein Tabellen-Objekt mit Namen \a name.
      */
    TableBase(const QString &name);

    /*!
        Gibt die Anzahl der Reihen in der Tabelle zurück.
      */
    int rowCount() const;

    /*!
        Gibt den Namen der Tabelle zurück.
      */
    QString name() const;

    /*!
        Führt den Query \a queryString aus und gibt das entstehende QSqlQuery
        Objekt zurück.

        Diese Methode übernimmt lästige Überprüfungen beim Ausführen eines
        Queries in der Tabelle, wie das Checken, ob die Datenbank \c null ist.

        Anschließen wird ein QSqlQuery Objekt zurückgegeben, welches zuvor schon
        mit exec() ausgeführt wurde.

        Dieses Objekt sollte in jedem Fall nach Benutzung mit finish() beendet
        werden.
      */
    QSqlQuery query(const QString &queryString) const;

    void addColumn(AttributeBase * attribute);

    /*!
        Jeder AttributeOwner muss attributes() implementieren.

        Von einer Tabelle wird diese Information jedoch nicht benötigt, daher
        wird hier eine leere Liste zurückgegeben.

        \warning Nicht benutzen!
      */
    QList<AttributeBase*> attributes() const;

    /*!
        Jeder AttributeOwner muss attributes() implementieren.

        Von einer Tabelle wird diese Information jedoch nicht benötigt, daher
        wird hier \c 0 zurückgegeben.

        \warning Nicht benutzen!
      */
    AttributeBase *attribute(const QString &name) const;

    /*!
        Gibt das Modell, das alle Reihen dieser Tabelle enthält, zurück.
      */
    virtual Models::TableModelBase *model() = 0;

    /*!
        Löscht die Reihe \a row aus der Datenbank.

        Zunächst werden alle Kinder (Row::childRows()) der Reihe gelöscht.
        Anschließend wird die Reihe selber aus der Datenbank und dem Cache der
        Tabelle gelöscht und ihre ID auf \c -1 gesetzt.

        \a row selber wird nicht gelöscht und verweilt im Speicher, bis dies
        entweder manuell geschieht, oder das Programm beendet wird.

        \row bleibt ein Kind dieser Tabelle.

        \warning Es wird nicht überprüft, ob \a row überhaupt in dieser Tabelle
        liegt, sondern schlicht die Reihe mit der ID der gegebenen Reihe aus
        dieser Tabelle gelöscht.
      */
    void deleteRow(Row *row);

    /*!
        Fügt die Reihe \a row dieser Tabelle hinzu.

        Zu aller erst wird die Reihe in die Datenbank eingefügt, wobei schon
        alle Werte der Attribute korrekt gesetzt werden. Die dabei entstehende
        ID wird der Reihe zugewiesen.

        Anschließend wird die Reihe dem Cache dieser Tabelle hinzugefügt und
        alle Kinder (Row::childRows()) der Reihe in ihre jeweiligen Tabellen
        eingetragen.

        Alle diese Änderungen werden dann dem Modell dieser Tabelle mitgeteilt.

        Zuletzt werden alle Attribute der Reihe mit dem Modell der Tabelle
        verknüpft (via Row::changed() und
        Models::TableModelBase::on_attribute_changed()).

        \warning Gehört \a row nicht in diese Tabelle, fliegt uns alles um die
        Ohren!
      */
    virtual void insertRow(Row *row) = 0;

protected:
    friend class Database;
    friend class RowRegistrar;

    /*!
        Erstellt die Tabelle in der Datenbank.

        Überprüft, ob die Tabelle in der Datenbank existiert, und falls das
        nicht der Fall ist, wird die Tabelle durch createTable() samt aller
        Spalten erstellt.
      */
    void createTableIfNotExists();

    /*!
        Erstellt die Tabelle in der Datenbank.

        Überprüft nicht, ob sie schon existiert, sondern führt schlicht den
        passenden SQL Befehl aus.

        Wird nur von createTableIfNotExists() aufgerufen.
      */
    virtual void createTable() = 0;

    /*!
        Fügt registrierte Spalten der Datenbank hinzu, die noch nicht in der
        Datenbank existieren.

        Wird von Database::createTables() aufgerufen und verwendet addColumn(),
        um die Spalten zu erzeugen.
      */
    virtual void alterTableToContainAllAttributes() = 0;

    /*!
        Registriert einen neuen Typen bei dieser Tabelle. Dies fügt die
        Attribute und Datenbankattribute der gegebenen Row zu den registrierten
        Attributen dieser Tabelle hinzu.

        Wird nur von RowRegistrar beim Programmstart aufgerufen.

        \see Table<RowType>::registeredAttributes()
        \see Table<RowType>::registeredDatabaseAttributes()
      */
    virtual void registerRowType(Row *row) = 0;

    /*!
        Befüllt die Liste aller in der Tabelle enthaltenen Rows und erzeugt das
        Model dieser Tabelle.

        Wird nur von Database::createTables() aufgerufen.

        Kann nur einmal aufgerufen werden. Alle weiteren Aufrufe haben keinen
        Effekt.
      */
    virtual void initializeCache() = 0;

    /*!
        Initialisiert die Werte der Datenbankattribute aller Reihen dieser
        Tabelle.

        Im Anschluss wird ein Hintergrundtask mit niedrigster Priorität
        gestartet, der die Berechnung der restlichen Attribute beginnt.

        Wird nur von Database::createTables() aufgerufen.
      */
    virtual void initializeRowCaches() = 0;

    QString m_name; //!< Der Name dieser Tabelle.
};

template<class RowType>
class TableCache;

//! Repräsentiert eine Tabelle in der Datenbank.
/*!
    Von dieser Klasse erben alle anderen Tabellen. Nur die Klasse Database
    selber kann Tabellen erstellen und verwalten.
  */
template <class RowType>
class Table : public TableBase
{
public:
    /*!
        Gibt alle Reihen dieser Tabelle zurück.

        \see getAll(const QString &condition)
      */
    QList<RowType*> allRows();

    /*!
        Gibt die Row mit der ID \p id zurück, oder \c 0, falls die Row nicht in
        dieser Tabelle existiert.
      */
    QPointer<RowType> rowById(int id);

    /*!
        Gibt alle Elemente dieser Tabelle zurück, die die SQL-Condition
        \a condition erfüllen.
      */
    QList<RowType *> rowsBySqlCondition(const QString &condition);

    void insertRow(Row *row);

    void registerRowType(Row *row);

    Models::TableModel<RowType, Table<RowType> > *model();

    /*!
        Gibt ein MappingAttribute zurück, das von IDs auf die zugehörigen Reihen
        abbildet.
      */
    MappingAttribute<int, RowType*, Table<RowType>, Table<RowType> > *rows() const;

    /*!
        Gibt eine QMap zurück, die von einem Namen auf die zugehörige
        AttributeBase abbildet.

        Enthalten sind alle Attribute, die ein bei dieser Tabelle registrierter
        Typ haben kann.
      */
    static QMap<QString, AttributeBase*> *registeredAttributes();

protected:
    /*!
        Erstellt ein Tabellen-Objekt mit dem Namen \a name.
      */
    Table(const QString &name);

    /*!
        Factory-Methode zum Erstellen der korrekten Row-Instanzen.

        In dieser Standardimplementierung wird immer eine Row vom template-Typ
        RowTyp erstellt.

        Tabellen können diese Methode reimplementieren, um verschiedene
        Instanzen von Rows zu erstellen (z.B. Game, LiveGame, DokoLiveGame,
        ...).
      */
    virtual QPointer<RowType> createRowInstance(int id);

    TableCache<RowType> *m_rows; //!< Alle Rows gecacht
    QList<RowType*> m_allRows;
    Models::TableModel<RowType, Table<RowType> > *m_model; //!< Das Modell, das alle Reihen enthält
    static QMap<QString, AttributeBase*> *registeredDatabaseAttributes(); //!< Alle bei dieser Tabelle registrierten Attribute
    bool m_cacheInitialized; //!< \c true, falls initializeCache() aufgerufen wurde

private:
    void createTable();

    void alterTableToContainAllAttributes();

    void initializeCache();

    void initializeRowCaches();
};

//! Ein Task zum initialisieren aller Nicht-Datenbank-Attribute
/*!
    Dieser Task läuft mit geringer Priorität und startet die asynchrone
    Berechnung aller Attribute aller Reihen seiner Tabelle.

    Wird nur von Table<RowType>::initializeRowCaches() aufgerufen.
  */
template<class TableType>
class AttributeInitilizerTask : public Task
{
public:
    /*!
        Erstellt einen Task, dessen execute() die Attribute der Reihen der
        Tabelle \a parent initialisiert.
      */
    explicit AttributeInitilizerTask(TableType* parent);

    /*!
        Startet die asynchrone Berechnung aller Attribute der Reihen der Tabelle
        m_parent.
      */
    void execute();

private:
    TableType* m_parent; //!< Die zu initialisierende Tabelle
};

//! Ein Cache für die Reihen in der zugehörigen Tabelle.
/*!
    Diese Klasse wird benötigt, damit Table<RowType> eine befreundete Klasse
    sein kann.
  */
template<class RowType>
class TableCache : public MappingAttribute<int, RowType*, Table<RowType>, Table<RowType> >
{
public:
    TableCache(Table<RowType>* table);

    friend class Table<RowType>;
};

//! Diese Klasse wird vom Macro REGISTER_ASROWTYPE() verwendet um Rows (bzw.
//! deren Attribute) bei einer Tabelle zu registrieren.
/*!
    Eine Row kann ihre Attribute also bei einer Tabelle registrieren, indem sie
    REGISTER_ASROWTYPE() aufruft.

    Diese Klasse darf außer durch das Macro nie instantiiert werden.
  */
class RowRegistrar
{
public:
    /*!
      Registriert \p row bei \a table.
      */
    RowRegistrar(TableBase* table, Row *row);
};

/*!
    Mit Hilfe dieses Macros registrieren sich Reihen bei ihrer Tabelle.

    Es muss normalerweise nicht von Hand aufgerufen werden, da es im Macro
    START_ROW_IMPLEMENTATION() enthalten ist.
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
    m_rows(new TableCache<RowType>(this)),
    m_allRows(QList<RowType*>()),
    m_model(0),
    m_cacheInitialized(false)
{
}

template<class RowType>
Models::TableModel<RowType, Table<RowType> > *Table<RowType>::model()
{
    if(!m_model)
    {
        m_model = new Models::TableModel<RowType, Table<RowType> >(this);
    }
    return m_model;
}

template<class RowType>
MappingAttribute<int, RowType*, Table<RowType>, Table<RowType> > *Table<RowType>::rows() const
{
    return m_rows;
}

template<class RowType>
void Table<RowType>::createTable()
{
    qDebug() << "Table<RowType>::createTable: Creating table" << m_name;

    // Query zusammensetzen
    QString createQuery = QLatin1String("CREATE TABLE ") + m_name + QLatin1String(" (id INTEGER PRIMARY KEY");
    foreach(AttributeBase *attribute, *registeredDatabaseAttributes())
    {
        createQuery += QLatin1String(", ") + attribute->name() + QLatin1String(" ") + attribute->sqlType();
    }
    createQuery += QLatin1String(")");

    // und ausführen
    QSqlQuery create(Database::instance()->sqlDatabaseLocked());
    create.exec(createQuery);
    Database::instance()->releaseDatabaseLock();

    create.finish();

    // Fehlerbehandlung
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

    // Dieser Query findet die Namen aller Spalten dieser Tabelle
    QString query = QLatin1String("PRAGMA table_info(") + m_name + QLatin1String(")");
    pragma.exec(query);
    Database::instance()->releaseDatabaseLock();

    // Aus der Liste aller registrierten Attribute werden diejenigen entfernt,
    // die in der Datenbank standen
    QMap<QString, AttributeBase*> unknownAttributes = *registeredDatabaseAttributes();
    while(pragma.next())
    {
        unknownAttributes.remove(pragma.value(1).toString());
    }

    // Alle übrigen werden als neue Spalte hinzugefügt
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
    // Kann hierdurch mehrfach aufgerufen werden ohne Schaden anzurichten
    if(m_cacheInitialized)
    {
        return;
    }

    // Alle Reihen selecten
    QSqlQuery select = QSqlQuery(Database::instance()->sqlDatabaseLocked());
    QString query(QLatin1String("SELECT id FROM ")+m_name);
    select.setForwardOnly(true);
    select.exec(query);
    Database::instance()->releaseDatabaseLock();

    if(select.lastError().isValid())
    {
	qWarning() << "Table::initializeCache: Could not read the whole table "<< m_name <<".";
	qWarning() << "Table::initializeCache: " << select.lastError();
	qWarning() << "Table::initializeCache: " << select.lastQuery();
    }

    m_rows->setEmitChange(false); // Beim initialisieren soll noch nicht
                                  // Row::change() emittet werden.
    m_rows->value(); // Den Cache einmal initialisieren (ist dann leer)
    m_allRows.reserve(select.size());

    // Zu allen IDs eine Instanz erzeugen und dem Cache hinzufügen.
    int id = 0;
    while(select.next())
    {
	id = select.value(0).toInt();
        RowType *rowInstance = createRowInstance(id);

        if(rowInstance) // createRowInstance() kann auch entscheiden, dass es
                        // zu der ID keine Reihe erzeugen will
        {
            m_rows->m_value.insert(id, rowInstance);
            m_allRows.append(rowInstance);
        }
    }
    select.finish();

    m_rows->setEmitChange(true); // Später hinzugefügte Reihen sollen durchaus
                                 // ein emit change() hervorrufen.

    m_cacheInitialized = true;
}

template<class RowType>
void Table<RowType>::initializeRowCaches()
{
    // Query zusammensetzen
    QString queryString("SELECT id");
    foreach(AttributeBase *attribute, *registeredDatabaseAttributes())
    {
        queryString += QLatin1String(", ")+attribute->name();
    }
    queryString += QLatin1String(" FROM ")+m_name;

    // und ausführen
    QSqlQuery select = QSqlQuery(Database::instance()->sqlDatabaseLocked());
    select.setForwardOnly(true);
    select.exec(queryString);
    Database::instance()->releaseDatabaseLock();

    if(select.lastError().isValid())
    {
	qWarning() << "Table::initializeRowCaches: Could not read the whole table "<< m_name <<".";
	qWarning() << "Table::initializeRowCaches: " << select.lastError();
	qWarning() << "Table::initializeRowCaches: " << select.lastQuery();
    }

    // außerhalb der Schleife, weil QMap::values() recht langsam ist
    QList<AttributeBase*> databaseAttributes = registeredDatabaseAttributes()->values();

    // Über alle Ergebnisse Iterieren und die Datenbankattribute initialisieren
    while(select.next())
    {
        Row *row = m_rows->m_value.value(select.value(0).toInt());

        if(row) // weiß nicht, warum manche row nicht auch in m_rows ist...
        {
            for(int i = 0; i < databaseAttributes.size(); ++i)
            {
                AttributeBase* rowAttribute = row->attribute(databaseAttributes.at(i)->name());
                if(rowAttribute) // Nicht jedes Attribut ist in jeder Row enthalten!
                {
                    rowAttribute->changeValue(select.value(i+1),false);
                }
            }
        }
    }

    // Einen Hintergrundtask starten, der alle Nicht-Datenbank-Attribute initialisiert.
    // Läuft mit sehr niedriger Priorität
    AttributeInitilizerTask<Table<RowType> >* task = new AttributeInitilizerTask<Table<RowType> >(this);
    TaskScheduler::instance()->schedule(task);
}

template<class TableType>
AttributeInitilizerTask<TableType>::AttributeInitilizerTask(TableType* parent) :
    Task(QThread::LowestPriority,parent),
    m_parent(parent)
{
}

template<class TableType>
void AttributeInitilizerTask<TableType>::execute()
{
    //Einfach über alle Reihen...
    foreach(Row* row, m_parent->allRows())
    {
        //...und jeweils alle Attribute iterieren
        foreach(AttributeBase* attribute, row->attributes())
        {
            attribute->startCalculationTask();
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
    return m_allRows;
}

template<class RowType>
QList<RowType*> Table<RowType>::rowsBySqlCondition(const QString &condition)
{
    QList<RowType*> list;

    //Query zusammensetzen und ausführen
    QSqlQuery select = QSqlQuery(Database::instance()->sqlDatabaseLocked());
    QString query = QLatin1String("SELECT id FROM ") + m_name + QLatin1String(" ") + condition;
    select.setForwardOnly(true);
    select.exec(query);
    Database::instance()->releaseDatabaseLock();

    if(select.lastError().isValid())
    {
	qWarning() << "Table::getAll: Could not read the whole table "<< m_name <<".";
	qWarning() << "Table::getAll: " << select.lastError();
	qWarning() << "Table::getAll: " << select.lastQuery();
	return list;
    }

    list.reserve(select.size()); // Schonmal Platz für alle Elemente schaffen

    // Rows hinzufügen
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
    //Query zusammensetzen...
    QSqlQuery create = QSqlQuery(Database::instance()->sqlDatabaseLocked());
    QString queryString = QLatin1String("INSERT INTO ") + m_name + QLatin1String(" (id");

    //...zuerst die Attribute...
    foreach(AttributeBase *attribute, row->databaseAttributes())
    {
        queryString += QLatin1String(", ") + attribute->name();
    }

    //...dann deren Werte als ? einfügen...
    queryString += QLatin1String(") VALUES (null");
    for(int i = 0; i < row->databaseAttributes().size(); ++i)
    {
        queryString += QLatin1String(", ?");
    }
    queryString += QLatin1String(")");

    create.prepare(queryString);

    //...und die tatsächlichen Werte daran binden
    foreach(AttributeBase *attribute, row->databaseAttributes())
    {
	create.addBindValue(attribute->toString());
    }

    //Query auführen
    create.exec();
    Database::instance()->releaseDatabaseLock();

    //ID setzen
    int id = create.lastInsertId().toInt();
    row->setId(id);

    //Dem Modell (und damit glaube ich den Views) mitteilen, dass sich gleich was ändern wird
    m_model->beginInsertRows(QModelIndex(),m_rows->value().size(),m_rows->value().size());

    //Reihe dem Cache hinzufügen
    RowType* r = static_cast<RowType*>(row);
    m_rows->m_value.insert(id,r);
    m_allRows.append(r);
    m_rows->emitChanged();

    //Alle Kinder der Reihe ihrer Tabelle hinuzfügen
    foreach(Row *childRow, row->childRows())
    {
	childRow->table()->insertRow(childRow);
    }

    //Dem Modell (einmal zu viel?) mitteilen, dass es Änderungen gab
    m_model->updateData();

    //Alle Attribute mit dem Modell verknüpfen
    foreach(AttributeBase *attribute, row->attributes())
    {
        connect(attribute,SIGNAL(changed(::Database::AttributeBase*)),m_model,SLOT(on_attribute_changed(::Database::AttributeBase*)));
    }

    //und die Änderung abschließen
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
    //Alle Attribute landen in den registeredAttributes
    foreach(AttributeBase *attribute, row->attributes())
    {
        //qDebug() << "Table::registerRowType: Attribute" << attribute->name() << "registered at table" << m_name;
        registeredAttributes()->insert(attribute->name(), attribute);
    }

    //und die Datenbankattribute in den databaseAttributes
    foreach(AttributeBase *attribute, row->databaseAttributes())
    {
        //qDebug() << "Table::registerRowType: Databaseattribute" << attribute->name() << "registered at table" << m_name;
        registeredDatabaseAttributes()->insert(attribute->name(), attribute);
    }
}

template<class RowType>
TableCache<RowType>::TableCache(Table<RowType>* table) :
    MappingAttribute<int, RowType*, Table<RowType>, Table<RowType> >("rows","rows",table)
{
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
