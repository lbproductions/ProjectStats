#include "point.h"

#include "round.h"
#include "player.h"

START_TABLE_IMPLEMENTATION(Point)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Point, Point, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(int,Point,playerId,tr("PlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Point,roundId,tr("RoundId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Point,points,tr("Points"))

    round2 = new ChildRelation<Point,Round>("round2","round2",this);
}

Point::Point(Round *round, Player *player, int points) :
    Row(0,Points::instance())
{
    initializeAttributes();

    this->playerId->setValue(player->id());
    this->roundId->setValue(round->id());
    this->points->setValue(points);
}

QString Point::mimeType() const
{
    return "application/projectstats.point";
}

END_ROW_IMPLEMENTATION()
