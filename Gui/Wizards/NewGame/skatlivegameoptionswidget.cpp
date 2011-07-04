#include "skatlivegameoptionswidget.h"
#include "ui_skatlivegameoptionswidget.h"

#include <Database/Skat/skatlivegame.h>

#include <QSettings>
#include <QMessageBox>

#include "newgamewizard.h"

using namespace Gui::Wizards::NewGame;

SkatLiveGameOptionsWidget::SkatLiveGameOptionsWidget(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::SkatLiveGameOptionsWidget)
{
    ui->setupUi(this);

    QSettings settings;
    ui->checkBoxMitRamschen->setChecked(settings.value("GameWizard/SkatLiveGameOptions/mitRamschen").toBool());

    ui->radioButtonPoints->setChecked(settings.value("GameWizard/SkatLiveGameOptions/EndGamePoints").toBool());
    ui->spinBoxPoints->setEnabled(settings.value("GameWizard/SkatLiveGameOptions/EndGamePoints").toBool());
    ui->spinBoxPoints->setValue(settings.value("GameWizard/SkatLiveGameOptions/EndGamePointsValue").toInt());

    ui->radioButtonRounds->setChecked(settings.value("GameWizard/SkatLiveGameOptions/EndGameRounds").toBool());
    ui->spinBoxRounds->setEnabled(settings.value("GameWizard/SkatLiveGameOptions/EndGameRounds").toBool());
    ui->spinBoxRounds->setValue(settings.value("GameWizard/SkatLiveGameOptions/EndGameRoundsValue").toInt());

    ui->radioButtonNever->setChecked(settings.value("GameWizard/SkatLiveGameOptions/EndGameNever").toBool());

    ui->buttonGroup->addButton(ui->radioButtonPoints);
    ui->buttonGroup->addButton(ui->radioButtonRounds);
    ui->buttonGroup->addButton(ui->radioButtonNever);

    registerField("skat_mitRamschen",ui->checkBoxMitRamschen);
    registerField("skat_endGamePoints",ui->radioButtonPoints);
    registerField("skat_endGamePointsValue",ui->spinBoxPoints);
    registerField("skat_endGameRounds",ui->radioButtonRounds);
    registerField("skat_endGameRoundsValue",ui->spinBoxRounds);
    registerField("skat_endGameNever",ui->radioButtonRounds);

    setTitle(tr("Advanced Skat Options"));
    setSubTitle(tr("Refine the options for this game:"));
}

SkatLiveGameOptionsWidget::~SkatLiveGameOptionsWidget()
{
    saveOptions();
    delete ui;
}

bool SkatLiveGameOptionsWidget::isComplete() const
{
    saveOptions();
}

int SkatLiveGameOptionsWidget::nextId() const
{
    saveOptions();
    return -1;
}

void SkatLiveGameOptionsWidget::saveOptions() const
{
    QSettings settings;
    settings.setValue("GameWizard/SkatLiveGameOptions/mitRamschen",ui->checkBoxMitRamschen->isChecked());
    settings.setValue("GameWizard/SkatLiveGameOptions/EndGamePoints",ui->radioButtonPoints->isChecked());
    settings.setValue("GameWizard/SkatLiveGameOptions/EndGamePointsValue",ui->spinBoxPoints->value());
    settings.setValue("GameWizard/SkatLiveGameOptions/EndGameRounds",ui->radioButtonRounds->isChecked());
    settings.setValue("GameWizard/SkatLiveGameOptions/EndGameRoundsValue",ui->spinBoxRounds->value());
    settings.setValue("GameWizard/SkatLiveGameOptions/EndGameNever",ui->radioButtonNever->isChecked());
}

void Gui::Wizards::NewGame::SkatLiveGameOptionsWidget::on_buttonGroup_buttonClicked(int /*id*/)
{
    ui->spinBoxPoints->setEnabled(ui->radioButtonPoints->isChecked());
    ui->spinBoxRounds->setEnabled(ui->radioButtonRounds->isChecked());
}
