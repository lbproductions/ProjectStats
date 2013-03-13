#ifndef PLAYERSCOMBOBOX_H
#define PLAYERSCOMBOBOX_H

#include <QComboBox>

namespace Database {
class Player;
}

class PlayersComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit PlayersComboBox(QWidget *parent = 0);

    void addPlayers(QList<Database::Player *> players);
    void addPlayer(Database::Player * const player);

    QList<Database::Player *> players() const;
    Database::Player *currentPlayer() const;
    void setCurrentPlayer(Database::Player *player);

    void removePlayer(Database::Player *player);

private:
    QList<Database::Player *> m_players;
    
};

#endif // PLAYERSCOMBOBOX_H
