#ifndef DRINKSFOLDERCATEGORIE_H
#define DRINKSFOLDERCATEGORIE_H

#include "foldercategorie.h"

namespace Database
{

class Drink;
class Categories;

class DrinksFolderCategorie : public FolderCategorie
{
    Q_OBJECT
public:
    DECLARE_LISTATTRIBUTE(Drink*,DrinksFolderCategorie,drinks)

    QIcon icon() const;

    Models::TableModelBase *model();

    Gui::MainWindow::Views::View *view();

    void dropMimeData(const QMimeData *data);

    friend class Categories;
private:
    DrinksFolderCategorie(int id, Categories *table);
};
}
#endif // DRINKSFOLDERCATEGORIE_H
