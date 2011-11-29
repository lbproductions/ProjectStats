#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QFrame>
#include <QPointer>

class QVBoxLayout;

namespace Gui
{
namespace MainWindow
{

class StatusbarButton;
class MainWindow;

class Statusbar : public QFrame
{
    Q_OBJECT
public:
    explicit Statusbar(MainWindow *parent = 0);

    void setLeftButton(const QString &text, QAction *action);

    void disableLeftButton();

private:
    QVBoxLayout* m_vBoxLayout;
    StatusbarButton* m_leftButton;

};
}
}

#endif // STATUSBAR_H
