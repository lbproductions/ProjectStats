#include "livegamedetailswidget.h"

#include <Database/livegame.h>
#include <Database/player.h>
#include <Gui/Misc/splitter.h>

#include <global.h>
#include <messagesystem.h>
#include <handler.h>

#include <QFile>
#include <QSettings>
#include <QLabel>
#include <QDebug>



using namespace Gui::Details::LiveGameDetails;

LiveGameDetailsWidget::LiveGameDetailsWidget(Database::LiveGame* livegame, QWidget* widget):
    DetailsWidget(livegame,widget),
    m_livegame(livegame),
    m_playerTotalPointsTable(0)
{

}

void LiveGameDetailsWidget::initializeItems(){

    m_layout = new QVBoxLayout();
    m_newItemLayout = new QVBoxLayout();
    m_centerLayout = new QHBoxLayout();

    m_splitter = new QSplitter(Qt::Vertical,this);
    qDebug() << "Loading BeerWidget...";
    m_beerwidget = new BeerWidget(m_livegame,this);
    if (m_roundTable.isNull()){
        qDebug() << "Loading LiveGameRoundTable...";
        m_roundTable = new LiveGameDetails::LiveGameRoundTable(m_livegame,this);
    }
    if (m_infoBox.isNull()){
        qDebug() << "Loading LiveGameInfoGroupBox...";
        m_infoBox = new LiveGameDetails::LiveGameInfoGroupBox(m_livegame,this);
    }
    qDebug() << "Loading PlayerTotalPointsTable...";
    m_playerTotalPointsTable = new QTableWidget(1,m_livegame->playersSortedByPosition->value().size()+1,m_splitter);

    if(m_graph.isNull())
    {
        m_graph = new Gui::Graphs::LiveGameGraphView(this);
        m_graph->setLiveGame(m_livegame);
    }

    timeGame.start();
    lengthPause = 0;

    m_gamecomment = new QTextEdit(this);
    m_gamecomment->setVisible(m_livegame->isFinished->value());

    m_playerlist = m_livegame->playersSortedByPosition->value();
}

void LiveGameDetailsWidget::setupWidget(){

    m_splitter->addWidget(m_roundTable);
    m_splitter->addWidget(m_playerTotalPointsTable);
    m_splitter->addWidget(m_graph);
    m_splitter->addWidget(m_gamecomment);

    QWidget *centerWidget = new QWidget;
    QLayout *centerLayout = new QHBoxLayout;
    centerLayout->addWidget(m_splitter);
    centerWidget->setLayout(centerLayout);

    Gui::Misc::Splitter* splitter = new Gui::Misc::Splitter(Qt::Horizontal);
    splitter->setFullscreen(true);
    splitter->setLeftToRight(true);
    splitter->addWidget(m_beerwidget);
    splitter->addWidget(centerWidget);

    Gui::Misc::Splitter* splitter2 = new Gui::Misc::Splitter(Qt::Horizontal);
    splitter2->setFullscreen(true);
    splitter2->addWidget(splitter);
    splitter2->addWidget(m_infoBox);

    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);

    m_layout->addWidget(splitter2);

    m_playerTotalPointsTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    for (int i = 0; i<m_playerTotalPointsTable->columnCount();i++){

         m_playerTotalPointsTable->setColumnWidth(i, ((double)m_roundTable->columnWidth(0)));

         QTableWidgetItem* item = new QTableWidgetItem("");
         item->setSizeHint(QSize(0,0));
         m_playerTotalPointsTable->setHorizontalHeaderItem(i,item);
    }
    m_playerTotalPointsTable->setRowHeight(0,50);
    m_playerTotalPointsTable->setMaximumHeight(m_playerTotalPointsTable->rowHeight(0));
    QTableWidgetItem* item = new QTableWidgetItem("0");
    item->setSizeHint(QSize(0,0));
    m_playerTotalPointsTable->setVerticalHeaderItem(0,item);

    m_roundTable->markCardMixer(m_fullscreen);

    this->setLayout(m_layout);

//    Handler::getInstance()->messageSystem()->checkForStats(m_livegame);

    resumeGame();
}

void LiveGameDetailsWidget::fillWidget(){

    QList<Database::Round*> roundlist = m_livegame->rounds->value();
    for(int i = 0; i<roundlist.size()-1;i++){
        m_roundTable->addRound(roundlist.at(i));
    }

    gameLength = m_livegame->length->value();

    for (int i = 0; i < m_playerlist.size(); i++){
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(m_livegame->points->value(m_playerlist.at(i))));
        item->setTextAlignment(Qt::AlignCenter);
        item->setFont(QFont("Lucia Grande",30,QFont::Bold,false));
        m_playerTotalPointsTable->setItem(0,i,item);

        m_beerwidget->updateWidget();
    }

    QTableWidgetItem* item = new QTableWidgetItem(QString::number(m_livegame->totalPoints->value()));
    item->setTextAlignment(Qt::AlignCenter);
    item->setFont(QFont("Lucia Grande",30,QFont::Bold,false));
    m_playerTotalPointsTable->setItem(0,m_playerlist.size(),item);

    if (m_livegame->isFinished->value()){
        m_roundTable->updateSizes();
        //m_statswidget->updateWidget();
        emit finishedGameShown();
        m_roundTable->addRound(roundlist.at(roundlist.size()-1));

        m_infoBox->updateWidget((gameLength+QTime(timeGame.elapsed()/1000/60/60,timeGame.elapsed()/1000/60%60,timeGame.elapsed()/1000%60,0)).toString("hh:mm:ss"));
    }

    if (m_livegame->isFinished->value()){
        m_gamecomment->setText(m_livegame->comment->value());
    }

    onSettingsChanged();
}

void LiveGameDetailsWidget::pauseGame(){
    timePause.start();
    timer->stop();
}

void LiveGameDetailsWidget::resumeGame(){
    lengthPause = lengthPause + timePause.elapsed();

    timer = new QTimer();
    timer->setInterval(200);
    timer->setSingleShot(false);
    timer->start();

    connect(timer,SIGNAL(timeout()),this,SLOT(updateWidget()));
}

void LiveGameDetailsWidget::closeGame(){
    m_livegame->finishGame();
    //Handler::getInstance()->messageSystem()->checkForStats(m_livegame);
}

void LiveGameDetailsWidget::updateWidget(){

    if (!m_livegame->isFinished->value()){

        QVBoxLayout* layout = static_cast<QVBoxLayout*>(m_infoBox->layout());

        QLabel* label = static_cast<QLabel*>(layout->itemAt(3)->widget());
        label->setText((gameLength+QTime(timeGame.elapsed()/1000/60/60,timeGame.elapsed()/1000/60%60,timeGame.elapsed()/1000%60,0)).toString("hh:mm:ss"));

        for (int i = 0; i<m_playerTotalPointsTable->columnCount();i++){
             m_playerTotalPointsTable->setColumnWidth(i,(double)m_splitter->width()/m_playerTotalPointsTable->columnCount());
        }

   }

    resizeEvent(0);
}

void LiveGameDetailsWidget::resizeEvent(QResizeEvent *)
{
    if (!m_roundTable.isNull()){
        m_roundTable->updateSizes();
    }

    if (m_playerTotalPointsTable != 0 && m_playerTotalPointsTable->columnCount() != 0){
        for (int i = 0; i<m_playerTotalPointsTable->columnCount();i++){
             m_playerTotalPointsTable->setColumnWidth(i, m_roundTable->columnWidth(0));
        }
    }
}

void LiveGameDetailsWidget::onRoundCreated(){

    m_livegame->lastRound->value()->length->setValue(QTime((timeGame.elapsed()-lengthPause)/1000/60/60,(timeGame.elapsed()-lengthPause)/1000/60%60,(timeGame.elapsed()-lengthPause)/1000%60,0));
    gameLength = gameLength + m_livegame->lastRound->value()->length->value();

    timeGame.start();
    lengthPause = 0;

    m_roundTable->addRound(m_livegame->lastRound->value());
    m_roundTable->markCardMixer(m_fullscreen);

    for (int i = 0; i < m_playerlist.size(); i++){
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(m_livegame->points->value(m_playerlist.at(i))));
        item->setTextAlignment(Qt::AlignCenter);
        item->setFont(QFont("Lucia Grande",30,QFont::Bold,false));
        m_playerTotalPointsTable->setItem(0,i,item);
    }
    QTableWidgetItem* item = new QTableWidgetItem(QString::number(m_livegame->totalPoints->value()));
    item->setTextAlignment(Qt::AlignCenter);
    item->setFont(QFont("Lucia Grande",30,QFont::Bold,false));
    m_playerTotalPointsTable->setItem(0,m_playerlist.size(),item);

    m_roundTable->scrollToBottom();

    m_infoBox->updateWidget((gameLength+QTime(timeGame.elapsed()/1000/60/60,timeGame.elapsed()/1000/60%60,timeGame.elapsed()/1000%60,0)).toString("hh:mm:ss"));

    //Handler::getInstance()->messageSystem()->checkForStats(m_livegame);

    emit roundCreated();

    checkForEndOfGame();
}

void LiveGameDetailsWidget::showRoundWidget(){

}

void LiveGameDetailsWidget::showLiveGameSettingsWidget(){
    m_settingsWidget = new LiveGameDetails::LiveGameSettingsWidget(this);

    if (m_fullscreen){
        QFile newround(":/stylesheets/livegame/newroundwidget_fullscreen");
        newround.open(QFile::ReadOnly);
        m_settingsWidget->setStyleSheet(newround.readAll());
        newround.close();
    }

    m_newItemLayout->addWidget(m_settingsWidget);

    connect(m_settingsWidget,SIGNAL(settingsChanged()),this,SLOT(onSettingsChanged()));

    this->repaint();
}

void LiveGameDetailsWidget::hideHeadHorizontalWidget(){
    while (m_newItemLayout->count() > 0)
    {
        m_newItemLayout->itemAt(0)->widget()->setVisible(false);
        m_newItemLayout->removeItem(m_newItemLayout->itemAt(0));
    }
    this->repaint();
}

void LiveGameDetailsWidget::onDrinkDealed(){
    m_beerwidget->updateWidget();
    emit drinkDealed();
}

void LiveGameDetailsWidget::showAddDrinkWidget(){
    m_addDrinkWidget = new LiveGameDetails::AddDrinkWidget(m_livegame,this);

    if (m_fullscreen){
        QFile newround(":/stylesheets/livegame/newroundwidget_fullscreen");
        newround.open(QFile::ReadOnly);
        m_addDrinkWidget->setStyleSheet(newround.readAll());
        newround.close();
    }

    m_newItemLayout->addWidget(m_addDrinkWidget);

    connect(m_addDrinkWidget,SIGNAL(drinkDealed()),this,SLOT(onDrinkDealed()));

    this->repaint();
}

QPointer<BeerWidget> LiveGameDetailsWidget::beerwidget(){
    return m_beerwidget;
}

void LiveGameDetailsWidget::setFullscreenMode(){

    this->setAutoFillBackground(true);
    this->setBackgroundRole(QPalette::Background);
    QPalette p(this->palette());
    p.setColor(QPalette::Background, QColor(51,51,51));
    this->setPalette(p);

    /*

    QString path;
    qDebug() << "Resolution:" + QString::number(Handler::getInstance()->getDesktopWidth()) + "x" + QString::number(Handler::getInstance()->getDesktopHeight());
    if (Handler::getInstance()->getDesktopWidth() == 1280 && Handler::getInstance()->getDesktopHeight() == 800){
        path = ":/stylesheets/livegame/livegame_fullscreen_1280x800";
    }
    else{
        path = ":/stylesheets/livegame/livegame_fullscreen";
    }
    QFile normal(path);
    normal.open(QFile::ReadOnly);
    this->setStyleSheet(normal.readAll());
    normal.close();

    QFile graph(":/stylesheets/livegame/graph_fullscreen");
    graph.open(QFile::ReadOnly);
    m_graph->setStyleSheet(graph.readAll());
    graph.close();

    QFile table(":/stylesheets/livegame/roundtable_fullscreen");
    table.open(QFile::ReadOnly);
    m_roundTable->setStyleSheet(table.readAll());
    table.close();

    /*
    QFile beerwidget(":/stylesheets/livegame/beerwidget_fullscreen");
    beerwidget.open(QFile::ReadOnly);
    m_beerwidget->setStyleSheet(beerwidget.readAll());
    beerwidget.close();
    */

    //this->setStyleSheet("Gui--Details--LiveGameDetails--LiveGameDetailsWidget{background-color: black;}QSplitter::handle{height: 10px; background-color: transparent; border: 0px solid #6c6c6c;}");
    this->setStyleSheet("");

    m_roundTable->setFullscreen();

    m_beerwidget->updateWidget();
    m_beerwidget->setFullscreen();

    m_infoBox->setFullscreen();

    m_fullscreen = true;
    m_roundTable->markCardMixer(m_fullscreen);

    m_graph->setFullscreen();

    m_playerTotalPointsTable->setStyleSheet("QWidget{background-color:black; color: white; border-radius: 10px;}");

    this->repaint();
}

void LiveGameDetailsWidget::setNormalMode(){
    this->setAutoFillBackground(false);
    this->setBackgroundRole(QPalette::Background);
    QPalette p(this->palette());
    p.setColor(QPalette::Background, Qt::white);
    this->setPalette(p);


    //QFile normal(":/stylesheet/livegame/livegame_normal");
    QFile normal("");
    normal.open(QFile::ReadOnly);
    this->setStyleSheet(normal.readAll());
    normal.close();

    m_graph->setStyleSheet("");
    m_roundTable->setNormalMode();

    /*
    //QFile beerwidget(":/stylesheets/livegame/beerwidget_normal");
    QFile beerwidget("");
    beerwidget.open(QFile::ReadOnly);
    m_beerwidget->setStyleSheet(beerwidget.readAll());
    beerwidget.close();
    */

    m_beerwidget->setNormalMode();

    QFile graph("");
    graph.open(QFile::ReadOnly);
    m_graph->setStyleSheet(graph.readAll());
    graph.close();

    QFile table("");
    table.open(QFile::ReadOnly);
    m_roundTable->setStyleSheet(table.readAll());
    table.close();

    m_fullscreen = false;
    m_roundTable->markCardMixer(m_fullscreen);

    m_infoBox->setNormalMode();

    this->repaint();
}

bool LiveGameDetailsWidget::isFullscreen(){
    return m_fullscreen;
}

void LiveGameDetailsWidget::onSettingsChanged(){
   if (m_settingsWidget != 0){
       m_beerwidget->setVisible(m_settingsWidget->stateBeerWidget());
       m_graph->setVisible(m_settingsWidget->stateGraph());
       m_roundTable->setVisible(m_settingsWidget->stateRoundsTable());
       m_playerTotalPointsTable->setVisible(m_settingsWidget->stateTotalPoints());
       m_infoBox->setVisible(m_settingsWidget->stateInfoBox());
       m_gamecomment->setVisible(m_settingsWidget->stateComment());

       QSettings settings;
       settings.setValue("LiveGameWidget/stateBeerWidget", QVariant(m_settingsWidget->stateBeerWidget()));
       settings.setValue("LiveGameWidget/stateGraph", QVariant(m_settingsWidget->stateGraph()));
       settings.setValue("LiveGameWidget/stateRoundsTable", QVariant(m_settingsWidget->stateRoundsTable()));
       settings.setValue("LiveGameWidget/stateTotalPoints", QVariant(m_settingsWidget->stateTotalPoints()));
       settings.setValue("LiveGameWidget/stateInfoBox", QVariant(m_settingsWidget->stateInfoBox()));
       settings.setValue("LiveGameWidget/stateComment", QVariant(m_settingsWidget->stateComment()));
    }
   else{
       QSettings settings;
       if (settings.value("LiveGameWidget/stateBeerWidget") != QVariant()){
            m_beerwidget->setVisible(settings.value("LiveGameWidget/stateBeerWidget").toBool());
       }
       if (settings.value("LiveGameWidget/stateGraph") != QVariant()){
            m_graph->setVisible(settings.value("LiveGameWidget/stateGraph").toBool());
       }
       if (settings.value("LiveGameWidget/stateRoundsTable") != QVariant()){
            m_roundTable->setVisible(settings.value("LiveGameWidget/stateRoundsTable").toBool());
       }
       if(settings.value("LiveGameWidget/stateTotalPoints") != QVariant()){
            m_playerTotalPointsTable->setVisible(settings.value("LiveGameWidget/stateTotalPoints").toBool());
       }
       if(settings.value("LiveGameWidget/stateInfoBox") != QVariant()){
            m_infoBox->setVisible(settings.value("LiveGameWidget/stateInfoBox").toBool());
       }
       if(settings.value("LiveGameWidget/stateComment") != QVariant()){
            if (m_livegame->isFinished->value()){
                m_gamecomment->setVisible(settings.value("LiveGameWidget/stateComment").toBool());
            }
       }
   }
}

void LiveGameDetailsWidget::checkForEndOfGame(){

}

