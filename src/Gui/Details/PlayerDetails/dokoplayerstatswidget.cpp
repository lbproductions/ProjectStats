#include "dokoplayerstatswidget.h"
#include "ui_dokoplayerstatswidget.h"
#include "ui_abstractplayerstatswidget.h"

#include <Database/player.h>

using namespace Gui::Details;

DokoPlayerStatsWidget::DokoPlayerStatsWidget(Database::Player* player, QWidget *parent) :
    AbstractPlayerStatsWidget(player,"Doppelkopf",parent),
    uiDoko(new Ui::DokoPlayerStatsWidget)
{
    uiDoko->setupUi(this);

    player->dokoStats()->hochzeiten->futureWatcher()->connectTo(uiDoko->labelHochzeiten);
    player->dokoStats()->soli->futureWatcher()->connectTo(uiDoko->labelSoli);
    player->dokoStats()->trumpfabgaben->futureWatcher()->connectTo(uiDoko->labelTrumpfabgaben);
    player->dokoStats()->schmeissereien->futureWatcher()->connectTo(uiDoko->labelSchmeissereien);
    player->dokoStats()->schweinereien->futureWatcher()->connectTo(uiDoko->labelSchweinereien);
    player->gameCount->mappingFutureWatcher("Doppelkopf")->connectTo(uiDoko->labelGames);
    player->liveGameCount->mappingFutureWatcher("Doppelkopf")->connectTo(uiDoko->labelLiveGames);
    player->offlineGameCount->mappingFutureWatcher("Doppelkopf")->connectTo(uiDoko->labelOfflineGames);
    player->gamePoints->mappingFutureWatcher("Doppelkopf")->connectTo(uiDoko->labelPoints);
    player->liveGamePoints->mappingFutureWatcher("Doppelkopf")->connectTo(uiDoko->labelPointsLive);
    player->offlineGamePoints->mappingFutureWatcher("Doppelkopf")->connectTo(uiDoko->labelPointsOffline);

    ui->tabWidget->addTab(uiDoko->tab_2,"Doko I");
    ui->tabWidget->addTab(uiDoko->tab,"Doko II");
}

DokoPlayerStatsWidget::~DokoPlayerStatsWidget()
{
    delete uiDoko;
}
