#include "dokolivegamerowwindow.h"

#include "dokolivegamedetailswidget.h"
#include "schmeissereiwidget.h"
#include "newdokoroundwidget.h"
#include "dokoendlivegamewidget.h"
#include "newdoppelkopfroundwidget.h"

#include <Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamedetailswidget.h>
#include <Database/Doppelkopf/dokolivegame.h>
#include <Server/soapprojectstatsService.h>

#include <QDebug>
#include <QAction>
#include <QToolBar>

using namespace Gui::Details;

DokoLiveGameRowWindow::DokoLiveGameRowWindow(Database::DokoLiveGame* dokogame, QWidget *parent) :
    LiveGameRowWindow(dokogame,parent),
    m_dokolivegame(dokogame)
{
    m_liveGameDetailsWidget = new DokoLiveGameDetailsWidget(dokogame,this);

    this->setCentralWidget(m_liveGameDetailsWidget);

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
    if(m_dokolivegame->doko_mitSchmeisserei->value())
    {
        m_actionSchmeisserei->setEnabled(true);
    }

    switch(m_livegame->state->value())
    {
    case Database::Round::PausedState:
        if(m_dokolivegame->doko_mitSchmeisserei->value())
        {
            m_actionSchmeisserei->setEnabled(false);
        }
        break;

    case Database::Round::FinishedState:
        if(m_dokolivegame->doko_mitSchmeisserei->value())
        {
            m_actionSchmeisserei->setEnabled(false);
        }
        break;

    case Database::Round::RunningState:
        break;

    default:
        break;
    }

    LiveGameRowWindow::reflectState();
}

void DokoLiveGameRowWindow::showNewRoundDialog()
{
    LiveGameDetails::DokoLiveGameDetails::NewDokoRoundWidget newDokoRoundWidget(m_dokolivegame,this);
    newDokoRoundWidget.exec();
    /*
    LiveGameDetails::DokoLiveGameDetails::NewDoppelkopfRoundWidget newDokoRoundWidget(m_dokolivegame,this);
    newDokoRoundWidget.exec();
    */
}

void DokoLiveGameRowWindow::showEndGameDialog()
{
    Gui::Details::LiveGameDetails::DokoLiveGameDetails::DokoEndLiveGameWidget endGameWidget(m_dokolivegame,this);
    endGameWidget.exec();
}
