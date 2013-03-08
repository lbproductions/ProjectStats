#include "league.h"

#include <Misc/logger.h>

#include "leagueplayerassignment.h"

START_TABLE_IMPLEMENTATION(League)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(League, League, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(QString,League,name,tr("Name"))
    IMPLEMENT_DATABASEATTRIBUTE(QDateTime,League,startDate,tr("StartDate"))
    IMPLEMENT_DATABASEATTRIBUTE(QDateTime,League,endDate,tr("EndDate"))
    IMPLEMENT_DATABASEATTRIBUTE(double,League,playerPercentage,tr("PlayerPercentage"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,League,gameType,tr("GameType"))
    IMPLEMENT_DATABASEATTRIBUTE(int,League,categorieId,tr("CategorieId"))

    IMPLEMENT_LISTATTRIBUTE(Game*,League,games,tr("Games"))
    IMPLEMENT_LISTATTRIBUTE(Player*,League,players,tr("Players"))
}

QString League::mimeType() const
{
    return "application/projectstats.league";
}

QList<Game*> League::calculate_games() {

    QList<Game*> games;
    foreach(Game* game, Games::instance()->allRows()) {
        if(this->gameType->value() == "General" || game->type->value() == this->gameType->value()){
            if(game->date->value().date() > this->startDate->value().date() && game->date->value().date() < this->endDate->value().date()) {
                int playerCount = 0;
                foreach(Player* player, this->players->value()) {
                    if(game->players->value().contains(player)) {
                        playerCount++;
                    }
                }
                if( (double)playerCount / (double)game->players->value().size() >= this->playerPercentage->value()) {
                    games.append(game);
                }
            }
        }
    }

    return games;
}

QList<Player*> League::calculate_players() {
    QList<Player*> players;

    foreach(LeaguePlayerAssignment* a, LeaguePlayerAssignments::instance()->allRows()) {
        if(a->leagueId->value() == this->id()) {
            players.append(Players::instance()->rowById(a->playerId->value()));
        }
    }

    return players;
}

END_ROW_IMPLEMENTATION()
