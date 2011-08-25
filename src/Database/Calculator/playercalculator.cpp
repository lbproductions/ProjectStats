#include "playercalculator.h"

#include <Database/game.h>
#include <Database/player.h>
#include <Database/place.h>
#include <Database/drink.h>
#include <Database/livegamedrink.h>
#include <Database/livegame.h>
#include <Misc/handler.h>

#include <Gui/Details/PlayerDetails/abstractplayerstatswidget.h>
#include <Gui/MainWindow/mainwindow.h>

#include <QDebug>
#include <QDateTime>

namespace Database {

PlayerCalculator::PlayerCalculator(QPointer<Player> player,QObject *parent):
    QObject(parent),
    m_player(player)
{
}

QList<Game*> PlayerCalculator::calculate_games(){
    QList<Game*> list;
    foreach(Game* g, Games::instance()->allRows()){
	if(g->players->value().contains(m_player)){
	    list.append(g);
	}
    }

    return list;
}

QMap<QString,int> PlayerCalculator::calculate_gameCount(){
    QMap<QString,int> hash;
    foreach(Game* g,m_player->games->value()){
        hash.insert("General",hash.value("General")+1);
        hash.insert(g->type->value(),hash.value(g->type->value())+1);
        if(g->live->value()){
            hash.insert("Live",hash.value("Live")+1);
        }
    }
    return hash;
}

QList<Place*> PlayerCalculator::calculate_places(){
    QList<Place*> list;
    foreach(Place* p, Places::instance()->allRows()){
	if(p->player->value() == m_player){
	    list.append(p);
	}
    }
    return list;
}

QMap<QString,int> PlayerCalculator::calculate_points(){
    QMap<QString,int> hash;
    QList<Game*> list = m_player->games->value();
    for(int i = 0; i<list.size();i++){
        Game* g = list.at(i);
        double zaehler = (double)(g->players->value().size() - g->placement->value(m_player));
        double nenner = (double)g->players->value().size()-1;
        hash.insert("General",hash.value("General") + (int)(100* (zaehler / nenner)));
        hash.insert(g->type->value(),hash.value(g->type->value()) + (int)(100* (zaehler / nenner)));
        if(g->live->value()){
            hash.insert("Live",hash.value("Live") + (int)(100* (zaehler / nenner)));
        }
    }
    return hash;
}

QMap<QString,double> PlayerCalculator::calculate_average(){
    QMap<QString,double> hash;
    foreach(QString type, Games::instance()->types->value()){
        if(m_player->gameCount->value(type) != 0){
            hash.insert(type,(double)m_player->points->value(type) / (double)m_player->gameCount->value(type));
        }
        else{
            hash.insert(type,0);
        }
    }
    double gameCount = m_player->gameCount->value("General");
    if(gameCount > 0){
        double points = m_player->points->value("General");

        hash.insert("General",points / gameCount);
    }

    if(m_player->gameCount->value("Live") > 0){
        hash.insert("Live",(double)m_player->points->value("Live")/(double)m_player->gameCount->value("Live"));
    }
    return hash;
}

QMap<QString,int> PlayerCalculator::calculate_wins(){
    QMap<QString,int> hash;
    for(int i = 0; i<m_player->games->value().size();i++){
        if(m_player->games->value(i)->placement->value(m_player) == 1){
            hash.insert("General",hash.value("General")+1);
            hash.insert(m_player->games->value(i)->type->value(),hash.value(m_player->games->value(i)->type->value())+1);
        }
    }
    return hash;
}

QMap<QString,int> PlayerCalculator::calculate_losses(){
    QMap<QString,int> hash;
    for(int i = 0; i<m_player->games->value().size();i++){
        if(m_player->games->value(i)->placement->value(m_player) == m_player->games->value(i)->players->value().size()){
            hash.insert("General",hash.value("General")+1);
            hash.insert(m_player->games->value(i)->type->value(),hash.value(m_player->games->value(i)->type->value())+1);
        }
    }
    return hash;
}

QMap<QString,QDateTime> PlayerCalculator::calculate_lastGame(){
    QMap<QString,QDateTime> hash;
    for(int i = 0; i<m_player->games->value().size();i++){
        foreach(QString type, Games::instance()->types->value()){
            if(m_player->games->value(i)->type->value() == type && m_player->games->value(i)->date->value() > hash.value(type)){
                hash.insert(type,m_player->games->value(i)->date->value());
            }
            if(m_player->games->value(i)->date->value() > hash.value("General")){
                hash.insert("General",m_player->games->value(i)->date->value());
            }
        }

    }
    return hash;
}

QMap<QString,QDateTime> PlayerCalculator::calculate_lastWin(){
    QMap<QString,QDateTime> hash;
    for(int i = 0; i<m_player->games->value().size();i++){
        foreach(QString type, Games::instance()->types->value()){
            if(m_player->games->value(i)->type->value() == type && m_player->games->value(i)->date->value() > hash.value(type) && m_player->games->value(i)->placement->value(m_player) == 1){
                hash.insert(type,m_player->games->value(i)->date->value());
            }
            if(m_player->games->value(i)->date->value() > hash.value("General") && m_player->games->value(i)->placement->value(m_player) == 1){
                hash.insert("General",m_player->games->value(i)->date->value());
            }
        }

    }
    return hash;
}

QMap<LiveGame*,double> PlayerCalculator::calculate_alcPegel(){
    QMap<LiveGame*,double> hash;

    /* Widmark-Formel für Pegel:
        c (in Promille) = A / (r*G)
        c: Blutalkoholgehalt in Promille
        A: aufgenommener Alkohol in Gramm
        r: Verteilungsfaktor im Körper (0,7 für Männer / 0,6 für Frauen)
            Nach Seidel auch:
            Rm = 0,31233 − 0,006446 · Körpergewicht + 0,004466 · Körperlänge
            Rw = 0,31608 − 0,004821 · Körpergewicht + 0,004432 · Körperlänge
        G: Körpergewicht in Kilogramm

        A = Menge des Getränks in cl  * Alc-Gehalt in % * 0,08

        außerdem zu berücksichtigen: Alkoholabbau von 0,1 pro Stunde bei keiner Alkoholaufnahme
        (der allerdings erst nach beendeter Diffusion beginnt, wenn ich das recht verstehe)

        http://de.wikipedia.org/wiki/Blutalkoholkonzentration#Berechnung_der_BAK
    */
    foreach(Game* g, m_player->games->value())
    {

        if(g->live->value())
        {
            double A = 0.0;
            LiveGame* game = static_cast<LiveGame*>(g);
            foreach(LiveGameDrink* lgdrink, game->drinksPerPlayer->value(m_player))
            {
                Drink* drink = lgdrink->drink->value();
                A += drink->size->value()*100 /*in cl umrechnen*/
                     * drink->alc->value() *0.08;
            }

            double r = 0.0;

            if(m_player->gender->value() == "male")
            {
                r = 0.31233 - 0.006446 * m_player->weight->value() + 0.004466 * m_player->size->value();
            }
            else if(m_player->gender->value() == "female")
            {
                r = 0.31608 - 0.004821 * m_player->weight->value() + 0.004432 * m_player->size->value();
            }

            if (m_player->weight->value() > 0 && r != 0.0)
            {
                hash.insert(game, A / (double)(r*m_player->weight->value()));
            }
            else
            {
                hash.insert(game,0.0);
            }
        }
    }

    return hash;
}

QMap<QString,double> PlayerCalculator::calculate_averagePlacement(){
    QMap<QString,double> hash;
    int livegamecount = 0;
    for(int i = 0; i<m_player->games->value().size();i++){
        if(m_player->games->value(i)->live->value()){
            livegamecount++;
            LiveGame* game = static_cast<LiveGame*>(m_player->games->value(i));
            hash.insert("General",(hash.value("General")*(livegamecount-1)+game->averagePlacement->value(m_player))/(double)(livegamecount));
            hash.insert(m_player->games->value(i)->type->value(),(hash.value(m_player->games->value(i)->type->value())*(livegamecount-1)+game->averagePlacement->value(m_player))/(double)(livegamecount));
        }
    }
    return hash;
}

QMap<QString,int> PlayerCalculator::calculate_offlineGameCount(){
    QMap<QString,int> hash;
    foreach(Game* g, m_player->games->value()){
        if(!g->live->value()){
            hash.insert("General",hash.value("General")+1);
            hash.insert(g->type->value(),hash.value(g->type->value())+1);
        }
    }
    return hash;
}

QMap<QString,int> PlayerCalculator::calculate_liveGameCount(){
    QMap<QString,int> hash;
    foreach(Game* g, m_player->games->value()){
        if(g->live->value()){
            hash.insert("General",hash.value("General")+1);
            hash.insert(g->type->value(),hash.value(g->type->value())+1);
        }
    }
    return hash;
}

QMap<QString,int> PlayerCalculator::calculate_gamePoints(){
    QMap<QString,int> hash;
    foreach(QString type, Games::instance()->types->value()){
        hash.insert(type,m_player->liveGamePoints->value(type)+m_player->offlineGamePoints->value(type));
    }
    return hash;
}

QMap<QString,int> PlayerCalculator::calculate_liveGamePoints(){
    QMap<QString,int> hash;
    foreach(Game* g, m_player->games->value()){
        if(g->live->value()){
            hash.insert(g->type->value(),hash.value(g->type->value())+g->points->value(m_player));
        }
    }
    return hash;
}

QMap<QString,int> PlayerCalculator::calculate_offlineGamePoints(){
    QMap<QString,int> hash;
    foreach(Game* g, m_player->games->value()){
        if(!g->live->value()){
            hash.insert(g->type->value(),hash.value(g->type->value())+g->points->value(m_player));
        }
    }
    return hash;
}

} // namespace Database
