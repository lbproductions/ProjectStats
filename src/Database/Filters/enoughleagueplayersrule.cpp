#include "enoughleagueplayersrule.h"

#include "atomicrule.h"
#include "constraints.h"

#include <Database/player.h>
#include <Database/game.h>

namespace Database {

REGISTER_ASROWTYPE( EnoughLeaguePlayersRule, Rule )

EnoughLeaguePlayersRule::EnoughLeaguePlayersRule() :
    RuleConnective(0,Rules::instance())
{
    initializeAttributes();

    type->setValue(Rule::EnoughLeaguePlayersRuleType);

    m_table->insertRow(this);
}

EnoughLeaguePlayersRule::EnoughLeaguePlayersRule(const EnoughLeaguePlayersRule &other) :
    RuleConnective(other.m_id, other.m_table)
{
    initializeAttributes();
}

EnoughLeaguePlayersRule::EnoughLeaguePlayersRule(int id, TableBase *table) :
    RuleConnective(id,table)
{
    initializeAttributes();
}

void EnoughLeaguePlayersRule::initializeAttributes()
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
    playerIsInGameRule->constraintId->setValue(Constraints::IsEqual);
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
