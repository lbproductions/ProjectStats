#include "abstractplayerstatswidget.h"
#include "ui_abstractplayerstatswidget.h"

#include <Database/player.h>

using namespace Gui::Details;

AbstractPlayerStatsWidget::AbstractPlayerStatsWidget(Database::Player* player, QString type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AbstractPlayerStatsWidget)
{
    ui->setupUi(this);

    player->points->mappingFutureWatcher(type)->connectTo(ui->labelPoints);
    player->gameCount->mappingFutureWatcher(type)->connectTo(ui->labelGames);
    player->losses->mappingFutureWatcher(type)->connectTo(ui->labelLosses);
    player->wins->mappingFutureWatcher(type)->connectTo(ui->labelWins);
    player->average->mappingFutureWatcher(type)->connectTo(ui->labelAverage);
    player->lastWin->mappingFutureWatcher(type)->connectTo(ui->labelLastWin);
    player->lastGame->mappingFutureWatcher(type)->connectTo(ui->labelLastGame);
}

AbstractPlayerStatsWidget::~AbstractPlayerStatsWidget()
{
    delete ui;
    qDebug() << "AbstractPlayerStatsWidget wird zerstört";
}
