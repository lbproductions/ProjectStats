#include "dokoplayerstatsgroupbox.h"
#include "ui_dokoplayerstatsgroupbox.h"

#include <Database/player.h>
#include <Database/Doppelkopf/dokolivegame.h>

#include "dokoplayerstatsroundbox.h"
#include "dokoplayerstatsspecialstats.h"

#include <QMouseEvent>

using namespace Gui::Details::LiveGameDetails::Sidebar;

DokoPlayerStatsGroupBox::DokoPlayerStatsGroupBox(Database::DokoLiveGame *dokoLiveGame, Database::Player *player, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DokoPlayerStatsGroupBox),
    m_player(player),
    m_dokoLiveGame(dokoLiveGame),
    m_clickCounter(0),
    m_rightClickMode(false)
{
    ui->setupUi(this);

    player->name->futureWatcher()->connectTo(ui->labelName);
    if (player->avatarPath->value() != ""){
        ui->labelAvatar->setPixmap(player->avatarPath->value());
    }

    ui->verticalLayoutBox->addWidget(new DokoPlayerStatsRoundBox(dokoLiveGame,player,this));
}

DokoPlayerStatsGroupBox::~DokoPlayerStatsGroupBox()
{
    delete ui;
}

void DokoPlayerStatsGroupBox::mouseReleaseEvent ( QMouseEvent * event ){

    QLayoutItem* item;
    while ( ( item = ui->verticalLayoutBox->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }

    if(event->button() == Qt::RightButton){
        m_rightClickMode = !m_rightClickMode;
        if(!m_rightClickMode){
            if(m_clickCounter == 0){
                ui->verticalLayoutBox->addWidget(new DokoPlayerStatsRoundBox(m_dokoLiveGame,m_player,this));
            }
            else{
                ui->verticalLayoutBox->addWidget(new DokoPlayerStatsSpecialStats(m_dokoLiveGame,m_player,this));
            }
            QPixmap pixmap(90,64);
            pixmap.load(m_player->avatarPath->value());
            ui->labelAvatar->setPixmap(pixmap);
            ui->labelAvatar->setVisible(true);
        }
        else{
            QPixmap pixmap(45,32);
            pixmap.load(m_player->avatarPath->value());
            ui->labelAvatar->setPixmap(pixmap);
            ui->labelAvatar->setVisible(false);
        }
    }

    if(event->button() == Qt::LeftButton){
        if(m_clickCounter == 0){
            ui->verticalLayoutBox->addWidget(new DokoPlayerStatsSpecialStats(m_dokoLiveGame,m_player,this));
            m_clickCounter++;
        }
        else{
            ui->verticalLayoutBox->addWidget(new DokoPlayerStatsRoundBox(m_dokoLiveGame,m_player,this));
            m_clickCounter--;
        }
    }
}

void DokoPlayerStatsGroupBox::resizeEvent(QResizeEvent *){
    if(!m_rightClickMode){
        QPixmap pixmap(90,64);
        pixmap.load(m_player->avatarPath->value());
        ui->labelAvatar->setPixmap(pixmap);
    }
    else{
        QPixmap pixmap(45,32);
        pixmap.load(m_player->avatarPath->value());
        ui->labelAvatar->setPixmap(pixmap);
    }
}
