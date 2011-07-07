#include "dokolivegameplayerstatswidget.h"

#include <Database/round.h>
#include <Database/player.h>
#include <Database/Doppelkopf/dokolivegame.h>

#include <QHeaderView>
#include <QLabel>

using namespace Gui::Details::LiveGameDetails::DokoLiveGameDetails;

DokoLiveGamePlayerStatsWidget::DokoLiveGamePlayerStatsWidget(Database::DokoLiveGame* livegame, QWidget *parent) :
    QTreeWidget(parent)
{
    m_livegame = livegame;

    playerlist = livegame->playersSortedByPosition->value();

    this->addTopLevelItem(new QTreeWidgetItem());

    this->setColumnCount(playerlist.size()+1);

    this->header()->hide();

    updateWidget();
}

void DokoLiveGamePlayerStatsWidget::updateWidget(){
    double width = (double)this->width() / (double)(playerlist.size() + 1);
    int roundId = m_livegame->currentRound->value()->id();

//    if (prevWidth != width || roundId != prevRoundId){
//	prevWidth = width;
//	prevRoundId = roundId;
//	for (int i = 0; i<playerlist.size();i++){
//	    QString stats;
//	    if (!m_livegame->isFinished->value()){
//                stats = "Re: " + QString::number(m_livegame->re(playerlist.at(i)))
//			+ "<br>Contra: " + QString::number(m_livegame->contra(playerlist.at(i))-1);
//	    }
//	    else{
//                stats = "Re: " + QString::number(m_livegame->re(playerlist.at(i)))
//			+ "<br>Contra: " + QString::number(m_livegame->contra(playerlist.at(i)));
//	    }
//	    if (m_livegame->mitHochzeit->value()){
//		stats = stats + "<br>Hochzeiten:" + QString::number(m_livegame->hochzeiten(playerlist.at(i)));
//	    }
//	    if (m_livegame->mitSolo()){
//		stats = stats + "<br>Soli:" + QString::number(m_livegame->soli(playerlist.at(i)));
//	    }
//	    if(m_livegame->mitTrumpfabgabe()){
//		stats = stats + "<br>Trumpfabgaben:" + QString::number(m_livegame->trumpfabgaben(playerlist.at(i)));
//	    }
//	    if (m_livegame->mitSchweinerei()){
//		stats = stats + "<br>Schweinereien:" + QString::number(m_livegame->schweinereien(playerlist.at(i)));
//	    }
//	    if (m_livegame->mitSchmeisserei()){
//		stats = stats + "<br>Schmeissereien:" + QString::number(m_livegame->schmeissereien(playerlist.at(i)));
//	    }
//	    stats = stats + "<br><br>";
//            stats = stats + "Round-Wins: " + QString::number(m_livegame->roundWins(playerlist.at(i)));
//            stats = stats + "<br>Average per win: " + QString::number(m_livegame->pointAveragePerWin(playerlist.at(i)));
//            stats = stats + "<br><br>";
//	    for (int j = 0; j<playerlist.size();j++){
//		if (i != j){
//                    stats = stats + playerlist.at(i)->name() + " - " + playerlist.at(j)->name() + " : " + QString::number(m_livegame->gamesTogether(playerlist.at(i),playerlist.at(j))) + "<br>";
//                    stats = stats + playerlist.at(i)->name() + " - " + playerlist.at(j)->name() + " : " + QString::number(m_livegame->winsTogether(playerlist.at(i),playerlist.at(j))) + "<br>";
//		}
//	    }
//	    QLabel* label = new QLabel(stats);
//	    label->setTextFormat(Qt::RichText);
//	    label->setAlignment(Qt::AlignCenter);
//	    this->setItemWidget(this->topLevelItem(0),i,label);

//	    this->header()->resizeSection(i, width);
//	}

//	QLabel* label = new QLabel("");
//	label->setTextFormat(Qt::RichText);
//	this->setItemWidget(this->topLevelItem(0),playerlist.size(),label);
//    }
}
