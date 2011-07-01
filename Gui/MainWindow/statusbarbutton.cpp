#include "statusbarbutton.h"

#include "statusbar.h"

using namespace Gui::MainWindow;

StatusbarButton::StatusbarButton(Statusbar *parent) :
    QPushButton(parent)
{
    setStyleSheet("Gui--MainWindow--StatusbarButton {"
			    "padding: 2px 6px 2px 6px;"
			    "font: normal 10px;"
			    "border: 1px solid #767676;"
			    "border-radius: 3px;"
			    "background-color: qlineargradient("
				    "spread:pad, x1:0, y1:0, x2:0, y2:1, "
				    "stop:0 rgba(254, 254, 254, 255), "
				    "stop:1 rgba(184, 184, 184, 255));"
		  "}"
		  "Gui--MainWindow--StatusbarButton:pressed {"
					      "background: url(:/graphics/styles/mac/statusbar/button_background_clicked);"
				    "}"
		  "Gui--MainWindow--StatusbarButton:checked {"
		  "background: url(:/graphics/styles/mac/statusbar/button_background_checked);"
/*				"background-color: qlineargradient("
				"spread:pad, x1:0, y1:0, x2:0, y2:1, "
				"stop:0 rgba(190, 190, 190, 190),"
				"stop:1 rgba(131, 131, 131, 131)); "*/
				    "}");

    setFixedHeight(16);
    setCheckable(true);
}
