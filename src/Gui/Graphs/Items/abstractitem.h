#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H

#include <QGraphicsObject>
#include <QPen>

namespace Gui
{

namespace Graphs
{

class GraphView;

namespace Items
{

//! Bildet die Oberklasse für alle QGraphicItems, die wir in unseren Views darstellen wollen.
/*!
  Dabei verwaltet dieses Abstrakte Objekt bisher nur einen QPen, der mit dem Pen des Vaterobjektes initialisiert wird.
  */
class AbstractItem : public QGraphicsObject
{
    Q_OBJECT
public:
    /*!
      Erstellt ein AbstractItem, welches den QPen seines Vater übernimmt.
      */
    explicit AbstractItem(AbstractItem *parent = 0);

    /*!
      Diese Aufzählung wird verwendet um all' unseren AbstractItems einen eigenen Typen zu geben.
      \see type()
      */
    enum {
	Type = UserType + 1
    };

    /*!
      Diese Funktion wird von Qt verwendet, um QGraphicsItems zu unterscheiden und mit qgraphicsitem_cast() einen Cast zwischen den Typen möglich zu machen.
      \return Type = UserType + 1
      */
    int type() const;

    /*!
      Gibt den QPen dieses Items zurück. Wird verwendet um an den Pen des Vaters zu kommen.
      */
    QPen pen() const;

protected:
    QPen m_pen; //!< Der Stift, mit dem dieses Objekt sich zeichnen soll.
};

}
}
}
#endif // ABSTRACTITEM_H
