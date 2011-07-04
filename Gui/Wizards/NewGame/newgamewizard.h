#ifndef NEWGAMEWIZARD_H
#define NEWGAMEWIZARD_H

#include <QWizard>
#include <QPointer>

namespace Database
{
    class Game;
}

namespace Gui
{

namespace Wizards
{

namespace NewGame
{
    class LiveOfflineGameWidget;
    class OfflineGameResultWidget;
    class OfflineSummaryWidget;
    class OfflineDetailledGameDokoWidget;
    class LiveGameGeneralOptionsWidget;
    class LiveDokoGameOptionsWidget;
    class LiveSummaryWidget;
    class WizardSideWidget;
    class SkatLiveGameOptionsWidget;
}

/**
 * Der Wizard hat die Aufgabe ein neues Game zu erstellen. Dabei wird differenziert zwischen einem OfflineGame und einem LiveGame.
 * Diese Klasse verwaltet die einzelnen WizardPages.
 */
class NewGameWizard : public QWizard
{
    Q_OBJECT

public:
    explicit NewGameWizard(QWidget *parent = 0);

    /**
     * WizardPages werden erstellt, Namen festgelegt
     */
    void initializeWidget();

    enum wizardWidgets {
        Page_LiveOfflineGame,
        Page_OfflineGameOptions,
        Page_OfflineGameResult,
        Page_LiveGameGeneralOptions,
        Page_LiveGameDokoOptions,
        Page_OfflineSummary ,
        Page_DetailledOfflineDokoGame ,
        Page_LiveSummary,
        Page_StartLiveGame,
        Page_SkatLiveGameOptionsWidget
    };

    void setGame(Database::Game *game);
    Database::Game *game() const;

private:
    QPointer<NewGame::LiveOfflineGameWidget> m_liveOfflineGameWidget;
    QPointer<NewGame::OfflineGameResultWidget> m_offlineGameResultWidget;
    QPointer<NewGame::OfflineSummaryWidget> m_offlineSummaryWidget;
    QPointer<NewGame::OfflineDetailledGameDokoWidget> m_offlineDokoWidget;
    QPointer<NewGame::LiveGameGeneralOptionsWidget> m_liveGameGeneralOptionsWidget;
    QPointer<NewGame::LiveDokoGameOptionsWidget> m_liveDokoGameOptionsWidget;
    QPointer<NewGame::LiveSummaryWidget> m_liveSummaryWidget;
    QPointer<NewGame::SkatLiveGameOptionsWidget> m_skatLiveGameOptionsWidget;

    QPointer<NewGame::WizardSideWidget> m_sideWidget;
};

}
}

#endif // NEWGAMEWIZARD_H
