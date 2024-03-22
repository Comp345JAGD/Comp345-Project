#ifndef LOGOBSERVER_H
#define LOGOBSERVER_H
#include <string>

class logObserver
{
    public:
    virtual ~logObserver(){};
    virtual void log(const std::string &message, int type);
};



#endif