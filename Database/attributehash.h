#ifndef ATTRIBUTEHASH_H
#define ATTRIBUTEHASH_H

#include <QMap>
#include <QObject>
#include <QVariant>

namespace Database{

class AttributeHashBase : public QObject
{
    Q_OBJECT
protected:
    explicit AttributeHashBase(QObject *parent = 0);
    AttributeHashBase(const AttributeHashBase& other);

    AttributeHashBase& operator=(const AttributeHashBase& other);

signals:

    void changed();
    void changed(QVariant);
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
    typename QMap<Key, V>::iterator it = QMap<Key,V>::insert(key,value);
    QVariant asdf = QVariant::fromValue<Key>(key);
    emit AttributeHash<Key,V>::changed();
    emit AttributeHash<Key,V>::changed(asdf);
    return it;
}

}

#endif // ATTRIBUTEHASH_H
