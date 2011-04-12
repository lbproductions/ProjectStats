#include "position.h"

START_TABLE_IMPLEMENTATION(Position)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Position, Position, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(int,Position,playerId,tr("PlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Position,gameId,tr("GameId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Position,position,tr("Position"))
}

QString Position::mimeType() const
{
    return "application/projectstats.position";
}

END_ROW_IMPLEMENTATION()
