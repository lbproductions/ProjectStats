#ifndef RULE_H
#define RULE_H

#include "../row.h"
#include "../attribute.h"
#include "../databaseattribute.h"
#include "../table.h"

START_ROW_DECLARATION(Rule, Row)
    DECLARE_ROW_CONSTRUCTORS(Rule, Rule)

//    enum RuleType {
//        RuleConjunctionType,
//        RuleDisjunctionType,
//        AtomicRuleType,
//        EnoughLeaguePlayersRuleType
//    };

    virtual bool appliesTo(Row* row);

    DECLARE_DATABASEATTRIBUTE(int, Rule, parentRuleId)
    DECLARE_DATABASEATTRIBUTE(int, Rule, type)

END_ROW_DECLARATION(Rule)

START_TABLE_DECLARATION(Rule)
//    QPointer<Rule> createRowInstance(int id);
END_TABLE_DECLARATION()

#endif // RULE_H
