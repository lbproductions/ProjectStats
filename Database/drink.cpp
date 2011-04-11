#include "drink.h"

#include <QWaitCondition>
#include <QIcon>

START_TABLE_IMPLEMENTATION(Drink)
END_ROW_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Drink, Drink, Row)
{
    IMPLEMENT_ATTRIBUTE_WITH_UPDATEFUNCTION(QString, Drink, test, "test")
    IMPLEMENT_ATTRIBUTE(QString,Drink,test2, "test2")
    IMPLEMENT_ATTRIBUTE(QList<Drink*>,Drink,drinks, "drinks")
    IMPLEMENT_DATABASEATTRIBUTE(QString, Drink, type, "Type")
    IMPLEMENT_DATABASEATTRIBUTE(QString, Drink, name, "Name")
    IMPLEMENT_DATABASEATTRIBUTE(double,Drink,size,"Size")
    IMPLEMENT_DATABASEATTRIBUTE(QIcon,Drink,icon,"Icon")
    icon->setRole(Qt::DecorationRole);
    IMPLEMENT_DATABASEATTRIBUTE(double,Drink,alc,"Vol%")

    name->addDependingAttribute(test);
    type->addDependingAttribute(test);

    test->addDependingAttribute(test2);
    type->addDependingAttribute(test2);
    test2->setUpdateFunction(test, &Drink::update_test2_test);
}

QString Drink::mimeType() const
{
    return "application/projectstats.drink";
}

QString Drink::calculate_test()
{
    QWaitCondition sleep;
    QMutex m;
    sleep.wait(&m,1000);
    return "Name: " + name->value() + "; Type: " + type->value();
}

QFuture<QString> Drink::updateIfPossible_test(AttributeBase *changedDependency)
{
    if(changedDependency->name() == "name")
    {
        return QtConcurrent::run(this, &Drink::update_test, changedDependency);
    }

    return QFuture<QString>();
}

QString Drink::update_test(AttributeBase *changedDependency)
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
