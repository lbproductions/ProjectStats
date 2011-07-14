#include "livegameroundtable.h"

#include <Database/player.h>
#include <Database/Doppelkopf/dokoround.h>
#include <Database/Doppelkopf/dokolivegame.h>
#include <Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamedetailswidget.h>

#include <QDebug>

using namespace Gui::Details::LiveGameDetails;

LiveGameRoundTable::LiveGameRoundTable(Database::LiveGame* livegame, QWidget *parent) :
    QTableWidget(parent)
{
    m_livegame = livegame;

    playerlist = m_livegame->playersSortedByPosition->value();

    foreach(Database::Player *player, m_livegame->playersSortedByPosition->value())
    {
	this->insertColumn(this->columnCount());
	QPixmap pixmap(150,150);
        pixmap.fill(player->color->value());
        this->setHorizontalHeaderItem(this->columnCount()-1,new QTableWidgetItem(QIcon(pixmap),player->name->value()));
    }

    this->insertColumn(this->columnCount());
    this->setHorizontalHeaderItem(this->columnCount()-1,new QTableWidgetItem(tr("RoundPoints")));

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    updateSizes();

}

void LiveGameRoundTable::addRound(Database::Round* /*round*/)
{

}

void LiveGameRoundTable::updateSizes()
{
    double width = ((double)this->width() / (double)(playerlist.size()+1));
    for (int i = 0;  i < this->columnCount(); i++)
    {
	this->setColumnWidth(i,width-3);
	this->horizontalHeaderItem(i)->setSizeHint(QSize(width,50));
    }
}

void LiveGameRoundTable::markCardMixer(bool fullscreen){

}

void LiveGameRoundTable::setFullscreen(){
    this->setStyleSheet(QString("QFrame{background-color:black; color: white; border-radius: 10px; margin-top: 10px;} QHeaderView::section {background-color: black;font-size: 30px; padding:2px;") +
                        "border-radius: 5px; margin-bottom: 2px; height: 65px;}"
                        "QScrollBar:vertical {"
                        "border: 1px solid black;"
                        "border-radius: 10px;"
                        "background: rgb(76,76,76);"
                        "width: 15px;"
                        "margin: 22px 0 22px 0;}"
                    "QScrollBar::handle:vertical {"
                        "background: rgb(135,135,135);"
                        "border-top: 2px;"
                        "border-bottom: 2px;}"
                        //"min-height: 20px;}"
                    "QScrollBar::add-line:vertical {"
                        "border: 1px solid black;"
                        "background: rgb(76,76,76);"
                        "height: 20px;"
                        "subcontrol-position: bottom;"
                        "subcontrol-origin: margin;}"
                    "QScrollBar::sub-line:vertical {"
                        "border: 1px solid black;"
                        "background: rgb(76,76,76);"
                        "height: 20px;"
                        //"subcontrol-position: bottom;"
                        "subcontrol-origin: margin;}"
                   "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
                        "height: 6px;"
                        "width: 7px;"
                       "background-image: url(:/graphics/styles/mac/scrollbar/fullscreen/scrollbar_arrowdown_fullscreen);}"
                    "QScrollBar::up-arrow:vertical{"
                         "height: 6px;"
                         "width: 7px;"
                         "background-image: url(:/graphics/styles/mac/scrollbar/fullscreen/scrollbar_arrowup_fullscreen);}"
                    "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
                        "background: none;}");
}

void LiveGameRoundTable::setNormalMode(){
    this->setStyleSheet("");
}
