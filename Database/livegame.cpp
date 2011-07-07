#include "livegame.h"

#include <Database/position.h>
#include <Database/drink.h>
#include <Database/livegamedrink.h>
#include <Database/round.h>
#include <Database/point.h>
#include "round.h"

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

    IMPLEMENT_ATTRIBUTE_IN_CALC(bool,LiveGame,LiveGameCalculator,calc,isFinished,tr("Finished"))
}

LiveGame::LiveGame(QString type) :
    Game(type,true)
{
    initializeAttributes();
    createRound();
}

QString LiveGame::mimeType() const
{
    return "application/projectstats.liveGame";
}

void LiveGame::addPlayer(Player* player)
{
    Position* position = new Position(player,this,players->value().size());
    addChildRow(position);
}

void LiveGame::addDrink(Player* player, Drink* drink)
{
    Round* round = 0;
    if(!rounds->value().isEmpty())
    {
        rounds->value().last();
    }

    LiveGameDrink* liveGameDrink = new LiveGameDrink(player,round,drink);
    addChildRow(liveGameDrink);
}

void LiveGame::setState(Round::RoundState state)
{
    if(rounds->value().isEmpty())
    {
        return;
    }

    rounds->value().last()->db_state->setValue(state);
}

Round* LiveGame::createRound()
{
    Round* round = new Round(this,rounds->value().count());
    addChildRow(round);

    return round;
}

Round* LiveGame::startNextRound()
{
    Round* lastRound = rounds->value().last();
    lastRound->db_state->setValue(Round::FinishedState);

    return createRound();
}

void LiveGame::finishGame()
{
    Round* round = rounds->value().takeLast();

    Rounds::instance()->deleteRow(round);
}

END_ROW_IMPLEMENTATION()
