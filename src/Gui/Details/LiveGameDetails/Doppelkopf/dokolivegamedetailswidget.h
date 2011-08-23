#ifndef DOKOLIVEGAMEDETAILSWIDGET_H
#define DOKOLIVEGAMEDETAILSWIDGET_H

#include <Gui/Details/LiveGameDetails/livegamedetailswidget.h>
#include <QPointer>

namespace Database
{
    class Player;
    class DokoLiveGame;
}

namespace Gui
{

namespace Details
{

namespace LiveGameDetails
{
    namespace DokoLiveGameDetails{
        class DokoLiveGamePlayerStatsWidget;
        class NewDokoRoundWidget;
        class DokoLiveGameSettingsWidget;
        class SchmeissereiWidget;
    }
}

/**
 * Verwaltet die Anzeige des LiveGameWidgets.
 */
class DokoLiveGameDetailsWidget : public LiveGameDetails::LiveGameDetailsWidget
{

public:
    /**
     * Erstellt das LiveGameStatsWidget. Dabei wird die UI erstellt, die QTime des Spiels gestartet und die Variablen für die Zeitmessung initialisiert.
     */
    explicit DokoLiveGameDetailsWidget(Database::DokoLiveGame *game, QWidget *parent = 0);

    ~DokoLiveGameDetailsWidget();

    void initializeItems();

private:
    QPointer<Database::DokoLiveGame> m_dokolivegame;
    QPointer<LiveGameDetails::DokoLiveGameDetails::NewDokoRoundWidget> m_dokoRoundWidget;
};

}
}

#endif // DOKOLIVEGAMEDETAILSWIDGET_H
