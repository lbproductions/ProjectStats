#include "livegamerowwindow.h"

#include "adddrinkwidget.h"

#ifdef Q_WS_MAC
#   include <Gui/Misc/macwindowcontroller.h>
#endif

#include <QAction>
#include <QToolBar>
#include <QLabel>
#include <QDebug>

using namespace Gui::Details;

LiveGameRowWindow::LiveGameRowWindow(Database::LiveGame* livegame, QWidget* widget):
    RowWindow(livegame,widget,false),
    m_livegame(livegame)
{
    setupToolBar();

    connect(livegame->state,SIGNAL(changed()),this,SLOT(reflectState()));

    reflectState();

#ifdef Q_WS_MAC
    setUpFullScreenButton(this);
#endif
}

LiveGameRowWindow::~LiveGameRowWindow()
{
    if(m_livegame->state->value() == Database::Round::RunningState)
    {
        m_livegame->setState(Database::Round::PausedState);
    }
}

void LiveGameRowWindow::setupToolBar()
{
    m_toolbar = new QToolBar(tr("Live Game"));
    m_toolbar->setIconSize(QSize(50,44));
    m_toolbar->setMovable(false);
    m_toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    addToolBar(m_toolbar);

    m_actionPause = new QAction(QIcon(":/graphics/icons/mac/livegame/pause"),tr("Pause"),m_toolbar);
    m_actionPause->setCheckable(true);
    connect(m_actionPause,SIGNAL(triggered(bool)),this,SLOT(pauseLiveGame(bool)));
    m_toolbar->addAction(m_actionPause);

    m_actionCloseGame = new QAction(QIcon(":/graphics/icons/mac/livegame/closegame"),tr("End Game"),m_toolbar);
    connect(m_actionCloseGame,SIGNAL(triggered()),this,SLOT(showEndGameDialog()));
    m_toolbar->addAction(m_actionCloseGame);

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_toolbar->addWidget(spacer);

    m_actionAddDrink = new QAction(QIcon(":/graphics/icons/mac/livegame/adddrink"),tr("Add Drink"),m_toolbar);
    connect(m_actionAddDrink,SIGNAL(triggered()),this,SLOT(showAddDrinkDialog()));
    m_toolbar->addAction(m_actionAddDrink);

    m_actionNewRound = new QAction(QIcon(":/graphics/icons/mac/livegame/newround"),tr("New Round"),m_toolbar);
    connect(m_actionNewRound,SIGNAL(triggered()),this,SLOT(showNewRoundDialog()));
    m_toolbar->addAction(m_actionNewRound);

    QIcon iconFullscreen(":/graphics/icons/mac/livegame/fullscreen");
    m_actionFullScreen = new QAction(iconFullscreen,tr("Fullscreen"),m_toolbar);
    m_actionFullScreen->setCheckable(true);
    connect(m_actionFullScreen, SIGNAL(triggered(bool)), this, SLOT(setFullScreen(bool)));
    m_toolbar->addAction(m_actionFullScreen);

    //setUnifiedTitleAndToolBarOnMac(true);
}


void LiveGameRowWindow::setFullScreen(bool state)
{
    if (state)
    {
#ifndef Q_WS_MAC
        this->showFullScreen();
#else
        //setUnifiedTitleAndToolBarOnMac(false);
        toggleFullscreen(this);
#endif
        m_actionFullScreen->setIcon(QIcon(":/graphics/icons/mac/livegame/normal"));
        m_actionFullScreen->setText(tr("Exit Fullscreen"));
        m_toolbar->setStyleSheet("QWidget { background-image: url(:/graphics/styles/mac/toolbar/fullscreen/toolbar_background_fullscreen); border: 0px solid transparent; border-bottom: 1px solid gray;color: white;}");
    }
    else
    {
        this->setMinimumSize(100,100);
#ifndef Q_WS_MAC
        this->showNormal();
#else
        toggleFullscreen(this);
        //setUnifiedTitleAndToolBarOnMac(true);
#endif
        m_actionFullScreen->setIcon(QIcon(":/graphics/icons/mac/livegame/fullscreen"));
        m_actionFullScreen->setText(tr("Fullscreen"));
        m_toolbar->setStyleSheet("");
    }
}

void LiveGameRowWindow::pauseLiveGame(bool pause)
{
    if(pause)
    {
        m_livegame->setState(Database::Round::PausedState);
    }
    else
    {
        m_livegame->setState(Database::Round::RunningState);
    }
}

void LiveGameRowWindow::showEndGameDialog()
{
    Gui::Details::LiveGameDetails::EndLiveGameWidget endGameWidget(m_livegame,this);
    endGameWidget.exec();
}

void LiveGameRowWindow::reflectState()
{
    m_actionPause->setEnabled(true);
    m_actionNewRound->setEnabled(true);
    m_actionCloseGame->setEnabled(true);
    m_actionAddDrink->setEnabled(true);
    m_actionPause->setEnabled(true);
    m_actionNewRound->setEnabled(true);

    switch(m_livegame->state->value())
    {
    case Database::Round::PausedState:
        m_actionPause->setIcon(QIcon(":/graphics/icons/mac/livegame/play"));
        m_actionPause->setText(tr("Play"));
        m_actionPause->setChecked(true);
        m_actionNewRound->setEnabled(false);
        break;

    case Database::Round::FinishedState:
        m_actionPause->setEnabled(false);
        m_actionNewRound->setEnabled(false);
        m_actionCloseGame->setEnabled(false);
        m_actionAddDrink->setEnabled(false);
        m_actionPause->setEnabled(false);
        m_actionNewRound->setEnabled(false);
        break;

    case Database::Round::RunningState:
        m_actionPause->setIcon(QIcon(":/graphics/icons/mac/livegame/pause"));
        m_actionPause->setText(tr("Pause"));
        break;

    default:
        break;
    }
}

void LiveGameRowWindow::showAddDrinkDialog()
{
    LiveGameDetails::AddDrinkWidget addDrinkDialog(this);
    addDrinkDialog.exec();
}

void LiveGameRowWindow::showNewRoundDialog()
{
}
