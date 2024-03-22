#include <limits>
#include "CharacterBuilder.h"

void CharacterBuilder::randomizeStats()
{
    std::cout << "We will now roll for your starting ability scores.\n";

    for (int i = 0; i < randomizedStats.size(); i++)
    {
        std::array<int, 4> rolls;
        for (int j = 0; j < 4; j++)
        {
            rolls[j] = produced_character->getDice().roll2("1d6");
        }
        std::sort(rolls.begin(), rolls.end(), std::greater<int>());
        randomizedStats[i] = rolls[0] + rolls[1] + rolls[2]; // Sum of the top 3 rolls
    }

    // Sort the sums in descending order
    std::sort(randomizedStats.begin(), randomizedStats.end(), std::greater<int>());

    // Print the sorted sums
    for (int k = 0; k < randomizedStats.size(); k++)
    {
        std::cout << "Num at " << k << ": " << randomizedStats[k] << "\n";
    }
}

void nimbleCharacterBuilder::build()
{

    produced_character->setLevel(1);
    produced_character->setDexterity(randomizedStats[0]);
    produced_character->setConstitution(randomizedStats[1]);
    produced_character->setStrength(randomizedStats[2]);
    produced_character->setIntelligence(randomizedStats[3]);
    produced_character->setCharisma(randomizedStats[4]);
    produced_character->setWisdom(randomizedStats[5]);
}

void bullyCharacterBuilder::build()
{
    produced_character->setLevel(1);
    produced_character->setStrength(randomizedStats[0]);
    produced_character->setConstitution(randomizedStats[1]);
    produced_character->setDexterity(randomizedStats[2]);
    produced_character->setIntelligence(randomizedStats[3]);
    produced_character->setCharisma(randomizedStats[4]);
    produced_character->setWisdom(randomizedStats[5]);
}

void tankCharacterBuilder::build()
{
    produced_character->setLevel(1);
    produced_character->setConstitution(randomizedStats[0]);
    produced_character->setDexterity(randomizedStats[1]);
    produced_character->setStrength(randomizedStats[2]);
    produced_character->setIntelligence(randomizedStats[3]);
    produced_character->setCharisma(randomizedStats[4]);
    produced_character->setWisdom(randomizedStats[5]);
}

void DungeonMaster::constructCharacter()
{

    std::cout << "We will be randomize the starting stats of your character.\n";

    produced_characterBuilder->createFighter();
    produced_characterBuilder->randomizeStats();
    produced_characterBuilder->build();
}

// int main()
// {

//     DungeonMaster dm;
//     int decision;
//     bool validity = false;

//     std::cout << "Welcome to the testing grounds of our game. Let's start off by creating a Fighter.\n";

//     while (!validity)
//     {
//         std::cout << "Please choose which build you would like to implement.\n";
//         std::cout << "1. Nimble: favors dexterity and armor class to evade blows\n";
//         std::cout << "2. Bully: uses brute strength to destroy his enemies\n";
//         std::cout << "3. Tank: favors survival by more hit points through high constitution score\n";

//         if (std::cin >> decision)
//         {
//             if (decision >= 1 && decision <= 3)
//                 validity = true;
//             else
//                 std::cout << "Invalid integer, please enter a number between 1 and 3.\n";
//         }
//         else
//         {
//             std::cin.clear();
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//             std::cout << "Invalid input, please enter a number between 1 and 3.\n";
//         }
//     }

//     switch (decision)
//     {
//     case 1:
//     {
//         std::cout << "You have chosen the Nimble build.\n";
//         CharacterBuilder *nimbleChar = new nimbleCharacterBuilder;
//         dm.setCharacterBuilder(nimbleChar);
//         dm.constructCharacter();
//         Fighter *test1 = dm.getCharacter();

//         std::cout << "Here are the stat allocations based on your build:\n";

//         test1->displayScores1();
//         test1->groupedCalculate();

//         delete nimbleChar;
//         delete test1;
//         break;
//     }
//     case 2:
//     {
//         std::cout << "You have chosen the Bully build.\n";
//         CharacterBuilder *bullyChar = new bullyCharacterBuilder;
//         dm.setCharacterBuilder(bullyChar);
//         dm.constructCharacter();
//         Fighter *test1 = dm.getCharacter();

//         std::cout << "Here are the stat allocations based on your build:\n";

//         test1->displayScores1();
//         test1->groupedCalculate();

//         delete bullyChar;
//         delete test1;
//         break;
//     }
//     case 3:
//     {
//         std::cout << "You have chosen the Tank build.\n";
//         CharacterBuilder *tankChar = new tankCharacterBuilder;
//         dm.setCharacterBuilder(tankChar);
//         dm.constructCharacter();
//         Fighter *test1 = dm.getCharacter();

//         std::cout << "\nHere are the stat allocations based on your build:\n";

//         test1->displayScores1();
//         test1->groupedCalculate();

//         delete tankChar;
//         delete test1;
//         break;
//     }
//     }

//     return 0;
// }