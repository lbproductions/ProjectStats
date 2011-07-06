#ifndef DATABASE_LISTATTRIBUTE_H
#define DATABASE_LISTATTRIBUTE_H

#include "attribute.h"
#include "attributelist.h"
#include "row.h"

#include <QLabel>

namespace Database {

template<class V, class R, class C>
class AttributeFutureWatcher;

template<class V, class R, class C>
class ListAttributeFutureWatcher : public AttributeFutureWatcher<AttributeList<V>,R,C>
{
public:

    ListAttributeFutureWatcher(Attribute<AttributeList<V>,R,C>* parent);

    /*!
      Verbindet diesen FutureWatcher mit dem Label \p label.<br>
      Alle zukünftigen Änderungen werden dem Label mitgeteilt, sodass es sich automatisch anpassen kann.
      */
    void connectTo(QLabel *label, V value);

 protected:
    /*!
      Wird für das Update eines Values aus einer Map oder List benötigt, um das richtige Element und dessen verknüpfte Labels zu aktualisieren.
      */
    void updateKey(QVariant variant);

    QMap<QLabel*,V> m_labels; //!< Speichert alle Labels, die mit dem Attribut verbunden wurden, sowie dessen Value.


};

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

    ListAttributeFutureWatcher<V,R,C> *listFutureWatcher();

protected:
    ListAttributeFutureWatcher<V,R,C>* m_attributeFutureWatcher;
};

template<class V, class R, class C>
ListAttribute<V,R,C>::ListAttribute(const QString &name, const QString &displayName, Row *row):
    Attribute<AttributeList<V>,R,C>(name,displayName,row)
{
}

template<class V, class R, class C>
void ListAttribute<V,R,C>::setValue(V value){
    qWarning() << "ListAttribute<T>::setValue(): You may not invoke this method on a ListAttribute!";
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

template<class V, class R, class C>
ListAttributeFutureWatcher<V,R,C>::ListAttributeFutureWatcher(Attribute<AttributeList<V>,R,C>* parent):
    AttributeFutureWatcher<AttributeList<V>,R,C>(parent)
{
}

template<class V, class R, class C>
void ListAttributeFutureWatcher<V,R,C>::connectTo(QLabel* label, V value)
{
    if(AttributeFutureWatcher<AttributeList<V>,R,C>::isRunning())
    {
        label->setText("Loading...");
    }
    else
    {
        QVariant display = Handler::getInstance()->convert(QVariant::fromValue<V>(value));
        if (!display.isNull()){
            label->setText(display.toString());
        }
        else{
            label->setText(QVariant::fromValue<V>(value).toString());
        }
    }
    m_labels.insert(label,value);

    //connect(pointer->value(),SIGNAL(changed(QVariant)),this,SLOT(updateKey(QVariant)));
}

template<class V, class R, class C>
void ListAttributeFutureWatcher<V,R,C>::updateKey(QVariant variant){
    V value = variant.value<V>();
    QPointer<ListAttribute<V,R,C> > pointer = (ListAttribute<V,R,C>*) AttributeFutureWatcher<AttributeList<V>,R,C>::m_attribute.data();
    QVariant display = Handler::getInstance()->convert(QVariant::fromValue<V>(value));
    foreach(QLabel* label, m_labels.keys()){
        if (!display.isNull()){
            label->setText(display.toString());
        }
        else{
            label->setText(QVariant::fromValue<V>(value).toString());
        }
    }
}

template<class V, class R, class C>
ListAttributeFutureWatcher<V,R,C> *ListAttribute<V,R,C>::listFutureWatcher()
{
    if(m_attributeFutureWatcher == 0)
    {
        m_attributeFutureWatcher = new ListAttributeFutureWatcher<V,R,C>(this);
        //m_attributeFutureWatcher->moveToThread(this->thread());
        //m_attributeFutureWatcher->setParent(this);
    }
    return m_attributeFutureWatcher;
}


} // namespace Database

#define STRINGIZE(s) # s
#define XSTR(s) STRINGIZE(s)

#define DECLARE_LISTATTRIBUTE(Value, RowClassname, Name) \
    ListAttribute<Value,RowClassname, RowClassname> *Name; \
    AttributeList<Value> calculate_ ## Name();

#define DECLARE_LISTATTRIBUTE_IN_CALC(Value, RowClassname, CalcClassName, Name) \
    ListAttribute<Value,RowClassname, CalcClassName> *Name;

#define DECLARE_VIRTUAL_LISTATTRIBUTE_IN_CALC(Value, RowClassname, CalcClassName, Name) \
ListAttribute<Value,RowClassname, RowClassname> *Name; \
AttributeList<Value> call_calculate_ ## Name(){ \
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
