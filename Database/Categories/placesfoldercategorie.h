#ifndef PLACESFOLDERCATEGORIE_H
#define PLACESFOLDERCATEGORIE_H

#include "foldercategorie.h"

namespace Database
{

class Place;
class Categories;

class PlacesFolderCategorie : public FolderCategorie
{
    Q_OBJECT
public:
    DECLARE_LISTATTRIBUTE(Place*,PlacesFolderCategorie,places)

    QIcon icon() const;

    Models::TableModelBase *model();

    Gui::MainWindow::Views::View *view();

    void dropMimeData(const QMimeData *data);

friend class Categories;
private:
    PlacesFolderCategorie(int id, Categories *table);
};

}

#endif // PLACESFOLDERCATEGORIE_H
