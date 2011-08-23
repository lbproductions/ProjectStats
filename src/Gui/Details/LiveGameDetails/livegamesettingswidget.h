#ifndef LIVEGAMESETTINSGSWIDGET_H
#define LIVEGAMESETTINSGSWIDGET_H

#include <QDialog>

namespace Ui {
    class LiveGameSettingsWidget;
}

namespace Gui
{

namespace Details
{

namespace LiveGameDetails
{

class LiveGameSettingsWidget : public QDialog
{
    Q_OBJECT

public:
    explicit LiveGameSettingsWidget(QWidget *parent = 0);
    ~LiveGameSettingsWidget();

    bool stateGraph();
    bool stateRoundsTable();
    bool statePlayerStats();
    bool stateTotalPoints();
    bool stateBeerWidget();
    bool stateInfoBox();
    bool stateComment();

private:
    Ui::LiveGameSettingsWidget *ui;

signals:
    void settingsChanged();
private slots:
    void on_pushButtonClose_clicked();
};

}
}
}
#endif // LIVEGAMESETTINSGSWIDGET_H
