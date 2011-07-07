#include "dokographpoint.h"

#include "dokolivegameplayerpointsgraph.h"
#include "dokolivegamecoordinatesystem.h"

#include <Database/Doppelkopf/dokoround.h>
#include <Database/player.h>

#include <QPainter>

using namespace Gui::Graphs::Items;

DokoGraphPoint::DokoGraphPoint(QPoint point, DokoLiveGamePlayerPointsGraph* graph, ::Database::DokoRound* r):
    GraphPoint(point,graph)
{
    m_radius = 7;
    m_dokoround = r;
    m_player = graph->player();
}

void DokoGraphPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    painter->setPen(m_player->color->value());
    painter->setBrush(Qt::black);
    painter->drawEllipse(QPointF(  m_point.x()*m_graph->coordinateSystem()->xScale(),
                                    -m_point.y()*m_graph->coordinateSystem()->yScale()),
                                    m_radius,
                                    m_radius);
    painter->setPen(QColor("white"));
    QFont font = painter->font();
    font.setPointSize(10);
    painter->setFont(font);

    QString text;
    if (m_dokoround->doko_soloPlayerId->value() == m_player->id()){
        text = "S";
    }
    else if(m_dokoround->doko_hochzeitPlayerId->value() == m_player->id()){
        text = "H";
    }
    else if(m_dokoround->doko_trumpfabgabePlayerId->value() == m_player->id()){
        text = "T";
    }
    else if(m_dokoround->doko_re1PlayerId->value() == m_player->id() || m_dokoround->doko_re2PlayerId->value() == m_player->id()){
        text = "R";
    }
    else if (m_dokoround->currentPlayingPlayers->value().contains(m_player)){
        text = "C";
    }
    else{
        text = "-";
    }

    painter->drawText(QPointF(  (m_point.x()*m_graph->coordinateSystem()->xScale())-2,
                              (-m_point.y()*m_graph->coordinateSystem()->yScale())+2),text);
}
