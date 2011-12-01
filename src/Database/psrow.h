#ifndef PSROW_H
#define PSROW_H

#include <LBDatabase/LBDatabase.h>

namespace Database {

class PSRow : public Row
{
public:
    PSRow();
    PSRow(const PSRow& other);
    PSRow(int id, TableBase *table);

    /*!
        Gibt das Gui::Details::DetailsWidget dieser Reihe zurück.

        Das DetailsWidget ist der linke Teil des RowWidget, wird aber auch an
        anderen Stellen verwendet (z.B. LeagueView)
      */
    virtual Gui::Details::DetailsWidget* detailsWidget();

    /*!
        Gibt das Gui::Details::RowWidget dieser Reihe zurück.

        Das RowWidget wird zum Beispiel im im Hauptfenster angezeigt, wenn die
        Reihe angeklickt wurde und kein SummaryWidget zur Verfüngung steht.

        Es besteht standardmäßig aus links dem DetailsWidget und rechts dem
        StatsWidget.
      */
    virtual Gui::Details::RowWidget* rowWidget();

    /*!
        Gibt das Gui::Details::RowWindow dieser Reihe zurück.

        Das RowWindow wird angezeigt, wenn die Reihe doppelt geklickt wurde.

        Es ist standardmäßig ein einfaches Fenster, welches das RowWidget
        enthält.
      */
    virtual Gui::Details::RowWindow *rowWindow();

    /*!
        Gibt das Gui::Details::StatsWidget dieser Reihe zurück.

        Es wird recht im RowWidget angezeigt.
      */
    virtual Gui::Details::StatsWidget *statsWidget();

    /*!
        Gibt Gui::Details::SummaryWidget dieser Reihe zurück.

        Es wird zum Beispiel im im Hauptfenster angezeigt, wenn die
        Reihe angeklickt wurde.
      */
    virtual Gui::Details::SummaryWidget *summaryWidget();
};

}

#endif // PSROW_H
