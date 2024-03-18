#include "cell.h"
#include "gameMap.h"
#include <stdexcept>

// private
bool GameMap::dfsCanGetMapEnd(int row, int column, bool **isVisited)
{
    if (isOutOfBounds(row, column) || isVisited[row][column] || !grid[row][column]->isWalkable())
    {
        return false;
    }

    if (row == endRow && column == endColumn)
    {
        return true;
    }

    isVisited[row][column] = true;

    // up
    bool isUp = dfsCanGetMapEnd(row - 1, column, isVisited);
    // down
    bool isDown = dfsCanGetMapEnd(row + 1, column, isVisited);
    // left
    bool isLeft = dfsCanGetMapEnd(row, column - 1, isVisited);
    // right
    bool isRight = dfsCanGetMapEnd(row, column + 1, isVisited);

    return isUp || isDown || isLeft || isRight;
}
bool GameMap::isOutOfBounds(int row, int column)
{
    if (row < 0 || column < 0)
    {
        return true;
    }

    if (row >= numRows || column >= numColumns)
    {
        return true;
    }

    return false;
};

// public
GameMap::GameMap(
    int numRows,
    int numColumns,
    int startRow,
    int startColumn,
    int endRow,
    int endColumn)
{
    this->numRows = numRows;
    this->numColumns = numColumns;

    if (isOutOfBounds(startRow, startColumn) || isOutOfBounds(endRow, endColumn))
    {
        throw std::invalid_argument("start or end cell is out of bounds.");
    }

    this->startRow = startRow;
    this->startColumn = startColumn;
    this->endRow = endRow;
    this->endColumn = endColumn;

    grid = new IGridCell **[numRows];

    for (int i = 0; i < numRows; i++)
    {
        //  create an array and assigns each element with an empty cell object
        grid[i] = new IGridCell *[numColumns]; // new returns a pointer

        for (int j = 0; j < numColumns; j++)
        {
            grid[i][j] = new EmptyCell();
        }
    }
};

GameMap::~GameMap()
{

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numColumns; j++)
        {
            delete grid[i][j];
        }

        delete grid[i];
    }

    delete grid;
}

void GameMap::setCell(int row, int column, IGridCell *cell)
{
    if (isOutOfBounds(row, column))
    {
        throw std::invalid_argument("desired cell is out of bounds.");
    }

    delete grid[row][column]; // deallocate old memory

    grid[row][column] = cell;

    notifyObservers(); // notify observers that map has changed
}
void GameMap::setStartRow(int row)
{
    if (isOutOfBounds(row, startColumn))
    {
        throw std::invalid_argument("desired row is out of bounds.");
    }

    startRow = row;
}

void GameMap::setStartColumn(int column)
{
    if (isOutOfBounds(startRow, column))
    {
        throw std::invalid_argument("desired column is out of bounds.");
    }

    startColumn = column;
}

void GameMap::setEndRow(int row)
{
    if (isOutOfBounds(row, endColumn))
    {
        throw std::invalid_argument("desired row is out of bounds.");
    }

    endRow = row;
}

void GameMap::setEndColumn(int column)
{
    if (isOutOfBounds(endRow, column))
    {
        throw std::invalid_argument("desired column is out of bounds.");
    }

    endColumn = column;
}
bool GameMap::validateGrid()
{
    bool **isVisited = new bool *[numRows];

    for (int i = 0; i < numRows; i++)
    {
        isVisited[i] = new bool[numColumns];
        for (int j = 0; j < numColumns; j++)
        {
            isVisited[i][j] = false;
        }
    }

    bool isValid = dfsCanGetMapEnd(startRow, startColumn, isVisited);

    // deallocate isVisited
    for (int i = 0; i < numRows; i++)
    {
        delete isVisited[i];
    }
    delete isVisited;

    return isValid;
}

IGridCell *GameMap::getCell(int row, int column)
{
    if (isOutOfBounds(row, column))
    {
        throw std::invalid_argument("desired cell is out of bounds.");
    }

    return grid[row][column];
}

int GameMap::getNumRows()
{
    return numRows;
}

int GameMap::getNumColumns()
{
    return numColumns;
}

int GameMap::getStartRow()
{
    return startRow;
}

int GameMap::getStartColumn()
{
    return startColumn;
}

int GameMap::getEndRow()
{
    return endRow;
}

int GameMap::getEndColumn()
{
    return endColumn;
}

void GameMap::playTurn() {
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numColumns; j++)
        {
            grid[i][j]->playTurn(this);
        }
    }
}