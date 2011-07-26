#include "leaguefilter.h"

#include "rules.h"

#include <handler.h>
#include <Database/database.h>
#include <Database/game.h>

#include <QDateTime>

using namespace Database::Filters;

LeagueFilter::LeagueFilter(QObject *parent) :
    Filter(parent),
    m_beginningRule(new AtomicRule()),
    m_endRule(new AtomicRule()),
    m_enoughPlayersRule(new EnoughLeaguePlayersRule())
{
    m_beginningRule->attributeName->setValue("date");
    m_beginningRule->constraintId->setValue(Constraints::DateIsAfter);
    m_beginningRule->parameter->setValue(QDateTime().toString());

    m_endRule->attributeName->setValue("date");
    m_endRule->constraintId->setValue(Constraints::DateIsBefore);
    m_endRule->parameter->setValue(QDateTime().toString());

    m_conjunction = new RuleConjunction();
    m_conjunction->addRule(m_beginningRule);
    m_conjunction->addRule(m_endRule);
}

void Database::Filters::LeagueFilter::setPeriod(const QDate &begin, const QDate &end)
{
    m_beginningRule->parameter->setValue(begin.toString());
    m_endRule->parameter->setValue(end.toString());
}

void LeagueFilter::addPlayer(Player *player)
{
    m_enoughPlayersRule->addPlayer(player);
}

void LeagueFilter::addPlayers(QList<QPointer<Player> > players)
{
    m_enoughPlayersRule->addPlayers(players);
}

Database::RuleConjunction* LeagueFilter::conjunction(){
    return m_conjunction;
}

QList<Database::Game*> LeagueFilter::games()
{
    QList<Game*> list;
    foreach(Game *game, Games::instance()->allRows())
    {
        if(m_conjunction.isNull()){
            if(m_conjunction->appliesTo(game))
            {
                list.append(game);
            }
        }
    }

    return list;
}
