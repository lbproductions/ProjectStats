#include "livegame.h"

#include "player.h"
#include "position.h"
#include "drink.h"
#include "livegamedrink.h"
#include "point.h"
#include "round.h"

#include <QTime>

#include <Gui/Details/LiveGameDetails/livegamesummarywidget.h>


START_ROW_IMPLEMENTATION(LiveGame, Game, Game)
{
    LiveGameCalculator* calc = new LiveGameCalculator(this,this);
    m_calc = calc;

    IMPLEMENT_LISTATTRIBUTE_IN_CALC(LiveGameDrink*,LiveGame,LiveGameCalculator,calc,drinks,tr("Drinks"))
    //drinks->setCheckChange(false);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Drink*,int,LiveGame,LiveGameCalculator,calc,drinkCount,tr("DrinkCount"))
    drinks->addDependingAttribute(drinkCount);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,QList<LiveGameDrink*>,LiveGame,LiveGameCalculator,calc,drinksPerPlayer,tr("Drinks per Player"))
    drinks->addDependingAttribute(drinksPerPlayer);

    IMPLEMENT_LISTATTRIBUTE_IN_CALC(Player*,LiveGame,LiveGameCalculator,calc,playersSortedByAlcPegel,tr("PlayersSortedByAlcPegel"))
    drinksPerPlayer->addDependingAttribute(playersSortedByAlcPegel);

    IMPLEMENT_LISTATTRIBUTE_IN_CALC(Round*,LiveGame,LiveGameCalculator,calc,rounds,tr("Rounds"))

    rounds->addDependingAttribute(length);

    IMPLEMENT_ATTRIBUTE_IN_CALC(Round*,LiveGame,LiveGameCalculator,calc,currentRound,tr("CurrentRound"))
    rounds->addDependingAttribute(currentRound);
    currentRound->addDependingAttribute(state);

    IMPLEMENT_ATTRIBUTE_IN_CALC(int,LiveGame,LiveGameCalculator,calc,roundCount,tr("Round Count"))
    currentRound->addDependingAttribute(roundCount);

    IMPLEMENT_ATTRIBUTE_IN_CALC(int,LiveGame,LiveGameCalculator,calc,percComplete,tr("%Complete"))
    currentRound->addDependingAttribute(percComplete);

    IMPLEMENT_ATTRIBUTE_IN_CALC(Round*,LiveGame,LiveGameCalculator,calc,lastRound,tr("LastRound"))
    currentRound->addDependingAttribute(lastRound);

    IMPLEMENT_LISTATTRIBUTE_IN_CALC(Player*,LiveGame,LiveGameCalculator,calc,currentPlayingPlayers,tr("CurrentPlayingPlayers"))
    currentRound->addDependingAttribute(currentPlayingPlayers);

    IMPLEMENT_ATTRIBUTE_IN_CALC(Player*,LiveGame,LiveGameCalculator,calc,cardmixer,tr("Cardmixer"))
    currentRound->addDependingAttribute(cardmixer);

    IMPLEMENT_VIRTUAL_ATTRIBUTE_IN_CALC(int,LiveGame,LiveGameCalculator,totalPoints,tr("TotalPoints"))
    currentRound->addDependingAttribute(totalPoints);
    totalPoints->addDependingAttribute(points);

    IMPLEMENT_ATTRIBUTE_IN_CALC(bool,LiveGame,LiveGameCalculator,calc,isFinished,tr("Finished"))

    IMPLEMENT_VIRTUAL_MAPPINGATTRIBUTE_IN_CALC(int,QMap<Player* COMMA int>,LiveGame,LiveGameCalculator,placementAfterRounds,tr("PlacementAfterRounds"))
    rounds->addDependingAttribute(placementAfterRounds);
    IMPLEMENT_VIRTUAL_MAPPINGATTRIBUTE_IN_CALC(Player*,int,LiveGame,LiveGameCalculator,leadingRounds,tr("LeadingRounds"))
    placementAfterRounds->addDependingAttribute(leadingRounds);
    IMPLEMENT_VIRTUAL_MAPPINGATTRIBUTE_IN_CALC(Player*,double,LiveGame,LiveGameCalculator,averagePlacement,tr("AveragePlacement"))
    placementAfterRounds->addDependingAttribute(averagePlacement);

}

LiveGame::LiveGame(QString type) :
    Game(type,true)
{
    initializeAttributes();
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
    Round* round = currentRound->value();

    LiveGameDrink* liveGameDrink = new LiveGameDrink(player,round,drink);
    addChildRow(liveGameDrink);
    this->drinks->recalculateFromScratch();
    emit drinkAdded(liveGameDrink);
}

void LiveGame::setState(Round::RoundState state)
{
    currentRound->value()->setState(state);
}

Round* LiveGame::createRound()
{
    Round* round = new Round(this,rounds->value().count());
    addChildRow(round);

    return round;
}

Round* LiveGame::startNextRound()
{
    Round* lastRound = currentRound->value();
    Round* newRound = createRound();/*
    rounds->recalculate();
    rounds->futureWatcher()->futureWatcher()->waitForFinished();
    currentRound->recalculate();
    currentRound->futureWatcher()->futureWatcher()->waitForFinished();
    currentRound->emitChanged();*/
    if(lastRound)
    {
        lastRound->setState(Round::FinishedState);
    }

    this->rounds->recalculateFromScratch();

    emit roundAdded(lastRound);

    newRound->length->addDependingAttribute(length);

    //Dieser Statuswechsel initialisiert den Timer, der die Length aktualisiert
    newRound->setState(Round::RunningState);

    return newRound;
}

void LiveGame::finishGame()
{
    Round* round = rounds->value().last();
    Round* lastRound = this->lastRound->value();

    Rounds::instance()->deleteRow(round);
    this->rounds->recalculateFromScratch();

    if(lastRound)
    {
        foreach(LiveGameDrink* d, this->drinks->value())
        {
            d->roundId->setValue(lastRound->id());
        }
    }
}

QWidget* LiveGame::summaryWidget(){
    return new Gui::Details::LiveGameDetails::LiveGameSummaryWidget(this);
}

END_ROW_IMPLEMENTATION()
