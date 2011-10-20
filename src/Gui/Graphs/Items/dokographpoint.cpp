#include "dokographpoint.h"

#include "dokolivegameplayerpointsgraph.h"
#include "dokolivegamecoordinatesystem.h"

#include <Database/Doppelkopf/dokoround.h>
#include <Database/player.h>
#include <Database/Doppelkopf/schmeisserei.h>

#include <QPainter>

using namespace Gui::Graphs::Items;

DokoGraphPoint::DokoGraphPoint(QPoint point, DokoLiveGamePlayerPointsGraph* graph, ::Database::DokoRound* r):
    GraphPoint(point,graph)
{
    m_radius = 7;
    m_dokoround = r;
    m_player = graph->player();

    QString tooltip = "<h1>"+m_player->name->value()+"</h1>"+
            "<span style=\"font-size: 18pt;\">"+tr("Round")+" "+QString::number(r->number->value()+1)+"<br></span>"
            "<span style=\"font-size: 22pt;\">"
            "<b>"+tr("Points")+":</b> "+QString::number(r->points->value(m_player))+"<br>"+
            "<b>"+tr("Total")+":</b> "+QString::number(point.y())+"<br>"+
            "<br>";
    if (m_dokoround->doko_hochzeitPlayerId->value() == m_player->id()){
        tooltip += "Hochzeit<br>";
    }
    if (m_dokoround->doko_soloPlayerId->value() == m_player->id()){
        tooltip += m_dokoround->doko_soloType->value()+"-Solo<br>";
    }
    if (m_dokoround->doko_trumpfabgabePlayerId->value() == m_player->id()){
        tooltip+= "Trumpfabgabe<br>";
    }
    if (m_dokoround->doko_schweinereiPlayerId->value() == m_player->id()){
        tooltip+= "Schweinerei<br>";
    }

    bool hasSchmeisserei = false;
    foreach(Database::Schmeisserei* s, m_dokoround->doko_schmeissereien->value())
    {
        if(s->playerId->value() == m_player->id())
        {
            hasSchmeisserei = true;
        }
    }

    if (hasSchmeisserei){
        tooltip+= "Schmeisserei<br>";
    }
    tooltip+="</span>";
    setToolTip(tooltip);
}

Database::DokoRound* DokoGraphPoint::round() const
{
    return m_dokoround;
}

void DokoGraphPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/)
{
    int deltaRadius = 0;

    foreach(Graph* g, m_graph->coordinateSystem()->graphs())
    {
        if(g != m_graph && g->qpoints().contains(m_point))
        {
            if(m_junctionIsDashed)
            {
                deltaRadius = -1;
            }
            break;
        }
    }

    painter->setPen(m_player->color->value());
    painter->setBrush(Qt::black);
    painter->drawEllipse(QPointF(  m_point.x()*m_graph->coordinateSystem()->xScale(),
                                    -m_point.y()*m_graph->coordinateSystem()->yScale()),
                                    m_radius+deltaRadius,
                                    m_radius+deltaRadius);
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
    else if(m_dokoround->doko_re->value(m_player)){
        text = "R";
    }
    else if (m_dokoround->currentPlayingPlayers->value().contains(m_player)){
        text = "C";
    }
    else{
        text = "-";
    }

    painter->drawText(QPointF(  (m_point.x()*m_graph->coordinateSystem()->xScale())-3,
                              (-m_point.y()*m_graph->coordinateSystem()->yScale())+3),text);
}
