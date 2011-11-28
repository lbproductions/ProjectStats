#ifndef LEAGUERULE_H
#define LEAGUERULE_H

#include <Database/row.h>
#include "ruleconjunction.h"

namespace Database
{
class EnoughLeaguePlayersRule;
class Player;
class LeagueFolderCategorie;
class AtomicRule;
}

START_ROW_DECLARATION(LeagueRule, RuleConjunction)
    DECLARE_ROW_CONSTRUCTORS(LeagueRule, Rule)

    LeagueRule(LeagueFolderCategorie* parent);

    DECLARE_ATTRIBUTE(EnoughLeaguePlayersRule*, LeagueRule, enoughLeaguePlayersRule)
    DECLARE_ATTRIBUTE(AtomicRule*, LeagueRule, gameIsAfterRule)
    DECLARE_ATTRIBUTE(AtomicRule*, LeagueRule, gameIsBeforeRule)

    void addPlayer(Player* player);

    void setStartDate(const QDate& date);
    void setEndDate(const QDate &date);

END_ROW_DECLARATION(LeagueRule)

#endif // LEAGUERULE_H
