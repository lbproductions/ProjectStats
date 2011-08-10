#include "dokolivegameinfogroupbox.h"

#include <Database/Doppelkopf/dokolivegame.h>

#include <Gui/Misc/valuelabel.h>
#include <Gui/Misc/headerlabel.h>

#include <QSpacerItem>
#include <QHBoxLayout>

#include "handler.h"

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

        //Misc::ValueLabel* hochzeitStatsLabel = new Misc::ValueLabel("-", this);
        //m_dokogame->doko_hochzeitStats->futureWatcher()->connectTo(hochzeitStatsLabel);
        //layout->addWidget(hochzeitStatsLabel);

        m_layout->addLayout(layout);
    }

    if (m_dokogame->doko_mitSolo->value())
    {
        m_layout->addWidget(new Misc::HeaderLabel(tr("Soli"),this));

        QHBoxLayout* layout = new QHBoxLayout();
        Misc::ValueLabel* soliCountLabel = new Misc::ValueLabel("-", this);
        m_dokogame->doko_soloCount->futureWatcher()->connectTo(soliCountLabel);
        layout->addWidget(soliCountLabel);

        //Misc::ValueLabel* hochzeitStatsLabel = new Misc::ValueLabel("-", this);
        //m_dokogame->doko_hochzeitStats->futureWatcher()->connectTo(hochzeitStatsLabel);
        //layout->addWidget(hochzeitStatsLabel);

        m_layout->addLayout(layout);
    }

    if (m_dokogame->doko_mitPflichtsolo->value())
    {
        m_layout->addWidget(new Misc::HeaderLabel(tr("Pflichtsoli"),this));

        QHBoxLayout* layout = new QHBoxLayout();
        Misc::ValueLabel* pflichtSoliCountLabel = new Misc::ValueLabel("-", this);
        m_dokogame->doko_pflichtSoloCount->futureWatcher()->connectTo(pflichtSoliCountLabel);
        layout->addWidget(pflichtSoliCountLabel);

        //Misc::ValueLabel* hochzeitStatsLabel = new Misc::ValueLabel("-", this);
        //m_dokogame->doko_hochzeitStats->futureWatcher()->connectTo(hochzeitStatsLabel);
        //layout->addWidget(hochzeitStatsLabel);

        m_layout->addLayout(layout);
    }

    if (m_dokogame->doko_mitTrumpfabgabe->value())
    {
        m_layout->addWidget(new Misc::HeaderLabel(tr("Trumpfabgaben"),this));

        QHBoxLayout* layout = new QHBoxLayout();
        Misc::ValueLabel* trumpfabgabeCountLabel = new Misc::ValueLabel("-", this);
        m_dokogame->doko_trumpfabgabeCount->futureWatcher()->connectTo(trumpfabgabeCountLabel);
        layout->addWidget(trumpfabgabeCountLabel);

        //Misc::ValueLabel* hochzeitStatsLabel = new Misc::ValueLabel("-", this);
        //m_dokogame->doko_hochzeitStats->futureWatcher()->connectTo(hochzeitStatsLabel);
        //layout->addWidget(hochzeitStatsLabel);

        m_layout->addLayout(layout);
    }

    if (m_dokogame->doko_mitSchmeisserei->value())
    {
        m_layout->addWidget(new Misc::HeaderLabel(tr("Schmeissereien"),this));

        QHBoxLayout* layout = new QHBoxLayout();
        Misc::ValueLabel* schmeissereienCountLabel = new Misc::ValueLabel("-", this);
        m_dokogame->doko_schmeissereiCount->futureWatcher()->connectTo(schmeissereienCountLabel);
        layout->addWidget(schmeissereienCountLabel);

        //Misc::ValueLabel* hochzeitStatsLabel = new Misc::ValueLabel("-", this);
        //m_dokogame->doko_hochzeitStats->futureWatcher()->connectTo(hochzeitStatsLabel);
        //layout->addWidget(hochzeitStatsLabel);

        m_layout->addLayout(layout);
    }

    if (m_dokogame->doko_mitSchweinerei->value())
    {
        m_layout->addWidget(new Misc::HeaderLabel(tr("Schweinereien"),this));

        QHBoxLayout* layout = new QHBoxLayout();
        Misc::ValueLabel* schweinereienCountLabel = new Misc::ValueLabel("-", this);
        m_dokogame->doko_schweinereiCount->futureWatcher()->connectTo(schweinereienCountLabel);
        layout->addWidget(schweinereienCountLabel);

        //Misc::ValueLabel* hochzeitStatsLabel = new Misc::ValueLabel("-", this);
        //m_dokogame->doko_hochzeitStats->futureWatcher()->connectTo(hochzeitStatsLabel);
        //layout->addWidget(hochzeitStatsLabel);

        m_layout->addLayout(layout);
    }
}

void DokoLiveGameInfoGroupBox::updateWidget(QString lengthText){
//    LiveGameInfoGroupBox::updateWidget(lengthText);
//    QLabel* label;
//    if (m_dokogame->mitHochzeit()){
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(9)->layout())->itemAt(0)->widget());
//        label->setText(QString::number(m_dokogame->hochzeitCount()));
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(9)->layout())->itemAt(2)->widget());
//        if (m_dokogame->isFinished() || m_dokogame->rounds->value()().size() <= 1){
//            label->setText(" (" + QString::number(Handler::getInstance()->stats()->dokoStats()->hochzeitPlacementAfterRounds(m_dokogame,m_dokogame->rounds().size())) +
//                           ".|"+ QString::number(m_dokogame->hochzeitCount->value()()*100/m_dokogame->rounds->value()().size())+ "%)");
//        }
//        else{
//            label->setText(" (" + QString::number(Handler::getInstance()->stats()->dokoStats()->hochzeitPlacementAfterRounds(m_dokogame,m_dokogame->rounds().size())) +
//                           ".|"+ QString::number(m_dokogame->hochzeitCount->value()()*100/(m_dokogame->rounds->value()().size()-1))+ "%)");
//        }

//    }
//    if (m_dokogame->mitSolo()){
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(11)->layout())->itemAt(0)->widget());
//        label->setText(QString::number(m_dokogame->soloCount()));
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(11)->layout())->itemAt(2)->widget());
//        if (m_dokogame->isFinished() || m_dokogame->rounds().size() <= 1){
//            label->setText(" (" + QString::number(Handler::getInstance()->stats()->dokoStats()->soliPlacementAfterRounds(m_dokogame,m_dokogame->rounds().size())) +
//                           ".|"+ QString::number(m_dokogame->soloCount()*100/m_dokogame->rounds().size())+ "%)");
//        }
//        else{
//            label->setText(" (" + QString::number(Handler::getInstance()->stats()->dokoStats()->soliPlacementAfterRounds(m_dokogame,m_dokogame->rounds().size())) +
//                           ".|"+ QString::number(m_dokogame->soloCount()*100/(m_dokogame->rounds().size()-1))+ "%)");
//        }
//    }

//    if (m_dokogame->mitTrumpfabgabe()){
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(15)->layout())->itemAt(0)->widget());
//        label->setText(QString::number(m_dokogame->trumpfabgabeCount()));
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(15)->layout())->itemAt(2)->widget());
//        if (m_dokogame->isFinished() || m_dokogame->rounds().size() <= 1){
//            label->setText(" (" + QString::number(Handler::getInstance()->stats()->dokoStats()->trumpfabgabenPlacementAfterRounds(m_dokogame,m_dokogame->rounds().size())) +
//                           ".|"+ QString::number(m_dokogame->trumpfabgabeCount()*100/m_dokogame->rounds().size())+ "%)");
//        }
//        else{
//            label->setText(" (" + QString::number(Handler::getInstance()->stats()->dokoStats()->trumpfabgabenPlacementAfterRounds(m_dokogame,m_dokogame->rounds().size())) +
//                           ".|"+ QString::number(m_dokogame->trumpfabgabeCount()*100/(m_dokogame->rounds().size()-1))+ "%)");
//        }
//    }

//    if (m_dokogame->mitSchmeisserei()){
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(17)->layout())->itemAt(0)->widget());
//        label->setText(QString::number(m_dokogame->schmeissereiCount()));
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(17)->layout())->itemAt(2)->widget());
//        if (m_dokogame->isFinished() || m_dokogame->rounds().size() <= 1){
//            label->setText(" (" + QString::number(Handler::getInstance()->stats()->dokoStats()->schmeissereienPlacementAfterRounds(m_dokogame,m_dokogame->rounds().size())) +
//                           ".|"+ QString::number(m_dokogame->schmeissereiCount()*100/m_dokogame->rounds().size())+ "%)");
//        }
//        else{
//            label->setText(" (" + QString::number(Handler::getInstance()->stats()->dokoStats()->schmeissereienPlacementAfterRounds(m_dokogame,m_dokogame->rounds().size())) +
//                           ".|"+ QString::number(m_dokogame->schmeissereiCount()*100/(m_dokogame->rounds().size()-1))+ "%)");
//        }
//    }

//    if (m_dokogame->mitSchweinerei()){
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(19)->layout())->itemAt(0)->widget());
//        label->setText(QString::number(m_dokogame->schweinereiCount()));
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(19)->layout())->itemAt(2)->widget());
//        if (m_dokogame->isFinished() || m_dokogame->rounds().size() <= 1){
//            label->setText(" (" + QString::number(Handler::getInstance()->stats()->dokoStats()->schweinereienPlacementAfterRounds(m_dokogame,m_dokogame->rounds().size())) +
//                           ".|"+ QString::number(m_dokogame->schweinereiCount()*100/m_dokogame->rounds().size())+ "%)");
//        }
//        else{
//            label->setText(" (" + QString::number(Handler::getInstance()->stats()->dokoStats()->schweinereienPlacementAfterRounds(m_dokogame,m_dokogame->rounds().size())) +
//                           ".|"+ QString::number(m_dokogame->schweinereiCount()*100/(m_dokogame->rounds().size()-1))+ "%)");
//        }
//    }
//    if (m_dokogame->mitPflichtsolo()){
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(13)->layout())->itemAt(0)->widget());
//        label->setText(QString::number(m_dokogame->pflichtSoloCount())+"/"+QString::number(m_dokogame->playersSortedByPosition().size()));
//    }
}
