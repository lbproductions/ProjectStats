#ifndef SIDEBARCONTROLLER_H
#define SIDEBARCONTROLLER_H

#include <QWidget>

namespace Ui {
    class SidebarController;
}

namespace Database{
    class LiveGame;
}

namespace Gui{

namespace Details{

namespace LiveGameDetails{

namespace Sidebar{

class SidebarPage;

class SidebarController : public QWidget
{
    Q_OBJECT

public:
    explicit SidebarController(Database::LiveGame* liveGame, QWidget *parent = 0);
    ~SidebarController();

private slots:
    void on_pushButtonLeft_clicked();

    void on_pushButtonRight_clicked();

    void currentPageChanged();

private:
    Ui::SidebarController *ui;

    int m_pageCounter;
    QList<SidebarPage*> m_sides;
    Database::LiveGame* m_liveGame;

    void setupWidget();
};

}}}}

#endif // SIDEBARCONTROLLER_H
