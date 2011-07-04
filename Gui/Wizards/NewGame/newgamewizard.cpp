#include "newgamewizard.h"

#include "liveofflinegamewidget.h"
#include "offlinegameoptionswidget.h"
#include "offlinegameresultwidget.h"
#include "offlinesummarywidget.h"
#include "offlinedetailledgamedokowidget.h"
#include "livegamegeneraloptionswidget.h"
#include "livedokogameoptionswidget.h"
#include "livesummarywidget.h"
#include "wizardsidewidget.h"
#include "skatlivegameoptionswidget.h"

//#include <Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamerowwindow.h>
//#include <Gui/Details/LiveGameDetails/Skat/skatlivegamerowwindow.h>
#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/Skat/skatlivegame.h>
#include <Database/livegame.h>

#include <QDebug>
#include <QMessageBox>

using namespace Gui::Wizards;

NewGameWizard::NewGameWizard(QWidget *parent) :
    QWizard(parent)
{
    initializeWidget();
    setModal(true);

    this->setPixmap(QWizard::BackgroundPixmap,QPixmap(":/pictures/logo"));

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
    m_offlineSummaryWidget = new NewGame::OfflineSummaryWidget(this);
    m_offlineDokoWidget = new NewGame::OfflineDetailledGameDokoWidget(this);
    m_liveGameGeneralOptionsWidget = new NewGame::LiveGameGeneralOptionsWidget(this);
    m_liveDokoGameOptionsWidget = new NewGame::LiveDokoGameOptionsWidget(this);
    m_liveSummaryWidget = new NewGame::LiveSummaryWidget(this);
    m_skatLiveGameOptionsWidget = new NewGame::SkatLiveGameOptionsWidget(this);

    this->setPage(Page_LiveOfflineGame, new NewGame::LiveOfflineGameWidget());
    this->setPage(Page_OfflineGameOptions, new NewGame::OfflineGameOptionsWidget());
    this->setPage(Page_OfflineGameResult, m_offlineGameResultWidget);
    this->setPage(Page_DetailledOfflineDokoGame, m_offlineDokoWidget);
    this->setPage(Page_OfflineSummary, m_offlineSummaryWidget);
    this->setPage(Page_LiveGameGeneralOptions, m_liveGameGeneralOptionsWidget);
    this->setPage(Page_LiveGameDokoOptions, m_liveDokoGameOptionsWidget);
    this->setPage(Page_LiveSummary, m_liveSummaryWidget);
    this->setPage(Page_SkatLiveGameOptionsWidget, m_skatLiveGameOptionsWidget);
}
