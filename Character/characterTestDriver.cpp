#include "characterTestDriver.h"

void characterTestDriver()
{
    // Sample character creation and customization interface, allowing players to choose their
    // name, class, level and allocation of their stats.
    cout << "Welcome to DnD! Please choose a class for your character:\n";

    int decision;
    bool validity = false;

    // Class selection. For now, only Fighter class option implemented.

    while (!validity)
    {
        cout << "1. Alchemist 2. Cleric 3. Fighter\n"
             << "4. Paladin, 5. Rogue, 6. Wizard\n";

        if (std::cin >> decision)
        {
            if (decision >= 1 && decision <= 6)
                validity = true;
            else
                std::cout << "Invalid integer, please enter a number between 1 and 6.\n";
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, please enter a number between 1 and 6.\n";
        }
    }

    int inputLevel;
    bool validity2 = false;

    // Level selection. Limited between 1 to 10 as each level equates to another dice roll. Restriction
    // implemented to mitigate excessive roll allocations.

    while (!validity2)
    {
        cout << "Please enter a level for your character between 1 and 10.\n";

        if (cin >> inputLevel)
        {
            if (inputLevel >= 1 && inputLevel <= 10)
                validity2 = true;
            else
                std::cout << "Invalid integer, please enter a number between 1 and 10.\n";
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, please enter a number between 1 and 10.\n";
        }
    }

    // Character name creation

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    string inputName;
    cout << "Please enter a name for your character: ";
    std::getline(std::cin, inputName);

    switch (decision)
    {
    case 1:
        cout << "Alchemist has no been implemented yet, sorry!\n";
        break;
    case 2:
        cout << "Cleric has not been implemented yet, sorry!\n";
        break;
    case 3:
    {
        cout << "Good choice! Creating a fighter with the name " << inputName << ".\n";
        Fighter test1(inputName, inputLevel);
        break;
    }
    case 4:
        cout << "Paladin has not been implemented yet, sorry!\n";
        break;
    case 5:
        cout << "Rogue has not been implemented yet, sorry!\n";
        break;
    case 6:
        cout << "Wizard has not been implemented yet, sorry!\n";
        break;
    }
}
