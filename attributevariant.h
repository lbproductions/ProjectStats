#ifndef ATTRIBUTEVARIANT_H
#define ATTRIBUTEVARIANT_H

#include <QVariant>

class AttributeVariant : public QVariant
{
public:
    explicit AttributeVariant();

    enum DisplayRole{
        MainWindow, DoppelkopfWindow
    };

    void setDisplayRole(DisplayRole role);

    QVariant displayVariant();

signals:

public slots:

private:
    DisplayRole m_currentRole;

};

#endif // ATTRIBUTEVARIANT_H
