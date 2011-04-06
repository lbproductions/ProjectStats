#include "drink.h"

#include "drinks.h"

#include <QWaitCondition>

namespace Database {

Drink::Drink(int id, Table<Drink> *table) :
    Row(id,table),
    name("name",this),
    type("type",this),
    test("test",this),
    test2("test2",this)
{
    registerAttribute(name);
    registerAttribute(type);
    registerAttribute(test);
    registerAttribute(test2);

    test.setCalculationFunction(&Drink::calculateTest);
    test.setUpdateFunction(&Drink::updateTest);
    name.addDependingAttribute(&test);
    type.addDependingAttribute(&test);

    test2.setCalculationFunction(&Drink::calculateTest2);
    test.addDependingAttribute(&test2);
}

QString Drink::calculateTest()
{
    QWaitCondition sleep;
    QMutex m;
    sleep.wait(&m,2500);
    return "Name: " + name() + "; Type: " + type();
}

bool Drink::updateTest(AttributeInterface *changedDependency)
{
    if(changedDependency->name() == "name")
    {
        test.setValue("Name: " + name() + "; Type: " + type());
        return true;
    }

    return false;
}

QString Drink::calculateTest2()
{
    QWaitCondition sleep;
    QMutex m;
    sleep.wait(&m,1500);
    return "Test: " + test() + "; Type: " + type();
}

} // namespace Database
