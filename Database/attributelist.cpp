#include "attributelist.h"

namespace Database {

AttributeListBase::AttributeListBase(QObject *parent):
    QObject(parent)
{
}

AttributeListBase::AttributeListBase(const AttributeListBase& other) :
    QObject(other.parent())
{
}

AttributeListBase& AttributeListBase::operator=(const AttributeListBase& other)
{
    setParent(other.parent());
    return *this;
}

}
