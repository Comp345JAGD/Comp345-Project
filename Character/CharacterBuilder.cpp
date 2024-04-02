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
	system("CLS");

	std::string characterCreationScreen = R"(
                         : === C H A R A C T E R  C R E A T I O N === :
======================================================================================================
     (o.o)                                                                                  (o.o)
      |=|                                                                                    |=|
     __|__                                                                                  __|__    
   //.=|=.\\                                                                              //.=|=.\\	
  // .=|=. \\       ██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗       // .=|=. \\
  \\ .=|=. //       ██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝       \\ .=|=. // 
   \\(_=_)//        ██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗          \\(_=_)//
    (:| |:)         ██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝           (:| |:)
     || ||          ╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗          || || 
     () ()           ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝          () () 
     || ||                                                                                  || ||
     || ||                                                                                  || ||  
    ==' '==                                                                                ==' '==
======================================================================================================
)";

	std::cout << characterCreationScreen << "\n\n\n";

	int decision;
	bool validity = false;

	// Class selection. For now, only Fighter class option implemented.

	while (!validity)
	{
		cout << "What class would you like your character to be? Selection an option from 1-4.\n";

		std::string characterSelectionScreen = R"(
1. FIGHTER      2. Magician      3. Hunter       4. Priest
   (oo) ^           (oo)*+*       ▲ (oo) ▲        (oo) +
 (-)||__|          __||__|         |__||__|        //||\\|
    /\  |           /  \ |         *  /\  *          /\  |
   ()()            /____\|           ()()           /__\ |
)";

		std::cout << characterSelectionScreen << std::endl;

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

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	string inputName;
	cout << "Please enter a name for your character: ";
	std::getline(std::cin, inputName);

	int decision2;
	bool validity2 = false;
	CharacterBuilder* chosenBuild;
	Character* myChar;

	while (!validity2)
	{
		std::cout << "What build type would you like your character to implement?\n\n";
		std::cout << "1. Nimble: favors dexterity and armor class to evade blows\n";
		std::cout << "2. Bully: uses brute strength to destroy his enemies\n";
		std::cout << "3. Tank: favors survival by more hit points through high constitution score\n";

		if (std::cin >> decision2)
		{
			if (decision2 >= 1 && decision2 <= 3)
				validity2 = true;
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

	switch (decision2)
	{
	case 1:
	{
		std::cout << "You have chosen the Nimble build.\n";
		chosenBuild = new nimbleCharacterBuilder;
		setCharacterBuilder(chosenBuild);
		// constructCharacter();
		// Character* test1 = dm.getCharacter();

		//std::cout << "Here are the stat allocations based on your build:\n";

		//test1->displayScores1();
		//test1->groupedCalculate();

		break;
	}
	case 2:
	{
		std::cout << "You have chosen the Bully build.\n";
		chosenBuild = new bullyCharacterBuilder;
		setCharacterBuilder(chosenBuild);

		break;
	}
	case 3:
	{
		std::cout << "You have chosen the Tank build.\n";
		chosenBuild = new tankCharacterBuilder;
		setCharacterBuilder(chosenBuild);

		break;
	}
	}

	switch (decision)
	{
	case 1:
		cout << "Good choice! Now creating your fighter..." << "\n";
		constructCharacter("Fighter");
		myChar = getCharacter();

		std::cout << "Here are the stat allocations based on your build:\n";

		myChar->displayScores1();
		myChar->groupedCalculate();
		break;
	case 2:
		cout << "Magician has not been implemented yet, sorry!\n";
		break;
	case 3:
	{
		cout << "Hunter has not been implemented yet, sorry!\n";
		break;
	}
	case 4:
		cout << "Priest has not been implemented yet, sorry!\n";
		break;
	}
}