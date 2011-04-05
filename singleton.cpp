#include "singleton.h"

template <class Derived>
Singleton<Derived>::Singleton()
{
}

template <class Derived>
Singleton<Derived>::Guard::~Guard()
{
    Singleton<Derived>::m_instance->deleteLater();
}
