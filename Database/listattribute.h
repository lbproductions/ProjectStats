#ifndef DATABASE_LISTATTRIBUTE_H
#define DATABASE_LISTATTRIBUTE_H

#include "attribute.h"
#include "attributelist.h"
#include "row.h"

namespace Database {

template<class V, class R, class C>
class ListAttribute : public Attribute<AttributeList<V>,R,C>
{
public:
    ListAttribute(const QString &name, const QString &displayName, Row *row);

    /*!
      Darf nicht aufgerufen werden!
      */
    void setValue(V value);

    /*!
    Gibt für den Wert an der Stelle pos zurück.
    */
    const V value(int pos);

    AttributeList<V>& value();
};

template<class V, class R, class C>
ListAttribute<V,R,C>::ListAttribute(const QString &name, const QString &displayName, Row *row):
    Attribute<AttributeList<V>,R,C>(name,displayName,row)
{
}

template<class V, class R, class C>
void ListAttribute<V,R,C>::setValue(V value){
    qWarning() << "MappingAttribute<T>::setValue(): You may not invoke this method on a MappingAttribute!";
}

template<class V, class R, class C>
const V ListAttribute<V,R,C>::value(int pos){
    return Attribute<AttributeList<V>,R,C>::m_value.at(pos);
}


template<class V, class R, class C>
AttributeList<V>& ListAttribute<V,R,C>::value(){
    disconnect(&this->m_value);
     Attribute<AttributeList<V>,R,C>::value();
     connect(&this->m_value,SIGNAL(changed()),this,SIGNAL(changed()));
     return Attribute<AttributeList<V>,R,C>::m_value;
}



} // namespace Database

#define STRINGIZE(s) # s
#define XSTR(s) STRINGIZE(s)

#define DECLARE_LISTATTRIBUTE(Value, RowClassname, Name) \
    ListAttribute<Value,RowClassname, RowClassname> *Name; \
    AttributeList<Value> calculate_ ## Name();

#define DECLARE_LISTATTRIBUTE_IN_CALC(Value, RowClassname, CalcClassName, Name) \
    ListAttribute<Value,RowClassname, CalcClassName> *Name;

#define IMPLEMENT_LISTATTRIBUTE(Value, RowClassname, Name, DisplayName) \
    Name = new ListAttribute<Value,RowClassname, RowClassname>(XSTR(Name) "",DisplayName, this); \
    Name->setCalculationFunction(this, & RowClassname::calculate_ ## Name); \
    registerAttribute(Name);

#define IMPLEMENT_LISTATTRIBUTE_IN_CALC(Value, RowClassname, CalcClassName, CalcClassInstanceName, Name, DisplayName) \
    Name = new ListAttribute<Value,RowClassname, CalcClassName>(XSTR(Name) "",DisplayName, this); \
    Name->setCalculationFunction(CalcClassInstanceName, & CalcClassName::calculate_ ## Name); \
    registerAttribute(Name);

#endif // DATABASE_LISTATTRIBUTE_H
