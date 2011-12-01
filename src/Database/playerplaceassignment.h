#ifndef PLAYERPLACEASSIGNMENT_H
#define PLAYERPLACEASSIGNMENT_H

#include <LBDatabase/LBDatabase.h>

START_ROW_DECLARATION(PlayerPlaceAssignment, Row)
    DECLARE_ROW_CONSTRUCTORS(PlayerPlaceAssignment, PlayerPlaceAssignment)

    DECLARE_DATABASEATTRIBUTE(int,PlayerPlaceAssignment,playerId)
    DECLARE_DATABASEATTRIBUTE(int,PlayerPlaceAssignment,placeId)

END_ROW_DECLARATION(PlayerPlaceAssignment)

START_TABLE_DECLARATION(PlayerPlaceAssignment)
END_TABLE_DECLARATION()

#endif // PLAYERPLACEASSIGNMENT_H
