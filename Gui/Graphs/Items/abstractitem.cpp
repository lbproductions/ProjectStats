#include "abstractitem.h"

#include "../graphview.h"

using namespace Gui::Graphs::Items;

AbstractItem::AbstractItem(AbstractItem *parent) :
    QGraphicsObject(parent),
    m_pen(QPen())
{
    if(parent != 0)
    {
	m_pen = parent->pen();
    }
}

int AbstractItem::type() const
{
    return Type;
}

QPen AbstractItem::pen() const
{
    return m_pen;
}
