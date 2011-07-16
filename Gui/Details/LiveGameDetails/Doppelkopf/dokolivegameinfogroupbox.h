#ifndef DOKOLIVEGAMEINFOGROUPBOX_H
#define DOKOLIVEGAMEINFOGROUPBOX_H

#include <Gui/Details/LiveGameDetails/livegameinfogroupbox.h>

namespace Database
{
    class DokoLiveGame;
}

namespace Gui
{

namespace Details
{

namespace LiveGameDetails
{

namespace DokoLiveGameDetails{

class DokoLiveGameInfoGroupBox : public LiveGameInfoGroupBox
{
public:
    DokoLiveGameInfoGroupBox(Database::DokoLiveGame* dokogame, QWidget *parent = 0);

    void updateWidget(QString lengthText);

private:

    Database::DokoLiveGame* m_dokogame;
};

}
}
}
}

#endif // DOKOLIVEGAMEINFOGROUPBOX_H
