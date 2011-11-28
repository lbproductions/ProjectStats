#ifndef LEAGUEFOLDERCATEGORIE_H
#define LEAGUEFOLDERCATEGORIE_H

#include "foldercategorie.h"
#include <Models/tablemodel.h>

#include <QStack>

namespace Database
{

class Categories;
class Games;
class Player;
class SmartFolderCategorie;
class PlayersFolderCategorie;

}

START_ROW_DECLARATION(LeagueFolderCategorie, FolderCategorie)
    DECLARE_ROW_CONSTRUCTORS(LeagueFolderCategorie, FolderCategorie)

    QIcon icon() const;

    Gui::MainWindow::Views::View *view();

    void addPlayer(Player* player);

private:
    DECLARE_ATTRIBUTE(PlayersFolderCategorie*, LeagueFolderCategorie, playersFolder)
    DECLARE_ATTRIBUTE(SmartFolderCategorie*, LeagueFolderCategorie, gamesFolder)

END_ROW_DECLARATION(LeagueFolderCategorie)

#endif // LEAGUEFOLDERCATEGORIE_H
