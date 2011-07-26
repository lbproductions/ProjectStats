#ifndef LEAGUEFILTER_H
#define LEAGUEFILTER_H

#include "filter.h"

#include <QPointer>

class QDate;

namespace Database
{

class Player;
class Game;
class AtomicRule;
class RuleConjunction;

namespace Filters{

class EnoughLeaguePlayersRule;

class LeagueFilter : public Filter
{
    Q_OBJECT
public:
    LeagueFilter(QObject *parent = 0);

    void setPeriod(const QDate &begin, const QDate &end);

    void addPlayer(Player *player);
    void addPlayers(QList<QPointer<Player> > players);

    QList<Game*> games();

    RuleConjunction* conjunction();

private:
    AtomicRule *m_beginningRule;
    AtomicRule *m_endRule;
    QPointer<RuleConjunction> m_conjunction;
    EnoughLeaguePlayersRule *m_enoughPlayersRule;
};

}
}
#endif // LEAGUEFILTER_H
