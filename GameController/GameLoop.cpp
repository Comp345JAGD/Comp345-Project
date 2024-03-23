#include "GameLoop.h"
#include <iostream>
#include <string>
using namespace std;

GameLoop::GameLoop(GameMap* currentMap) {
	this->currentMap = currentMap;
}

void GameLoop::setGameMap(GameMap* currentMap) {
	this->currentMap = currentMap;
}

void GameLoop::play() {
	int turnCycleNum = 1;
    string endPhase = "Entering end phase...\n";
    currentMap->printMap();
	
	while (true) {
        
        string currentTurn = "The current turn number is : " + std::to_string(turnCycleNum) + ".\n";
        //this->logNotify(currentTurn);
        
        system("pause");
        cout << endl;


		currentMap->playTurnCycle();

        cout << "Turn Cycle: " << turnCycleNum << endl << endl;

        //system("CLS");

        currentMap->printMap();

        

		if (turnCycleNum == 10) {
			break;
		}
        //this->logNotify(endPhase);
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

    //Logger gameMapLogger(gameMap);
    //gameMap->logNotify("Loading Map...\n");

    for (int i = 1; i < gameMap->getNumRows(); i++) {
        gameMap->setCell(i, 2, new WallCell());
    }
   // gameMap->logNotify("Map Loaded\n");

    //gameMap->setCell(2, 1, new WallCell());

    gameMap->setCell(1, 1, new Character(1, new HumanPlayerStrategy()));
    gameMap->setCell(1, 3, new Character(1, new FriendlyStrategy()));

    //gameMap->setCell(1, 1, new MoverCell());

    GameLoop gameLoop(gameMap);

    /*Logger gameLoopLog(&gameLoop);
    string gameStarting = "Game Starting...\n";
    gameLoop.logNotify(gameStarting);*/
    
    gameLoop.play();
}