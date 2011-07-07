#include "livegamecoordinatesystem.h"

#include "livegameplayerpointsgraph.h"
#include "dokolivegameplayerpointsgraph.h"

#include <Database/livegame.h>
#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/player.h>

#include <QDebug>
#include <QPainter>

using namespace Gui::Graphs::Items;

LiveGameCoordinateSystem::LiveGameCoordinateSystem(Database::LiveGame *liveGame) :
    CoordinateSystem(),
    m_liveGame(liveGame)
{
}

 void LiveGameCoordinateSystem::setupSystem(){
     m_xMax = 20;
     m_pen.setWidth(3);
     addGraphsForPlayers();
 }

void LiveGameCoordinateSystem::addGraphsForPlayers()
{
    foreach(Database::Player *player, m_liveGame->playersSortedByPosition->value())
    {
        LiveGamePlayerPointsGraph* graph = new LiveGamePlayerPointsGraph(player,m_liveGame,this);
        graph->setupGraph();
        addGraph(graph);
    }
}

void LiveGameCoordinateSystem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    CoordinateSystem::paint(painter,option,widget);

    QPen pen;
    pen.setWidth(3);
    pen.setColor(QColor(255,255,255));
    painter->setPen(pen);
    //Zeichnet die x-Achse
    painter->drawLine(m_xMin * m_xScale,0,
		       (m_xMax+1) * m_xScale,0);

    //Zeichne die einen grauen Strich, wenn alle Spieler einmal gegeben haben.
    int playerCount = m_liveGame->playersSortedByPosition->value().size();
    for(float i = playerCount; i < m_liveGame->rounds->value().size(); i+=playerCount)
    {
	QPen pen;
	pen.setColor(QColor(204,204,204));
	pen.setWidth(0);
	painter->setPen(pen);
	painter->drawLine((i+0.5) * m_xScale,-(m_yMax+2) * m_yScale,
			   (i+0.5) * m_xScale,-(m_yMin-2) * m_yScale);
    }

    //Zeichne graue Striche alle 10 Punkte
    int i = m_yMin;
    i/=10;
    i*=10;
    for(; i < m_yMax; i+=10)
    {
	if(i % 50 == 0)
	{
	    QPen pen;
	    pen.setWidth(2);
	    pen.setColor(QColor(240,240,240));
	    painter->setPen(pen);
	}
	else
	{
	    QPen pen;
	    pen.setColor(QColor(229,229,229));
	    pen.setWidth(0);
	    painter->setPen(pen);
	}
	painter->drawLine(m_xMin * m_xScale, -i * m_yScale,
			   (m_xMax+1) * m_xScale,-i * m_yScale);
    }
}
