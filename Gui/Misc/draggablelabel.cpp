#include "draggablelabel.h"

#include <QDrag>
#include <QMimeData>

#include <Database/drink.h>

DraggableLabel::DraggableLabel(Database::Row* row, QWidget *parent) :
    QLabel(parent)
{
    m_row = row;
}

void DraggableLabel::mousePressEvent(QMouseEvent *event){
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    QByteArray encodedData;
    QDataStream stream(&encodedData, QIODevice::WriteOnly);
    stream << m_row->id();

    mimeData->setData("application/projectstats.livegame/drink",encodedData);
    drag->setMimeData(mimeData);
    QPixmap pixmap;
    pixmap.load(static_cast<Database::Drink*>(m_row)->iconPath->value());
    drag->setPixmap(pixmap);

    Qt::DropAction dropAction = drag->exec();
}


