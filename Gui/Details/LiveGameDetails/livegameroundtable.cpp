#include "livegameroundtable.h"

#include <Database/player.h>
#include <Database/Doppelkopf/dokoround.h>
#include <Database/Doppelkopf/dokolivegame.h>
#include <Gui/Details/LiveGameDetails/Doppelkopf/dokolivegamedetailswidget.h>

#include <QDebug>
#include <QHeaderView>

using namespace Gui::Details::LiveGameDetails;

LiveGameRoundTable::LiveGameRoundTable(Database::LiveGame* livegame, QWidget *parent) :
    QTableWidget(parent),
    m_livegame(livegame)
{
    setStyleSheet(QString(
                    "Gui--Details--LiveGameDetails--LiveGameRoundTable {"
                        "background:transparent;"
                        "color: white;"
                        "border: none;"
                        "margin: 0px;"
                        "font-weight: bold;"
                        "font-size: 20px;"
                    "}"
                      "QHeaderView {"
                          "background: transparent;"
                      "}"

                    "QHeaderView::section {"
                        "background: transparent;"
                        "font-size: 40px;"
                        "padding:2px;"
                        "border: none; "
                        "margin-bottom: 2px; "
                        "height: 55px;"
                    "}"

                    "QScrollBar:vertical {"
                        "background: transparent;"
                        "background-image: url(:/graphics/styles/mac/scrollbar/fullscreen/scrollbar_background_fullscreen);"
                        "background-repeat: repeat-y;"
                        "width: 15px;"
                        "margin: 15px 0 14px 0;"
                    "}"

                    "QScrollBar::handle:vertical {"
                        "border-image: url(:/graphics/styles/mac/scrollbar/fullscreen/scrollbar_handle_fullscreen) 7 0 7 0;"
                        "border-top: 7px transparent;"
                        "border-bottom: 7px transparent;"
                        "border-right: 0px transparent;"
                        "border-left: 0px transparent;"
                    "}"

                    "QScrollBar::add-line:vertical {"
                        "border: none;"
                        "background: none;"
                        "height: 24px;"
                        "subcontrol-position: bottom;"
                        "subcontrol-origin: margin;"
                     "}"

                    "QScrollBar::sub-line:vertical {"
                        "border: none;"
                        "background: none;"
                        "height: 24px;"
                        "subcontrol-position: top;"
                        "subcontrol-origin: margin;"
                     "}"

                    "QScrollBar::up-arrow:vertical {"
                        "height: 24px;"
                        "width: 15px;"
                        "background-image: url(:/graphics/styles/mac/scrollbar/fullscreen/scrollbar_arrowup_fullscreen);"
                    "}"
                    "QScrollBar::down-arrow:vertical {"
                        "height: 25px;"
                        "width: 15px;"
                        "background-image: url(:/graphics/styles/mac/scrollbar/fullscreen/scrollbar_arrowdown_fullscreen);"
                    "}"
                    "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
                        "background: none;"
                    "}"));

    this->setGridStyle(Qt::NoPen);

    foreach(Database::Player *player, m_livegame->playersSortedByPosition->value())
    {
	this->insertColumn(this->columnCount());
        QPixmap pixmap(140,140);
        pixmap.fill(player->color->value());
        this->setHorizontalHeaderItem(this->columnCount()-1,new QTableWidgetItem(QIcon(pixmap),player->name->value()));
    }

    this->insertColumn(this->columnCount());
    this->setHorizontalHeaderItem(this->columnCount()-1,new QTableWidgetItem(tr("")));

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    updateSizes();

    markCardMixer();

    connect(livegame->cardmixer,SIGNAL(changed()),this,SLOT(markCardMixer()));
    connect(livegame,SIGNAL(roundAdded(::Database::Round*)),this,SLOT(addRound(::Database::Round*)));
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

void LiveGameRoundTable::addRound(::Database::Round* /*round*/)
{
}

void LiveGameRoundTable::updateSizes()
{
    double width = ((double)this->width() / (double)(m_livegame->players->value().size()+0.3));
    for (int i = 0;  i < this->columnCount()-1; i++)
    {
        this->setColumnWidth(i,width-3);
        this->horizontalHeaderItem(i)->setSizeHint(QSize(width,50));
    }
    this->setColumnWidth(this->columnCount()-1, width / 3);
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
