#include "ruleconnective.h"

START_ROW_IMPLEMENTATION(RuleConnective, Rule, Rule)
{
    IMPLEMENT_LISTATTRIBUTE(Rule*,RuleConnective,rules, tr("Rules"))
}

QString RuleConnective::mimeType() const
{
    return Rule::mimeType();
}

QList<Rule*> RuleConnective::calculate_rules()
{
    return Rules::instance()->rowsBySqlCondition(QLatin1String(" WHERE parentRuleId = ")+QString::number(m_id));
}

void RuleConnective::addRule(Rule *rule)
{
    rule->parentRuleId->setValue(this->id());
    connect(this,SIGNAL(idChanged(int)),rule->parentRuleId,SLOT(changeValue(int)));
    addChildRow(rule);
    rules->recalculateFromScratch();
}

END_ROW_IMPLEMENTATION()
