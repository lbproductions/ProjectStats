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

END_ROW_IMPLEMENTATION()
