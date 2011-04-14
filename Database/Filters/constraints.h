#ifndef DATABASE_CONSTRAINTS_H
#define DATABASE_CONSTRAINTS_H

#include <QVariant>

namespace Database {

class Constraints
{
public:
    enum Constraint {
        DateIsBefore,
        DateIsAfter,
        DateIsEqual
    };

    Constraints();

    static bool appliesTo(const QVariant& value, Constraint constraint, const QVariant& parameter);
};

} // namespace Database

#endif // DATABASE_CONSTRAINTS_H
