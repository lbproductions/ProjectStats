#ifndef PLACESCOMBOBOX_H
#define PLACESCOMBOBOX_H

#include <QComboBox>
#include <QPointer>

namespace Database
{
    class Places;
    class Place;
    class Row;
}

namespace Gui
{

namespace Misc
{

class PlacesComboBox : public QComboBox
{
    Q_OBJECT

public:
    PlacesComboBox(QWidget *parent = 0);

    void addItems(const QList<Database::Place*> &places);

    Database::Place *currentPlace() const;

public slots:
    void setCurrentPlace(int placeId);

signals:
    void currentIndexChanged(Database::Place *const);
    void currentIndexChanged(Database::Place *const, Database::Place* const);
    void focusLost();

private slots:
    void updateView();
    void on_currentIndexChanged();
    void on_placeCreated(::Database::Row*);
    void on_placeCreationCanceled();

private:
    QVector<int> m_placePositions;

    int placeIndexBefore;
};

}
}

#endif // PLACESCOMBOBOX_H
