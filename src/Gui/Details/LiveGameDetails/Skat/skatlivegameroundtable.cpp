#include "skatlivegameroundtable.h"

#include <Database/Skat/skatlivegame.h>
#include <Database/Skat/skatround.h>
#include <Database/player.h>

#include <QDebug>

using namespace Gui::Details::LiveGameDetails::SkatLiveGameDetails;

SkatLiveGameRoundTable::SkatLiveGameRoundTable(Database::Skat::SkatLiveGame* livegame, QWidget *parent):
    LiveGameRoundTable(livegame,parent)
{
}

void SkatLiveGameRoundTable::addRound(Database::Round *round){
    Q_ASSERT(round != 0);
    Database::Skat::SkatRound* skatround = static_cast<Database::Skat::SkatRound*>(round);
    Q_ASSERT(skatround != 0);

    this->insertRow(this->rowCount());
    for(int i = 0; i<playerlist.size();i++){
        QTableWidgetItem* item = new QTableWidgetItem("");
        if (skatround->solist()->id() == playerlist.at(i)->id()){
            item->setText(QString::number(skatround->points(playerlist.at(i))) + " (S)");
        }
        else{
            item->setText(QString::number(skatround->points(playerlist.at(i))) + " (C)");
        }
        if (skatround->points(playerlist.at(i)) == 0){
            item->setBackgroundColor(QColor("lightGray"));
        }
        if (skatround->points(playerlist.at(i)) > 0){
            item->setBackgroundColor(QColor(148,0,0));
        }
        if (skatround->points(playerlist.at(i)) > 24){
            item->setBackgroundColor(QColor(188,0,0));
        }
        if (skatround->points(playerlist.at(i)) > 36){
            item->setBackgroundColor(QColor(220,0,0));
        }
        if (skatround->points(playerlist.at(i)) > 48){
            item->setBackgroundColor(QColor(255,0,0));
        }

        item->setTextAlignment(Qt::AlignCenter);
        this->setItem(this->rowCount()-1,i,item);
    }


    QTableWidgetItem* item = new QTableWidgetItem(QString::number(skatround->roundPoints()));
    item->setTextAlignment(Qt::AlignCenter);
    this->setItem(this->rowCount()-1,playerlist.size(),item);

    QTableWidgetItem* item1 = new QTableWidgetItem("");
    item1->setSizeHint(QSize(0,0));
    this->setVerticalHeaderItem(this->rowCount()-1,item1);
}

void SkatLiveGameRoundTable::markCardMixer(bool fullscreen){
    if (fullscreen)
        for (int i = 0; i<this->columnCount();i++){
            if (this->horizontalHeaderItem(i)->text() == m_livegame->cardmixer()->name()){
                this->horizontalHeaderItem(i)->setTextColor(QColor("red"));
            }
            else{
                this->horizontalHeaderItem(i)->setTextColor(QColor("white"));
            }
        }
    else{
        for (int i = 0; i<this->columnCount();i++){
            if (this->horizontalHeaderItem(i)->text() == m_livegame->cardmixer()->name()){
                this->horizontalHeaderItem(i)->setTextColor(QColor("red"));
            }
            else{
                this->horizontalHeaderItem(i)->setTextColor(QColor("black"));
            }
        }
    }
}
