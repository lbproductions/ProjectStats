#ifndef RULEDISJUNCTION_H
#define RULEDISJUNCTION_H

#include "ruleconnective.h"

START_ROW_DECLARATION(RuleDisjunction, RuleConnective)
    DECLARE_ROW_CONSTRUCTORS(RuleDisjunction, Rule)

    bool appliesTo(Row *row);

END_ROW_DECLARATION(RuleDisjunction)

#endif // RULEDISJUNCTION_H
