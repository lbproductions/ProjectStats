#ifndef DATABASE_RULE_H
#define DATABASE_RULE_H

#include "../row.h"
#include "../attribute.h"
#include "../databaseattribute.h"
#include "../table.h"

START_ROW_DECLARATION(Rule, Row)
    DECLARE_ROW_CONSTRUCTORS(Rule, Rule)

    virtual bool appliesTo(::Database::Row* row);

private:
    DECLARE_DATABASEATTRIBUTE(int, Rule, parentRuleId)

END_ROW_DECLARATION(Rule)

START_TABLE_DECLARATION(Rule)
END_TABLE_DECLARATION()

#endif // DATABASE_RULE_H
