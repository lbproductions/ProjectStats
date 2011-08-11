#ifndef RULECONNECTIVE_H
#define RULECONNECTIVE_H

#include "rule.h"

#include <Database/listattribute.h>

START_ROW_DECLARATION(RuleConnective, Rule)
    DECLARE_ROW_CONSTRUCTORS(RuleConnective, Rule)

    void addRule(Rule *rule);

    DECLARE_LISTATTRIBUTE(Rule*, RuleConnective, rules)

END_ROW_DECLARATION(RuleConnective)

#endif // RULECONNECTIVE_H
