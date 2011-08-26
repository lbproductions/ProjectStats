#ifndef DOKOLIVEGAMEROUNDTABLE_H
#define DOKOLIVEGAMEROUNDTABLE_H

#include <Gui/Details/LiveGameDetails/livegameroundtable.h>

namespace Database
{
    class DokoLiveGame;
    class DokoRound;
}

namespace Gui
{

namespace Details
{

namespace LiveGameDetails
{

namespace DokoLiveGameDetails
{

class DokoLiveGameRoundTableItem;

class DokoLiveGameRoundTable : public LiveGameRoundTable
{
public:
    DokoLiveGameRoundTable(Database::DokoLiveGame* livegame, QWidget *parent = 0);

    void addRound(::Database::Round* round);

    DokoLiveGameRoundTableItem* itemAtIndex(const QModelIndex& index);
};

}
}
}
}

#endif // DOKOLIVEGAMEROUNDTABLE_H
