#include "dokolivegameroundtable.h"

#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/Doppelkopf/dokoround.h>
#include <Database/player.h>

using namespace Gui::Details::LiveGameDetails::DokoLiveGameDetails;

DokoLiveGameRoundTable::DokoLiveGameRoundTable(Database::DokoLiveGame* livegame, QWidget *parent):
    LiveGameRoundTable(livegame,parent)
{
    setStyleSheet(QString("Gui--Details--LiveGameDetails--DokoLiveGameDetails--DokoLiveGameRoundTable{background-color:black; color: white; border-radius: 10px; margin-top: 10px;} "
//                    "QHeaderView::section {background-color: black;font-size: 30px; padding:2px;"
//                        "border-radius: 5px; margin-bottom: 2px; height: 65px;}"
//                  "QScrollBar:vertical {"
//                        "border: 1px solid black;"
//                        "border-radius: 10px;"
//                        "background: rgb(76,76,76);"
//                        "width: 15px;"
//                        "margin: 22px 0 22px 0;}"
//                    "QScrollBar::handle:vertical {"
//                        "background: rgb(135,135,135);"
//                        "border-top: 2px;"
//                        "border-bottom: 2px;}"
//                        //"min-height: 20px;}"
//                    "QScrollBar::add-line:vertical {"
//                        "border: 1px solid black;"
//                        "background: rgb(76,76,76);"
//                        "height: 20px;"
//                        "subcontrol-position: bottom;"
//                        "subcontrol-origin: margin;}"
//                    "QScrollBar::sub-line:vertical {"
//                        "border: 1px solid black;"
//                        "background: rgb(76,76,76);"
//                        "height: 20px;"
//                        //"subcontrol-position: bottom;"
//                        "subcontrol-origin: margin;}"
//                   "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
//                        "height: 6px;"
//                        "width: 7px;"
//                       "background-image: url(:/graphics/styles/mac/scrollbar/fullscreen/scrollbar_arrowdown_fullscreen);}"
//                    "QScrollBar::up-arrow:vertical{"
//                         "height: 6px;"
//                         "width: 7px;"
//                         "background-image: url(:/graphics/styles/mac/scrollbar/fullscreen/scrollbar_arrowup_fullscreen);}"
//                    "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
//                        "background: none;}"));
                          ));

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
        if (dokoround->doko_re->value(p)){
            item->setText(QString::number(dokoround->points->value(p)) + " (R)");
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
