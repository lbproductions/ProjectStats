#ifndef PLAYERSTATSWIDGET_H
#define PLAYERSTATSWIDGET_H

#include <QWidget>

#include <Gui/Details/statswidget.h>

namespace Ui {
    class PlayerStatsWidget;
}

namespace Database
{
    class Player;
}

namespace Gui{

    namespace Details{

class PlayerStatsWidget : public StatsWidget
{
    Q_OBJECT

public:
    explicit PlayerStatsWidget(Database::Player* player, QWidget *parent = 0);
    ~PlayerStatsWidget();

private:
    Ui::PlayerStatsWidget *ui;
};

}
}

#endif // PLAYERSTATSWIDGET_H
