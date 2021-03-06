#include "atomicrule.h"

#include "constraints.h"

START_ROW_IMPLEMENTATION(AtomicRule, Rule, Rule)
{
    IMPLEMENT_DATABASEATTRIBUTE(QString,AtomicRule,attributeName, tr("Attribute Name"))
    IMPLEMENT_DATABASEATTRIBUTE(int,AtomicRule,constraintId, tr("Constraint"))
    IMPLEMENT_DATABASEATTRIBUTE(QString,AtomicRule,parameter, tr("Parameter"))
}

QString AtomicRule::mimeType() const
{
    return Rule::mimeType();
}

bool AtomicRule::appliesTo(Row* row)
{
    QVariant value = row->attribute(attributeName->value())->toVariant();
    QVariant para = QVariant(parameter->value());
    Constraints::Constraint cons = (Constraints::Constraint) constraintId->value();
    return Constraints::appliesTo(value,cons,para);
}

END_ROW_IMPLEMENTATION()
