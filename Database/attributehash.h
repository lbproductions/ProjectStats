#ifndef ATTRIBUTEHASH_H
#define ATTRIBUTEHASH_H

#include <QHash>

namespace Database{

template<class Key, class V>
class AttributeHash : public QHash<Key,V>
{
public:
    explicit AttributeHash(QObject *parent = 0);

    Q_INLINE_TEMPLATE typename QHash<Key, V>::iterator insert ( const Key & key, const V & value );

    QString toString();

signals:

    void changed();

public slots:

};

}

#endif // ATTRIBUTEHASH_H
