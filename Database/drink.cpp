#include "drink.h"

#include <QWaitCondition>
#include <QImage>

#include <Database/Calculator/drinkcalculator.h>
#include <Database/livegame.h>

#include <Gui/Details/DrinkDetails/DrinkDetailsWidget.h>

START_TABLE_IMPLEMENTATION(Drink)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Drink, Drink, Row)
{
    DrinkCalculator* calc = new DrinkCalculator(this,this);

    IMPLEMENT_ATTRIBUTE_WITH_UPDATEFUNCTION(QString, Drink, test, tr("test"))
    IMPLEMENT_ATTRIBUTE(QString,Drink,test2, tr("test2"))
    IMPLEMENT_DATABASEATTRIBUTE(QString, Drink, type, tr("Type"))
    IMPLEMENT_DATABASEATTRIBUTE(QString, Drink, name, tr("Name"))
    IMPLEMENT_DATABASEATTRIBUTE(double,Drink,size,tr("Size"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Drink,iconPath,tr("IconPath"))
    IMPLEMENT_DATABASEATTRIBUTE(double,Drink,alc,tr("Vol%"))

    name->addDependingAttribute(test);
    type->addDependingAttribute(test);

    test->addDependingAttribute(test2);
    type->addDependingAttribute(test2);
    test2->setUpdateFunction(test, &Drink::update_test2_test);

    IMPLEMENT_ATTRIBUTE(QImage,Drink,icon,tr("Icon"))
    iconPath->addDependingAttribute(icon);
    icon->setRole(Qt::DecorationRole);

    IMPLEMENT_ATTRIBUTE_IN_CALC(int,Drink,DrinkCalculator,calc,drinkCount,"DrinkCount")
}

QString Drink::mimeType() const
{
    return "application/projectstats.drink";
}

QString Drink::calculate_test()
{
    //QWaitCondition sleep;
    //QMutex m;
    //sleep.wait(&m,1000);
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
    //QWaitCondition sleep;
    //QMutex m;
    //sleep.wait(&m,800);
    return "Test: " + test->value() + "; Type: " + type->value();
}

QString Drink::update_test2_test()
{
    return "Name: " + test->value() + "; Type: " + type->value();
}

QImage Drink::calculate_icon(){
    return QImage(iconPath->value()).scaledToHeight(40);
}

Gui::Details::DetailsWidget* Drink::detailsWidget(){
    return new Gui::Details::DrinkDetailsWidget(this);
}

END_ROW_IMPLEMENTATION()
