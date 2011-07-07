#include "livegameinfogroupbox.h"

#include <Database/livegame.h>
#include <Database/player.h>
#include <Database/round.h>

#include <Gui/Misc/valuelabel.h>
#include <Gui/Misc/headerlabel.h>

#include <QDebug>

using namespace Gui::Details::LiveGameDetails;


LiveGameInfoGroupBox::LiveGameInfoGroupBox(Database::LiveGame* livegame, QWidget* parent) :
    QGroupBox(parent),
    m_game(livegame)
{    
    m_layout = new QVBoxLayout(this);

    m_layout->addWidget(new Misc::HeaderLabel(tr("Type"),this));
    m_layout->addWidget(new Misc::ValueLabel(m_game->type->value(),this));

    m_layout->addWidget(new Misc::HeaderLabel(tr("Length"),this));
    m_layout->addWidget(new Misc::ValueLabel(/*QString::number(timeGame.elapsed())*/ "-",this));

    m_layout->addWidget(new Misc::HeaderLabel(tr("CardMixer"),this));
    Database::Player *cardMixer = m_game->cardmixer->value();
    if(cardMixer != 0)
    {
        m_layout->addWidget(new Misc::ValueLabel(cardMixer->name->value(),this));
    }

    if (m_game->isFinished->value()){
        m_layout->addWidget(new Misc::HeaderLabel(tr("RoundCount"),this));
        m_layout->addWidget(new Misc::ValueLabel(QString::number(m_game->rounds->value().size()),this));
    }
    else{
        m_layout->addWidget(new Misc::HeaderLabel(tr("RoundCount"),this));
        m_layout->addWidget(new Misc::ValueLabel(QString::number(m_game->rounds->value().size()-1),this));
    }

    this->setLayout(m_layout);

    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
}

void LiveGameInfoGroupBox::updateWidget(QString lengthText){
    QLabel* label = static_cast<QLabel*>(m_layout->itemAt(3)->widget());
    label->setText(lengthText);

    label = static_cast<QLabel*>(m_layout->itemAt(5)->widget());
    label->setText(m_game->cardmixer->value()->name->value());

    label = static_cast<QLabel*>(m_layout->itemAt(7)->widget());
    if (m_game->isFinished->value()){
        label->setText(QString::number(m_game->rounds->value().size()));
    }
    else{
        label->setText(QString::number(m_game->rounds->value().size()-1));
    }
}