#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"

class Subject
{
public:
    virtual ~Subject();

    virtual void attach(Observer *o)
};

#endif // SUBJECT_H