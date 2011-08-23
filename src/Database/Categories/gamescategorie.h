#ifndef GAMESCATEGORIE_H
#define GAMESCATEGORIE_H

#include "childcategorie.h"

namespace Database
{

class GamesCategorie : public ChildCategorie
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
    GamesCategorie(int id, Categories *table);
};

}
#endif // GAMESCATEGORIE_H
