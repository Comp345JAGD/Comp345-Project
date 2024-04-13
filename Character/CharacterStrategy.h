#include "character.h"
#include "../Map/GameMap.h"
#include"../Item/Item.h"

#ifndef CHARACTERSTRATEGY_H
#define CHARACTERSTRATEGY_H

class CharacterStrategy
{
public:
    virtual ~CharacterStrategy() = default;
    virtual void execute(Character *character, GameMap *map) = 0;
};

class FriendlyStrategy : public CharacterStrategy
{
public:
    void execute(Character* character, GameMap* map) override;
};

class AggressorStrategy : public CharacterStrategy
{
public:
    void execute(Character *c, GameMap *m) override;
};

class HumanPlayerStrategy : public CharacterStrategy
{
public:
       
    void execute(Character *character, GameMap *map) override;
};

#endif // CHARACTERSTRATEGY_H