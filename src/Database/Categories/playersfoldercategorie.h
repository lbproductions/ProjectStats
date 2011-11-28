#ifndef PLAYERSFOLDERCATEGORIE_H
#define PLAYERSFOLDERCATEGORIE_H

#include "foldercategorie.h"

namespace Database
{
class Player;
}

START_ROW_DECLARATION(PlayersFolderCategorie, FolderCategorie)
    DECLARE_ROW_CONSTRUCTORS(PlayersFolderCategorie, FolderCategorie)

    DECLARE_LISTATTRIBUTE(Player*,PlayersFolderCategorie,players)

    QIcon icon() const;

    Models::TableModelBase *model();

    Gui::MainWindow::Views::View *view();

    void dropMimeData(const QMimeData *data);

    void addPlayer(Player* player);

END_ROW_DECLARATION(PlayersFolderCategorie)

#endif // PLAYERSFOLDERCATEGORIE_H
