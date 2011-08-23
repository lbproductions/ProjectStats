#include "livegamesettingswidget.h"
#include "ui_livegamesettingswidget.h"

#include <QSettings>

using namespace Gui::Details::LiveGameDetails;

LiveGameSettingsWidget::LiveGameSettingsWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LiveGameSettingsWidget)
{
    ui->setupUi(this);

    setWindowModality(Qt::WindowModal);

    QSettings settings;
    ui->checkBoxBeerWidget->setChecked(settings.value("LiveGameWidget/stateBeerWidget",true).toBool());
    ui->checkBoxGeneralInformation->setChecked(settings.value("LiveGameWidget/stateInfoBox",true).toBool());
    ui->checkBoxGraph->setChecked(settings.value("LiveGameWidget/stateGraph",true).toBool());
    ui->checkBoxPlayerStats->setChecked(settings.value("LiveGameWidget/statePlayerStats",true).toBool());
    ui->checkBoxRoundsTable->setChecked(settings.value("LiveGameWidget/stateRoundsTable",true).toBool());
    ui->checkBoxTotalPoints->setChecked(settings.value("LiveGameWidget/stateTotalPoints",true).toBool());
    ui->checkBoxComment->setChecked(settings.value("LiveGameWidget/stateComment",true).toBool());

    connect(ui->checkBoxBeerWidget,SIGNAL(clicked()),this,SIGNAL(settingsChanged()));
    connect(ui->checkBoxGeneralInformation,SIGNAL(clicked()),this,SIGNAL(settingsChanged()));
    connect(ui->checkBoxGraph,SIGNAL(clicked()),this,SIGNAL(settingsChanged()));
    connect(ui->checkBoxPlayerStats,SIGNAL(clicked()),this,SIGNAL(settingsChanged()));
    connect(ui->checkBoxRoundsTable,SIGNAL(clicked()),this,SIGNAL(settingsChanged()));
    connect(ui->checkBoxTotalPoints,SIGNAL(clicked()),this,SIGNAL(settingsChanged()));
    connect(ui->checkBoxComment,SIGNAL(clicked()),this,SIGNAL(settingsChanged()));
}

LiveGameSettingsWidget::~LiveGameSettingsWidget()
{
    delete ui;
}

bool LiveGameSettingsWidget::stateGraph(){
    return ui->checkBoxGraph->isChecked();
}

bool LiveGameSettingsWidget::stateRoundsTable(){
    return ui->checkBoxRoundsTable->isChecked();
}

bool LiveGameSettingsWidget::statePlayerStats(){
    return ui->checkBoxPlayerStats->isChecked();
}

bool LiveGameSettingsWidget::stateTotalPoints(){
    return ui->checkBoxTotalPoints->isChecked();
}

bool LiveGameSettingsWidget::stateBeerWidget(){
    return ui->checkBoxBeerWidget->isChecked();
}

bool LiveGameSettingsWidget::stateInfoBox(){
    return ui->checkBoxGeneralInformation->isChecked();
}

bool LiveGameSettingsWidget::stateComment(){
    return ui->checkBoxComment->isChecked();
}

void Gui::Details::LiveGameDetails::LiveGameSettingsWidget::on_pushButtonClose_clicked()
{
    this->reject();
}
