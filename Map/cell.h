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

#ifndef CELL_H
#define CELL_H

class IGridCell
{
public:
    virtual bool isWalkable() = 0; // pure vitual function, no body, you cannot instantiate this class, it is like an interface now
};

class EmptyCell : public IGridCell
{
public:
    bool isWalkable() override;
};

class WallCell : public IGridCell
{
public:
    bool isWalkable() override;
};
class StartCell : public IGridCell
{
public:
    bool isWalkable() override;
};

class EndCell : public IGridCell
{
public:
    bool isWalkable() override;
};

#endif