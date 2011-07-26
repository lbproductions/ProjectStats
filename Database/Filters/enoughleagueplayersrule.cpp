#include "enoughleagueplayersrule.h"

#include "filter.h"

#include <Database/player.h>
#include <Database/game.h>

using namespace Database::Filters;

EnoughLeaguePlayersRule::EnoughLeaguePlayersRule(Filter *parent) :
    Rule()
{
}

void EnoughLeaguePlayersRule::addPlayer(Player *player)
{
    m_players.append(player);
}

void EnoughLeaguePlayersRule::addPlayers(QList<QPointer<Player> > players)
{
    m_players.append(players);
}

bool Database::Filters::EnoughLeaguePlayersRule::appliesTo(::Database::Row *row)
{
    Game* game = static_cast<Game*>(row);
    int playersInGame = 0;

    QList<Player*> players = game->playersSortedByPlacement->value();

    foreach(Player *player, players)
    {
        if(m_players.contains(player))
        {
            ++playersInGame;
        }
    }

    return ((double) playersInGame / (double) players.size()) > 0.75;
}
