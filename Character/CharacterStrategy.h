#ifndef CHARACTERSTRATEGY_H
#define CHARACTERSTRATEGY_H

#include "character.h"
#include "../Map/GameMap.h"

class CharacterStrategy
{
public:
    virtual ~CharacterStrategy() = default;
    virtual void move(Character &character) = 0;
    virtual void attack(Character &character) = 0;
    virtual void freeAction(Character &character) = 0;
    virtual void execute(Character *character, GameMap *map) = 0;
};

class HumanPlayerStrategy : public CharacterStrategy
{
public:
    void move(Character &character) override
    {
        // Implement player-controlled movement logic
    }
    void attack(Character &character) override
    { // Implement player-controlled attack logic
    }
    void freeAction(Character &character) override
    {
        // Implement player-controlled free actions logic
    }
};

class AggressorStrategy : public CharacterStrategy
{
public:
    void move(Character &character) override
    {
        // Implement aggressive movement logic towards the player character
    }
    void attack(Character &character) override
    {
        // Implement aggressive attack logic towards the player character
    }
    void freeAction(Character &character) override
    {
        // Implement any free actions an aggressive character might take
    }
};

class FriendlyStrategy : public CharacterStrategy
{
public:
    void move(Character &character) override
    {
        // Implement friendly movement logic towards the character
    }
    void attack(Character &character) override
    {
        // Implement logic for attacking only if attacked (switch to AggressorStrategy)
    }
    void freeAction(Character &character) override
    {
        // Implement any free actions a friendly character might take
    }
};

#endif // CHARACTERSTRATEGY_H