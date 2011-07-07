#include "coordinatesystem.h"

#include "../graphview.h"
#include "graph.h"

using namespace Gui::Graphs::Items;

CoordinateSystem::CoordinateSystem() :
    AbstractItem(),
    m_xScale(20),
    m_yScale(5),
    m_xMax(0),
    m_yMax(0),
    m_xMin(0),
    m_yMin(0)
{
}

void CoordinateSystem::addGraph(Items::Graph *graph)
{
    if(graph != 0)
    {
	graph->setParentItem(this);
	m_graphs.append(graph);
	updateDimensions(QPoint(graph->xMax(),graph->yMax()));
	updateDimensions(QPoint(graph->xMin(),graph->yMin()));

	connect(graph,SIGNAL(pointAdded(QPoint)),this,SLOT(updateDimensions(QPoint)));
    }
}

QRectF CoordinateSystem::boundingRect() const
{
    return QRectF( QPointF( (m_xMin)   * m_xScale, -(m_yMax+2) * m_yScale ),
		    QPointF( (m_xMax+1) * m_xScale, -(m_yMin-2) * m_yScale));
}

void CoordinateSystem::paint(QPainter */*painter*/, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
}

void CoordinateSystem::updateDimensions(const QPoint &point)
{
    m_xMax = qMax(m_xMax,point.x());
    m_xMin = qMin(m_xMin,point.x());
    m_yMax = qMax(m_yMax,point.y());
    m_yMin = qMin(m_yMin,point.y());

    prepareGeometryChange();
    emit dimensionsChanged(boundingRect());
}

void CoordinateSystem::updateScales(int height, int width)
{
    qreal xRange = qAbs(m_xMax) + qAbs(m_xMin) + 2;
    qreal yRange = qAbs(m_yMax) + qAbs(m_yMin) + 4;
    if(xRange > 0)
    {
	m_xScale = ((qreal)width) / xRange;
    }

    if(yRange > 0)
    {
	m_yScale = ((qreal)height) / yRange;
    }
}

qreal CoordinateSystem::xScale() const
{
    return m_xScale;
}

qreal CoordinateSystem::yScale() const
{
    return m_yScale;
}

int CoordinateSystem::xMax() const
{
    return m_xMax;
}

int CoordinateSystem::yMax() const
{
    return m_yMax;
}

int CoordinateSystem::xMin() const
{
    return m_xMin;
}

int CoordinateSystem::yMin() const
{
    return m_yMin;
}
