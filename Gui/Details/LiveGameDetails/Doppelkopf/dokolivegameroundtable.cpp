#include "dokolivegameroundtable.h"

#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/Doppelkopf/dokoround.h>
#include <Database/player.h>

using namespace Gui::Details::LiveGameDetails::DokoLiveGameDetails;

DokoLiveGameRoundTable::DokoLiveGameRoundTable(Database::DokoLiveGame* livegame, QWidget *parent):
    LiveGameRoundTable(livegame,parent)
{
    fillWidget();
}

void DokoLiveGameRoundTable::addRound(::Database::Round* round)
{
    Database::DokoRound* dokoround = static_cast<Database::DokoRound*>(round);

    this->insertRow(this->rowCount());
    int i = 0;
    foreach(Database::Player* p, m_livegame->playersSortedByPosition->value())
    {
        QTableWidgetItem* item = new QTableWidgetItem("");
        item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
        if (dokoround->doko_re->value(p)){
            QString text = QString::number(dokoround->points->value(p)) + " (R";
            if(dokoround->doko_hochzeitPlayerId->value() == p->id())
            {
                text += ",H)";
            }
            else if(dokoround->doko_trumpfabgabePlayerId->value() == p->id())
            {
                text += ",T)";
            }
            else
            {
                text += ")";
            }
            item->setText(text);
        }
        else{
            item->setText(QString::number(dokoround->points->value(p)) + " (C)");
        }
        if (dokoround->points->value(p) == 0){
            item->setBackgroundColor(QColor("lightGray"));
        }
        if (dokoround->points->value(p) < 0){
            item->setBackgroundColor(QColor(148,0,0));
        }
        if (dokoround->points->value(p) < -3){
            item->setBackgroundColor(QColor(188,0,0));
        }
        if (dokoround->points->value(p) < -6){
            item->setBackgroundColor(QColor(220,0,0));
        }
        if (dokoround->points->value(p) <-9){
            item->setBackgroundColor(QColor(255,0,0));
        }
        if (dokoround->points->value(p) > 0){
            item->setBackgroundColor(QColor(10,104,0));
        }
        if (dokoround->points->value(p) > 3){
            item->setBackgroundColor(QColor(13,141,0));
        }
        if (dokoround->points->value(p) > 6){
            item->setBackgroundColor(QColor(19,205,0));
        }
        if (dokoround->points->value(p) > 9){
            item->setBackgroundColor(QColor(24,255,0));
        }

        item->setTextAlignment(Qt::AlignCenter);
        this->setItem(this->rowCount()-1,i,item);
        ++i;
    }


    QTableWidgetItem* item = new QTableWidgetItem(QString::number(dokoround->roundPoints->value()));
    item->setTextAlignment(Qt::AlignCenter);
    this->setItem(this->rowCount()-1,m_livegame->players->value().size(),item);

    QTableWidgetItem* item1 = new QTableWidgetItem("");
    item1->setSizeHint(QSize(0,0));
    this->setVerticalHeaderItem(this->rowCount()-1,item1);

    this->scrollToBottom();
}
