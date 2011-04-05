#ifndef DATABASE_DRINKS_H
#define DATABASE_DRINKS_H

#include "table.h"
#include <singleton.h>

#include "drink.h"

namespace Database {

class Drinks : public Table<Drink>, public Singleton<Drinks>
{
    Q_OBJECT
public:
    Drinks();
};

} // namespace Database

#endif // DATABASE_DRINKS_H
