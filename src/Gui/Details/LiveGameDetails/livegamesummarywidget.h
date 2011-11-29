#ifndef GUI_DETAILS_LIVEGAMEDETAILS_LIVEGAMESUMMARYWIDGET_H
#define GUI_DETAILS_LIVEGAMEDETAILS_LIVEGAMESUMMARYWIDGET_H

#include <Gui/Details/GameDetails/gamesummarywidget.h>

namespace Database{
    class LiveGame;
}

namespace Gui {
namespace Details {
namespace LiveGameDetails {

class LiveGameSummaryWidget : public Gui::Details::GameDetails::GameSummaryWidget
{
public:
    LiveGameSummaryWidget(Database::LiveGame* game, QWidget *parent = 0);

protected:
    void setupDrinkTab();
    void setupGeneralTab();
    void setupCommentTab();

    Database::LiveGame* m_livegame;

protected slots:
    void update();
};

} // namespace LiveGameDetails
} // namespace Details
} // namespace Gui

#endif // GUI_DETAILS_LIVEGAMEDETAILS_LIVEGAMESUMMARYWIDGET_H
