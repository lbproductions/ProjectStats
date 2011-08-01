#ifndef DATABASE_LISTATTRIBUTE_H
#define DATABASE_LISTATTRIBUTE_H

#include "attribute.h"
#include "row.h"

#include <QLabel>

namespace Database {

template<class V, class R, class C>
class ListAttribute : public Attribute<QList<V>,R,C>
{
public:
    ListAttribute(const QString &name, const QString &displayName, AttributeOwner *owner);

    /*!
    Gibt für den Wert an der Stelle pos zurück.
    */
    const V value(int pos);

    const QList<V> value();
};

template<class V, class R, class C>
ListAttribute<V,R,C>::ListAttribute(const QString &name, const QString &displayName, AttributeOwner *owner):
    Attribute<QList<V>,R,C>(name,displayName,owner)
{
}

template<class V, class R, class C>
const V ListAttribute<V,R,C>::value(int pos){
    return value().at(pos);
}

template<class V, class R, class C>
const QList<V> ListAttribute<V,R,C>::value(){
     return Attribute<QList<V>,R,C>::value();
}

} // namespace Database

#define STRINGIZE(s) # s
#define XSTR(s) STRINGIZE(s)

#define DECLARE_LISTATTRIBUTE(Value, RowClassname, Name) \
    ListAttribute<Value,RowClassname, RowClassname> *Name; \
    QList<Value> calculate_ ## Name();

#define DECLARE_LISTATTRIBUTE_IN_CALC(Value, RowClassname, CalcClassName, Name) \
    ListAttribute<Value,RowClassname, CalcClassName> *Name;

#define DECLARE_VIRTUAL_LISTATTRIBUTE_IN_CALC(Value, RowClassname, CalcClassName, Name) \
ListAttribute<Value,RowClassname, RowClassname> *Name; \
QList<Value> call_calculate_ ## Name(){ \
    return m_calc->calculate_ ## Name(); \
}

#define IMPLEMENT_VIRTUAL_LISTATTRIBUTE_IN_CALC(Value, RowClassname, CalcClassName, Name, DisplayName) \
    Name = new ListAttribute<Value,RowClassname, RowClassname>(XSTR(Name) "",DisplayName, this); \
    Name->setCalculationFunction(this, & RowClassname::call_calculate_ ## Name); \
    registerAttribute(Name);

#define IMPLEMENT_LISTATTRIBUTE(Value, RowClassname, Name, DisplayName) \
    Name = new ListAttribute<Value,RowClassname, RowClassname>(XSTR(Name) "",DisplayName, this); \
    Name->setCalculationFunction(this, & RowClassname::calculate_ ## Name); \
    registerAttribute(Name);

#define IMPLEMENT_LISTATTRIBUTE_IN_CALC(Value, RowClassname, CalcClassName, CalcClassInstanceName, Name, DisplayName) \
    Name = new ListAttribute<Value,RowClassname, CalcClassName>(XSTR(Name) "",DisplayName, this); \
    Name->setCalculationFunction(CalcClassInstanceName, & CalcClassName::calculate_ ## Name); \
    registerAttribute(Name);

#endif // DATABASE_LISTATTRIBUTE_H
