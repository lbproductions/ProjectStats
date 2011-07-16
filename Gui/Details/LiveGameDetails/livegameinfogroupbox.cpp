#include "livegameinfogroupbox.h"

#include <Database/livegame.h>

#include <Gui/Misc/valuelabel.h>
#include <Gui/Misc/headerlabel.h>

#include <QVBoxLayout>
#include <QTimer>
#include <QDateTime>

using namespace Gui::Details::LiveGameDetails;


LiveGameInfoGroupBox::LiveGameInfoGroupBox(Database::LiveGame* livegame, QWidget* parent) :
    AbstractLiveGameWidget(parent),
    m_game(livegame)
{    
    m_layout = new QVBoxLayout(this);

    m_typeHeaderLabel = new Misc::HeaderLabel(tr("Type"),this);
    m_layout->addWidget(m_typeHeaderLabel);
    m_typeLabel = new Misc::ValueLabel("-",this);
    m_game->type->futureWatcher()->connectTo(m_typeLabel);
    m_layout->addWidget(m_typeLabel);

    m_timeHeaderLabel = new Misc::HeaderLabel(tr("Current Time"),this);
    m_layout->addWidget(m_timeHeaderLabel);
    m_timeLabel = new Misc::ValueLabel(QTime::currentTime().toString(),this);
    m_layout->addWidget(m_timeLabel);

    m_layout->addWidget(new Misc::HeaderLabel(tr("Length"),this));
    Misc::ValueLabel* lengthLabel = new Misc::ValueLabel("-",this);
    m_game->length->futureWatcher()->connectTo(lengthLabel);
    m_layout->addWidget(lengthLabel);

    m_layout->addWidget(new Misc::HeaderLabel(tr("Dealer"),this));
    Misc::ValueLabel* cardmixerLabel = new Misc::ValueLabel("-",this);
    m_game->cardmixer->futureWatcher()->connectTo(cardmixerLabel);
    m_layout->addWidget(cardmixerLabel);

    m_layout->addWidget(new Misc::HeaderLabel(tr("RoundCount"),this));
    Misc::ValueLabel* roundCountLabel = new Misc::ValueLabel("-",this);
    m_game->roundCount->futureWatcher()->connectTo(roundCountLabel);
    m_layout->addWidget(roundCountLabel);

    this->setLayout(m_layout);

    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    this->setAutoFillBackground(true);

    QPalette palette = this->palette();
    QPixmap pixmap;
    pixmap.load(":/graphics/styles/mac/toolbar/fullscreen/sidebar_background_fullscreen");
    palette.setBrush(QPalette::Window,QBrush(pixmap));
    this->setPalette(palette);
    this->setStyleSheet(QString("Gui--Misc--HeaderLabel{font-size: 20px; font-style: italic; color: rgb(200,200,200);}")+
                "Gui--Misc--ValueLabel{font-size: 40px; color: white;}");

    connect(livegame->state,SIGNAL(changed()),this,SLOT(reflectState()));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start(1000);

    reflectState();
}

void LiveGameInfoGroupBox::reflectState()
{
    m_typeHeaderLabel->setVisible(false);
    m_typeLabel->setVisible(false);
    m_timeHeaderLabel->setVisible(false);
    m_timeLabel->setVisible(false);

    switch(m_game->state->value())
    {
    case Database::Round::FinishedState:
        m_typeHeaderLabel->setVisible(true);
        m_typeLabel->setVisible(true);
        break;

    case Database::Round::PausedState:
    case Database::Round::RunningState:
        m_timeHeaderLabel->setVisible(true);
        m_timeLabel->setVisible(true);
        break;

    default:
        break;
    }
}

void LiveGameInfoGroupBox::updateTime()
{
    m_timeLabel->setText(QTime::currentTime().toString());
}
