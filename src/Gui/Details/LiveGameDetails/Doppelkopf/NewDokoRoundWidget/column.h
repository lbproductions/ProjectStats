#ifndef COLUMN_H
#define COLUMN_H

#include <QPointer>
#include <QMap>

class QGridLayout;

namespace Database{
    class DokoLiveGame;
    class Player;
}

namespace Gui
{

namespace Misc{
    class CheckBox;
    class PlayerCheckBox;
}

namespace Details
{

namespace LiveGameDetails
{

namespace DokoLiveGameDetails{

class Column : public QObject
{
    Q_OBJECT
public:
    explicit Column(Database::DokoLiveGame* game, QGridLayout* layout, int minRow, int column, QObject* parent = 0);

protected:

    QPointer<Database::DokoLiveGame> m_dokoLiveGame;

    QMap<Database::Player*,Misc::PlayerCheckBox*> m_checkBoxes;

signals:

public slots:
    virtual void update(Misc::CheckBox* check ,bool checked);

};

}}}}

#endif // COLUMN_H
