#ifndef OFFLINEGAMEOPTIONSWIDGET_H
#define OFFLINEGAMEOPTIONSWIDGET_H

#include <QWizardPage>

namespace Ui {
    class OfflineGameOptionsWidget;
}

namespace Gui
{

namespace Wizards
{

namespace NewGame
{

class OfflineGameOptionsWidget : public QWizardPage
{
    Q_OBJECT

public:
    explicit OfflineGameOptionsWidget(QWidget *parent = 0);
    ~OfflineGameOptionsWidget();

    int nextId() const;
    bool isComplete() const;

private:
    Ui::OfflineGameOptionsWidget *ui;

    void saveOptions() const;

private slots:
    void on_checkBoxDetailled_stateChanged();
};

}
}
}

#endif // OFFLINEGAMEOPTIONSWIDGET_H
