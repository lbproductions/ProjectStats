#ifndef PLACESCATEGORIE_H
#define PLACESCATEGORIE_H

#include "childcategorie.h"

namespace Database
{

class PlacesCategorie : public ChildCategorie
{
    Q_OBJECT
public:
    /*!
      \return Das TableModel, welches alle Elemente, die in dieser Kategorie enhalten sind, beschreibt.
      */
    Models::TableModelBase *model();

    Gui::MainWindow::Views::View *view();

friend class Categories;
private:
    PlacesCategorie(int id, Categories *table);
};

}

#endif // PLACESCATEGORIE_H
