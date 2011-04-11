#include "samplerow.h"

IMPLEMENT_TABLE(SampleRow)

START_ROW_IMPLEMENTATION(SampleRow, SampleRow, Row)
{
    IMPLEMENT_DATABASEATTRIBUTE(QString,SampleRow,name)
    IMPLEMENT_DATABASEATTRIBUTE(QString,SampleRow,type)

    IMPLEMENT_ATTRIBUTE_WITH_UPDATEFUNCTION(QString, SampleRow, test)

    IMPLEMENT_ATTRIBUTE(QString, SampleRow, test2)
    test2->setUpdateFunction(test, &SampleRow::update_test2_test);

    IMPLEMENT_ATTRIBUTE(QList<Drink*>, SampleRow, drinks)

    name->addDependingAttribute(test);
    type->addDependingAttribute(test);
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
