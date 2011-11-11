#ifndef RECOLUMN_H
#define RECOLUMN_H

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

class ReColumn : public Column
{
public:
    ReColumn(Database::DokoLiveGame* game, QGridLayout* layout, int minRow, int column, QObject* parent = 0);

    QList<Database::Player*> rePlayers();

public slots:
    void update(Misc::CheckBox* check ,bool checked);

    void onHochzeitPlayerChanged(Database::Player* player, bool hochzeit);

signals:
    void rePlayersChanged(QMap<Database::Player*,bool>,int);

private:
    int m_reCount;

    QMap<Database::Player*,bool> m_reMap;

};

}}}}

#endif // RECOLUMN_H
