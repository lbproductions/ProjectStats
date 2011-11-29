#ifndef PLAYERCHECKBOX_H
#define PLAYERCHECKBOX_H

#include <QPointer>

#include "checkbox.h"

namespace Database{
    class Player;
}

namespace Gui
{

namespace Misc
{

class PlayerCheckBox : public CheckBox
{
public:
    PlayerCheckBox(Database::Player* player, QWidget *parent = 0);

    Database::Player* player();
private:
    Database::Player* m_player;
};

}}

#endif // PLAYERCHECKBOX_H
