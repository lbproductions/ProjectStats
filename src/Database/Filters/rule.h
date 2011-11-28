#ifndef RULE_H
#define RULE_H

#include "../row.h"
#include "../attribute.h"
#include "../databaseattribute.h"
#include "../table.h"

START_ROW_DECLARATION(Rule, Row)
    DECLARE_ROW_CONSTRUCTORS(Rule, Rule)

    enum RuleType {
        RuleConjunctionType,
        RuleDisjunctionType,
        AtomicRuleType,
        EnoughLeaguePlayersRuleType
    };

    virtual bool appliesTo(Row* row);

    template<class Type, class Table>
    QList<Type*> getAll();

    DECLARE_DATABASEATTRIBUTE(int, Rule, parentRuleId)
    DECLARE_DATABASEATTRIBUTE(int, Rule, type)

END_ROW_DECLARATION(Rule)

template<class Type, class Table>
QList<Type*> Database::Rule::getAll()
{
    QList<Type*> all = Table::instance()->allRows();
    QList<Type*> filtered;
    foreach(Type* row, all)
    {
        if(appliesTo(row))
        {
            filtered.append(row);
        }
    }
    return filtered;
}

START_TABLE_DECLARATION(Rule)
    QPointer<Rule> createRowInstance(int id);
END_TABLE_DECLARATION()

#endif // RULE_H
