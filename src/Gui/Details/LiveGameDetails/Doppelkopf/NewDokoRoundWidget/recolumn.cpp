#include "recolumn.h"

#include <QDebug>

#include <Gui/Misc/playercheckbox.h>
#include <Database/player.h>

using namespace Gui::Details::LiveGameDetails::DokoLiveGameDetails;

ReColumn::ReColumn(Database::DokoLiveGame* game, QGridLayout* layout, int minRow, int column, QObject* parent):
    Column(game,layout,minRow,column,parent),
    m_reCount(0)
{
}

void ReColumn::update(Misc::CheckBox* check ,bool checked){
    Misc::PlayerCheckBox* checkBox = static_cast<Misc::PlayerCheckBox*>(check);
    if(checked){
        m_reCount++;
        m_reMap.insert(checkBox->player(),true);
        if(m_reCount == 2){
            qDebug() << m_checkBoxes.values();
            foreach(Misc::PlayerCheckBox* box, m_checkBoxes.values()){
                if(!m_reMap.value(box->player())){
                    box->setEnabled(false);
                }
            }
        }
    }
    else{
        m_reCount--;
        m_reMap.insert(checkBox->player(),false);
        foreach(Misc::PlayerCheckBox* box, m_checkBoxes.values()){
            if(!m_reMap.value(box->player())){
                box->setEnabled(true);
            }
        }
    }
    emit rePlayersChanged(m_reMap,m_reCount);
}

QList<Database::Player*> ReColumn::rePlayers(){
    QList<Database::Player*> list;
    foreach(Database::Player* player, m_reMap.keys()){
        if(m_reMap.value(player)){
            list.append(player);
        }
    }
    return list;
}

void ReColumn::onHochzeitPlayerChanged(Database::Player* player, bool hochzeit){
    if(hochzeit){
        m_reMap.insert(player,true);
        m_checkBoxes.value(player)->setChecked(true);
        m_checkBoxes.value(player)->setEnabled(false);
    }
    else{
        m_checkBoxes.value(player)->setEnabled(true);
    }
}

void ReColumn::rePlayersChanged(QMap<Database::Player*,bool> map, int reCount){

}
