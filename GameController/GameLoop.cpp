#include "GameLoop.h"

GameLoop::GameLoop(GameMap* currentMap) {
	this->currentMap = currentMap;
}

void GameLoop::setGameMap(GameMap* currentMap) {
	this->currentMap = currentMap;
}

void GameLoop::play() {

	int turn = 0;
	
	while (true) {

		currentMap->playTurn();

		if (turn == 10) {
			break;
		}

		turn++;
	}
}