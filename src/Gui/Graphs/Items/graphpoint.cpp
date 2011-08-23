#include "graphpoint.h"

#include "coordinatesystem.h"
#include "graph.h"
#include "../graphview.h"

#include <QStaticText>

using namespace Gui::Graphs::Items;

GraphPoint::GraphPoint(QPoint point, Graph* graph) :
    AbstractItem(graph),
    m_graph(graph),
    m_point(point),
    m_radius(3)
{
    m_pen = QPen();
    m_pen.setBrush(QBrush(m_pen.color()));
}

QPoint GraphPoint::point() const
{
    return m_point;
}

QRectF GraphPoint::boundingRect() const
{
    return QRectF(  m_point.x() * m_graph->coordinateSystem()->xScale() - m_radius,
		    -m_point.y() * m_graph->coordinateSystem()->yScale() - m_radius,
		    m_radius*2,
		    m_radius*2);
}

void GraphPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    painter->setPen(m_pen);
    painter->drawEllipse(QPointF(  m_point.x()*m_graph->coordinateSystem()->xScale(),
				    -m_point.y()*m_graph->coordinateSystem()->yScale()),
				    m_radius,
                                    m_radius);
}
