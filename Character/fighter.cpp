#include "fighter.h"

Fighter::Fighter() : Character()
{
}

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

    system("CLS");
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
    calculateHitPoints();
    calculateArmorClass();
    calculateAttackBonus();
    calculateDamageBonus();

    std::cout << "Here are your class bonuses:\n";
    displayScores3();
}
