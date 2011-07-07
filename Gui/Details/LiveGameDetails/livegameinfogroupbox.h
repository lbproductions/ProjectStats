#ifndef LIVEGAMEINFOGROUPBOX_H
#define LIVEGAMEINFOGROUPBOX_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QPointer>

namespace Database{
    class LiveGame;
}

namespace Gui{

    namespace Details{

        namespace LiveGameDetails{


class LiveGameInfoGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit LiveGameInfoGroupBox(Database::LiveGame* livegame, QWidget *parent = 0);

    virtual void updateWidget(QString lengthText);

signals:

public slots:

protected:

    QPointer<Database::LiveGame> m_game;

    QVBoxLayout* m_layout;

};

}}}

#endif // LIVEGAMEINFOGROUPBOX_H
