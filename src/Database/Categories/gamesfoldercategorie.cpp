#include "gamesfoldercategorie.h"

#include <LBDatabase/LBDatabase.h>
#include "../game.h"

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

QList<Game*> GamesFolderCategorie::calculate_games()
{
    QList<Game*> games;
    foreach(int i, this->rows->value())
    {
        games.append(Games::instance()->castedRowById(i));
    }

    return games;
}

Models::TableModelBase *GamesFolderCategorie::model()
{
    return Games::instance()->model();
}

Gui::MainWindow::Views::View *GamesFolderCategorie::view()
{
    if(!m_view)
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

        Game *g = Games::instance()->castedRowById(id);
        if(g)
	{
	    insertRow(g);
	}
    }
}
