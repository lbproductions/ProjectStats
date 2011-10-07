#include "dokolivegameinfogroupbox.h"

#include <Database/Doppelkopf/dokolivegame.h>

#include <Gui/Misc/valuelabel.h>
#include <Gui/Misc/headerlabel.h>

#include <QSpacerItem>
#include <QHBoxLayout>

#include <Misc/handler.h>

using namespace Gui::Details::LiveGameDetails::DokoLiveGameDetails;

DokoLiveGameInfoGroupBox::DokoLiveGameInfoGroupBox(Database::DokoLiveGame* dokogame, QWidget* parent):
    LiveGameInfoGroupBox(dokogame,parent),
    m_dokogame(dokogame)
{
    if (m_dokogame->doko_mitHochzeit->value())
    {
        m_layout->addWidget(new Misc::HeaderLabel(tr("Hochzeiten"),this));

        QHBoxLayout* layout = new QHBoxLayout();

        Misc::ValueLabel* hochzeitCountLabel = new Misc::ValueLabel("-", this);
        m_dokogame->doko_hochzeitCount->futureWatcher()->connectTo(hochzeitCountLabel);
        layout->addWidget(hochzeitCountLabel);

        Misc::ValueLabel* hochzeitStatsLabel = new Misc::ValueLabel("-", this);
        m_dokogame->doko_hochzeitStats->futureWatcher()->connectTo(hochzeitStatsLabel);
        layout->addWidget(hochzeitStatsLabel);

        m_layout->addLayout(layout);
    }

    if (m_dokogame->doko_mitSolo->value())
    {
        m_layout->addWidget(new Misc::HeaderLabel(tr("Soli"),this));

        QHBoxLayout* layout = new QHBoxLayout();
        Misc::ValueLabel* soliCountLabel = new Misc::ValueLabel("-", this);
        m_dokogame->doko_soloCount->futureWatcher()->connectTo(soliCountLabel);
        layout->addWidget(soliCountLabel);

        Misc::ValueLabel* soloStatsLabel = new Misc::ValueLabel("-", this);
        m_dokogame->doko_soloStats->futureWatcher()->connectTo(soloStatsLabel);
        layout->addWidget(soloStatsLabel);

        m_layout->addLayout(layout);
    }

    if (m_dokogame->doko_mitPflichtsolo->value())
    {
        m_layout->addWidget(new Misc::HeaderLabel(tr("Pflichtsoli"),this));

        QHBoxLayout* layout = new QHBoxLayout();
        Misc::ValueLabel* pflichtSoliCountLabel = new Misc::ValueLabel("-", this);
        m_dokogame->doko_pflichtSoloCount->futureWatcher()->connectTo(pflichtSoliCountLabel);
        layout->addWidget(pflichtSoliCountLabel);

        Misc::ValueLabel* pflichtsoloStatsLabel = new Misc::ValueLabel("-", this);
        m_dokogame->doko_pflichtSoloStats->futureWatcher()->connectTo(pflichtsoloStatsLabel);
        layout->addWidget(pflichtsoloStatsLabel);

        m_layout->addLayout(layout);
    }

    if (m_dokogame->doko_mitTrumpfabgabe->value())
    {
        m_layout->addWidget(new Misc::HeaderLabel(tr("Trumpfabgaben"),this));

        QHBoxLayout* layout = new QHBoxLayout();
        Misc::ValueLabel* trumpfabgabeCountLabel = new Misc::ValueLabel("-", this);
        m_dokogame->doko_trumpfabgabeCount->futureWatcher()->connectTo(trumpfabgabeCountLabel);
        layout->addWidget(trumpfabgabeCountLabel);

        Misc::ValueLabel* trumpfabgabeStatsLabel = new Misc::ValueLabel("-", this);
        m_dokogame->doko_trumpfabgabeStats->futureWatcher()->connectTo(trumpfabgabeStatsLabel);
        layout->addWidget(trumpfabgabeStatsLabel);

        m_layout->addLayout(layout);
    }

    if (m_dokogame->doko_mitSchmeisserei->value())
    {
        m_layout->addWidget(new Misc::HeaderLabel(tr("Schmeissereien"),this));

        QHBoxLayout* layout = new QHBoxLayout();
        Misc::ValueLabel* schmeissereienCountLabel = new Misc::ValueLabel("-", this);
        m_dokogame->doko_schmeissereiCount->futureWatcher()->connectTo(schmeissereienCountLabel);
        layout->addWidget(schmeissereienCountLabel);

        Misc::ValueLabel* schmeissereiStatsLabel = new Misc::ValueLabel("-", this);
        m_dokogame->doko_schmeissereiStats->futureWatcher()->connectTo(schmeissereiStatsLabel);
        layout->addWidget(schmeissereiStatsLabel);

        m_layout->addLayout(layout);
    }

    if (m_dokogame->doko_mitSchweinerei->value())
    {
        m_layout->addWidget(new Misc::HeaderLabel(tr("Schweinereien"),this));

        QHBoxLayout* layout = new QHBoxLayout();
        Misc::ValueLabel* schweinereienCountLabel = new Misc::ValueLabel("-", this);
        m_dokogame->doko_schweinereiCount->futureWatcher()->connectTo(schweinereienCountLabel);
        layout->addWidget(schweinereienCountLabel);

        Misc::ValueLabel* schweinereiStatsLabel = new Misc::ValueLabel("-", this);
        m_dokogame->doko_schweinereiStats->futureWatcher()->connectTo(schweinereiStatsLabel);
        layout->addWidget(schweinereiStatsLabel);

        m_layout->addLayout(layout);
    }
}
