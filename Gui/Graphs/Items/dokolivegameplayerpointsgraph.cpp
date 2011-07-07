#include "dokolivegameplayerpointsgraph.h"

#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/Doppelkopf/dokoround.h>
#include <Database/Doppelkopf/schmeisserei.h>
#include <Database/player.h>

#include <Gui/Graphs/Items/livegamecoordinatesystem.h>
#include <Gui/Graphs/Items/dokographpoint.h>

#include <QDebug>

using namespace Gui::Graphs::Items;

DokoLiveGamePlayerPointsGraph::DokoLiveGamePlayerPointsGraph(Database::Player *player, Database::DokoLiveGame *liveGame, LiveGameCoordinateSystem *coordinateSystem):
    LiveGamePlayerPointsGraph(player,liveGame,coordinateSystem)
{
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
        addPoint(QPoint(r->number->value()+1,m_totalPoints),dokoround);
        QString tooltip = "<h1>"+m_player->name->value()+"</h1>"+
                "<span style=\"font-size: 18pt;\">"+tr("Round")+" "+QString::number(r->number->value()+1)+"<br></span>"
                "<span style=\"font-size: 22pt;\">"
                "<b>"+tr("Points")+":</b> "+QString::number(r->points->value(m_player))+"<br>"+
                "<b>"+tr("Total")+":</b> "+QString::number(m_totalPoints)+"<br>"+
                "<br>";
        if (dokoround->doko_hochzeitPlayerId->value() == m_player->id()){
            tooltip += "Hochzeit<br>";
        }
        if (dokoround->doko_soloPlayerId->value() == m_player->id()){
            tooltip += dokoround->doko_soloType->value()+"-Solo<br>";
        }
        if (dokoround->doko_trumpfabgabePlayerId->value() == m_player->id()){
            tooltip+= "Trumpfabgabe<br>";
        }
        if (dokoround->doko_schweinereiPlayerId->value() == m_player->id()){
            tooltip+= "Schweinerei<br>";
        }

        bool hasSchmeisserei = false;
        foreach(Database::Schmeisserei* s, dokoround->doko_schmeissereien->value())
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
        m_points.last()->setToolTip(tooltip);
    }
}
