#include "gameMap.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <limits>
#include <queue>
#include "../Character/character.h"
#include "../Character/CharacterStrategy.h"

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

    //delete grid[row][column]; // deallocate old memory

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

void GameMap::printInfoBar() {

    vector<Character*> characters;

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numColumns; j++)
        {
            Character* character = dynamic_cast<Character*>(grid[i][j]);
            if (character != nullptr) {
                characters.push_back(character);

            }
        }
    }

    
     // 8 rows

    for (int i = 0; i < 8; i++)
    {

        for (int j = 0; j < characters.size(); j++)
        {
            if (j == 0) {

                if (i == 0 || i == 7) {
                    std::cout << "+";
                }
                else {
                    std::cout << "|";
                }

            }

            if (i == 0 || i == 7) {
                std::cout << "---------------------------+";
            }
            else if (i == 1 || i == 6) {
                std::cout << "                           |";
            }
            else { // i == 2, 3, 4, 5

                vector<string>* art = dynamic_cast<Character*>(characters.at(j))->getGridRepresentation();

                std::cout << "  " << art->at(i - 2) << "   ";

                string info = "";

                if (i == 2) {
                    if (dynamic_cast<HumanPlayerStrategy*>(characters.at(j)->getStrategy()) != nullptr) {
                        info = "Human Player";
                    }
                    else if (dynamic_cast<FriendlyStrategy*>(characters.at(j)->getStrategy()) != nullptr) {
                        info = "Friendly";
                    }
                    else if (dynamic_cast<AggressorStrategy*>(characters.at(j)->getStrategy()) != nullptr) {
                        info = "Aggressor";
                    }
                    else {
                        info = "???";
                    }

                }
                else if (i == 4) {
                    info = "HP: " + std::to_string(characters.at(j)->getCurrentHealth()) + "/" + std::to_string(characters.at(j)->getHitPoints());
                }
                else if (i == 5) {
                    info = "Level: " + std::to_string(characters.at(j)->getLevel());

                }

                string padding = "";

                int numPadding = 14 - info.length();

                numPadding = numPadding >= 0 ? numPadding : 0;

                for (int i = 0; i < numPadding; i++)
                {
                    padding += " ";
                }

                std::cout << info << padding << "|";

            }

        }
        std::cout << endl;

    }

    std::cout << endl;

    


}

void GameMap::printMap()
{

    vector<string> startCellArt = {
        R"( /-SS-\ )",
        " |    | ",
        " |   +| ",
        " |    | "
    };

    vector<string>* startCellArtPtr = &startCellArt;

    vector<string> endCellArt = {
        R"( /-EE-\ )",
        " |    | ",
        " |   +| ",
        " |    | "
    };

    vector<string>* endCellArtPtr = &endCellArt;

    vector<string> startOccupiedCellArt = {
      R"( /-SS-\ )",
        " |(oo)| ",
        " |-||-| ",
      R"( | /\ | )"
    };

    vector<string>* startOccupiedCellArtPtr = &startOccupiedCellArt;

    vector<string> endOccupiedCellArt = {
      R"( /-EE-\ )",
        " |(oo)| ",
        " |-||-| ",
      R"( | /\ | )"
    };

    vector<string>* endOccupiedCellArtPtr = &endOccupiedCellArt;

    for (int i = 0; i < this->getNumRows(); i++)
    {
        // 4 rows per cell

        for (int k = 0; k < 4; k++)
        {

            for (int j = 0; j < this->getNumColumns(); j++)
            {

                vector<string>* art;

                IGridCell* cell = this->getCell(i, j);

                bool isCellCharacter = dynamic_cast<Character*>(cell) != nullptr;

                if (i == this->getStartRow() && j == this->getStartColumn())
                {
                    art = isCellCharacter? startOccupiedCellArtPtr : startCellArtPtr;
                }
                else if (i == this->getEndRow() && j == this->getEndColumn())
                {
                    art = isCellCharacter? endOccupiedCellArtPtr : endCellArtPtr;
                }
                else
                {
                    art = cell->getGridRepresentation();
                }

                std::cout << art->at(k) << " ";

            }
            std::cout << endl;

        }

        std::cout << endl;

    }

    std::cout << endl;
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

    grid[targetRow][targetColumn]->setPosition(targetRow, targetColumn);

    return true;
}

int GameMap::bfsMinStepsToTarget(int subjectRow, int subjectColumn, int targetRow, int targetColumn, int originalRow, int originalColumn)
{

    if (isOutOfBounds(subjectRow, subjectColumn) || isOutOfBounds(targetRow, targetColumn) || !grid[subjectRow][subjectColumn]->isWalkable())
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
            if (
                (
                    !isOutOfBounds(nextRow, nextColumn)
                    && !isVisited[nextRow][nextColumn]
                    && grid[nextRow][nextColumn]->isWalkable()
                )
                //|| (nextRow == originalRow && nextColumn == originalColumn)
                || (nextRow == targetRow && nextColumn == targetColumn) // fixing cant get to target if not walkable (but character is not walkable)
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
