#include "gameMapDriver.h"

/**
 * @brief This method demonstrates the functionality of the GameMap
 * @details
 * 1- Creates a game map with start and end cell
 * 2- Adds some walls
 * 3- Displays a message informing if the map is valid
 * 4- Displays the map with ascii art
 */

void gameMapDriver()
{

    cout << endl
         << "Game Map Demo" << endl
         << endl;

    int numRows = 4;
    int numColumns = 4;

    GameMap gameMap(
        numRows,
        numColumns,
        1,
        1,
        numRows - 1,
        numColumns - 1.);

    // for (int i = 0; i < gameMap.getNumRows() - 1; i++){
    //   gameMap.setCell(i, 2, new WallCell());
    // }

    gameMap.setCell(2, 3, new WallCell());
    gameMap.setCell(3, 2, new WallCell());

    if (gameMap.validateGrid())
    {
        cout << "It is possible to get from the start to the end" << endl;
    }
    else
    {
        cout << "It is NOT possible to get from the start to the end" << endl;
    }

    for (int i = 0; i < gameMap.getNumRows(); i++)
    {
        for (int j = 0; j < gameMap.getNumColumns(); j++)
        {
            IGridCell *cell = gameMap.getCell(i, j);

            if (i == gameMap.getStartRow() && j == gameMap.getStartColumn())
            {
                cout << "S";
            }
            else if (i == gameMap.getEndRow() && j == gameMap.getEndColumn())
            {
                cout << "E";
            }
            else if (cell->isWalkable())
            {
                cout << "O";
            }
            else
            {
                cout << "X";
            }

            // cout << cell->isWalkable();
        }

        cout << endl;
    }
}