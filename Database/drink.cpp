#include "drink.h"

#include "drinks.h"

namespace Database {

Drink::Drink(int id, Table<Drink> *table) :
    Row(id,table)
{
}

} // namespace Database
