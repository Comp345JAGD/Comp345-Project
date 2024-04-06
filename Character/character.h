#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <stdlib.h>
#include <limits>
#include "dice.h"
#include "Subject.h"
#include "../GameLogger.h"
#include "../GameFileWriter.h"
// #include "CharacterStrategy.h"
#include "../Map/cell.h"

class CharacterStrategy; // https://stackoverflow.com/a/15782499

class Character : public Subject, public IGridCell , public GameLogger
{
public:
    Character();
    Character(std::string name);
    Character(const std::string &inputName, int inputLevel);
    Character(std::string name, int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma);
    Character(int level, CharacterStrategy *charStrat);
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
    virtual void groupCalculateSilent();
    void addStats(StatType type, int value);
    void setName(std::string name);
    void setStrength(int value);
    void setDexterity(int value);
    void setConstitution(int value);
    void setIntelligence(int value);
    void setWisdom(int value);
    void setCharisma(int value);
    void setLevel(int value);
    void setStrategy(CharacterStrategy* strat);
    void setClassType(std::string type);
    std::string getName();
    int getLevel();
    int getStrength();
    int getDexterity();
    int getConstitution();
    int getIntelligence();
    int getWisdom();
    int getCharisma();
    int getArmorClass();
    int getAttackBonus();
    int getDamageBonus();
    int getHitPoints();
    int getCurrentHealth();
    std::string getClassType();
    Dice getDice()
    {
        return dice;
    }
    virtual int getTotalStength();
    virtual int getTotalDexterity();
    virtual int getTotalConstitution();
    virtual int getTotalIntelligence();
    virtual int getTotalWisdom();
    virtual int getTotalCharisma();
    virtual int getTotalArmorClass();
    virtual int getTotalAttackBonus();
    virtual int getTotalDamageBonus();
    virtual CharacterStrategy *getStrategy();
    virtual bool isWalkable() override;
    virtual void playTurn(GameMap *map) override;
    virtual vector<string> *getGridRepresentation() override;
    // virtual void setPosition(int row, int column) override;
    int attack();
    int attacked(int damage);

protected:
    int level = 1;
    int strength, dexterity, constitution, intelligence, wisdom, charisma;
    int hitPoints, armorClass, attackBonus, damageBonus;
    int currentHp, attackRate;
    Dice dice;
    CharacterStrategy *cs;
    std::string name;
    std::string classType;
    GameFileWriter Logger;
};

void displayCharacters(std::vector<Character*>& characters);

#endif // CHARACTER_H