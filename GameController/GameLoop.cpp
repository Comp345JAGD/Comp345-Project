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

    currentMap->printMap();
	
	while (true) {

        system("pause");
        cout << endl;

        system("CLS");

		currentMap->playTurnCycle();

        cout << "Turn Cycle: " << turnCycleNum << endl << endl;

        currentMap->printMap();


		if (turnCycleNum == 10) {
			break;
		}

		turnCycleNum++;
	}
}

void gameLoopDriver() {
    int numRows = 4;
    int numColumns = 4;

    GameMap* gameMap = new GameMap(
        numRows,
        numColumns,
        0,
        0,
        numRows - 1,
        numColumns - 1.);

    for (int i = 1; i < gameMap->getNumRows(); i++) {
        gameMap->setCell(i, 2, new WallCell());
    }

    //gameMap->setCell(2, 1, new WallCell());

    gameMap->setCell(1, 1, new MoverCell());

    GameLoop gameLoop(gameMap);
    gameLoop.play();
}