#include "livegame.h"

#include <Database/drink.h>
#include <Database/livegamedrink.h>
#include <Database/round.h>


START_ROW_IMPLEMENTATION(LiveGame, Game, Game)
{
    LiveGameCalculator* calc = new LiveGameCalculator(this,this);

    IMPLEMENT_ATTRIBUTE_IN_CALC(QList<Drink*>,LiveGame,LiveGameCalculator,calc,drinks,"Drinks")
    LiveGameDrinks::instance()->rows()->addDependingAttribute(drinks);

    IMPLEMENT_ATTRIBUTE_IN_CALC(QList<Round*>,LiveGame,LiveGameCalculator,calc,rounds,"Rounds")
    Rounds::instance()->rows()->addDependingAttribute(rounds);
}

QString LiveGame::mimeType() const
{
    return "application/projectstats.liveGame";
}

END_ROW_IMPLEMENTATION()
