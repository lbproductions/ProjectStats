#ifndef DATABASE_LIVEGAME_H
#define DATABASE_LIVEGAME_H

#include "game.h"

#include "row.h"
#include "table.h"
#include "databaseattribute.h"
#include "listattribute.h"
#include "round.h"

#include <Database/Calculator/livegamecalculator.h>

namespace Database{
    class Drink;
}

class QTime;

START_ROW_DECLARATION(LiveGame, Game)
    DECLARE_ROW_CONSTRUCTORS(LiveGame, Game)

    LiveGame(QString type);

    DECLARE_LISTATTRIBUTE_IN_CALC(LiveGameDrink*,LiveGame,LiveGameCalculator,drinks)
    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Drink*,int,LiveGame,LiveGameCalculator,drinkCount)

    DECLARE_MAPPINGATTRIBUTE_IN_CALC(Player*,QList<LiveGameDrink*>,LiveGame,LiveGameCalculator,drinksPerPlayer)
    DECLARE_LISTATTRIBUTE_IN_CALC(Player*,LiveGame,LiveGameCalculator,playersSortedByAlcPegel)

    DECLARE_LISTATTRIBUTE_IN_CALC(Round*,LiveGame,LiveGameCalculator,rounds)
    DECLARE_ATTRIBUTE_IN_CALC(int,LiveGame,LiveGameCalculator,roundCount)

    DECLARE_ATTRIBUTE_IN_CALC(int,LiveGame,LiveGameCalculator,percComplete)
    DECLARE_VIRTUAL_ATTRIBUTE_IN_CALC(int,LiveGame,LiveGameCalculator,totalPoints)
    DECLARE_ATTRIBUTE_IN_CALC(Round*,LiveGame,LiveGameCalculator,lastRound)
    DECLARE_ATTRIBUTE_IN_CALC(Round*,LiveGame,LiveGameCalculator,currentRound)
    DECLARE_ATTRIBUTE_IN_CALC(Player*,LiveGame,LiveGameCalculator,cardmixer)
    DECLARE_ATTRIBUTE_IN_CALC(bool,LiveGame,LiveGameCalculator,isFinished)

    DECLARE_LISTATTRIBUTE_IN_CALC(Player*,LiveGame,LiveGameCalculator,currentPlayingPlayers)

    void addPlayer(Player* player);

    void addDrink(Player* player, Drink* drink);

    void setState(Round::RoundState state);

    void finishGame();

    Round* startNextRound();

    Gui::Details::SummaryWidget* summaryWidget();

private:
    virtual Round *createRound();

END_ROW_DECLARATION(LiveGame)

Q_DECLARE_METATYPE(QMap<Database::Player* COMMA QList<Database::LiveGameDrink*> >)

#endif // DATABASE_LIVEGAME_H
