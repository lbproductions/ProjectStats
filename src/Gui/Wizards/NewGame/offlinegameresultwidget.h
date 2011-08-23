#ifndef OFFLINEGAMERESULTWIDGET_H
#define OFFLINEGAMERESULTWIDGET_H

#include <QWizardPage>
#include <QPointer>

namespace Database
{
    class Game;
}

namespace Ui {
    class OfflineGameResultWidget;
}

namespace Gui
{

namespace Misc
{
    class PlacesComboBox;
}

namespace Wizards
{

namespace NewGame
{

class OfflineGameResultWidget : public QWizardPage
{
    Q_OBJECT

public:
    explicit OfflineGameResultWidget(QWidget *parent = 0);
    ~OfflineGameResultWidget();

    /**
     * Verwaltet die Anzahl an Spinboxen und Comboboxen je nach Anzahl der Spieler, die in der vorigen Wizard-Page ausgewählt wurden
     */
    void initializePage();

    /**
     * Befüllt die ComboBoxen und LineEdits mit entsprechendem Inhalt
     */
    void setupWidget();

    bool isComplete() const;

    int nextId() const;

private:
    Ui::OfflineGameResultWidget *ui;

    QPointer<Gui::Misc::PlacesComboBox> m_placesComboBox;
};

}
}
}

#endif // OFFLINEGAMERESULTWIDGET_H
