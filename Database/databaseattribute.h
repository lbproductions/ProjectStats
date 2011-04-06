#ifndef DATABASE_DATABASEATTRIBUTE_H
#define DATABASE_DATABASEATTRIBUTE_H

#include "attribute.h"

#include "row.h"

#include <QVariant>
#include <QtConcurrentRun>

namespace Database {

template<class T, class R>
class DatabaseAttribute : public Attribute<T,R>
{
public:
    typedef T (Row::*CalculateFunction)();

    DatabaseAttribute(const QString &name, Row *row);

    void setValue(T value);

    void setCalculationFunction(CalculateFunction calculateFuntion);

    bool isDatabaseAttribute() const;

protected:
    T calculate();
};

template<class T, class R>
DatabaseAttribute<T,R>::DatabaseAttribute(const QString &name, Row *row) :
    Attribute<T,R>(name,row)
{
}

template<class T, class R>
void DatabaseAttribute<T,R>::setValue(T value)
{
    Attribute<T,R>::setValue(value);
    QtConcurrent::run(Attribute<T,R>::m_row.data(), &Row::set, Attribute<T,R>::m_name, value);
}

template<class T, class R>
void DatabaseAttribute<T,R>::setCalculationFunction(CalculateFunction /*calculateFuntion*/)
{
    qWarning() << "DatabaseAttribute<T>::setCalculationFunction: You may not invoke this method on a DatabaseAttribute!";
}

template<class T, class R>
T DatabaseAttribute<T,R>::calculate()
{
    return QVariant(Attribute<T,R>::m_row->get(Attribute<T,R>::m_name)).value<T>();
}

template<class T, class R>
bool DatabaseAttribute<T,R>::isDatabaseAttribute() const
{
    return true;
}

} // namespace Database

#endif // DATABASE_DATABASEATTRIBUTE_H
