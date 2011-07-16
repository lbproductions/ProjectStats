#include "beerplayerwidget.h"
#include "ui_beerplayerwidget.h"

#include <Database/player.h>
#include <Database/drink.h>
#include <Database/livegame.h>
#include <Database/livegamedrink.h>

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

BeerPlayerWidget::BeerPlayerWidget(Database::Player* player, Database::LiveGame* livegame, QWidget *parent) :
    AbstractLiveGameWidget(parent),
    ui(new Ui::BeerPlayerWidget),
    m_livegame(livegame),
    m_player(player)
{
    ui->setupUi(this);

    player->name->futureWatcher()->connectTo(ui->labelName);
    player->alcPegel->mappingFutureWatcher()->connectTo(ui->labelAlc,livegame);

    int drinks = 0;
    foreach(Database::LiveGameDrink* lgdrink, livegame->drinksPerPlayer->value(player))
    {
        Database::Drink* drink = lgdrink->drink->value();
        DraggableLabel* drinkIcon = new DraggableLabel(drink,this);
        drinkIcon->setPixmap(QPixmap::fromImage(drink->icon->value().scaled(20,45,Qt::KeepAspectRatio,Qt::SmoothTransformation)));
	ui->gridLayoutDrinks->addWidget(drinkIcon,(drinks/5),drinks%5,Qt::AlignCenter);
        drinks++;
    }

    setAcceptDrops(true);

    m_parent = static_cast<BeerWidget*>(parent);

    m_palette = this->palette();

    this->setStyleSheet("QFrame{background: black; color: white; border-radius: 10px;}");
    ui->line->setStyleSheet("QFrame{background-color:gray;}");
}

BeerPlayerWidget::~BeerPlayerWidget()
{
    delete ui;
}

void BeerPlayerWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/projectstats.livegame/drink")){
        event->acceptProposedAction();
    }
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
    //m_parent->updateWidget();
}

void BeerPlayerWidget::dragMoveEvent(QDragMoveEvent * /*event*/)
{
    this->setStyleSheet("QFrame{background: rgb(51,51,51); color: white; border-radius: 10px;}");
    this->repaint();
}

void BeerPlayerWidget::dragLeaveEvent(QDragLeaveEvent * /*event*/){
    this->setStyleSheet("QFrame{background: black; color: white; border-radius: 10px;}");
    this->repaint();
}

void BeerPlayerWidget::setFullscreen(){
    /*
    QPalette p(this->palette());
    p.setColor(QPalette::Window, Qt::black);
    p.setColor(QPalette::Foreground, Qt::white);
    this->setPalette(p);
    this->setContentsMargins(10,10,10,10);
    this->setMinimumHeight(80);
    */
}

void BeerPlayerWidget::setNormalMode(){
    this->setStyleSheet("");
}
