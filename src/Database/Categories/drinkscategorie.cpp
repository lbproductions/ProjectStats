#include "drinkscategorie.h"

#include "../categorie.h"
#include "../drink.h"

#include <Gui/MainWindow/Views/ListView/listview.h>

#include <QIcon>

using namespace Database;

DrinksCategorie::DrinksCategorie(int id, Categories *table) :
    ChildCategorie(id,table)
{
}

Models::TableModelBase *DrinksCategorie::model()
{
    return Drinks::instance()->model();
}

Gui::MainWindow::Views::View *DrinksCategorie::view()
{
    if(!m_view)
    {
        m_view = new Gui::MainWindow::Views::ListView(this);
        m_view->setWindowTitle("Drinks");
        m_view->setWindowIcon(QIcon(icon->value()));
    }

    return m_view;
}
