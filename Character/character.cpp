#include "character.h"

Character::Character() : level(1), strength(0), dexterity(0), constitution(0), intelligence(0), wisdom(0), charisma(0)
{
}

Character::Character(const std::string &inputName, int inputLevel) : name(inputName), level(inputLevel), strength(8), dexterity(8), constitution(8), intelligence(8), wisdom(8), charisma(8)
{
    generateAbilityScore();
}

Character::Character(int npcCode, int level) : level(level), strength(8), dexterity(8), constitution(8), intelligence(8), wisdom(8), charisma(8)
{
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
              << "Charisma: " << charisma << std::endl;
}

void Character::displayScores3() const
{
    std::cout << "Hit Points: " << hitPoints << "\n"
              << "Armor Class: " << armorClass << "\n"
              << "Attack Bonus: " << attackBonus << "\n"
              << "Damage Bonus: " << damageBonus << "\n\n";
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
    armorClass = 10 + (dexterity - 10) / 2;

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

// Map movement functions

bool Character::isWalkable()
{
    return false;
}

string Character::getGridRepresentation()
{
    return "C";
}

void Character::playTurn(GameMap *m)
{
    // m->moveOneCellTowardsTarget();
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
    int dmg = 0;
    dmg = dice.roll2("1d12") + attackBonus + damageBonus;
    return dmg;
}

int Character::attacked(int damage)
{
    int damageTaken = damage - armorClass;
    currentHp = currentHp - damageTaken;

    return damageTaken;
}