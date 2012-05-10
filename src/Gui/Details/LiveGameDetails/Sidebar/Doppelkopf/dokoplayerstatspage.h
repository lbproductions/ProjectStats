#ifndef DOKOPLAYERSTATSPAGE_H
#define DOKOPLAYERSTATSPAGE_H

#include "../sidebarpage.h"

namespace Database{
    class DokoLiveGame;
}

namespace Gui{

namespace Details{

namespace LiveGameDetails{

namespace Sidebar{

class DokoPlayerStatsPage : public SidebarPage
{
public:
    DokoPlayerStatsPage(Database::DokoLiveGame* dokolivegame, QWidget* parent = 0);
};

}}}}

#endif // DOKOPLAYERSTATSPAGE_H
