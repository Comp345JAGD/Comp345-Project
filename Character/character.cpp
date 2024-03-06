#include "character.h"

Character::Character(const std::string &inputName, int inputLevel) : name(inputName), level(inputLevel), strength(8), dexterity(8), constitution(8), intelligence(8), wisdom(8), charisma(8)
{
    generateAbilityScore();
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
    for (int i = 0; i < rolls.size(); i++)
    {
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
    std::cout << "Here are your final stats:\n";
    displayScores2();
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
              << "Charisma: " << charisma << std::endl;
}