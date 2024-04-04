#include "magician.h"

Magician::Magician(std::string name) : Character(name)
{
    setClassType("Magician");
}

Magician::Magician(std::string inputName, int inputStrength, int inputDexterity, int inputConstitution, int inputIntelligence, int inputWisdom, int inputCharisma) : Character(name, strength, dexterity, constitution, intelligence, wisdom, charisma)
{
    setClassType("Magician");
}

void Magician::addMagicianBonus()
{
    std::cout << "Because you have selected the Magician class, you get 2 bonus intelligence and 1 bonus wisdom!\n";

    intelligence += 2;
    wisdom += 1;

    std::cout << "Here are now your final Magician stats:\n\n";
    displayScores2();
}

void Magician::groupedCalculate()
{
    addMagicianBonus();
    Character::groupedCalculate();

    std::cout << "Here are your class bonuses:\n";
    displayScores3();
}