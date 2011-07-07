#include "beerplayerwidget.h"
#include "ui_beerplayerwidget.h"

#include <Database/player.h>
#include <Database/drink.h>
#include <Database/livegame.h>

#include <handler.h>
#include <Database/database.h>
#include <Gui/Details/LiveGameDetails/beerwidget.h>

#include <Gui/Misc/draggablelabel.h>
#include <Gui/Details/LiveGameDetails/choosedrinkcountdialog.h>

#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDebug>

 #include <QGraphicsColorizeEffect>

using namespace Gui::Details::LiveGameDetails;

BeerPlayerWidget::BeerPlayerWidget(Database::Player* player, QList<QPointer<Database::Drink> > drinklist, Database::LiveGame* livegame, QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::BeerPlayerWidget),
    m_livegame(livegame),
    m_player(player)
{
    ui->setupUi(this);

    ui->labelName->setText(player->name->value() + " (" + QString::number(player->alcPegel->value(livegame)) + ")");

    for (int i = 0; i<drinklist.size();i++){
	int drinks = i;
        DraggableLabel* drinkIcon = new DraggableLabel(drinklist.at(i),this);
        drinkIcon->setPixmap(QPixmap::fromImage(drinklist.at(i)->icon->value().scaled(20,45,Qt::KeepAspectRatio,Qt::SmoothTransformation)));
	ui->gridLayoutDrinks->addWidget(drinkIcon,(drinks/5),drinks%5,Qt::AlignCenter);
    }

    setAcceptDrops(true);

    m_parent = static_cast<BeerWidget*>(parent);

    this->setStyleSheet("QGroupBox{border: 2px solid black}");

}

BeerPlayerWidget::~BeerPlayerWidget()
{
    delete ui;
}

void BeerPlayerWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/projectstats.livegame/drink"))
        event->acceptProposedAction();
}

void BeerPlayerWidget::dropEvent(QDropEvent *event)
 {
     QByteArray encodedData = event->mimeData()->data("application/projectstats.livegame/drink");
     QDataStream stream(&encodedData, QIODevice::ReadOnly);
     int id = -1;
     stream >> id;

     event->acceptProposedAction();

     Database::Drink *d = Database::Drinks::instance()->rowById(id);
     if(d != 0 && d->isValid())
     {
         m_droppedDrink = d;

         ChooseDrinkCountDialog* dialog = new ChooseDrinkCountDialog();
         dialog->setFocus();
         dialog->show();

         connect(dialog,SIGNAL(numberChosen(int)),this,SLOT(onNumberChosen(int)));
     }
 }

void BeerPlayerWidget::onNumberChosen(int number){
    for(int i = 0; i<number;i++){
        m_livegame->addDrink(m_player,m_droppedDrink);
    }
    m_parent->updateWidget();
}

void BeerPlayerWidget::dragMoveEvent(QDragMoveEvent *event)
{
    this->setStyleSheet("QGroupBox{border: 2px solid white}");
    this->repaint();
}

void BeerPlayerWidget::dragLeaveEvent(QDragLeaveEvent *event){
    this->setStyleSheet("QGroupBox{border: 2px solid black}");
    this->repaint();
}
