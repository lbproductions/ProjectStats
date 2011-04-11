#ifndef SINGLETON_H
#define SINGLETON_H

#include <QPointer>
#include <QMutex>
#include <QDebug>

#define DECLARE_SINGLETON( Classname ) \
public:\
    static Classname* instance();\
private:\
    static QPointer<Classname> m_instance;\
    static QMutex *lock();\
    class Classname ## Guard\
    {\
    public:\
        ~Classname ## Guard();\
    };

#define IMPLEMENT_SINGLETON( Classname )\
QPointer<Classname> Classname::m_instance(0);\
QMutex *Classname::lock()\
{\
    static QMutex *mutex = new QMutex(QMutex::Recursive);\
    return mutex;\
}\
Classname* Classname::instance()\
{\
    lock()->lock();\
    static Classname ## Guard g;\
    if(m_instance.isNull())\
    {\
        m_instance = new Classname();\
    }\
    lock()->unlock();\
    return m_instance;\
}\
Classname::Classname ## Guard::~Classname ## Guard() \
{\
    qDebug() << "Deleting" << Classname::m_instance;\
    Classname::m_instance->deleteLater();\
}
#endif // SINGLETON_H
