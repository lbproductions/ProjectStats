#ifndef DATABASE_ROW_H
#define DATABASE_ROW_H

#include <QObject>

namespace Database {

class Row : public QObject
{
    Q_OBJECT
public:
    explicit Row(QObject *parent = 0);

signals:

public slots:

};

} // namespace Database

#endif // DATABASE_ROW_H
