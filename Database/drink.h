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

    DatabaseAttribute<QString,Drink> name;
    DatabaseAttribute<QString,Drink> type;
    Attribute<QString,Drink> test;
    Attribute<QString,Drink> test2;

    QString calculateTest();
    bool updateTest(AttributeInterface *changedDependency);

    QString calculateTest2();

};

} // namespace Database

#endif // DATABASE_DRINK_H
