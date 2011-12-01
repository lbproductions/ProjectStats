#ifndef LEAGUEFOLDERCATEGORIE_H
#define LEAGUEFOLDERCATEGORIE_H

#include "foldercategorie.h"
#include <LBDatabase/Models/tablemodel.h>

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

    LeagueFolderCategorie(const QString& name);

    QIcon icon() const;

    Gui::MainWindow::Views::View *view();

    Models::TableModelBase* gamesModel();
    Models::TableModelBase* playersModel();

    void addPlayer(Player* player);
    void setStartDate(const QDate& date);
    void setEndDate(const QDate &date);

private:
    DECLARE_ATTRIBUTE(PlayersFolderCategorie*, LeagueFolderCategorie, playersFolder)
    DECLARE_ATTRIBUTE(SmartFolderCategorie*, LeagueFolderCategorie, gamesFolder)

    Models::TableModelBase* m_gamesModel;
    Models::TableModelBase* m_playersModel;


END_ROW_DECLARATION(LeagueFolderCategorie)

#endif // LEAGUEFOLDERCATEGORIE_H
