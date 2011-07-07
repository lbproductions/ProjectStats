#ifndef LIVEGAMEINFOGROUPBOX_H
#define LIVEGAMEINFOGROUPBOX_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QPointer>

#include <Gui/Details/LiveGameDetails/abstractlivegamewidget.h>


namespace Database{
    class LiveGame;
}

namespace Gui{

    namespace Details{

        namespace LiveGameDetails{


class LiveGameInfoGroupBox : public AbstractLiveGameWidget
{
    Q_OBJECT
public:
    explicit LiveGameInfoGroupBox(Database::LiveGame* livegame, QWidget *parent = 0);

    virtual void updateWidget(QString lengthText);

signals:

public slots:
    void setFullscreen();

    void setNormalMode();

protected:

    QPointer<Database::LiveGame> m_game;

    QVBoxLayout* m_layout;

    QPalette m_defaultpalette;

};

}}}

#endif // LIVEGAMEINFOGROUPBOX_H
