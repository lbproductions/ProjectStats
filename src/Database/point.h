#ifndef DATABASE_POINT_H
#define DATABASE_POINT_H


#include "row.h"
#include "table.h"
#include "attribute.h"
#include "databaseattribute.h"

namespace Database
{
    class Round;
    class Player;
}

START_ROW_DECLARATION(Point, Row)
    DECLARE_ROW_CONSTRUCTORS(Point, Point)

    Point(Round* round, Player* player, int points);

    DECLARE_DATABASEATTRIBUTE(int,Point,playerId)
    DECLARE_DATABASEATTRIBUTE(int,Point,roundId)
    DECLARE_DATABASEATTRIBUTE(int,Point,points)

END_ROW_DECLARATION(Point)

START_TABLE_DECLARATION(Point)
END_TABLE_DECLARATION()

#endif // DATABASE_POINT_H
