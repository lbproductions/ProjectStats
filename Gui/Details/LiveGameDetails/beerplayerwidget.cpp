#include "beerplayerwidget.h"
#include "ui_beerplayerwidget.h"

#include <Database/player.h>
#include <Database/drink.h>
#include <Database/livegame.h>
#include <Database/livegamedrink.h>

#include <handler.h>
#include <Database/database.h>
#include <Gui/Details/LiveGameDetails/beerwidget.h>

#include <Gui/Misc/clickablelabel.h>
#include <Gui/Details/LiveGameDetails/choosedrinkcountdialog.h>

#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDebug>

 #include <QGraphicsColorizeEffect>

using namespace Gui::Details::LiveGameDetails;

DrinkLabel::DrinkLabel(Database::LiveGameDrink *drink, QWidget *parent) :
    Gui::Misc::ClickableLabel(parent),
    m_drink(drink)
{
    Database::Drink* d = drink->drink->value();
    QImage image = d->icon->value();
    if(image.isNull())
    {
        image = QImage(":graphics/drinks/default");
    }
    setPixmap(QPixmap::fromImage(image.scaled(20,45,Qt::KeepAspectRatio,Qt::SmoothTransformation)));
    setToolTip(d->name->value() + QLatin1String(" ") + QString::number(d->size->value()) + tr("l - doubleclick to drink another"));
    connect(this,SIGNAL(doubleClicked()),this,SLOT(on_doubleClicked()));
}

void DrinkLabel::on_doubleClicked()
{
    emit drinkDoubleClicked(m_drink);
}

BeerPlayerWidget::BeerPlayerWidget(Database::Player* player, Database::LiveGame* livegame, QWidget *parent) :
    AbstractLiveGameWidget(parent),
    ui(new Ui::BeerPlayerWidget),
    m_livegame(livegame),
    m_player(player)
{
    ui->setupUi(this);

    player->name->futureWatcher()->connectTo(ui->labelName);
    player->alcPegel->mappingFutureWatcher(livegame)->connectTo(ui->labelAlc);

    int drinks = 0;
    foreach(Database::LiveGameDrink* lgdrink, livegame->drinksPerPlayer->value(player))
    {
        DrinkLabel* drinkIcon = new DrinkLabel(lgdrink,this);
        connect(drinkIcon,SIGNAL(drinkDoubleClicked(::Database::LiveGameDrink*)),this,SLOT(ondrinkdoubleClicked(::Database::LiveGameDrink*)));
	ui->gridLayoutDrinks->addWidget(drinkIcon,(drinks/5),drinks%5,Qt::AlignCenter);
        drinks++;
    }

    setAcceptDrops(true);

    this->setStyleSheet("QFrame{background: black; color: white; border-radius: 10px;}");
    ui->line->setStyleSheet("QFrame{background-color:gray;}");

    connect(m_livegame,SIGNAL(drinkAdded(::Database::LiveGameDrink*)),this,SLOT(onlivegamedrinkAdded(::Database::LiveGameDrink*)));
}

void BeerPlayerWidget::onlivegamedrinkAdded(::Database::LiveGameDrink* drink)
{
    if(drink->playerId->value() == m_player->id())
    {
        int drinks = ui->gridLayoutDrinks->count();

        DrinkLabel* drinkIcon = new DrinkLabel(drink,this);
        connect(drinkIcon,SIGNAL(drinkDoubleClicked(::Database::LiveGameDrink*)),this,SLOT(ondrinkdoubleClicked(::Database::LiveGameDrink*)));
        ui->gridLayoutDrinks->addWidget(drinkIcon,(drinks/5),drinks%5,Qt::AlignCenter);

        this->parentWidget()->update();
    }
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
    if(d)
    {
        ChooseDrinkCountDialog dialog(d,m_player,m_livegame);
        dialog.exec();
    }
    this->setStyleSheet("QFrame{background: black; color: white; border-radius: 10px;}");
    this->repaint();
}

void BeerPlayerWidget::ondrinkdoubleClicked(::Database::LiveGameDrink* drink)
{
    m_livegame->addDrink(m_player,drink->drink->value());
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
