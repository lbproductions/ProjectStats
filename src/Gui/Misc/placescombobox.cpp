#include "placescombobox.h"

#include <Misc/handler.h>

#include <LBDatabase/LBDatabase.h>
#include <Database/place.h>
#include <Gui/Misc/newrowwidget.h>

#include <QListIterator>

using namespace Gui::Misc;

PlacesComboBox::PlacesComboBox(QWidget *parent) :
    QComboBox(parent),
    placeIndexBefore(-1)
{
    connect(this,SIGNAL(currentIndexChanged(int)),this,SLOT(on_currentIndexChanged()));
    connect(Database::Places::instance(),SIGNAL(rowInserted(::Database::PSRow*)),this,SLOT(on_placeCreated(::Database::PSRow*)));

    updateView();
}

void PlacesComboBox::updateView()
{
    this->clear();
    m_placePositions.clear();

    addItems(Database::Places::instance()->allRows());

    insertSeparator(count());

    addItem(tr("Create new place..."));
}

void PlacesComboBox::on_currentIndexChanged()
{
    int index = currentIndex();

    if(index == count()-1 && currentText() == tr("Create new place..."))
    {
        NewRowWidget* createplace = new NewRowWidget(new Database::Place());
        createplace->setModal(true);
	//connect(npw,SIGNAL(placeCreated(Database::Place*)),this,SLOT(on_placeCreated(Database::Place*)));
	//connect(npw,SIGNAL(rejected()),this,SLOT(on_placeCreationCanceled()));
	createplace->show();
	return;
    }
    if (placeIndexBefore != -1 && placeIndexBefore < m_placePositions.count())
    {
        emit currentIndexChanged(Database::Places::instance()->castedRowById(m_placePositions.at(placeIndexBefore)),currentPlace());
    }
    else
    {
	emit currentIndexChanged(0,currentPlace());
    }

    placeIndexBefore = currentIndex();
}

void PlacesComboBox::on_placeCreated(::Database::PSRow* row)
{
    Database::Place* place = static_cast<Database::Place*>(row);
    updateView();

    if(place != 0)
    {
	setCurrentPlace(place->id());
    }
}

void PlacesComboBox::on_placeCreationCanceled()
{
    emit(currentIndexChanged(0));
}

void PlacesComboBox::addItems(const QList<Database::Place*> &places)
{
    foreach(Database::Place *place, places)
    {
        m_placePositions.insert(m_placePositions.size(),place->id());
        addItem(place->displayString->value());
    }
}

void PlacesComboBox::setCurrentPlace(int placeId)
{
    int index = m_placePositions.indexOf(placeId);

    setCurrentIndex(index);
}

Database::Place *PlacesComboBox::currentPlace() const
{
    int index = currentIndex();

    if(index < 0 || index >= m_placePositions.count())
    {
	return 0;
    }

    int placeId = m_placePositions.at(index);

    return Database::Places::instance()->castedRowById(placeId);
}
