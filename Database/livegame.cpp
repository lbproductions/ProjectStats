#include "livegame.h"

#include <Database/drink.h>
#include <Database/livegamedrink.h>
#include <Database/round.h>
#include <Database/point.h>

#include <QTime>


START_ROW_IMPLEMENTATION(LiveGame, Game, Game)
{
    LiveGameCalculator* calc = new LiveGameCalculator(this,this);

    IMPLEMENT_LISTATTRIBUTE_IN_CALC(Drink*,LiveGame,LiveGameCalculator,calc,drinks,tr("Drinks"))
    LiveGameDrinks::instance()->rows()->addDependingAttribute(drinks);

    IMPLEMENT_LISTATTRIBUTE_IN_CALC(Round*,LiveGame,LiveGameCalculator,calc,rounds,tr("Rounds"))
    Rounds::instance()->rows()->addDependingAttribute(rounds);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,LiveGame,LiveGameCalculator,calc,points,tr("Points"))
    Points::instance()->rows()->addDependingAttribute(points);

    IMPLEMENT_ATTRIBUTE_IN_CALC(QTime,LiveGame,LiveGameCalculator,calc,length,tr("Length"))
    rounds->addDependingAttribute(length);
}

QString LiveGame::mimeType() const
{
    return "application/projectstats.liveGame";
}

END_ROW_IMPLEMENTATION()
