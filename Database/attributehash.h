#ifndef ATTRIBUTEHASH_H
#define ATTRIBUTEHASH_H

#include <QMap>
#include <QObject>

namespace Database{

class AttributeHashBase : public QObject
{
    Q_OBJECT
protected:
    explicit AttributeHashBase(QObject *parent = 0);

signals:

    void changed();
};

template<class Key, class V>
class AttributeHash : public QMap<Key,V>, public AttributeHashBase
{
public:
    explicit AttributeHash(QObject *parent = 0);

    typename QMap<Key, V>::iterator insert ( const Key & key, const V & value );

};

template<class Key, class V>
AttributeHash<Key,V>::AttributeHash(QObject *parent) :
    QMap<Key,V>(),
    AttributeHashBase(parent)
{
}

template<class Key, class V>
typename QMap<Key, V>::iterator AttributeHash<Key,V>::insert ( const Key & key, const V & value ){
    QMap<Key,V>::insert(key,value);
    emit AttributeHash<Key,V>::changed();
}

}

#endif // ATTRIBUTEHASH_H
