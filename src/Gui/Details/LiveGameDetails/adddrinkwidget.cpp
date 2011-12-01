#include "adddrinkwidget.h"
#include "ui_adddrinkwidget.h"

#include <Gui/Details/LiveGameDetails/livegamedetailswidget.h>
#include "beerwidget.h"

#include <Misc/handler.h>

#include <Database/livegame.h>
#include <Database/drink.h>
#include <Database/player.h>
#include <Gui/Misc/draggablelabel.h>
#include <Gui/Misc/groupbox.h>

using namespace Gui::Details::LiveGameDetails;

AddDrinkWidget::AddDrinkWidget(QWidget *parent) :
    QDialog(parent)
{

    QPalette p(this->palette());
    p.setColor(QPalette::Background, QColor(55,55,55));
    this->setPalette(p);

    this->setStyleSheet("QFrame{margin: 0px; padding: 0px; background: transparent; color: white; border: none; font-weight: bold;}");

    QVBoxLayout* layout = new QVBoxLayout(this);

    foreach(QString type, Database::Drinks::instance()->types->value()){
        QGridLayout* grid = new QGridLayout(this);
        grid->addWidget(new QLabel(type,this),0,0);
        QList<Database::Drink*> list =  Database::Drinks::instance()->drinksOfType->value(type);
        for(int i = 0; i<list.size();i++){
            QVBoxLayout* drink = new QVBoxLayout(this);

            DraggableLabel* name = new DraggableLabel(list.at(i),this);
            name->setText(list.at(i)->name->value());
            //name->setStyleSheet("QLabel{color:white;}");

            QHBoxLayout* iconlayout = new QHBoxLayout(this);
            iconlayout->addStretch();
            DraggableLabel* icon = new DraggableLabel(list.at(i),this);
            icon->setPixmap(QPixmap::fromImage(list.at(i)->icon->value().scaled(30,55,Qt::KeepAspectRatio,Qt::SmoothTransformation)));
            icon->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            iconlayout->addWidget(icon);
            iconlayout->addStretch();

            drink->addLayout(iconlayout);
            drink->addWidget(name);

            grid->addLayout(drink,(i/7)+1,i%7);

        }
        Gui::Misc::GroupBox* box = new Gui::Misc::GroupBox(grid,this);
        layout->addWidget(box);
    }

    QHBoxLayout* close = new QHBoxLayout(this);
    close->addStretch();
    QPushButton* closeButton = new QPushButton(tr("Close"),this);
    connect(closeButton,SIGNAL(clicked()),this,SLOT(buttonCloseClicked()));
    close->addWidget(closeButton);
    close->addStretch();

    layout->addLayout(close);

    QList<Database::Drink*> drinklist = Database::Drinks::instance()->/*drinksByDrinkCount*/allRows();

    /*
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

    */

    setWindowModality(Qt::WindowModal);
}

AddDrinkWidget::~AddDrinkWidget()
{

}


void Gui::Details::LiveGameDetails::AddDrinkWidget::buttonCloseClicked()
{
    this->reject();
}
