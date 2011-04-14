#include "ruledisjunction.h"

START_ROW_IMPLEMENTATION(RuleDisjunction, Rule, RuleConnective)
{
}

QString RuleDisjunction::mimeType() const
{
    return "application/projectstats.rule";
}

bool RuleDisjunction::appliesTo(::Database::Row *row)
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
