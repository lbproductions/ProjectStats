#ifndef DATABASE_LIVEGAMECALCULATOR_H
#define DATABASE_LIVEGAMECALCULATOR_H

#include <QObject>
#include <QPointer>

#include <Database/attributelist.h>

namespace Database {

class LiveGame;
class Drink;
class Round;

class LiveGameCalculator : public QObject
{
    Q_OBJECT
public:
    explicit LiveGameCalculator(LiveGame* livegame, QObject *parent = 0);

    AttributeList<Drink*> calculate_drinks();

    AttributeList<Round*> calculate_rounds();

signals:

public slots:

private:
    QPointer<LiveGame> m_livegame;

};

} // namespace Database

#endif // DATABASE_LIVEGAMECALCULATOR_H
