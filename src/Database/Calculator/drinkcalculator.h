#ifndef DATABASE_DRINKCALCULATOR_H
#define DATABASE_DRINKCALCULATOR_H

#include <QObject>
#include <QPointer>
#include <QMap>


namespace Database {

class Drink;
class Player;

class DrinkCalculator : public QObject
{
    Q_OBJECT
public:
    explicit DrinkCalculator(Drink* drink, QObject *parent = 0);

    QMap<Player*,int> calculate_countPerPlayer();

    int calculate_drinkCount();

    QString calculate_mostDrinks();

signals:

public slots:

private:
    QPointer<Drink> m_drink;

};

} // namespace Database

#endif // DATABASE_DRINKCALCULATOR_H
