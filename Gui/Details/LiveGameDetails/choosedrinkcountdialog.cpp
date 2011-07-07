#include "choosedrinkcountdialog.h"
#include "ui_choosedrinkcountdialog.h"

ChooseDrinkCountDialog::ChooseDrinkCountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseDrinkCountDialog)
{
    ui->setupUi(this);
}

ChooseDrinkCountDialog::~ChooseDrinkCountDialog()
{
    delete ui;
}

void ChooseDrinkCountDialog::on_buttonBox_accepted()
{
    emit numberChosen(ui->spinBox->value());
}

void ChooseDrinkCountDialog::on_buttonBox_rejected()
{
    this->hide();
}
