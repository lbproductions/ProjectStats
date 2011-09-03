#include "playerplaceassignment.h"

START_TABLE_IMPLEMENTATION(PlayerPlaceAssignment)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(PlayerPlaceAssignment, PlayerPlaceAssignment, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(int,PlayerPlaceAssignment,placeId,tr("PlaceId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,PlayerPlaceAssignment,playerId,tr("PlayerId"))
}

QString PlayerPlaceAssignment::mimeType() const
{
    return "application/projectstats.playerPlaceAssignment";
}

END_ROW_IMPLEMENTATION()
