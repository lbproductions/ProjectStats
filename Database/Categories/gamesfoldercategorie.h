#ifndef GAMESFOLDERCATEGORIE_H
#define GAMESFOLDERCATEGORIE_H

#include "foldercategorie.h"

namespace Database
{

class Categories;

class GamesFolderCategorie : public FolderCategorie
{
    Q_OBJECT
public:
    DECLARE_LISTATTRIBUTE(Game*,GamesFolderCategorie,games)

    QIcon icon() const;

    Models::TableModelBase *model();

    Gui::MainWindow::Views::View *view();

    void dropMimeData(const QMimeData *data);

friend class Categories;
private:
    GamesFolderCategorie(int id, Categories *table);
};

}

#endif // GAMESFOLDERCATEGORIE_H
