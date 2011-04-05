#ifndef SINGLETON_H
#define SINGLETON_H

#include <QPointer>

#include <Database/database.h>

template <class Derived>
class Singleton
{
public:
    static Derived* instance();

protected:
     Singleton();

private:
    Singleton( const Singleton& );
    static Derived *m_instance;

    class Guard
    {
    public:
        ~Guard();
    };
};

template <class Derived>
Derived* Singleton<Derived>::m_instance = 0;

template <class Derived>
Singleton<Derived>::Singleton()
{
}

template <class Derived>
Derived* Singleton<Derived>::instance()
{
    static Guard g;
    if(m_instance == 0)
    {
        m_instance = new Derived();
    }
    return m_instance;
}

template <class Derived>
Singleton<Derived>::Guard::~Guard()
{
    Singleton<Derived>::m_instance->deleteLater();
}


#endif // SINGLETON_H
