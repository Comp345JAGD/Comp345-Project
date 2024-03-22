#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <stdlib.h>
#include <limits>
#include "dice.h"
#include "Subject.h"
#include "../Map/cell.h"

class Character : public Subject, public IGridCell
{
public:
    Character();
    Character(const std::string &inputName, int inputLevel);
    Character(int npcCode, int level);
    void generateAbilityScore();
    void assignAbilityScore(const std::vector<int> rolls);
    void displayScores1() const;
    void displayScores2() const;
    void displayScores3() const;
    virtual void calculateHitPoints();
    virtual void calculateArmorClass();
    virtual void calculateAttackBonus();
    virtual void calculateDamageBonus();
    virtual void groupedCalculate();
    void addStats(StatType type, int value);
    void setStrength(int value);
    void setDexterity(int value);
    void setConstitution(int value);
    void setIntelligence(int value);
    void setWisdom(int value);
    void setCharisma(int value);
    void setLevel(int value);
    int getStrength();
    int getDexterity();
    int getConstitution();
    int getIntelligence();
    int getWisdom();
    int getCharisma();
    Dice getDice()
    {
        return dice;
    }
    virtual int getGearStength();
    virtual int getGearDexterity();
    virtual int getGearConstitution();
    virtual int getGearIntelligence();
    virtual int getGearWisdom();
    virtual int getGearCharisma();
    virtual bool isWalkable() override;
    virtual void playTurn(GameMap *map) override;
    virtual string getGridRepresentation() override;
    virtual void setPosition(int row, int column) override;

protected:
    int level;
    int strength, dexterity, constitution, intelligence, wisdom, charisma;
    int hitPoints, armorClass, attackBonus, damageBonus;
    int currentHp, attackRate;
    Dice dice;
    std::string name;
};

#endif // CHARACTER_H