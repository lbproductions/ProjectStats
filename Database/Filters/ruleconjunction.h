#ifndef RULECONJUNCTION_H
#define RULECONJUNCTION_H

#include "ruleconnective.h"

START_ROW_DECLARATION(RuleConjunction, RuleConnective)
    DECLARE_ROW_CONSTRUCTORS(RuleConjunction, Rule)

    bool appliesTo(Row *row);

END_ROW_DECLARATION(RuleConjunction)

#endif // RULECONJUNCTION_H
