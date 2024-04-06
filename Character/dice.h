#ifndef DICE_H
#define DICE_H

#include <string>
#include <iostream>
#include "../GameLogger.h"
#include "../GameFileWriter.h"
//#include "../Logger/logSubject.h"

class Dice : public GameLogger
{
public:
    Dice();
    int roll(const std::string &notation);
    int roll2(const std::string &notation);
private:
    GameFileWriter Logger;
};

#endif // DICE_H