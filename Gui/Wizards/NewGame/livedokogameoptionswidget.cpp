#include "livedokogameoptionswidget.h"
#include "ui_livedokogameoptionswidget.h"

#include "newgamewizard.h"

#include <Database/Doppelkopf/dokolivegame.h>

#include <QSettings>

using namespace Gui::Wizards::NewGame;

LiveDokoGameOptionsWidget::LiveDokoGameOptionsWidget(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::LiveDokoGameOptionsWidget)
{
    ui->setupUi(this);

    this->setTitle("Doppelkopf Game Mechanics");

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

//Database::DokoLiveGame* LiveDokoGameOptionsWidget::startLiveGame()
//{
//    m_dokoLiveGame->doko_mitHochzeit->setValue(ui->checkBoxHochzeit->isChecked());
//    m_dokoLiveGame->doko_mitSolo->setValue(ui->checkBoxSolo->isChecked());
//    m_dokoLiveGame->doko_mitTrumpfabgabe->setValue(ui->checkBoxTrumpfabgabe->isChecked());
//    m_dokoLiveGame->doko_mitSchmeisserei->setValue(ui->checkBoxSchmeisserei->isChecked());
//    m_dokoLiveGame->doko_mitSchweinerei->setValue(ui->checkBoxSchweinerei->isChecked());

////    m_dokoLiveGame->doko_mitBubenSolo(ui->checkBoxBuben->isChecked());
////    m_dokoLiveGame->doko_mitDamenSolo(ui->checkBoxDamen->isChecked());
////    m_dokoLiveGame->doko_mitFarbsolo(ui->checkBoxFarb->isChecked());
////    m_dokoLiveGame->doko_mitFleischlos(ui->checkBoxFleischlos->isChecked());
////    m_dokoLiveGame->doko_setMitTrumpfsolo(ui->checkBoxTrumpf->isChecked());

////    m_dokoLiveGame->setMitFuenfKoenige(ui->checkBoxKings->isChecked());
////    m_dokoLiveGame->setMitZuWenigTrumpf(ui->checkBoxWenigTrumpf->isChecked());
////    m_dokoLiveGame->setMitNeunzigPunkte(ui->checkBoxPunkte->isChecked());
////    m_dokoLiveGame->setMitTrumpfabgabeSchmeisserei(ui->checkBoxAbgabe->isChecked());
////    m_dokoLiveGame->setMitPflichtsolo(ui->checkBoxPflichtsolo->isChecked());



//    return m_dokoLiveGame;
//}


void Gui::Wizards::NewGame::LiveDokoGameOptionsWidget::on_checkBoxSolo_clicked(bool checked)
{
    ui->groupBoxSolo->setEnabled(checked);
}


void Gui::Wizards::NewGame::LiveDokoGameOptionsWidget::on_checkBoxSchmeisserei_clicked(bool checked)
{
    ui->groupBoxSchmeisserei->setEnabled(checked);
}
