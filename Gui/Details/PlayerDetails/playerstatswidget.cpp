#include "playerstatswidget.h"
#include "ui_playerstatswidget.h"

#include <Database/player.h>
#include <Database/game.h>
//#include <Stats/PlayerStats/abstractplayerstats.h>
//#include <Stats/PlayerStats/generalplayerstats.h>
//#include <Gui/Details/PlayerDetails/abstractplayerstatswidget.h>

using namespace Gui::Details;

PlayerStatsWidget::PlayerStatsWidget(Database::Player* player, QWidget *parent) :
    StatsWidget(player,parent),
    ui(new Ui::PlayerStatsWidget)
{
    ui->setupUi(this);

//    foreach(Stats::Players::AbstractPlayerStats* stats, player->stats().values()){
//	ui->tabWidget->addTab(stats->statsWidget(),stats->statsWidget()->title());
//    }

    player->average->futureWatcher()->connectTo(ui->labelAverageValue);
    player->games->futureWatcher()->connectTo(ui->labelGamesValue);
    player->losses->futureWatcher()->connectTo(ui->labelLossesValue);
    player->points->mappingFutureWatcher()->connectTo(ui->labelPointsValue,"General");
    player->wins->futureWatcher()->connectTo(ui->labelWinsValue);

    QDateTime game = player->lastGame->value();
    if(game.date().year() != 1960)
    {
        player->lastGame->futureWatcher()->connectTo(ui->labelLastGameValue);
    }
    else
    {
	ui->labelLastGameValue->setText(tr("Never"));
    }

    game = player->lastWin->value();
    if(game.date().year() != 1960)
    {
        player->lastGame->futureWatcher()->connectTo(ui->labelLastWinValue);
    }
    else
    {
	ui->labelLastWinValue->setText(tr("Never"));
    }

}

PlayerStatsWidget::~PlayerStatsWidget()
{
    delete ui;
}
