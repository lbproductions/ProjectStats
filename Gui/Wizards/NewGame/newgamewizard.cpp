#include "newgamewizard.h"

#include "liveofflinegamewidget.h"
#include "offlinegameoptionswidget.h"
#include "offlinegameresultwidget.h"
#include "offlinesummarywidget.h"
#include "offlinedetailledgamedokowidget.h"
#include "livegamegeneraloptionswidget.h"
#include "livedokogameoptionswidget.h"
#include "wizardsidewidget.h"
#include "skatlivegameoptionswidget.h"

//#include <Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamerowwindow.h>
//#include <Gui/Details/LiveGameDetails/Skat/skatlivegamerowwindow.h>
#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/Skat/skatlivegame.h>
#include <Database/livegame.h>
#include <Gui/Details/rowwindow.h>

#include <QDebug>
#include <QMessageBox>

using namespace Gui::Wizards;

NewGameWizard::NewGameWizard(QWidget *parent) :
    QWizard(parent)
{
    initializeWidget();
    setModal(true);

    this->setPixmap(QWizard::BackgroundPixmap,QPixmap(":/pictures/logo"));

    //this->setSideWidget(new NewGame::WizardSideWidget());

    connect(this,SIGNAL(accepted()),this,SLOT(on_accepted()));

    setAttribute(Qt::WA_DeleteOnClose);
    setButtonText(QWizard::FinishButton,"Create Game");
}

void NewGameWizard::initializeWidget()
{
    this->setWindowTitle(tr("New Game"));

    this->setOption(QWizard::NoBackButtonOnStartPage,true);

    m_sideWidget = new NewGame::WizardSideWidget();
    this->setSideWidget(m_sideWidget);

    m_offlineGameResultWidget = new NewGame::OfflineGameResultWidget(this);
    m_offlineDokoWidget = new NewGame::OfflineDetailledGameDokoWidget(this);
    m_liveGameGeneralOptionsWidget = new NewGame::LiveGameGeneralOptionsWidget(this);
    m_liveDokoGameOptionsWidget = new NewGame::LiveDokoGameOptionsWidget(this);
    m_skatLiveGameOptionsWidget = new NewGame::SkatLiveGameOptionsWidget(this);

    this->setPage(Page_LiveOfflineGame, new NewGame::LiveOfflineGameWidget());
    this->setPage(Page_OfflineGameOptions, new NewGame::OfflineGameOptionsWidget());
    this->setPage(Page_OfflineGameResult, m_offlineGameResultWidget);
    this->setPage(Page_DetailledOfflineDokoGame, m_offlineDokoWidget);
    this->setPage(Page_LiveGameGeneralOptions, m_liveGameGeneralOptionsWidget);
    this->setPage(Page_LiveGameDokoOptions, m_liveDokoGameOptionsWidget);
    this->setPage(Page_SkatLiveGameOptionsWidget, m_skatLiveGameOptionsWidget);
}

void NewGameWizard::on_accepted()
{
    Database::Game* game = 0;
    if(field("isLive").toBool())
    {
        Database::LiveGame *livegame = 0;
        QString type = field("live_type").toString();
        if(type == Database::DokoLiveGame::TYPE)
        {
            livegame = createDokoLiveGame();
        }
        else if(type == "Skat")
        {

        }

        Database::Games::instance()->insertRow(livegame);

        livegame->startNextRound();

        livegame->date->setValue(QDateTime::currentDateTime());

        QPointer<Database::Place> place = m_liveGameGeneralOptionsWidget->selectedPlace();
        livegame->siteId->setValue(place->id());

        foreach(Database::Player *player, m_liveGameGeneralOptionsWidget->selectedPlayers())
        {
            livegame->addPlayer(player);
        }

        game = livegame;
    }
    else
    {

    }

    game->rowWindow()->show();
}

Database::DokoLiveGame *NewGameWizard::createDokoLiveGame()
{
    Database::DokoLiveGame *game = new Database::DokoLiveGame(
                field("doko_mitHochzeit").toBool(),
                field("doko_mitSolo").toBool(),
                field("doko_mitTrumpfabgabe").toBool(),
                field("doko_mitSchweinerei").toBool(),
                field("doko_mitSchmeisserei").toBool(),

                field("doko_mitPflichtsolo").toBool(),
                field("doko_mitBubenSolo").toBool(),
                field("doko_mitDamenSolo").toBool(),
                field("doko_mitFarbsolo").toBool(),
                field("doko_mitFleischlos").toBool(),
                field("doko_mitTrumpfsolo").toBool(),

                field("doko_mitFuenfKoenige").toBool(),
                field("doko_mitZuWenigTrumpf").toBool(),
                field("doko_mitNeunzigPunkte").toBool(),
                field("doko_mitTrumpfabgabeSchmeisserei").toBool()
                );

    return game;
}
