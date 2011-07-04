#include "wizardsidewidget.h"
#include "ui_wizardsidewidget.h"

#include <QPalette>

using namespace Gui::Wizards::NewGame;

WizardSideWidget::WizardSideWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WizardSideWidget)
{
    ui->setupUi(this);


    QString text = ui->labelChoose->text();
    ui->labelChoose->setText("<font color='gray'>"+text+"</font>");
    text = ui->labelLive->text();
    ui->labelLive->setText("<font color='gray'>"+text+"</font>");
    text = ui->labelLiveGame->text();
    ui->labelLiveGame->setText("<font color='gray'>"+text+"</font>");
    text = ui->labelLiveGeneral->text();
    ui->labelLiveGeneral->setText("<font color='gray'>"+text+"</font>");
    text = ui->labelLiveOffline->text();
    ui->labelLiveOffline->setText("<font color='gray'>"+text+"</font>");
    text = ui->labelLiveSummary->text();
    ui->labelLiveSummary->setText("<font color='gray'>"+text+"</font>");
    text = ui->labelOffline->text();
    ui->labelOffline->setText("<font color='gray'>"+text+"</font>");
    text = ui->labelOfflineGame->text();
    ui->labelOfflineGame->setText("<font color='gray'>"+text+"</font>");
    text = ui->labelOfflineGeneral->text();
    ui->labelOfflineGeneral->setText("<font color='gray'>"+text+"</font>");
    text = ui->labelOfflineResult->text();
    ui->labelOfflineResult->setText("<font color='gray'>"+text+"</font>");

}

WizardSideWidget::~WizardSideWidget()
{
    delete ui;
}
