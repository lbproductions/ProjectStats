#ifndef ABSTRACTDETAILSWIDGET_H
#define ABSTRACTDETAILSWIDGET_H

#include <QWidget>
#include <QPointer>

namespace Database
{
    class Row;
}

namespace Gui
{

namespace Details
{
//! Oberklasse für alle Widgets, die Details über eine Row anzeigen.
/*!
  Dieses Widget wird entweder direkt im MainWindow angezeigt, oder ist centralWidget des zugehörigen DetailsWindow.
  \see DetailsWindow
  */
class DetailsWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
      Erstellt ein AbstractDetailsWidget, welches Details der Reihe \p row darstellt.
      */
    explicit DetailsWidget(Database::Row *row, QWidget *parent = 0);

    /*!
      \return Die Reihe, dessen Details dieses Widget darstellt.
      */
    Database::Row *row() const;

    /*!
      Setzt den Titel auf \p title.
      */
    void setTitle(QString title);
    /*!
      \return Der Titel des DetailsWidgets.
      */
    QString title();
    /*!
      Setzt die Beschreibung auf \p description.
      */
    void setDescription(QString description);
    /*!
      \return Die Beschreibung für das DetailsWidget.
      */
    QString description();

    bool isEditable() const;

    virtual void setEditable(bool editable);

    virtual bool mayBeEditable() const;

protected:
    QPointer<Database::Row> m_row; //!< Die Reihe, dess Details dieses Widget darstellt.

    bool m_editable;
    bool m_mayBeEditable;
    QString m_description;
    QString m_title;
};
}
}

#endif // ABSTRACTDETAILSWIDGET_H
