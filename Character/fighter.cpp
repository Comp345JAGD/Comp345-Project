#include "fighter.h"

Fighter::Fighter(std::string name) : Character(name)
{
	setClassType("Fighter");
}

Fighter::Fighter(std::string inputName, int inputStrength, int inputDexterity, int inputConstitution, int inputIntelligence, int inputWisdom, int inputCharisma) : Character(inputName, inputStrength, inputDexterity, inputConstitution, inputIntelligence, inputWisdom, inputCharisma)
{
	setClassType("Fighter");
}

void Fighter::addFighterBonus()
{
	std::cout << "Because you have selected the Fighter class, you get 2 bonus strength and 1 bonus dexterity!\n";

	strength += 2;
	dexterity += 1;

	std::cout << "Here are now your final Fighter stats:\n\n";
	displayScores2();
}

void Fighter::addFighterBonusSilent() {
	strength += 2;
	dexterity += 1;
}

void Fighter::calculateHitPoints()
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

void Fighter::calculateArmorClass()
{
	armorClass = 10 + (dexterity - 10) / 2;

	notify(aClass, armorClass);
}

void Fighter::calculateAttackBonus()
{
	attackBonus = 1;
	notify(aBonus, attackBonus);
}

void Fighter::calculateDamageBonus()
{
	damageBonus = 1;
	notify(dBonus, damageBonus);
}

void Fighter::groupedCalculate()
{
	addFighterBonus();
	Character::groupedCalculate();

	std::cout << "Here are your class bonuses:\n";
	displayScores3();
}

void Fighter::groupCalculateSilent() {
	addFighterBonusSilent();
	Character::groupCalculateSilent();
}


vector<string>* Fighter::getGridRepresentation()
{

	vector<string>* art;

	art = new vector<string>(
		{ "  (oo) ^",
		  "(-)||__|",
		R"(   /\  |)",
		  "  ()()  " });

	return art;
}