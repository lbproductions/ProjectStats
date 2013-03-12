#ifndef LEAGUEPLAYERASSIGNMENT_H
#define LEAGUEPLAYERASSIGNMENT_H

#include "row.h"
#include "table.h"
#include "databaseattribute.h"

START_ROW_DECLARATION(LeaguePlayerAssignment, Row)
#if QT_VERSION >= 0x050000
    Q_OBJECT
#endif

    DECLARE_ROW_CONSTRUCTORS(LeaguePlayerAssignment, LeaguePlayerAssignment)

    DECLARE_DATABASEATTRIBUTE(int,LeaguePlayerAssignment,playerId)
    DECLARE_DATABASEATTRIBUTE(int,LeaguePlayerAssignment,leagueId)

END_ROW_DECLARATION(LeaguePlayerAssignment)

START_TABLE_DECLARATION(LeaguePlayerAssignment)
END_TABLE_DECLARATION()
#endif // LEAGUEPLAYERASSIGNMENT_H
