#ifndef LEAGUEVIEW_H
#define LEAGUEVIEW_H

#include "../view.h"

namespace Database
{
    class LeagueFolderCategorie;
}

namespace Gui
{

namespace MainWindow
{
namespace Views
{

namespace LeagueViewDetails{
    class LeagueOverviewWidget;
    class LeagueGraphWidget;
    class LeagueStatsWidget;
}

class LeagueView : public View
{
    Q_OBJECT
public:
    LeagueView(Database::LeagueFolderCategorie *categorie, MainWindow *parent = 0);

    ~LeagueView();

    void updateStatusbar();

private:
    void saveSettings();
    void restoreSettings();

    QPointer<Database::LeagueFolderCategorie> m_categorie;
    QPointer<Gui::MainWindow::Views::LeagueViewDetails::LeagueOverviewWidget> m_overviewwidget;
    QPointer<Gui::MainWindow::Views::LeagueViewDetails::LeagueGraphWidget> m_graphwidget;
    QPointer<Gui::MainWindow::Views::LeagueViewDetails::LeagueStatsWidget> m_statswidget;


};

}}}

#endif // LEAGUEVIEW_H
