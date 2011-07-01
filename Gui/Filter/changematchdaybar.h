#ifndef CHANGEMATCHDAYBAR_H
#define CHANGEMATCHDAYBAR_H

#include <QFrame>

class ChangeMatchdayBar : public QFrame
{
    Q_OBJECT
public:
    explicit ChangeMatchdayBar(QWidget *parent = 0);

signals:
    void prevClicked();
    void nextClicked();

public slots:

};

#endif // CHANGEMATCHDAYBAR_H
