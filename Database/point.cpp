#include "point.h"

START_TABLE_IMPLEMENTATION(Point)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Point, Point, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(int,Point,playerId,tr("PlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Point,roundId,tr("RoundId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Point,points,tr("Points"))
}

QString Point::mimeType() const
{
    return "application/projectstats.point";
}

END_ROW_IMPLEMENTATION()
