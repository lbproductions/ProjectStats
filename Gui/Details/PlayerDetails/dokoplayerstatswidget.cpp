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
    player->gameCount->mappingFutureWatcher()->connectTo(uiDoko->labelGames,"Doppelkopf");
    player->dokoStats()->liveGames->futureWatcher()->connectTo(uiDoko->labelLiveGames);
    player->dokoStats()->offlineGames->futureWatcher()->connectTo(uiDoko->labelOfflineGames);
    player->dokoStats()->points->futureWatcher()->connectTo(uiDoko->labelPoints);
    player->dokoStats()->livePoints->futureWatcher()->connectTo(uiDoko->labelPointsLive);
    player->dokoStats()->offlinePoints->futureWatcher()->connectTo(uiDoko->labelPointsOffline);

    ui->tabWidget->addTab(uiDoko->tab_2,"Doko I");
    ui->tabWidget->addTab(uiDoko->tab,"Doko II");
}

DokoPlayerStatsWidget::~DokoPlayerStatsWidget()
{
    delete uiDoko;
}
