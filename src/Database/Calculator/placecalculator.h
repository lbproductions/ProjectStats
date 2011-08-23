#ifndef DATABASE_PLACECALCULATOR_H
#define DATABASE_PLACECALCULATOR_H

#include <QObject>
#include <QPointer>

namespace Database {

class Place;

class PlaceCalculator : public QObject
{
    Q_OBJECT
public:
    explicit PlaceCalculator(Place* place, QObject *parent = 0);

    int calculate_gameCount();

signals:

public slots:

private:
    QPointer<Place> m_place;

};

} // namespace Database

#endif // DATABASE_PLACECALCULATOR_H
