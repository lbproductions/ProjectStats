#ifndef DATABASE_DRINKCALCULATOR_H
#define DATABASE_DRINKCALCULATOR_H

#include <QObject>
#include <QPointer>


namespace Database {

class Drink;

class DrinkCalculator : public QObject
{
    Q_OBJECT
public:
    explicit DrinkCalculator(Drink* drink, QObject *parent = 0);

    int calculate_drinkCount();

signals:

public slots:

private:
    QPointer<Drink> m_drink;

};

} // namespace Database

#endif // DATABASE_DRINKCALCULATOR_H
