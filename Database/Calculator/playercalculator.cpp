#include "playercalculator.h"

#include <Database/game.h>
#include <Database/player.h>
#include <Database/place.h>
#include <Database/drink.h>
#include <Database/livegamedrink.h>
#include <Database/livegame.h>
#include <handler.h>

#include <Database/attributelist.h>

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

AttributeList<Game*> PlayerCalculator::calculate_games(){
    AttributeList<Game*> list;
    foreach(Game* g, Games::instance()->allRows()){
	if(g->players->value().contains(m_player)){
	    list.append(g);
	}
    }

    return list;
}

AttributeHash<QString,int> PlayerCalculator::calculate_gameCount(){
    AttributeHash<QString,int> hash;
    foreach(Game* g,m_player->games->value()){
        hash.insert("General",hash.value("General")+1);
        hash.insert(g->type->value(),hash.value(g->type->value())+1);
    }
    return hash;
}

AttributeList<Place*> PlayerCalculator::calculate_places(){
    AttributeList<Place*> list;
    foreach(Place* p, Places::instance()->allRows()){
	if(p->player->value() == m_player){
	    list.append(p);
	}
    }
    return list;
}

AttributeHash<QString,int> PlayerCalculator::calculate_points(){
    AttributeHash<QString,int> hash;
    AttributeList<Game*> list = m_player->games->value();
    for(int i = 0; i<list.size();i++){
        Game* g = list.at(i);
        double zaehler = (double)(g->players->value().size() - g->placement->value(m_player));
        double nenner = (double)g->players->value().size()-1;
        hash.insert("General",hash.value("General") + (int)(100* (zaehler / nenner)));
        hash.insert(g->type->value(),hash.value(g->type->value()) + (int)(100* (zaehler / nenner)));
    }
    return hash;
}

AttributeHash<QString,double> PlayerCalculator::calculate_average(){
    AttributeHash<QString,double> hash;
    foreach(QString type, Games::instance()->types->value()){
        if(m_player->gameCount->value(type) != 0){
            hash.insert(type,(double)m_player->points->value(type) / (double)m_player->gameCount->value(type));
        }
        else{
            hash.insert(type,0);
        }
    }
    if(m_player->gameCount->value("General") > 0){
        hash.insert("General",(double)m_player->points->value("General") / (double)m_player->gameCount->value("General"));
    }
    return hash;
}

AttributeHash<QString,int> PlayerCalculator::calculate_wins(){
    AttributeHash<QString,int> hash;
    for(int i = 0; i<m_player->games->value().size();i++){
        if(m_player->games->value(i)->placement->value(m_player) == 1){
            hash.insert("General",hash.value("General")+1);
            hash.insert(m_player->games->value(i)->type->value(),hash.value(m_player->games->value(i)->type->value())+1);
        }
    }
    return hash;
}

AttributeHash<QString,int> PlayerCalculator::calculate_losses(){
    AttributeHash<QString,int> hash;
    for(int i = 0; i<m_player->games->value().size();i++){
        if(m_player->games->value(i)->placement->value(m_player) == m_player->games->value(i)->players->value().size()){
            hash.insert("General",hash.value("General")+1);
            hash.insert(m_player->games->value(i)->type->value(),hash.value(m_player->games->value(i)->type->value())+1);
        }
    }
    return hash;
}

AttributeHash<QString,QDateTime> PlayerCalculator::calculate_lastGame(){
    AttributeHash<QString,QDateTime> hash;
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

AttributeHash<QString,QDateTime> PlayerCalculator::calculate_lastWin(){
    AttributeHash<QString,QDateTime> hash;
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

AttributeHash<LiveGame*,double> PlayerCalculator::calculate_alcPegel(){
    AttributeHash<LiveGame*,double> hash;

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
    for(int i = 0; i<m_player->games->value().size();i++){

        double A = 0.0;

        if(m_player->games->value(i)->live->value()){
            LiveGame* game = static_cast<LiveGame*>(m_player->games->value(i));
            for(int j = 0; j<game->drinks->value().size();j++){
                {
                    Drink* drink = Drinks::instance()->rowById(game->drinks->value(j)->drinkId->value());
                    if(drink != 0)
                    {
                        A += drink->size->value()*100 /*in cl umrechnen*/
                                * drink->alc->value() *0.08;
                    }
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
                else
                {
                    hash.insert(game,0.0);
                }
                if (m_player->weight->value() > 0){
                    hash.insert(game,A / (double)(r*m_player->weight->value()));
                }
                else{
                    hash.insert(game,0.0);
                }
            }
        }

    }

    return hash;
}

} // namespace Database
