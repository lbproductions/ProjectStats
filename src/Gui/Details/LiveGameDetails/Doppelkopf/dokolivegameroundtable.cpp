#include "dokolivegameroundtable.h"

#include "dokolivegameroundtableitem.h"
#include "dokolivegameroundtabledelegate.h"
#include "newdokoroundwidget.h"

#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/Doppelkopf/dokoround.h>
#include <Database/player.h>

#include <QMenu>
#include <QAction>

using namespace Gui::Details::LiveGameDetails::DokoLiveGameDetails;

DokoLiveGameRoundTable::DokoLiveGameRoundTable(Database::DokoLiveGame* livegame, QWidget *parent):
    LiveGameRoundTable(livegame,parent)
{
    fillWidget();

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(on_customContextMenuRequested(QPoint)));


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

    if(round->comment->value() != ""){
        QTableWidgetItem* item1 = new QTableWidgetItem("C");
        this->setItem(this->rowCount()-1,i+1,item1);
        item1->setToolTip(round->comment->value());
    }

    QTableWidgetItem* item1 = new QTableWidgetItem("");
    item1->setSizeHint(QSize(0,0));
    this->setVerticalHeaderItem(this->rowCount()-1,item1);

    this->scrollToBottom();
}

DokoLiveGameRoundTableItem* DokoLiveGameRoundTable::itemAtIndex(const QModelIndex& index)
{
    return static_cast<DokoLiveGameRoundTableItem*>(item(index.row(),index.column()));
}


void DokoLiveGameRoundTable::on_customContextMenuRequested(const QPoint &pos)
{
    int index = indexAt(pos).row();

    Database::Round* round = m_livegame->rounds->value(index);

    QMenu* contextMenu = new QMenu(this);

    QAction* editRoundAction = new QAction(contextMenu);
    editRoundAction->setText(tr("Edit round %1").arg(round->number->value()+1));
    editRoundAction->setData(qVariantFromValue(static_cast<void*>(round)));
    connect(editRoundAction,SIGNAL(triggered()),this,SLOT(on_editRoundActionTriggered()));
    contextMenu->addAction(editRoundAction);

    contextMenu->exec(mapToGlobal(QPoint(pos.x(),pos.y()+55)));
}


void DokoLiveGameRoundTable::on_editRoundActionTriggered()
{
    QAction* action = static_cast<QAction*>(sender());
    Database::DokoRound* round = static_cast<Database::DokoRound*>(action->data().value<void*>());

    NewDokoRoundWidget ndrw(round,static_cast<Database::DokoLiveGame*>(m_livegame.data()));
    ndrw.exec();
}
