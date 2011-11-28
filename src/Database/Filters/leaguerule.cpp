#include "leaguerule.h"

#include "enoughleagueplayersrule.h"
#include "atomicrule.h"
#include "constraints.h"

namespace Database
{

REGISTER_ASROWTYPE(LeagueRule, Rule)

LeagueRule::LeagueRule() :
    RuleConjunction(0,Rules::instance())
{
    initializeAttributes();
}

LeagueRule::LeagueRule(LeagueFolderCategorie* /*parent*/) :
    RuleConjunction(0,Rules::instance())
{
    initializeAttributes();

    m_table->insertRow(this);

    AtomicRule* gameIsBeforeRule = new AtomicRule();
    gameIsBeforeRule->constraintId->setValue(Constraints::DateIsBefore);
    gameIsBeforeRule->attributeName->setValue(QLatin1String("date"));
    addRule(gameIsBeforeRule);

    AtomicRule* gameIsAfterRule = new AtomicRule();
    gameIsAfterRule->constraintId->setValue(Constraints::DateIsAfter);
    gameIsAfterRule->attributeName->setValue(QLatin1String("date"));
    addRule(gameIsAfterRule);

    EnoughLeaguePlayersRule* enoughLeaguePlayersRule = new EnoughLeaguePlayersRule();
    addRule(enoughLeaguePlayersRule);
}

LeagueRule::LeagueRule(const LeagueRule &other) :
    RuleConjunction(other.m_id, other.m_table)
{
    initializeAttributes();
}

LeagueRule::LeagueRule(int id, TableBase *table) :
    RuleConjunction(id,table)
{
    initializeAttributes();
}

void LeagueRule::initializeAttributes()
{
    IMPLEMENT_ATTRIBUTE(EnoughLeaguePlayersRule*, LeagueRule, enoughLeaguePlayersRule, tr("EnoughLeaguePlayersRule"))
    IMPLEMENT_ATTRIBUTE(AtomicRule*, LeagueRule, gameIsBeforeRule, tr("gameIsBeforeRule"))
    IMPLEMENT_ATTRIBUTE(AtomicRule*, LeagueRule, gameIsAfterRule, tr("gameIsAfterRule"))
}

EnoughLeaguePlayersRule* LeagueRule::calculate_enoughLeaguePlayersRule()
{
    return static_cast<EnoughLeaguePlayersRule*>(
                Rules::instance()->rowsBySqlCondition(
                    QLatin1String(" WHERE parentRuleId = ")+QString::number(m_id)+QLatin1String(" AND type = 3")
                    ).at(0)
                );
}

AtomicRule* LeagueRule::calculate_gameIsBeforeRule()
{
    return static_cast<AtomicRule*>(
                Rules::instance()->rowsBySqlCondition(
                    QLatin1String(" WHERE parentRuleId = ")+QString::number(m_id)+QLatin1String(" AND constraintId = 0")
                    ).at(0)
                );
}

AtomicRule* LeagueRule::calculate_gameIsAfterRule()
{
    return static_cast<AtomicRule*>(
                Rules::instance()->rowsBySqlCondition(
                    QLatin1String(" WHERE parentRuleId = ")+QString::number(m_id)+QLatin1String(" AND constraintId = 1")
                    ).at(0)
                );
}

void LeagueRule::addPlayer(Player *player)
{
    enoughLeaguePlayersRule->value()->addPlayer(player);
}

void LeagueRule::setStartDate(const QDate& date)
{
    gameIsAfterRule->value()->parameter->setValue(date.toString("dd.MM.yyyy"));
}

void LeagueRule::setEndDate(const QDate& date)
{
    gameIsBeforeRule->value()->parameter->setValue(date.toString("dd.MM.yyyy"));
}

QString LeagueRule::mimeType() const
{
    return Rule::mimeType();
}

}
