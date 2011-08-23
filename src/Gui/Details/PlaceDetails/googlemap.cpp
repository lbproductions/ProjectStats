#include "googlemap.h"
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDomDocument>
#include <QDomElement>
#include <QWebFrame>
#include <QWebPage>
#include <QEventLoop>
#include <QApplication>
#include <math.h>

using namespace Gui::Details;


GoogleMap::GoogleMap(QWidget *parent) : QWebView(parent), pendingRequests(0)
{
	manager = new QNetworkAccessManager(this);
	
        this->settings()->setAttribute(QWebSettings::JavascriptCanAccessClipboard,true);
	
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
	connect(this,SIGNAL(reloadMap()), this,SLOT(loadCoordinates()));
}

void GoogleMap::geoCode(QString local)
{
	clearCoordinates();

        QString requestStr( tr("http://maps.google.com/maps/geo?q=%1&output=%2&key=%3")
			.arg(local)
			.arg("csv")
			.arg("GOOGLE_MAPS_KEY") );

	manager->get( QNetworkRequest(requestStr) );
	++pendingRequests;
}
void GoogleMap::replyFinished(QNetworkReply *reply)
{
    QString replyStr( reply->readAll() );
    QStringList coordinateStrList = replyStr.split(",");

    if( coordinateStrList.size() == 4)
    {
        QPointF coordinate( coordinateStrList[2].toFloat(),coordinateStrList[3].toFloat() );
        coordinates << coordinate;
    }

    --pendingRequests;
    if( pendingRequests<1 )
    {
        emit( reloadMap() ); 
    }

}

void GoogleMap::loadCoordinates()
{
	foreach(QPointF point ,coordinates)
    {
		this->page()->mainFrame()->evaluateJavaScript( 
				QString("Open(%1,%2)").arg(point.x()).arg(point.y()) ); 
    }
}

void GoogleMap::clearCoordinates()
{
    coordinates.clear();
}

void GoogleMap::showCurrentLocation(){
    this->page()->mainFrame()->evaluateJavaScript(QString("ShowMyLocation()"));
}

