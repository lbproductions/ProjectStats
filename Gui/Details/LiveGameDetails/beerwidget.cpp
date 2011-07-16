#include "beerwidget.h"

#include "beerplayerwidget.h"

#include <Database/livegame.h>
#include <Database/player.h>
#include <Database/drink.h>

#include <QGridLayout>
#include <QLabel>

using namespace Gui::Details::LiveGameDetails;

BeerWidget::BeerWidget(Database::LiveGame* livegame, QWidget *parent) :
    AbstractLiveGameWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    this->setLayout(layout);

    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);

    this->setAutoFillBackground(true);

    QPalette palette = this->palette();
    QPixmap pixmap;
    pixmap.load(":/graphics/styles/mac/toolbar/fullscreen/sidebar_background_fullscreen");
    palette.setBrush(QPalette::Window,QBrush(pixmap));
    this->setPalette(palette);

    foreach(Database::Player* p, livegame->playersSortedByPosition->value())
    {
        layout->addStretch();
        layout->addWidget(new BeerPlayerWidget(p,livegame,this));
        layout->addStretch();
    }
}
