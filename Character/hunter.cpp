#include "hunter.h"

Hunter::Hunter(std::string name) : Character(name)
{
    setClassType("Hunter");
}

Hunter::Hunter(std::string inputName, int inputStrength, int inputDexterity, int inputConstitution, int inputIntelligence, int inputWisdom, int inputCharisma) : Character(inputName, inputStrength, inputDexterity, inputConstitution, inputIntelligence, inputWisdom, inputCharisma)
{
    setClassType("Hunter");
}

void Hunter::addHunterBonus()
{
    std::cout << "Because you have selected the Hunter class, you get 2 bonus dexterity and 1 bonus strength!\n";

    dexterity += 2;
    strength += 1;

    std::cout << "Here are now your final Archer stats:\n\n";
    displayScores2();
}

void Hunter::groupedCalculate()
{
    addHunterBonus();
    Character::groupedCalculate();

    std::cout << "Here are your class bonuses:\n";
    displayScores3();
}

vector<string>* Hunter::getGridRepresentation()
{

	vector<string>* art;

    art = new vector<string>(
        { 
         "^ (oo) ^",
         "|__||__|",
       R"(*  /\  *)",
         "  ()()  " });

	return art;
}