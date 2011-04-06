#ifndef DATABASE_ROW_H
#define DATABASE_ROW_H

#include <QObject>

#include <QPointer>
#include <QSqlQuery>
#include <QHash>

namespace Database {

class TableInterface;
class AttributeInterface;

//! Repräsentiert eine Row einer Tabelle.
/*!
  Alle Reihen wie z.B. Player oder Game erben von dieser Klasse. Sie bietet ihnen durch set() und get() eine einfache Schnittstelle zu ihren Daten.
  */
class Row : public QObject
{
    Q_OBJECT
public:
    /*!
      \return Die ID der Reihe.
      */
    int id() const;

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

    QList<AttributeInterface*> attributes() const;

    QList<AttributeInterface*> databaseAttributes() const;

    AttributeInterface *attribute(const QString &name) const;

protected:
    /*!
      Erstellt ein Row Objekt, welches in der Tabelle \p table  die Daten mit der ID  \p id repräsentiert.
      */
    explicit Row(int id, TableInterface *table);

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

    void registerAttribute(AttributeInterface &attribute);

    int m_id; //!< Die ID dieser Row
    QPointer<TableInterface> m_table; //!< Die Tabelle, in die diese Row liegt
    QHash<QString, AttributeInterface* > m_attributes; //!< Alle Attribute der Row. Muss von Kindklassen befüllt werden.
    QList<AttributeInterface*> m_databaseAttributes;

private:
    /*!
      Überprueft, ob die eine Row mit dieser ID tatsächlich existiert.
      Ist das nicht der Fall wird ID auf -1 gesetzt und die Row damit invalid.
      Wird vom Konstruktor aufgerufen.
      */
    void checkId();
};

} // namespace Database

#endif // DATABASE_ROW_H
