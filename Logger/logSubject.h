/*

#ifndef LOGSUBJECT_H
#define LOGSUBJECT_H

#include "logObserver.h"
#include <vector>

class logSubject
{
    public:
    logSubject();
    virtual ~logSubject() = default;
    virtual void logAttach(logObserver *o, int type); //type to determine what is being attached 1 - player| 2 - dice| 3 - GameLog| 4 - GameMap
    virtual void logDetach(logObserver *o);
    virtual void logNotify(const std::string &message);
    virtual void startLogging();
    virtual void endLogging();

    private:
        std::vector<logObserver *> *logObservers;
        int logType;
};

#endif

*/