#include "livegamegeneraloptionswidget.h"
#include "ui_livegamegeneraloptionswidget.h"

#include "newgamewizard.h"

#include <Database/database.h>
#include <handler.h>
#include <Database/player.h>
#include <Database/Doppelkopf/dokolivegame.h>
#include <Gui/Misc/placescombobox.h>

#include <QSettings>

using namespace Gui::Wizards::NewGame;

LiveGameGeneralOptionsWidget::LiveGameGeneralOptionsWidget(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::LiveGameGeneralOptionsWidget)
{
    ui->setupUi(this);

    setupWidget();

    registerField("type", ui->comboBoxGameType,"currentText",SIGNAL(currentTextChanged()));
    registerField("place", placesbox,"currentPlace",SIGNAL(currentPlaceChanged(Database::Place*,Database::Place*)));

    connect(ui->comboBoxGameType,SIGNAL(currentIndexChanged(int)),this,SIGNAL(completeChanged()));
    connect(placesbox,SIGNAL(currentIndexChanged(int)),this,SIGNAL(completeChanged()));
    connect(ui->pushButtonDeselect,SIGNAL(clicked()),this,SIGNAL(completeChanged()));
    connect(ui->pushButtonSelect,SIGNAL(clicked()),this,SIGNAL(completeChanged()));

    setTitle(tr("General Live Game Options"));
}

LiveGameGeneralOptionsWidget::~LiveGameGeneralOptionsWidget()
{
    saveOptions();
    delete ui;
}

void LiveGameGeneralOptionsWidget::saveOptions() const
{
    QSettings settings;
    settings.setValue("LiveGameGeneralOptionsWidget/comboBoxGameTypeSelectedType",ui->comboBoxGameType->currentText());
    settings.setValue("LiveGameGeneralOptionsWidget/placesboxSelectedPlace",placesbox->currentText());
}

int LiveGameGeneralOptionsWidget::nextId() const
{
    saveOptions();

    if (ui->comboBoxGameType->currentText() == "Doppelkopf")
    {
        return NewGameWizard::Page_LiveGameDokoOptions;
    }
    else if(ui->comboBoxGameType->currentText() == "Skat")
    {
        return NewGameWizard::Page_SkatLiveGameOptionsWidget;
    }

    return NewGameWizard::Page_LiveGameGeneralOptions;
}

void LiveGameGeneralOptionsWidget::setupWidget()
{
    ui->comboBoxGameType->clear();

    ui->comboBoxGameType->addItem(tr("Choose a game..."));

    foreach(QString type, Database::Games::instance()->possibleTypes())
    {
        ui->comboBoxGameType->addItem(type);
    }

    QSettings settings;
    int selectedIndex = ui->comboBoxGameType->findText(settings.value("LiveGameGeneralOptionsWidget/comboBoxGameTypeSelectedType",tr("Choose a game...")).toString());
    selectedIndex = selectedIndex == -1 ? 0 : selectedIndex;
    ui->comboBoxGameType->setCurrentIndex(selectedIndex);

    foreach(Database::Player *player, Database::Players::instance()->allRows())
    {
        ui->listWidgetAllPlayers->addItem(player->name->value());
    }

    ui->listWidgetAllPlayers->setAlternatingRowColors(true);
    ui->listWidgetSelectedPlayers->setAlternatingRowColors(true);

    QVBoxLayout* layout = new QVBoxLayout();
    placesbox = new Gui::Misc::PlacesComboBox(this);
    layout->addWidget(placesbox);

    selectedIndex = placesbox->findText(settings.value("LiveGameGeneralOptionsWidget/placesboxSelectedPlace","").toString());
    selectedIndex = selectedIndex == -1 ? 0 : selectedIndex;
    placesbox->setCurrentIndex(selectedIndex);

    ui->groupBox_3->setLayout(layout);
}

bool LiveGameGeneralOptionsWidget::isComplete() const
{
    if(ui->comboBoxGameType->currentIndex() < 0 || ui->comboBoxGameType->currentText() == tr("Choose a game...") )
    {
        return false;
    }

    if(placesbox->currentIndex() >= placesbox->count())
    {
        return false;
    }

    int minPlayerCount = 1;

    if (ui->comboBoxGameType->currentText() == "Doppelkopf")
    {
        minPlayerCount = 4;
    }
    else if(ui->comboBoxGameType->currentText() == "Skat")
    {
        minPlayerCount = 3;
    }

    if(ui->listWidgetSelectedPlayers->count() < minPlayerCount)
    {
        return false;
    }

    return true;
}

void LiveGameGeneralOptionsWidget::on_comboBoxGameType_currentIndexChanged(int /*index*/)
{
    if(ui->comboBoxGameType->itemText(0) == tr("Choose a game..."))
    {
        ui->comboBoxGameType->removeItem(0);
    }
}

void LiveGameGeneralOptionsWidget::on_pushButtonSelect_clicked()
{
    ui->listWidgetSelectedPlayers->addItem(ui->listWidgetAllPlayers->takeItem(ui->listWidgetAllPlayers->currentRow()));
}

void LiveGameGeneralOptionsWidget::on_pushButtonDeselect_clicked()
{
    ui->listWidgetAllPlayers->addItem(ui->listWidgetSelectedPlayers->takeItem(ui->listWidgetSelectedPlayers->currentRow()));
}
