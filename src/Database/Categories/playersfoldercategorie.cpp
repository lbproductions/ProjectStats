#include "playersfoldercategorie.h"

#include <LBDatabase/LBDatabase.h>

#include "../player.h"
#include "leaguefoldercategorie.h"

#include <LBDatabase/LBDatabase.h>
#include <Gui/MainWindow/Views/ListView/listview.h>

#include <QIcon>
#include <QMimeData>

using namespace Database;

PlayersFolderCategorie::PlayersFolderCategorie() :
    FolderCategorie(0,Categories::instance())
{
    initializeAttributes();
}

PlayersFolderCategorie::PlayersFolderCategorie(LeagueFolderCategorie* /*parent*/) :
    FolderCategorie(0,Categories::instance())
{
    initializeAttributes();

    this->contentType->setValue(ChildCategorie::PlayersCategorieContentType);
}

PlayersFolderCategorie::PlayersFolderCategorie(const PlayersFolderCategorie &other) :
    FolderCategorie(other.m_id, other.m_table)
{
    initializeAttributes();
}

PlayersFolderCategorie::PlayersFolderCategorie(int id, TableBase *table) :
    FolderCategorie(id,table)
{
    initializeAttributes();
}

void PlayersFolderCategorie::initializeAttributes()
{
    IMPLEMENT_LISTATTRIBUTE(Player*,PlayersFolderCategorie,players,tr("Players"))
}

QString PlayersFolderCategorie::mimeType() const
{
    return FolderCategorie::mimeType();
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
    if(!m_view)
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

void PlayersFolderCategorie::addPlayer(Player *player)
{
    insertRow(player);
}
