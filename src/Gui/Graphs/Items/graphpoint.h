#ifndef GRAPHPOINT_H
#define GRAPHPOINT_H

#include "abstractitem.h"

#include <QPointer>

namespace Gui
{

namespace Graphs
{

namespace Items
{

class Graph;

//! Oberklasse für alle möglichen Arten von Punkten.
/*!
  Aus Punkten bestehen Graphen. Dabei ist GraphPoint nur zum Zeichnen eines Punktes an der korrekten Stelle im Koordinatensystem zuständig.<br>
  Einfache Änderungen wie das Anpassen der Farbe, Anzeigen von Tooltips, oder Radius können stattfinden, indem Zugriffsmethoden zu dieser Klasse hinzugefügt werden.<br>
  Will man ganz andere Dinge darstellen (z.B. Bilder als Punkt), muss diese Klasse spezialisiert werden.
  */
class GraphPoint : public AbstractItem
{
    Q_OBJECT
public:
    /*!
      Erstellt einen Punkt an \p point im Graphen \p graph.
      */
    GraphPoint(QPoint point, Graph *graph);

    /*!
      Gibt den Punkt zurück an dem dieser Punkt liegt.
      */
    QPoint point() const;

    void setPoint(const QPoint& point);

    /*!
      \return Das Rechteck, in dem die Darstellung dieses Punktes liegt.
      */
    QRectF boundingRect() const;

    /*!
      Zeichnet den Punkt.
      */
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool junctionIsDashed() const;

    void setJunctionIsDashed(bool dashed);

protected:
    QPointer<Graph> m_graph; //!< Der Graph, zu dem dieser Punkt gehört.
    QPoint m_point; //!< Der eigentliche Punkt, der dieser GraphPoint repräsentiert.
    int m_radius; //! Der Radius des Kreises, mit dem dieser Punkt dargestellt wird.
    bool m_junctionIsDashed;
};
}
}
}
#endif // GRAPHPOINT_H
