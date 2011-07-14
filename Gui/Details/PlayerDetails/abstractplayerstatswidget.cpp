#include "abstractplayerstatswidget.h"
#include "ui_abstractplayerstatswidget.h"

#include <Database/player.h>

using namespace Gui::Details;

AbstractPlayerStatsWidget::AbstractPlayerStatsWidget(Database::Player* player, QString type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AbstractPlayerStatsWidget)
{
    ui->setupUi(this);

    player->points->mappingFutureWatcher()->connectTo(ui->labelPoints,type);
    player->gameCount->mappingFutureWatcher()->connectTo(ui->labelGames,type);
    player->losses->mappingFutureWatcher()->connectTo(ui->labelLosses,type);
    player->wins->mappingFutureWatcher()->connectTo(ui->labelWins,type);
    player->average->mappingFutureWatcher()->connectTo(ui->labelAverage,type);
    player->lastWin->mappingFutureWatcher()->connectTo(ui->labelLastWin,type);
    player->lastGame->mappingFutureWatcher()->connectTo(ui->labelLastGame,type);
}

AbstractPlayerStatsWidget::~AbstractPlayerStatsWidget()
{
    delete ui;
    qDebug() << "AbstractPlayerStatsWidget wird zerstört";
}
