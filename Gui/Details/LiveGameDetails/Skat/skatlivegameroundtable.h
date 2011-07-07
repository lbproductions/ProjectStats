#ifndef SKATLIVEGAMEROUNDTABLE_H
#define SKATLIVEGAMEROUNDTABLE_H

#include <Gui/Details/LiveGameDetails/livegameroundtable.h>

namespace Database{
    namespace Skat{
        class SkatLiveGame;
        class SkatRound;
    }
}

namespace Gui{

namespace Details{

namespace LiveGameDetails
{

namespace SkatLiveGameDetails{

class SkatLiveGameRoundTable : public LiveGameRoundTable
{
public:
    SkatLiveGameRoundTable(Database::Skat::SkatLiveGame* livegame, QWidget *parent = 0);

    void addRound(Database::Round* round);

    void markCardMixer(bool fullscreen);
};

}}}}

#endif // SKATLIVEGAMEROUNDTABLE_H
