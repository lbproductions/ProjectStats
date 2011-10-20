#include "graph.h"

#include "graphpoint.h"
#include "coordinatesystem.h"
#include "../graphview.h"

#include <QPainter>

using namespace Gui::Graphs::Items;

Graph::Graph(CoordinateSystem *coordinateSystem) :
    AbstractItem(coordinateSystem),
    m_coordinateSystem(coordinateSystem),
    m_xMax(0),
    m_yMax(0),
    m_xMin(0),
    m_yMin(0)
{
}

bool xCoordinateLessThan(GraphPoint *p1, GraphPoint *p2)
{
    return p1->point().x() < p2->point().x();
}

void Graph::addPoint(const QPoint &point)
{
    GraphPoint *graphPoint = new GraphPoint(point,this);
    m_points.append(graphPoint);
    m_qpoints.append(point);

    qSort(m_points.begin(),m_points.end(),xCoordinateLessThan);

    updateDimensions(point);
    emit pointAdded(point);
}

QRectF Graph::boundingRect() const
{
    return QRectF( QPointF( m_xMin * m_coordinateSystem->xScale(), -m_yMax * m_coordinateSystem->yScale() ),
		    QPointF(  m_xMax * m_coordinateSystem->xScale(), -m_yMin * m_coordinateSystem->yScale()));
}

void Graph::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    GraphPoint *p1 = 0;
    foreach(GraphPoint *p2, m_points)
    {
	if(p1 != 0 && p2 != 0)
	{
            drawJunction(p1,p2,painter);
	}
	p1 = p2;
    }
}

void Graph::drawJunction(GraphPoint* p1, GraphPoint* p2, QPainter *painter)
{
    foreach(Graph* g, m_coordinateSystem->graphs())
    {
        if(g != this && g->m_qpoints.contains(p1->point()) && g->m_qpoints.contains(p2->point()))
        {
            GraphPoint* otherPoint = g->point(p1->point());
            if(p1->junctionIsDashed())
            {
                m_pen.setStyle(Qt::DotLine);
            }
            else
            {
                otherPoint->setJunctionIsDashed(true);
            }
            break;
        }
    }

    m_pen.setJoinStyle(Qt::RoundJoin);
    painter->setPen(m_pen);
    QPen pen = painter->pen();
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawLine(p1->point().x() * m_coordinateSystem->xScale(),-p1->point().y() * m_coordinateSystem->yScale(),
                       p2->point().x() * m_coordinateSystem->xScale(),-p2->point().y() * m_coordinateSystem->yScale());

    m_pen.setStyle(Qt::SolidLine);
}

CoordinateSystem *Graph::coordinateSystem() const
{
    return m_coordinateSystem;
}

void Graph::updateDimensions(const QPoint &point)
{
    prepareGeometryChange();

    m_xMax = qMax(m_xMax,point.x());
    m_xMin = qMin(m_xMin,point.x());
    m_yMax = qMax(m_yMax,point.y());
    m_yMin = qMin(m_yMin,point.y());
}

int Graph::xMax() const
{
    return m_xMax;
}

int Graph::yMax() const
{
    return m_yMax;
}

int Graph::xMin() const
{
    return m_xMin;
}

int Graph::yMin() const
{
    return m_yMin;
}

QList<QPointer<GraphPoint> > Graph::points() const
{
    return m_points;
}

GraphPoint* Graph::point(QPoint p)
{
    foreach(GraphPoint* point, m_points)
    {
        if(point->point() == p)
        {
            return point;
        }
    }
    return 0;
}
