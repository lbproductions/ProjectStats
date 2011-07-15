#include "splitter.h"

#include <QPainter>

#include <QDebug>

using namespace Gui::Misc;

Splitter::Splitter(Qt::Orientation orientation, QWidget *parent) :
    QSplitter(orientation,parent),
    m_fullscreen(false),
    m_leftToRight(false)
{
}

void Splitter::setFullscreen(bool fullscreen)
{
    m_fullscreen = fullscreen;
    repaint();
}

bool Splitter::isFullscreen()
{
    return m_fullscreen;
}

void Splitter::setLeftToRight(bool leftToRight)
{
    m_leftToRight = leftToRight;
    repaint();
}

bool Splitter::isLeftToRight()
{
    return m_leftToRight;
}


#ifdef Q_WS_MAC
MacSplitterHandle::MacSplitterHandle(Qt::Orientation orientation, Splitter *parent)
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
        if(static_cast<Splitter*>(parent())->isFullscreen())
        {
            if(static_cast<Splitter*>(parent())->isLeftToRight())
            {
                QColor leftColor(78,77,79);
                QColor rightColor(26,25,26);

                painter.setPen(leftColor);
                painter.drawLine(0, 0, 0, height());
                painter.setPen(rightColor);
                painter.drawLine(1, 0, 1, height());
            }
            else
            {
                QColor leftColor(26,25,26);
                QColor rightColor(78,77,79);

                painter.setPen(leftColor);
                painter.drawLine(2, 0, 2, height());
                painter.setPen(rightColor);
                painter.drawLine(3, 0, 3, height());
            }
        }
        else
        {
            painter.setPen(topColor);
            painter.drawLine(0, 0, 0, height());
        }
    }
}

QSize MacSplitterHandle::sizeHint() const
{
    QSize parentSize = QSplitterHandle::sizeHint();
    if (orientation() == Qt::Vertical)
    {
        return parentSize + QSize(0, 2);
    }
    else
    {
        if(static_cast<Splitter*>(parent())->isFullscreen())
        {
            return QSize(4, height());
        }
        else
        {
            return QSize(1, height());
        }
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

