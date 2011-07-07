#ifndef LIVEGAMESUMMARYWIDGET_H
#define LIVEGAMESUMMARYWIDGET_H

#include <Gui/Details/GameDetails/gamesummarywidget.h>
#include <QPointer>

namespace Database{
    class LiveGame;
    class Drink;
    class Player;
}

namespace Gui
{

namespace Details
{

namespace LiveGameDetails{

class LiveGameSummaryWidget : public Gui::Details::GameDetails::GameSummaryWidget
{
public:
    LiveGameSummaryWidget(Database::LiveGame* game, QWidget *parent = 0);

    void initData();

    void createDrinkTab();

private:

    QList<QPointer<Database::Drink> > m_drinklist;
    QPointer<Database::LiveGame> m_livegame;

    QList<QPair<Database::Player*,Database::LiveGame*> > m_mostdrinks;
    QList<QPair<Database::Player*,Database::LiveGame*> > m_drunkenplayer;
};

}}}

#endif // LIVEGAMESUMMARYWIDGET_H
