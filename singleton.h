#ifndef SINGLETON_H
#define SINGLETON_H

#include <QPointer>
#include <QDebug>
#include <QMutex>

//! Mit Hilfe dieser template-Klasse lassen sich andere Klassen extrem leicht in Singletons verwandeln.
/*!
  Um eine Klasse zu einem Singleton zu machen, muss sie nur noch von Singleton<Klassenname> erben, und erhält damit einige typische Singleton Eigeschaften.<br>
  Zu erwähnen sei, dass der Konstruktor der erbenden Singletons public sein muss, also nicht sichergestellt sein kann, dass wirklich nur eine Instanz der Klasse existiert.<br>
  Außerdem erwähnenswert ist, dass diese Singleton-Klasse sich um die Zerstörung der Instanz bei Beenden des Programmes kümmert und die Singleton-Kindklassen somit kein QObject-parent haben sollten, der sich um die Zerstörung kümmern würde.
  */
template <class Derived>
class Singleton
{
public:
    /*!
      Gibt die Instanz des Singletons zurück.

      \return die Instanz des Singletons.
      */
    static Derived* instance();

protected:
    /*!
      Der versteckte Konstruktor. Die Konstruktoren der Kindklassen müssen public sein.
      */
    Singleton();

private:
    /*!
      Der private Copykonstruktor verhindert das Erstellen neuer Instanzen des Objektes durch den Zuweisungsoperator (a=b).
      */
    Singleton( const Singleton& );

    static QPointer<Derived> m_instance; //!< Die Instanz des Singletons.

    static QMutex m_lock;

    /*!
      Der Guard kümmert sich um die Zerstörung der Instanz beim Beenden des Programms.
      */
    class Guard
    {
    public:
        /*!
          Zerstört die Instanz des Singletons.
          */
        ~Guard();
    };
};

template <class Derived>
QPointer<Derived> Singleton<Derived>::m_instance(0);
template <class Derived>
QMutex Singleton<Derived>::m_lock;

template <class Derived>
Singleton<Derived>::Singleton()
{
}

template <class Derived>
Derived* Singleton<Derived>::instance()
{
    static Guard g;
    if(m_instance.isNull())
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
