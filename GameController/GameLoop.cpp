#include "GameLoop.h"
#include <iostream>
#include <string>
using namespace std;

GameLoop::GameLoop(GameMap* currentMap, Character* humanCharacter) : Logger("Game_Log.txt") {
	this->currentMap = currentMap;
    this->humanCharacter = humanCharacter;

    this->currentMap->setCell(currentMap->getStartRow(), currentMap->getStartColumn(), humanCharacter);
    this->logAttach(&Logger);
}

void GameLoop::setHumanCharacter(Character* humanCharacter) {
    this->humanCharacter = humanCharacter;
}

void GameLoop::setGameMap(GameMap* currentMap) {
	this->currentMap = currentMap;
}

bool GameLoop::play() {
	int turnCycleNum = 1;
	
	while (true) {
        
        cout << "Turn Cycle: " << turnCycleNum << endl << endl;
        
        currentMap->printInfoBar();
        currentMap->printMap();
        
        system("pause");
        cout << endl;

		currentMap->playTurnCycle();

        bool didPlayerWin = false;

		if (isGameOver(didPlayerWin)) {
            return didPlayerWin;
		}
		turnCycleNum++;


        cout << endl << "TURN CYCLE END" << endl;
        system("pause");
        system("CLS");

	}
}

bool GameLoop::isGameOver(bool& didPlayerWin) {

    if (humanCharacter->getRow() == currentMap->getEndRow() && humanCharacter->getColumn() == currentMap->getEndColumn()) {
        didPlayerWin = true;
        return true;
    }

    if (humanCharacter->getCurrentHealth() <= 0) {
        didPlayerWin = false;
        return true;
    }
    
    return false;

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

    // gameMap->setCell(2, 1, new WallCell());

    Character* humanCharacter = new Character(1, new HumanPlayerStrategy());

    //gameMap->setCell(1, 1, humanCharacter);
    gameMap->setCell(1, 3, new Character(1, new FriendlyStrategy()));

    gameMap->setCell(3, 1, new ChestCell());

    //gameMap->setCell(1, 1, new MoverCell());

    GameLoop gameLoop(gameMap, humanCharacter);

    
    string gameStarting = "Game Starting...\n";
    gameLoop.log(gameStarting);
    
    bool didWin = gameLoop.play();

    cout << "GAME OVER!!!\n\n" << didWin ? "You win!" : "You loose!";
}