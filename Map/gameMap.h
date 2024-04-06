/**
 * @brief These classes represents the map
 * @details
 * 1- Game rules taken into accound:
 * A blank map is created using breadth and width.
 * Be able to set any cell to any thing it can contain.
 * Be able to verify the validity of the map.
 * 2- Design
 * We set all the cells to empty.
 * We use a 2d array of IGridCell to be able to set any cell to anthing that implements it.
 * We verify the validity of the map using DFS.
 * 3- Libraries used
 * stdexcept is used to to throw illegal argument exception.
 */

#include "cell.h"
#include "../SubjectObserver/subjectObserver.h"
#include "GameLogger.h"
#include "GameFileWriter.h"
// #include "logSubject.h"

#ifndef GAMEMAP_H
#define GAMEMAP_H

class GameMap : public BSubject , public GameLogger
{
private:
    IGridCell ***grid; // 2d array
    int numRows;
    int numColumns;
    int startRow;
    int startColumn;
    int endRow;
    int endColumn;
    bool dfsCanGetMapEnd(int row, int column, bool **isVisited);
    int bfsMinStepsToTarget(int subjectRow, int subjectColumn, int targetRow, int targetColumn, int originalRow, int originalColumn);
    GameFileWriter Logger;

public:
    GameMap(
        int numRows,
        int numColumns,
        int startRow,
        int startColumn,
        int endRow,
        int endColumn);
    ~GameMap();
    void setCell(int row, int column, IGridCell *cell);
    bool validateGrid();
    IGridCell *getCell(int row, int column);
    int getNumRows();
    int getNumColumns();
    int getStartRow();
    int getStartColumn();
    int getEndRow();
    int getEndColumn();
    void setStartRow(int row);
    void setStartColumn(int column);
    void setEndRow(int row);
    void setEndColumn(int column);
    void playTurnCycle();
    void printMap();
    bool moveOneCellTowardsTarget(int subjectRow, int subjectColumn, int targetRow, int targetColumn);
    bool moveCell(int subjectRow, int subjectColumn, int targetRow, int targetColumn);
    bool isOutOfBounds(int row, int column);
    void printInfoBar();
};



#endif