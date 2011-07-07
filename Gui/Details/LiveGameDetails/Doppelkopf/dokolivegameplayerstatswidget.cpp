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

    if (prevWidth != width || roundId != prevRoundId){
	prevWidth = width;
	prevRoundId = roundId;
	for (int i = 0; i<playerlist.size();i++){
//	    QString stats;
//            if (!m_livegame->isFinished->value()){
//                stats = "Re: " + QString::number(m_livegame->doko_re->value(playerlist.at(i)))
//                        + "<br>Contra: " + QString::number(m_livegame->doko_contra->value(playerlist.at(i))-1);
//	    }
//	    else{
//                stats = "Re: " + QString::number(m_livegame->doko_re->value(playerlist.at(i)))
//                        + "<br>Contra: " + QString::number(m_livegame->doko_contra->value(playerlist.at(i)));
//	    }
//            if (m_livegame->doko_mitHochzeit->value()){
//                stats = stats + "<br>Hochzeiten:" + QString::number(m_livegame->doko_hochzeitCount->value(playerlist.at(i)));
//	    }
//            if (m_livegame->doko_mitSolo->value()){
//                stats = stats + "<br>Soli:" + QString::number(m_livegame->doko_soloCount->value(playerlist.at(i)));
//	    }
//            if(m_livegame->doko_mitTrumpfabgabe->value()){
//                stats = stats + "<br>Trumpfabgaben:" + QString::number(m_livegame->doko_trumpfabgabeCount->value(playerlist.at(i)));
//	    }
//            if (m_livegame->doko_mitSchweinerei->value()){
//                stats = stats + "<br>Schweinereien:" + QString::number(m_livegame->doko_schweinereiCount->value(playerlist.at(i)));
//	    }
//            if (m_livegame->doko_mitSchmeisserei->value()){
//                stats = stats + "<br>Schmeissereien:" + QString::number(m_livegame->doko_schmeissereiCount->value(playerlist.at(i)));
//	    }
//	    stats = stats + "<br><br>";
//            stats = stats + "Round-Wins: " + QString::number(m_livegame->doko_roundWins->value(playerlist.at(i)));
//            stats = stats + "<br>Average per win: " + QString::number(m_livegame->doko_pointAveragePerWin->value(playerlist.at(i)));
//            stats = stats + "<br><br>";
//	    for (int j = 0; j<playerlist.size();j++){
//		if (i != j){
//                    stats = stats + playerlist.at(i)->name->value() + " - " + playerlist.at(j)->name->value() + " : " + QString::number(m_livegame->doko_gamesTogether->value(playerlist.at(i),playerlist.at(j))) + "<br>";
//                    stats = stats + playerlist.at(i)->name->value() + " - " + playerlist.at(j)->name->value() + " : " + QString::number(m_livegame->doko_winsTogether->value(playerlist.at(i),playerlist.at(j))) + "<br>";
//		}
//	    }
//	    QLabel* label = new QLabel(stats);
//	    label->setTextFormat(Qt::RichText);
//	    label->setAlignment(Qt::AlignCenter);
//	    this->setItemWidget(this->topLevelItem(0),i,label);

//	    this->header()->resizeSection(i, width);
	}

	QLabel* label = new QLabel("");
	label->setTextFormat(Qt::RichText);
	this->setItemWidget(this->topLevelItem(0),playerlist.size(),label);
    }
}
