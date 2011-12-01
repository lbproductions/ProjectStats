#include "actionsmanager.h"

#include "mainwindow.h"

#include <Gui/Wizards/NewGame/newgamewizard.h>
#include <Gui/Details/PlaceDetails/placedetailswidget.h>
#include <Gui/Details/DrinkDetails/DrinkDetailsWidget.h>
#include <Gui/Filter/newleaguedialog.h>
#include <Misc/handler.h>
#include <Gui/Misc/databasewindow.h>
#include <Database/player.h>
#include <Database/place.h>
#include <Database/drink.h>
#include <LBDatabase/LBDatabase.h>
#include <Database/categorie.h>
#include <Database/game.h>
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

    actionPlayersShowGeneral = constructAction(tr("General"),"");
    actionPlayersShowGeneral->setCheckable(true);
    connect(actionPlayersShowGeneral,SIGNAL(triggered()),this,SLOT(playersShowGeneral()));
    actionPlayersShowDoppelkopf = constructAction(tr("Doppelkopf"),"");
    actionPlayersShowDoppelkopf->setCheckable(true);
    connect(actionPlayersShowDoppelkopf,SIGNAL(triggered()),this,SLOT(playersShowDoppelkopf()));
    actionPlayersShowSkat = constructAction(tr("Skat"),"");
    actionPlayersShowSkat->setCheckable(true);
    connect(actionPlayersShowSkat,SIGNAL(triggered()),this,SLOT(playersShowSkat()));
    actionPlayersShowHearts = constructAction(tr("Hearts"),"");
    actionPlayersShowHearts->setCheckable(true);
    connect(actionPlayersShowHearts,SIGNAL(triggered()),this,SLOT(playersShowHearts()));
    actionPlayersShowPrognose = constructAction(tr("Prognose"),"");
    actionPlayersShowPrognose->setCheckable(true);
    connect(actionPlayersShowPrognose,SIGNAL(triggered()),this,SLOT(playersShowPrognose()));
    actionPlayersShowPoker = constructAction(tr("Poker"),"");
    actionPlayersShowPoker->setCheckable(true);
    connect(actionPlayersShowPoker,SIGNAL(triggered()),this,SLOT(playersShowPoker()));

    actionGamesShowAll = constructAction(tr("Show All"),"");
    actionGamesShowAll->setCheckable(true);
    connect(actionGamesShowAll,SIGNAL(triggered()),this,SLOT(gamesShowAll()));
    actionGamesShowUnfinished = constructAction(tr("Show unfinished games"),"");
    actionGamesShowUnfinished->setCheckable(true);
    connect(actionGamesShowUnfinished,SIGNAL(triggered()),this,SLOT(gamesShowUnfinished()));
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
    DatabaseWindow* databaseWindow = new DatabaseWindow();
    databaseWindow->show();
}

QList<QString> ActionsManager::createDefaultPlayerColumns()
{
    QList<QString> list;
    list.append("Name");
    list.append("Games");
    list.append("Points");
    list.append("Wins");
    list.append("Losses");
    list.append("LastGame");
    list.append("LastWin");
    list.append("Avatar");
    list.append("Color");
    list.append("Average");
    return list;
}

void ActionsManager::playersShowGeneral(){
    if(actionPlayersShowGeneral->isChecked()){
        Database::Players::instance()->model()->setDisplayRole(AttributeVariant::MainWindow);
        Database::Players::instance()->model()->setData(Database::Players::instance()->allRows());
        Database::Players::instance()->model()->setVisibleColumns(createDefaultPlayerColumns());
        actionPlayersShowDoppelkopf->setChecked(false);
        actionPlayersShowHearts->setChecked(false);
        actionPlayersShowPoker->setChecked(false);
        actionPlayersShowPrognose->setChecked(false);
        actionPlayersShowSkat->setChecked(false);
     }
}
void ActionsManager::playersShowDoppelkopf(){
    if(actionPlayersShowDoppelkopf->isChecked()){
        Database::Players::instance()->model()->setDisplayRole(AttributeVariant::DoppelkopfWindow);
        Database::Players::instance()->model()->setData(Database::Players::instance()->playersOfType->value("Doppelkopf"));

        QList<QString> list;
        list.append(createDefaultPlayerColumns());
        list.append("Hochzeiten");
        list.append("Soli");
        list.append("Trumpfabgaben");
        list.append("Schweinereien");
        list.append("Schmeissereien");
        list.append("GamePoints");
        list.append("RePercentage");
        list.append("ContraPercentage");
        list.append("PointAveragePerRound");
        list.append("RoundWinsPercentage");
        Database::Players::instance()->model()->setVisibleColumns(list);

        actionPlayersShowGeneral->setChecked(false);
        actionPlayersShowHearts->setChecked(false);
        actionPlayersShowPoker->setChecked(false);
        actionPlayersShowPrognose->setChecked(false);
        actionPlayersShowSkat->setChecked(false);
    }
}

void ActionsManager::playersShowPoker(){
    if(actionPlayersShowPoker->isChecked()){
        Database::Players::instance()->model()->setDisplayRole(AttributeVariant::PokerWindow);
        Database::Players::instance()->model()->setData(Database::Players::instance()->playersOfType->value("Poker"));
        Database::Players::instance()->model()->setVisibleColumns(createDefaultPlayerColumns());
        actionPlayersShowGeneral->setChecked(false);
        actionPlayersShowDoppelkopf->setChecked(false);
        actionPlayersShowHearts->setChecked(false);
        actionPlayersShowPrognose->setChecked(false);
        actionPlayersShowSkat->setChecked(false);
    }
}

void ActionsManager::playersShowHearts(){
    if(actionPlayersShowHearts->isChecked()){
        Database::Players::instance()->model()->setDisplayRole(AttributeVariant::HeartsWindow);
        Database::Players::instance()->model()->setData(Database::Players::instance()->playersOfType->value("Hearts"));
        Database::Players::instance()->model()->setVisibleColumns(createDefaultPlayerColumns());
        actionPlayersShowGeneral->setChecked(false);
        actionPlayersShowDoppelkopf->setChecked(false);
        actionPlayersShowPoker->setChecked(false);
        actionPlayersShowPrognose->setChecked(false);
        actionPlayersShowSkat->setChecked(false);
    }
}

void ActionsManager::playersShowSkat(){
    if(actionPlayersShowSkat->isChecked()){
        Database::Players::instance()->model()->setDisplayRole(AttributeVariant::SkatWindow);
        Database::Players::instance()->model()->setData(Database::Players::instance()->playersOfType->value("Skat"));

        QList<QString> list;
        list.append(createDefaultPlayerColumns());
        list.append("GamePoints");
        Database::Players::instance()->model()->setVisibleColumns(list);

        actionPlayersShowGeneral->setChecked(false);
        actionPlayersShowDoppelkopf->setChecked(false);
        actionPlayersShowHearts->setChecked(false);
        actionPlayersShowPoker->setChecked(false);
        actionPlayersShowPrognose->setChecked(false);
    }
}

void ActionsManager::playersShowPrognose(){
    if(actionPlayersShowPrognose->isChecked()){
        Database::Players::instance()->model()->setDisplayRole(AttributeVariant::PrognoseWindow);
        Database::Players::instance()->model()->setData(Database::Players::instance()->playersOfType->value("Prognose"));
        Database::Players::instance()->model()->setVisibleColumns(createDefaultPlayerColumns());
        actionPlayersShowGeneral->setChecked(false);
        actionPlayersShowDoppelkopf->setChecked(false);
        actionPlayersShowHearts->setChecked(false);
        actionPlayersShowPoker->setChecked(false);
        actionPlayersShowSkat->setChecked(false);
    }
}

QList<QString> ActionsManager::createDefaultGameColumns(){
    QList<QString> list;
    list.append("Name");
    list.append("Date");
    list.append("Length");
    list.append("%Complete");
    list.append("State");
    list.append("Type");
    list.append("Players");
    list.append("Site");
    return list;
}

void ActionsManager::gamesShowAll(){
    if(actionGamesShowAll->isChecked()){
        Database::Games::instance()->model()->setData(Database::Games::instance()->allRows());
        Database::Games::instance()->model()->setVisibleColumns(createDefaultGameColumns());
        actionGamesShowUnfinished->setChecked(false);
    }
}

void ActionsManager::gamesShowUnfinished(){
    if(actionGamesShowUnfinished->isChecked()){
        Database::Games::instance()->model()->setData(Database::Games::instance()->unfinishedGames->value());
        Database::Games::instance()->model()->setVisibleColumns(createDefaultGameColumns());
        actionGamesShowAll->setChecked(false);
    }
}
