#include "dokoplayerstatsroundbox.h"
#include "ui_dokoplayerstatsroundbox.h"

#include <Database/player.h>
#include <Database/Doppelkopf/dokolivegame.h>

using namespace Gui::Details::LiveGameDetails::Sidebar;

DokoPlayerStatsRoundBox::DokoPlayerStatsRoundBox(Database::DokoLiveGame *dokoLiveGame, Database::Player *player, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DokoPlayerStatsRoundBox)
{
    ui->setupUi(this);

    dokoLiveGame->doko_rounds->mappingFutureWatcher(player)->connectTo(ui->labelRounds);
    dokoLiveGame->doko_roundWins->mappingFutureWatcher(player)->connectTo(ui->labelRoundsWon);
    dokoLiveGame->doko_re->mappingFutureWatcher(player)->connectTo(ui->labelReRounds);
    dokoLiveGame->doko_reWins->mappingFutureWatcher(player)->connectTo(ui->labelReRoundsWins);
    dokoLiveGame->doko_contra->mappingFutureWatcher(player)->connectTo(ui->labelContraRounds);
    dokoLiveGame->doko_contraWins->mappingFutureWatcher(player)->connectTo(ui->labelContraWins);
}

DokoPlayerStatsRoundBox::~DokoPlayerStatsRoundBox()
{
    delete ui;
}
