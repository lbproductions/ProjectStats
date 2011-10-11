#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include "abstractitem.h"

#include <QPointer>

namespace Gui
{

namespace Graphs
{

namespace Items
{

class Graph;

//! Oberklasse für alle Koordinatensysteme.
/*!
  Ein Koordinatensystem verwaltet bei uns seine enthaltenen Graphen und ist auch gleichzeitig Parent-QGraphicsItem für diese.<br>
  Außerdem achtet jedes Koordinatensystem auf Werteänderungen seiner Graphen und weiß immer von den maximalen und minimalen x und y Werten seiner Graphen.<br>
  In Verbindung mit dem Wissen über die Größe des anzeigenden Views kann ein Koordinatensystem seine Skalierung immer automatisch anpassen und so in den View passen (updateScales()).<br>
  Aktuell zeichnet dieses Ober-Koordinatensystem überhaupt nichts. Das Aussehen des Systems kann so komplett in spezialisierenden Klassen durch Implementierung von paint() angepasst werden.
  */
class CoordinateSystem : public AbstractItem
{
    Q_OBJECT
public:
    /*!
      Erstellt ein leeres Koordinatensystem.
      */
    CoordinateSystem();

    /*!
      Fügt den Graphen \\pgraph zum System hinzu. Veränderungen am System werden anschließend von diesem System verwaltet.
      */
    void addGraph(Items::Graph* graph);

    /*!
      Passt die Skalierung dieses Koordinatensystems so an, dass höchstens \\pheight Pixel hoch und \\pwidth Pixel breit ist.
      */
    void updateScales(int height, int width);

    /*!
      \return Die Skalierung in x Richtung.
      */
    qreal xScale() const;

    /*!
      \return Die Skalierung in y Richtung.
      */
    qreal yScale() const;

    /*!
      \return Der Maximale X-Wert aller Graphen dieses Koordinatensystems.
      */
    int xMax() const;

    /*!
      \return Der Minimale X-Wert aller Graphen dieses Koordinatensystems.
      */
    int xMin() const;

    /*!
      \return Der Maximale Y-Wert aller Graphen dieses Koordinatensystems.
      */
    int yMax() const;

    /*!
      \return Der Minimale Y-Wert aller Graphen dieses Koordinatensystems.
      */
    int yMin() const;

    /*!
      \return Das Rechteck enthält das komplette Koordinatensystem sowie alle zugehörigen Graphen.
      */
    QRectF boundingRect() const;

    /*!
      Zeichnet gar nichts. Dadurch ist das Aussehen des Koordinatensystems in allen spezialisierenden Klassen anpassbar.
      */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void updateDimensions();

signals:
    /*!
      Dieses Signal wird gesendet, wenn ein neuer Punkt zu einem enthaltenen Graphen hinzugefügt wurde.
      \param rect boundingRect()
      */
    void dimensionsChanged(QRectF rect);

private slots:
    /*!
      Dieser Slot wird aufgerufen, wenn ein neuer Punkt zu einem enthaltenen Graphen hinzugefügt wurde.
      Hier werden die maximalen und minimalen x und y Werte an den neuen Punkt angepasst.
      */
    void updateDimensions(const QPoint &point);

protected:
    QList<QPointer<Items::Graph> > m_graphs; //!< Alle enthaltenen Graphen.
    qreal m_xScale; //!< Die Skalierung in x Richtung.
    qreal m_yScale; //!< Die Skalierung in y Richtung.
    int m_xMax; //!< Der Maximale X-Wert aller Graphen dieses Koordinatensystems.
    int m_yMax; //!< Der Maximale Y-Wert aller Graphen dieses Koordinatensystems.
    int m_xMin; //!< Der Minimale X-Wert aller Graphen dieses Koordinatensystems.
    int m_yMin; //!< Der Minimale Y-Wert aller Graphen dieses Koordinatensystems.
};
}
}
}
#endif // COORDINATESYSTEM_H
