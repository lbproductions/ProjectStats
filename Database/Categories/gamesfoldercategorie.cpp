#include "gamesfoldercategorie.h"

#include "../table.h"
#include "../database.h"
#include "../game.h"

#include <Models/tablemodel.h>
#include <Gui/MainWindow/Views/ListView/listview.h>

#include <QIcon>
#include <QMimeData>

using namespace Database;

GamesFolderCategorie::GamesFolderCategorie(int id, Categories *table) :
    FolderCategorie(id,table)
{
    IMPLEMENT_LISTATTRIBUTE(Game*,GamesFolderCategorie,games,tr("Games"))
}

QIcon GamesFolderCategorie::icon() const
{
    return QIcon(":/graphics/icons/mac/sidebar/sidebar_folder_games");

}

AttributeList<Game*> GamesFolderCategorie::calculate_games()
{
    AttributeList<Game*> games;
    foreach(int i, this->rows->value())
    {
        games.append(Games::instance()->rowById(i));
    }

    return games;
}

Models::TableModelBase *GamesFolderCategorie::model()
{
    return Games::instance()->model();
}

Gui::MainWindow::Views::View *GamesFolderCategorie::view()
{
    if(m_view.isNull())
    {
	m_view = new Gui::MainWindow::Views::ListView(this);
        m_view->setWindowTitle(QString::fromUtf8("Games \u2013 ")+name->value());
	m_view->setWindowIcon(icon());
    }

    return m_view;
}

void GamesFolderCategorie::dropMimeData(const QMimeData *data)
{
    if(!acceptMimeTypes(data->formats()))
    {
	return;
    }

    QByteArray encodedData = data->data("application/projectstats.game");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);

    while (!stream.atEnd())
    {
	int id = -1;
	stream >> id;

        Game *g = Games::instance()->rowById(id);
	if(g != 0 && g->isValid())
	{
	    insertRow(g);
	}
    }
}
