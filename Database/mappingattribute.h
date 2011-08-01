#ifndef DATABASE_MAPPINGATTRIBUTE_H
#define DATABASE_MAPPINGATTRIBUTE_H

#include "attribute.h"
#include "handler.h"

#include <QDebug>
#include <QVariant>
#include <QLabel>

namespace Database {

class Row;

template<class T, class R, class C>
class Attribute;

template<class K, class V, class R, class C>
class MappingAttributeFutureWatcher : public AttributeFutureWatcher
{
public:
    MappingAttributeFutureWatcher(Attribute<QMap<K,V>,R,C>* parent);

    /*!
      Verbindet diesen FutureWatcher mit dem Label \p label.<br>
      Alle zukünftigen Änderungen werden dem Label mitgeteilt, sodass es sich automatisch anpassen kann.
      */
    void connectTo(QLabel *label, K key);

 protected:
    /*!
      Wird für das Update eines Values aus einer Map oder List benötigt, um das richtige Element und dessen verknüpfte Labels zu aktualisieren.
      */
    void updateKey(QVariant variant);

    QMap<QLabel*,K> m_labels; //!< Speichert alle Labels, die mit dem Attribut verbunden wurden, sowie dessen Key.
};

template<class K, class V, class R, class C>
class MappingAttribute : public Attribute<QMap<K,V>,R,C>
{
public:
    /*!
      Erstellt ein Mappingattribut mit dem Namen \p name, das zur Row \p row gehört.
      */
    MappingAttribute(const QString &name, const QString &displayName, AttributeOwner *row);

    /*!
    Gibt für \p key den richtigen Wert zurück.
    */
    const V value(K key);

    const QMap<K,V> value();

    MappingAttributeFutureWatcher<K,V,R,C> *mappingFutureWatcher();

protected:
    MappingAttributeFutureWatcher<K,V,R,C>* m_attributeFutureWatcher;
};

template<class K, class V, class R, class C>
MappingAttribute<K,V,R,C>::MappingAttribute(const QString &name, const QString &displayName, AttributeOwner *row):
    Attribute<QMap<K,V> ,R,C>(name,displayName,row),
    m_attributeFutureWatcher(0)
{
}

template<class K, class V, class R, class C>
const V MappingAttribute<K,V,R,C>::value(K key){
    return value().value(key);
}

template<class K, class V, class R, class C>
const QMap<K,V> MappingAttribute<K,V,R,C>::value()
{
     return Attribute<QMap<K,V>,R,C>::value();
}

template<class K, class V, class R, class C>
MappingAttributeFutureWatcher<K,V,R,C>::MappingAttributeFutureWatcher(Attribute<QMap<K,V>,R,C>* parent):
    AttributeFutureWatcher(parent)
{
}

template<class K, class V, class R, class C>
void MappingAttributeFutureWatcher<K,V,R,C>::connectTo(QLabel* label, K key)
{
    MappingAttribute<K,V,R,C>* pointer = static_cast<MappingAttribute<K,V,R,C>*>(AttributeFutureWatcher::m_attribute);

    if(pointer->isCalculating())
    {
        label->setText("Loading...");
    }
    else
    {
        AttributeVariant variant;
        variant.setValue(pointer->value(key));
        QVariant display = variant.displayVariant();
        if (!display.isNull()){
            label->setText(display.toString());
        }
        else{
            label->setText(QVariant::fromValue<V>(pointer->value(key)).toString());
        }
    }
    m_labels.insert(label,key);

    //connect(pointer->value(),SIGNAL(changed(QVariant)),this,SLOT(updateKey(QVariant)));
}

template<class K, class V, class R, class C>
void MappingAttributeFutureWatcher<K,V,R,C>::updateKey(QVariant variant){
    K key = variant.value<K>();
    MappingAttribute<K,V,R,C>* pointer = static_cast<MappingAttribute<K,V,R,C>*>(AttributeFutureWatcher::m_attribute);
    AttributeVariant var;
    var.setValue(pointer->value(key));
    QVariant display = var.displayVariant();
    foreach(QLabel* label, m_labels.keys()){
        if (!display.isNull()){
            label->setText(display.toString());
        }
        else{
            label->setText(QVariant::fromValue<V>(pointer->value(key)).toString());
        }
    }
}

template<class K, class V, class R, class C>
MappingAttributeFutureWatcher<K,V,R,C> *MappingAttribute<K,V,R,C>::mappingFutureWatcher()
{
    if(m_attributeFutureWatcher == 0)
    {
        m_attributeFutureWatcher = new MappingAttributeFutureWatcher<K,V,R,C>(this);
        //m_attributeFutureWatcher->moveToThread(this->thread());
        //m_attributeFutureWatcher->setParent(this);
    }
    return m_attributeFutureWatcher;
}

} // namespace Database

#define STRINGIZE(s) # s
#define XSTR(s) STRINGIZE(s)

#define DECLARE_MAPPINGATTRIBUTE(Key, Value, RowClassname, Name) \
    MappingAttribute<Key,Value,RowClassname, RowClassname> *Name; \
    QMap<Key,Value> calculate_ ## Name();

#define DECLARE_MAPPINGATTRIBUTE_IN_CALC(Key, Value, RowClassname, CalcClassName, Name) \
    MappingAttribute<Key,Value,RowClassname, CalcClassName> *Name;

#define DECLARE_VIRTUAL_MAPPINGATTRIBUTE_IN_CALC(Key, Value, RowClassname, CalcClassName, Name) \
    MappingAttribute<Key,Value,RowClassname, RowClassname> *Name; \
    QMap<Key,Value> call_calculate_ ## Name(){ \
        return m_calc->calculate_ ## Name(); \
    }

#define IMPLEMENT_VIRTUAL_MAPPINGATTRIBUTE_IN_CALC(Key, Value, RowClassname, CalcClassName, Name, DisplayName) \
    Name = new MappingAttribute<Key,Value,RowClassname, RowClassname>(XSTR(Name) "",DisplayName, this); \
    Name->setCalculationFunction(this, & RowClassname::call_calculate_ ## Name); \
    registerAttribute(Name);

#define IMPLEMENT_MAPPINGATTRIBUTE(Key, Value, RowClassname, Name, DisplayName) \
    Name = new MappingAttribute<Key ,Value,RowClassname, RowClassname>(XSTR(Name) "",DisplayName, this); \
    Name->setCalculationFunction(this, & RowClassname::calculate_ ## Name); \
    registerAttribute(Name);

#define IMPLEMENT_MAPPINGATTRIBUTE_IN_CALC(Key, Value, RowClassname, CalcClassName, CalcClassInstanceName, Name, DisplayName) \
    Name = new MappingAttribute<Key ,Value,RowClassname, CalcClassName>(XSTR(Name) "",DisplayName, this); \
    Name->setCalculationFunction(CalcClassInstanceName, & CalcClassName::calculate_ ## Name); \
    registerAttribute(Name);

#endif // DATABASE_MAPPINGATTRIBUTE_H
