#include "dice.h"
#include <cstdlib>
#include <ctime>

Dice::Dice()
{
    std::srand(std::time(nullptr));
}

int Dice::roll(const std::string &notation)
{
    int x, y, z = 0;

    if (std::sscanf(notation.c_str(), "%dd%d+%d", &x, &y, &z) >= 2)
    {
        if (y != 4 && y != 6 && y != 8 && y != 10 && y != 12 && y != 20 && y != 100)
        {
            std::cout << "Invalid dice value.\n";
            return -1;
        }
        int sum = 0;

        for (int i = 0; i < x; i++)
        {
            int thisRoll = 0;
            thisRoll = rand() % y + 1;
            std::cout << "Your " << i + 1 << " roll is: " << thisRoll << std::endl;
            sum += thisRoll;
        }

        sum += z;
        return sum;
    }
    std::cout << "Invalid notation.\n";
    return -1;
}

int Dice::roll2(const std::string &notation)
{
    int x, y, z = 0;

    if (std::sscanf(notation.c_str(), "%dd%d+%d", &x, &y, &z) >= 2)
    {
        if (y != 4 && y != 6 && y != 8 && y != 10 && y != 12 && y != 20 && y != 100)
        {
            std::cout << "Invalid dice value.\n";
            return -1;
        }
        int sum = 0;

        for (int i = 0; i < x; i++)
        {
            int thisRoll = 0;
            thisRoll = rand() % y + 1;
            sum += thisRoll;
        }

        sum += z;
        return sum;
    }
    std::cout << "Invalid notation.\n";
    return -1;
}