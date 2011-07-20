#include "livegamesummarywidget.h"
#include "ui_gamesummarywidget.h"

#include <Database/livegame.h>
#include <Database/livegamedrink.h>
#include <Database/drink.h>

#include <QGridLayout>

namespace Gui {
namespace Details {
namespace LiveGameDetails {

LiveGameSummaryWidget::LiveGameSummaryWidget(Database::LiveGame* game, QWidget *parent):
    GameSummaryWidget(game,parent),
    m_livegame(game)
{
    if(!m_livegame->drinks->value().isEmpty()){
        QWidget* drinkwidget = new QWidget(this);
        QGridLayout* drinklayout = new QGridLayout();
        drinklayout->addWidget(new QLabel(tr("Drunken Drinks:")),0,0);

        QGridLayout* useddrinks = new QGridLayout();
        if (game->drinks->value().isEmpty()){
            QLabel* label = new QLabel(tr("Nothing was drunk."));
            useddrinks->addWidget(label,0,0);
        }
        else{
            int j = 0;
            foreach(Database::Drink* d, m_livegame->drinkCount->value().keys()){
                QLabel* icon = new QLabel(this);
                icon->setPixmap(QPixmap(d->iconPath->value()).scaled(20,45,Qt::KeepAspectRatio,Qt::SmoothTransformation));
                QLabel* name = new QLabel(d->name->value() + " (" + QString::number(m_livegame->drinkCount->value(d)) +")",this);
                useddrinks->addWidget(icon,j,0);
                useddrinks->addWidget(name,j,1);
                j++;
            }
        }
        drinklayout->addLayout(useddrinks,0,1);

        drinklayout->addWidget(new QLabel(tr("Drunken players:")),1,0);

        if (!game->drinks->value().isEmpty()){
            QGridLayout* layout = new QGridLayout();
            for(int i = 0; i<m_livegame->playersSortedByAlcPegel->value().size();i++){
                QLabel* avatar = new QLabel(this);
                avatar->setPixmap(QPixmap(m_livegame->playersSortedByAlcPegel->value(i)->avatarPath->value()).scaled(40,45,Qt::KeepAspectRatio,Qt::SmoothTransformation));
                layout->addWidget(avatar,i,0);
                QLabel* label = new QLabel(m_livegame->playersSortedByAlcPegel->value(i)->name->value() + " (" + QString::number(m_livegame->playersSortedByAlcPegel->value(i)->alcPegel->value(m_livegame)) + ")");
                layout->addWidget(label,i,1);
            }

            drinklayout->addLayout(layout,1,1);
        }
        else{
            drinklayout->addWidget(new QLabel("-"),1,1);
        }

        /*
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
    */

        drinkwidget->setLayout(drinklayout);
        ui->tabWidget->addTab(drinkwidget,tr("Drinks"));
    }

    for(int i = 0; i<m_livegame->playersSortedByPlacement->value().size();i++){
            QLabel* points = new QLabel(QString::number(m_livegame->points->value(m_livegame->playersSortedByPlacement->value(i))));
            points->setAlignment(Qt::AlignCenter);

            if(i<3){
                QFont font = points->font();
                font.setBold(true);
                font.setPointSize(14);
                points->setFont(font);
            }

            static_cast<QGridLayout*>(ui->tab->layout())->addWidget(points,i,2);
        }
}

} // namespace LiveGameDetails
} // namespace Details
} // namespace Gui
