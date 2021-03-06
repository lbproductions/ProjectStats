#include "playersfoldercategorie.h"

#include "../table.h"
#include "../database.h"
#include "../player.h"

#include <Models/tablemodel.h>
#include <Gui/MainWindow/Views/ListView/listview.h>

#include <QIcon>
#include <QMimeData>

using namespace Database;

PlayersFolderCategorie::PlayersFolderCategorie(int id, Categories *table) :
    FolderCategorie(id,table)
{
    IMPLEMENT_LISTATTRIBUTE(Player*,PlayersFolderCategorie,players,tr("Players"))
}

QIcon PlayersFolderCategorie::icon() const
{
        return QIcon(":/graphics/icons/mac/sidebar/sidebar_folder_players");
}

QList<Player*> PlayersFolderCategorie::calculate_players()
{
    QList<Player*> players;
    foreach(int i, this->rows->value())
    {
        players.append(Players::instance()->rowById(i));
    }

    return players;
}

Models::TableModelBase *PlayersFolderCategorie::model()
{
    return Players::instance()->model();
}

Gui::MainWindow::Views::View *PlayersFolderCategorie::view()
{
    if(m_view.isNull())
    {
	m_view = new Gui::MainWindow::Views::ListView(this);
        m_view->setWindowTitle(QString::fromUtf8("Players \u2013 ")+name->value());
	m_view->setWindowIcon(icon());
    }

    return m_view;
}

void PlayersFolderCategorie::dropMimeData(const QMimeData *data)
{
    if(!acceptMimeTypes(data->formats()))
    {
	return;
    }

    QByteArray encodedData = data->data("application/projectstats.player");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);

    while (!stream.atEnd())
    {
	int id = -1;
	stream >> id;

        Player *p = Players::instance()->rowById(id);
        if(p != 0)
	{
	    insertRow(p);
	}
    }
}
