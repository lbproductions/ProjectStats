#include "dokolivegamerowwindow.h"

#include "dokolivegamedetailswidget.h"

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
    LiveGameRowWindow(dokogame,parent)
{
    m_liveGameDetailsWidget = new DokoLiveGameDetailsWidget(dokogame,this);

    m_livegame = dokogame;
    m_dokolivegame = dokogame;

    this->setCentralWidget(m_liveGameDetailsWidget);

    setupToolBar();
    this->fillWidget();

    if (m_dokolivegame->doko_mitSchmeisserei->value()){
        Gui::Details::LiveGameDetails::LiveGameDetailsWidget* widget = m_liveGameDetailsWidget;
    }

#ifdef Q_WS_MAC
    setUpFullScreenButton(this);
#endif
}

void DokoLiveGameRowWindow::setupToolBar()
{
    LiveGameRowWindow::setupToolBar();
    if (m_dokolivegame->doko_mitSchmeisserei->value()){
        m_actionSchmeisserei = new QAction(QIcon(":/graphics/icons/mac/livegame/schmeisserei"),tr("Schmeisserei"),m_toolbar);
        //m_actionSchmeisserei->setCheckable(true);
        connect(m_actionSchmeisserei,SIGNAL(triggered()),this,SLOT(newSchmeisserei()));
        m_toolbar->insertAction(m_actionFullScreen,m_actionSchmeisserei);
    }

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_toolbar->insertWidget(m_actionFullScreen,spacer);
}

void DokoLiveGameRowWindow::newSchmeisserei(){
        Gui::Details::LiveGameDetails::LiveGameDetailsWidget* widget = m_liveGameDetailsWidget;
        static_cast<DokoLiveGameDetailsWidget*>(widget)->showSchmeissereiWidget();
}

void DokoLiveGameRowWindow::pauseLiveGame(bool state){
    if(state){
        m_actionSchmeisserei->setEnabled(false);
    }
    else{
        m_actionSchmeisserei->setEnabled(true);
    }
    LiveGameRowWindow::pauseLiveGame(state);
}

void DokoLiveGameRowWindow::disableIcons(){
    m_actionSchmeisserei->setEnabled(false);
    LiveGameRowWindow::disableIcons();
}

