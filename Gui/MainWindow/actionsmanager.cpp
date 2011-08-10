#include "actionsmanager.h"

#include "mainwindow.h"

#include <Gui/Wizards/NewGame/newgamewizard.h>
#include <Gui/Details/PlaceDetails/placedetailswidget.h>
#include <Gui/Details/DrinkDetails/DrinkDetailsWidget.h>
#include <Gui/Filter/newleaguedialog.h>
#include <handler.h>
#include <databasewindow.h>
#include <Database/player.h>
#include <Database/place.h>
#include <Database/drink.h>
#include <Database/database.h>
#include <Database/categorie.h>
#include <Database/Categories/childcategorie.h>
#include <Gui/Misc/newrowwidget.h>

#include <QKeySequence>
#include <QSettings>
#include <QAction>
#include <QIcon>


using namespace Gui::MainWindow;

ActionsManager::ActionsManager(MainWindow *parent) :
    QObject(parent),
    m_mainWindow(parent)
{
    createActions();
}

void ActionsManager::createActions()
{
    actionGameWizard = constructAction(tr("&New game"),":/graphics/icons/mac/mainwindow/newgame",QKeySequence::New);
    connect(actionGameWizard, SIGNAL(triggered()), this, SLOT(openGameWizard()));

    actionNewPlayer = constructAction(tr("&Player"),":/graphics/icons/mac/mainwindow/newplayer");
    connect(actionNewPlayer, SIGNAL(triggered()), this, SLOT(openNewPlayer()));

    actionNewPlace = constructAction(tr("P&lace"),":/graphics/icons/mac/mainwindow/newplace");
    connect(actionNewPlace, SIGNAL(triggered()), this, SLOT(openNewPlace()));

    actionNewDrink = constructAction(tr("&Drink"),":/graphics/icons/mac/mainwindow/newdrink");
    connect(actionNewDrink, SIGNAL(triggered()), this, SLOT(openNewDrink()));

    actionSwitchDatabase = constructAction(tr("&Switch database"),"",QKeySequence::Open);
    connect(actionSwitchDatabase, SIGNAL(triggered()), this, SLOT(switchDatabase()));

    actionCheckForUpdates = constructAction(tr("&Check for updates..."),"");
    actionCheckForUpdates->setMenuRole(QAction::ApplicationSpecificRole);
    connect(actionCheckForUpdates, SIGNAL(triggered()), this, SLOT(checkForUpdates()));

    actionNewPlayersFolder = constructAction(tr("Folder for players"),"");
    connect(actionNewPlayersFolder, SIGNAL(triggered()), this, SLOT(newPlayersFolder()));

    actionNewGamesFolder = constructAction(tr("Folder for games"),"");
    connect(actionNewGamesFolder, SIGNAL(triggered()), this, SLOT(newGamesFolder()));

    actionNewPlacesFolder = constructAction(tr("Folder for places"),"");
    connect(actionNewPlacesFolder, SIGNAL(triggered()), this, SLOT(newPlacesFolder()));

    actionNewDrinksFolder = constructAction(tr("Folder for drinks"),"");
    connect(actionNewDrinksFolder, SIGNAL(triggered()), this, SLOT(newDrinksFolder()));

    actionNewLeague = constructAction(tr("Folder for League"),"");
    connect(actionNewLeague, SIGNAL(triggered()), this, SLOT(newLeagueFolder()));

    actionUndo = constructAction(tr("Undo"),"",QKeySequence(QKeySequence::Undo));
    actionRedo = constructAction(tr("Redo"),"",QKeySequence(QKeySequence::Redo));
    actionCut = constructAction(tr("Cut"),"",QKeySequence(QKeySequence::Cut));
    actionCut->setEnabled(false);
    actionCopy = constructAction(tr("Copy"),"",QKeySequence(QKeySequence::Copy));
    actionCopy->setEnabled(false);
    actionPaste = constructAction(tr("Paste"),"",QKeySequence(QKeySequence::Paste));
    actionPaste->setEnabled(false);

    actionShowDatabase = constructAction(tr("Show Database"),"");
    connect(actionShowDatabase,SIGNAL(triggered()), this, SLOT(showDatabase()));
}

QAction *ActionsManager::constructAction(const QString &name, const QString &iconPath, const QKeySequence &shortcut)
{
    QIcon icon(iconPath);
    QAction *action = new QAction(icon,name,this);
    action->setShortcut(shortcut);
    return action;
}

void ActionsManager::openGameWizard()
{
    Wizards::NewGameWizard *gw = new Wizards::NewGameWizard(m_mainWindow);
    gw->show();
}

void ActionsManager::openNewPlayer(){
    NewRowWidget* createplayer = new NewRowWidget(new Database::Player(),m_mainWindow);
    createplayer->show();
}

void ActionsManager::openNewPlace(){
    NewRowWidget* createplace = new NewRowWidget(new Database::Place(),m_mainWindow);
    createplace->show();
}

void ActionsManager::openNewDrink(){
    NewRowWidget* createdrink = new NewRowWidget(new Database::Drink(),m_mainWindow);
    createdrink->show();
}

void ActionsManager::switchDatabase()
{
    QSettings settings;
    settings.setValue("handler/databaseFile",QVariant());
    Handler::getInstance()->showMainWindow();
}

void ActionsManager::checkForUpdates()
{
    Handler::getInstance()->checkForUpdates();
}

void ActionsManager::newPlayersFolder()
{

    //Handler::getInstance()->database()->categories()->createFolderCategorie(Database::ChildCategorie::PlayersCategorieContentType);
}

void ActionsManager::newGamesFolder()
{
    //Handler::getInstance()->database()->categories()->createFolderCategorie(Database::ChildCategorie::GamesCategorieContentType);
}

void ActionsManager::newPlacesFolder()
{
    //Handler::getInstance()->database()->categories()->createFolderCategorie(Database::ChildCategorie::PlacesCategorieContentType);
}

void ActionsManager::newDrinksFolder()
{
    //Handler::getInstance()->database()->categories()->createFolderCategorie(Database::ChildCategorie::DrinksCategorieContentType);
}

void ActionsManager::newLeagueFolder()
{
    NewLeagueDialog* leaguedialog = new NewLeagueDialog(m_mainWindow);
    leaguedialog->show();
}

void ActionsManager::showDatabase()
{
    DatabaseWindow* databaseWindow = new DatabaseWindow(m_mainWindow);
    databaseWindow->show();
}
