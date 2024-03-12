#include "cell.h"

bool EmptyCell::isWalkable()
{
    return true;
}

bool WallCell::isWalkable()
{
    return false;
}

bool StartCell::isWalkable()
{
    return true;
}

bool EndCell::isWalkable()
{
    return true;
}
