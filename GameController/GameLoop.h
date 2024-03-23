#include "../Map/gameMap.h"
#include "../Map/gameMapDriver.h"
//#include "logSubject.h"
//#include "Logger.h"

#ifndef GAMELOOP_H
#define GAMELOOP_H

class GameLoop : //public logSubject
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