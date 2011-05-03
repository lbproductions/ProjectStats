#ifndef ATTRIBUTEHASH_H
#define ATTRIBUTEHASH_H

#include <QHash>
#include <QObject>

namespace Database{

class AttributeHashBase : public QObject
{
    Q_OBJECT
public:
    explicit AttributeHashBase();

signals:

    void changed();
};

template<class Key, class V>
class AttributeHash : public QHash<Key,V>, public AttributeHashBase
{
public:
    explicit AttributeHash();

    typename QHash<Key, V>::iterator insert ( const Key & key, const V & value );

    QString toString();

};


AttributeHashBase::AttributeHashBase()
{
}

template<class Key, class V>
AttributeHash<Key,V>::AttributeHash() :
    QHash<Key,V>()
{
}

template<class Key, class V>
typename QHash<Key, V>::iterator AttributeHash<Key,V>::insert ( const Key & key, const V & value ){
    QHash<Key,V>::insert(key,value);
    emit AttributeHash<Key,V>::changed();
}

template<class Key, class V>
QString AttributeHash<Key,V>::toString(){
    QString string = "";
    foreach(Key k, this->keys()){
        string += k + ":" + this->value(k) + ", ";
    }
    return string;
}

}

#endif // ATTRIBUTEHASH_H
