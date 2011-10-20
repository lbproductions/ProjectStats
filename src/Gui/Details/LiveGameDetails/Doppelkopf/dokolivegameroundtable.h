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
    Q_OBJECT
public:
    DokoLiveGameRoundTable(Database::DokoLiveGame* livegame, QWidget *parent = 0);

    void addRound(::Database::Round* round);

    DokoLiveGameRoundTableItem* itemAtIndex(const QModelIndex& index);

private slots:
    void on_customContextMenuRequested(const QPoint &pos);
    void on_editRoundActionTriggered();
};

}
}
}
}

#endif // DOKOLIVEGAMEROUNDTABLE_H
