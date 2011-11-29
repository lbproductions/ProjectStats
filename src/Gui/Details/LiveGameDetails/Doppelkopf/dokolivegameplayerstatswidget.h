#ifndef DOKOLIVEGAMEPLAYERSTATSWIDGET_H
#define DOKOLIVEGAMEPLAYERSTATSWIDGET_H

#include <QTreeWidget>
#include <QPointer>

namespace Database
{
    class Player;
    class DokoLiveGame;
}

namespace Gui
{

namespace Details
{

namespace LiveGameDetails
{

namespace DokoLiveGameDetails{

/**
* Widget, das die Stats der Player eines DokoLiveGames anzeigt.
*/
class DokoLiveGamePlayerStatsWidget : public QTreeWidget
{
    Q_OBJECT
public:
    /**
    * Erstellt eine neue Instanz des DokoLiveGamePlayerStatsWidget für das übergebene DokoLiveGame.
    */
    explicit DokoLiveGamePlayerStatsWidget(Database::DokoLiveGame* livegame, QWidget *parent = 0);

    Database::DokoLiveGame* m_livegame;

    QList<Database::Player*> playerlist;

    /**
    * Aktualisiert die Stats der Player.
    */
    void updateWidget();

private:
    double prevWidth;
    int prevRoundId;

};

}
}
}
}
#endif // DOKOLIVEGAMEPLAYERSTATSWIDGET_H
