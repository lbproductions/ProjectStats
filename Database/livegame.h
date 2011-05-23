#ifndef DATABASE_LIVEGAME_H
#define DATABASE_LIVEGAME_H

#include "game.h"

#include "row.h"
#include "table.h"
#include "databaseattribute.h"
#include "listattribute.h"

#include <Database/Calculator/livegamecalculator.h>

namespace Database{
    class Drink;
    class Round;
}

class QTime;

START_ROW_DECLARATION(LiveGame, Game)
    DECLARE_ROW_CONSTRUCTORS(LiveGame, Game)

    DECLARE_LISTATTRIBUTE_IN_CALC(Drink*,LiveGame,LiveGameCalculator,drinks)
    DECLARE_LISTATTRIBUTE_IN_CALC(Round*,LiveGame,LiveGameCalculator,rounds)

    DECLARE_ATTRIBUTE_IN_CALC(int,LiveGame,LiveGameCalculator,percComplete)

END_ROW_DECLARATION(LiveGame)

#endif // DATABASE_LIVEGAME_H
