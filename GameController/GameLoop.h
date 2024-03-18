#include "../Map/gameMap.h"
#include "../SubjectObserver/subjectObserver.h"

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

#endif