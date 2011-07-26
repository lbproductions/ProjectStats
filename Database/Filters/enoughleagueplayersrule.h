#ifndef ENOUGHLEAGUEPLAYERSRULE_H
#define ENOUGHLEAGUEPLAYERSRULE_H

#include "rule.h"

#include <QPointer>

namespace Database
{

class Game;
class Player;

namespace Filters
{

class Filter;

class EnoughLeaguePlayersRule : public Rule
{
    Q_OBJECT
public:
    explicit EnoughLeaguePlayersRule(Filter *parent = 0);

    bool appliesTo(::Database::Row* row);

    void addPlayer(Player *player);
    void addPlayers(QList<QPointer<Player> > players);
private:
    QList<QPointer<Player> > m_players;
};

}
}
#endif // ENOUGHLEAGUEPLAYERSRULE_H
