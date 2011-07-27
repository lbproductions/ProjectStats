#ifndef LEAGUEFOLDERCATEGORIE_H
#define LEAGUEFOLDERCATEGORIE_H

#include "foldercategorie.h"
#include <Models/tablemodel.h>

#include <QStack>

namespace Database
{

class Categories;
class Games;
class Players;

namespace Filters{
    class LeagueFilter;
}

}


START_ROW_DECLARATION(LeagueFolderCategorie, FolderCategorie)
    DECLARE_ROW_CONSTRUCTORS(LeagueFolderCategorie, FolderCategorie)

    QList<Game*> games();

    QList<Player*> players();

    QIcon icon() const;

    Gui::MainWindow::Views::View *view();

    Models::TableModelBase* gamesModel();

    Models::TableModelBase* playersModel();

    void setPlayers(QList<Player*> players);

    void setFilter(QPointer<Filters::LeagueFilter> filter);

    QPixmap placeChangeOfPlayer(Player* p);

    int placementOfPlayer(Player* p);

    Filters::LeagueFilter* createFilter();

private slots:
    void matchBack();
    void matchNext();

private:

    QList<Game*> m_games;
    QList<Player*> m_players;

    QPointer<Filters::LeagueFilter> m_filter;

    QPointer<Models::TableModel<Game,Games> > m_gameModel;
    QPointer<Models::TableModel<Player,Players> > m_playerModel;

    QStack<QPointer<Game> > m_gamesstack;
    QHash<QString,int> m_placementhash; //! bildet von Spielername.Spieltag auf Platzierung ab

    QPointer<Gui::MainWindow::Views::View> m_view;

    int m_currentMatchday;

END_ROW_DECLARATION(LeagueFolderCategorie)

#endif // LEAGUEFOLDERCATEGORIE_H
