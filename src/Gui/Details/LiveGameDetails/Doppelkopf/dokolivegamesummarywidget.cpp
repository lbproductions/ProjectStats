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

    statsWidget->setLayout(statsLayout);
    ui->tabWidget->addTab(statsWidget,tr("DokoGameStats"));
}

} // namespace DokoLiveGameDetails
} // namespace LiveGameDetails
} // namespace Details
} // namespace Gui
