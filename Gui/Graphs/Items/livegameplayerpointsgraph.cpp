#include "livegameplayerpointsgraph.h"

#include "livegamecoordinatesystem.h"
#include "graphpoint.h"

#include <Database/player.h>
#include <Database/livegame.h>
#include <Database/round.h>

#include <QDebug>

using namespace Gui::Graphs::Items;

LiveGamePlayerPointsGraph::LiveGamePlayerPointsGraph(Database::Player *player, Database::LiveGame *liveGame, LiveGameCoordinateSystem *coordinateSystem) :
    Graph(coordinateSystem),
    m_player(player),
    m_liveGame(liveGame),
    m_totalPoints(0)
{
}

void LiveGamePlayerPointsGraph::setupGraph(){
    m_pen.setColor(m_player->color->value());
    addPoint(QPoint(0,0));
    readPlayerPoints();

    connect(m_liveGame,SIGNAL(roundFinished(::Database::Round*)),this,SLOT(addRound(::Database::Round*)));
}

void LiveGamePlayerPointsGraph::readPlayerPoints()
{
    foreach(Database::Round *r, m_liveGame->rounds->value())
    {
	addRound(r);
    }
}

void LiveGamePlayerPointsGraph::addRound(::Database::Round *r)
{
    if(r->state->value() == Database::Round::FinishedState)
    {
        m_totalPoints += r->points->value(m_player);
        addPoint(QPoint(r->number->value()+1,m_totalPoints));
        m_points.last()->setToolTip("<h1>"+m_player->name->value()+"</h1>"+
                                     "<span style=\"font-size: 18pt;\">"+tr("Round")+" "+QString::number(r->number->value()+1)+"<br></span>"
				     "<span style=\"font-size: 22pt;\">"
                                     "<b>"+tr("Points")+":</b> "+QString::number(r->points->value(m_player))+"<br>"+
				     "<b>"+tr("Total")+":</b> "+QString::number(m_totalPoints)+
				     "</span>");
    }
}

Database::Player* LiveGamePlayerPointsGraph::player(){
    return m_player;
}
