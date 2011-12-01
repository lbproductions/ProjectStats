#ifndef ROWWINDOW_H
#define ROWWINDOW_H

#include <QMainWindow>

namespace Database{

    class PSRow;

}

namespace Gui{

    namespace Details{

    class RowWidget;

class RowWindow : public QMainWindow
{
    Q_OBJECT
public:
    RowWindow(QWidget *parent = 0);
    explicit RowWindow(Database::PSRow* row, QWidget *parent = 0, bool setupCentralWidget = true);

    virtual void show();

signals:

public slots:

protected:
    RowWidget* m_rowWidget;

};

    }}

#endif // ROWWINDOW_H
