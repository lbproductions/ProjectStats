#include "dokolivegameplayerpointsgraph.h"

#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/Doppelkopf/dokoround.h>
#include <Database/Doppelkopf/schmeisserei.h>
#include <Database/player.h>
#include <Database/point.h>

#include <Gui/Graphs/Items/livegamecoordinatesystem.h>
#include <Gui/Graphs/Items/dokographpoint.h>

#include <QDebug>
#include <QGraphicsScene>

using namespace Gui::Graphs::Items;

DokoLiveGamePlayerPointsGraph::DokoLiveGamePlayerPointsGraph(Database::Player *player, Database::DokoLiveGame *liveGame, LiveGameCoordinateSystem *coordinateSystem):
    LiveGamePlayerPointsGraph(player,liveGame,coordinateSystem)
{
}

void DokoLiveGamePlayerPointsGraph::update()
{
    m_totalPoints = 0;
    int i = 0;

    m_coordinateSystem->resetDimensions();

    foreach(GraphPoint* gpoint, m_points)
    {
        if(i == 0)
        {
            i=1;
            continue;
        }
        DokoGraphPoint* point = static_cast<DokoGraphPoint*>(gpoint);
        Database::DokoRound* round = point->round();
        if(round)
        {
            m_totalPoints += round->points->value(m_player);
            QPoint p = point->point();
            p.setY(m_totalPoints);
            point->setPoint(p);
            updateDimensions(p);
            emit pointAdded(p);
        }
    }

    this->scene()->invalidate();
}

bool xCoordinateLessThan1(GraphPoint *p1, GraphPoint *p2)
{
    return p1->point().x() < p2->point().x();
}

void DokoLiveGamePlayerPointsGraph::addPoint(const QPoint &point, ::Database::DokoRound* r)
{
    DokoGraphPoint *graphPoint = new DokoGraphPoint(point,this,r);
    m_points.append(graphPoint);

    qSort(m_points.begin(),m_points.end(),xCoordinateLessThan1);

    updateDimensions(point);
    emit pointAdded(point);
}

void DokoLiveGamePlayerPointsGraph::addRound(::Database::Round *r){
    if(r->state->value() == Database::Round::FinishedState)
    {
        Database::DokoRound* dokoround = static_cast<Database::DokoRound*>(r);
        m_totalPoints += r->points->value(m_player);
        Database::Point* point = r->pointObjects->value(m_player);
        if(point)
        {
            connect(point->points,SIGNAL(changed()),this,SLOT(update()));
        }
        addPoint(QPoint(r->number->value()+1,m_totalPoints),dokoround);
    }
}
