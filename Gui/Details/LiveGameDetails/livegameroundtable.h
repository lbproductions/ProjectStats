#ifndef LIVEGAMEROUNDTABLE_H
#define LIVEGAMEROUNDTABLE_H

#include <QTableWidget>
#include <QPointer>

namespace Database
{
    class Player;
    class Round;
    class LiveGame;
}

namespace Gui
{

namespace Details
{

namespace LiveGameDetails
{

/**
* Widget, das die einzelnen Runden eines DokoLiveGames anzeigt.
*/
class LiveGameRoundTable : public QTableWidget
{
    Q_OBJECT
public:
    /**
    * Erstellt eine neue Instanz der LiveGameRoundTable für das übergebene DokoLiveGame. Dabei wird für jeden Spieler und zusätzlich für die Runden-Punkte eine neue Spalte hinzugefügt.
    */
    explicit LiveGameRoundTable(Database::LiveGame* livegame, QWidget *parent = 0);

    /**
    * Fügt zur Tabelle eine neue Runde hinzu. Für diese wird eine neue Reihe erstellt und mit den Daten aus der Runde befüllt.
    */
    virtual void addRound(Database::Round *round);

    /**
    * Aktualisiert die Spaltenbreite je nachdem wie breit das gesamte Widget ist.
    */
    void updateSizes();

private slots:
    /**
    * Markiert das HeaderItem des aktuellen Cardmixers durch einen farbigen Hintergrund
    */
    void markCardMixer();

    void addCurrentRound();

protected:

    QPointer<Database::LiveGame> m_livegame;
};

}
}
}

#endif // LIVEGAMEROUNDTABLE_H
