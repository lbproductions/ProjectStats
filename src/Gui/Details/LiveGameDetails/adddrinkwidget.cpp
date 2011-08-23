#include "adddrinkwidget.h"
#include "ui_adddrinkwidget.h"

#include <Gui/Details/LiveGameDetails/livegamedetailswidget.h>
#include "beerwidget.h"

#include <Misc/handler.h>
#include <Database/database.h>
#include <Database/livegame.h>
#include <Database/drink.h>
#include <Database/player.h>
#include <Gui/Misc/draggablelabel.h>

using namespace Gui::Details::LiveGameDetails;

AddDrinkWidget::AddDrinkWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDrinkWidget)
{
    ui->setupUi(this);

    QFile newround(":/stylesheets/livegame/newroundwidget_fullscreen");
    newround.open(QFile::ReadOnly);
    setStyleSheet(newround.readAll());
    newround.close();

    QList<Database::Drink*> drinklist = Database::Drinks::instance()->/*drinksByDrinkCount*/allRows();

    for (int i = 0; i<drinklist.size();i++)
    {
        QVBoxLayout* layout = new QVBoxLayout();
        DraggableLabel* label = new DraggableLabel(drinklist.at(i));
        label->setText(drinklist.at(i)->name->value());
        QFont font = label->font();
        font.setPointSize(font.pointSize()*((double)(Handler::getInstance()->getDesktopWidth())/1680.0));
        label->setFont(font);
        QHBoxLayout* iconlayout = new QHBoxLayout();
        iconlayout->addStretch();
        DraggableLabel* icon = new DraggableLabel(drinklist.at(i));
        icon->setPixmap(QPixmap::fromImage(drinklist.at(i)->icon->value().scaled(40*((double)(Handler::getInstance()->getDesktopWidth())/1680.0),100*((double)(Handler::getInstance()->getDesktopHeight())/1680.0),Qt::KeepAspectRatio,Qt::SmoothTransformation)));
        icon->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        iconlayout->addWidget(icon);
        iconlayout->addStretch();
        layout->addLayout(iconlayout);
        layout->addWidget(label);
        ui->horizontalLayoutGroupBox->addLayout(layout);
    }

    setWindowModality(Qt::WindowModal);
}

AddDrinkWidget::~AddDrinkWidget()
{
    delete ui;
}


void Gui::Details::LiveGameDetails::AddDrinkWidget::on_pushButtonClose_clicked()
{
    this->reject();
}
