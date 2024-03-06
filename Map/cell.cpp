#include "cell.h"

bool EmptyCell::isWalkable()
{
    return true;
};

bool WallCell::isWalkable()
{
    return false;
};