#ifndef DRINKSCATEGORIE_H
#define DRINKSCATEGORIE_H

#include "childcategorie.h"

namespace Database
{

class DrinksCategorie : public ChildCategorie
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
    DrinksCategorie(int id, Categories *table);
};

}

#endif // DRINKSCATEGORIE_H
