#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <stdlib.h>
#include "dice.h"
#include "Subject.h"

class Character : public Subject
{
public:
    Character();
    Character(const std::string &inputName, int inputLevel);
    void generateAbilityScore();
    void assignAbilityScore(const std::vector<int> rolls);
    void displayScores1() const;
    void displayScores2() const;
    void displayScores3() const;
    virtual void calculateHitPoints() = 0;
    virtual void calculateArmorClass() = 0;
    virtual void calculateAttackBonus() = 0;
    virtual void calculateDamageBonus() = 0;
    void addStats(StatType type, int value);
    void setStrength(int value);
    void setDexterity(int value);
    void setConstitution(int value);
    void setIntelligence(int value);
    void setWisdom(int value);
    void setCharisma(int value);
    void setLevel(int value);

protected:
    int level;
    int strength, dexterity, constitution, intelligence, wisdom, charisma;
    int hitPoints, armorClass, attackBonus, damageBonus;
    Dice dice;
    std::string name;
};

#endif // CHARACTER_H