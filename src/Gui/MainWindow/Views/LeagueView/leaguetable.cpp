#include "leaguetable.h"

#include <Database/league.h>
#include <QDebug>

LeagueTable::LeagueTable(Database::League* league, QWidget *parent) :
    QTableWidget(parent),
    m_league(league)
{
    this->setRowCount(league->players->value().size());
    this->setColumnCount(2);

    QList<Database::Player*> players = league->players->value();
    qSort(players.begin(),players.end(),sortByAverage);

    this->setHorizontalHeaderItem(0,new QTableWidgetItem("Name"));
    this->setHorizontalHeaderItem(1,new QTableWidgetItem("Average"));

    int row = 0;
    foreach(Database::Player* player, players) {
        this->setItem(row, 0, new QTableWidgetItem(player->name->value()));
        this->setItem(row, 1, new QTableWidgetItem(QString::number(player->average->value("General"))));
        row++;
    }
}

bool sortByAverage(Database::Player* player1, Database::Player* player2){
    return player1->average->value("General") > player2->average->value("General");
}
