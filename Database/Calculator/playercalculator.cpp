#include "playercalculator.h"

#include <Database/game.h>
#include <Database/player.h>
#include <Database/place.h>
#include <Database/drink.h>
#include <Database/livegame.h>

#include <Database/attributelist.h>

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

AttributeList<Place*> PlayerCalculator::calculate_places(){
    AttributeList<Place*> list;
    foreach(Place* p, Places::instance()->allRows()){
	if(p->player->value() == m_player){
	    list.append(p);
	}
    }
    return list;
}

int PlayerCalculator::calculate_points(){
    int points = 0;
    AttributeList<Game*> list = m_player->games->value();
    for(int i = 0; i<list.size();i++){
        Game* g = list.at(i);
        double zaehler = (double)(g->players->value().size() - g->placement->value(m_player));
        double nenner = (double)g->players->value().size()-1;
	points = points + 100* (zaehler / nenner);
    }
    return points;
}

double PlayerCalculator::calculate_average(){
    if(m_player->games->value().size() > 0){
        return (double)m_player->points->value() / (double)m_player->games->value().size();
    }
    else{
        return 0.0;
    }
}

int PlayerCalculator::calculate_wins(){
    int count = 0;
    for(int i = 0; i<m_player->games->value().size();i++){
        if(m_player->games->value(i)->placement->value(m_player) == 1){
            count++;
        }
    }
    return count;
}

int PlayerCalculator::calculate_losses(){
    int count = 0;
    for(int i = 0; i<m_player->games->value().size();i++){
        if(m_player->games->value(i)->placement->value(m_player) == m_player->games->value(i)->players->value().size()){
            count++;
        }
    }
    return count;
}

QDateTime PlayerCalculator::calculate_lastGame(){
    QDateTime time(QDate(1960,1,1));
    for(int i = 0; i<m_player->games->value().size();i++){
        if(m_player->games->value(i)->date->value() > time){
            time = m_player->games->value(i)->date->value();
        }
    }
    return time;
}

QDateTime PlayerCalculator::calculate_lastWin(){
    QDateTime time(QDate(1960,1,1));
    for(int i = 0; i<m_player->games->value().size();i++){
        if(m_player->games->value(i)->date->value() > time && m_player->games->value(i)->placement->value(m_player) == 1){
            time = m_player->games->value(i)->date->value();
        }
    }
    return time;
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
                    if(game->drinks->value(j) != 0)
                    {
                        A += game->drinks->value(j)->size->value()*100 /*in cl umrechnen*/
                                * game->drinks->value(j)->alc->value() *0.08;
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
