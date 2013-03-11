#include "drink.h"

#include <QWaitCondition>
#include <QImage>

#include <Database/Calculator/drinkcalculator.h>
#include <Database/livegame.h>

#include <Gui/Details/DrinkDetails/DrinkDetailsWidget.h>

namespace Database {
IMPLEMENT_SINGLETON( Drinks )
Drinks::Drinks() :
    Table<Drink>(QString("drinks"))
{
    types = new ListAttribute<QString,Drinks, Drinks>("types",tr("Types"), this);
    types->setCalculationFunction(this,&Drinks::calculate_types);
    this->rows()->addDependingAttribute(types);

    drinksOfType = new MappingAttribute<QString,QList<Drink*>,Drinks,Drinks>("drinksOfType",tr("DrinksOfType"),this);
    drinksOfType->setCalculationFunction(this,&Drinks::calculate_drinksOfType);
    this->rows()->addDependingAttribute(drinksOfType);
}
REGISTER_TABLE(Drinks)

QList<QString> Drinks::calculate_types(){
    QList<QString> list;
    foreach(Drink* g, Drinks::instance()->allRows()){
        if(!list.contains(g->type->value())){
            list.append(g->type->value());
        }
    }
    return list;
}

QMap<QString,QList<Drink*> > Drinks::calculate_drinksOfType(){
    QMap<QString,QList<Drink*> > map;
    foreach(QString type, Drinks::instance()->types->value()){
        QList<Drink*> list;
        foreach(Drink* g, Drinks::instance()->allRows()){
            if(g->type->value() == type){
                list.append(g);
            }
        }
        map.insert(type,list);
    }
    return map;
}

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
    QString path = iconPath->value();
    if(path.isEmpty())
        return QImage();

    QImage image(path);
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
