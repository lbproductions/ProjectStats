#include "livegamegeneraloptionswidget.h"
#include "ui_livegamegeneraloptionswidget.h"

#include "newgamewizard.h"

#include <Database/database.h>
#include <Misc/handler.h>
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

    registerField("live_type", ui->comboBoxGameType,"currentText",SIGNAL(currentTextChanged()));

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

    if (ui->comboBoxGameType->currentText() == Database::DokoLiveGame::TYPE)
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
    ui->comboBoxGameType->addItem(Database::DokoLiveGame::TYPE);

//    foreach(QString type, Database::Games::instance()->possibleTypes())
//    {
//        ui->comboBoxGameType->addItem(type);
//    }

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

QList<Database::Player*> LiveGameGeneralOptionsWidget::selectedPlayers()
{
    QList<Database::Player*> list;
    for(int i = 0; i < ui->listWidgetSelectedPlayers->count(); ++i)
    {
        list.append(Database::Players::instance()->playerByName(ui->listWidgetSelectedPlayers->item(i)->text()));
    }

    return list;
}

Database::Place *LiveGameGeneralOptionsWidget::selectedPlace()
{
    return placesbox->currentPlace();
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

    if (ui->comboBoxGameType->currentText() == Database::DokoLiveGame::TYPE)
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
    if(ui->listWidgetAllPlayers->selectedItems().isEmpty())
    {
        return;
    }

    int row = ui->listWidgetAllPlayers->selectionModel()->selectedRows().at(0).row();

    QListIterator<QListWidgetItem *> it(ui->listWidgetAllPlayers->selectedItems());

    while (it.hasNext())
    {
        ui->listWidgetSelectedPlayers->addItem(ui->listWidgetAllPlayers->takeItem(ui->listWidgetAllPlayers->row(it.next())));
    }

    QAbstractItemModel * model = ui->listWidgetAllPlayers->model();

    ui->listWidgetAllPlayers->selectionModel()->setCurrentIndex(
            model->index(row,0,model->index(0,0,QModelIndex()))
            ,QItemSelectionModel::Select);
}

void LiveGameGeneralOptionsWidget::on_pushButtonDeselect_clicked()
{
    QListIterator<QListWidgetItem *> it(ui->listWidgetSelectedPlayers->selectedItems());

    while (it.hasNext())
    {
        ui->listWidgetAllPlayers->addItem(ui->listWidgetSelectedPlayers->takeItem(ui->listWidgetSelectedPlayers->row(it.next())));
    }
}
