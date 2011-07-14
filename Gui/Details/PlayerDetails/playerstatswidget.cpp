#include "playerstatswidget.h"
#include "ui_playerstatswidget.h"

#include <Database/player.h>
#include <Database/game.h>
//#include <Stats/PlayerStats/abstractplayerstats.h>
//#include <Stats/PlayerStats/generalplayerstats.h>
#include <Gui/Details/PlayerDetails/abstractplayerstatswidget.h>

using namespace Gui::Details;

PlayerStatsWidget::PlayerStatsWidget(Database::Player* player, QWidget *parent) :
    StatsWidget(player,parent),
    ui(new Ui::PlayerStatsWidget)
{
    ui->setupUi(this);

//    foreach(Stats::Players::AbstractPlayerStats* stats, player->stats().values()){
//	ui->tabWidget->addTab(stats->statsWidget(),stats->statsWidget()->title());
//    }

    foreach(QString s, Database::Games::instance()->types->value()){
        ui->tabWidget->addTab(player->typeStatsWidget(s),s);
    }

    player->average->mappingFutureWatcher()->connectTo(ui->labelAverageValue,"General");
    player->gameCount->mappingFutureWatcher()->connectTo(ui->labelGamesValue,"General");
    player->losses->mappingFutureWatcher()->connectTo(ui->labelLossesValue,"General");
    player->points->mappingFutureWatcher()->connectTo(ui->labelPointsValue,"General");
    player->wins->mappingFutureWatcher()->connectTo(ui->labelWinsValue,"General");

    if(player->lastGame->value("General") != QDateTime())
    {
        player->lastGame->mappingFutureWatcher()->connectTo(ui->labelLastGameValue,"General");
    }
    else
    {
	ui->labelLastGameValue->setText(tr("Never"));
    }

    if(player->lastWin->value("General") != QDateTime())
    {
        player->lastWin->mappingFutureWatcher()->connectTo(ui->labelLastWinValue,"General");
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
