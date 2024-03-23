#ifndef DICE_H
#define DICE_H

#include <string>
#include <iostream>
//#include "../Logger/logSubject.h"

class Dice // : public logSubject
{
public:
    Dice();
    int roll(const std::string &notation);
    int roll2(const std::string &notation);
};

#endif // DICE_H