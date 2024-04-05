#include "DungeonMaster.h"

void DungeonMaster::constructCharacter(string classType, string name)
{
	produced_characterBuilder->createCharacter(classType, name);
	produced_characterBuilder->randomizeStats();
	produced_characterBuilder->build();
}

std::unique_ptr<Character> DungeonMaster::createCharType(std::string classType, std::string name, int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma)
{
	if (classType == "Fighter")
		return std::make_unique<Fighter>(name, strength, dexterity, constitution, intelligence, wisdom, charisma);
	else if (classType == "Archer")
		return std::make_unique<Archer>(name, strength, dexterity, constitution, intelligence, wisdom, charisma);
	else if (classType == "Hunter")
		return std::make_unique<Hunter>(name, strength, dexterity, constitution, intelligence, wisdom, charisma);
	else if (classType == "Doctor")
		return std::make_unique<Doctor>(name, strength, dexterity, constitution, intelligence, wisdom, charisma);
	else
		return nullptr;
}

void DungeonMaster::saveCharacter(Character* character)
{
	std::ofstream file("createdCharacters.txt", std::ios::app);
	if (file.is_open())
	{
		if (character != nullptr)
		{
			file << "Class: " << character->getClassType() << "\n";
			file << "Name: " << character->getName() << "\n";
			file << "Strength: " << character->getStrength() << "\n";
			file << "Dexterity: " << character->getDexterity() << "\n";
			file << "Constitution: " << character->getConstitution() << "\n";
			file << "Intelligence: " << character->getIntelligence() << "\n";
			file << "Wisdom: " << character->getWisdom() << "\n";
			file << "Charisma: " << character->getCharisma() << "\n";
			file << "---"
				<< "\n";
		}
	}
	else
	{
		std::cerr << "Error, file not open.\n";
	}

	file.close();
}

std::vector<std::unique_ptr<Character>> DungeonMaster::loadCharacters()
{
	std::vector<std::unique_ptr<Character>> loadedCharacters;
	std::ifstream file("createdCharacters.txt");
	std::string line, name, classType;
	int stats[6] = { 0 };
	int statsIndex = 0;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			if (line.substr(0, 4) == "Name")
			{
				name = line.substr(line.find(":") + 2);
				continue;
			}
			else if (line.substr(0, 5) == "Class")
			{
				classType = line.substr(line.find(":") + 2);
				continue;
			}
			if (line == "---")
			{
				loadedCharacters.push_back(createCharType(classType, name, stats[0], stats[1], stats[2], stats[3], stats[4], stats[5]));
				statsIndex = 0;
				continue;
			}
			std::istringstream iss(line.substr(line.find(":") + 2));
			iss >> stats[statsIndex++];
		}
	}
	else
	{
		std::cerr << "Error opening file for reading.\n";
	}
	file.close();

	return loadedCharacters;
}

void DungeonMaster::displayCharacters(std::vector<std::unique_ptr<Character>>& characters) {
	for (int i = 0; i < characters.size(); i++) {
		std::cout << i + 1 << ".   " << "Class Type: " << characters[i]->getClassType() << ", Name: " << characters[i]->getName() << std::endl;
	}
}

Character* DungeonMaster::creationMenu()
{
	system("CLS");

	std::string characterCreationScreen = R"(
                         : === C H A R A C T E R  C R E A T I O N === :
======================================================================================================
      .-.                                                                                      .-.     
     (o.o)                                                                                    (o.o)     
      |=|                                                                                      |=|     
     __|__   ____    __    ____  _______  __        ______   ______   .___  ___.  _______     __|__  
   //.=|=.\\ \   \  /  \  /   / |   ____||  |      /      | /  __  \  |   \/   | |   ____|  //.=|=.\\ 
  // .=|=. \\ \   \/    \/   /  |  |__   |  |     |  ,----'|  |  |  | |  \  /  | |  |__    // .=|=. \\   
  \\ .=|=. //  \            /   |   __|  |  |     |  |     |  |  |  | |  |\/|  | |   __|   \\ .=|=. //  
   \\(_=_)//	\    /\    /    |  |____ |  `----.|  `----.|  `--'  | |  |  |  | |  |____   \\(_=_)// 
    (:| |:)      \__/  \__/     |_______||_______| \______| \______/  |__|  |__| |_______|   (:| |:)   
     || ||                                                                                    || ||    
     () ()                                                                                    () ()    
     || ||                                                                                    || ||
     || ||                                                                                    || ||    
    ==' '==                                                                                  ==' '==    
=======================================================================================================
)";

	std::cout << characterCreationScreen << "\n\n\n";

	int decision;
	bool validity = false;

	// Class selection. For now, only Fighter class option implemented.

	while (!validity)
	{
		cout << "What class would you like your character to be? Selection an option from 1-4.\n";

		std::string characterSelectionScreen = R"(
1. FIGHTER      2. Doctor        3. Hunter       4. Archer
   (oo) ^           (oo) O         ^ (oo) ^         (oo) ^
 (-)||__|          __||__|         |__||__|        //||\\|
    /\  |           /  \           *  /\  *          /\  *
   ()()            /____\            ()()           /__\ 
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

		// std::cout << "Here are the stat allocations based on your build:\n";

		// test1->displayScores1();
		// test1->groupedCalculate();

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
		cout << "Good choice! Now creating your fighter..."
			<< "\n";
		constructCharacter("Fighter", inputName);
		break;
	case 2:
		cout << "Good choice! Now creating your Doctor..."
			<< "\n";
		constructCharacter("Doctor", inputName);
		break;
	case 3:
	{
		cout << "Good choice! Now creating your hunter..."
			<< "\n";
		constructCharacter("Hunter", inputName);
		break;
	}
	case 4:
		cout << "Good choice! Now creating your Archer..."
			<< "\n";
		constructCharacter("Archer", inputName);
		break;
	}

	myChar = getCharacter();

	std::cout << "\nHere are the stat allocations based on your build:\n\n";

	myChar->displayScores2();
	myChar->groupedCalculate();

	return myChar;
}
