#ifndef DOKOENDLIVEGAMEWIDGET_H
#define DOKOENDLIVEGAMEWIDGET_H

#include <Gui/Details/LiveGameDetails/endlivegamewidget.h>

class QGridLayout;

namespace Database{
    class DokoLiveGame;
}

namespace Gui
{

namespace Details
{

namespace LiveGameDetails
{

namespace DokoLiveGameDetails
{


class DokoEndLiveGameWidget : public EndLiveGameWidget
{
public:
    DokoEndLiveGameWidget(Database::DokoLiveGame* livegame, QWidget *parent = 0);

    void addTypeSpecificInformation(QGridLayout* layout, int row, int minColumn, Database::Player* player);

private:
    QPointer<Database::DokoLiveGame> m_dokolivegame;
};

}}}}

#endif // DOKOENDLIVEGAMEWIDGET_H
