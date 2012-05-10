#include "sidebarcontroller.h"
#include "ui_sidebarcontroller.h"

#include "sidebarpage.h"

#include <Database/livegame.h>
#include <Database/Doppelkopf/dokolivegame.h>

#include <Gui/Details/LiveGameDetails/Doppelkopf/dokolivegameinfogroupbox.h>
#include "Doppelkopf/dokoplayerpairpage.h"
#include "Doppelkopf/dokoplayerstatspage.h"
#include "commentsidebarpage.h"

using namespace Gui::Details::LiveGameDetails::Sidebar;

SidebarController::SidebarController(Database::LiveGame* liveGame, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SidebarController),
    m_pageCounter(0),
    m_liveGame(liveGame)
{
    ui->setupUi(this);

    currentPageChanged();
}

SidebarController::~SidebarController()
{
    delete ui;
}

void SidebarController::setupWidget()
{
    m_sides.clear();

    if(m_liveGame->type->value() == "Doppelkopf"){
        Gui::Details::LiveGameDetails::DokoLiveGameDetails::DokoLiveGameInfoGroupBox* groupBox =
                new Gui::Details::LiveGameDetails::DokoLiveGameDetails::DokoLiveGameInfoGroupBox(static_cast<Database::DokoLiveGame*>(m_liveGame), this);
        m_sides.append(groupBox);
    }
    else{
        Gui::Details::LiveGameDetails::LiveGameInfoGroupBox* groupBox1 = new Gui::Details::LiveGameDetails::LiveGameInfoGroupBox(m_liveGame,this);
        m_sides.append(groupBox1);
    }

    Gui::Details::LiveGameDetails::Sidebar::DokoPlayerStatsPage* playerStatsPage = new Gui::Details::LiveGameDetails::Sidebar::DokoPlayerStatsPage(static_cast<Database::DokoLiveGame*>(m_liveGame), this);
    m_sides.append(playerStatsPage);

    CommentSidebarPage* commentPage = new CommentSidebarPage(m_liveGame,this);
    m_sides.append(commentPage);

    Gui::Details::LiveGameDetails::Sidebar::DokoPlayerPairPage* pairPage = new Gui::Details::LiveGameDetails::Sidebar::DokoPlayerPairPage(static_cast<Database::DokoLiveGame*>(m_liveGame), this);
    m_sides.append(pairPage);  

}

void SidebarController::on_pushButtonLeft_clicked()
{
    m_pageCounter--;

    currentPageChanged();
}

void SidebarController::on_pushButtonRight_clicked()
{
    m_pageCounter++;

    currentPageChanged();
}

void SidebarController::currentPageChanged()
{
    QLayoutItem* item;
    while ( ( item = ui->verticalLayoutSide->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }

    setupWidget();

    m_sides.at(m_pageCounter)->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->verticalLayoutSide->addWidget(m_sides.at(m_pageCounter));

    if(m_pageCounter > 0){
        ui->pushButtonLeft->setEnabled(true);
    }
    else{
        ui->pushButtonLeft->setEnabled(false);
    }

    if(m_pageCounter >= m_sides.size()-1){
        ui->pushButtonRight->setEnabled(false);
    }
    else{
        ui->pushButtonRight->setEnabled(true);
    }
}
