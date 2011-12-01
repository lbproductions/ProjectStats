#include "place.h"

#include <QImage>

#include <Misc/logger.h>
#include "game.h"
#include "playerplaceassignment.h"
#include "player.h"

#include <Gui/Details/PlaceDetails/placedetailswidget.h>

START_TABLE_IMPLEMENTATION(Place)
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Place, Place, PSRow)
{
    PlaceCalculator* calc = new PlaceCalculator(this,this);

    IMPLEMENT_DATABASEATTRIBUTE(int,Place,plz,tr("PLZ"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Place,ort,tr("Ort"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Place,strasse,tr("Strasse"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Place,nummer,tr("Nr"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Place,comment,tr("Comment"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Place,iconPath,tr("IconPath"))

    IMPLEMENT_LISTATTRIBUTE_IN_CALC(Player*, Place, PlaceCalculator, calc, players,tr("Players"))
    PlayerPlaceAssignments::instance()->rows()->addDependingAttribute(players);

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

QImage Place::calculate_icon(){
    return QImage(iconPath->value());
}

QString Place::calculate_displayString(){
    return strasse->value() + " " + QString::number(nummer->value()) + ", " + ort->value();
}

Gui::Details::DetailsWidget* Place::detailsWidget(){
    return new Gui::Details::PlaceDetailsWidget(this);
}

END_ROW_IMPLEMENTATION()
