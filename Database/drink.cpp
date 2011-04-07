#include "drink.h"

#include <QWaitCondition>

IMPLEMENT_TABLE(Drink)

START_ROW_IMPLEMENTATION(Drink)
{
    IMPLEMENT_ATTRIBUTE_WITH_UPDATEFUNCTION(QString, Drink, test)
    IMPLEMENT_ATTRIBUTE(QString,Drink,test2)
    IMPLEMENT_ATTRIBUTE(QList<Drink*>,Drink,drinks)
    IMPLEMENT_DATABASEATTRIBUTE(QString, Drink, type)
    IMPLEMENT_DATABASEATTRIBUTE(QString, Drink, name)

    name->addDependingAttribute(test);
    type->addDependingAttribute(test);

    test->addDependingAttribute(test2);
    type->addDependingAttribute(test2);
    test2->setUpdateFunction(test, &Drink::update_test2_test);
}

QString Drink::calculate_test()
{
    QWaitCondition sleep;
    QMutex m;
    sleep.wait(&m,1000);
    return "Name: " + name->value() + "; Type: " + type->value();
}

QFuture<QString> Drink::updateIfPossible_test(AttributeInterface *changedDependency)
{
    if(changedDependency->name() == "name")
    {
        return QtConcurrent::run(this, &Drink::update_test, changedDependency);
    }

    return QFuture<QString>();
}

QString Drink::update_test(AttributeInterface *changedDependency)
{
    if(changedDependency->name() == "name")
    {
        return "Name: " + name->value() + "; Type: " + type->value();
    }

    return "";
}

QString Drink::calculate_test2()
{
    QWaitCondition sleep;
    QMutex m;
    sleep.wait(&m,800);
    return "Test: " + test->value() + "; Type: " + type->value();
}

QString Drink::update_test2_test()
{
    return "Name: " + test->value() + "; Type: " + type->value();
}

QList<Drink*> Drink::calculate_drinks()
{
    return Drinks::instance()->allRows();
}

END_ROW_IMPLEMENTATION()
