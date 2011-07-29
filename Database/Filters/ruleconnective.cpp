#include "ruleconnective.h"

START_ROW_IMPLEMENTATION(RuleConnective, Rule, Rule)
{
    IMPLEMENT_LISTATTRIBUTE(Rule*,RuleConnective,rules, tr("Rules"))
}

QString RuleConnective::mimeType() const
{
    return "application/projectstats.rule";
}

QList<Rule*> RuleConnective::calculate_rules()
{
    QList<Rule*> list;
    foreach(Rule* rule, Rules::instance()->rowsBySqlCondition(" WHERE parentRuleId = "+m_id))
    {
        list.append(rule);
    }

    return list;
}

void RuleConnective::addRule(Rule *rule)
{
    addChildRow(rule);
    //rules->append(rule);
}

END_ROW_IMPLEMENTATION()
