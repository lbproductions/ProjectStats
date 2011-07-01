#ifndef HEADERLABEL_H
#define HEADERLABEL_H

#include <QLabel>

namespace Gui
{

namespace Misc
{

class HeaderLabel : public QLabel
{
    Q_OBJECT
public:
    explicit HeaderLabel(QString text, QWidget *parent = 0);

signals:

public slots:

};

}
}

#endif // HEADERLABEL_H
