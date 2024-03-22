#ifndef CHARACTERSTRATEGY_H
#define CHARACTERSTRATEGY_H

#include "character.h"
#include "../Map/GameMap.h"

class CharacterStrategy
{
public:
    virtual ~CharacterStrategy() = default;
    virtual void execute(Character *character, GameMap *map) = 0;
};

class HumanPlayerStrategy : public CharacterStrategy
{
    void execute(Character *character, GameMap *map)
    {
        // Output the current map

        int decision;
        bool validity = false;

        std::cout << "Please choose an action:\n";
        std::cout << "1. Move\n2. Attack\n 3. Free Action";

        while (!validity)
        {
            std::cout << "1. Move\n2. Attack\n 3. Free Action";

            if (std::cin >> decision)
            {
                if (decision >= 1 && decision <= 3)
                    validity = true;
                else
                    std::cout << "Invalid integer, please enter a number between 1 and 3.\n";
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input, please enter a number between 1 and 3.\n";
            }
        }

        switch (decision)
        {
        case 1:
        {
        }
                }
    }
};

#endif // CHARACTERSTRATEGY_H