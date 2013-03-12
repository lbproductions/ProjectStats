#ifndef DATABASE_POSITION_H
#define DATABASE_POSITION_H

#include "row.h"
#include "table.h"
#include "attribute.h"
#include "databaseattribute.h"

START_ROW_DECLARATION(Position, Row)
#if QT_VERSION >= 0x050000
    Q_OBJECT
#endif

    DECLARE_ROW_CONSTRUCTORS(Position, Position)

    Position(Player* player, Game* game, int position);

    DECLARE_DATABASEATTRIBUTE(int,Position,playerId)
    DECLARE_DATABASEATTRIBUTE(int,Position,gameId)
    DECLARE_DATABASEATTRIBUTE(int,Position,position)

END_ROW_DECLARATION(Position)

START_TABLE_DECLARATION(Position)
END_TABLE_DECLARATION()

#endif // DATABASE_POSITION_H
