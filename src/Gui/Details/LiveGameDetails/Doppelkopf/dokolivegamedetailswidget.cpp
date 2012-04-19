#include "dokolivegamedetailswidget.h"

#include "dokolivegameplayerstatswidget.h"
#include "dokolivegameinfogroupbox.h"
#include "dokolivegameroundtable.h"

#include <Database/Doppelkopf/dokolivegame.h>
#include <Gui/Details/LiveGameDetails/Doppelkopf/schmeissereiwidget.h>
#include <Gui/Details/LiveGameDetails/Doppelkopf/dokolivegameinfogroupbox.h>
#include <Gui/Details/LiveGameDetails/Doppelkopf/dokolivegameplayerstatswidget.h>
#include <Gui/Details/LiveGameDetails/Doppelkopf/dokolivegameroundtable.h>
#include <Gui/Details/LiveGameDetails/Doppelkopf/newdokoroundwidget.h>
#include <Gui/Graphs/dokolivegamegraphview.h>

#include <QFile>
#include <QLabel>
#include <QSettings>
#include <QDebug>


using namespace Gui::Details;

DokoLiveGameDetailsWidget::DokoLiveGameDetailsWidget(Database::DokoLiveGame *game, QWidget *parent) :
    LiveGameDetailsWidget(game,parent),
    m_dokolivegame(game)
{
    initializeItems();
    setupWidget();
}

DokoLiveGameDetailsWidget::~DokoLiveGameDetailsWidget()
{

}

void DokoLiveGameDetailsWidget::initializeItems(){
    m_roundTable = new LiveGameDetails::DokoLiveGameDetails::DokoLiveGameRoundTable(m_dokolivegame,this);

    if(m_graph.isNull())
    {
        m_graph = new Gui::Graphs::DokoLiveGameGraphView(this);
        m_graph->setLiveGame(m_livegame);
        m_graph->setFullscreen();
    }
    else
    {
        m_graph->setLiveGame(m_livegame);
        m_graph->setFullscreen();
    }

    LiveGameDetailsWidget::initializeItems();
}
