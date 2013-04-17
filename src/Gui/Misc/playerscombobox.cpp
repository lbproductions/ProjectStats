#include "playerscombobox.h"

#include <Database/player.h>

PlayersComboBox::PlayersComboBox(QWidget *parent) :
    QComboBox(parent)
{
    addItem(tr("---"), 0);
}

void PlayersComboBox::addPlayers(QList<Database::Player *> players)
{
    foreach(Database::Player *player, players) {
        addPlayer(player);
    }
}

void PlayersComboBox::addPlayer(Database::Player * const player)
{
    if(m_players.contains(player))
        return;

    m_players.append(player);
    addItem(QIcon(QPixmap::fromImage(player->avatar->value())),
            player->name->value(),
            QVariant::fromValue<Database::Player *>(player));
}

QList<Database::Player *> PlayersComboBox::players() const
{
    return m_players;
}

Database::Player *PlayersComboBox::currentPlayer() const
{
    return itemData(currentIndex()).value<Database::Player *>();
}

void PlayersComboBox::setCurrentPlayer(Database::Player *player)
{
    for(int i = 0; i < count(); ++i) {
        if(itemData(i).value<Database::Player *>() == player) {
            setCurrentIndex(i);
            return;
        }
    }

    setCurrentIndex(0);
}

void PlayersComboBox::removePlayer(Database::Player *player)
{
    for(int i = 0; i < count(); ++i) {
        if(itemData(i).value<Database::Player *>() == player) {
            m_players.removeAll(player);
            removeItem(i);
            return;
        }
    }
}
