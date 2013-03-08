#include "chooseunfinishedgamedialog.h"
#include "ui_chooseunfinishedgamedialog.h"

#include "newgamewizard.h"
#include "livegamegeneraloptionswidget.h"

#include <Database/player.h>
#include <Database/game.h>
#include <Database/Doppelkopf/dokolivegame.h>

#include <Gui/Details/rowwindow.h>

#include <QDateTime>
#include <QKeyEvent>

using namespace Gui::Wizards::NewGame;

ChooseUnfinishedGameDialog::ChooseUnfinishedGameDialog(Gui::Wizards::NewGameWizard *parent) :
    QWizardPage(parent),
    ui(new Ui::ChooseUnfinishedGameDialog),
    m_wizard(parent)
{
    ui->setupUi(this);

    connect(ui->listWidget,SIGNAL(clicked(QModelIndex)),this,SIGNAL(completeChanged()));

    this->setFocusPolicy(Qt::StrongFocus);
}

ChooseUnfinishedGameDialog::~ChooseUnfinishedGameDialog()
{
    delete ui;
}

int ChooseUnfinishedGameDialog::nextId() const
{
    if(!ui->listWidget->selectedItems().isEmpty()){
        if(ui->listWidget->selectedItems().first()->data(Qt::UserRole+1).toInt() == -1){

            if (field("live_type").toString() == Database::DokoLiveGame::TYPE)
            {
                return NewGameWizard::Page_LiveGameDokoOptions;
            }
            else if(field("live_type").toString() == "Skat")
            {
                return NewGameWizard::Page_SkatLiveGameOptionsWidget;
            }
        }
        else{
            return -1;
        }
    }
    return NewGameWizard::Page_ChooseUnfinishedGame;
}

bool ChooseUnfinishedGameDialog::isComplete() const
{
    if(ui->listWidget->selectedItems().isEmpty()){
        return false;
    }
    return true;
}

void Gui::Wizards::NewGame::ChooseUnfinishedGameDialog::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    /*
    Database::Game* game = Database::Games::instance()->rowById(item->data(Qt::UserRole+1).toInt());

    Details::RowWindow *newRowWindow = game->rowWindow();
    if(newRowWindow)
    {
        newRowWindow->show();
    }
    */
}

void Gui::Wizards::NewGame::ChooseUnfinishedGameDialog::initializePage()
{
    LiveGameGeneralOptionsWidget* asdf = m_wizard->liveGameGeneralOptionsWidget();
    QList<Database::Player*> list = asdf->selectedPlayers();

    QListWidgetItem* itemNew = new QListWidgetItem(ui->listWidget);
    itemNew->setText(tr("Create New Game"));
    itemNew->setData(Qt::UserRole+1,-1);
    ui->listWidget->addItem(itemNew);

    foreach(Database::Game* game, Database::Games::instance()->unfinishedGames->value()){
        bool complete = true;
        if(game->live->value()){
            if(game->playersSortedByPosition->value().size() == list.size()){
                foreach(Database::Player* player, list){
                    if(!game->playersSortedByPosition->value().contains(player)){
                       complete = false;
                    }
                }
                if(complete){
                    QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
                    if(game->name->value() == ""){
                        item->setText(game->date->value().toString());
                    }
                    else{
                        item->setText(game->name->value());
                    }
                    item->setData(Qt::UserRole+1,game->id());

                }
            }
        }
    }
}

Database::LiveGame* Gui::Wizards::NewGame::ChooseUnfinishedGameDialog::selectedGame()
{
    if(!ui->listWidget->selectedItems().isEmpty()){
        if(ui->listWidget->selectedItems().first()->text() != tr("Create New Game"))
        {
            QListWidgetItem* item = ui->listWidget->selectedItems().first();
            return (Database::LiveGame*)Database::Games::instance()->rowById(item->data(Qt::UserRole+1).toInt()).data();
        }
        else{
            qWarning() << "No Game can be returned, because a new game should be created!";
        }
    }
    else{
        qWarning() << "No Game selected in ChooseUnfinishedGameDialog";
    }
}

bool Gui::Wizards::NewGame::ChooseUnfinishedGameDialog::newGameItemIsChosen()
{
    if(!ui->listWidget->selectedItems().isEmpty()){
        if(ui->listWidget->selectedItems().first()->text() == tr("Create New Game"))
        {
            return true;
        }
    }
    return false;
}

void Gui::Wizards::NewGame::ChooseUnfinishedGameDialog::keyPressEvent(QKeyEvent* event)
{
    qDebug() << "keyPressEvent activated";
    if(event->key() == Qt::Key_Space)
    {
        qDebug() << "Space pressed";
    }
}
