#ifndef GROUPBOX_H
#define GROUPBOX_H

#include <QFrame>

namespace Gui
{

namespace Misc
{

class GroupBox : public QFrame
{
    Q_OBJECT
public:
    explicit GroupBox(QWidget* contentWidget, QWidget *parent = 0);

};

}
}

#endif // GROUPBOX_H
