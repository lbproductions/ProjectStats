#include "newleaguedialog.h"
#include "ui_newleaguedialog.h"

#include <Misc/handler.h>
#include <Database/database.h>
#include <Database/player.h>
#include <Database/categorie.h>
#include <Database/Categories/childcategorie.h>
#include <Database/Categories/leaguefoldercategorie.h>
//#include <Database/Filters/rules.h>

#include <QListWidgetItem>

NewLeagueDialog::NewLeagueDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewLeagueDialog)
{
    ui->setupUi(this);

    setWindowModality(Qt::WindowModal);
    setAttribute(Qt::WA_DeleteOnClose);

    foreach(Database::Player* p, Database::Players::instance()->allRows()){
        ui->listWidgetAllPlayers->addItem(p->name->value());
    }

    ui->dateEditFrom->setDate(QDate(1970,1,1));
    ui->dateEditTo->setDate(QDate::currentDate());
}

NewLeagueDialog::~NewLeagueDialog()
{
    delete ui;
}

void NewLeagueDialog::on_pushButtonOkay_clicked()
{
    QPointer<Database::LeagueFolderCategorie> league = new Database::LeagueFolderCategorie();

    for (int i = 0; i<ui->listWidgetLeaguePlayers->count();i++)
    {
        league->addPlayer(Database::Players::instance()->playerByName(ui->listWidgetLeaguePlayers->item(i)->text()));
    }

    this->accept();
}

void NewLeagueDialog::on_pushButtonCancel_clicked()
{
    this->reject();
}

void NewLeagueDialog::on_pushButtonAdd_clicked()
{
    ui->listWidgetLeaguePlayers->addItem(ui->listWidgetAllPlayers->takeItem(ui->listWidgetAllPlayers->currentRow()));
}

void NewLeagueDialog::on_pushButtonRemove_clicked()
{
    ui->listWidgetAllPlayers->addItem(ui->listWidgetLeaguePlayers->takeItem(ui->listWidgetLeaguePlayers->currentRow()));
}

void NewLeagueDialog::on_dateEditFrom_dateChanged(QDate date)
{
    if (date > ui->dateEditTo->date()){
        //ui->dateEditTo->setDate(date);
    }
}

void NewLeagueDialog::on_dateEditTo_dateChanged(QDate date)
{
    if (date < ui->dateEditFrom->date()){
        //ui->dateEditFrom->setDate(date);
    }
}
