#ifndef DATABASE_ROW_H
#define DATABASE_ROW_H


#include <QObject>
#include "attribute.h"

#include "database.h"

#include <QPointer>
#include <QSqlQuery>

namespace Gui{
    namespace Details{
        class DetailsWidget;
        class RowWidget;
        class RowWindow;
        class StatsWidget;
        class SummaryWidget;
    }
}

namespace Database {

class TableBase;
class AttributeBase;

//! Repräsentiert eine Reihe in einer Tabelle.
/*!
    Alle Reihen wie z.B. Player oder Game erben von dieser Klasse. Row ist
    selbstverständlich ein AttributeOwner, wodurch es Attribute enthalten kann,
    was eine Row schließlich ausmacht ;-)

    Man erbt eigentlich nicht "von Hand" von dieser Klasse sondern durch die
    Nutzung der Macros in diesem Header.

    Hier gehört viel mehr Doku hin (Macrobenutzung etc).
  */
class Row : public AttributeOwner
{
    Q_OBJECT
public:
    /*!
        \internal

        Dieser Standardkonstruktor wird benötigt damit Row ein QMetaType sein
        kann.
      */
    Row() : AttributeOwner(Database::instance()), m_id(0) {}
    /*!
        \internal

        Dieser Standardkonstruktor wird benötigt damit Row ein QMetaType sein
        kann.
      */
    Row(const Row &other) : AttributeOwner(other.parent()), m_id(0) {}

    /*!
      Gibt die ID der Reihe zurück.
      */
    const int& id() const;

    /*!
      Setzt die ID dieser Reihe auf \a id.

      \warning Darf nur von Table<RowType>::insertRow() aufgerufen werden!
      */
    void setId(int id);

    /*!
        Liest den Wert \p key  dieser Reihe aus der Datenbank aus und gibt ihn
        zurück.

        Sollte eigentlich nur von DatabaseAttribute<T,R,C>::calculate()
        verwendet werden.
      */
    QVariant get(const QString &key) const;

    /*!
        Setzt den Wert \p key  dieser Reihe auf \p value.

        Sollte eigentlich nur von DatabaseAttribute<T,R,C>::setValue()
        verwendet werden.
      */
    bool set(const QString &key, const QVariant &value);

    QList<AttributeBase*> attributes() const;

    /*!
        Gibt alle Datenbankattribute dieser Row zurück.
      */
    QList<AttributeBase*> databaseAttributes() const;

    AttributeBase *attribute(const QString &name) const;

    /*!
        Gibt dem MIME-Type dieser Reihe zurück.

        Dieser sollte die Form \p application/projectstats.rowname haben.

        Wird benötigt um drag and drop uz ermöglichen.
      */
    virtual QString mimeType() const = 0;

    /*!
        Gibt eine Liste aller Kinder dieser Reihe zurück.

        Dies können zum Beispiel die Runden eines Spiels sein.
      */
    QList<Row*> childRows() const;

    /*!
        Gibt das Gui::Details::DetailsWidget dieser Reihe zurück.

        Das DetailsWidget ist der linke Teil des RowWidget, wird aber auch an
        anderen Stellen verwendet (z.B. LeagueView)
      */
    virtual Gui::Details::DetailsWidget* detailsWidget();

    /*!
        Gibt die Tabelle zurück, in der diese Reihe liegt.
      */
    TableBase *table() const;

    /*!
        Gibt das Gui::Details::RowWidget dieser Reihe zurück.

        Das RowWidget wird zum Beispiel im im Hauptfenster angezeigt, wenn die
        Reihe angeklickt wurde und kein SummaryWidget zur Verfüngung steht.

        Es besteht standardmäßig aus links dem DetailsWidget und rechts dem
        StatsWidget.
      */
    virtual Gui::Details::RowWidget* rowWidget();

    /*!
        Gibt das Gui::Details::RowWindow dieser Reihe zurück.

        Das RowWindow wird angezeigt, wenn die Reihe doppelt geklickt wurde.

        Es ist standardmäßig ein einfaches Fenster, welches das RowWidget
        enthält.
      */
    virtual Gui::Details::RowWindow* rowWindow();

    /*!
        Gibt das Gui::Details::StatsWidget dieser Reihe zurück.

        Es wird recht im RowWidget angezeigt.
      */
    virtual Gui::Details::StatsWidget* statsWidget();

    /*!
        Gibt Gui::Details::SummaryWidget dieser Reihe zurück.

        Es wird zum Beispiel im im Hauptfenster angezeigt, wenn die
        Reihe angeklickt wurde.
      */
    virtual Gui::Details::SummaryWidget* summaryWidget();

signals:
    /*!
        Wird gesendet, wenn sich die ID der Reihe ändert.

        Dies geschieht nur dann, wenn die Reihe in die Datenbank eingefügt, oder
        daraus gelöscht wurde.
      */
    void idChanged(int newId);

protected:
    /*!
        \internal

        Erstellt ein Row Objekt, welches in der Tabelle \p table die Daten mit
        der ID  \p id repräsentiert.
      */
    explicit Row(int id, TableBase *table);

    /*!
        \internal

        Setzt den Wert \p key  dieser Reihe auf \p value für die Reihe, für die
        die SQL-Conditon \p condition gilt.

        Diese Methode wird nur von
        set(const QString &key, const QVariant &value) verwendet.
      */
    bool set(const QString &key, const QVariant &value, const QString &condition);

    /*!
        \internal

        Liest den Wert \p key  der Reihe, für die die SQL-Conditon \p condition
        gilt, aus der Datenbank aus.

        Diese Methode wird nur von get(const QString &key) verwendet.
      */
    QVariant get(const QString &key, const QString &condition) const;

    /*!
        Führt den gegebenen Query \p queryString in der Datenbank aus.

        In dem QSqlQuery Objekt wurde schon exec() ausgeführt und sollte auf
        jeden fall mit finish() beendet werden.

        \see Table::query(const QString &queryString)
      */
    QSqlQuery query(const QString &queryString) const;

    /*!
        Fügt das gegebene Attribut zu den Attributen der Row hinzu.

        Ist es ein Datenbankattribute wird es außerdem zusätzlich zu den
        Datenbankattributen hinzugefügt.

        Es sollte nie nötig sein, diese Methode "per Hand" aufzurufen. Das
        übernehmen die Macros in attribute.h.
      */
    void registerAttribute(AttributeBase *attribute);

    /*!
        Fügt dieser Reihe das Kind \a row hinzu.

        Dieses Kind wird dann beim einfügen in die oder löschen aus der
        Datenbank mit hinzugefügt bzw. gelöscht.

        Runden sind Beispiele für Kinder von Spielen.
      */
    void addChildRow(Row *row);

    /*!
        Fügt alle Reihen in \a rows als Kind hinzu.

        \see addChildRow()
      */
    void addChildRows(QList<Row *> rows);

    int m_id; //!< Die ID dieser Row
    QPointer<TableBase> m_table; //!< Die Tabelle, in die diese Row liegt
    QHash<QString, AttributeBase* > m_attributes; //!< Alle Attribute der Row. Muss von Kindklassen befüllt werden.
    QList<AttributeBase*> m_databaseAttributes; //!< Alle Datenbankattribute
    QList<Row*> m_childRows; //!< Alle Rows, die logisch zu dieser Row gehören (z.B. Round gehört zu Game)

    friend class TableBase;
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
    Q_DECLARE_METATYPE(QMap<Database::RowClassname* COMMA int>) \
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
