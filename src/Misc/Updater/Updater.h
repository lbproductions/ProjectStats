#ifndef UPDATER_H
#define UPDATER_H

class Updater
{
public:
    virtual void checkForUpdates() = 0;
    virtual void checkForUpdatesInBackground() = 0;
};

#endif // UPDATER_H
