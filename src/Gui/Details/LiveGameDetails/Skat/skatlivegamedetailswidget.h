#ifndef SKATLIVEGAMEDETAILSWIDGET_H
#define SKATLIVEGAMEDETAILSWIDGET_H

#include <Gui/Details/LiveGameDetails/livegamedetailswidget.h>
#include <QPointer>

namespace Database
{
    class Player;
    namespace Skat
    {
        class SkatLiveGame;
    }
}

namespace Gui
{

namespace Details
{

namespace LiveGameDetails
{
    namespace SkatLiveGameDetails{
        class NewSkatRoundWidget;
    }
}

class SkatLiveGameDetailsWidget : public LiveGameDetails::LiveGameDetailsWidget
{
public:
    SkatLiveGameDetailsWidget(Database::Skat::SkatLiveGame* game, QWidget *parent = 0);

    void initializeItems();

    /**
     * Überprüft ob das laufende Skat-Spiel beendet werden muss
     */
    void checkForEndOfGame();

private:
    QPointer<LiveGameDetails::SkatLiveGameDetails::NewSkatRoundWidget> m_skatRoundWidget;
    QPointer<Database::Skat::SkatLiveGame> m_skatlivegame;

private slots:
    /**
     * Zeigt das NewSkatRoundWidget an.
     */
    void showRoundWidget();
};
}}
#endif // SKATLIVEGAMEDETAILSWIDGET_H
