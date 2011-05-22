#ifndef DATABASE_MAPPINGATTRIBUTE_H
#define DATABASE_MAPPINGATTRIBUTE_H

#include "attributehash.h"

#include <QDebug>
#include <QVariant>

namespace Database {

class Row;

template<class T, class R, class C>
class Attribute;


template<class K, class V, class R, class C>
class MappingAttribute : public Attribute<AttributeHash<K,V>,R,C>
{
public:
    /*!
      Erstellt ein Mappingattribut mit dem Namen \p name, das zur Row \p row gehört.
      */
    MappingAttribute(const QString &name, const QString &displayName, Row *row);

    /*!
      Darf nicht aufgerufen werden!
      */
    void setValue(V value);

    /*!
      Setzt für \p key den Wert \p value.
      */
    void setValue(K key, V value);


    /*!
    Gibt für \p key den richtigen Wert zurück.
    */
    const V value(K key);

    AttributeHash<K,V>& value();
};

template<class K, class V, class R, class C>
MappingAttribute<K,V,R,C>::MappingAttribute(const QString &name, const QString &displayName, Row *row):
    Attribute<AttributeHash<K,V> ,R,C>(name,displayName,row)
{
}

template<class K, class V, class R, class C>
void MappingAttribute<K,V,R,C>::setValue(V value){
    qWarning() << "MappingAttribute<T>::setValue(): You may not invoke this method on a MappingAttribute!";
}

template<class K, class V, class R, class C>
void MappingAttribute<K,V,R,C>::setValue(K key, V value){
    Attribute<AttributeHash<K,V>,R,C>::m_lock.lockForWrite();
    QVariant v1;
    v1.setValue(Attribute<AttributeHash<K,V>,R,C>::m_value.value(key));
    QVariant v2;
    v2.setValue(value);
    bool change = v1 != v2;
    Attribute<AttributeHash<K,V>*,R,C>::m_cacheInitialized = true;
    if(change)
    {
	Attribute<AttributeHash<K,V>,R,C>::m_value.insert(key,value);

	emit Attribute<AttributeHash<K,V>,R,C>::changed();
    }
    Attribute<AttributeHash<K,V>,R,C>::m_lock.unlock();
}

template<class K, class V, class R, class C>
const V MappingAttribute<K,V,R,C>::value(K key){
    return Attribute<AttributeHash<K,V>,R,C>::value().value(key);
}

template<class K, class V, class R, class C>
AttributeHash<K,V>& MappingAttribute<K,V,R,C>::value(){
    disconnect(&this->m_value);
     Attribute<AttributeHash<K,V>,R,C>::value();
     connect(&this->m_value,SIGNAL(changed()),this,SIGNAL(changed()));
     return Attribute<AttributeHash<K,V>,R,C>::m_value;
}

} // namespace Database

#define STRINGIZE(s) # s
#define XSTR(s) STRINGIZE(s)

#define DECLARE_MAPPINGATTRIBUTE(Key, Value, RowClassname, Name) \
    MappingAttribute<Key,Value,RowClassname, RowClassname> *Name; \
    AttributeHash<Key,Value> calculate_ ## Name();

#define DECLARE_MAPPINGATTRIBUTE_IN_CALC(Key, Value, RowClassname, CalcClassName, Name) \
    MappingAttribute<Key,Value,RowClassname, CalcClassName> *Name;

#define DECLARE_VIRTUAL_MAPPINGATTRIBUTE_IN_CALC(Key, Value, RowClassname, CalcClassName, Name) \
    MappingAttribute<Key,Value,RowClassname, RowClassname> *Name; \
    AttributeHash<Key,Value> call_calculate_ ## Name(){ \
        return m_calc->calculate_ ## Name(); \
    }

#define IMPLEMENT_VIRTUAL_MAPPINGATTRIBUTE_IN_CALC(Key, Value, RowClassname, CalcClassName, Name, DisplayName) \
    Name = new MappingAttribute<Key,Value,RowClassname, RowClassname>(XSTR(Name) "",DisplayName, this); \
    Name->setCalculationFunction(this, & RowClassname::call_calculate_ ## Name); \
    registerAttribute(Name);

#define IMPLEMENT_MAPPINGATTRIBUTE(Key, Value, RowClassname, Name, DisplayName) \
    Name = new MappingAttribute<Key,Value,RowClassname, RowClassname>(XSTR(Name) "",DisplayName, this); \
    Name->setCalculationFunction(this, & RowClassname::calculate_ ## Name); \
    registerAttribute(Name);

#define IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Key, Value, RowClassname, CalcClassName, CalcClassInstanceName, Name, DisplayName) \
    Name = new MappingAttribute<Key,Value,RowClassname, CalcClassName>(XSTR(Name) "",DisplayName, this); \
    Name->setCalculationFunction(CalcClassInstanceName, & CalcClassName::calculate_ ## Name); \
    registerAttribute(Name);

#endif // DATABASE_MAPPINGATTRIBUTE_H
