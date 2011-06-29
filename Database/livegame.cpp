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

    IMPLEMENT_ATTRIBUTE_IN_CALC(int,LiveGame,LiveGameCalculator,calc,percComplete,tr("%Complete"))
    rounds->addDependingAttribute(percComplete);

    IMPLEMENT_ATTRIBUTE_IN_CALC(Round*,LiveGame,LiveGameCalculator,calc,lastRound,tr("LastRound"))
    rounds->addDependingAttribute(lastRound);

    IMPLEMENT_ATTRIBUTE_IN_CALC(Round*,LiveGame,LiveGameCalculator,calc,currentRound,tr("CurrentRound"))
    rounds->addDependingAttribute(currentRound);
    currentRound->addDependingAttribute(state);

    IMPLEMENT_LISTATTRIBUTE_IN_CALC(Player*,LiveGame,LiveGameCalculator,calc,currentPlayingPlayers,tr("CurrentPlayingPlayers"))
    currentRound->addDependingAttribute(currentPlayingPlayers);

    IMPLEMENT_ATTRIBUTE_IN_CALC(Player*,LiveGame,LiveGameCalculator,calc,cardmixer,tr("Cardmixer"))
    currentRound->addDependingAttribute(cardmixer);

    IMPLEMENT_VIRTUAL_ATTRIBUTE_IN_CALC(int,LiveGame,LiveGameCalculator,totalPoints,tr("TotalPoints"))
    rounds->addDependingAttribute(totalPoints);
}

QString LiveGame::mimeType() const
{
    return "application/projectstats.liveGame";
}

END_ROW_IMPLEMENTATION()
