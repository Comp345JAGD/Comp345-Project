#include "archer.h"

Archer::Archer(std::string name) : Character(name)
{
    setClassType("Archer");
}

Archer::Archer(std::string inputName, int inputStrength, int inputDexterity, int inputConstitution, int inputIntelligence, int inputWisdom, int inputCharisma) : Character(name, strength, dexterity, constitution, intelligence, wisdom, charisma)
{
    setClassType("Archer");
}

void Archer::addArcherBonus()
{
    std::cout << "Because you have selected the Archer class, you get 2 bonus dexterity and 1 bonus charisma!\n";

    dexterity += 2;
    charisma += 1;

    std::cout << "Here are now your final Archer stats:\n\n";
    displayScores2();
}

void Archer::groupedCalculate()
{
    addArcherBonus();
    Character::groupedCalculate();

    std::cout << "Here are your class bonuses:\n";
    displayScores3();
}