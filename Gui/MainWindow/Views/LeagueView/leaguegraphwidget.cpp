#include "leaguegraphwidget.h"

#include <Gui/Misc/splitter.h>
#include <Database/Categories/leaguefoldercategorie.h>
//#include <Gui/Graphs/playerplacementgraphview.h>

#include <QHBoxLayout>
#include <QScrollArea>
#include <QDebug>

using namespace Gui::MainWindow::Views::LeagueViewDetails;

LeagueGraphWidget::LeagueGraphWidget(Database::LeagueFolderCategorie *categorie, QWidget *parent) :
    QWidget(parent),
    m_categorie(categorie)
{
    setLayout(new QHBoxLayout(this));
    layout()->setContentsMargins(0,0,0,0);

    m_splitter = new Gui::Misc::Splitter(Qt::Horizontal,this);

    m_treeWidget = new QTreeWidget(this);
    m_treeWidget->setAlternatingRowColors(true);
    m_treeWidget->setHeaderHidden(true);

    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,"PlayerPlacement");
    m_treeWidget->addTopLevelItem(item);

    m_splitter->addWidget(m_treeWidget);

    m_scrollAreaDetails = new QScrollArea(m_splitter);
    m_scrollAreaDetails->setFrameStyle(QFrame::NoFrame);
    m_scrollAreaDetails->setAttribute(Qt::WA_MacShowFocusRect, false);
    m_scrollAreaDetails->setAutoFillBackground(true);
    m_scrollAreaDetails->setBackgroundRole(QPalette::Base);
    //m_scrollAreaDetails->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_scrollAreaDetails->setWidgetResizable(true);
    m_splitter->addWidget(m_scrollAreaDetails);

    layout()->addWidget(m_splitter);

    connect(m_treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(graphClicked(QTreeWidgetItem*)));
}

void LeagueGraphWidget::graphClicked(QTreeWidgetItem* item){
    /*
    if (item->text(0) == "PlayerPlacement"){
        m_graphview = new Gui::Graphs::PlayerPlacementGraphView(m_categorie->players(),m_categorie->games());
        m_scrollAreaDetails->setWidget(m_graphview);
    }
    */
}
