#ifndef DATABASE_RULECONNECTIVE_H
#define DATABASE_RULECONNECTIVE_H

#include "rule.h"

START_ROW_DECLARATION(RuleConnective, Rule)
    DECLARE_ROW_CONSTRUCTORS(RuleConnective, Rule)

    void addRule(Rule *rule);

protected:
    DECLARE_ATTRIBUTE(QList<Rule*>, RuleConnective, rules)

END_ROW_DECLARATION(RuleConnective)

#endif // DATABASE_RULECONNECTIVE_H
