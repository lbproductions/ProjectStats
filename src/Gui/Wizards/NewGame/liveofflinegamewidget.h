#ifndef LIVEOFFLINEGAMEWIDGET_H
#define LIVEOFFLINEGAMEWIDGET_H

#include <QWizardPage>

namespace Ui {
    class LiveOfflineGameWidget;
}


namespace Gui
{

namespace Wizards
{

namespace NewGame
{

class LiveOfflineGameWidget : public QWizardPage
{
    Q_OBJECT

public:
    explicit LiveOfflineGameWidget(QWidget *parent = 0);
    ~LiveOfflineGameWidget();

    int nextId() const;

private:
    Ui::LiveOfflineGameWidget *ui;
    void saveOptions() const;
};

}
}
}

#endif // LIVEOFFLINEGAMEWIDGET_H
