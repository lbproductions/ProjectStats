#include "column.h"

#include <QVBoxLayout>
#include <QDebug>

#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/Doppelkopf/dokoround.h>
#include <Database/player.h>

#include <Gui/Misc/playercheckbox.h>

using namespace Gui::Details::LiveGameDetails::DokoLiveGameDetails;

Column::Column(Database::DokoLiveGame* game, QGridLayout* layout, int minRow, int column, QObject* parent):
    m_dokoLiveGame(game)
{
    int row = minRow;
    foreach(Database::Player* player, m_dokoLiveGame->currentRound->value()->currentPlayingPlayers->value()){
        Misc::PlayerCheckBox* checkBox = new Misc::PlayerCheckBox(player);
        m_checkBoxes.insert(player,checkBox);
        layout->addWidget(checkBox,row,column);
        connect(checkBox,SIGNAL(checkStateChanged(Misc::CheckBox*,bool)),this,SLOT(update(Misc::CheckBox*,bool)));
        row++;
    }

    this->setParent(parent);
}

void Column::update(Misc::CheckBox* check ,bool checked){
}
