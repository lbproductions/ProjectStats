#include "dokoplayerstatsspecialstats.h"
#include "ui_dokoplayerstatsspecialstats.h"

#include <Database/player.h>
#include <Database/Doppelkopf/dokolivegame.h>

using namespace Gui::Details::LiveGameDetails::Sidebar;

DokoPlayerStatsSpecialStats::DokoPlayerStatsSpecialStats(Database::DokoLiveGame *dokoLiveGame, Database::Player *player, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DokoPlayerStatsSpecialStats),
    m_player(player),
    m_dokoLiveGame(dokoLiveGame)
{
    ui->setupUi(this);

    if(dokoLiveGame->doko_mitSolo->value()){
        if(dokoLiveGame->doko_mitPflichtsolo->value()){
            onPflichtSoloChanged();
            connect(dokoLiveGame->doko_hasPflichtSolo->mappingFutureWatcher(player),SIGNAL(valueChanged(QString)),this,SLOT(onPflichtSoloChanged()));
        }
        else{
            ui->labelSoloPflicht->setVisible(false);
            ui->labelSoloPflichtHeader->setVisible(false);
        }
        dokoLiveGame->doko_solo->mappingFutureWatcher(player)->connectTo(ui->labelSoli);
    }
    else{
        ui->labelSoli->setVisible(false);
        ui->labelSoliHeader->setVisible(false);
    }

    if(dokoLiveGame->doko_mitHochzeit->value()){
        dokoLiveGame->doko_hochzeit->mappingFutureWatcher(player)->connectTo(ui->labelHochzeiten);
    }
    else{
        ui->labelHochzeiten->setVisible(false);
        ui->labelHochzeitenWon->setVisible(false);
        ui->labelHochzeitenHeader->setVisible(false);
        ui->labelHochzeitenWonHeader->setVisible(false);
    }

    if(dokoLiveGame->doko_mitTrumpfabgabe->value()){
        dokoLiveGame->doko_trumpfabgabe->mappingFutureWatcher(player)->connectTo(ui->labelAbgaben);
    }
    else{
        ui->labelAbgaben->setVisible(false);
        ui->labelAbgabenWon->setVisible(false);
        ui->labelAbgabenHeader->setVisible(false);
        ui->labelAbgabenWonHeader->setVisible(false);
    }

    if(dokoLiveGame->doko_mitSchweinerei->value()){
        dokoLiveGame->doko_schweinerei->mappingFutureWatcher(player)->connectTo(ui->labelSchweinereien);
    }
    else{
        ui->labelSchweinereien->setVisible(false);
        ui->labelSchweinereienWon->setVisible(false);
        ui->labelSchweinereienHeader->setVisible(false);
        ui->labelSchweinereienWonHeader->setVisible(false);
    }

}

DokoPlayerStatsSpecialStats::~DokoPlayerStatsSpecialStats()
{
    delete ui;
}

void DokoPlayerStatsSpecialStats::onPflichtSoloChanged(){
    if(m_dokoLiveGame->doko_hasPflichtSolo->value(m_player)){
        ui->labelSoloPflicht->setPixmap(QPixmap(":/graphics/icons/mac/gamewidget/gamestate_finished"));
    }
    else{
        ui->labelSoloPflicht->setPixmap(QPixmap(":/graphics/icons/mac/gamewidget/gamestate_default"));
    }
}
