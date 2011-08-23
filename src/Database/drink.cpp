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

    IMPLEMENT_DATABASEATTRIBUTE(QString, Drink, type, tr("Type"))
    IMPLEMENT_DATABASEATTRIBUTE(QString, Drink, name, tr("Name"))
    IMPLEMENT_DATABASEATTRIBUTE(double,Drink,size,tr("Size"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Drink,iconPath,tr("IconPath"))
    IMPLEMENT_DATABASEATTRIBUTE(double,Drink,alc,tr("Vol%"))

    IMPLEMENT_ATTRIBUTE(QImage,Drink,icon,tr("Icon"))
    iconPath->addDependingAttribute(icon);
    icon->setRole(Qt::DecorationRole);

    IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Player*,int,Drink,DrinkCalculator,calc,countPerPlayer,tr("CountPerPlayer"))
    IMPLEMENT_ATTRIBUTE_IN_CALC(int,Drink,DrinkCalculator,calc,drinkCount,"DrinkCount")
    IMPLEMENT_ATTRIBUTE_IN_CALC(QString,Drink,DrinkCalculator,calc,mostDrinks,tr("Most Drinks"))
}

QString Drink::mimeType() const
{
    return "application/projectstats.drink";
}

QImage Drink::calculate_icon()
{
    QImage image(iconPath->value());
    if(!image.isNull())
    {
        return image.scaledToHeight(40);
    }
    return QImage();
}

Gui::Details::DetailsWidget* Drink::detailsWidget(){
    return new Gui::Details::DrinkDetailsWidget(this);
}

END_ROW_IMPLEMENTATION()
