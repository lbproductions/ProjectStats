#include "dokolivegamedetailswidget.h"

#include "dokolivegameplayerstatswidget.h"
#include "dokolivegameinfogroupbox.h"
#include "dokolivegameroundtable.h"

#include <Database/Doppelkopf/dokolivegame.h>
#include <Gui/Details/LiveGameDetails/Doppelkopf/schmeissereiwidget.h>
#include <Gui/Details/LiveGameDetails/Doppelkopf/dokolivegameinfogroupbox.h>
#include <Gui/Details/LiveGameDetails/Doppelkopf/dokolivegameplayerstatswidget.h>
#include <Gui/Details/LiveGameDetails/Doppelkopf/dokolivegameroundtable.h>
#include <Gui/Details/LiveGameDetails/Doppelkopf/newdokoroundwidget.h>
#include <Gui/Graphs/dokolivegamegraphview.h>

#include <QFile>
#include <QLabel>
#include <QSettings>
#include <QDebug>


using namespace Gui::Details;

DokoLiveGameDetailsWidget::DokoLiveGameDetailsWidget(Database::DokoLiveGame *game, QWidget *parent) :
    LiveGameDetailsWidget(game,parent),
    m_dokolivegame(game)
{
    initializeItems();
    setupWidget();

    setFullscreenMode();
}

DokoLiveGameDetailsWidget::~DokoLiveGameDetailsWidget()
{

}

void DokoLiveGameDetailsWidget::initializeItems(){
    qDebug() << "Loading DokoLiveGamePlayerStatsWidget...";
    m_statswidget = new LiveGameDetails::DokoLiveGameDetails::DokoLiveGamePlayerStatsWidget(m_dokolivegame,this);
    qDebug() << "Loading DokoLiveGameInfoGroupBox...";
    m_infoBox = new LiveGameDetails::DokoLiveGameDetails::DokoLiveGameInfoGroupBox(m_dokolivegame,this);
    qDebug() << "Loading DokoLiveGameRoundTable...";
    m_roundTable = new LiveGameDetails::DokoLiveGameDetails::DokoLiveGameRoundTable(m_dokolivegame,this);
    if(m_graph.isNull())
    {
        m_graph = new Gui::Graphs::DokoLiveGameGraphView(this);
        m_graph->setLiveGame(m_livegame);
    }
    else
    {
        m_graph->setLiveGame(m_livegame);
    }
    LiveGameDetailsWidget::initializeItems();
}

void DokoLiveGameDetailsWidget::setupWidget(){

    LiveGameDetailsWidget::setupWidget();

    m_splitter->addWidget(m_statswidget);
}

void DokoLiveGameDetailsWidget::resizeEvent(QResizeEvent *)
{
        LiveGameDetailsWidget::resizeEvent(0);

        m_statswidget->updateWidget();
}

void DokoLiveGameDetailsWidget::onRoundCreated(){
    LiveGameDetailsWidget::onRoundCreated();
}

void DokoLiveGameDetailsWidget::fillWidget(){
    if (m_dokolivegame->isFinished->value()){
        m_statswidget->updateWidget();
    }    
    LiveGameDetailsWidget::fillWidget();
}

void DokoLiveGameDetailsWidget::showSchmeissereiWidget(){
    m_schmeissereiWidget = new LiveGameDetails::DokoLiveGameDetails::SchmeissereiWidget(m_dokolivegame,this);

    if (m_fullscreen){
        QFile newround(":/stylesheets/livegame/newroundwidget_fullscreen");
        newround.open(QFile::ReadOnly);
        m_schmeissereiWidget->setStyleSheet(newround.readAll());
        newround.close();
    }

    m_newItemLayout->addWidget(m_schmeissereiWidget);

    connect(m_schmeissereiWidget,SIGNAL(schmeissereiAdded()),this,SIGNAL(schmeissereiAdded()));

    this->repaint();
}

void DokoLiveGameDetailsWidget::showRoundWidget(){
    m_dokoRoundWidget = new LiveGameDetails::DokoLiveGameDetails::NewDokoRoundWidget(m_dokolivegame,this);

    if (m_fullscreen){
        QFile newround(":/stylesheets/livegame/newroundwidget_fullscreen");
        newround.open(QFile::ReadOnly);
        m_dokoRoundWidget->setStyleSheet(newround.readAll());
        newround.close();
    }

    m_newItemLayout->addWidget(m_dokoRoundWidget);

    connect(m_dokoRoundWidget,SIGNAL(roundCreated()),this,SLOT(onRoundCreated()));

    this->repaint();
}

void DokoLiveGameDetailsWidget::onSchmeissereiAdded(){
    QVBoxLayout* layout = static_cast<QVBoxLayout*>(m_infoBox->layout());

    if (m_dokolivegame->doko_mitSchmeisserei->value()){
        QLabel* label = static_cast<QLabel*>(layout->itemAt(15)->widget());
        label->setText(QString::number(m_dokolivegame->doko_schmeissereiCount->value()));
    }

    emit schmeissereiAdded();
}

void DokoLiveGameDetailsWidget::onSettingsChanged(){
   LiveGameDetailsWidget::onSettingsChanged();
   if (m_settingsWidget != 0){
       m_statswidget->setVisible(m_settingsWidget->statePlayerStats());

       QSettings settings;
       settings.setValue("LiveGameWidget/statePlayerStats", QVariant(m_settingsWidget->statePlayerStats()));
    }
   else{
       QSettings settings;
       if(settings.value("LiveGameWidget/statePlayerStats") != QVariant()){
            m_statswidget->setVisible(settings.value("LiveGameWidget/statePlayerStats").toBool());
       }
   }


}
