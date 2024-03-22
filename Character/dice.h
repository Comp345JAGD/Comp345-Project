#ifndef DICE_H
#define DICE_H

#include <string>
#include <iostream>

class Dice
{
public:
    Dice();
    int roll(const std::string &notation);
    int roll2(const std::string &notation);
};

#endif // DICE_H