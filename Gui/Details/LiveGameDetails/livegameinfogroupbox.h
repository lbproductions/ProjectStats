#ifndef LIVEGAMEINFOGROUPBOX_H
#define LIVEGAMEINFOGROUPBOX_H

#include <Gui/Details/LiveGameDetails/abstractlivegamewidget.h>

class QVBoxLayout;

namespace Database
{
    class LiveGame;
}

namespace Gui{

namespace Misc
{
    class HeaderLabel;
    class ValueLabel;
}

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

    Misc::HeaderLabel* m_typeHeaderLabel;
    Misc::ValueLabel* m_typeLabel;

    Misc::HeaderLabel* m_timeHeaderLabel;
    Misc::ValueLabel* m_timeLabel;

protected slots:
    void reflectState();

    void updateTime();
};

}
}
}

#endif // LIVEGAMEINFOGROUPBOX_H
