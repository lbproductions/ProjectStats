#include "junction.h"

#include <QPainter>
#include <QDebug>
#include <QPoint>

#include "coordinatesystem.h"

#include "Database/player.h"

namespace Gui {
namespace Graphs {
namespace Items {

Junction::Junction(QPoint p1, QPoint p2, CoordinateSystem *system):
    m_drawCount(0),
    m_coordinateSystem(system)
{
    m_x1 = p1.x();
    m_x2 = p2.x();
    m_y1 = p1.y();
    m_y2 = p2.y();
}

void Junction::draw(QPainter *painter)
{
    painter->drawLine(this->x1() * m_coordinateSystem->xScale(),-this->y1() * m_coordinateSystem->yScale(),
               this->x2() * m_coordinateSystem->xScale(),-this->y2() * m_coordinateSystem->yScale());
}

void Junction::draw(QPainter *painter, Database::Player* player)
{
    if(!m_players.contains(player)) {
        m_players.append(player);
    }

    QPen originalPen = painter->pen();
    QPen pen = painter->pen();
    pen.setWidth(3);
    if(m_drawCount % m_players.size() != 0) {
        pen.setStyle(Qt::DotLine);
    }
    painter->setPen(pen);
    painter->drawLine(this->x1() * m_coordinateSystem->xScale(),-this->y1() * m_coordinateSystem->yScale(),
               this->x2() * m_coordinateSystem->xScale(),-this->y2() * m_coordinateSystem->yScale());
    painter->setPen(originalPen);

    m_drawCount++;
}

int Junction::x1()
{
    return m_x1;
}

int Junction::x2()
{
    return m_x2;
}

int Junction::y1()
{
    return m_y1;
}

int Junction::y2()
{
    return m_y2;
}

} // namespace Items
} // namespace Graphs
} // namespace Gui
