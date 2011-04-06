#ifndef DATABASE_ATTRIBUTE_H
#define DATABASE_ATTRIBUTE_H

#include <QObject>

#include <QPointer>
#include <QFuture>
#include <QSemaphore>

#define CALL_MEMBER_FN(object,ptrToMember)  ((*object).*(ptrToMember))

namespace Database {

class Row;

class AttributeInterface : public QObject
{
    Q_OBJECT
public:
    explicit AttributeInterface(Row *row);

public slots:
    virtual void clearCache() = 0;
    virtual void update() = 0;

signals:
    void changed();

protected:
    QPointer<Row> m_row;
};

template<class T, class R>
class Attribute : public AttributeInterface
{
public:
    typedef T (R::*CalculateFunction)();
    typedef T (R::*UpdateFunction)(AttributeInterface *changedDependency);

    Attribute(const QString &name, Row *row);

    QString name() const;

    virtual T value();

    virtual void setValue(T value);

    QFuture<T> valueASync();

    virtual void setCalculationFunction(CalculateFunction calculateFuntion);

    void setUpdateFunction(CalculateFunction updateFunction);

    void update();

    void clearCache();

    T operator()();

protected:
    virtual T calculate();

    bool m_cacheInitialized;
    T m_value;
    QString m_name;
    QList<QPointer<Attribute> > m_dependendAttributes;
    CalculateFunction m_calculateFunction;
    UpdateFunction m_updateFunction;
    QSemaphore m_semaphore;
};

template<class T, class R>
Attribute<T,R>::Attribute(const QString &name, Row *row) :
    AttributeInterface(row),
    m_cacheInitialized(false),
    m_name(name),
    m_dependendAttributes(QList<QPointer<Attribute> >()),
    m_calculateFunction(0),
    m_updateFunction(0)
{

}

template<class T, class R>
QString Attribute<T,R>::name() const
{
    return m_name;
}

template<class T, class R>
T Attribute<T,R>::operator()()
{
    return value();
}

template<class T, class R>
T Attribute<T,R>::value()
{
    if(!m_cacheInitialized)
    {
        m_value = calculate();
        m_cacheInitialized = true;
    }

    return m_value;
}

template<class T, class R>
void Attribute<T,R>::setValue(T value)
{
    m_value = value;
    m_cacheInitialized = true;
}

template<class T, class R>
QFuture<T> Attribute<T,R>::valueASync()
{
    /// \todo Attribute<T>::valueASync() Implementieren
    qWarning() << "Attribute<T>::valueASync() has not been implemented yet!";
    return QFuture<T>();
}

template<class T, class R>
void Attribute<T,R>::setCalculationFunction(CalculateFunction calculateFuntion)
{
    m_calculateFunction = calculateFuntion;
}

template<class T, class R>
void Attribute<T,R>::setUpdateFunction(CalculateFunction updateFunction)
{
    m_updateFunction = updateFunction;
}

template<class T, class R>
T Attribute<T,R>::calculate()
{
    return CALL_MEMBER_FN(static_cast<R*>(m_row.data()),m_calculateFunction)();
}

template<class T, class R>
void Attribute<T,R>::update()
{
    AttributeInterface *dependentAttribute = static_cast<AttributeInterface*>(sender());
    setValue(CALL_MEMBER_FN(static_cast<R*>(m_row.data()),m_updateFunction)(dependentAttribute));
}

template<class T, class R>
void Attribute<T,R>::clearCache()
{
    m_cacheInitialized = false;
}

} // namespace Database

#endif // DATABASE_ATTRIBUTE_H
