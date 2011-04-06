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

template<class T>
class Attribute : public AttributeInterface
{
public:
    typedef T (Row::*CalculateFunction)();
    typedef void (Row::*UpdateFunction)(AttributeInterface *changedDependency);

    Attribute(const QString &name, Row *row);

    QString name() const;

    T value();

    void setValue(T value);

    QFuture<T> valueASync();

    void setCalculationFunction(CalculateFunction calculateFuntion);

    void setUpdateFunction(CalculateFunction updateFunction);

    void update();

    void clearCache();

private:
    T calculate();

    bool m_cacheInitialized;
    T m_value;
    QString m_name;
    QList<QPointer<Attribute> > m_dependendAttributes;
    CalculateFunction m_calculateFunction;
    UpdateFunction m_updateFunction;
    QSemaphore m_semaphore;
};

template<class T>
Attribute<T>::Attribute(const QString &name, Row *row) :
    AttributeInterface(row),
    m_cacheInitialized(false),
    m_name(name),
    m_dependendAttributes(QList<QPointer<Attribute> >()),
    m_calculateFunction(0),
    m_updateFunction(0)
{

}

template<class T>
QString Attribute<T>::name() const
{
    return m_name;
}

template<class T>
T Attribute<T>::value()
{
    if(!m_cacheInitialized)
    {
        m_value = calculate();
        m_cacheInitialized = true;
    }

    return m_value;
}

template<class T>
void Attribute<T>::setValue(T value)
{
    m_value = value;
    m_cacheInitialized = true;
}

template<class T>
QFuture<T> Attribute<T>::valueASync()
{
    /// \todo Attribute<T>::valueASync() Implementieren
    qWarning() << "Attribute<T>::valueASync() has not been implemented yet!";
    return QFuture<T>();
}

template<class T>
void Attribute<T>::setCalculationFunction(CalculateFunction calculateFuntion)
{
    m_calculateFunction = calculateFuntion;
}

template<class T>
void Attribute<T>::setUpdateFunction(CalculateFunction updateFunction)
{
    m_updateFunction = updateFunction;
}

template<class T>
T Attribute<T>::calculate()
{
    return CALL_MEMBER_FN(m_row,m_calculateFunction)();
}

template<class T>
void Attribute<T>::update()
{
    AttributeInterface *dependentAttribute = static_cast<AttributeInterface*>(sender());
    CALL_MEMBER_FN(m_row,m_updateFunction)(dependentAttribute);
}

template<class T>
void Attribute<T>::clearCache()
{
    m_cacheInitialized = false;
}

} // namespace Database

#endif // DATABASE_ATTRIBUTE_H
