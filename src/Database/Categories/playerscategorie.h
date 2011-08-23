#ifndef PLAYERSCATEGORIE_H
#define PLAYERSCATEGORIE_H

#include "childcategorie.h"

namespace Database
{

class PlayersCategorie : public ChildCategorie
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
    PlayersCategorie(int id, Categories *table);
};

}


#endif // PLAYERSCATEGORIE_H
