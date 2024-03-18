#include "cell.h"

bool EmptyCell::isWalkable()
{
    return true;
}

string EmptyCell::getGridRepresentation()
{
    return "O";
}

void EmptyCell::playTurn(GameMap* map)
{
    // nothing
}

bool WallCell::isWalkable()
{
    return false;
}

string WallCell::getGridRepresentation()
{
    return "W";
}

void WallCell::playTurn(GameMap* map)
{
    // nothing
}
