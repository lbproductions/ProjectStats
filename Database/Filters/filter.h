#ifndef FILTER_H
#define FILTER_H

#include <QObject>

namespace Database
{

namespace Filters
{

class Filter : public QObject
{
    Q_OBJECT
public:
    explicit Filter(QObject *parent = 0);

signals:

public slots:

};

}
}

#endif // FILTER_H
