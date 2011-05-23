#include "offlinegame.h"

#include <QTime>


START_ROW_IMPLEMENTATION(OfflineGame, Game, Game)
{
    m_calc = new OfflineGameCalculator(this);

    IMPLEMENT_DATABASEATTRIBUTE(QTime,OfflineGame,offline_length,tr("OfflineGameLength"))
}

QString OfflineGame::mimeType() const
{
    return "application/projectstats.offlineGame";
}

END_ROW_IMPLEMENTATION()
