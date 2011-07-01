#include "valuelabel.h"

#include <QPainter>
#include <QPaintEvent>

using namespace Gui::Misc;

ValueLabel::ValueLabel(QWidget *parent) :
    QLabel(parent)
{
}

ValueLabel::ValueLabel(QString text, QWidget *parent) :
    QLabel(parent)
{
    this->setText(text);
}

void ValueLabel::paintEvent(QPaintEvent *event){
    QPainter* painter = new QPainter();
    painter->begin(this);
    painter->setPen(QColor("black"));
    painter->setBrush(QColor("black"));
    painter->drawText(QRect(event->rect().x()+2,event->rect().y()+2,event->rect().width(),event->rect().height()),this->text());
    painter->end();
    QLabel::paintEvent(event);
}
