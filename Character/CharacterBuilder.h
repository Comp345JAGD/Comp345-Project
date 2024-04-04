#ifndef CHARACTERBUILDER_H
#define CHARACTERBUILDER_H

#include "fighter.h"
#include <array>
#include <algorithm>
#include "dice.h"
#include <limits>
#include <fstream>
#include <sstream>
// #include "Logger.h"
// #include "logSubject.h"

class CharacterBuilder
{
public:
    Character *getCharacter() { return produced_character; }
    void createCharacter(string characterType, string name)
    {
        if (characterType._Equal("Fighter")) 
            produced_character = new Fighter(name);
        else
            produced_character = new Character(name);
        /*Character *tempCharPointer = static_cast<Character*>(produced_character);
        Logger *charLogPointer = new Logger(tempCharPointer);
        Logger *diceLogPointer = new Logger(&(produced_character->getDice()));*/
    }
    void randomizeStats();
    virtual void build() = 0;

protected:
    Dice dice;
    Character *produced_character;
    // Logger *charLogPointer;
    // Logger *diceLogPointer;
    std::array<int, 6> randomizedStats;
};

class nimbleCharacterBuilder : public CharacterBuilder
{
public:
    void build() override;
};

class bullyCharacterBuilder : public CharacterBuilder
{
public:
    void build() override;
};

class tankCharacterBuilder : public CharacterBuilder
{
public:
    void build() override;
};

#endif // CHARACTERBUILDER_H