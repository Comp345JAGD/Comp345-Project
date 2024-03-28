#include "../Map/gameMap.h"
#include "../Map/gameMapDriver.h"
#include "../Character/character.h"
#include "../Character/CharacterStrategy.h"
//#include "logSubject.h"
//#include "Logger.h"

#ifndef GAMELOOP_H
#define GAMELOOP_H

class GameLoop // : public logSubject
{
private:
	GameMap* currentMap;
	Character* humanCharacter;
	bool isGameOver(bool& didPlayerWin);

public:
	GameLoop(GameMap* currentMap, Character* humanCharacter);
	void setGameMap(GameMap* currentMap);
	void setHumanCharacter(Character* humanCharacter);
	bool play();
};

void gameLoopDriver();

#endif