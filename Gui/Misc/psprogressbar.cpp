#include "psprogressbar.h"
#include <QPainter>
#include <QPaintEvent>

#include <Gui/Misc/valuelabel.h>
#include <QPair>

#include <QDebug>

using namespace Gui::Misc;

PSProgressBar::PSProgressBar(QWidget *parent) :
    QProgressBar(parent),
    m_clickcount(0)
{
    setFullscreen();

    this->setMinimumHeight(35);
}

void PSProgressBar::paintEvent(QPaintEvent *event){
    QProgressBar::paintEvent(event);
    QPainter* painter = new QPainter();
    painter->begin(this);
    QFont font = this->font();
    double ratio = 1/((double)m_text.length()/4.0);
    if (ratio > 0 && ratio <= 1){
        font.setPixelSize(25*ratio);
    }
    else{
        font.setPixelSize(25);
    }
    this->setFont(font);
    painter->setPen(QColor("white"));
    painter->setBrush(QColor("white"));
    painter->drawText(QRect(this->height()/2,event->rect().y()+3,event->rect().width(),event->rect().height()),m_text);
    painter->end();
}

void PSProgressBar::setFullscreen(){
    this->setStyleSheet("QProgressBar{border: 1px solid black; border-radius: 5px; background-color: transparent; color: transparent; text-align: center;}QProgressBar::chunk {background-color: black;}");
}

void PSProgressBar::setNormalMode(){

}

void PSProgressBar::mousePressEvent(QMouseEvent *event){
    if (m_values.keys().size() > 0){
        QPair<int,ValueLabel*> pair = m_values.value(m_values.keys().at(m_clickcount%m_values.keys().size()));
        this->setValue(pair.first);
        m_text = pair.second->text();
        update();
        m_clickcount++;
    }
}

void PSProgressBar::registerNewDisplayValue(QString hashString, int value, QString displayText){
    QPair<int,ValueLabel*> pair;
    pair.first = value;
    ValueLabel* label = new ValueLabel(displayText,this);
    label->setVisible(false);
    pair.second = label;
    m_values.insert(hashString,pair);
}
