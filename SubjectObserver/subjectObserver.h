#ifndef SUBJECT_OBSERVER_H
#define SUBJECT_OBSERVER_H

#include <vector>
using namespace std;

class IObserver
{
public:
    virtual void update() = 0; // pure virtual function, no body, you cannot instantiate this class, it is like an interface now
};

class BSubject
{
private:
    vector<IObserver*> observers;
public:
    void registerObserver(IObserver* observer);
    void unRegisterObserver(IObserver* observer);
    void notifyObservers();
};

#endif