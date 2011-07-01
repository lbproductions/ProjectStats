#ifndef DATABASE_ROW_H
#define DATABASE_ROW_H


#include <QObject>
#include "attribute.h"

#include "database.h"

#include <QPointer>
#include <QSqlQuery>

#include <Database/attributelist.h>
#include <Database/attributehash.h>

#include <Gui/Details/detailswidget.h>

namespace Database {

class TableBase;
class AttributeBase;

//! Repräsentiert eine Row einer Tabelle.
/*!
  Alle Reihen wie z.B. Player oder Game erben von dieser Klasse. Sie bietet ihnen durch set() und get() eine einfache Schnittstelle zu ihren Daten.
  */
class Row : public AttributeOwner
{
    Q_OBJECT
public:
    Row() : AttributeOwner(Database::instance()) {}
    Row(const Row &other) : AttributeOwner(other.parent()) {}

    /*!
      \return Die ID der Reihe.
      */
    int id() const;

    bool isValid();

    /*!
      Löscht diese Row aus der Datenbank. Das Objekt selber wird nicht gelöscht sondern nur mit der ID -1 invalidiert.
      */
    void deleteFromDatabase();

    /*!
      Liest den Wert \p key  dieser Reihe aus der Datenbank aus.

      \param key Die Spalte, die ausgelesen werden soll.
      \return Den Wert, den die Spalte \p key  in dieser Reihe hat.
      */
    QVariant get(const QString &key) const;

    /*!
      Setzt den Wert \p key  dieser Reihe auf \p value .

      \param key Der zu ändernde Wert.
      \param value Der Wert auf den \p key  gesetzt werden soll.
      \return true, wenn die Operation erfolgreich in die Datenbank eingetragen wurde.
      */
    bool set(const QString &key, const QVariant &value);

    /*!
      Gibt alle Attribute dieser Row zurück.

      \return Alle Attribute dieser Row
      */
    QList<AttributeBase*> attributes() const;

    /*!
      Gibt alle Datenbankattribute dieser Row zurück.

      \return Alle Datenbankattribute dieser Row
      */
    QList<AttributeBase*> databaseAttributes() const;

    /*!
      Gibt das Attribut mit dem Namen \p name oder 0 zurück, falls es dieses nicht gibt.

      \return das Attribut mit dem Namen \p name oder 0, falls es dieses nicht gibt.
      */
    AttributeBase *attribute(const QString &name) const;

    void setId(int id);

    virtual QString mimeType() const = 0;

    QList<Row*> childRows() const;

    virtual Gui::Details::DetailsWidget* detailsWidget();

protected:
    /*!
      Erstellt ein Row Objekt, welches in der Tabelle \p table  die Daten mit der ID  \p id repräsentiert.
      */
    explicit Row(int id, TableBase *table);

    /*!
      Setzt den Wert \p key  dieser Reihe auf \p value  für die Reihe, für die die SQL-Conditon \p condition ilt. Diese Methode wird nur von set(const QString &key, const QVariant &value) verwendet.
      */
    bool set(const QString &key, const QVariant &value, const QString &condition);

    /*!
      Liest den Wert \p key  der Reihe, für die die SQL-Conditon \p condition gilt, aus der Datenbank aus. Diese Methode wird nur von get(const QString &key) verwendet.
      */
    QVariant get(const QString &key, const QString &condition) const;

    /*!
      Führt den gegebenen Query \p queryString in der Datenbank aus, falls diese Reihe valid ist. In dem QSqlQuery Objekt wurde schon exec() ausgeführt und sollte auf jeden fall mit finish() beendet werden.

      \param queryString Der SQL-Query, der ausgeführt werden soll.
      \return Ein QSqlQuery Objekt, welches den gegeben Query repräsentiert.
      \see Table::query(const QString &queryString)
      */
    QSqlQuery query(const QString &queryString) const;

    /*!
      Fügt das gegebene Attribut zu den Attributen der Row hinzu.<br>
      Ist es ein Datenbankattribute wird es außerdem zusätzlich zu den Datenbankattributen hinzugefügt.

      \param attribute Das Attribut, das hinzugefügt werden soll.
      */
    void registerAttribute(AttributeBase *attribute);

    void addChildRow(Row *row);

    void addChildRows(QList<Row *> rows);

    int m_id; //!< Die ID dieser Row
    QPointer<TableBase> m_table; //!< Die Tabelle, in die diese Row liegt
    QHash<QString, AttributeBase* > m_attributes; //!< Alle Attribute der Row. Muss von Kindklassen befüllt werden.
    QList<AttributeBase*> m_databaseAttributes; //!< Alle Datenbankattribute
    QList<Row*> m_childRows; //!< Alle Rows, die logisch zu dieser Row gehören (z.B. Round gehört zu Game)

private:
    friend class TableBase;

    /*!
      Überprueft, ob die eine Row mit dieser ID tatsächlich existiert.
      Ist das nicht der Fall wird ID auf -1 gesetzt und die Row damit invalid.
      Wird vom Konstruktor aufgerufen.
      */
    void checkId();
};

} // namespace Database

#define START_ROW_DECLARATION( RowClassname, RowSuperclassname ) \
    namespace Database { \
    template<class RowType> \
    class Table; \
    class RowClassname : public RowSuperclassname \
    {

#define DECLARE_ROW_CONSTRUCTORS( RowClassname, RowBaseclassname ) \
    public: \
	RowClassname(const RowClassname &other); \
	RowClassname(); \
	RowClassname(int id, TableBase *table); \
	void initializeAttributes(); \
	QString mimeType() const;

#define COMMA ,

#define END_ROW_DECLARATION( RowClassname ) \
    }; \
    } \
    Q_DECLARE_METATYPE(Database::RowClassname) \
    Q_DECLARE_METATYPE(Database::RowClassname*) \
    Q_DECLARE_METATYPE(Database::AttributeList<Database::RowClassname*>) \
    Q_DECLARE_METATYPE(Database::AttributeHash<Database::RowClassname* COMMA int>) \
    Q_DECLARE_METATYPE(QList<Database::RowClassname*>) \
    Q_DECLARE_METATYPE(QMap<int COMMA Database::RowClassname*>)

#define START_ROW_IMPLEMENTATION( RowClassname, RowBaseclassname, RowSuperclassname  ) \
    namespace Database { \
    REGISTER_ASROWTYPE( RowClassname, RowBaseclassname ) \
    RowClassname::RowClassname() : RowSuperclassname(0,RowBaseclassname ## s::instance()) { initializeAttributes(); }  \
    RowClassname::RowClassname(const RowClassname &other) : RowSuperclassname(other.m_id, other.m_table) { initializeAttributes(); } \
    RowClassname::RowClassname(int id, TableBase *table) : RowSuperclassname(id,table) { initializeAttributes(); } \
    void RowClassname::initializeAttributes()

#define END_ROW_IMPLEMENTATION() } // namespace Database

#endif // DATABASE_ROW_H
