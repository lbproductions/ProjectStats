#ifndef NEWGAMEWIZARD_H
#define NEWGAMEWIZARD_H

#include <QWizard>
#include <QPointer>

namespace Database
{
    class Game;
    class DokoLiveGame;
}

namespace Gui
{

namespace Misc
{
    class PlacesComboBox;
}

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
        Page_StartLiveGame,
        Page_SkatLiveGameOptionsWidget
    };

private slots:
    void on_accepted();

private:
    NewGame::LiveOfflineGameWidget* m_liveOfflineGameWidget;
    NewGame::OfflineGameResultWidget* m_offlineGameResultWidget;
    NewGame::OfflineSummaryWidget* m_offlineSummaryWidget;
    NewGame::OfflineDetailledGameDokoWidget* m_offlineDokoWidget;
    NewGame::LiveGameGeneralOptionsWidget* m_liveGameGeneralOptionsWidget;
    NewGame::LiveDokoGameOptionsWidget* m_liveDokoGameOptionsWidget;
    NewGame::SkatLiveGameOptionsWidget* m_skatLiveGameOptionsWidget;

    NewGame::WizardSideWidget* m_sideWidget;

    Database::DokoLiveGame *createDokoLiveGame();


};

}
}

#endif // NEWGAMEWIZARD_H
