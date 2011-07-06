#include "offlinesummarywidget.h"
#include "ui_offlinesummarywidget.h"

#include "newgamewizard.h"

#include <Database/game.h>
#include <Database/place.h>
#include <Database/Doppelkopf/dokoofflinegame.h>
#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/player.h>

using namespace Gui::Wizards::NewGame;

OfflineSummaryWidget::OfflineSummaryWidget(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::OfflineSummaryWidget)
{
    ui->setupUi(this);

    this->setFinalPage(true);

    this->setTitle(tr("Summary"));
}

OfflineSummaryWidget::~OfflineSummaryWidget()
{
    delete ui;
}

int OfflineSummaryWidget::nextId() const
{
    return -1;
}

void OfflineSummaryWidget::initializePage()
{
    bool detailled = field("DetailledOfflineGame").toBool();

    ui->labelComment->setText(field("comment").toString());
    ui->labelDate->setText(field("date").toDate().toString("dd.MM.yyyy"));
    ui->labelResidence->setText(field("place").toString());
    ui->labelType->setText(field("type").toString());
    ui->groupBox->setTitle(field("name").toString());

    int compareRow = 0;
    while(compareRow<ui->gridLayoutPositions->rowCount())
    {
        if (ui->gridLayoutPositions->itemAtPosition(compareRow,0) != 0)
        {
            ui->gridLayoutPositions->itemAtPosition(compareRow,0)->widget()->setVisible(false);
            ui->gridLayoutPositions->removeWidget(ui->gridLayoutPositions->itemAtPosition(compareRow,0)->widget());
        }
        if (ui->gridLayoutPositions->itemAtPosition(compareRow,1) != 0)
        {
            ui->gridLayoutPositions->itemAtPosition(compareRow,1)->widget()->setVisible(false);
            ui->gridLayoutPositions->removeWidget(ui->gridLayoutPositions->itemAtPosition(compareRow,1)->widget());
        }
        compareRow++;
    }

    for (int i = 0; i<field("OfflineGame_PlayerNumber").toInt();i++)
    {
        ui->gridLayoutPositions->addWidget(new QLabel(QString::number(i+1) + ". " + field(QString("player%1").arg(i+1)).toString(),this),i,0);
    }

    ui->groupBox_2->setEnabled(!detailled);
    ui->groupBox_2->setEnabled(detailled && field("type").toString() == Database::DokoLiveGame::TYPE);
}
