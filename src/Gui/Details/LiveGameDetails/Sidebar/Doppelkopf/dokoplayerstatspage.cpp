#include "dokoplayerstatspage.h"

#include <Database/player.h>
#include <Database/Doppelkopf/dokolivegame.h>

#include <Gui/Misc/groupbox.h>

#include "dokoplayerstatsgroupbox.h"

#include <QVBoxLayout>

using namespace Gui::Details::LiveGameDetails::Sidebar;

DokoPlayerStatsPage::DokoPlayerStatsPage(Database::DokoLiveGame *dokolivegame, QWidget *parent):
    SidebarPage(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    foreach(Database::Player* player, dokolivegame->players->value()){
        DokoPlayerStatsGroupBox* box = new DokoPlayerStatsGroupBox(dokolivegame, player,this);
        Gui::Misc::GroupBox* group = new Gui::Misc::GroupBox(box,this);
        layout->addWidget(group);
    }
    this->setLayout(layout);

    this->setStyleSheet("QLabel{color: white;}");
}
