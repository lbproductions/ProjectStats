#ifndef DOKOPLAYERSTATSWIDGET_H
#define DOKOPLAYERSTATSWIDGET_H

#include <QWidget>

#include "abstractplayerstatswidget.h"

namespace Ui {
class DokoPlayerStatsWidget;
}

namespace Database{
    class Player;
}

namespace Gui{

namespace Details{

class DokoPlayerStatsWidget : public AbstractPlayerStatsWidget
{
    Q_OBJECT

public:
    explicit DokoPlayerStatsWidget(Database::Player* player, QWidget *parent = 0);
    ~DokoPlayerStatsWidget();

private:
    Ui::DokoPlayerStatsWidget *uiDoko;
};

}}

#endif // DOKOPLAYERSTATSWIDGET_H
