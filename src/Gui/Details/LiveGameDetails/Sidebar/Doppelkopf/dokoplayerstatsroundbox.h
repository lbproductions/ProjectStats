#ifndef DOKOPLAYERSTATSROUNDBOX_H
#define DOKOPLAYERSTATSROUNDBOX_H

#include <QWidget>

namespace Database{
    class Player;
    class DokoLiveGame;
}

namespace Ui {
class DokoPlayerStatsRoundBox;
}

namespace Gui{

namespace Details{

namespace LiveGameDetails{

namespace Sidebar{

class DokoPlayerStatsRoundBox : public QWidget
{
    Q_OBJECT
    
public:
    explicit DokoPlayerStatsRoundBox(Database::DokoLiveGame *dokoLiveGame, Database::Player *player, QWidget *parent);
    ~DokoPlayerStatsRoundBox();
    
private:
    Ui::DokoPlayerStatsRoundBox *ui;
};
}}}}

#endif // DOKOPLAYERSTATSROUNDBOX_H
