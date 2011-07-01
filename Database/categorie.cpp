#include "categorie.h"

#include <QStandardItem>
#include <Database/Categories/parentcategorie.h>
#include <Database/Categories/childcategorie.h>
#include "Categories/playerscategorie.h"
#include "Categories/gamescategorie.h"
#include "Categories/drinkscategorie.h"
#include "Categories/placescategorie.h"
#include "Categories/gamesfoldercategorie.h"
#include "Categories/playersfoldercategorie.h"
#include "Categories/drinksfoldercategorie.h"
#include "Categories/placesfoldercategorie.h"

START_TABLE_IMPLEMENTATION(Categorie)
QPointer<Categorie> Categories::createRowInstance(int id)
{
    qDebug() << "Categories::createRowInstance(int id) wird ausgeführt";
    int categorieId = id;
    Categorie* c = new Categorie(categorieId, this);

    if(c->isParentCategorie())
    {
        c->deleteLater();
        c = new ParentCategorie(categorieId, this);
    }
    else
    {

        c->deleteLater();
        c = 0;
        ChildCategorie *cc = new ChildCategorie(categorieId,this);
        switch(cc->type->value())
        {
        case Categorie::LibraryCategorieType:
            switch(cc->contentType->value())
            {
            case ChildCategorie::GamesCategorieContentType:
                c = new GamesCategorie(categorieId,this);
                break;
            case ChildCategorie::PlayersCategorieContentType:
                c = new PlayersCategorie(categorieId,this);
                break;
            case ChildCategorie::DrinksCategorieContentType:
                c = new DrinksCategorie(categorieId,this);
                break;
            case ChildCategorie::PlacesCategorieContentType:
                c = new PlacesCategorie(categorieId,this);
                break;
            }
            break;

        case Categorie::FolderCategorieType:
            switch(cc->contentType->value())
            {
            case ChildCategorie::GamesCategorieContentType:
                c = new GamesFolderCategorie(categorieId,this);
                break;
            case ChildCategorie::PlayersCategorieContentType:
                c = new PlayersFolderCategorie(categorieId,this);
                break;
            case ChildCategorie::DrinksCategorieContentType:
                c = new DrinksFolderCategorie(categorieId,this);
                break;
            case ChildCategorie::PlacesCategorieContentType:
                c = new PlacesFolderCategorie(categorieId,this);
                break;
            case ChildCategorie::LeagueCategorieContentType:
                //c = new LeagueFolderCategorie(categorieId,this);
                break;
            }
            break;

        }
        cc->deleteLater();

    }
    qDebug() << "Categories::createRowInstance(int id) wird beendet";
    return c;
}

QList<QPointer<ParentCategorie> > Categories::parentCategories()
{
    QList<Categorie*> clist = Categories::instance()->rowsBySqlCondition("WHERE parentId = -1 ORDER BY orderIndicator ASC");

    QList<QPointer<ParentCategorie> > list;
    foreach(Categorie* c, clist)
    {
        list.append(static_cast<ParentCategorie*>(c));
    }
    return list;
}
END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(Categorie, Categorie, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(QString,Categorie,name,tr("Name"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,Categorie,icon,tr("Icon"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Categorie,parentId,tr("parentId"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Categorie,type,tr("Type"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Categorie,orderIndicator,tr("OrderIndicator"))
    IMPLEMENT_DATABASEATTRIBUTE(int,Categorie,contentType,tr("ContentType"))


}

QString Categorie::mimeType() const
{
    return "application/projectstats.categorie";
}

void Categorie::setStandardItem(QStandardItem *item)
{
    m_standardItem = item;
}

QStandardItem * Categorie::standardItem() const
{
    return m_standardItem;
}

bool Categorie::isParentCategorie()
{
    return this->type->value() == Categorie::ParentCategorieType;
}

END_ROW_IMPLEMENTATION()
