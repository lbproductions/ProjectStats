#include "attributevariant.h"

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

QVariant AttributeVariant::displayVariant() const
{
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

    else if(QString(this->typeName()) == "QList<Database::Place*>"){
        QList<Database::Place*> list = this->value<QList<Database::Place*> >();
        QString string = "";
        for (int i = 0; i<list.size();i++){
            string += list.at(i)->displayString->value();
            if (i < list.size()-1){
                string += "; ";
            }
        }
        variant.setValue(string);
    }

    else if(QString(this->typeName()) == "QList<Database::Drink*>"){
        QList<Database::Drink*> list = this->value<QList<Database::Drink*> >();
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

    else if(QString(this->typeName()) == "QList<Database::Game*>"){
        QList<Database::Game*> list = this->value<QList<Database::Game*> >();
        variant.setValue(list.size());
    }

    else if(QString(this->typeName()) == "QList<Database::Round*>"){
        QList<Database::Round*> list = this->value<QList<Database::Round*> >();
        variant.setValue(list.size());
    }

    else if(QString(this->typeName()) == "QList<Database::Player*>"){
        QList<Database::Player*> list = this->value<QList<Database::Player*> >();
        QString string = "";
        for (int i = 0; i<list.size();i++){
            string += list.at(i)->name->value();
            if (i < list.size()-1){
                string += ", ";
            }
        }
        variant.setValue(string);
    }

    else if(QString(this->typeName()) == "QList<Database::Schmeisserei*>"){
        QList<Database::Schmeisserei*> list = this->value<QList<Database::Schmeisserei*> >();
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

    else if(QString(this->typeName()) == "QMap<Database::Player*COMMA int>"){
        QString string = "";
        QMap<Database::Player*,int> hash = this->value<QMap<Database::Player*,int> >();
        foreach(Database::Player* p, hash.keys()){
            string += p->name->value() + ":" + QString::number(hash.value(p)) + ", ";
        }
        variant.setValue(string);
    }

    else if(QString(this->typeName()) == "QMap<Database::Player*COMMA double>"){
        QString string = "";
        QMap<Database::Player*,double> hash = this->value<QMap<Database::Player*,double> >();
        foreach(Database::Player* p, hash.keys()){
            string += p->name->value() + ":" + QString::number(hash.value(p)) + ", ";
        }
        variant.setValue(string);
    }

    else if(QString(this->typeName()) == "QMap<Database::Player*COMMA bool>"){
        QString string = "";
        QMap<Database::Player*,bool> hash = this->value<QMap<Database::Player*,bool> >();
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

    else if(QString(this->typeName()) == "QMap<Database::LiveGame*COMMA double>"){
        QString string = "";
        QMap<Database::LiveGame*,double> hash = this->value<QMap<Database::LiveGame*,double> >();
        foreach(Database::LiveGame* p, hash.keys()){
            string += p->name->value() + ":" + QString::number(hash.value(p)) + ", ";
        }
        variant.setValue(string);
    }
    else if(QString(this->typeName()) == "QMap<QString COMMA int>"){
        if(m_currentRole == MainWindow){
            QMap<QString,int> hash = this->value<QMap<QString,int> >();
            variant.setValue(hash.value("General"));
        }
        else if(m_currentRole == DoppelkopfWindow){
            QMap<QString,int> hash = this->value<QMap<QString,int> >();
            variant.setValue(hash.value("Doppelkopf"));
        }
        else if(m_currentRole == SkatWindow){
            QMap<QString,int> hash = this->value<QMap<QString,int> >();
            variant.setValue(hash.value("Skat"));
        }
        else if(m_currentRole == HeartsWindow){
            QMap<QString,int> hash = this->value<QMap<QString,int> >();
            variant.setValue(hash.value("Hearts"));
        }
        else if(m_currentRole == PokerWindow){
            QMap<QString,int> hash = this->value<QMap<QString,int> >();
            variant.setValue(hash.value("Poker"));
        }
        else if(m_currentRole == PrognoseWindow){
            QMap<QString,int> hash = this->value<QMap<QString,int> >();
            variant.setValue(hash.value("Prognose"));
        }
        else{
            QString string = "";
            QMap<QString,int> hash = this->value<QMap<QString,int> >();
            foreach(QString i, hash.keys()){
                string += i + ":" + QString::number(hash.value(i)) + ", ";
            }
            variant.setValue(string);
        }

    }
    else if(QString(this->typeName()) == "QMap<QString COMMA double>"){
        if(m_currentRole == MainWindow){
            QMap<QString,double> hash(this->value<QMap<QString,double> >());
            variant.setValue(hash.value("General"));
        }
        else if(m_currentRole == DoppelkopfWindow){
            QMap<QString,double> hash = this->value<QMap<QString,double> >();
            variant.setValue(hash.value("Doppelkopf"));
        }
        else if(m_currentRole == SkatWindow){
            QMap<QString,double> hash = this->value<QMap<QString,double> >();
            variant.setValue(hash.value("Skat"));
        }
        else if(m_currentRole == HeartsWindow){
            QMap<QString,double> hash = this->value<QMap<QString,double> >();
            variant.setValue(hash.value("Hearts"));
        }
        else if(m_currentRole == PokerWindow){
            QMap<QString,double> hash = this->value<QMap<QString,double> >();
            variant.setValue(hash.value("Poker"));
        }
        else if(m_currentRole == PrognoseWindow){
            QMap<QString,double> hash = this->value<QMap<QString,double> >();
            variant.setValue(hash.value("Prognose"));
        }
        else{
            QString string = "";
            QMap<QString,double> hash = this->value<QMap<QString,double> >();
            foreach(QString i, hash.keys()){
                string += i + ":" + QString::number(hash.value(i)) + ", ";
            }
            variant.setValue(string);
        }
    }
    else if(QString(this->typeName()) == "QMap<QString COMMA QDateTime>"){
        if(m_currentRole == MainWindow){
            QMap<QString,QDateTime> hash(this->value<QMap<QString,QDateTime> >());
            variant.setValue(hash.value("General"));
        }
        else if(m_currentRole == DoppelkopfWindow){
            QMap<QString,QDateTime> hash(this->value<QMap<QString,QDateTime> >());
            variant.setValue(hash.value("Doppelkopf"));
        }
        else if(m_currentRole == SkatWindow){
            QMap<QString,QDateTime> hash = this->value<QMap<QString,QDateTime> >();
            variant.setValue(hash.value("Skat"));
        }
        else if(m_currentRole == HeartsWindow){
            QMap<QString,QDateTime> hash = this->value<QMap<QString,QDateTime> >();
            variant.setValue(hash.value("Hearts"));
        }
        else if(m_currentRole == PokerWindow){
            QMap<QString,QDateTime> hash = this->value<QMap<QString,QDateTime> >();
            variant.setValue(hash.value("Poker"));
        }
        else if(m_currentRole == PrognoseWindow){
            QMap<QString,QDateTime> hash = this->value<QMap<QString,QDateTime> >();
            variant.setValue(hash.value("Prognose"));
        }
        else{
            QString string = "";
            QMap<QString,QDateTime> hash = this->value<QMap<QString,QDateTime> >();
            foreach(QString i, hash.keys()){
                string += i + ":" + hash.value(i).toString("dd.MM.yyyy") + ", ";
            }
            variant.setValue(string);
        }
    }
    else if(QString(this->typeName()) == "QMap<int COMMA int>"){
        QString string = "";
        QMap<int,int> hash(this->value<QMap<int,int> >());
        foreach(int i, hash.keys()){
            string += QString::number(i) + ":" + QString::number(hash.value(i)) + ", ";
        }
        variant.setValue(string);
    }
    else if(QString(this->typeName()) == "QMap<QPair<Database::Player*COMMA Database::Player*>COMMA int>"){
        QString string = "";
        QMap<QPair<Database::Player*,Database::Player*>,int> hash = this->value<QMap<QPair<Database::Player*,Database::Player*>,int> >();
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
