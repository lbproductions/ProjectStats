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
    QFont f = font();
    f.setBold(true);
    this->setFont(f);
    this->setAlignment(Qt::AlignTop);
}

void ValueLabel::paintEvent(QPaintEvent *event){
    QPainter* painter = new QPainter(this);
    QRect cr = this->contentsRect();
    cr.adjust(0,1,0,1);
    painter->begin(this);
    painter->setPen(QColor("black"));
    painter->setBrush(QColor("black"));
    painter->setFont(font());
    painter->drawText(cr,this->alignment(),this->text());
    painter->end();
    QLabel::paintEvent(event);
}
