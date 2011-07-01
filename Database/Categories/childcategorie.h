#ifndef CHILDCATEGORIE_H
#define CHILDCATEGORIE_H

#include "../categorie.h"
#include <Models/tablemodel.h>

namespace Gui
{
    namespace MainWindow
    {
	namespace Views
	{
	    class View;
	}
    }
}

namespace Database
{

class Categories;
class ParentCategorie;

class ChildCategorie : public Categorie
{
    Q_OBJECT
public:
    /*!
      Gibt an, welchen Typ diese Kategorie hat.
      */
    enum CategorieContentType {
	GamesCategorieContentType, //!< Die Kategorie enthält Spiele
	PlayersCategorieContentType, //!< Die Kategorie enthält Spieler
	DrinksCategorieContentType, //!< Die Kategorie enthält Drinks
        PlacesCategorieContentType, //!< Die Kategorie enthält Places
        LeagueCategorieContentType //!< Die Kategorie enthält Places
    };

    ChildCategorie(int id, Categories *table);

    /*!
      \return Der Vater dieser Kategorie, sprich die Überschrift unter der sie in der Sidebar eingefügt ist.
      */
    DECLARE_ATTRIBUTE(ParentCategorie*,ChildCategorie,parentCategorie)

    /*!
      \return Das TableModel, welches alle Elemente, die in dieser Kategorie enhalten sind, beschreibt.
      */
    virtual Models::TableModelBase* model();

    virtual Gui::MainWindow::Views::View *view();

friend class ParentCategorie;
protected:
    QPointer<Gui::MainWindow::Views::View> m_view;

};

}
#endif // CHILDCATEGORIE_H
