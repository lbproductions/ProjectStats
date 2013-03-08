#ifndef LEAGUEFOLDERCATEGORIE_H
#define LEAGUEFOLDERCATEGORIE_H

#include "foldercategorie.h"
#include <Models/tablemodel.h>
#include <Database/player.h>
#include <Database/game.h>

namespace Database
{

class Categories;
class League;

}


START_ROW_DECLARATION(LeagueFolderCategorie, FolderCategorie)
    DECLARE_ROW_CONSTRUCTORS(LeagueFolderCategorie, FolderCategorie)

    QIcon icon() const;

    Gui::MainWindow::Views::View *view();

    Models::TableModel<Game,Games>* gamesModel();

    Models::TableModel<Player,Players>* playersModel();

    League* league();

private:
    Models::TableModel<Game,Games>* m_gameModel;
    Models::TableModel<Player,Players>* m_playerModel;

    QPointer<Gui::MainWindow::Views::View> m_view;

    League* m_league;

END_ROW_DECLARATION(LeagueFolderCategorie)

#endif // LEAGUEFOLDERCATEGORIE_H
