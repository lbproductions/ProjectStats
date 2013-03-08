#ifndef LEAGUEHACKTABLE_H
#define LEAGUEHACKTABLE_H

#include <QTableWidget>

namespace Database{
    class League;
    class Player;
}

class LeagueTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit LeagueTable(Database::League* league, QWidget *parent);
    
signals:
    
public slots:

private:
    Database::League* m_league;
    
};

bool sortByAverage(Database::Player* player1, Database::Player* player2);

#endif // LEAGUEHACKTABLE_H
