#ifndef SKATLIVEGAMEROWWINDOW_H
#define SKATLIVEGAMEROWWINDOW_H

#include <Gui/Details/LiveGameDetails/livegamerowwindow.h>

#include <QPointer>

namespace Database
{
    namespace Skat
    {
        class SkatLiveGame;
    }
}

namespace Gui
{

namespace Details
{

class SkatLiveGameDetailsWidget;

class SkatLiveGameRowWindow : public LiveGameRowWindow
{
public:
    SkatLiveGameRowWindow(Database::Skat::SkatLiveGame* skatgame, QWidget *parent = 0);

private:
    QPointer<Database::Skat::SkatLiveGame> m_skatlivegame;
};

}}

#endif // SKATLIVEGAMEROWWINDOW_H
