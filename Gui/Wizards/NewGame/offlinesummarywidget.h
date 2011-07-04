#ifndef OFFLINESUMMARYWIDGET_H
#define OFFLINESUMMARYWIDGET_H

#include <QWizardPage>

namespace Database
{
    class Game;
}

namespace Ui {
    class OfflineSummaryWidget;
}

namespace Gui
{

namespace Wizards
{

namespace NewGame
{

class OfflineSummaryWidget : public QWizardPage
{
    Q_OBJECT

public:
    explicit OfflineSummaryWidget(QWidget *parent = 0);
    ~OfflineSummaryWidget();

    void initializePage();

    int nextId() const;

private:
    Ui::OfflineSummaryWidget *ui;
};

}
}
}

#endif // OFFLINESUMMARYWIDGET_H
