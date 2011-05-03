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

    Q_INLINE_TEMPLATE typename QHash<Key, V>::iterator insert ( const Key & key, const V & value );

    QString toString();

};

}

#endif // ATTRIBUTEHASH_H
