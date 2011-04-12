#include "livegamedrink.h"

#include <QDateTime>

START_TABLE_IMPLEMENTATION(LiveGameDrink)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(LiveGameDrink, LiveGameDrink, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(int,LiveGameDrink,playerId,tr("PlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,LiveGameDrink,roundId,tr("RoundId"))
    IMPLEMENT_DATABASEATTRIBUTE(QDateTime,LiveGameDrink,time,tr("Time"))
    IMPLEMENT_DATABASEATTRIBUTE(int,LiveGameDrink,drinkId,tr("DrinkId"))
}

QString LiveGameDrink::mimeType() const
{
    return "application/projectstats.liveGameDrink";
}

END_ROW_IMPLEMENTATION()
