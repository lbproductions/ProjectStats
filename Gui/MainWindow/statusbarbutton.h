#ifndef STATUSBARBUTTON_H
#define STATUSBARBUTTON_H

#include <QPushButton>

namespace Gui
{
namespace MainWindow
{

class Statusbar;

class StatusbarButton : public QPushButton
{
    Q_OBJECT
public:
    explicit StatusbarButton(Statusbar *parent = 0);

};

}
}

#endif // STATUSBARBUTTON_H
