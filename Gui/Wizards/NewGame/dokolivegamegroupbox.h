#ifndef DOKOLIVEGAMEGROUPBOX_H
#define DOKOLIVEGAMEGROUPBOX_H

#include <QGroupBox>

namespace Database
{
    class DokoLiveGame;
}

namespace Ui {
    class DokoLiveGameGroupBox;
}
namespace Gui
{

namespace Wizards
{

namespace NewGame
{

class DokoLiveGameGroupBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit DokoLiveGameGroupBox(Database::DokoLiveGame* livegame, QWidget *parent = 0);
    ~DokoLiveGameGroupBox();

private:
    Ui::DokoLiveGameGroupBox *ui;
};

}
}
}

#endif // DOKOLIVEGAMEGROUPBOX_H
