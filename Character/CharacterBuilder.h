#ifndef CHARACTERBUILDER_H
#define CHARACTERBUILDER_H

#include "fighter.h"
#include <array>
#include <algorithm>
#include "dice.h"

class CharacterBuilder
{
public:
    Character *getCharacter() { return produced_character; }
    void createFighter() { produced_character = new Fighter(); }
    void randomizeStats();
    virtual void build() = 0;

protected:
    Character *produced_character;
    std::array<int, 6> randomizedStats;
    Dice dice;
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

class DungeonMaster // Director Class
{
public:
    void setCharacterBuilder(CharacterBuilder *cb)
    {
        produced_characterBuilder = cb;
    }
    Character *getCharacter()
    {
        return produced_characterBuilder->getCharacter();
    }
    void constructCharacter();

private:
    CharacterBuilder *produced_characterBuilder;
};

#endif // CHARACTERBUILDER_H