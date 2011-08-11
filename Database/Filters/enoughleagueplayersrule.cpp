#include "enoughleagueplayersrule.h"

#include "atomicrule.h"

#include <Database/player.h>
#include <Database/game.h>

START_ROW_IMPLEMENTATION(EnoughLeaguePlayersRule, Rule, RuleConnective)
{
}

QString EnoughLeaguePlayersRule::mimeType() const
{
    return Rule::mimeType();
}

void EnoughLeaguePlayersRule::addPlayer(Player *player)
{
    AtomicRule* playerIsInGameRule = new AtomicRule();
    playerIsInGameRule->attributeName->setValue("playerId");
    playerIsInGameRule->parameter->setValue(QString::number(player->id()));
    addRule(playerIsInGameRule);
}

void EnoughLeaguePlayersRule::addPlayers(QList<Player*> players)
{
    foreach(Player* player, players)
    {
        addPlayer(player);
    }
}

bool EnoughLeaguePlayersRule::appliesTo(Row *row)
{
    Game* game = static_cast<Game*>(row);
    int playersInGame = 0;

    QList<Player*> players = game->players->value();

    QList<Rule*> list = rules->value();
    foreach(Player* player, players)
    {
        foreach(Rule* rule, list)
        {
            AtomicRule* arule = static_cast<AtomicRule*>(rule);
            if(player->id() == arule->parameter->value().toInt())
            {
                ++playersInGame;
                break;
            }
        }
    }

    return ((double) playersInGame / (double) players.size()) > 0.75;
}

END_ROW_IMPLEMENTATION()
