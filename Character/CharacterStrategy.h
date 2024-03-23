#ifndef CHARACTERSTRATEGY_H
#define CHARACTERSTRATEGY_H

#include "character.h"
#include "../Map/GameMap.h"

class CharacterStrategy
{
public:
    virtual ~CharacterStrategy() = default;
    virtual void execute(Character *character, GameMap *map) = 0;
};

class FriendlyStrategy : public CharacterStrategy
{
    void execute(Character *c, GameMap *m) override;
};

class AggressorStrategy : public CharacterStrategy
{
    void execute(Character *c, GameMap *m) override;
};

class HumanPlayerStrategy : public CharacterStrategy
{
    void execute(Character *character, GameMap *map) override;
};

#endif // CHARACTERSTRATEGY_H