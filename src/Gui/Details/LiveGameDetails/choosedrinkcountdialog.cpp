#include "choosedrinkcountdialog.h"
#include "ui_choosedrinkcountdialog.h"

#include <Database/livegame.h>
#include <Database/drink.h>

ChooseDrinkCountDialog::ChooseDrinkCountDialog(Database::Drink* drink, Database::Player* player, Database::LiveGame* game, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseDrinkCountDialog),
    m_drink(drink),
    m_player(player),
    m_game(game)
{
    ui->setupUi(this);

    this->setModal(true);
}

ChooseDrinkCountDialog::~ChooseDrinkCountDialog()
{
    delete ui;
}

void ChooseDrinkCountDialog::on_buttonBox_accepted()
{
    for(int i = 0; i < ui->spinBox->value(); ++i)
    {
        m_game->addDrink(m_player,m_drink);
    }

    this->accept();
}

void ChooseDrinkCountDialog::on_buttonBox_rejected()
{
    this->reject();
}
