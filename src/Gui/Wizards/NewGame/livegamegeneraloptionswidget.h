#ifndef LIVEGAMEGENERALOPTIONSWIDGET_H
#define LIVEGAMEGENERALOPTIONSWIDGET_H

#include <QWizardPage>

namespace Database
{
    class LiveGame;
    class Player;
    class Place;
}

namespace Ui {
    class LiveGameGeneralOptionsWidget;
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

            class LiveGameGeneralOptionsWidget : public QWizardPage
            {
                Q_OBJECT

                public:
                    explicit LiveGameGeneralOptionsWidget(QWidget *parent = 0);
                    ~LiveGameGeneralOptionsWidget();

                    void setupWidget();

                    Database::LiveGame* createLiveGame();

                    QString selectedType();

                    int selectedPlayersCount();

                    int nextId() const;

                    bool isComplete() const;

                    void saveOptions() const;

                    QList<Database::Player*> selectedPlayers();

                    Database::Place *selectedPlace();

                private:
                    Ui::LiveGameGeneralOptionsWidget *ui;
                    Gui::Misc::PlacesComboBox* placesbox;

                    void generatePlayerPositions();
                    QList<Database::Player*> minimumPlayerConstellation();

                private slots:
                    void on_pushButtonDeselect_clicked();
                    void on_pushButtonSelect_clicked();
                    void on_comboBoxGameType_currentIndexChanged(int index);

                    void on_pushButtonGeneratePositions_clicked();
                    void on_pushButton_clicked();

                     void on_chooseUnfinishedGamesDialogAccepted();
            };

        }

    }

}

#endif // LIVEGAMEGENERALOPTIONSWIDGET_H
