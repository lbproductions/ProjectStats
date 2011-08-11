#ifndef ATOMICRULE_H
#define ATOMICRULE_H

#include "rule.h"

#include <QString>

START_ROW_DECLARATION(AtomicRule, Rule)
    DECLARE_ROW_CONSTRUCTORS(AtomicRule, Rule)

    DECLARE_DATABASEATTRIBUTE(QString, AtomicRule, attributeName)
    DECLARE_DATABASEATTRIBUTE(int, AtomicRule, constraintId)
    DECLARE_DATABASEATTRIBUTE(QString, AtomicRule, parameter)

    bool appliesTo(Row* row);
END_ROW_DECLARATION(AtomicRule)

#endif // ATOMICRULE_H
