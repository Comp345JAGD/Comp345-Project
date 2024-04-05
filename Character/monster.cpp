#include "monster.h"
#include "CharacterStrategy.h"

Monster::Monster(std::string monsterName) {

	name = monsterName;

	if (monsterName == "Goblin") {
		strength = 3;
		dexterity = 3;
		constitution = 2;
		intelligence = 1;
		wisdom = 1;
		charisma = 1;
		cs = new FriendlyStrategy();

		groupCalculateSilent();
	}
	else if (monsterName == "Insect") {
		strength = 4;
		dexterity = 3;
		constitution = 3;
		intelligence = 1;
		wisdom = 1;
		charisma = 1;
		cs = new AggressorStrategy();

		groupCalculateSilent();
	}
	else if (monsterName == "Goblin Enforcer") {
		strength = 5;
		dexterity = 4;
		constitution = 5;
		intelligence = 1;
		wisdom = 1;
		charisma = 1;
		cs = new FriendlyStrategy();

		groupCalculateSilent();
	}
	else if (monsterName == "Adam the Strong") {
		strength = 12;
		dexterity = 6;
		constitution = 8;
		intelligence = 8;
		wisdom = 8;
		charisma = 8;
		cs = new FriendlyStrategy();

		groupCalculateSilent();
	}
	else if (monsterName == "John the Prankster") {
		strength = 7;
		dexterity = 8;
		constitution = 11;
		intelligence = 11;
		wisdom = 11;
		charisma = 11;
		cs = new FriendlyStrategy();

		groupCalculateSilent();
	}
	else if (monsterName == "David the Dragonknight") {
		strength = 7;
		dexterity = 15;
		constitution = 10;
		intelligence = 6;
		wisdom = 6;
		charisma = 15;
		cs = new FriendlyStrategy();

		groupCalculateSilent();
	}
	else {
		strength = 7;
		dexterity = 15;
		constitution = 10;
		intelligence = 6;
		wisdom = 6;
		charisma = 15;
		cs = new FriendlyStrategy();

		groupCalculateSilent();
	}

	string classString = "";
	
	if (dynamic_cast<HumanPlayerStrategy*>(this->getStrategy()) != nullptr) {
		classString = "Human Player";
	}
	else if (dynamic_cast<FriendlyStrategy*>(this->getStrategy()) != nullptr) {
		classString = "Friendly";
	}
	else if (dynamic_cast<AggressorStrategy*>(this->getStrategy()) != nullptr) {
		classString = "Aggressor";
	}
	else {
		classString = "???";
	}

	classType = classString;
					
}

vector<string>* Monster::getGridRepresentation()
{

	vector<string>* art;

	if (name == "Insect")
	{
		art = new vector<string>(
			{
				R"( \ /\ / )",
				R"( \{==}/ )",
				R"(   ()   )",
				R"( /{OO}\ )",
			}
		);
	}
	else
	{
		art = new vector<string>(
			{ "   }{  |",
			 "__{><}_+",
			 "   []  |",
			 R"(  /  \  )" });
	}

	return art;
}