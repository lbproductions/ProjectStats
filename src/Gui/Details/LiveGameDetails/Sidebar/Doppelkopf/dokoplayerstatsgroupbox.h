#ifndef DOKOPLAYERSTATSGROUPBOX_H
#define DOKOPLAYERSTATSGROUPBOX_H

#include <QWidget>

namespace Database{
    class Player;
    class DokoLiveGame;
}

namespace Ui {
class DokoPlayerStatsGroupBox;
}

namespace Gui{

namespace Details{

namespace LiveGameDetails{

namespace Sidebar{

class DokoPlayerStatsGroupBox : public QWidget
{
    Q_OBJECT
    
public:
    explicit DokoPlayerStatsGroupBox(Database::DokoLiveGame* dokoLiveGame, Database::Player* player, QWidget *parent = 0);
    ~DokoPlayerStatsGroupBox();

    void mouseReleaseEvent ( QMouseEvent * event );

    void resizeEvent(QResizeEvent *);
    
private:
    Ui::DokoPlayerStatsGroupBox *ui;

    Database::Player* m_player;
    Database::DokoLiveGame* m_dokoLiveGame;

    int m_clickCounter;
    bool m_rightClickMode;
};

}}}}

#endif // DOKOPLAYERSTATSGROUPBOX_H
