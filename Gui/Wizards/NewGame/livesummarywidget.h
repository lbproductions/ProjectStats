#ifndef LIVESUMMARYWIDGET_H
#define LIVESUMMARYWIDGET_H

#include <QWizardPage>

namespace Database
{
    class LiveGame;
}

namespace Ui {
    class LiveSummaryWidget;
}

namespace Gui
{

namespace Wizards
{

namespace NewGame
{

class LiveSummaryWidget : public QWizardPage
{
    Q_OBJECT

public:
    explicit LiveSummaryWidget(QWidget *parent = 0);
    ~LiveSummaryWidget();

//    void fillWidget(Database::LiveGame* livegame);

private:
    Ui::LiveSummaryWidget *ui;

    bool active;
};

}
}
}

#endif // LIVESUMMARYWIDGET_H
