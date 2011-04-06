#include "drink.h"

#include "drinks.h"

namespace Database {

Drink::Drink(int id, Table<Drink> *table) :
    Row(id,table),
    name("name",this),
    type("type",this),
    test("test",this)
{
    test.setCalculationFunction(&Drink::calculateTest);
    name.addDependingAttribute(&test);
    type.addDependingAttribute(&test);
}

QString Drink::calculateTest()
{
    return name() + type();
}

} // namespace Database
