#include "livegameroundtable.h"

#include <Database/player.h>
#include <Database/Doppelkopf/dokoround.h>
#include <Database/Doppelkopf/dokolivegame.h>
#include <Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamedetailswidget.h>

#include <QDebug>

using namespace Gui::Details::LiveGameDetails;

LiveGameRoundTable::LiveGameRoundTable(Database::LiveGame* livegame, QWidget *parent) :
    QTableWidget(parent),
    m_livegame(livegame)
{
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

    markCardMixer();

    connect(livegame->cardmixer,SIGNAL(changed()),this,SLOT(markCardMixer()));
    connect(livegame->currentRound,SIGNAL(changed()),this,SLOT(addCurrentRound()));
}

void LiveGameRoundTable::fillWidget()
{
    foreach(Database::Round* round, m_livegame->rounds->value())
    {
        if(round->state->value() == Database::Round::FinishedState)
        {
            addRound(round);
        }
    }
}

void LiveGameRoundTable::addCurrentRound()
{
    addRound(m_livegame->currentRound->value());
}

void LiveGameRoundTable::addRound(Database::Round* /*round*/)
{
}

void LiveGameRoundTable::updateSizes()
{
    double width = ((double)this->width() / (double)(m_livegame->players->value().size()+1));
    for (int i = 0;  i < this->columnCount(); i++)
    {
        this->setColumnWidth(i,width-3);
        this->horizontalHeaderItem(i)->setSizeHint(QSize(width,50));
    }
}

void LiveGameRoundTable::resizeEvent(QResizeEvent* /*event*/)
{
    updateSizes();
}

void LiveGameRoundTable::markCardMixer()
{
    if(!m_livegame->cardmixer->value())
    {
        return;
    }

    for (int i = 0; i<this->columnCount();i++)
    {
        if (m_livegame->state->value() != Database::Round::FinishedState &&
                this->horizontalHeaderItem(i)->text() == m_livegame->cardmixer->value()->name->value())
        {
            this->horizontalHeaderItem(i)->setTextColor(QColor("red"));
        }
        else
        {
            this->horizontalHeaderItem(i)->setTextColor(QColor("white"));
        }
    }
}
