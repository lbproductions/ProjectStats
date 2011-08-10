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
    setupDrinkTab();
    setupGeneralTab();
}

void LiveGameSummaryWidget::setupDrinkTab(){
    if(!m_livegame->drinks->value().isEmpty()){
        QWidget* drinkwidget = new QWidget(this);
        QGridLayout* drinklayout = new QGridLayout();
        drinklayout->addWidget(new QLabel(tr("Drunken Drinks:")),0,0);

        QGridLayout* useddrinks = new QGridLayout();
        if (m_livegame->drinks->value().isEmpty()){
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

        if (!m_livegame->drinks->value().isEmpty()){
            QGridLayout* layout = new QGridLayout();
            for(int i = 0; i<m_livegame->playersSortedByAlcPegel->value().size();i++){
                if(m_livegame->playersSortedByAlcPegel->value(i)->alcPegel->value(m_livegame) > 0.0){
                    QLabel* avatar = new QLabel(this);
                    avatar->setPixmap(QPixmap(m_livegame->playersSortedByAlcPegel->value(i)->avatarPath->value()).scaled(40,45,Qt::KeepAspectRatio,Qt::SmoothTransformation));
                    layout->addWidget(avatar,i,0);
                    QLabel* label = new QLabel(m_livegame->playersSortedByAlcPegel->value(i)->name->value() + " (" + QString::number(m_livegame->playersSortedByAlcPegel->value(i)->alcPegel->value(m_livegame)) + ")");
                    layout->addWidget(label,i,1);
                }
            }

            drinklayout->addLayout(layout,1,1);
        }
        else{
            drinklayout->addWidget(new QLabel("-"),1,1);
        }

        drinkwidget->setLayout(drinklayout);
        ui->tabWidget->addTab(drinkwidget,tr("Drinks"));
    }
}

void LiveGameSummaryWidget::setupGeneralTab(){
    for(int i = 0; i<m_livegame->playersSortedByPlacement->value().size();i++){
        QLabel* points = new QLabel(QString::number(m_livegame->points->value(m_livegame->playersSortedByPlacement->value(i))));
        points->setAlignment(Qt::AlignCenter);
        m_labelList.append(points);

        double perc = 100* (double)m_livegame->leadingRounds->value(m_livegame->playersSortedByPlacement->value(i)) / (double)m_livegame->roundCount->value();
        QLabel* leadPercentage = new QLabel(QString::number((int)perc)+"%");
        leadPercentage->setAlignment(Qt::AlignCenter);
        m_labelList.append(leadPercentage);

        QLabel* averagePos = new QLabel(QString::number(m_livegame->averagePlacement->value(m_livegame->playersSortedByPlacement->value(i))));
        averagePos->setAlignment(Qt::AlignCenter);
        m_labelList.append(averagePos);

        if(i<3){
            QFont font = points->font();
            font.setBold(true);
            font.setPointSize(14);
            points->setFont(font);
            leadPercentage->setFont(font);
            averagePos->setFont(font);
        }
        static_cast<QGridLayout*>(ui->tab->layout())->addWidget(points,i+1,2);
        static_cast<QGridLayout*>(ui->tab->layout())->addWidget(leadPercentage,i+1,3);
        static_cast<QGridLayout*>(ui->tab->layout())->addWidget(averagePos,i+1,4);
    }

    QLabel* pointsHeader = new QLabel(tr("Points"));
    pointsHeader->setAlignment(Qt::AlignCenter);
    QFont font = pointsHeader->font();
    font.setPointSize(9);
    pointsHeader->setFont(font);
    m_labelList.append(pointsHeader);
    static_cast<QGridLayout*>(ui->tab->layout())->addWidget(pointsHeader,0,2);

    QLabel* leadHeader = new QLabel(tr("Leadership"));
    leadHeader->setAlignment(Qt::AlignCenter);
    leadHeader->setFont(font);
    m_labelList.append(leadHeader);
    static_cast<QGridLayout*>(ui->tab->layout())->addWidget(leadHeader,0,3);

    QLabel* averageHeader = new QLabel(tr("AveragePosition"));
    averageHeader->setAlignment(Qt::AlignCenter);
    averageHeader->setFont(font);
    m_labelList.append(averageHeader);
    static_cast<QGridLayout*>(ui->tab->layout())->addWidget(averageHeader,0,4);
}

} // namespace LiveGameDetails
} // namespace Details
} // namespace Gui
