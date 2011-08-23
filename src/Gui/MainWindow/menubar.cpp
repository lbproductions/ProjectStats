#include "menubar.h"

#include "mainwindow.h"
#include "actionsmanager.h"

using namespace Gui::MainWindow;

MenuBar::MenuBar(MainWindow *parent) :
    QMenuBar(),
    m_actionsManager(parent->actionsManager())
{
    setupFileMenu();
    setupEditMenu();
    setupViewMenu();
    setupHelpMenu();
}

void MenuBar::setupFileMenu()
{
    m_fileMenu = addMenu(tr("&File"));

    m_fileMenu->addAction(m_actionsManager->actionGameWizard);

    QMenu *newMenu = m_fileMenu->addMenu(tr("New"));
    newMenu->addAction(m_actionsManager->actionNewPlayer);
    newMenu->addAction(m_actionsManager->actionNewPlace);
    newMenu->addAction(m_actionsManager->actionNewDrink);
    newMenu->addSeparator();
    newMenu->addAction(m_actionsManager->actionNewPlayersFolder);
    newMenu->addAction(m_actionsManager->actionNewGamesFolder);
    newMenu->addAction(m_actionsManager->actionNewDrinksFolder);
    newMenu->addAction(m_actionsManager->actionNewPlacesFolder);
    newMenu->addAction(m_actionsManager->actionNewLeague);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_actionsManager->actionSwitchDatabase);
    m_fileMenu->addAction(m_actionsManager->actionCheckForUpdates);
}

void MenuBar::setupEditMenu()
{
    m_editMenu = addMenu(tr("&Edit"));

    m_editMenu->addAction(m_actionsManager->actionUndo);
    m_editMenu->addAction(m_actionsManager->actionRedo);
    m_editMenu->addSeparator();
    m_editMenu->addAction(m_actionsManager->actionCut);
    m_editMenu->addAction(m_actionsManager->actionCopy);
    m_editMenu->addAction(m_actionsManager->actionPaste);
}

void MenuBar::setupHelpMenu()
{
    m_helpMenu = addMenu(tr("&Help"));
}

void MenuBar::setupViewMenu(){
    m_viewMenu = addMenu(tr("&View"));

    m_viewMenu->addAction(m_actionsManager->actionShowDatabase);
    m_viewPlayers = m_viewMenu->addMenu(tr("&Players"));
    m_viewGames = m_viewMenu->addMenu(tr("&Games"));
    m_viewPlayers->addAction(m_actionsManager->actionPlayersShowGeneral);
    m_viewPlayers->addAction(m_actionsManager->actionPlayersShowDoppelkopf);
    m_viewPlayers->addAction(m_actionsManager->actionPlayersShowHearts);
    m_viewPlayers->addAction(m_actionsManager->actionPlayersShowPoker);
    m_viewPlayers->addAction(m_actionsManager->actionPlayersShowPrognose);
    m_viewPlayers->addAction(m_actionsManager->actionPlayersShowSkat);
    m_actionsManager->actionPlayersShowGeneral->setChecked(true);
}
