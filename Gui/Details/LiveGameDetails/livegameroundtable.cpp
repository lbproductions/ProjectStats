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

void LiveGameRoundTable::markCardMixer(bool /*fullscreen*/)
{

}
