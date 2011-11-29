#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QPointer>

namespace Gui
{
namespace MainWindow
{

class MainWindow;

namespace Views
{

class View : public QWidget
{
    Q_OBJECT
public:
    explicit View(MainWindow *parent = 0);

public slots:
    virtual void updateStatusbar() = 0;

protected:
    MainWindow* m_mainWindow;
};

}
}
}

#endif // VIEW_H
