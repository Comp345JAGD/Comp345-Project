/**
 * @brief These classes represent a single cell in the map
 * @details
 * 1- Game rules taken into accound:
 * A grid cell can either be an empty cell, a wall, or an occupied cell.
 * 2- Design
 * An interface called IGridCell is used to be able to have different types of objects in the grid according to the game rules.
 * 3- Libraries used
 * No external library is used.
 */

#include <string>
using namespace std;

#ifndef CELL_H
#define CELL_H

class GameMap; // https://stackoverflow.com/questions/27677728/statement-includes-itself

class IGridCell
{
protected:
    int row;
    int column;

public:
    virtual bool isWalkable() = 0; // pure vitual function, no body, you cannot instantiate this class, it is like an interface now
    virtual void playTurn(GameMap *map) = 0;
    virtual string getGridRepresentation() = 0;
    virtual void setPosition(int row, int column)
    {
        this->row = row;
        this->column = column;
    }

    int getRow()
    {
        return this->row;
    }
    int getColumn()
    {
        return this->column;
    }
};

class EmptyCell : public IGridCell
{
public:
    bool isWalkable() override;
    void playTurn(GameMap *map) override;
    string getGridRepresentation() override;
    void setPosition(int row, int column) override;
};

class WallCell : public IGridCell
{
public:
    bool isWalkable() override;
    void playTurn(GameMap *map) override;
    string getGridRepresentation() override;
    void setPosition(int row, int column) override;
};

class MoverCell : public IGridCell
{
public:
    bool isWalkable() override;
    void playTurn(GameMap *map) override;
    string getGridRepresentation() override;
    void setPosition(int row, int column) override;
};

#endif