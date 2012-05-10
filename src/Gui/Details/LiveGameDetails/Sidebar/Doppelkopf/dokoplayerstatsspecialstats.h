#ifndef DOKOPLAYERSTATSSPECIALSTATS_H
#define DOKOPLAYERSTATSSPECIALSTATS_H

#include <QWidget>

namespace Database{
    class Player;
    class DokoLiveGame;
}

namespace Ui {
class DokoPlayerStatsSpecialStats;
}

namespace Gui{

namespace Details{

namespace LiveGameDetails{

namespace Sidebar{

class DokoPlayerStatsSpecialStats : public QWidget
{
    Q_OBJECT
    
public:
    explicit DokoPlayerStatsSpecialStats(Database::DokoLiveGame *dokoLiveGame, Database::Player *player, QWidget *parent);
    ~DokoPlayerStatsSpecialStats();

public slots:
    void onPflichtSoloChanged();
    
private:
    Ui::DokoPlayerStatsSpecialStats *ui;

    Database::Player* m_player;
    Database::DokoLiveGame* m_dokoLiveGame;
};

}}}}

#endif // DOKOPLAYERSTATSSPECIALSTATS_H
