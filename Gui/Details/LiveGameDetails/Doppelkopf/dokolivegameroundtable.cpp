#include "dokolivegameroundtable.h"

#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/Doppelkopf/dokoround.h>
#include <Database/player.h>

using namespace Gui::Details::LiveGameDetails::DokoLiveGameDetails;

DokoLiveGameRoundTable::DokoLiveGameRoundTable(Database::DokoLiveGame* livegame, QWidget *parent):
    LiveGameRoundTable(livegame,parent)
{
}

void DokoLiveGameRoundTable::addRound(Database::Round *round){
    Q_ASSERT(round != 0);
    Database::DokoRound* dokoround = static_cast<Database::DokoRound*>(round);
    Q_ASSERT(dokoround != 0);

    this->insertRow(this->rowCount());
    for(int i = 0; i<playerlist.size();i++){
        QTableWidgetItem* item = new QTableWidgetItem("");
        if (dokoround->doko_re->value(playerlist.at(i))){
            item->setText(QString::number(dokoround->points->value(playerlist.at(i))) + " (R)");
        }
        else{
            item->setText(QString::number(dokoround->points->value(playerlist.at(i))) + " (C)");
        }
        if (dokoround->points->value(playerlist.at(i)) == 0){
            item->setBackgroundColor(QColor("lightGray"));
        }
        if (dokoround->points->value(playerlist.at(i)) < 0){
            item->setBackgroundColor(QColor(148,0,0));
        }
        if (dokoround->points->value(playerlist.at(i)) < -3){
            item->setBackgroundColor(QColor(188,0,0));
        }
        if (dokoround->points->value(playerlist.at(i)) < -6){
            item->setBackgroundColor(QColor(220,0,0));
        }
        if (dokoround->points->value(playerlist.at(i)) <-9){
            item->setBackgroundColor(QColor(255,0,0));
        }
        if (dokoround->points->value(playerlist.at(i)) > 0){
            item->setBackgroundColor(QColor(10,104,0));
        }
        if (dokoround->points->value(playerlist.at(i)) > 3){
            item->setBackgroundColor(QColor(13,141,0));
        }
        if (dokoround->points->value(playerlist.at(i)) > 6){
            item->setBackgroundColor(QColor(19,205,0));
        }
        if (dokoround->points->value(playerlist.at(i)) > 9){
            item->setBackgroundColor(QColor(24,255,0));
        }

        item->setTextAlignment(Qt::AlignCenter);
        this->setItem(this->rowCount()-1,i,item);
    }


    QTableWidgetItem* item = new QTableWidgetItem(QString::number(dokoround->roundPoints->value()));
    item->setTextAlignment(Qt::AlignCenter);
    this->setItem(this->rowCount()-1,playerlist.size(),item);

    QTableWidgetItem* item1 = new QTableWidgetItem("");
    item1->setSizeHint(QSize(0,0));
    this->setVerticalHeaderItem(this->rowCount()-1,item1);
}

void DokoLiveGameRoundTable::markCardMixer(bool fullscreen){
    if (fullscreen)
        for (int i = 0; i<this->columnCount();i++){
            if (this->horizontalHeaderItem(i)->text() == m_livegame->cardmixer->value()->name->value()){
                this->horizontalHeaderItem(i)->setTextColor(QColor("red"));
            }
            else{
                this->horizontalHeaderItem(i)->setTextColor(QColor("white"));
            }
        }
    else{
        for (int i = 0; i<this->columnCount();i++){
            if (this->horizontalHeaderItem(i)->text() == m_livegame->cardmixer->value()->name->value()){
                this->horizontalHeaderItem(i)->setTextColor(QColor("red"));
            }
            else{
                this->horizontalHeaderItem(i)->setTextColor(QColor("black"));
            }
        }
    }
}
