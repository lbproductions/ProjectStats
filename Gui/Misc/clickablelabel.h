#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>

namespace Gui
{

namespace Misc
{

class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickableLabel(QWidget *parent = 0);

signals:
    void clicked();

protected:
    void mouseReleaseEvent(QMouseEvent *event);

};

}
}

#endif // CLICKABLELABEL_H
