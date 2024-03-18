#include "../Map/gameMap.h"
#include "../Map/gameMapDriver.h"

#ifndef GAMELOOP_H
#define GAMELOOP_H

class GameLoop
{
private:
	GameMap* currentMap;

public:
	GameLoop(GameMap* currentMap);
	void setGameMap(GameMap* currentMap);
	void play();
};

void gameLoopDriver();

#endif