#include "samplerow.h"

#include "samplerowchild.h"

START_TABLE_IMPLEMENTATION(SampleRow)

QPointer<SampleRow> SampleRows::createRowInstance(int id)
{
    SampleRow *row = new SampleRow(id,this);

    if(row->type->value() == "child")
    {
        return new SampleRowChild(id,this);
    }

    return row;
}

END_TABLE_IMPLEMENTATION()

START_ROW_IMPLEMENTATION(SampleRow /*Name der Row*/,
                         SampleRow /*Name der Basisklasse der Row (z.B. Game für alle games)*/,
                         Row /*Name der Superklasse dieser Row*/ )
{
    IMPLEMENT_DATABASEATTRIBUTE(QString,SampleRow,name /*Name des Attributs*/, "name" /*Displayname zB für Tabellenheader*/)
    IMPLEMENT_DATABASEATTRIBUTE(QString,SampleRow,type, "type")

    IMPLEMENT_ATTRIBUTE_WITH_UPDATEFUNCTION(QString, SampleRow, test, "test")

    IMPLEMENT_ATTRIBUTE(QString, SampleRow, test2, "test2")
    test2->setUpdateFunction(test, &SampleRow::update_test2_test);

    IMPLEMENT_ATTRIBUTE(QList<Drink*>, SampleRow, drinks, "drinks")

    name->addDependingAttribute(test);
    type->addDependingAttribute(test);
}

QString SampleRow::mimeType() const
{
    return "application/projectstats.samplerow";
}

QString SampleRow::calculate_test()
{
    return "test_value";
}

QFuture<QString> SampleRow::updateIfPossible_test(AttributeBase */*changedDependency*/)
{
    return QFuture<QString>();
}

QString SampleRow::calculate_test2()
{
    return "test2_value";
}

QString SampleRow::update_test2_test()
{
    return "test2_value_updatedVia_test";
}

QList<Drink*> SampleRow::calculate_drinks()
{
    return Drinks::instance()->rowsBySqlCondition("WHERE size = 0.33");
}


END_ROW_IMPLEMENTATION()