#include "subjectObserver.h"

void Subject::registerObserver(Observer* observer)
{
	observers.push_back(observer);
}

void Subject::unRegisterObserver(Observer* observer)
{
	vector<Observer*>::iterator position = find(observers.begin(), observers.end(), observer);
	if(position != observers.end()) // if it is equal to .end() it means the observer* was not found
		observers.erase(position);
}

void Subject::notifyObservers()
{
	for (Observer* observer : observers) {
		observer->update();
	}
}

