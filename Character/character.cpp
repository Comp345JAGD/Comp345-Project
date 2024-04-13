#include "character.h"
#include "CharacterStrategy.h"



Character::Character() : name("NPC"), level(1), strength(0), dexterity(0), constitution(0), intelligence(0), wisdom(0), charisma(0), Logger("Game_log.txt")
{

}

Character::Character(std::string name) : name(name), level(1), strength(0), dexterity(0), constitution(0), intelligence(0), wisdom(0), charisma(0), Logger("Game_log.txt")
{

}

Character::Character(std::string inputName, int inputStrength, int inputDexterity, int inputConstitution, int inputIntelligence, int inputWisdom, int inputCharisma) : Logger("Game_Log.txt")
{
	name = inputName;
	strength = inputStrength;
	dexterity = inputDexterity;
	constitution = inputConstitution;
	intelligence = inputIntelligence;
	wisdom = inputWisdom;
	charisma = inputCharisma;
	cs = new HumanPlayerStrategy();

	groupCalculateSilent();
}

Character::Character(int level, CharacterStrategy *charStrat) : level(level), strength(8), dexterity(8), constitution(8), intelligence(8), wisdom(8), charisma(8), cs(charStrat), Logger("Game_log.txt")

{	
	this->logAttach(&Logger);
	groupedCalculate();
}

void Character::generateAbilityScore()
{
	std::vector<int> rolls;
	for (int i = 0; i < 6; i++)
		rolls.push_back(dice.roll("1d6"));

	assignAbilityScore(rolls);
}

void Character::assignAbilityScore(const std::vector<int> rolls)
{
	system("CLS");
	for (int i = 0; i < rolls.size(); i++)
	{
		system("CLS");
		std::cout << "Roll number: " << i + 1 << " has value: " << rolls[i] << ". Which stat would you like to increase?\n";

		displayScores1();

		int decision;
		bool validity = false;

		while (!validity)
		{
			std::cout << "Please choose a number corresponding to one of the stats from the table:\n";

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
				std::cin.ignore(256, '\n');
				std::cout << "Invalid input, please enter a number between 1 and 6.\n";
				displayScores1();
			}
		}

		switch (decision)
		{
		case 1:
			std::cout << "Strength has been increased from " << strength << " to ";
			strength += rolls[i];
			std::cout << strength << ".\n";
			continue;
		case 2:
			std::cout << "Dexterity has been increased from " << dexterity << " to ";
			dexterity += rolls[i];
			std::cout << dexterity << ".\n";
			continue;
		case 3:
			std::cout << "Constitution has been increased from " << constitution << " to ";
			constitution += rolls[i];
			std::cout << constitution << ".\n";
			continue;
		case 4:
			std::cout << "Intelligence has been increased from " << intelligence << " to ";
			intelligence += rolls[i];
			std::cout << intelligence << ".\n";
			continue;
		case 5:
			std::cout << "Wisdom has been increased from " << wisdom << " to ";
			wisdom += rolls[i];
			std::cout << wisdom << ".\n";
			continue;
		case 6:
			std::cout << "Charisma has been increased from " << charisma << " to ";
			charisma += rolls[i];
			std::cout << charisma << ".\n";
			continue;
		}
	}
	system("CLS");
	std::cout << "Here are your final stats:\n";
	displayScores2();
}

void Character::addStats(StatType type, int value)
{
	switch (type)
	{
	case lvl:
		level += value;
		std::cout << "Adding " << value << " levels to your character.\n";
		notify(lvl, level);
		break;
	case str:
		strength += value;
		std::cout << "Adding " << value << " strength to your character.\n";
		notify(str, strength);
		break;
	case dex:
		dexterity += value;
		std::cout << "Adding " << value << " dexterity to your character.\n";
		notify(dex, dexterity);
		break;
	case consti:
		constitution += value;
		std::cout << "Adding " << value << " constitution to your character.\n";
		notify(consti, constitution);
		break;
	case intel:
		intelligence += value;
		std::cout << "Adding " << value << " intelligence to your character.\n";
		notify(intel, intelligence);
		break;
	case wis:
		wisdom += value;
		std::cout << "Adding " << value << " wisdom to your character.\n";
		notify(wis, wisdom);
		break;
	case chrm:
		charisma += value;
		std::cout << "Adding " << value << " charisma to your character.\n";
		notify(chrm, charisma);
		break;
	case hp:
		hitPoints += value;
		std::cout << "Adding " << value << " hit points to your character.\n";
		notify(hp, hitPoints);
		break;
	case aClass:
		armorClass += value;
		std::cout << "Adding " << value << " armor class to your character.\n";
		notify(aClass, armorClass);
		break;
	case aBonus:
		attackBonus += value;
		std::cout << "Adding " << value << " attack bonus to your character.\n";
		notify(aBonus, attackBonus);
		break;
	case dBonus:
		damageBonus += value;
		std::cout << "Adding " << value << " damage bonus to your character.\n";
		notify(dBonus, damageBonus);
		break;
	default:
		std::cout << "default.\n";
		break;
	}
}

void Character::displayScores1() const
{
	std::cout << "(1) Strength: " << strength << "\n"
			  << "(2) Dexterity: " << dexterity << "\n"
			  << "(3) Constitution: " << constitution << "\n"
			  << "(4) Intelligence: " << intelligence << "\n"
			  << "(5) Wisdom: " << wisdom << "\n"
			  << "(6) Charisma: " << charisma << std::endl;
}

void Character::displayScores2() const
{
	std::cout << "Strength: " << strength << "\n"
			  << "Dexterity: " << dexterity << "\n"
			  << "Constitution: " << constitution << "\n"
			  << "Intelligence: " << intelligence << "\n"
			  << "Wisdom: " << wisdom << "\n"
			  << "Charisma: " << charisma << "\n\n";
}

void Character::displayScores3() const
{
	std::cout << "Hit Points: " << hitPoints << "\n"
			  << "Armor Class: " << armorClass << "\n"
			  << "Attack Bonus: " << attackBonus << "\n"
			  << "Damage Bonus: " << damageBonus << "\n\n";
}

void Character::setClassType(std::string type)
{
	classType = type;
}

void Character::setStrength(int value)
{
	strength = value;
}

void Character::setDexterity(int value)
{
	dexterity = value;
}

void Character::setConstitution(int value)
{
	constitution = value;
}

void Character::setCharisma(int value)
{
	charisma = value;
}

void Character::setWisdom(int value)
{
	wisdom = value;
}

void Character::setIntelligence(int value)
{
	intelligence = value;
}

void Character::setLevel(int value)
{
	level = value;
}

void Character::setName(std::string userName)
{
	name = userName;
}

std::string Character::getName()
{
	return name;
}

std::string Character::getClassType()
{
	return classType;
}

int Character::getLevel()
{
	return level;
}

int Character::getStrength()
{
	return strength;
}

int Character::getDexterity()
{
	return dexterity;
}

int Character::getConstitution()
{
	return constitution;
}

int Character::getIntelligence()
{
	return intelligence;
}

int Character::getWisdom()
{
	return wisdom;
}

int Character::getCharisma()
{
	return charisma;
}

int Character::getArmorClass()
{
	return armorClass;
}

int Character::getAttackBonus()
{
	return attackBonus;
}

int Character::getDamageBonus()
{
	return damageBonus;
}
void Character::calculateHitPoints()
{
	hitPoints = 10 + (constitution - 10) / 2;
	if (level > 1)
	{
		std::cout << "We will now roll a d10 to calculate your hit point based on your level.\n";
	}

	for (int i = 1; i < level; i++)
	{
		hitPoints += dice.roll("1d6");
	}
	notify(hp, hitPoints);
}

void Character::calculateArmorClass()
{
	armorClass = 5 + (dexterity - 10) / 2;

	notify(aClass, armorClass);
}

void Character::calculateAttackBonus()
{
	attackBonus = 1;
	notify(aBonus, attackBonus);
}

void Character::calculateDamageBonus()
{
	damageBonus = 1;
	notify(dBonus, damageBonus);
}

void Character::groupedCalculate()
{
	calculateHitPoints();
	calculateArmorClass();
	calculateAttackBonus();
	calculateDamageBonus();
	currentHp = hitPoints;
	attackRate = 1 + (level / 5);
}

void Character::groupCalculateSilent()
{
	calculateHitPoints();
	calculateArmorClass();
	calculateAttackBonus();
	calculateDamageBonus();
	currentHp = hitPoints;
	attackRate = 1 + (level / 5);
}

// Map movement functions

bool Character::isWalkable()
{
	return false;
}

vector<string> *Character::getGridRepresentation()
{

	vector<string> *art;

	if (dynamic_cast<HumanPlayerStrategy *>(cs) != nullptr)
	{
		art = new vector<string>(
			{"  (oo) ^",
			 "(-)||__|",
			 R"(   /\  |)",
			 "  ()()  "});
	}
	else
	{
		art = new vector<string>(
			{"   }{  |",
			 "__{><}_+",
			 "   []  |",
			 R"(  /  \  )"});
	}

	return art;
}

void Character::playTurn(GameMap *m)
{
	cs->execute(this, m);
	system("pause");
}

int Character::getTotalStength()
{
	return getStrength();
}
int Character::getTotalDexterity()
{
	return getDexterity();
}
int Character::getTotalConstitution()
{
	return getConstitution();
}
int Character::getTotalIntelligence()
{
	return getIntelligence();
}
int Character::getTotalWisdom()
{
	return getWisdom();
}
int Character::getTotalCharisma()
{
	return getCharisma();
}

int Character::getTotalArmorClass()
{
	return getArmorClass();
}

int Character::getTotalAttackBonus()
{
	return getAttackBonus();
}

int Character::getTotalDamageBonus()
{
	return getDamageBonus();
}
int Character::getHitPoints()
{
	return hitPoints;
}

int Character::getCurrentHealth()
{
	return currentHp;
}

int Character::attack()
{
	int dmg = dice.roll2("1d12") + attackBonus + damageBonus + 1;
	log(this->getName() + " attacked for: " + to_string(dmg) + " damage.");
	return dmg;
}

int Character::attacked(int damage)
{
	int damageTaken = damage - armorClass;
	damageTaken = damageTaken > 0 ? damageTaken : 1;
	currentHp = currentHp - damageTaken;
	log(this->getName() + " took: " + to_string(damageTaken) + " damage and has current HP of: " + to_string(currentHp));
	return damageTaken;
}

CharacterStrategy *Character::getStrategy()
{
	return cs;
}

void Character::setStrategy(CharacterStrategy* strat) {
	cs = strat;
}


void displayCharacters(std::vector<Character*>& characters)
{
	for (int i = 0; i < 8; i++)
	{

		for (int j = 0; j < characters.size(); j++)
		{
			if (j == 0) {

				if (i == 0 || i == 7) {
					std::cout << "+";
				}
				else {
					std::cout << "|";
				}

			}

			if (i == 0 || i == 7) {
				std::cout << "---------------------------+";
			}
			else if (i == 1 || i == 6) {
				std::cout << "                           |";
			}
			else { // i == 2, 3, 4, 5

				vector<string>* art = dynamic_cast<Character*>(characters.at(j))->getGridRepresentation();

				std::cout << "  " << art->at(i - 2) << "   ";

				string info = "";

				if (i == 2) {

					info = characters.at(j)->getName();

				}
				else if (i == 3) {
					info = characters.at(j)->getClassType();
				}
				else if (i == 4) {
					info = "HP: " + std::to_string(characters.at(j)->getCurrentHealth()) + "/" + std::to_string(characters.at(j)->getHitPoints());
				}
				else if (i == 5) {
					info = "Level: " + std::to_string(characters.at(j)->getLevel());

				}

				string padding = "";

				int numPadding = 14 - info.length();

				numPadding = numPadding >= 0 ? numPadding : 0;

				for (int i = 0; i < numPadding; i++)
				{
					padding += " ";
				}

				std::cout << info << padding << "|";

			}

		}
		std::cout << endl;

	}

	std::cout << endl;
}

int Character::getChestEncountered() {
	return chestEncountered;
}

void Character::addChestEncountered() {
	chestEncountered++;
}