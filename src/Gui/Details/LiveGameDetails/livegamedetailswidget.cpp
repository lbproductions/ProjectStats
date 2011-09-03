#include "livegamedetailswidget.h"

#include "beerwidget.h"
#include "livegameroundtable.h"
#include "livegameinfogroupbox.h"

#include <Database/livegame.h>
#include <Database/player.h>
#include <Gui/Misc/splitter.h>
#include <Gui/Misc/groupbox.h>
#include <Gui/Graphs/livegamegraphview.h>

#include <Misc/global.h>
#include <Misc/messagesystem.h>
#include <Misc/handler.h>

#include <QFile>
#include <QSettings>
#include <QLabel>
#include <QDebug>
#include <QTableWidgetItem>
#include <QVBoxLayout>

using namespace Gui::Details::LiveGameDetails;

LiveGameDetailsWidget::LiveGameDetailsWidget(Database::LiveGame* livegame, QWidget* widget):
    DetailsWidget(livegame,widget),
    m_livegame(livegame),
    m_playerTotalPointsTable(0)
{
    this->setAutoFillBackground(true);
    this->setBackgroundRole(QPalette::Background);
    QPalette p(this->palette());
    p.setColor(QPalette::Background, QColor(55,55,55));
    this->setPalette(p);

    connect(livegame->currentRound,SIGNAL(changed()),this,SLOT(on_currentRoundChanged()));
    connect(livegame->points,SIGNAL(changed()),this,SLOT(fillWidget()));
}

void LiveGameDetailsWidget::initializeItems()
{
    m_playerTotalPointsTable = new QTableWidget(1,m_livegame->playersSortedByPosition->value().size()+1);

    if (m_roundTable.isNull())
    {
        m_roundTable = new LiveGameDetails::LiveGameRoundTable(m_livegame,this);
    }
    if (m_infoBox.isNull())
    {
        m_infoBox = new LiveGameDetails::LiveGameInfoGroupBox(m_livegame,this);
    }
    if(m_graph.isNull())
    {
        m_graph = new Gui::Graphs::LiveGameGraphView(this);
        m_graph->setLiveGame(m_livegame);
        m_graph->setFullscreen();
    }
}

void LiveGameDetailsWidget::setupWidget()
{
    QSplitter* centralSplitter = new QSplitter(Qt::Vertical,this);
    centralSplitter->addWidget(new Gui::Misc::GroupBox(m_roundTable));
    Gui::Misc::GroupBox* totalPointsGroupBox = new Gui::Misc::GroupBox(m_playerTotalPointsTable);
    totalPointsGroupBox->setMaximumHeight(60);
    centralSplitter->addWidget(totalPointsGroupBox);
    centralSplitter->addWidget(new Gui::Misc::GroupBox(m_graph));
    centralSplitter->setStretchFactor(0,1);
    centralSplitter->setStretchFactor(1,0);
    centralSplitter->setStretchFactor(2,2);

    QWidget* centralWidget = new QWidget();
    QLayout* centralLayout = new QVBoxLayout(this);
    centralLayout->setSpacing(0);
    centralLayout->setContentsMargins(12,12,12,12);
    centralLayout->addWidget(centralSplitter);
    centralWidget->setLayout(centralLayout);

    Gui::Misc::Splitter* leftSplitter = new Gui::Misc::Splitter(Qt::Horizontal);
    leftSplitter->setFullscreen(true);
    leftSplitter->setLeftToRight(true);
    leftSplitter->addWidget(new BeerWidget(m_livegame,leftSplitter));
    leftSplitter->addWidget(centralWidget);
    leftSplitter->setStretchFactor(0,0);
    leftSplitter->setStretchFactor(1,1);

    Gui::Misc::Splitter* rightSplitter = new Gui::Misc::Splitter(Qt::Horizontal);
    rightSplitter->setFullscreen(true);
    rightSplitter->addWidget(leftSplitter);
    rightSplitter->addWidget(m_infoBox);
    rightSplitter->setStretchFactor(0,1);
    rightSplitter->setStretchFactor(1,0);

    QLayout* l = new QVBoxLayout(this);
    l->setSpacing(0);
    l->setContentsMargins(0,0,0,0);
    l->addWidget(rightSplitter);
    setLayout(l);

    m_playerTotalPointsTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_playerTotalPointsTable->setGridStyle(Qt::NoPen);
    for (int i = 0; i<m_playerTotalPointsTable->columnCount();i++)
    {
         m_playerTotalPointsTable->setColumnWidth(i, ((double)m_roundTable->columnWidth(0)));

         QTableWidgetItem* item = new QTableWidgetItem("");
         item->setSizeHint(QSize(0,0));
         item->setTextAlignment(Qt::AlignCenter);
         item->setFont(QFont("Lucia Grande",35,QFont::Bold,false));
         m_playerTotalPointsTable->setHorizontalHeaderItem(i,item);

         item = new QTableWidgetItem("");
         item->setTextAlignment(Qt::AlignCenter);
         item->setFont(QFont("Lucia Grande",35,QFont::Bold,false));
         item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
         m_playerTotalPointsTable->setItem(0,i,item);
    }
    m_playerTotalPointsTable->setRowHeight(0,35);
    m_playerTotalPointsTable->setMaximumHeight(m_playerTotalPointsTable->rowHeight(0));
    QTableWidgetItem* item = new QTableWidgetItem("0");
    item->setSizeHint(QSize(0,0));
    item->setTextAlignment(Qt::AlignCenter);
    item->setFont(QFont("Lucia Grande",35,QFont::Bold,false));
    m_playerTotalPointsTable->setVerticalHeaderItem(0,item);
    m_playerTotalPointsTable->setStyleSheet("QWidget{margin: 0px; padding: 0px; background:transparent; color: white;}");
    updateSizes();
}

void LiveGameDetailsWidget::fillWidget()
{
    for (int i = 0; i < m_livegame->players->value().size(); i++)
    {
        m_playerTotalPointsTable->item(0,i)->setText(QString::number(m_livegame->points->value(m_livegame->playersSortedByPosition->value().at(i))));
    }

    m_playerTotalPointsTable->item(0,m_livegame->players->value().size())->setText(QString::number(m_livegame->totalPoints->value()));
}

void LiveGameDetailsWidget::on_currentRoundChanged()
{
    connect(m_livegame->currentRound->value()->points,SIGNAL(changed()),this,SLOT(fillWidget()));
    fillWidget();
}

void LiveGameDetailsWidget::updateSizes()
{
    if (m_playerTotalPointsTable){
        for (int i = 0; i < m_playerTotalPointsTable->columnCount();i++)
        {
             m_playerTotalPointsTable->setColumnWidth(i, m_roundTable->columnWidth(i));
        }
    }
}

void LiveGameDetailsWidget::resizeEvent(QResizeEvent* /*event*/)
{
    updateSizes();
}
