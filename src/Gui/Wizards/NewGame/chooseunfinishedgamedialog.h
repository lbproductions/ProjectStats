#ifndef CHOOSEUNFINISHEDGAMEDIALOG_H
#define CHOOSEUNFINISHEDGAMEDIALOG_H

#include <QWizardPage>

class QListWidgetItem;

namespace Ui {
    class ChooseUnfinishedGameDialog;
}

namespace Database
{
    class Player;
    class LiveGame;
}

namespace Gui
{

namespace Wizards
{
    class NewGameWizard;

namespace NewGame
{

class ChooseUnfinishedGameDialog : public QWizardPage
{
    Q_OBJECT

public:
    explicit ChooseUnfinishedGameDialog(Gui::Wizards::NewGameWizard *parent);
    ~ChooseUnfinishedGameDialog();

    Database::LiveGame* selectedGame();

    bool newGameItemIsChosen();

private slots:
    int nextId() const;

    bool isComplete() const;

    void initializePage();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    void keyPressEvent(QKeyEvent* event);

    Ui::ChooseUnfinishedGameDialog *ui;

    Gui::Wizards::NewGameWizard* m_wizard;
};

}}}

#endif // CHOOSEUNFINISHEDGAMEDIALOG_H
