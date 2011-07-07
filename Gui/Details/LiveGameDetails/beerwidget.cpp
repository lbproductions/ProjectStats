#include "beerwidget.h"

#include "beerplayerwidget.h"

#include <Database/livegame.h>
#include <Database/player.h>
#include <Database/drink.h>

#include <QGridLayout>
#include <QLabel>

using namespace Gui::Details::LiveGameDetails;

BeerWidget::BeerWidget(Database::LiveGame* livegame, QWidget *parent) :
    QGroupBox(parent)
{
    m_livegame = livegame;
    m_playerlist = m_livegame->playersSortedByPosition->value();

    m_layout = new QVBoxLayout(this);
    this->setLayout(m_layout);
    this->setTitle(tr("BeerCounter"));

    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
}

void BeerWidget::updateWidget(){
    while (m_layout->count() > 0)
    {
	m_layout->itemAt(0)->widget()->setVisible(false);
	m_layout->removeItem(m_layout->itemAt(0));
    }

    for (int i = 0; i<m_playerlist.size();i++){
        //m_layout->addWidget(new BeerPlayerWidget(m_playerlist.at(i),m_livegame->drinks->value(m_playerlist.at(i)),m_livegame,this));
    }
}


