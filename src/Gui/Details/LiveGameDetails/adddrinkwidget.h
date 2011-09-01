#ifndef ADDDRINKWIDGET_H
#define ADDDRINKWIDGET_H

#include <QDialog>
#include <QPointer>

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
    explicit AddDrinkWidget(QWidget *parent = 0);

    ~AddDrinkWidget();

private slots:
    void buttonCloseClicked();
};

}
}
}


#endif // ADDDRINKWIDGET_H
