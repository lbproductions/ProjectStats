#include "placescombobox.h"

#include "handler.h"

#include "Database/database.h"
#include <Database/place.h>
#include <Gui/Misc/newrowwidget.h>

#include <QListIterator>

using namespace Gui::Misc;

PlacesComboBox::PlacesComboBox(Database::Places *placesTable, QWidget *parent) :
    QComboBox(parent),
    m_places(placesTable)
{

    placeIndexBefore = -1;

    connect(m_places,SIGNAL(rowChanged(Row*)),this,SLOT(updateView()));
    connect(this,SIGNAL(currentIndexChanged(int)),this,SLOT(on_currentIndexChanged()));

    updateView();
}

void PlacesComboBox::updateView()
{
    this->clear();
    m_placePositions.clear();

    Q_ASSERT(!m_places.isNull());

    addItems(m_places->allRows());

    insertSeparator(count());

    addItem(tr("Create new place..."));
}

void PlacesComboBox::on_currentIndexChanged()
{
    int index = currentIndex();

    if(index == count()-1 && currentText() == tr("Create new place..."))
    {
        NewRowWidget* createplace = new NewRowWidget(new Database::Place());
	//connect(npw,SIGNAL(placeCreated(Database::Place*)),this,SLOT(on_placeCreated(Database::Place*)));
	//connect(npw,SIGNAL(rejected()),this,SLOT(on_placeCreationCanceled()));
	createplace->show();
	return;
    }
    if (placeIndexBefore != -1){
        emit currentIndexChanged(m_places->rowById(m_placePositions.at(placeIndexBefore)),currentPlace());
    }
    else{
	emit currentIndexChanged(0,currentPlace());
    }

    placeIndexBefore = currentIndex();
}

void PlacesComboBox::on_placeCreated(Database::Place* place)
{
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
    QListIterator<Database::Place*> it(places);
    while(it.hasNext()) {
	QPointer<Database::Place> p = it.next();

	Q_ASSERT(p != 0);

	m_placePositions.insert(m_placePositions.size(),p->id());
        QComboBox::addItem(p->displayString->value());
    }
}

void PlacesComboBox::setCurrentPlace(int placeId)
{
    int index = m_placePositions.indexOf(placeId);

    setCurrentIndex(index);
}

Database::Place *PlacesComboBox::currentPlace() const
{
    Q_ASSERT(!m_places.isNull());

    int index = currentIndex();

    if(index < 0 || index >= count() - 1)
    {
	return 0;
    }

    int placeId = m_placePositions.at(index);

    return m_places->rowById(placeId);
}
