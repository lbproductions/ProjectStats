#include "skatlivegamerowwindow.h"

#include <Database/Skat/skatlivegame.h>
#include <Gui/Details/LiveGameDetails/Skat/skatlivegamedetailswidget.h>

using namespace Gui::Details;

SkatLiveGameRowWindow::SkatLiveGameRowWindow(Database::Skat::SkatLiveGame* skatgame, QWidget *parent):
    LiveGameRowWindow(skatgame,parent)
{
    m_liveGameDetailsWidget = new SkatLiveGameDetailsWidget(skatgame,this);

    m_livegame = skatgame;
    m_skatlivegame = skatgame;

    this->setCentralWidget(m_liveGameDetailsWidget);

    setupToolBar();
    this->fillWidget();
}
