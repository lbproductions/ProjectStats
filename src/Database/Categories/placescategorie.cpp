#include "placescategorie.h"

#include "../categorie.h"
#include <LBDatabase/LBDatabase.h>
#include "../place.h"

#include <Gui/MainWindow/Views/ListView/listview.h>

#include <QIcon>

using namespace Database;

PlacesCategorie::PlacesCategorie(int id, Categories *table) :
    ChildCategorie(id,table)
{
}

Models::TableModelBase *PlacesCategorie::model()
{
    return Places::instance()->model();
}

Gui::MainWindow::Views::View *PlacesCategorie::view()
{
    if(!m_view)
    {
        m_view = new Gui::MainWindow::Views::ListView(this);
        m_view->setWindowTitle("Places");
        m_view->setWindowIcon(QIcon(icon->value()));
    }

    return m_view;
}
