#ifndef OBSERVER_H
#define OBSERVER_H
#include <string>

// Abstract observer (View)

enum StatType {lvl, str, dex, consti, intel, wis, chrm, hp, aClass, aBonus, dBonus};

class Observer
{
public:
    Observer();
    ~Observer() = default;
    virtual void update(StatType statChange, int value) = 0;
};

#endif // OBSERVER_H