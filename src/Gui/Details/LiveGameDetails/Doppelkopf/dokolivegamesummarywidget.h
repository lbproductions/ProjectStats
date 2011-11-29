#ifndef GUI_DETAILS_LIVEGAMEDETAILS_DOKOLIVEGAMEDETAILS_DOKOLIVEGAMESUMMARYWIDGET_H
#define GUI_DETAILS_LIVEGAMEDETAILS_DOKOLIVEGAMEDETAILS_DOKOLIVEGAMESUMMARYWIDGET_H

#include <Gui/Details/LiveGameDetails/livegamesummarywidget.h>

namespace Database{
    class DokoLiveGame;
}

namespace Gui {
namespace Details {
namespace LiveGameDetails {
namespace DokoLiveGameDetails {

class DokoLiveGameSummaryWidget : public LiveGameSummaryWidget
{
public:
    DokoLiveGameSummaryWidget(Database::DokoLiveGame* game, QWidget* parent = 0);

    void setupDokoPlayersTab();

    void setupDokoStatsTab();

private:
    Database::DokoLiveGame* m_dokoLiveGame;
};

} // namespace DokoLiveGameDetails
} // namespace LiveGameDetails
} // namespace Details
} // namespace Gui

#endif // GUI_DETAILS_LIVEGAMEDETAILS_DOKOLIVEGAMEDETAILS_DOKOLIVEGAMESUMMARYWIDGET_H
