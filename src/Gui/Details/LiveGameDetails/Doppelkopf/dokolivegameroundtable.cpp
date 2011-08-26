#include "dokolivegameroundtable.h"

#include "dokolivegameroundtableitem.h"
#include "dokolivegameroundtabledelegate.h"

#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/Doppelkopf/dokoround.h>
#include <Database/player.h>

using namespace Gui::Details::LiveGameDetails::DokoLiveGameDetails;

DokoLiveGameRoundTable::DokoLiveGameRoundTable(Database::DokoLiveGame* livegame, QWidget *parent):
    LiveGameRoundTable(livegame,parent)
{
    fillWidget();

    this->setItemDelegate(new DokoLiveGameRoundTableDelegate(this));
}

void DokoLiveGameRoundTable::addRound(::Database::Round* round)
{
    Database::DokoRound* dokoround = static_cast<Database::DokoRound*>(round);

    this->insertRow(this->rowCount());
    int i = 0;
    foreach(Database::Player* p, m_livegame->playersSortedByPosition->value())
    {
        DokoLiveGameRoundTableItem* item = new DokoLiveGameRoundTablePlayerItem(p,dokoround);
        this->setItem(this->rowCount()-1,i,item);
        ++i;
    }


    DokoLiveGameRoundTableItem* item = new DokoLiveGameRoundTableTotalPointsItem(dokoround);
    this->setItem(this->rowCount()-1,i,item);

    QTableWidgetItem* item1 = new QTableWidgetItem("");
    item1->setSizeHint(QSize(0,0));
    this->setVerticalHeaderItem(this->rowCount()-1,item1);

    this->scrollToBottom();
}

DokoLiveGameRoundTableItem* DokoLiveGameRoundTable::itemAtIndex(const QModelIndex& index)
{
    return static_cast<DokoLiveGameRoundTableItem*>(item(index.row(),index.column()));
}
