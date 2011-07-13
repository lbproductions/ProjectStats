#ifndef ABSTRACTPLAYERSTATSWIDGET_H
#define ABSTRACTPLAYERSTATSWIDGET_H

#include <QWidget>

namespace Database{
    class Player;
}

namespace Ui {
    class AbstractPlayerStatsWidget;
}

namespace Gui{

    namespace Details{

class AbstractPlayerStatsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AbstractPlayerStatsWidget(Database::Player* player, QString type, QWidget *parent = 0);
    ~AbstractPlayerStatsWidget();

private:
    Ui::AbstractPlayerStatsWidget *ui;
};

    }}

#endif // ABSTRACTPLAYERSTATSWIDGET_H
