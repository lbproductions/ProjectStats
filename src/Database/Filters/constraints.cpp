#include "constraints.h"

#include <QDate>

using namespace Database;

bool Constraints::appliesTo(const QVariant &value, Database::Constraints::Constraint constraint, const QVariant &parameter)
{
    switch(constraint)
    {
    case DateIsBefore:
        return value.toDate() < parameter.toDate();
    case DateIsAfter:
        return value.toDate() > parameter.toDate();
    case DateIsEqual:
        return value.toDate() == parameter.toDate();
    case StringIsEqual:
        return value.toString() == parameter.toString();
    case IsEqual:
        return value == parameter;
    default:
        return false;
    }
}
