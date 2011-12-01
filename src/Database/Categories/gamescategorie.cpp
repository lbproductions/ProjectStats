#include "gamescategorie.h"

#include "../categorie.h"
#include <LBDatabase/LBDatabase.h>
#include "../game.h"

#include <Gui/MainWindow/Views/ListView/listview.h>

#include <QIcon>

using namespace Database;

GamesCategorie::GamesCategorie(int id, Categories *table) :
    ChildCategorie(id,table)
{
}

Models::TableModelBase *GamesCategorie::model()
{
    return Games::instance()->model();
}

Gui::MainWindow::Views::View *GamesCategorie::view()
{
    if(!m_view)
    {
        m_view = new Gui::MainWindow::Views::ListView(this);
        m_view->setWindowTitle("Games");
        m_view->setWindowIcon(QIcon(icon->value()));
    }

    return m_view;
}
