#include "playerscategorie.h"

#include "../categorie.h"
#include "../database.h"
#include <Database/player.h>

#include <Models/tablemodel.h>
#include <Gui/MainWindow/Views/ListView/listview.h>

#include <QIcon>

using namespace Database;

PlayersCategorie::PlayersCategorie(int id, Categories *table) :
    ChildCategorie(id,table)
{
}

Models::TableModelBase *PlayersCategorie::model()
{
    return Players::instance()->model();
}

Gui::MainWindow::Views::View *PlayersCategorie::view()
{
    if(!m_view)
    {
        m_view = new Gui::MainWindow::Views::ListView(this);
        m_view->setWindowTitle("Players");
        m_view->setWindowIcon(QIcon(icon->value()));
    }

    return m_view;
}
