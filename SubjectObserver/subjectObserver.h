#ifndef SUBJECT_OBSERVER_H
#define SUBJECT_OBSERVER_H

#include <vector>
using namespace std;

class Observer
{
public:
    virtual void update() = 0; // pure virtual function, no body, you cannot instantiate this class, it is like an interface now
};

class Subject
{
private:
    vector<Observer*> observers;
public:
    void registerObserver(Observer* observer);
    void unRegisterObserver(Observer* observer);
    void notifyObservers();
};

#endif