#include "CharacterBuilder.h"

void CharacterBuilder::randomizeStats()
{
	std::cout << "We will now roll for your starting ability scores.\n";
	// std::string characterCreation = "Creating a character:\n";
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
		// characterCreation = "The stat roll for the " + std::to_string(k + 1) + " stat is: " + std::to_string(randomizedStats[k]) + ".\n";
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
