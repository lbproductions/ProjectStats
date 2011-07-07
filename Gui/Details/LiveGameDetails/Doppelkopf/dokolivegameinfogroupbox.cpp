#include "dokolivegameinfogroupbox.h"

#include <Database/Doppelkopf/dokolivegame.h>

#include <Gui/Misc/valuelabel.h>
#include <Gui/Misc/headerlabel.h>

#include <QSpacerItem>

#include "handler.h"

using namespace Gui::Details::LiveGameDetails::DokoLiveGameDetails;

DokoLiveGameInfoGroupBox::DokoLiveGameInfoGroupBox(Database::DokoLiveGame* dokogame, QWidget* parent):
    LiveGameInfoGroupBox(dokogame,parent),
    m_dokogame(dokogame)
{
//    if (m_dokogame->doko_mitHochzeit->value()){
//        m_layout->addWidget(new Misc::HeaderLabel(tr("Hochzeiten"),this));
//        QHBoxLayout* layout = new QHBoxLayout();
//        layout->addWidget(new Misc::ValueLabel(QString::number(m_dokogame->doko_hochzeitCount->value()),this));
//        layout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding, QSizePolicy::Expanding));
//        layout->addWidget(new Misc::ValueLabel(" (" + QString::number(m_dokogame->doko_hochzeitCountAfterRounds->value(m_dokogame->rounds->value().size())) +
//                                     ". | "+ QString::number(m_dokogame->doko_hochzeitCount->value()*100/m_dokogame->rounds->value().size())+ "%)",this));
//        m_layout->addLayout(layout);
//    }
//    else{
//        m_layout->addWidget(new Misc::HeaderLabel("",this));
//        m_layout->addWidget(new Misc::ValueLabel("",this));
//    }

//    if (m_dokogame->doko_mitSolo->value()){
//        m_layout->addWidget(new Misc::HeaderLabel(tr("Soli"),this));
//        QHBoxLayout* layout = new QHBoxLayout();
//        layout->addWidget(new Misc::ValueLabel(QString::number(m_dokogame->doko_soloCount->value()),this));
//        layout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding, QSizePolicy::Expanding));
//        layout->addWidget(new Misc::ValueLabel(" (" + QString::number(m_dokogame->doko_soloCountAfterRounds->value(m_dokogame,m_dokogame->rounds().size())) +
//                                               "./"+ QString::number(Handler::getInstance()->stats()->dokoStats()->dokoGamesWithSoliAfterRounds(m_dokogame->rounds().size()))+ ")",this));
//        m_layout->addLayout(layout);
//    }
//    else{
//        m_layout->addWidget(new Misc::HeaderLabel("",this));
//        m_layout->addWidget(new Misc::ValueLabel("",this));
//    }

//    if (m_dokogame->doko_mitPflichtsolo->value()){
//        m_layout->addWidget(new Misc::HeaderLabel(tr("Pflicht-Soli"),this));
//        QHBoxLayout* layout = new QHBoxLayout();
//        layout->addWidget(new Misc::ValueLabel(QString::number(m_dokogame->pflichtSoloCount())+"/"+QString::number(m_dokogame->playersSortedByPosition().size()),this));
//        m_layout->addLayout(layout);
//    }
//    else{
//        m_layout->addWidget(new Misc::HeaderLabel("",this));
//        m_layout->addWidget(new Misc::ValueLabel("",this));
//    }

//    if (m_dokogame->doko_mitTrumpfabgabe->value()){
//        m_layout->addWidget(new Misc::HeaderLabel(tr("Trumpfabgaben"),this));
//        QHBoxLayout* layout = new QHBoxLayout();
//        layout->addWidget(new Misc::ValueLabel(QString::number(m_dokogame->trumpfabgabeCount()),this));
//        layout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding, QSizePolicy::Expanding));
//        layout->addWidget(new Misc::ValueLabel(" (" + QString::number(Handler::getInstance()->stats()->dokoStats()->trumpfabgabenPlacementAfterRounds(m_dokogame,m_dokogame->rounds().size())) +
//                                               "./"+ QString::number(Handler::getInstance()->stats()->dokoStats()->dokoGamesWithTrumpfabgabenAfterRounds(m_dokogame->rounds().size()))+ ")",this));
//        m_layout->addLayout(layout);
//    }
//    else{
//        m_layout->addWidget(new Misc::HeaderLabel("",this));
//        m_layout->addWidget(new Misc::ValueLabel("",this));
//    }

//    if (m_dokogame->doko_mitSchmeisserei->value()){
//        m_layout->addWidget(new Misc::HeaderLabel(tr("Schmeissereien"),this));
//        QHBoxLayout* layout = new QHBoxLayout();
//        layout->addWidget(new Misc::ValueLabel(QString::number(m_dokogame->schmeissereiCount()),this));
//        layout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding, QSizePolicy::Expanding));
//        layout->addWidget(new Misc::ValueLabel(" (" + QString::number(Handler::getInstance()->stats()->dokoStats()->schmeissereienPlacementAfterRounds(m_dokogame,m_dokogame->rounds().size())) +
//                                               "./"+ QString::number(Handler::getInstance()->stats()->dokoStats()->dokoGamesWithSchmeissereienAfterRounds(m_dokogame->rounds().size()))+ ")",this));
//        m_layout->addLayout(layout);
//    }
//    else{
//        m_layout->addWidget(new Misc::HeaderLabel("",this));
//        m_layout->addWidget(new Misc::ValueLabel("",this));
//    }

//    if (m_dokogame->doko_mitSchweinerei->value()){
//        m_layout->addWidget(new Misc::HeaderLabel(tr("Schweinereien"),this));
//        QHBoxLayout* layout = new QHBoxLayout();
//        layout->addWidget(new Misc::ValueLabel(QString::number(m_dokogame->schweinereiCount()),this));
//        layout->addItem(new QSpacerItem(20,20,QSizePolicy::Expanding, QSizePolicy::Expanding));
//        layout->addWidget(new Misc::ValueLabel(" (" + QString::number(Handler::getInstance()->stats()->dokoStats()->schweinereienPlacementAfterRounds(m_dokogame,m_dokogame->rounds().size())) +
//                                               "./"+ QString::number(Handler::getInstance()->stats()->dokoStats()->dokoGamesWithSchweinereienAfterRounds(m_dokogame->rounds().size()))+ ")",this));
//        m_layout->addLayout(layout);
//    }
//    else{
//        m_layout->addWidget(new Misc::HeaderLabel("",this));
//        m_layout->addWidget(new Misc::ValueLabel("",this));
//    }
}

void DokoLiveGameInfoGroupBox::updateWidget(QString lengthText){
    LiveGameInfoGroupBox::updateWidget(lengthText);
//    QLabel* label;
//    if (m_dokogame->mitHochzeit()){
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(9)->layout())->itemAt(0)->widget());
//        label->setText(QString::number(m_dokogame->hochzeitCount()));
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(9)->layout())->itemAt(2)->widget());
//        label->setText(" (" + QString::number(Handler::getInstance()->stats()->dokoStats()->hochzeitPlacementAfterRounds(m_dokogame,m_dokogame->rounds().size())) +
//                       ".|"+ QString::number(m_dokogame->hochzeitCount()*100/m_dokogame->rounds().size())+ "%)");

//    }
//    if (m_dokogame->mitSolo()){
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(11)->layout())->itemAt(0)->widget());
//        label->setText(QString::number(m_dokogame->soloCount()));
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(11)->layout())->itemAt(2)->widget());
//        label->setText(" (" + QString::number(Handler::getInstance()->stats()->dokoStats()->soliPlacementAfterRounds(m_dokogame,m_dokogame->rounds().size())) +
//                       ".|"+ QString::number(m_dokogame->soloCount()*100/m_dokogame->rounds().size())+ "%)");
//    }

//    if (m_dokogame->mitTrumpfabgabe()){
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(15)->layout())->itemAt(0)->widget());
//        label->setText(QString::number(m_dokogame->trumpfabgabeCount()));
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(15)->layout())->itemAt(2)->widget());
//        label->setText(" (" + QString::number(Handler::getInstance()->stats()->dokoStats()->trumpfabgabenPlacementAfterRounds(m_dokogame,m_dokogame->rounds().size())) +
//                       ".|"+ QString::number(m_dokogame->trumpfabgabeCount()*100/m_dokogame->rounds().size())+ "%)");
//    }

//    if (m_dokogame->mitSchmeisserei()){
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(17)->layout())->itemAt(0)->widget());
//        label->setText(QString::number(m_dokogame->schmeissereiCount()));
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(17)->layout())->itemAt(2)->widget());
//        label->setText(" (" + QString::number(Handler::getInstance()->stats()->dokoStats()->schmeissereienPlacementAfterRounds(m_dokogame,m_dokogame->rounds().size())) +
//                       ".|"+ QString::number(m_dokogame->schmeissereiCount()*100/m_dokogame->rounds().size())+ "%)");
//    }

//    if (m_dokogame->mitSchweinerei()){
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(19)->layout())->itemAt(0)->widget());
//        label->setText(QString::number(m_dokogame->schweinereiCount()));
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(19)->layout())->itemAt(2)->widget());
//        label->setText(" (" + QString::number(Handler::getInstance()->stats()->dokoStats()->schweinereienPlacementAfterRounds(m_dokogame,m_dokogame->rounds().size())) +
//                       ".|"+ QString::number(m_dokogame->schweinereiCount()*100/m_dokogame->rounds().size())+ "%)");
//    }
//    if (m_dokogame->mitPflichtsolo()){
//        label = static_cast<QLabel*>(static_cast<QHBoxLayout*>(m_layout->itemAt(13)->layout())->itemAt(0)->widget());
//        label->setText(QString::number(m_dokogame->pflichtSoloCount())+"/"+QString::number(m_dokogame->playersSortedByPosition().size()));
//    }
}
