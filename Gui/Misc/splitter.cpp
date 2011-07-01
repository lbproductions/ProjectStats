#include "splitter.h"

#include <QPainter>

#include <QDebug>

using namespace Gui::Misc;

Splitter::Splitter(Qt::Orientation orientation, QWidget *parent) :
    QSplitter(orientation,parent)
{
}

#ifdef Q_WS_MAC
MacSplitterHandle::MacSplitterHandle(Qt::Orientation orientation, QSplitter *parent)
: QSplitterHandle(orientation, parent) {   }

// Paint the horizontal handle as a gradient, paint
// the vertical handle as a line.
void MacSplitterHandle::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QColor topColor(181, 181, 181);
    QColor bottomColor(158, 158, 158);
    QColor gradientStart(248, 248, 248);
    QColor gradientStop(225, 225, 225);

    if (orientation() == Qt::Vertical) {
	painter.setPen(topColor);
	painter.drawLine(0, 0, width(), 0);
	painter.setPen(bottomColor);
	painter.drawLine(0, height() - 1, width(), height() - 1);

        QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height() - 2));
	linearGrad.setColorAt(0, gradientStart);
	linearGrad.setColorAt(1, gradientStop);
	painter.fillRect(QRect(QPoint(0,1), size() - QSize(0, 2)), QBrush(linearGrad));

        painter.drawPixmap(width() / 2 - 2, 3, 4,4 , QPixmap(":/graphics/styles/mac/splitter/handle"));
    } else {
	painter.setPen(topColor);
	painter.drawLine(0, 0, 0, height());
    }
}

QSize MacSplitterHandle::sizeHint() const
{
    QSize parent = QSplitterHandle::sizeHint();
    if (orientation() == Qt::Vertical) {
        return parent + QSize(0, 2);
    } else {
	return QSize(1, parent.height());
    }
}

QSplitterHandle *Splitter::createHandle()
{
    return new MacSplitterHandle(orientation(), this);
}

void Splitter::myMoveSplitter(int pos)
{
    QSplitter::moveSplitter(sizes().at(0)+pos,1);
}
#endif

