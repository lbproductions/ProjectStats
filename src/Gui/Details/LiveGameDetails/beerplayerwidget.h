#ifndef BEERPLAYERWIDGET_H
#define BEERPLAYERWIDGET_H

#include <QGroupBox>
#include <QPointer>
#include <QFrame>

#include <Gui/Details/LiveGameDetails/abstractlivegamewidget.h>
#include <Gui/Misc/clickablelabel.h>

namespace Ui {
    class BeerPlayerWidget;
}

namespace Database
{
    class Player;
    class Drink;
    class LiveGame;
    class LiveGameDrink;
}

namespace Gui
{

namespace Details
{

namespace LiveGameDetails
{
    class BeerWidget;

class BeerPlayerWidget : public AbstractLiveGameWidget
{
    Q_OBJECT

public:
    explicit BeerPlayerWidget(Database::Player* player, Database::LiveGame* livegame, QWidget *parent = 0);

    ~BeerPlayerWidget();

    void dragEnterEvent(QDragEnterEvent *event);

    void dropEvent(QDropEvent *event);

    void dragMoveEvent(QDragMoveEvent *event);

    void dragLeaveEvent(QDragLeaveEvent *event);

private:
    Ui::BeerPlayerWidget *ui;

    Database::LiveGame* m_livegame;
    Database::Player* m_player;

public slots:
    void onlivegamedrinkAdded(::Database::LiveGameDrink*);
    void ondrinkdoubleClicked(::Database::LiveGameDrink*);
};

class DrinkLabel : public Gui::Misc::ClickableLabel
{
    Q_OBJECT
public:
    explicit DrinkLabel(Database::LiveGameDrink* drink, QWidget* parent);

signals:
    void drinkDoubleClicked(::Database::LiveGameDrink*);

private slots:
    void on_doubleClicked();

private:
    Database::LiveGameDrink* m_drink;
};

}
}
}

#endif // BEERPLAYERWIDGET_H
