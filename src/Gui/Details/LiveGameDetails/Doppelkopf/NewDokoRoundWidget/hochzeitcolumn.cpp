#include "hochzeitcolumn.h"

#include <Gui/Misc/playercheckbox.h>

#include <Database/player.h>

using namespace Gui::Details::LiveGameDetails::DokoLiveGameDetails;

HochzeitColumn::HochzeitColumn(Database::DokoLiveGame* game, QGridLayout* layout, int minRow, int column, QObject* parent):
    Column(game,layout,minRow,column,parent)
{
}

void HochzeitColumn::update(Misc::CheckBox *check, bool checked){
    Misc::PlayerCheckBox* checkBox = static_cast<Misc::PlayerCheckBox*>(check);
    if(checked){
        m_hochzeitPlayer = checkBox->player();
        foreach(Misc::PlayerCheckBox* box, m_checkBoxes.values()){
            if(box->player() != m_hochzeitPlayer){
                box->setEnabled(false);
            }
        }
    }
    else{
        foreach(Misc::PlayerCheckBox* box, m_checkBoxes.values()){
          box->setEnabled(true);
        }
    }
    emit hochzeitPlayerChanged(m_hochzeitPlayer,checked);
    if(!checked){
        m_hochzeitPlayer = 0;
    }
}

void HochzeitColumn::onRePlayersChanged(QMap<Database::Player*,bool> map, int reCount){
    if(reCount == 2){
        foreach(Misc::PlayerCheckBox* box, m_checkBoxes.values()){
            if(!map.value(box->player())){
                box->setEnabled(false);
            }
        }
    }
    else{
        foreach(Misc::PlayerCheckBox* box, m_checkBoxes.values()){
            box->setEnabled(true);
        }
    }
}

void HochzeitColumn::hochzeitPlayerChanged(Database::Player* player, bool hochzeit){

}
