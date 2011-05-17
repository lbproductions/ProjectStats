#include "attributehash.h"

namespace Database {

AttributeHashBase::AttributeHashBase(QObject *parent):
    QObject(parent)
{
}

AttributeHashBase::AttributeHashBase(const AttributeHashBase& other) :
    QObject(other.parent())
{
}

AttributeHashBase& AttributeHashBase::operator=(const AttributeHashBase& other)
{
    setParent(other.parent());
    return *this;
}
}
