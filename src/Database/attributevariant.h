#ifndef ATTRIBUTEVARIANT_H
#define ATTRIBUTEVARIANT_H

#include <QVariant>

class AttributeVariant : public QVariant
{
public:
    explicit AttributeVariant();

    enum DisplayRole{
        MainWindow, DoppelkopfWindow, SkatWindow, HeartsWindow, PrognoseWindow, PokerWindow
    };

    void setDisplayRole(DisplayRole role);

    QVariant displayVariant() const;

signals:

public slots:

private:
    DisplayRole m_currentRole;

};

#endif // ATTRIBUTEVARIANT_H
