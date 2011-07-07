#ifndef BEERPLAYERWIDGET_H
#define BEERPLAYERWIDGET_H

#include <QGroupBox>
#include <QPointer>


namespace Ui {
    class BeerPlayerWidget;
}

namespace Database
{
    class Player;
    class Drink;
    class LiveGame;
}

namespace Gui
{

namespace Details
{

namespace LiveGameDetails
{
    class BeerWidget;

class BeerPlayerWidget : public QGroupBox
{
    Q_OBJECT

public:
    explicit BeerPlayerWidget(Database::Player* player, QList<QPointer<Database::Drink> > drinklist, Database::LiveGame* livegame, QWidget *parent = 0);
    ~BeerPlayerWidget();

    void dragEnterEvent(QDragEnterEvent *event);

    void dropEvent(QDropEvent *event);

    void dragMoveEvent(QDragMoveEvent *event);

    void dragLeaveEvent(QDragLeaveEvent *event);
private:
    Ui::BeerPlayerWidget *ui;

    Database::LiveGame* m_livegame;
    Database::Player* m_player;

    Database::Drink* m_droppedDrink;

    BeerWidget* m_parent;

private slots:

    void onNumberChosen(int number);
};

}
}
}

#endif // BEERPLAYERWIDGET_H