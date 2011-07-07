#ifndef BEERWIDGET_H
#define BEERWIDGET_H

#include <QPointer>
#include <Gui/Details/LiveGameDetails/abstractlivegamewidget.h>

class QVBoxLayout;

namespace Database
{
    class Player;
    class LiveGame;

}

namespace Gui
{

namespace Details
{

namespace LiveGameDetails
{

/**
* GroupBox, die die bereits getrunkenen Getränke der Player eines LiveGames anzeigt.
*/
class BeerWidget : public AbstractLiveGameWidget
{
    Q_OBJECT
public:
    /**
    * Erstellt eine neue Instanz des BeerWidgets für das übergebene LiveGame. Für jeden Player wird ein neues QGridLayout hinzugefügt.
    */
    explicit BeerWidget(Database::LiveGame* livegame, QWidget *parent = 0);

    QVBoxLayout* m_layout;
    QPointer<Database::LiveGame> m_livegame;
    QList< Database::Player* > m_playerlist;

    QPalette m_defaultpalette;
    bool m_isFullscreen;

public slots:
    void updateWidget();

    void setFullscreen();

    void setNormalMode();

};

}
}
}

#endif // BEERWIDGET_H
