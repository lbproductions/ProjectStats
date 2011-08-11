#include "tablemodel.h"

#include <QMimeData>
#include <QIcon>
#include <QPixmap>
#include <QDebug>

namespace Models {

TableModelBase::TableModelBase(QObject *parent) :
    QAbstractTableModel(parent),
    m_displayRole(AttributeVariant::MainWindow)
{
}

AttributeVariant::DisplayRole TableModelBase::displayRole(){
    return m_displayRole;
}

void TableModelBase::setDisplayRole(AttributeVariant::DisplayRole role){
    m_displayRole = role;
    this->reset();
}

}
