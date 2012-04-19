#ifndef DOKOPLAYERPAIRPAGE_H
#define DOKOPLAYERPAIRPAGE_H

#include <Gui/Details/LiveGameDetails/Sidebar/sidebarpage.h>

namespace Database{
    class DokoLiveGame;
}

namespace Gui{

namespace Details{

namespace LiveGameDetails{

namespace Sidebar{

class DokoPlayerPairPage : public SidebarPage
{
public:
    DokoPlayerPairPage(Database::DokoLiveGame* dokolivegame, QWidget* parent = 0);

private:
    Database::DokoLiveGame* m_dokoLiveGame;
};

}}}}
#endif // DOKOPLAYERPAIRPAGE_H
