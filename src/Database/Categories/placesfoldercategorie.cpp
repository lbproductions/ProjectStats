#include "placesfoldercategorie.h"

#include "../table.h"
#include "../database.h"
#include "../place.h"

#include <Models/tablemodel.h>
#include <Gui/MainWindow/Views/ListView/listview.h>

#include <QIcon>
#include <QMimeData>

using namespace Database;

PlacesFolderCategorie::PlacesFolderCategorie(int id, Categories *table) :
    FolderCategorie(id,table)
{
    IMPLEMENT_LISTATTRIBUTE(Place*,PlacesFolderCategorie,places,tr("Places"))
}

QIcon PlacesFolderCategorie::icon() const
{
    return QIcon(":/graphics/icons/mac/sidebar/sidebar_folder_places");
}

QList<Place*> PlacesFolderCategorie::calculate_places()
{
    QList<Place*> places;
    foreach(int i, this->rows->value())
    {
        places.append(Places::instance()->rowById(i));
    }

    return places;
}

Models::TableModelBase *PlacesFolderCategorie::model()
{
    return Places::instance()->model();
}

Gui::MainWindow::Views::View *PlacesFolderCategorie::view()
{
    if(m_view.isNull())
    {
	m_view = new Gui::MainWindow::Views::ListView(this);
        m_view->setWindowTitle(QString::fromUtf8("Places \u2013 ")+name->value());
	m_view->setWindowIcon(icon());
    }

    return m_view;
}

void PlacesFolderCategorie::dropMimeData(const QMimeData *data)
{
    if(!acceptMimeTypes(data->formats()))
    {
	return;
    }

    QByteArray encodedData = data->data("application/projectstats.place");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);

    while (!stream.atEnd())
    {
	int id = -1;
	stream >> id;

        Place *p = Places::instance()->rowById(id);
        if(p)
	{
	    insertRow(p);
	}
    }
}
