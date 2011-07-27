#include "attributevariant.h"

#include <Database/attributehash.h>
#include <Database/attributelist.h>
#include <Database/place.h>
#include <Database/player.h>
#include <Database/livegame.h>
#include <Database/drink.h>
#include <Database/round.h>
#include <Database/Doppelkopf/schmeisserei.h>

#include <QDateTime>
#include <QObject>

AttributeVariant::AttributeVariant() :
    QVariant()
{
}

void AttributeVariant::setDisplayRole(DisplayRole role){
    m_currentRole = role;
}

QVariant AttributeVariant::displayVariant(){
    QVariant variant;

    if(this->type() == QVariant::Double)
    {
        variant.setValue(QString("%L1").arg(this->toDouble(),0,'f',2));
    }
    else if(QString(this->typeName()) == "QPointer<Database::Player>"){
        QPointer<Database::Player> player = this->value<QPointer<Database::Player> >();
        if (!player.isNull()){
            variant.setValue(player->name->value());
        }
    }
    /*
    else if(QString(this->typeName()) == "QDateTime"){
        QDateTime time = this->value<QDateTime>();
        if(time.time().hour() == 0 && time.time().minute() == 0 && time.time().second() == 0){
            variant.setValue(time.toString("dd.MM.yyyy"));
        }
        else if (time.date().year() != 1960){
            variant.setValue(time.toString("dd.MM.yyyy hh:mm"));
        }
        else{
            variant.setValue(QString("Never"));
        }
    }
    */
    else if(QString(this->typeName()) == "QPointer<Database::Place>"){
        QPointer<Database::Place> place = this->value<QPointer<Database::Place> >();
        if (!place.isNull()){
            variant.setValue(place->displayString->value());
        }
    }

    else if(QString(this->typeName()) == "QPointer<Database::Game>"){
        QPointer<Database::Game> game = this->value<QPointer<Database::Game> >();
        if (!game.isNull()){
            variant.setValue(game->name->value());
        }
    }

    else if(QString(this->typeName()) == "Database::Round*"){
        Database::Round* round = this->value<Database::Round*>();
        if (round != 0){
            variant.setValue(round->id());
        }
    }

    else if(QString(this->typeName()) == "Database::Player*"){
        Database::Player* player = this->value<Database::Player*>();
        if (player != 0){
            variant.setValue(player->name->value());
        }
    }

    else if(QString(this->typeName()) == "Database::Round::RoundState"){
        Database::Round::RoundState round = this->value<Database::Round::RoundState>();
        QPixmap pixmap;
        if(round == Database::Round::FinishedState){
            pixmap.load(":/graphics/icons/mac/gamewidget/gamestate_finished");
            variant.setValue(pixmap);
        }
        else if(round == Database::Round::RunningState){
            pixmap.load(":/graphics/icons/mac/gamewidget/gamestate_running");
            variant.setValue(pixmap);
        }
        else if(round == Database::Round::PausedState){
            pixmap.load(":/graphics/icons/mac/gamewidget/gamestate_paused");
            variant.setValue(pixmap);
        }
        else{
            pixmap.load(":/graphics/icons/mac/gamewidget/gamestate_default");
            variant.setValue(pixmap);
        }
    }

    else if(QString(this->typeName()) == "Database::AttributeList<Database::Place*>"){
        Database::AttributeList<Database::Place*> list = this->value<Database::AttributeList<Database::Place*> >();
        QString string = "";
        for (int i = 0; i<list.size();i++){
            string += list.at(i)->displayString->value();
            if (i < list.size()-1){
                string += "; ";
            }
        }
        variant.setValue(string);
    }

    else if(QString(this->typeName()) == "Database::AttributeList<Database::Drink*>"){
        Database::AttributeList<Database::Drink*> list = this->value<Database::AttributeList<Database::Drink*> >();
        QHash<Database::Drink*,int> hash;
        for(int i = 0; i<list.size();i++){
            hash.insert(list.at(i),hash.value(list.at(i)) + 1);
        }
        QString string = "";
        for(int i = 0; i<hash.keys().size();i++){
            string += hash.keys().at(i)->name->value() + " (" + QString::number(hash.value(hash.keys().at(i))) + ")";
            if (i < hash.keys().size()-1){
                string += "; ";
            }
        }
        variant.setValue(string);
    }

    else if(QString(this->typeName()) == "Database::AttributeList<Database::Game*>"){
        Database::AttributeList<Database::Game*> list = this->value<Database::AttributeList<Database::Game*> >();
        variant.setValue(list.size());
    }

    else if(QString(this->typeName()) == "Database::AttributeList<Database::Round*>"){
        Database::AttributeList<Database::Round*> list = this->value<Database::AttributeList<Database::Round*> >();
        variant.setValue(list.size());
    }

    else if(QString(this->typeName()) == "Database::AttributeList<Database::Player*>"){
        Database::AttributeList<Database::Player*> list = this->value<Database::AttributeList<Database::Player*> >();
        QString string = "";
        for (int i = 0; i<list.size();i++){
            string += list.at(i)->name->value();
            if (i < list.size()-1){
                string += ", ";
            }
        }
        variant.setValue(string);
    }

    else if(QString(this->typeName()) == "Database::AttributeList<Database::Schmeisserei*>"){
        Database::AttributeList<Database::Schmeisserei*> list = this->value<Database::AttributeList<Database::Schmeisserei*> >();
        QString string = "";
        for (int i = 0; i<list.size();i++){
            string += list.at(i)->player->value()->name->value();
            string += ":";
            string += list.at(i)->type->value();
            if (i < list.size()-1){
                string += ", ";
            }
        }
        variant.setValue(string);
    }

    else if(QString(this->typeName()) == "Database::AttributeHash<Database::Player*COMMA int>"){
        QString string = "";
        Database::AttributeHash<Database::Player*,int> hash = this->value<Database::AttributeHash<Database::Player*,int> >();
        foreach(Database::Player* p, hash.keys()){
            string += p->name->value() + ":" + QString::number(hash.value(p)) + ", ";
        }
        variant.setValue(string);
    }

    else if(QString(this->typeName()) == "Database::AttributeHash<Database::Player*COMMA double>"){
        QString string = "";
        Database::AttributeHash<Database::Player*,double> hash = this->value<Database::AttributeHash<Database::Player*,double> >();
        foreach(Database::Player* p, hash.keys()){
            string += p->name->value() + ":" + QString::number(hash.value(p)) + ", ";
        }
        variant.setValue(string);
    }

    else if(QString(this->typeName()) == "Database::AttributeHash<Database::Player*COMMA bool>"){
        QString string = "";
        Database::AttributeHash<Database::Player*,bool> hash = this->value<Database::AttributeHash<Database::Player*,bool> >();
        foreach(Database::Player* p, hash.keys()){
            if(hash.value(p)){
                string += p->name->value() + ":" + "true" + ", ";
            }
            else{
                string += p->name->value() + ":" + "false" + ", ";
            }
        }
        variant.setValue(string);
    }

    else if(QString(this->typeName()) == "Database::AttributeHash<Database::LiveGame*COMMA double>"){
        QString string = "";
        Database::AttributeHash<Database::LiveGame*,double> hash = this->value<Database::AttributeHash<Database::LiveGame*,double> >();
        foreach(Database::LiveGame* p, hash.keys()){
            string += p->name->value() + ":" + QString::number(hash.value(p)) + ", ";
        }
        variant.setValue(string);
    }
    else if(QString(this->typeName()) == "Database::AttributeHash<QString COMMA int>"){
        if(m_currentRole == MainWindow){
            Database::AttributeHash<QString,int> hash = this->value<Database::AttributeHash<QString,int> >();
            variant.setValue(hash.value("General"));
        }
        else{
            QString string = "";
            Database::AttributeHash<QString,int> hash = this->value<Database::AttributeHash<QString,int> >();
            foreach(QString i, hash.keys()){
                string += i + ":" + QString::number(hash.value(i)) + ", ";
            }
            variant.setValue(string);
        }

    }
    else if(QString(this->typeName()) == "Database::AttributeHash<QString COMMA double>"){
        if(m_currentRole == MainWindow){
            Database::AttributeHash<QString,double> hash = this->value<Database::AttributeHash<QString,double> >();
            variant.setValue(hash.value("General"));
        }
        else{
            QString string = "";
            Database::AttributeHash<QString,double> hash = this->value<Database::AttributeHash<QString,double> >();
            foreach(QString i, hash.keys()){
                string += i + ":" + QString::number(hash.value(i)) + ", ";
            }
            variant.setValue(string);
        }
    }
    else if(QString(this->typeName()) == "Database::AttributeHash<QString COMMA QDateTime>"){
        if(m_currentRole == MainWindow){
            Database::AttributeHash<QString,QDateTime> hash = this->value<Database::AttributeHash<QString,QDateTime> >();
            variant.setValue(hash.value("General"));
        }
        else{
            QString string = "";
            Database::AttributeHash<QString,QDateTime> hash = this->value<Database::AttributeHash<QString,QDateTime> >();
            foreach(QString i, hash.keys()){
                string += i + ":" + hash.value(i).toString("dd.MM.yyyy") + ", ";
            }
            variant.setValue(string);
        }
    }
    else if(QString(this->typeName()) == "Database::AttributeHash<int COMMA int>"){
        QString string = "";
        Database::AttributeHash<int,int> hash = this->value<Database::AttributeHash<int,int> >();
        foreach(int i, hash.keys()){
            string += QString::number(i) + ":" + QString::number(hash.value(i)) + ", ";
        }
        variant.setValue(string);
    }
    else if(QString(this->typeName()) == "Database::AttributeHash<QPair<Database::Player*COMMA Database::Player*>COMMA int>"){
        QString string = "";
        Database::AttributeHash<QPair<Database::Player*,Database::Player*>,int> hash = this->value<Database::AttributeHash<QPair<Database::Player*,Database::Player*>,int> >();
        for(int i = 0; i< hash.keys().size();i++){
            QPair<Database::Player*,Database::Player*> pair = hash.keys().at(i);
            QPointer<Database::Player> p1 = pair.first;
            QPointer<Database::Player> p2 = pair.second;
            string += pair.first->name->value() + "-" + pair.second->name->value() + ":" + QString::number(hash.value(pair)) + " ,";

        }
        variant.setValue(string);
    }


    return variant;
}
