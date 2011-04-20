#ifndef DATABASE_LIVEGAME_H
#define DATABASE_LIVEGAME_H

#include "game.h"

#include "row.h"
#include "table.h"
#include "databaseattribute.h"

#include <Database/Calculator/livegamecalculator.h>

namespace Database{
    class Drink;
    class Round;
}

START_ROW_DECLARATION(LiveGame, Game)
    DECLARE_ROW_CONSTRUCTORS(LiveGame, Game)

    DECLARE_ATTRIBUTE_IN_CALC(QList<Drink*>,LiveGame,LiveGameCalculator,drinks)
    DECLARE_ATTRIBUTE_IN_CALC(QList<Round*>,LiveGame,LiveGameCalculator,rounds)

END_ROW_DECLARATION(LiveGame)

#endif // DATABASE_LIVEGAME_H
