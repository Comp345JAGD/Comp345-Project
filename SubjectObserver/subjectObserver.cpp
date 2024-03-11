#include "subjectObserver.h"

void BSubject::registerObserver(IObserver* observer)
{
	observers.push_back(observer);
}

void BSubject::unRegisterObserver(IObserver* observer)
{
	vector<IObserver*>::iterator position = find(observers.begin(), observers.end(), observer);
	if(position != observers.end()) // if it is equal to .end() it means the observer* was not found
		observers.erase(position);
}

void BSubject::notifyObservers()
{
	for (IObserver* observer : observers) {
		observer->update();
	}
}

