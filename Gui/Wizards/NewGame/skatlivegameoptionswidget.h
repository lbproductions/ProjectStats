#ifndef SKATLIVEGAMEOPTIONSWIDGET_H
#define SKATLIVEGAMEOPTIONSWIDGET_H

#include <QWizardPage>
#include <QPointer>

namespace Ui {
    class SkatLiveGameOptionsWidget;
}

namespace Database{
    class SkatLiveGame;
}

namespace Gui
{

namespace Wizards
{

namespace NewGame
{

class SkatLiveGameOptionsWidget : public QWizardPage
{
    Q_OBJECT

public:
    explicit SkatLiveGameOptionsWidget(QWidget *parent = 0);
    ~SkatLiveGameOptionsWidget();

    int nextId() const;

    bool isComplete() const;

private slots:
    void on_buttonGroup_buttonClicked(int id);

private:
    Ui::SkatLiveGameOptionsWidget *ui;

    QPointer<Database::SkatLiveGame> m_skatlivegame;

    void saveOptions() const;
};

}}}

#endif // SKATLIVEGAMEOPTIONSWIDGET_H
