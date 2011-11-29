#ifndef OFFLINEDETAILLEDGAMEDOKOWIDGET_H
#define OFFLINEDETAILLEDGAMEDOKOWIDGET_H

#include <QWizardPage>
#include <QPointer>

namespace Ui {
    class OfflineDetailledGameDokoWidget;
}

namespace Database
{
    class Game;
}

namespace Gui
{

namespace Misc
{
    class PlacesComboBox;
}

namespace Wizards
{

namespace NewGame
{

class OfflineDetailledGameDokoWidget : public QWizardPage
{
    Q_OBJECT

public:
    explicit OfflineDetailledGameDokoWidget(QWidget *parent = 0);
    ~OfflineDetailledGameDokoWidget();

    void setupWidget(QWidget* parent);
    void setPlayerNumberLayout(int number);
    Database::Game* saveGame();

    bool checkInput();

    bool getCorrectInput();

    int nextId();

private:
    Ui::OfflineDetailledGameDokoWidget *ui;

    Gui::Misc::PlacesComboBox* m_placesComboBox;

    int m_playernumber;

    bool correctInput;
};

}
}
}

#endif // OFFLINEDETAILLEDGAMEDOKOWIDGET_H
