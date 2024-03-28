#include "characterTestDriver.h"

void characterTestDriver()
{
    // // Sample character creation and customization interface, allowing players to choose their
    // // name, class, level and allocation of their stats.
    // cout << "Welcome to DnD! Please choose a class for your character:\n";

    // int decision;
    // bool validity = false;

    // // Class selection. For now, only Fighter class option implemented.

    // while (!validity)
    // {
    //     cout << "1. Scientist 2. Doctor 3. Fighter\n"
    //          << "4. Paladin, 5. Rogue, 6. Archer\n";

    //     if (std::cin >> decision)
    //     {
    //         if (decision >= 1 && decision <= 6)
    //             validity = true;
    //         else
    //             std::cout << "Invalid integer, please enter a number between 1 and 6.\n";
    //     }
    //     else
    //     {
    //         std::cin.clear();
    //         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //         std::cout << "Invalid input, please enter a number between 1 and 6.\n";
    //     }
    // }

    // int inputLevel;
    // bool validity2 = false;

    // // Level selection. Limited between 1 to 10 as each level equates to another dice roll. Restriction
    // // implemented to mitigate excessive roll allocations.

    // while (!validity2)
    // {
    //     cout << "Please enter a level for your character between 1 and 10.\n";

    //     if (cin >> inputLevel)
    //     {
    //         if (inputLevel >= 1 && inputLevel <= 10)
    //             validity2 = true;
    //         else
    //             std::cout << "Invalid integer, please enter a number between 1 and 10.\n";
    //     }
    //     else
    //     {
    //         std::cin.clear();
    //         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //         std::cout << "Invalid input, please enter a number between 1 and 10.\n";
    //     }
    // }

    // // Character name creation

    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // string inputName;
    // cout << "Please enter a name for your character: ";
    // std::getline(std::cin, inputName);

    // switch (decision)
    // {
    // case 1:
    //     cout << "Scientist has no been implemented yet, sorry!\n";
    //     break;
    // case 2:
    //     cout << "Doctor has not been implemented yet, sorry!\n";
    //     break;
    // case 3:
    // {
    //     cout << "Good choice! Creating a fighter with the name " << inputName << ".\n";
    //     Fighter test1(inputName, inputLevel);
    //     Player user(&test1);

    //     std::cout << "Let's further test functionality of the our Observer Pattern implementation.\n";
    //     std::cout << "Let's add two strength to the character we've created.\n";
    //     test1.addStats(str, 2);
    //     std::cout << "The output above is a result of the notify function notifying the observer we've attached to your "
    //               << "character.\nLet's try it again by adding 5 wisdom.\n";
    //     test1.addStats(dex, 5);
    //     break;
    // }
    // case 4:
    //     cout << "Paladin has not been implemented yet, sorry!\n";
    //     break;

    // case 5:
    //     cout << "Rogue has not been implemented yet, sorry!\n";
    //     break;
    // case 6:
    //     cout << "Archer has not been implemented yet, sorry!\n";
    //     break;
    // }

    DungeonMaster dm;
    int decision;
    bool validity = false;

    std::cout << "Welcome to the testing grounds of our game. Let's start off by creating a Fighter.\n";

    while (!validity)
    {
        std::cout << "Please choose which build you would like to implement.\n";
        std::cout << "1. Nimble: favors dexterity and armor class to evade blows\n";
        std::cout << "2. Bully: uses brute strength to destroy his enemies\n";
        std::cout << "3. Tank: favors survival by more hit points through high constitution score\n";

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
        std::cout << "You have chosen the Nimble build.\n";
        CharacterBuilder *nimbleChar = new nimbleCharacterBuilder;
        dm.setCharacterBuilder(nimbleChar);
        dm.constructCharacter();
        Character *test1 = dm.getCharacter();

        std::cout << "Here are the stat allocations based on your build:\n";

        test1->displayScores1();
        test1->groupedCalculate();

        delete nimbleChar;
        delete test1;
        break;
    }
    case 2:
    {
        std::cout << "You have chosen the Bully build.\n";
        CharacterBuilder *bullyChar = new bullyCharacterBuilder;
        dm.setCharacterBuilder(bullyChar);
        dm.constructCharacter();
        Character *test1 = dm.getCharacter();

        std::cout << "Here are the stat allocations based on your build:\n";

        test1->displayScores1();
        test1->groupedCalculate();

        delete bullyChar;
        delete test1;
        break;
    }
    case 3:
    {
        std::cout << "You have chosen the Tank build.\n";
        CharacterBuilder *tankChar = new tankCharacterBuilder;
        dm.setCharacterBuilder(tankChar);
        dm.constructCharacter();
        Character *test1 = dm.getCharacter();

        std::cout << "\nHere are the stat allocations based on your build:\n";

        test1->displayScores1();
        test1->groupedCalculate();

        delete tankChar;
        delete test1;
        break;
    }
    }
}