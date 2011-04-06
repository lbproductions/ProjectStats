#ifndef DATABASE_DRINK_H
#define DATABASE_DRINK_H

#include "row.h"

#include "databaseattribute.h"

namespace Database {

template<class RowType>
class Table;

class Drink : public Row
{
public:
    Drink(int id, Table<Drink> *table);

    DatabaseAttribute<QString> name;
};

} // namespace Database

#endif // DATABASE_DRINK_H
