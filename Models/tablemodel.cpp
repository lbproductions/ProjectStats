#include "tablemodel.h"

#include <QMimeData>
#include <QIcon>
#include <QPixmap>
#include <QDebug>

namespace Models {

TableModelBase::TableModelBase(QObject *parent) :
    QAbstractTableModel(parent)
{
}

}
