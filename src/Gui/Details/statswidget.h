#ifndef STATSWIDGET_H
#define STATSWIDGET_H

#include <QWidget>

namespace Database{

    class Row;

}

namespace Gui{

    namespace Details{

class StatsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StatsWidget(Database::Row *row, QWidget *parent = 0);

signals:

public slots:

};

}}

#endif // STATSWIDGET_H
