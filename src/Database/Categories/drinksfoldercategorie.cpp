#include "drinksfoldercategorie.h"

#include "../drink.h"

#include <Gui/MainWindow/Views/ListView/listview.h>

#include <QIcon>
#include <QMimeData>

using namespace Database;

DrinksFolderCategorie::DrinksFolderCategorie(int id, Categories *table) :
    FolderCategorie(id,table)
{
    IMPLEMENT_LISTATTRIBUTE(Drink*,DrinksFolderCategorie,drinks,tr("Drinks"))
}

QIcon DrinksFolderCategorie::icon() const
{
    return QIcon(":/graphics/icons/mac/sidebar/sidebar_folder_drinks");

}

QList<Drink*> DrinksFolderCategorie::calculate_drinks()
{
    QList<Drink*> drinks;
    foreach(int i, this->rows->value())
    {
        drinks.append(Drinks::instance()->castedRowById(i));
    }

    return drinks;
}

Models::TableModelBase* DrinksFolderCategorie::model()
{
    return Drinks::instance()->model();
}

Gui::MainWindow::Views::View *DrinksFolderCategorie::view()
{
    if(!m_view)
    {
        m_view = new Gui::MainWindow::Views::ListView(this);
        m_view->setWindowTitle(QString::fromUtf8("Drinks \u2013 ")+name->value());
        m_view->setWindowIcon(icon());
    }

    return m_view;
}


void DrinksFolderCategorie::dropMimeData(const QMimeData *data)
{
    if(!acceptMimeTypes(data->formats()))
    {
	return;
    }

    QByteArray encodedData = data->data("application/projectstats.drink");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);

    while (!stream.atEnd())
    {
	int id = -1;
	stream >> id;

        Drink *d = Drinks::instance()->castedRowById(id);
        if(d)
	{
	    insertRow(d);
	}
    }
}
