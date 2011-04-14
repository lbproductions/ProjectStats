#include "rule.h"

START_TABLE_IMPLEMENTATION(Rule)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Rule, Rule, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(int,Rule,parentRuleId, tr("Parent rule id"))
}

QString Rule::mimeType() const
{
    return "application/projectstats.rule";
}

bool Rule::appliesTo(::Database::Row* /*row*/)
{
    return false;
}

END_ROW_IMPLEMENTATION()
