#include <limits>
#include "CharacterBuilder.h"

void CharacterBuilder::randomizeStats()
{
	std::cout << "We will now roll for your starting ability scores.\n";
	std::string characterCreation = "Creating a character:\n";
	// charLogPointer->log(characterCreation, 1);
	for (int i = 0; i < randomizedStats.size(); i++)
	{
		std::array<int, 4> rolls;
		for (int j = 0; j < 4; j++)
		{
			rolls[j] = dice.roll2("1d6");
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
		characterCreation = "The stat roll for the " + std::to_string(k + 1) + " stat is: " + std::to_string(randomizedStats[k]) + ".\n";
		// charLogPointer->log(characterCreation, 1);
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

void DungeonMaster::constructCharacter(string classType)
{
	produced_characterBuilder->createCharacter(classType);
	produced_characterBuilder->randomizeStats();
	produced_characterBuilder->build();
}

void DungeonMaster::creationMenu() {
	std::string characterCreationScreen = R"(
                         : === C H A R A C T E R  C R E A T I O N === :
======================================================================================================
     (o.o)                                                                                  (o.o)
      |=|                                                                                    |=|
     |                                                                                  |
   //.=|=.\                                                                              //.=|=.\
  // .=|=. \       ██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗       // .=|=. \
  \ .=|=. //       ██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝       \ .=|=. // 
   \(=)//        ██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗          \(=)//
    (:| |:)         ██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝           (:| |:)
                ╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗            
     () ()           ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝          () () 
                                                                                         
                                                                                         
    ==' '==                                                                                ==' '==
======================================================================================================
)";

	std::cout << characterCreationScreen << std::endl;

	return 0;

	int decision;
	bool validity = false;

	// Class selection. For now, only Fighter class option implemented.

	while (!validity)
	{
		cout << "1. Scientist 2. Doctor 3. Fighter\n"
			<< "4. Paladin, 5. Rogue, 6. Archer\n";

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

	switch (decision)
	{
	case 1:
		cout << "Scientist has no been implemented yet, sorry!\n";
		break;
	case 2:
		cout << "Doctor has not been implemented yet, sorry!\n";
		break;
	case 3:
	{
		cout << "Good choice! Now creating your fighter..." << "\n";
		constructCharacter("Fighter");
		break;
	}
	case 4:
		cout << "Paladin has not been implemented yet, sorry!\n";
		break;
	case 5:
		cout << "Rogue has not been implemented yet, sorry!\n";
		break;
	case 6:
		cout << "Archer has not been implemented yet, sorry!\n";
		break;
	}
}