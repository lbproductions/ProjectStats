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
    m_livegame = livegame;
    m_playerlist = m_livegame->playersSortedByPosition->value();

    m_layout = new QVBoxLayout(this);
    this->setLayout(m_layout);

    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);

    this->setAutoFillBackground(true);

    m_defaultpalette = this->palette();
}

void BeerWidget::updateWidget(){

    while (m_layout->count() > 0)
    {
        if (m_layout->itemAt(0)->widget() != 0){
            m_layout->itemAt(0)->widget()->setVisible(false);
        }
        m_layout->removeItem(m_layout->itemAt(0));
    }

    for (int i = 0; i<m_playerlist.size();i++){
        m_layout->addStretch();
        //m_layout->addWidget(new BeerPlayerWidget(m_playerlist.at(i),m_livegame->drinks->value(m_playerlist.at(i)),m_livegame, this));
        if(m_isFullscreen){
            setFullscreen();
        }
        m_layout->addStretch();
    }

}

void BeerWidget::setFullscreen(){
    QPalette palette = this->palette();
    QPixmap pixmap;
    pixmap.load(":/graphics/styles/mac/toolbar/fullscreen/sidebar_background_fullscreen");
    palette.setBrush(QPalette::Window,QBrush(pixmap));
    this->setPalette(palette);

    for (int i = 0; i<m_layout->count();i++){
        if (m_layout->itemAt(i)->widget() != 0){
            static_cast<BeerPlayerWidget*>(m_layout->itemAt(i)->widget())->setFullscreen();
        }
    }
    m_isFullscreen = true;
}

void BeerWidget::setNormalMode(){
    this->setPalette(m_defaultpalette);

    for (int i = 0; i<m_layout->count();i= i+2){
        if (m_layout->itemAt(i)->widget() != 0){
            static_cast<BeerPlayerWidget*>(m_layout->itemAt(i)->widget())->setNormalMode();
        }
    }
    m_isFullscreen = false;
}

