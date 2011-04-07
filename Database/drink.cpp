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
    test.setUpdateFunction(&Drink::updateTestIfPossible);
    name.addDependingAttribute(&test);
    type.addDependingAttribute(&test);

    test2.setCalculationFunction(&Drink::calculateTest2);
    test.addDependingAttribute(&test2);
    type.addDependingAttribute(&test2);
}

QString Drink::calculateTest()
{
    QWaitCondition sleep;
    QMutex m;
    sleep.wait(&m,1000);
    return "Name: " + name() + "; Type: " + type();
}

QFuture<QString> Drink::updateTestIfPossible(AttributeInterface *changedDependency)
{
    if(changedDependency->name() == "name")
    {
        return QtConcurrent::run(this, &Drink::updateTest, changedDependency);
    }

    return QFuture<QString>();
}

QString Drink::updateTest(AttributeInterface *changedDependency)
{
    if(changedDependency->name() == "name")
    {
        return "Name: " + name() + "; Type: " + type();
    }

    return "";
}

QString Drink::calculateTest2()
{
    qDebug() << "calculateTest2";
    QWaitCondition sleep;
    QMutex m;
    sleep.wait(&m,800);
    return "Test: " + test() + "; Type: " + type();
}

} // namespace Database
