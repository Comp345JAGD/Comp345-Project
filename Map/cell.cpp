#include "cell.h"

bool EmptyCell::isWalkable()
{
    return true;
}

void EmptyCell::playTurn(GameMap* map)
{
    // nothing
}

bool WallCell::isWalkable()
{
    return false;
}

void WallCell::playTurn(GameMap* map)
{
    // nothing
}
