#ifndef WIZARDSIDEWIDGET_H
#define WIZARDSIDEWIDGET_H

#include <QWidget>

namespace Ui {
    class WizardSideWidget;
}

namespace Gui
{

namespace Wizards
{

namespace NewGame
{

class WizardSideWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WizardSideWidget(QWidget *parent = 0);
    ~WizardSideWidget();

private:
    Ui::WizardSideWidget *ui;
};

}
}
}

#endif // WIZARDSIDEWIDGET_H
