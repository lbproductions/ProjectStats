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

    DECLARE_LISTATTRIBUTE_IN_CALC(Drink*,LiveGame,LiveGameCalculator,drinks)
    DECLARE_LISTATTRIBUTE_IN_CALC(Round*,LiveGame,LiveGameCalculator,rounds)

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

private:
    virtual Round *createRound();

END_ROW_DECLARATION(LiveGame)

#endif // DATABASE_LIVEGAME_H
