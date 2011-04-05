#include "drinks.h"

namespace Database {

REGISTER_TABLE(Drinks)

Drinks::Drinks() :
    Table<Drink>("drinks"),
    Singleton<Drinks>()
{
}

} // namespace Database
