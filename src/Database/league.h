#ifndef LEAGUE_H
#define LEAGUE_H

class QDateTime;

#include "row.h"
#include "table.h"
#include "databaseattribute.h"
#include "game.h"
#include "player.h"

START_ROW_DECLARATION(League, Row)
    DECLARE_ROW_CONSTRUCTORS(League, League)

    DECLARE_DATABASEATTRIBUTE(QString,League,name)
    DECLARE_DATABASEATTRIBUTE(QDateTime,League,startDate)
    DECLARE_DATABASEATTRIBUTE(QDateTime,League,endDate)
    DECLARE_DATABASEATTRIBUTE(double,League,playerPercentage)
    DECLARE_DATABASEATTRIBUTE(QString,League,gameType)
    DECLARE_DATABASEATTRIBUTE(int,League,categorieId)

    DECLARE_LISTATTRIBUTE(Game*,League,games)
    DECLARE_LISTATTRIBUTE(Player*,League,players)

END_ROW_DECLARATION(League)

START_TABLE_DECLARATION(League)

END_TABLE_DECLARATION()

#endif // LEAGUE_H
