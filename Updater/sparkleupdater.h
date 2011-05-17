#ifndef SPARKLEUPDATER_H
#define SPARKLEUPDATER_H

#include "updater.h"

#include <QString>

class SparkleUpdater : public Updater
{
    public:
	SparkleUpdater(const QString& url);
	~SparkleUpdater();

	virtual void checkForUpdates();
	virtual void checkForUpdatesInBackground();
    private:
	class Private;
	Private* d;
};

#endif // SPARKLEUPDATER_H
