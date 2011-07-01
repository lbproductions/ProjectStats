#ifndef PLAYERSFOLDERCATEGORIE_H
#define PLAYERSFOLDERCATEGORIE_H

#include "foldercategorie.h"

namespace Database
{

class Categories;

class PlayersFolderCategorie : public FolderCategorie
{
    Q_OBJECT
public:
    DECLARE_LISTATTRIBUTE(Player*,PlayersFolderCategorie,players)

    QIcon icon() const;

    Models::TableModelBase *model();

    Gui::MainWindow::Views::View *view();

    void dropMimeData(const QMimeData *data);

    friend class Categories;
private:
    PlayersFolderCategorie(int id, Categories *table);
};

}
#endif // PLAYERSFOLDERCATEGORIE_H
