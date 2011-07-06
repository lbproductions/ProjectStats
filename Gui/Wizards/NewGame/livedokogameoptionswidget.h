#ifndef LIVEDOKOGAMEOPTIONSWIDGET_H
#define LIVEDOKOGAMEOPTIONSWIDGET_H

#include <QWizardPage>
#include <QPointer>

namespace Database
{
    class LiveGame;
    class DokoLiveGame;
}

namespace Ui {
    class LiveDokoGameOptionsWidget;
}

namespace Gui
{

namespace Wizards
{

namespace NewGame
{

class LiveDokoGameOptionsWidget : public QWizardPage
{
    Q_OBJECT

public:
    explicit LiveDokoGameOptionsWidget(QWidget *parent = 0);
    ~LiveDokoGameOptionsWidget();

    int nextId() const;

private slots:
    void on_checkBoxSolo_clicked(bool checked);

    void on_checkBoxSchmeisserei_clicked(bool checked);

private:
    Ui::LiveDokoGameOptionsWidget *ui;

    void saveOptions() const;
};

}
}
}

#endif // LIVEDOKOGAMEOPTIONSWIDGET_H
