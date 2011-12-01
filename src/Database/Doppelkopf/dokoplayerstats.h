#ifndef DOKOPLAYERSTATS_H
#define DOKOPLAYERSTATS_H

#include <QObject>

#include <LBDatabase/LBDatabase.h>

namespace Database{

    class Player;
    class Game;

class DokoPlayerStats : public AttributeOwner
{
public:
    DokoPlayerStats(Player* player);

    /*!
      Gibt alle Attribute dieser Row zurück.

      \return Alle Attribute dieser Row
      */
    QList<AttributeBase*> attributes() const;

    /*!
      Gibt das Attribut mit dem Namen \p name oder 0 zurück, falls es dieses nicht gibt.

      \return das Attribut mit dem Namen \p name oder 0, falls es dieses nicht gibt.
      */
    AttributeBase *attribute(const QString &name) const;

    DECLARE_LISTATTRIBUTE(Game*,DokoPlayerStats,dokoGames)
    DECLARE_ATTRIBUTE(int,DokoPlayerStats,re)
    DECLARE_ATTRIBUTE(double,DokoPlayerStats,rePercentage)
    DECLARE_ATTRIBUTE(int,DokoPlayerStats,reWins)
    DECLARE_ATTRIBUTE(double,DokoPlayerStats,reWinsPercentage)
    DECLARE_ATTRIBUTE(int,DokoPlayerStats,contra)
    DECLARE_ATTRIBUTE(double,DokoPlayerStats,contraPercentage)
    DECLARE_ATTRIBUTE(int,DokoPlayerStats,contraWins)
    DECLARE_ATTRIBUTE(double,DokoPlayerStats,contraWinsPercentage)
    DECLARE_ATTRIBUTE(int,DokoPlayerStats,hochzeiten)
    DECLARE_ATTRIBUTE(int,DokoPlayerStats,soli)
    DECLARE_ATTRIBUTE(int,DokoPlayerStats,trumpfabgaben)
    DECLARE_ATTRIBUTE(int,DokoPlayerStats,schweinereien)
    DECLARE_ATTRIBUTE(int,DokoPlayerStats,schmeissereien)
    DECLARE_ATTRIBUTE(double,DokoPlayerStats,pointAveragePerRound)
    DECLARE_ATTRIBUTE(double,DokoPlayerStats,roundWinsPercentage)


private:
    Player* m_player;
};

}
#endif // DOKOPLAYERSTATS_H
