#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <list>

class Subject
{
public:
    Subject();
    virtual ~Subject() = default;
    virtual void attach(Observer *o);
    virtual void detach(Observer *o);
    virtual void notify(StatType statChanged, int value);

private:
    std::list<Observer *> *observers;
};

#endif // SUBJECT_H