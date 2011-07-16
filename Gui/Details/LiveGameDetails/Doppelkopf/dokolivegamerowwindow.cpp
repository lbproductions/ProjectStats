#include "dokolivegamerowwindow.h"

#include "dokolivegamedetailswidget.h"
#include "schmeissereiwidget.h"

#include <Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamedetailswidget.h>
#include <Database/Doppelkopf/dokolivegame.h>
#ifdef Q_WS_MAC
#   include <Gui/Misc/macwindowcontroller.h>
#endif


#include <QDebug>
#include <QAction>
#include <QToolBar>

using namespace Gui::Details;

DokoLiveGameRowWindow::DokoLiveGameRowWindow(Database::DokoLiveGame* dokogame, QWidget *parent) :
    LiveGameRowWindow(dokogame,parent),
    m_dokolivegame(dokogame)
{
    //m_liveGameDetailsWidget = new DokoLiveGameDetailsWidget(dokogame,this);

    //this->setCentralWidget(m_rowWidget);

    setupToolBar();

    reflectState();
}

void DokoLiveGameRowWindow::setupToolBar()
{
    if (m_dokolivegame->doko_mitSchmeisserei->value())
    {
        m_actionSchmeisserei = new QAction(QIcon(":/graphics/icons/mac/livegame/schmeisserei"),tr("Schmeisserei"),m_toolbar);
        //m_actionSchmeisserei->setCheckable(true);
        connect(m_actionSchmeisserei,SIGNAL(triggered()),this,SLOT(showNewSchmeissereiDialog()));
        m_toolbar->insertAction(m_actionFullScreen,m_actionSchmeisserei);
    }

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_toolbar->insertWidget(m_actionFullScreen,spacer);
}

void DokoLiveGameRowWindow::showNewSchmeissereiDialog()
{
    LiveGameDetails::DokoLiveGameDetails::SchmeissereiWidget schmeissereiWidget(m_dokolivegame,this);
    schmeissereiWidget.exec();
}

void DokoLiveGameRowWindow::reflectState()
{
    m_actionSchmeisserei->setEnabled(true);

    switch(m_livegame->state->value())
    {
    case Database::Round::PausedState:
        m_actionSchmeisserei->setEnabled(false);
        break;

    case Database::Round::FinishedState:
        m_actionSchmeisserei->setEnabled(false);
        break;

    case Database::Round::RunningState:
        break;

    default:
        break;
    }

    LiveGameRowWindow::reflectState();
}
