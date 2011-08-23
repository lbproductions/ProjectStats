#ifndef ROWWINDOW_H
#define ROWWINDOW_H

#include <QMainWindow>

namespace Database{

    class Row;

}

namespace Gui{

    namespace Details{

    class RowWidget;

class RowWindow : public QMainWindow
{
    Q_OBJECT
public:
    RowWindow(QWidget *parent = 0);
    explicit RowWindow(Database::Row* row, QWidget *parent = 0, bool setupCentralWidget = true);

signals:

public slots:

private:
    RowWidget* m_rowWidget;

};

    }}

#endif // ROWWINDOW_H
