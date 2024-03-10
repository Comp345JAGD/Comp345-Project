#include "Subject.h"
#include "Observer.h"

Subject::Subject()
{
    observers = new std::list<Observer *>;
}

void Subject::attach(Observer *o)
{
    observers->push_back(o);
}

void Subject::detach(Observer *o)
{
    observers->remove(o);
}

void Subject::notify(StatType statChanged, int value)
{
    std::list<Observer *>::iterator i = observers->begin();
    for (; i != observers->end(); i++)
    {
        (*i)->update(statChanged, value);
    }
}