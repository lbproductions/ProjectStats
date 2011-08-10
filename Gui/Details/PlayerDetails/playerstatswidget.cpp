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


    foreach(QString s, Database::Games::instance()->types->value()){
        ui->tabWidget->addTab(player->typeStatsWidget(s),s);
    }

    player->average->mappingFutureWatcher("General")->connectTo(ui->labelAverageValue);
    player->gameCount->mappingFutureWatcher("General")->connectTo(ui->labelGamesValue);
    player->losses->mappingFutureWatcher("General")->connectTo(ui->labelLossesValue);
    player->points->mappingFutureWatcher("General")->connectTo(ui->labelPointsValue);
    player->wins->mappingFutureWatcher("General")->connectTo(ui->labelWinsValue);

    if(player->lastGame->value("General") != QDateTime())
    {
        player->lastGame->mappingFutureWatcher("General")->connectTo(ui->labelLastGameValue);
    }
    else
    {
	ui->labelLastGameValue->setText(tr("Never"));
    }

    if(player->lastWin->value("General") != QDateTime())
    {
        player->lastWin->mappingFutureWatcher("General")->connectTo(ui->labelLastWinValue);
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
