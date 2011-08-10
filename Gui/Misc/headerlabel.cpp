#include "headerlabel.h"

#include <QPainter>

using namespace Gui::Misc;

HeaderLabel::HeaderLabel(QString text, QWidget *parent) :
    QLabel(parent)
{
    this->setAlignment(Qt::AlignBottom);
    this->setText(text);
}

void HeaderLabel::paintEvent(QPaintEvent *event)
{
    QPainter* painter = new QPainter(this);
    QRect cr = this->contentsRect();
    cr.adjust(0,1,0,1);
    painter->setPen(QColor("black"));
    painter->setBrush(QColor("black"));
    painter->setFont(font());
    painter->drawText(cr,this->alignment(),this->text());
    painter->end();
    QLabel::paintEvent(event);
}
