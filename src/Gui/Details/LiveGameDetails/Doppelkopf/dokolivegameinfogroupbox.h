#ifndef DOKOLIVEGAMEINFOGROUPBOX_H
#define DOKOLIVEGAMEINFOGROUPBOX_H

#include <Gui/Details/LiveGameDetails/livegameinfogroupbox.h>
#include <Gui/Misc/valuelabel.h>

namespace Database
{
    class DokoLiveGame;
    class AttributeBase;
}

namespace Gui
{

namespace Details
{

namespace LiveGameDetails
{

namespace DokoLiveGameDetails
{

class DokoLiveGameInfoGroupBox : public LiveGameInfoGroupBox
{
public:
    DokoLiveGameInfoGroupBox(Database::DokoLiveGame* dokogame, QWidget *parent = 0);

private:
    Database::DokoLiveGame* m_dokogame;
};

}
}
}
}

#endif // DOKOLIVEGAMEINFOGROUPBOX_H
