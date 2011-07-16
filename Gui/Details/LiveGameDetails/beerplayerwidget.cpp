#include "beerplayerwidget.h"
#include "ui_beerplayerwidget.h"

#include <Database/player.h>
#include <Database/drink.h>
#include <Database/livegame.h>
#include <Database/livegamedrink.h>
#include <Database/attributelist.h>

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

    this->setStyleSheet("QFrame{background: black; color: white; border-radius: 10px;}");
    ui->line->setStyleSheet("QFrame{background-color:gray;}");

    connect(Database::LiveGameDrinks::instance()->rows(),SIGNAL(changed()),this,SLOT(update()));
}

void BeerPlayerWidget::update()
{
    //FAIL:
    m_livegame->drinks->recalculate();
    m_livegame->drinks->futureWatcher()->futureWatcher()->waitForFinished();
    m_livegame->drinksPerPlayer->recalculate();
    m_livegame->drinksPerPlayer->futureWatcher()->futureWatcher()->waitForFinished();

    int drinks = m_livegame->drinksPerPlayer->value(m_player).size() - 1;

    if(drinks >= 0)
    {
        Database::Drink* drink = m_livegame->drinksPerPlayer->value(m_player).last()->drink->value();
        DraggableLabel* drinkIcon = new DraggableLabel(drink,this);
        drinkIcon->setPixmap(QPixmap::fromImage(drink->icon->value().scaled(20,45,Qt::KeepAspectRatio,Qt::SmoothTransformation)));
        ui->gridLayoutDrinks->addWidget(drinkIcon,(drinks/5),drinks%5,Qt::AlignCenter);
    }

    this->repaint();
}

BeerPlayerWidget::~BeerPlayerWidget()
{
    delete ui;
}

void BeerPlayerWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/projectstats.livegame/drink"))
    {
        this->setStyleSheet("QFrame{background: rgb(51,51,51); color: white; border-radius: 10px;}");
        event->acceptProposedAction();
        this->repaint();
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
        ChooseDrinkCountDialog dialog(d,m_player,m_livegame);
        dialog.exec();
    }
    this->setStyleSheet("QFrame{background: black; color: white; border-radius: 10px;}");
    this->repaint();
}

void BeerPlayerWidget::dragMoveEvent(QDragMoveEvent * /*event*/)
{
    this->repaint();
}

void BeerPlayerWidget::dragLeaveEvent(QDragLeaveEvent * /*event*/)
{
    this->setStyleSheet("QFrame{background: black; color: white; border-radius: 10px;}");
    this->repaint();
}
