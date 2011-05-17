#include "place.h"

#include <QImage>

#include <Logger/logger.h>
#include "game.h"

START_TABLE_IMPLEMENTATION(Place)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Place, Place, Row)
{
    PlaceCalculator* calc = new PlaceCalculator(this,this);

    IMPLEMENT_DATABASEATTRIBUTE(int,Place,playerId,tr("PlayerId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Place,plz,tr("PLZ"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Place,ort,tr("Ort"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Place,strasse,tr("Strasse"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Place,nummer,tr("Nr"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Place,comment,tr("Comment"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Place,iconPath,tr("IconPath"))

    IMPLEMENT_ATTRIBUTE(QPointer<Player>, Place, player,tr("Player"))
    playerId->addDependingAttribute(player);

    IMPLEMENT_ATTRIBUTE(QImage,Place,icon,tr("Icon"))
    iconPath->addDependingAttribute(icon);
    icon->setRole(Qt::DecorationRole);

    IMPLEMENT_ATTRIBUTE_IN_CALC(int,Place,PlaceCalculator,calc,gameCount,"GameCount")
    Games::instance()->rows()->addDependingAttribute(gameCount);

    IMPLEMENT_ATTRIBUTE(QString,Place,displayString,"Place")
    strasse->addDependingAttribute(displayString);
    nummer->addDependingAttribute(displayString);
    ort->addDependingAttribute(displayString);
}

QString Place::mimeType() const
{
    return "application/projectstats.place";
}

QPointer<Player> Place::calculate_player()
{
    return Players::instance()->rowById(this->playerId->value());
}

QImage Place::calculate_icon(){
    return QImage(iconPath->value());
}

QString Place::calculate_displayString(){
    return strasse->value() + " " + QString::number(nummer->value()) + ", " + ort->value();
}

END_ROW_IMPLEMENTATION()
