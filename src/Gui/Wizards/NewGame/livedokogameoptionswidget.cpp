#include "livedokogameoptionswidget.h"
#include "ui_livedokogameoptionswidget.h"

#include "newgamewizard.h"

#include <Database/Doppelkopf/dokolivegame.h>
#include <Database/place.h>

#include <QSettings>

using namespace Gui::Wizards::NewGame;

LiveDokoGameOptionsWidget::LiveDokoGameOptionsWidget(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::LiveDokoGameOptionsWidget)
{
    ui->setupUi(this);

    this->setTitle("Doppelkopf Game Mechanics");

    registerField("doko_mitHochzeit",ui->checkBoxHochzeit);
    registerField("doko_mitSolo",ui->checkBoxSolo);
    registerField("doko_mitTrumpfabgabe",ui->checkBoxTrumpfabgabe);
    registerField("doko_mitSchmeisserei",ui->checkBoxSchmeisserei);
    registerField("doko_mitSchweinerei",ui->checkBoxSchweinerei);

    registerField("doko_mitBubenSolo",ui->checkBoxBuben);
    registerField("doko_mitDamenSolo",ui->checkBoxDamen);
    registerField("doko_mitFarbsolo",ui->checkBoxFarb);
    registerField("doko_mitFleischlos",ui->checkBoxFleischlos);
    registerField("doko_mitTrumpfsolo",ui->checkBoxTrumpf);
    registerField("doko_mitPflichtsolo",ui->checkBoxPflichtsolo);
    registerField("doko_mitSchwarzsolo",ui->checkBoxSchwarz);

    registerField("doko_mitFuenfKoenige",ui->checkBoxKings);
    registerField("doko_mitZuWenigTrumpf",ui->checkBoxWenigTrumpf);
    registerField("doko_mitNeunzigPunkte",ui->checkBoxPunkte);
    registerField("doko_mitTrumpfabgabeSchmeisserei",ui->checkBoxAbgabe);

    QSettings settings;
    ui->checkBoxHochzeit->setChecked(settings.value("GameWizard/LiveGameDokoGameOptions/mitHochzeit",true).toBool());
    ui->checkBoxSolo->setChecked(settings.value("GameWizard/LiveGameDokoGameOptions/mitSolo",true).toBool());
    ui->checkBoxTrumpfabgabe->setChecked(settings.value("GameWizard/LiveGameDokoGameOptions/mitTrumpfabgabe",true).toBool());
    ui->checkBoxSchmeisserei->setChecked(settings.value("GameWizard/LiveGameDokoGameOptions/mitSchmeisserei",true).toBool());
    ui->checkBoxSchweinerei->setChecked(settings.value("GameWizard/LiveGameDokoGameOptions/mitSchweinerei",true).toBool());

    ui->checkBoxBuben->setChecked(settings.value("GameWizard/LiveGameDokoGameOptions/mitBubenSolo",true).toBool());
    ui->checkBoxDamen->setChecked(settings.value("GameWizard/LiveGameDokoGameOptions/mitDamenSolo",true).toBool());
    ui->checkBoxFarb->setChecked(settings.value("GameWizard/LiveGameDokoGameOptions/mitFarbsolo",true).toBool());
    ui->checkBoxFleischlos->setChecked(settings.value("GameWizard/LiveGameDokoGameOptions/mitFleischlos",true).toBool());
    ui->checkBoxTrumpf->setChecked(settings.value("GameWizard/LiveGameDokoGameOptions/mitTrumpfsolo",true).toBool());
    ui->checkBoxPflichtsolo->setChecked(settings.value("GameWizard/LiveGameDokoGameOptions/mitPflichtsolo",true).toBool());
    ui->checkBoxSchwarz->setChecked(settings.value("GameWizard/LiveGameDokoGameOptions/mitSchwarzSolo").toBool());

    ui->checkBoxKings->setChecked(settings.value("GameWizard/LiveGameDokoGameOptions/mitFuenfKoenige",true).toBool());
    ui->checkBoxWenigTrumpf->setChecked(settings.value("GameWizard/LiveGameDokoGameOptions/mitZuWenigTrumpf",true).toBool());
    ui->checkBoxPunkte->setChecked(settings.value("GameWizard/LiveGameDokoGameOptions/mitNeunzigPunkte",true).toBool());
    ui->checkBoxAbgabe->setChecked(settings.value("GameWizard/LiveGameDokoGameOptions/mitTrumpfabgabeSchmeisserei",true).toBool());
}

LiveDokoGameOptionsWidget::~LiveDokoGameOptionsWidget()
{
    saveOptions();
    delete ui;
}

void LiveDokoGameOptionsWidget::saveOptions() const
{
    QSettings settings;
    settings.setValue("GameWizard/LiveGameDokoGameOptions/mitHochzeit", ui->checkBoxHochzeit->isChecked());
    settings.setValue("GameWizard/LiveGameDokoGameOptions/mitSolo", ui->checkBoxSolo->isChecked());
    settings.setValue("GameWizard/LiveGameDokoGameOptions/mitTrumpfabgabe", ui->checkBoxTrumpfabgabe->isChecked());
    settings.setValue("GameWizard/LiveGameDokoGameOptions/mitSchmeisserei", ui->checkBoxSchmeisserei->isChecked());
    settings.setValue("GameWizard/LiveGameDokoGameOptions/mitSchweinerei", ui->checkBoxSchweinerei->isChecked());

    settings.setValue("GameWizard/LiveGameDokoGameOptions/mitBubenSolo", ui->checkBoxBuben->isChecked());
    settings.setValue("GameWizard/LiveGameDokoGameOptions/mitDamenSolo", ui->checkBoxDamen->isChecked());
    settings.setValue("GameWizard/LiveGameDokoGameOptions/mitFarbsolo", ui->checkBoxFarb->isChecked());
    settings.setValue("GameWizard/LiveGameDokoGameOptions/mitFleischlos", ui->checkBoxFleischlos->isChecked());
    settings.setValue("GameWizard/LiveGameDokoGameOptions/mitTrumpfsolo", ui->checkBoxTrumpf->isChecked());
    settings.setValue("GameWizard/LiveGameDokoGameOptions/mitPflichtsolo", ui->checkBoxPflichtsolo->isChecked());
    settings.setValue("GameWizard/LiveGameDokoGameOptions/mitSchwarzsolo",ui->checkBoxSchwarz->isChecked());

    settings.setValue("GameWizard/LiveGameDokoGameOptions/mitFuenfKoenige", ui->checkBoxKings->isChecked());
    settings.setValue("GameWizard/LiveGameDokoGameOptions/mitZuWenigTrumpf", ui->checkBoxWenigTrumpf->isChecked());
    settings.setValue("GameWizard/LiveGameDokoGameOptions/mitNeunzigPunkte", ui->checkBoxPunkte->isChecked());
    settings.setValue("GameWizard/LiveGameDokoGameOptions/mitTrumpfabgabeSchmeisserei", ui->checkBoxAbgabe->isChecked());
}

int LiveDokoGameOptionsWidget::nextId() const
{
    saveOptions();
    return -1;
}

void Gui::Wizards::NewGame::LiveDokoGameOptionsWidget::on_checkBoxSolo_clicked(bool checked)
{
    ui->groupBoxSolo->setEnabled(checked);
}


void Gui::Wizards::NewGame::LiveDokoGameOptionsWidget::on_checkBoxSchmeisserei_clicked(bool checked)
{
    ui->groupBoxSchmeisserei->setEnabled(checked);
}
