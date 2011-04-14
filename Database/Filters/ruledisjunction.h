#ifndef DATABASE_RULEDISJUNCTION_H
#define DATABASE_RULEDISJUNCTION_H

#include "ruleconnective.h"

START_ROW_DECLARATION(RuleDisjunction, RuleConnective)
    DECLARE_ROW_CONSTRUCTORS(RuleDisjunction, Rule)

    bool appliesTo(::Database::Row *row);

END_ROW_DECLARATION(RuleDisjunction)

#endif // DATABASE_RULEDISJUNCTION_H
