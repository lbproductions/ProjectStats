#ifndef ATTRIBUTELIST_H
#define ATTRIBUTELIST_H

#include <QList>
#include <QObject>

namespace Database{

class AttributeListBase : public QObject
{
    Q_OBJECT
protected:
    explicit AttributeListBase(QObject *parent = 0);
    AttributeListBase(const AttributeListBase& other);

    AttributeListBase& operator=(const AttributeListBase& other);

signals:

    void changed();
};

template<class V>
class AttributeList : public AttributeListBase, public QList<V>
{
public:
    explicit AttributeList(QObject *parent = 0);

    void append(const V &value);

    void insert ( int i, const V & value );

    V takeLast();
};

template<class V>
AttributeList<V>::AttributeList(QObject *parent):
    AttributeListBase(parent),
    QList<V>()
{

}

template<class V>
void AttributeList<V>::append(const V &value){
    QList<V>::append(value);
    emit changed();
}

template<class V>
void AttributeList<V>::insert ( int i, const V & value ){
    QList<V>::insert(i,value);
    emit changed();
}

template<class V>
V AttributeList<V>::takeLast()
{
    V v = QList<V>::takeLast();
    emit changed();
    return v;
}

}

#endif // ATTRIBUTELIST_H
