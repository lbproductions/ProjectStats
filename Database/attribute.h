#ifndef DATABASE_ATTRIBUTE_H
#define DATABASE_ATTRIBUTE_H

#include <QObject>

#include <QPointer>
#include <QFuture>
#include <QReadWriteLock>
#include <QtConcurrentRun>
#include <QVariant>
#include <QFutureWatcher>

#define CALL_MEMBER_FN(object,ptrToMember)  ((*object).*(ptrToMember))

class QLabel;
class QLineEdit;

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

    virtual QString name() const = 0;

signals:
    void changed();
    void aboutToChange();

protected:
    QPointer<Row> m_row;
};

template<class T, class R>
class AttributeFutureWatcher;

template<class T, class R>
class Attribute : public AttributeInterface
{
public:
    typedef T (R::*CalculateFunction)();
    typedef bool (R::*UpdateFunction)(AttributeInterface *changedDependency);

    Attribute(const QString &name, Row *row);

    QString name() const;

    virtual T value();

    virtual void setValue(T value);

    AttributeFutureWatcher<T,R> *futureWatcher();

    virtual void setCalculationFunction(CalculateFunction calculateFuntion);

    void setUpdateFunction(UpdateFunction updateFunction);

    void update();

    void clearCache();

    T operator()();

    void addDependingAttribute(AttributeInterface *dependingAttribute);

protected:
    friend class AttributeFutureWatcher<T,R>;
    virtual T calculate();

    bool m_cacheInitialized;
    T m_value;
    QString m_name;
    CalculateFunction m_calculateFunction;
    UpdateFunction m_updateFunction;
    QReadWriteLock m_lock;
    AttributeFutureWatcher<T,R> *m_futureWatcher;
};

class AttributeFutureWatcherInterface : public QObject
{
    Q_OBJECT
public:
    explicit AttributeFutureWatcherInterface(AttributeInterface* parent);

    void connectTo(QLabel *label);
    void connectTo(QLineEdit *lineEdit);

signals:
    void valueChanged(QString);

private slots:
    virtual void update() = 0;
    virtual void on_attributeAboutToChange() = 0;

private:
    virtual bool isRunning() = 0;
    virtual QString value() = 0;

};

template<class T, class R>
class AttributeFutureWatcher : public AttributeFutureWatcherInterface
{
public:
    explicit AttributeFutureWatcher(Attribute<T,R> *attribute);

    void setFuture(QFuture<T> future);

private:
    friend class Attribute<T,R>;
    void update();
    void on_attributeAboutToChange();
    bool isRunning();
    QString value();

    QPointer<Attribute<T,R> > m_attribute;
    QPointer<QFutureWatcher<T> > m_futureWatcher;
};

template<class T, class R>
Attribute<T,R>::Attribute(const QString &name, Row *row) :
    AttributeInterface(row),
    m_cacheInitialized(false),
    m_name(name),
    m_calculateFunction(0),
    m_updateFunction(0),
    m_lock(QReadWriteLock::Recursive),
    m_futureWatcher(new AttributeFutureWatcher<T,R>(this))
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
    m_lock.lockForWrite();
    if(!m_cacheInitialized)
    {
        if(!m_futureWatcher->isRunning())
        {
            m_value = calculate();
        }
        else
        {
            m_futureWatcher->m_futureWatcher->waitForFinished();
        }
        m_cacheInitialized = true;
    }

    m_lock.unlock();
    return m_value;
}

template<class T, class R>
void Attribute<T,R>::setValue(T value)
{
    m_lock.lockForWrite();
    bool change = m_value != value;
    m_cacheInitialized = true;
    if(change)
    {
        m_value = value;

        emit changed();
    }
    m_lock.unlock();
}

template<class T, class R>
AttributeFutureWatcher<T,R> *Attribute<T,R>::futureWatcher()
{
    m_lock.lockForWrite();

    if(!m_cacheInitialized && !m_futureWatcher->isRunning())
    {
        emit aboutToChange();
        QFuture<T> future = QtConcurrent::run(this, &Attribute<T,R>::calculate);
        m_futureWatcher->setFuture(future);
    }

    m_lock.unlock();

    return m_futureWatcher;
}

template<class T, class R>
void Attribute<T,R>::setCalculationFunction(CalculateFunction calculateFuntion)
{
    m_lock.lockForWrite();
    m_calculateFunction = calculateFuntion;
    m_lock.unlock();
}

template<class T, class R>
void Attribute<T,R>::setUpdateFunction(UpdateFunction updateFunction)
{
    m_lock.lockForWrite();
    m_updateFunction = updateFunction;
    m_lock.unlock();
}

template<class T, class R>
T Attribute<T,R>::calculate()
{
    if(m_calculateFunction == 0)
    {
        return T();
    }

    T newValue = CALL_MEMBER_FN(static_cast<R*>(m_row.data()),m_calculateFunction)();

    return newValue;
}

template<class T, class R>
void Attribute<T,R>::update()
{
    m_lock.lockForWrite();
    if(m_updateFunction == 0 || !m_cacheInitialized)
    {
        m_lock.unlock();
        clearCache();
        return;
    }

    AttributeInterface *dependentAttribute = static_cast<AttributeInterface*>(sender());
    m_cacheInitialized = CALL_MEMBER_FN(static_cast<R*>(m_row.data()),m_updateFunction)(dependentAttribute);

    futureWatcher(); // ungefaehr: if(!m_cacheInitialized) m_value = calculate();
    m_lock.unlock();
}

template<class T, class R>
void Attribute<T,R>::clearCache()
{
    m_lock.lockForWrite();
    m_cacheInitialized = false;
    futureWatcher(); // ungefaehr: if(!m_cacheInitialized) m_value = calculate();
    m_lock.unlock();
}

template<class T, class R>
void Attribute<T,R>::addDependingAttribute(AttributeInterface *dependingAttribute)
{
    connect(this,SIGNAL(changed()),dependingAttribute,SLOT(update()));
}

template<class T, class R>
AttributeFutureWatcher<T,R>::AttributeFutureWatcher(Attribute<T,R> *parent) :
    AttributeFutureWatcherInterface(parent),
    m_attribute(parent),
    m_futureWatcher(new QFutureWatcher<T>())
{
    connect(m_futureWatcher,SIGNAL(finished()),this,SLOT(update()));
    connect(m_attribute,SIGNAL(changed()),this,SLOT(update()));
    connect(m_attribute,SIGNAL(aboutToChange()),this,SLOT(on_attributeAboutToChange()));
}

template<class T, class R>
void AttributeFutureWatcher<T,R>::setFuture(QFuture<T> future)
{
    m_futureWatcher->setFuture(future);
}

template<class T, class R>
void AttributeFutureWatcher<T,R>::on_attributeAboutToChange()
{
    emit valueChanged("Loading...");
}

template<class T, class R>
void AttributeFutureWatcher<T,R>::update()
{
    if(sender() == m_futureWatcher)
    {
        T value = m_futureWatcher->future().result();
        m_attribute->setValue(value);
        emit valueChanged(QVariant(value).toString());
    }
    else
    {
        T value = m_attribute->value();
        emit valueChanged(QVariant(value).toString());
    }
}

template<class T, class R>
bool AttributeFutureWatcher<T,R>::isRunning()
{
    return m_futureWatcher->isRunning();
}

template<class T, class R>
QString AttributeFutureWatcher<T,R>::value()
{
    return m_attribute->value();
}

} // namespace Database

#endif // DATABASE_ATTRIBUTE_H
