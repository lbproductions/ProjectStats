#ifndef ADDDRINKWIDGET_H
#define ADDDRINKWIDGET_H

#include <QDialog>
#include <QPointer>

namespace Ui {
    class AddDrinkWidget;
}


namespace Database
{
    class LiveGame;
    class Player;
}

namespace Gui
{

namespace Details
{

namespace LiveGameDetails
{

class BeerWidget;

/**
* Widget zum Hinzufügen von Drinks zu einem LiveGame.
*/
class AddDrinkWidget : public QDialog
{
    Q_OBJECT

public:
    /**
    * Erstellt eine neue Instanz des AddDrinkWidgets für das übergebene LiveGame. Dieses wird dabei mit den Playern des Spiels und den existierenden Drinks befüllt.
    */
    explicit AddDrinkWidget(Database::LiveGame* livegame, QWidget *parent = 0);
    ~AddDrinkWidget();

private:
    Ui::AddDrinkWidget *ui;

    QPointer<Database::LiveGame> m_livegame;
    QPointer<BeerWidget> m_beerwidget;
    QList < QPointer<Database::Player> > playerlist;

signals:
    /**
    * Wird gesendet, wenn neue Drinks dem Game hinzugefügt wurden.
    */
    void drinkDealed();
private slots:
    void on_pushButtonClose_clicked();
};

}
}
}


#endif // ADDDRINKWIDGET_H
