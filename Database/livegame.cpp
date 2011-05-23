#include "livegame.h"

#include <Database/drink.h>
#include <Database/livegamedrink.h>
#include <Database/round.h>
#include <Database/point.h>

#include <QTime>


START_ROW_IMPLEMENTATION(LiveGame, Game, Game)
{
    LiveGameCalculator* calc = new LiveGameCalculator(this,this);
    m_calc = calc;

    IMPLEMENT_LISTATTRIBUTE_IN_CALC(Drink*,LiveGame,LiveGameCalculator,calc,drinks,tr("Drinks"))
    LiveGameDrinks::instance()->rows()->addDependingAttribute(drinks);

    IMPLEMENT_LISTATTRIBUTE_IN_CALC(Round*,LiveGame,LiveGameCalculator,calc,rounds,tr("Rounds"))
    Rounds::instance()->rows()->addDependingAttribute(rounds);

    rounds->addDependingAttribute(length);

    IMPLEMENT_ATTRIBUTE_IN_CALC(int,LiveGame,LiveGameCalculator,calc,percComplete,tr("CompleteState"))
    rounds->addDependingAttribute(percComplete);
}

QString LiveGame::mimeType() const
{
    return "application/projectstats.liveGame";
}

END_ROW_IMPLEMENTATION()
