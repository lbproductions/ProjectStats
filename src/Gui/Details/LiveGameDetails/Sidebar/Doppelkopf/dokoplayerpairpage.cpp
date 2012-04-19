#include "dokoplayerpairpage.h"

#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/player.h>

#include <Gui/Misc/groupbox.h>

#include <QVBoxLayout>

using namespace Gui::Details::LiveGameDetails::Sidebar;

DokoPlayerPairPage::DokoPlayerPairPage(Database::DokoLiveGame* dokolivegame, QWidget* parent):
    SidebarPage(parent),
    m_dokoLiveGame(dokolivegame)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Games/Wins together",this));

    foreach(Database::Player* playerOne, m_dokoLiveGame->players->value()){
        QVBoxLayout* playerLayout = new QVBoxLayout(this);
        foreach(Database::Player* playerTwo, m_dokoLiveGame->players->value()){
            if(playerOne->id() != playerTwo->id()){
                QPair<Database::Player*,Database::Player*> pair;
                pair.first = playerOne;
                pair.second = playerTwo;
                QLabel* label = new QLabel(this);
                m_dokoLiveGame->doko_gamesTogether->mappingFutureWatcher(pair)->connectTo(label);
                QHBoxLayout* internalLayout = new QHBoxLayout(this);
                internalLayout->addWidget(new QLabel(playerOne->name->value() + " - " + playerTwo->name->value(),this));
                internalLayout->addWidget(label);
                QLabel* wins = new QLabel(this);
                m_dokoLiveGame->doko_winsTogether->mappingFutureWatcher(pair)->connectTo(wins);
                internalLayout->addWidget(wins);
                playerLayout->addLayout(internalLayout);
            }
        }
        Gui::Misc::GroupBox* group = new Gui::Misc::GroupBox(playerLayout,this);
        layout->addWidget(group);
    }

    this->setLayout(layout);

    QPalette palette = this->palette();
    QPixmap pixmap;
    pixmap.load(":/graphics/styles/mac/toolbar/fullscreen/sidebar_background_fullscreen");
    palette.setBrush(QPalette::Window,QBrush(pixmap));
    this->setPalette(palette);
    this->setStyleSheet("QLabel{font-size: 15px; color: white;}");
}
