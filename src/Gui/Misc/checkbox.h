#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QCheckBox>

namespace Gui
{

namespace Misc
{

class CheckBox : public QCheckBox
{
    Q_OBJECT
public:
    explicit CheckBox(QString text, QWidget *parent = 0);

signals:
    void checkStateChanged(Misc::CheckBox*,bool);

public slots:
    void onStateChanged();

};

}
}

#endif // CHECKBOX_H
