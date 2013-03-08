#include "leagueplayerassignment.h"

START_TABLE_IMPLEMENTATION(LeaguePlayerAssignment)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(LeaguePlayerAssignment, LeaguePlayerAssignment, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(int,LeaguePlayerAssignment,leagueId,tr("LeagueId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,LeaguePlayerAssignment,playerId,tr("PlayerId"))
}

QString LeaguePlayerAssignment::mimeType() const
{
    return "application/projectstats.LeaguePlayerAssignment";
}

END_ROW_IMPLEMENTATION()
