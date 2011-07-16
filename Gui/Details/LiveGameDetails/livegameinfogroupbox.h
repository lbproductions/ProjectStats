#ifndef LIVEGAMEINFOGROUPBOX_H
#define LIVEGAMEINFOGROUPBOX_H

#include <Gui/Details/LiveGameDetails/abstractlivegamewidget.h>

class QVBoxLayout;

namespace Database
{
    class LiveGame;
}

namespace Gui{

namespace Details{

namespace LiveGameDetails{

class LiveGameInfoGroupBox : public AbstractLiveGameWidget
{
    Q_OBJECT
public:
    explicit LiveGameInfoGroupBox(Database::LiveGame* livegame, QWidget *parent = 0);

protected:
    Database::LiveGame* m_game;
    QVBoxLayout* m_layout;
};

}
}
}

#endif // LIVEGAMEINFOGROUPBOX_H
