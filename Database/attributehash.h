#ifndef ATTRIBUTEHASH_H
#define ATTRIBUTEHASH_H

#include <QHash>
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
class AttributeHash : public QHash<Key,V>, public AttributeHashBase
{
public:
    explicit AttributeHash(QObject *parent = 0);

    typename QHash<Key, V>::iterator insert ( const Key & key, const V & value );

    QString toString();

};

template<class Key, class V>
AttributeHash<Key,V>::AttributeHash(QObject *parent) :
    QHash<Key,V>(),
    AttributeHashBase(parent)
{
}

template<class Key, class V>
typename QHash<Key, V>::iterator AttributeHash<Key,V>::insert ( const Key & key, const V & value ){
    QHash<Key,V>::insert(key,value);
    emit AttributeHash<Key,V>::changed();
}

template<class Key, class V>
QString AttributeHash<Key,V>::toString(){
    QString string = "asdf";
    foreach(Key k, this->keys()){
        string += k + ":" + this->value(k) + ", ";
    }
    return string;
}

}

#endif // ATTRIBUTEHASH_H
