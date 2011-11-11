#include "playercheckbox.h"

#include <Database/player.h>

using namespace Gui::Misc;

PlayerCheckBox::PlayerCheckBox(Database::Player* player, QWidget* parent):
    CheckBox(player->name->value(),parent),
    m_player(player)
{
}

QPointer<Database::Player> PlayerCheckBox::player(){
    return m_player;
}
