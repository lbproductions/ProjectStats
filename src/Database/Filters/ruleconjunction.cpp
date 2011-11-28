#include "ruleconjunction.h"

START_ROW_IMPLEMENTATION(RuleConjunction, Rule, RuleConnective)
{
    type->setValue(Rule::RuleConjunctionType);
}

QString RuleConjunction::mimeType() const
{
    return Rule::mimeType();
}

bool RuleConjunction::appliesTo(Row *row)
{
    foreach(Rule* rule, rules->value())
    {
        if(!rule->appliesTo(row))
        {
            return false;
        }
    }

    return true;
}

END_ROW_IMPLEMENTATION()
