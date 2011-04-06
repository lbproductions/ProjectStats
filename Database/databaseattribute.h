#ifndef DATABASE_DATABASEATTRIBUTE_H
#define DATABASE_DATABASEATTRIBUTE_H

#include "attribute.h"

#include "row.h"

#include <QVariant>

namespace Database {

template<class T>
class DatabaseAttribute : public Attribute<T>
{
public:
    typedef T (Row::*CalculateFunction)();

    DatabaseAttribute(const QString &name, Row *row);

    void setValue(T value);

    void setCalculationFunction(CalculateFunction calculateFuntion);

protected:
    T calculate();
};

template<class T>
DatabaseAttribute<T>::DatabaseAttribute(const QString &name, Row *row) :
    Attribute<T>(name,row)
{
}

template<class T>
void DatabaseAttribute<T>::setValue(T value)
{
    Attribute<T>::setValue(value);
    Attribute<T>::m_row->set(Attribute<T>::m_name,value);
}

template<class T>
void DatabaseAttribute<T>::setCalculationFunction(CalculateFunction /*calculateFuntion*/)
{
    qWarning() << "DatabaseAttribute<T>::setCalculationFunction: You may not invoke this method on a DatabaseAttribute!";
}

template<class T>
T DatabaseAttribute<T>::calculate()
{
    return QVariant(Attribute<T>::m_row->get(Attribute<T>::m_name)).value<T>();
}

} // namespace Database

#endif // DATABASE_DATABASEATTRIBUTE_H
