#include "livegamesummarywidget.h"
#include "ui_gamesummarywidget.h"

#include <Database/livegame.h>
#include <Database/player.h>
#include <Database/drink.h>
#include <Stats/PlayerStats/generalplayerstats.h>

#include <QLabel>
#include <QGridLayout>
#include <QDebug>

using namespace Gui::Details::LiveGameDetails;

LiveGameSummaryWidget::LiveGameSummaryWidget(Database::LiveGame* game, QWidget *parent):
    GameSummaryWidget(game,parent),
    m_livegame(game)
{
    initData();
    createDrinkTab();
}


bool sortToAlcPegel(QPair<Database::Player*,Database::LiveGame*> p1, QPair<Database::Player*,Database::LiveGame*> p2){
    return p1.first->generalStats()->alcPegel(p1.second) > p2.first->generalStats()->alcPegel(p2.second);
}

bool sortToDrinkCount(QPair<Database::Player*,Database::LiveGame*> p1, QPair<Database::Player*,Database::LiveGame*> p2){
    return p1.second->drinks(p1.first).size() > p2.second->drinks(p2.first).size();
}

void LiveGameSummaryWidget::initData(){
    foreach(Database::Player* p, m_livegame->playersSortedByPlacement()){
        QPair<Database::Player*,Database::LiveGame*> pair;
        pair.first = p;
        pair.second = m_livegame;
        m_drunkenplayer.append(pair);
        m_mostdrinks.append(pair);
    }
    qSort(m_drunkenplayer.begin(),m_drunkenplayer.end(),sortToAlcPegel);
    qSort(m_mostdrinks.begin(),m_mostdrinks.end(),sortToDrinkCount);

    for(int i = 0; i<m_livegame->playersSortedByPlacement().size();i++){
        QLabel* points = new QLabel(QString::number(m_livegame->points(m_livegame->playersSortedByPlacement().at(i))));
        points->setAlignment(Qt::AlignCenter);

        if(i<2){
            QFont font = points->font();
            font.setBold(true);
            font.setPointSize(14);
            points->setFont(font);
        }

        foreach(Database::Drink* d, m_livegame->drinks(m_livegame->playersSortedByPlacement().at(i))){
            if (!m_drinklist.contains(d)){
                m_drinklist.append(d);
            }
        }

        static_cast<QGridLayout*>(ui->tab->layout())->addWidget(points,i,2);
    }
}

void LiveGameSummaryWidget::createDrinkTab(){

    QWidget* drinkwidget = new QWidget(this);
    QGridLayout* drinklayout = new QGridLayout();
    drinklayout->addWidget(new QLabel(tr("Drunken Drinks:")),0,0);

    QGridLayout* useddrinks = new QGridLayout();
    if (m_drinklist.isEmpty()){
        QLabel* label = new QLabel(tr("Nothing was drunk."));
        useddrinks->addWidget(label,0,0);
    }
    else{
        int j = 0;
        foreach(Database::Drink* d, m_drinklist){
            QLabel* icon = new QLabel(this);
            icon->setPixmap(d->icon().scaled(20,45,Qt::KeepAspectRatio,Qt::SmoothTransformation));
            QLabel* name = new QLabel(d->name(),this);
            useddrinks->addWidget(icon,j,0);
            useddrinks->addWidget(name,j,1);
            j++;
        }
    }
    drinklayout->addLayout(useddrinks,0,1);

    drinklayout->addWidget(new QLabel(tr("Most drunken player:")),1,0);

    if(m_drunkenplayer.at(0).first->generalStats()->alcPegel(m_livegame) > 0.0){
        QGridLayout* layout = new QGridLayout();
        for(int i = 0; i<m_drunkenplayer.size();i++){
            if (m_drunkenplayer.at(i).first->generalStats()->alcPegel(m_livegame) == m_drunkenplayer.at(0).first->generalStats()->alcPegel(m_livegame)){
                QLabel* avatar = new QLabel(this);
                if(m_drunkenplayer.at(i).first->avatarFilePath() != ""){
                    avatar->setPixmap(m_drunkenplayer.at(i).first->avatar().scaled(40,45,Qt::KeepAspectRatio,Qt::SmoothTransformation));
                }
                else{
                    QPixmap pixmap;
                    pixmap.load(":/graphics/images/player");
                    avatar->setPixmap(pixmap.scaled(40,45,Qt::KeepAspectRatio,Qt::SmoothTransformation));
                }
                layout->addWidget(avatar,i,0);
                QLabel* label = new QLabel(m_drunkenplayer.at(i).first->name() + " (" + QString::number(m_drunkenplayer.at(i).first->generalStats()->alcPegel(m_livegame)) + ")");
                layout->addWidget(label,i,1);
            }
        }
        drinklayout->addLayout(layout,1,1);
    }
    else{
        drinklayout->addWidget(new QLabel("-"),1,1);
    }

    drinklayout->addWidget(new QLabel(tr("Most drinks:")),2,0);
    if(m_livegame->drinks(m_mostdrinks.at(0).first).size() > 0){
        QGridLayout* layout = new QGridLayout();
        for(int i = 0; i<m_mostdrinks.size();i++){
            if (m_livegame->drinks(m_mostdrinks.at(i).first).size() == m_livegame->drinks(m_mostdrinks.at(0).first).size()){
                QLabel* avatar = new QLabel(this);
                if(m_mostdrinks.at(i).first->avatarFilePath() != ""){
                    avatar->setPixmap(m_mostdrinks.at(i).first->avatar().scaled(40,45,Qt::KeepAspectRatio,Qt::SmoothTransformation));
                }
                else{
                    QPixmap pixmap;
                    pixmap.load(":/graphics/images/player");
                    avatar->setPixmap(pixmap.scaled(40,45,Qt::KeepAspectRatio,Qt::SmoothTransformation));
                }
                layout->addWidget(avatar,i,0);
                QLabel* label = new QLabel(m_mostdrinks.at(i).first->name() + " (" + QString::number(m_livegame->drinks(m_mostdrinks.at(i).first).size()) + ")");
                layout->addWidget(label,i,1);
            }
        }
        drinklayout->addLayout(layout,2,1);
    }
    else{
        drinklayout->addWidget(new QLabel("-"),2,1);
    }

    drinkwidget->setLayout(drinklayout);
    ui->tabWidget->addTab(drinkwidget,tr("Drinks"));
}
