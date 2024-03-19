#include "cell.h"
#include "gameMap.h"

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

void EmptyCell::setPosition(int row, int column)
{
    this->row = row;
    this->column = column;
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

void WallCell::setPosition(int row, int column)
{
    this->row = row;
    this->column = column;
}


bool MoverCell::isWalkable()
{
    return false;
}

string MoverCell::getGridRepresentation()
{
    return "M";
}

void MoverCell::playTurn(GameMap* map)
{
    // move towards end
    map->moveOneCellTowardsTarget(this->row, this->column, map->getEndRow(), map->getEndColumn());
}

void MoverCell::setPosition(int row, int column)
{
    this->row = row;
    this->column = column;
}

