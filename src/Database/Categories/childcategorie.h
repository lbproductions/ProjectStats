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

class Categories;
class ParentCategorie;

START_ROW_DECLARATION(ChildCategorie, Categorie)
    DECLARE_ROW_CONSTRUCTORS(ChildCategorie, Categorie)
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

    /*!
      \return Der Vater dieser Kategorie, sprich die Überschrift unter der sie in der Sidebar eingefügt ist.
      */
    DECLARE_ATTRIBUTE(QPointer<ParentCategorie>,ChildCategorie,parentCategorie)
    DECLARE_DATABASEATTRIBUTE(QString,Categorie,icon)
    DECLARE_DATABASEATTRIBUTE(int,Categorie,parentId)
    DECLARE_DATABASEATTRIBUTE(int,Categorie,contentType)

    /*!
      \return Das TableModel, welches alle Elemente, die in dieser Kategorie enhalten sind, beschreibt.
      */
    virtual Models::TableModelBase* model();

    virtual Gui::MainWindow::Views::View *view();

friend class ParentCategorie;
protected:
    QPointer<Gui::MainWindow::Views::View> m_view;

END_ROW_DECLARATION(ChildCategorie)
#endif // CHILDCATEGORIE_H
