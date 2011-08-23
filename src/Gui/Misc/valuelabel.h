#ifndef VALUELABEL_H
#define VALUELABEL_H

#include <QLabel>

namespace Gui
{

namespace Misc
{

class ValueLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ValueLabel(QString text, QWidget *parent = 0);
    ValueLabel(QWidget *parent = 0);

    void paintEvent(QPaintEvent *event);

signals:

public slots:

};

}
}

#endif // VALUELABEL_H
