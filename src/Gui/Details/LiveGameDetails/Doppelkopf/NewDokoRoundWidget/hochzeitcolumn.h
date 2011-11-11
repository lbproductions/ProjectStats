#ifndef HOCHZEITCOLUMN_H
#define HOCHZEITCOLUMN_H

#include "column.h"

namespace Database{
    class DokoLiveGame;
    class Player;
}

namespace Gui
{

namespace Details
{

namespace LiveGameDetails
{

namespace DokoLiveGameDetails{

class HochzeitColumn : public Column
{
public:
    HochzeitColumn(Database::DokoLiveGame* game, QGridLayout* layout, int minRow, int column, QObject* parent = 0);

public slots:
    void update(Misc::CheckBox* check, bool checked);

    void onRePlayersChanged(QMap<Database::Player*,bool> map, int reCount);

signals:
    void hochzeitPlayerChanged(Database::Player*, bool);

private:
    QPointer<Database::Player> m_hochzeitPlayer;
};

}}}}

#endif // HOCHZEITCOLUMN_H
