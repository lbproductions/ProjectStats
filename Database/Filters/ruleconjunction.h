#ifndef DATABASE_RULECONJUNCTION_H
#define DATABASE_RULECONJUNCTION_H

#include "ruleconnective.h"
#include "../table.h"
#include "../attribute.h"
#include "../databaseattribute.h"

START_ROW_DECLARATION(RuleConjunction, RuleConnective)
    DECLARE_ROW_CONSTRUCTORS(RuleConjunction, Rule)

    bool appliesTo(::Database::Row *row);

END_ROW_DECLARATION(RuleConjunction)

#endif // DATABASE_RULECONJUNCTION_H
