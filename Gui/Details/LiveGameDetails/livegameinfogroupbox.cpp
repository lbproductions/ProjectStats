#include "livegameinfogroupbox.h"

#include <Database/livegame.h>

#include <Gui/Misc/valuelabel.h>
#include <Gui/Misc/headerlabel.h>

#include <QVBoxLayout>

using namespace Gui::Details::LiveGameDetails;


LiveGameInfoGroupBox::LiveGameInfoGroupBox(Database::LiveGame* livegame, QWidget* parent) :
    AbstractLiveGameWidget(parent),
    m_game(livegame)
{    
    m_layout = new QVBoxLayout(this);

    m_layout->addWidget(new Misc::HeaderLabel(tr("Type"),this));
    Misc::ValueLabel* typeLabel = new Misc::ValueLabel("-",this);
    m_game->type->futureWatcher()->connectTo(typeLabel);
    m_layout->addWidget(typeLabel);

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
}
