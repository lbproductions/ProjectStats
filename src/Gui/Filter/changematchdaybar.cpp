#include "changematchdaybar.h"

#include <QHBoxLayout>
#include <QPushButton>

ChangeMatchdayBar::ChangeMatchdayBar(QWidget *parent) :
    QFrame(parent)
{
    QHBoxLayout* layout = new QHBoxLayout();

    QPushButton* previous = new QPushButton("<",this);
    previous->setStyleSheet("QPushButton {"
                            "background: transparent;"
                            "height: 16px;"
                            "width: 16px;"
                        "}"
                        "QPushButton:hover {"
                            "border: 6px transparent;"
                            "border-left: 6px transparent;"
                            "border-right: 6px transparent;"
                            "border-image: url(:/graphics/styles/mac/tabbar/button) 8px 16px 16px 8px;"
                            "padding-top: -8px;"
                            "padding-bottom: -8px;"
                            "padding-left: -6px;"
                            "padding-right: -6px;"
                        "}");
    previous->setFixedWidth(22);
    layout->addWidget(previous);

    layout->addStretch();

    QPushButton* next = new QPushButton(">",this);
    next->setStyleSheet("QPushButton {"
                            "background: transparent;"
                            "height: 16px;"
                            "width: 16px;"
                        "}"
                        "QPushButton:hover {"
                            "border: 6px transparent;"
                            "border-left: 6px transparent;"
                            "border-right: 6px transparent;"
                            "border-image: url(:/graphics/styles/mac/tabbar/button) 8px 8px 8px 8px;"
                            "padding-top: -3px;"
                            "padding-bottom: -3px;"
                            "padding-left: -3px;"
                            "padding-right: -3px;"

                        "}");
    next->setFixedWidth(22);
    layout->addWidget(next);

    layout->setContentsMargins(3,3,3,3);
    layout->setSpacing(12);
    setFixedHeight(21);

    this->setLayout(layout);

    this->setStyleSheet("ChangeMatchdayBar {"
                        "margin: 0px;"
                        "padding: 3px;"
                        "background-image: url(:/graphics/styles/mac/tabbar/background);"
                        "background-repeat: repeat-x;"
                  "}");

    connect(previous,SIGNAL(clicked()),this,SIGNAL(prevClicked()));
    connect(next,SIGNAL(clicked()),this,SIGNAL(nextClicked()));
}
