#include "gameMap.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <limits>
#include <queue>
using namespace std;

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

void GameMap::playTurnCycle()
{
    // doesnt like modifying the map while in a loop.
    vector<IGridCell *> cells;

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numColumns; j++)
        {
            grid[i][j]->setPosition(i, j);

            cells.push_back(grid[i][j]);
        }
    }

    for (IGridCell *cell : cells)
    {
        cell->playTurn(this);
    }
}

void GameMap::printMap()
{

    for (int i = 0; i < this->getNumRows(); i++)
    {
        for (int j = 0; j < this->getNumColumns(); j++)
        {
            IGridCell *cell = this->getCell(i, j);

            if (i == this->getStartRow() && j == this->getStartColumn())
            {
                cout << "S";
            }
            else if (i == this->getEndRow() && j == this->getEndColumn())
            {
                cout << "E";
            }
            else
            {
                cout << cell->getGridRepresentation();
            }
        }

        cout << endl;
    }

    cout << endl;
}

bool GameMap::moveOneCellTowardsTarget(int subjectRow, int subjectColumn, int targetRow, int targetColumn)
{
    if (isOutOfBounds(subjectRow, subjectColumn) || isOutOfBounds(targetRow, targetColumn))
    {
        throw std::invalid_argument("desired cell is out of bounds.");
    }

    bool wasMoved = false;

    // up
    int upSteps = bfsMinStepsToTarget(subjectRow - 1, subjectColumn, targetRow, targetColumn, subjectRow, subjectColumn);
    // down
    int downSteps = bfsMinStepsToTarget(subjectRow + 1, subjectColumn, targetRow, targetColumn, subjectRow, subjectColumn);
    // left
    int leftSteps = bfsMinStepsToTarget(subjectRow, subjectColumn - 1, targetRow, targetColumn, subjectRow, subjectColumn);
    // right
    int rightSteps = bfsMinStepsToTarget(subjectRow, subjectColumn + 1, targetRow, targetColumn, subjectRow, subjectColumn);

    int minSteps = min({upSteps, downSteps, leftSteps, rightSteps});

    if (minSteps != numeric_limits<int>::max())
    {

        if (minSteps == upSteps)
        {
            wasMoved = moveCell(subjectRow, subjectColumn, subjectRow - 1, subjectColumn);
        }
        else if (minSteps == downSteps)
        {
            wasMoved = moveCell(subjectRow, subjectColumn, subjectRow + 1, subjectColumn);
        }
        else if (minSteps == leftSteps)
        {
            wasMoved = moveCell(subjectRow, subjectColumn, subjectRow, subjectColumn - 1);
        }
        else if (minSteps == rightSteps)
        {
            wasMoved = moveCell(subjectRow, subjectColumn, subjectRow, subjectColumn + 1);
        }
    }

    return wasMoved;
}

bool GameMap::moveCell(int subjectRow, int subjectColumn, int targetRow, int targetColumn)
{

    if (isOutOfBounds(subjectRow, subjectColumn) || isOutOfBounds(targetRow, targetColumn) || !grid[targetRow][targetColumn]->isWalkable())
    {
        return false;
    }

    if (subjectRow == targetRow && subjectColumn == targetColumn)
    {
        return false;
    }

    // delete grid[targetRow, targetColumn];

    grid[targetRow][targetColumn] = grid[subjectRow][subjectColumn];

    grid[subjectRow][subjectColumn] = new EmptyCell;

    return true;
}

int GameMap::bfsMinStepsToTarget(int subjectRow, int subjectColumn, int targetRow, int targetColumn, int originalRow, int originalColumn)
{

    if (isOutOfBounds(subjectRow, subjectColumn) || isOutOfBounds(targetRow, targetColumn) || !grid[subjectRow][subjectColumn]->isWalkable() || !grid[targetRow][targetColumn]->isWalkable())
    {
        return numeric_limits<int>::max();
    }

    if (isOutOfBounds(originalRow, originalColumn))
    {
        throw std::invalid_argument("original cell is out of bounds.");
    }

    bool **isVisited = new bool *[numRows];

    for (int i = 0; i < numRows; i++)
    {
        isVisited[i] = new bool[numColumns];
        for (int j = 0; j < numColumns; j++)
        {
            isVisited[i][j] = false;
        }
    }

    int **distanceToSubject = new int *[numRows];

    for (int i = 0; i < numRows; i++)
    {
        distanceToSubject[i] = new int[numColumns];
        for (int j = 0; j < numColumns; j++)
        {
            distanceToSubject[i][j] = numeric_limits<int>::max();
        }
    }

    queue<int> rowQueue;
    queue<int> columnQueue;

    distanceToSubject[subjectRow][subjectColumn] = 0;
    isVisited[subjectRow][subjectColumn] = true;

    rowQueue.push(subjectRow);
    columnQueue.push(subjectColumn);

    // up, down, left, right
    int rowDirections[] = {-1, 1, 0, 0};
    int columnDirections[] = {0, 0, -1, 1};

    while (!rowQueue.empty())
    { // or !columnQueue.empty() since they push and pop at the same time
        int row = rowQueue.front();
        int column = columnQueue.front();
        rowQueue.pop();
        columnQueue.pop();

        for (int i = 0; i < 4; i++)
        {
            int nextRow = row + rowDirections[i];
            int nextColumn = column + columnDirections[i];
            if (!isOutOfBounds(nextRow, nextColumn) && !isVisited[nextRow][nextColumn] && grid[nextRow][nextColumn]->isWalkable() || (nextRow == originalColumn && nextColumn == originalColumn) // if the subject is not walkable, we want to allow walking at its place
            )
            {

                distanceToSubject[nextRow][nextColumn] = distanceToSubject[row][column] + 1;
                isVisited[nextRow][nextColumn] = true;

                rowQueue.push(nextRow);
                columnQueue.push(nextColumn);
            }
        }
    }

    int steps = distanceToSubject[targetRow][targetColumn];

    // deallocate isVisited
    for (int i = 0; i < numRows; i++)
    {
        delete isVisited[i];
    }
    delete isVisited;

    for (int i = 0; i < numRows; i++)
    {
        delete distanceToSubject[i];
    }
    delete distanceToSubject;

    return steps;
}
