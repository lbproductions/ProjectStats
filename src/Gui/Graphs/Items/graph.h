#ifndef GRAPH_H
#define GRAPH_H

#include "abstractitem.h"

#include <QPointer>

namespace Gui
{

namespace Graphs
{

class GraphView;

namespace Items
{

class CoordinateSystem;
class GraphPoint;
class Junction;

//! Oberklasse für alle Graphen.
/*!
  Jeder Graph besteht aus Punkten (GraphPoint). Diese werden intern erstellt (via addPoint()) und sortiert verwaltet.<br>
  Der Graph weiß immer von seinen maximalen und minimalen x und y Werten und teilt Änderungen durch das Signal pointAdded() mit.<br>
  Die Punkte zeichnen sich in GraphPoint selber, ihre Verbindungen werden vom Graph in drawJunction() gezeichnet.
  */
class Graph : public AbstractItem
{
    Q_OBJECT
public:
    /*!
      Erstellt einen Graphen im gegebenen Koordinatensystem \p coordinateSystem
      */
    Graph(CoordinateSystem *coordinateSystem);

    /*!
      Fügt einen Punkt \\ppoint zum Graphen hinzu.
      */
    virtual void addPoint(const QPoint &point);

    /*!
      \return Der Maximale X-Wert aller Graphen dieses Koordinatensystems.
      */
    int xMax() const;

    /*!
      \return Der Maximale Y-Wert aller Graphen dieses Koordinatensystems.
      */
    int yMax() const;

    /*!
      \return Der Minimale X-Wert aller Graphen dieses Koordinatensystems.
      */
    int xMin() const;

    /*!
      \return Der Minimale Y-Wert aller Graphen dieses Koordinatensystems.
      */
    int yMin() const;

    /*!
      \return Das Koordinatensystem, in dem dieser Graph liegt.
      */
    CoordinateSystem *coordinateSystem() const;

    /*!
      \return Das Rechteck, dass alle Punkte enthält.
      */
    QRectF boundingRect() const;

    /*!
      Zeichnet die Verbindungen zwischen alle Punkten des Graphen.
      \see drawJunction()
      */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QList<QPointer<GraphPoint> > points() const;

    QMap<QPair<int,int>, QPair<int,int> > drawnLines() const;


signals:
    /*!
      Dieses Signal wird gesendet, wenn ein Punkt zu diesem Graphen hinzugefügt wurde.
      */
    void pointAdded(const QPoint&);

public slots:
    /*!
      Dieser Slot wird aufgerufen, sobald ein Punkt zum Graphen hinzugefügt wurde. Hier werden die minmalen und maximalen x und y Werte angepasst.
      */
    void updateDimensions(const QPoint &point);

protected:
    /*!
      Zeichnet im QPainter \p painter eine Verbindung zwischen den Punkten \p p1 und \p p2.
      */
    virtual void drawJunction(const QPoint &p1, const QPoint &p2, QPainter *painter);

    QList<QPointer<GraphPoint> > m_points; //!< Die Punkte in diesem Graphen
    QPointer<CoordinateSystem> m_coordinateSystem; //!< Das Koordinatensystem, in dem dieser Graph liegt.
    int m_xMax; //!< Der Maximale X-Wert aller Graphen dieses Koordinatensystems.
    int m_yMax; //!< Der Maximale Y-Wert aller Graphen dieses Koordinatensystems.
    int m_xMin; //!< Der Minimale X-Wert aller Graphen dieses Koordinatensystems.
    int m_yMin; //!< Der Minimale Y-Wert aller Graphen dieses Koordinatensystems.


};

}
}
}
#endif // GRAPH_H
