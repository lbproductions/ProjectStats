#include "sparkleupdater.h"

#include <Cocoa/Cocoa.h>
#include <Sparkle/Sparkle.h>

class SparkleUpdater::Private
{
    public:
	SUUpdater* updater;
};

SparkleUpdater::SparkleUpdater(const QString& aUrl)
{
    d = new Private;
    d->updater = [[SUUpdater sharedUpdater] retain];
    NSURL* url = [NSURL URLWithString:
		    [NSString stringWithUTF8String: aUrl.toUtf8().data()]];
    [d->updater setFeedURL: url];
}

SparkleUpdater::~SparkleUpdater()
{
    [d->updater release];
    delete d;
}

void SparkleUpdater::checkForUpdatesInBackground()
{
    [d->updater checkForUpdatesInBackground];
}

void SparkleUpdater::checkForUpdates()
{
    [d->updater checkForUpdates:d->updater];
}
