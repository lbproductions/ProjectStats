#ifndef ENOUGHLEAGUEPLAYERSRULE_H
#define ENOUGHLEAGUEPLAYERSRULE_H

#include "ruleconnective.h"

#include <QPointer>

namespace Database
{
    class Game;
    class Player;
}

START_ROW_DECLARATION(EnoughLeaguePlayersRule, RuleConnective)
    DECLARE_ROW_CONSTRUCTORS(EnoughLeaguePlayersRule, RuleConnective)

    void addPlayer(Player *player);
    void addPlayers(QList<Player*> players);

    bool appliesTo(Row* row);

END_ROW_DECLARATION(EnoughLeaguePlayersRule)

#endif // ENOUGHLEAGUEPLAYERSRULE_H
