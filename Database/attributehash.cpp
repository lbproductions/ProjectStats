#include "attributehash.h"

using namespace Database;

template<class Key, class V>
AttributeHash<Key,V>::AttributeHash() :
    QHash<Key,V>(parent),
    AttributeHashBase()
{
}

template<class Key, class V>
Q_INLINE_TEMPLATE typename QHash<Key, V>::iterator AttributeHash<Key,V>::insert ( const Key & key, const V & value ){
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


AttributeHashBase::AttributeHashBase()
{
}
