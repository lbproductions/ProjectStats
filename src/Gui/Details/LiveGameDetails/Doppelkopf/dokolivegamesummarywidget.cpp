#include "dokolivegamesummarywidget.h"
#include "ui_gamesummarywidget.h"

#include <Database/Doppelkopf/dokolivegame.h>

namespace Gui {
namespace Details {
namespace LiveGameDetails {
namespace DokoLiveGameDetails {

DokoLiveGameSummaryWidget::DokoLiveGameSummaryWidget(Database::DokoLiveGame* game, QWidget* parent):
    LiveGameSummaryWidget(game,parent),
    m_dokoLiveGame(game)
{
    setupDokoStatsTab();
    setupDokoPlayersTab();
}

void DokoLiveGameSummaryWidget::setupDokoPlayersTab(){
    QWidget* statsWidget = new QWidget(this);
    QGridLayout* statsLayout = new QGridLayout(this);

    statsLayout->addWidget(new QLabel(tr("Player"),this),0,0);
    statsLayout->addWidget(new QLabel(tr("Re"),this),0,1);
    statsLayout->addWidget(new QLabel(tr("ReWins"),this),0,2);
    statsLayout->addWidget(new QLabel(tr("Contra"),this),0,3);
    statsLayout->addWidget(new QLabel(tr("ContraWins"),this),0,4);
    statsLayout->addWidget(new QLabel(tr("RoundWins"),this),0,5);
    statsLayout->addWidget(new QLabel(tr("AverageWinPoints"),this),0,6);

    int count = 1;
    foreach(Database::Player* p, m_dokoLiveGame->playersSortedByPlacement->value()){
        statsLayout->addWidget(new QLabel(p->name->value(),this),count,0);
        QString re = QString::number(m_dokoLiveGame->doko_rePercentage->value(p))
                + "% (" + QString::number(m_dokoLiveGame->doko_re->value(p))
                + "/" + QString::number(m_dokoLiveGame->doko_rounds->value(p)) + ")";
        statsLayout->addWidget(new QLabel(re,this),count,1);
        QString reWins = QString::number(m_dokoLiveGame->doko_reWinsPercentage->value(p))
                + "% (" + QString::number(m_dokoLiveGame->doko_reWins->value(p))
                + "/" + QString::number(m_dokoLiveGame->doko_re->value(p)) + ")";
        statsLayout->addWidget(new QLabel(reWins,this),count,2);
        QString contra = QString::number(m_dokoLiveGame->doko_contraPercentage->value(p))
                + "% (" + QString::number(m_dokoLiveGame->doko_contra->value(p))
                + "/" + QString::number(m_dokoLiveGame->doko_rounds->value(p)) + ")";
        statsLayout->addWidget(new QLabel(contra,this),count,3);
        QString contraWins = QString::number(m_dokoLiveGame->doko_contraWinsPercentage->value(p))
                + "% (" + QString::number(m_dokoLiveGame->doko_contraWins->value(p))
                + "/" + QString::number(m_dokoLiveGame->doko_contra->value(p)) + ")";
        statsLayout->addWidget(new QLabel(contraWins,this),count,4);
        statsLayout->addWidget(new QLabel(QString::number(m_dokoLiveGame->doko_roundWins->value(p)),this),count,5);
        statsLayout->addWidget(new QLabel(QString::number(m_dokoLiveGame->doko_pointAveragePerWin->value(p)),this),count,6);


        count++;
    }

    statsWidget->setLayout(statsLayout);
    ui->tabWidget->addTab(statsWidget,tr("DokoPlayerStats"));
}

void DokoLiveGameSummaryWidget::setupDokoStatsTab(){
    QWidget* statsWidget = new QWidget(this);
    QGridLayout* statsLayout = new QGridLayout(this);

    // Re vs. Contra Stats
    QGridLayout* roundWinsLayout = new QGridLayout(this);
    roundWinsLayout->addWidget(new QLabel(tr("ReWins"),this),0,0);
    roundWinsLayout->addWidget(new QLabel(tr("ContraWins"),this),1,0);
    QLabel* reWins = new QLabel(this);
    m_dokoLiveGame->doko_reRoundWins->futureWatcher()->connectTo(reWins);
    roundWinsLayout->addWidget(reWins,0,1);
    QLabel* contraWins = new QLabel(this);
    m_dokoLiveGame->doko_contraRoundWins->futureWatcher()->connectTo(contraWins);
    roundWinsLayout->addWidget(contraWins,1,1);
    statsLayout->addLayout(roundWinsLayout,0,0);

    //Doko-Besonderheiten-Stats
    QGridLayout* specialsLayout = new QGridLayout(this);
    if(m_dokoLiveGame->doko_mitHochzeit->value()){
        specialsLayout->addWidget(new QLabel(tr("Hochzeiten"),this),0,0);
        QLabel* hochzeitCount = new QLabel(tr(""),this);
        m_dokoLiveGame->doko_hochzeitCount->futureWatcher()->connectTo(hochzeitCount);
        specialsLayout->addWidget(hochzeitCount,0,1);
        QString players = "";
        foreach(Database::Player* p, m_dokoLiveGame->players->value()){
            if(m_dokoLiveGame->doko_hochzeit->value(p) > 0){
                players += p->name->value() + " (" + QString::number(m_dokoLiveGame->doko_hochzeit->value(p)) + "), ";
            }
        }
        players = players.remove(players.length()-2,players.length()-1);
        specialsLayout->addWidget(new QLabel(players,this),1,1);

    }
    if(m_dokoLiveGame->doko_mitSolo->value()){
        specialsLayout->addWidget(new QLabel(tr("Soli"),this),2,0);
        QLabel* soloCount = new QLabel(tr(""),this);
        m_dokoLiveGame->doko_soloCount->futureWatcher()->connectTo(soloCount);
        specialsLayout->addWidget(soloCount,2,1);
        QString players = "";
        foreach(Database::Player* p, m_dokoLiveGame->players->value()){
            if(m_dokoLiveGame->doko_solo->value(p) > 0){
                players += p->name->value() + " (" + QString::number(m_dokoLiveGame->doko_solo->value(p)) + "), ";
            }
        }
        players = players.remove(players.length()-2,players.length()-1);
        specialsLayout->addWidget(new QLabel(players,this),3,1);
    }
    if(m_dokoLiveGame->doko_mitPflichtsolo->value()){
        specialsLayout->addWidget(new QLabel(tr("Pflicht-Soli"),this),4,0);
        QLabel* pflichtSoloCount = new QLabel(tr(""),this);
        m_dokoLiveGame->doko_pflichtSoloCount->futureWatcher()->connectTo(pflichtSoloCount);
        specialsLayout->addWidget(pflichtSoloCount,4,1);
        QString players = "";
        foreach(Database::Player* p, m_dokoLiveGame->players->value()){
            if(m_dokoLiveGame->doko_hasPflichtSolo->value(p)){
                players += p->name->value() + " (" + "1" + "), ";
            }
        }
        players = players.remove(players.length()-2,players.length()-1);
        specialsLayout->addWidget(new QLabel(players,this),5,1);
    }
    if(m_dokoLiveGame->doko_mitTrumpfabgabe->value()){
        specialsLayout->addWidget(new QLabel(tr("Trumpfabgaben"),this),6,0);
        QLabel* trumpfabgabeCount = new QLabel(tr(""),this);
        m_dokoLiveGame->doko_trumpfabgabeCount->futureWatcher()->connectTo(trumpfabgabeCount);
        specialsLayout->addWidget(trumpfabgabeCount,6,1);
        QString players = "";
        foreach(Database::Player* p, m_dokoLiveGame->players->value()){
            if(m_dokoLiveGame->doko_trumpfabgabe->value(p) > 0){
                players += p->name->value() + " (" + QString::number(m_dokoLiveGame->doko_trumpfabgabe->value(p)) + "), ";
            }
        }
        players = players.remove(players.length()-2,players.length()-1);
        specialsLayout->addWidget(new QLabel(players,this),7,1);

    }
    if(m_dokoLiveGame->doko_mitSchweinerei->value()){
        specialsLayout->addWidget(new QLabel(tr("Schweinereien"),this),8,0);
        QLabel* schweinereiCount = new QLabel(tr(""),this);
        m_dokoLiveGame->doko_schweinereiCount->futureWatcher()->connectTo(schweinereiCount);
        specialsLayout->addWidget(schweinereiCount,8,1);
        QString players = "";
        foreach(Database::Player* p, m_dokoLiveGame->players->value()){
            if(m_dokoLiveGame->doko_schweinerei->value(p) > 0){
                players += p->name->value() + " (" + QString::number(m_dokoLiveGame->doko_schweinerei->value(p)) + "), ";
            }
        }
        players = players.remove(players.length()-2,players.length()-1);
        specialsLayout->addWidget(new QLabel(players,this),9,1);
     }
    if(m_dokoLiveGame->doko_mitSchmeisserei->value()){
        specialsLayout->addWidget(new QLabel(tr("Schmeissereien"),this),10,0);
        QLabel* schmeissereiCount = new QLabel(tr(""),this);
        m_dokoLiveGame->doko_schmeissereiCount->futureWatcher()->connectTo(schmeissereiCount);
        specialsLayout->addWidget(schmeissereiCount,10,1);
        QString players = "";
        foreach(Database::Player* p, m_dokoLiveGame->players->value()){
            if(m_dokoLiveGame->doko_schmeisserei->value(p) > 0){
                players += p->name->value() + " (" + QString::number(m_dokoLiveGame->doko_schmeisserei->value(p)) + "), ";
            }
        }
        players = players.remove(players.length()-2,players.length()-1);
        specialsLayout->addWidget(new QLabel(players,this),11,1);
    }
    statsLayout->addLayout(specialsLayout,1,0);

    statsWidget->setLayout(statsLayout);
    ui->tabWidget->addTab(statsWidget,tr("DokoGameStats"));
}

} // namespace DokoLiveGameDetails
} // namespace LiveGameDetails
} // namespace Details
} // namespace Gui
