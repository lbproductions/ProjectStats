#include "ruleconnective.h"

START_ROW_IMPLEMENTATION(RuleConnective, Rule, Rule)
{
    IMPLEMENT_ATTRIBUTE(QList<Rule*>,RuleConnective,rules, tr("Rules"))
}

QString RuleConnective::mimeType() const
{
    return "application/projectstats.rule";
}

QList<Rule*> RuleConnective::calculate_rules()
{
    return Rules::instance()->rowsBySqlCondition(" WHERE parentRuleId = "+m_id);
}

void RuleConnective::addRule(Rule *rule)
{
    addChildRow(rule);
    rules->value().append(rule);
}

END_ROW_IMPLEMENTATION()
