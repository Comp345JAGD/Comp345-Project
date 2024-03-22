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

#endif // CHARACTERSTRATEGY_H