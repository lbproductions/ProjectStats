#include "rule.h"

#include "ruleconjunction.h"
#include "ruledisjunction.h"
#include "atomicrule.h"
#include "enoughleagueplayersrule.h"

START_TABLE_IMPLEMENTATION(Rule)
QPointer<Rule> Rules::createRowInstance(int id)
{
    Rule *row = new Rule(id,this);
    Rule *row2 = 0;

    switch(row->type->value())
    {
    case Rule::RuleConjunctionType:
        row2 = new RuleConjunction(id,this);
        break;
    case Rule::RuleDisjunctionType:
        row2 = new RuleDisjunction(id,this);
        break;
    case Rule::AtomicRuleType:
        row2 = new AtomicRule(id,this);
        break;
    case Rule::EnoughLeaguePlayersRuleType:
        row2 = new EnoughLeaguePlayersRule(id,this);
        break;
    default:
        break;
    }

    if(row2 != 0)
    {
        return row2;
    }

    return row;
}

END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Rule, Rule, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(int,Rule,parentRuleId, tr("Parent rule id"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Rule,type,tr("Type"))
}

QString Rule::mimeType() const
{
    return "application/projectstats.rule";
}

bool Rule::appliesTo(Row* /*row*/)
{
    return false;
}

END_ROW_IMPLEMENTATION()
