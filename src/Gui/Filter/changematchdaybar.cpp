#include "changematchdaybar.h"

#include <QHBoxLayout>
#include <QPushButton>

ChangeMatchdayBar::ChangeMatchdayBar(QWidget *parent) :
    QFrame(parent)
{
    QHBoxLayout* layout = new QHBoxLayout();

    QPushButton* previous = new QPushButton("Previous",this);
    layout->addWidget(previous);

    layout->addStretch();

    QPushButton* next = new QPushButton("Next",this);
    layout->addWidget(next);

    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(12);
    setFixedHeight(23);

    this->setLayout(layout);

    this->setStyleSheet("ChangeMatchdayBar {"
                        "margin: 0px;"
                        "padding: 0px;"
                    "background-image: url(:/graphics/styles/mac/statusbar/background); "
                    "background-repeat: repeat-x;"
                    "background-position: top left;"
                    "background-origin: margin;"
                  "}");

    connect(previous,SIGNAL(clicked()),this,SIGNAL(prevClicked()));
    connect(next,SIGNAL(clicked()),this,SIGNAL(nextClicked()));
}
