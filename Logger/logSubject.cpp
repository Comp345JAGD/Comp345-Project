/*

#include "logSubject.h"


logSubject::logSubject(){
    logObservers = new std::vector<logObserver *>;
}

void logSubject::logAttach(logObserver *o, int type){
    logObservers->push_back(o);
    logType = type;
}

void logSubject::logDetach(logObserver *o){
    auto itr = find(logObservers->begin(), logObservers->end(), o);

    if(itr != logObservers->end()){
        logObservers->erase(itr);
    }
}

void logSubject::logNotify(const std::string &message){

    std::vector<logObserver *>::iterator itr = logObservers->begin();
    for(; itr != logObservers->end(); itr++){
        (*itr)->log(message);
    }
}

void startLogging(){
    
}

void endLogging(){
}

*/