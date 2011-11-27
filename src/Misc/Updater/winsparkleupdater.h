#ifndef WINSPARKLEUPDATER_H
#define WINSPARKLEUPDATER_H

#include "Updater.h"

#include <QString>

class WinSparkleUpdater : public Updater
{
    public:
        WinSparkleUpdater(const QString& url);
        ~WinSparkleUpdater();

        virtual void checkForUpdates();
        virtual void checkForUpdatesInBackground();
};

#endif // WINSPARKLEUPDATER_H
