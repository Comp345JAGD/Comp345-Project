#include "GameLoop.h"
#include <iostream>
using namespace std;

GameLoop::GameLoop(GameMap* currentMap) {
	this->currentMap = currentMap;
}

void GameLoop::setGameMap(GameMap* currentMap) {
	this->currentMap = currentMap;
}

void GameLoop::play() {

	int turnCycleNum = 1;
	
	while (true) {

		currentMap->playTurnCycle();

        cout << "Turn Cycle: " << turnCycleNum << endl << endl;

        currentMap->printMap();


		if (turnCycleNum == 10) {
			break;
		}

        system("pause");
        cout << endl;


		turnCycleNum++;
	}
}

void gameLoopDriver() {
    int numRows = 4;
    int numColumns = 4;

    GameMap gameMap(
        numRows,
        numColumns,
        1,
        1,
        numRows - 1,
        numColumns - 1.);

    for (int i = 0; i < gameMap.getNumRows() - 1; i++) {
        gameMap.setCell(i, 2, new WallCell());
    }

    GameLoop gameLoop(&gameMap);
    gameLoop.play();
}