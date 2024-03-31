#include "cell.h"
#include "gameMap.h"

bool EmptyCell::isWalkable()
{
    return true;
}

// 8x4

vector<string>* EmptyCell::getGridRepresentation()
{
    vector<string>* art = new vector<string>(
        { 
            "        ", 
            "        ", 
            "        ",
            "        "
        }
    );
    return art;
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

vector<string>* WallCell::getGridRepresentation()
{
    vector<string>* art = new vector<string>(
        {
            "########",
            "########",
            "########",
            "########"
        }
    );
    return art;
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

vector<string>* MoverCell::getGridRepresentation()
{
    vector<string>* art = new vector<string>(
        {
            "mm mm mm",
            "mm mm mm",
            "mm mm mm",
            "mm mm mm"
        }
    );
    return art;
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

