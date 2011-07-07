#include "livegamerowwindow.h"

#include <QAction>
#include <QToolBar>
#include <QLabel>

#include <QDebug>

using namespace Gui::Details;

LiveGameRowWindow::LiveGameRowWindow(Database::LiveGame* livegame, QWidget* widget):
    RowWindow(livegame,widget)
{
    m_liveGameDetailsWidget = new LiveGameDetails::LiveGameDetailsWidget(livegame,this);

    this->setAttribute(Qt::WA_DeleteOnClose);
}

void LiveGameRowWindow::setupToolBar(){
    m_toolbar = new QToolBar(tr("LiveGame"));
    m_toolbar->setIconSize(QSize(50,44));
    m_toolbar->setMovable(false);
    m_toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    addToolBar(m_toolbar);

    m_actionPause = new QAction(QIcon(":/graphics/icons/mac/livegame/pause"),tr("Pause"),m_toolbar);
    m_actionPause->setCheckable(true);
    connect(m_actionPause,SIGNAL(triggered(bool)),this,SLOT(pauseLiveGame(bool)));
    m_toolbar->addAction(m_actionPause);

    m_actionCloseGame = new QAction(QIcon(":/graphics/icons/mac/livegame/closegame"),tr("Close Game"),m_toolbar);
    connect(m_actionCloseGame,SIGNAL(triggered()),this,SLOT(finishLiveGame()));
    m_toolbar->addAction(m_actionCloseGame);

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_toolbar->addWidget(spacer);

    m_actionAddDrink = new QAction(QIcon(":/graphics/icons/mac/livegame/adddrink"),tr("Add Drink"),m_toolbar);
    //m_actionAddDrink->setCheckable(true);
    connect(m_actionAddDrink,SIGNAL(triggered()),this,SLOT(addDrink()));
    m_toolbar->addAction(m_actionAddDrink);

    m_actionNewRound = new QAction(QIcon(":/graphics/icons/mac/livegame/newround"),tr("New Round"),m_toolbar);
    //m_actionNewRound->setCheckable(true);
    connect(m_actionNewRound,SIGNAL(triggered()),this,SLOT(newRound()));
    m_toolbar->addAction(m_actionNewRound);

    QIcon iconFullscreen(":/graphics/icons/mac/livegame/fullscreen");
    m_actionFullScreen = new QAction(iconFullscreen,tr("Fullscreen"),m_toolbar);
    m_actionFullScreen->setCheckable(true);
    connect(m_actionFullScreen, SIGNAL(triggered(bool)), this, SLOT(setFullScreen(bool)));
    m_toolbar->addAction(m_actionFullScreen);

    m_actionSettings = new QAction(QIcon(":/graphics/icons/mac/livegame/settings"),tr("Settings"),m_toolbar);
    //m_actionSettings->setCheckable(true);
    connect(m_actionSettings,SIGNAL(triggered()),this,SLOT(showSettings()));
    m_toolbar->addAction(m_actionSettings);

    connect(m_liveGameDetailsWidget,SIGNAL(drinkDealed()),m_actionAddDrink,SLOT(trigger()));
    connect(m_liveGameDetailsWidget,SIGNAL(finishedGameShown()),this,SLOT(disableIcons()));
    connect(m_liveGameDetailsWidget,SIGNAL(gameEnded()),this,SLOT(onGameEnded()));

    //setUnifiedTitleAndToolBarOnMac(true);
}

void LiveGameRowWindow::setFullScreen(bool state){
    if (state){
        //setUnifiedTitleAndToolBarOnMac(false);
        this->showFullScreen();
        m_actionFullScreen->setIcon(QIcon(":/graphics/icons/mac/livegame/normal"));
        m_actionFullScreen->setText(tr("NormalMode"));
        m_liveGameDetailsWidget->setFullscreenMode();
        //m_toolbar->setStyleSheet("QWidget { background: black; border: 2px solid black; color: white;}");
        m_toolbar->setStyleSheet("QWidget { background-image: url(:/graphics/styles/mac/toolbar/fullscreen/toolbar_background_fullscreen); border: 0px solid transparent; border-bottom: 1px solid gray;color: white;}");
        qDebug() << "Height of Toolbar: " + QString::number(m_toolbar->height());
    }
    else{
        this->setMinimumSize(100,100);
        this->showNormal();
        m_actionFullScreen->setIcon(QIcon(":/graphics/icons/mac/livegame/fullscreen"));
        m_actionFullScreen->setText(tr("FullScreen"));
        m_liveGameDetailsWidget->setNormalMode();
        m_toolbar->setStyleSheet("");
        //setUnifiedTitleAndToolBarOnMac(true);
    }
}

void LiveGameRowWindow::pauseLiveGame(bool state){
    if(state){
        m_livegame->setState(Database::Round::PausedState);
        m_liveGameDetailsWidget->pauseGame();
        m_actionPause->setIcon(QIcon(":/graphics/icons/mac/livegame/play"));
        m_actionPause->setText(tr("Play"));

        m_actionNewRound->setEnabled(false);
    }
    else{
        m_livegame->setState(Database::Round::RunningState);
        m_liveGameDetailsWidget->resumeGame();
        m_actionPause->setIcon(QIcon(":/graphics/icons/mac/livegame/pause"));
        m_actionPause->setText(tr("Pause"));

        m_actionNewRound->setEnabled(true);
    }
}

void LiveGameRowWindow::finishLiveGame(){
    m_endLiveGameWidget = new Gui::Details::LiveGameDetails::EndLiveGameWidget(m_livegame);
    m_endLiveGameWidget->show();

    connect(m_endLiveGameWidget,SIGNAL(liveGameClosed()),this,SLOT(onLiveGameClosed()));
}

void LiveGameRowWindow::onLiveGameClosed(){

    m_liveGameDetailsWidget->closeGame();

    this->close();

}

void LiveGameRowWindow::fillWidget(){
    m_liveGameDetailsWidget->fillWidget();
}

void LiveGameRowWindow::addDrink(){
    m_liveGameDetailsWidget->showAddDrinkWidget();
}

void LiveGameRowWindow::disableIcons(){
    m_actionPause->setEnabled(false);
    m_actionNewRound->setEnabled(false);
    m_actionCloseGame->setEnabled(false);
    m_actionAddDrink->setEnabled(false);
}

void LiveGameRowWindow::showSettings(){
    m_liveGameDetailsWidget->showLiveGameSettingsWidget();
}

void LiveGameRowWindow::newRound(){
   m_liveGameDetailsWidget->showRoundWidget();
}

void LiveGameRowWindow::onGameEnded(){
    m_actionPause->setEnabled(false);
    m_actionNewRound->setEnabled(false);
}
