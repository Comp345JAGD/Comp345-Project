#include "fighter.h"

Fighter::Fighter(const std::string &inputName, int inputLevel) : Character(inputName, inputLevel)
{
    bool validity3 = false;
    char proceed = '\0';

    std::cout << "When you are ready, we will proceed with your class bonuses and other calculations.\n";
    std::cout << "Press y if you are ready to proceed\n";
    while (!validity3)
    {
        if (std::cin >> proceed)
        {
            if (proceed == 'y')
                validity3 = true;
            else
                std::cout << "You may not proceed until you select 'y'.\n";
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cout << "You may not proceed until you select 'y'.\n";
        }
    }

    groupedCalculate();
}

void Fighter::addFighterBonus()
{
    std::cout << "\nBecause you have selected the Fighter class, you get 2 bonus strength and 1 bonus dexterity!\n";

    strength += 2;
    dexterity += 1;

    std::cout << "Here are now your final Fighter stats:\n";
    displayScores2();
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

    std::cout << "Your hit point is: " << hitPoints << ".\n";
}

void Fighter::calculateArmorClass()
{
    armorClass = 10 + (dexterity - 10) / 2;

    std::cout << "Your dexterity is is: " << dexterity << ".\n";
}

void Fighter::calculateAttackBonus()
{
    std::cout << "Attack bonus is unimplemented for now, set to default 1.\n";
    attackBonus = 1;
}

void Fighter::calculateDamageBonus()
{
    std::cout << "Damage bonus is unimplemented for now, set to default 1.\n";
    damageBonus = 1;
}

void Fighter::groupedCalculate()
{
    addFighterBonus();
    calculateHitPoints();
    calculateArmorClass();
    calculateAttackBonus();
    calculateDamageBonus();
}