#include "ruledisjunction.h"

START_ROW_IMPLEMENTATION(RuleDisjunction, Rule, RuleConnective)
{
}

QString RuleDisjunction::mimeType() const
{
    return Rule::mimeType();
}

bool RuleDisjunction::appliesTo(Row *row)
{
    foreach(Rule* rule, rules->value())
    {
        if(rule->appliesTo(row))
        {
            return true;
        }
    }

    return false;
}

END_ROW_IMPLEMENTATION()
