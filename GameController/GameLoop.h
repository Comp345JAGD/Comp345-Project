#include "../Map/gameMap.h"
#include "../Map/gameMapDriver.h"
#include "../Character/character.h"
#include "../Character/CharacterStrategy.h"
#include "GameLogger.h"
#include "GameFileWriter.h"
//#include "logSubject.h"
//#include "Logger.h"

#ifndef GAMELOOP_H
#define GAMELOOP_H

class GameLoop : public GameLogger
{
private:
	GameMap* currentMap;
	Character* humanCharacter;
	bool isGameOver(bool& didPlayerWin);
	GameFileWriter Logger;

public:
	GameLoop(GameMap* currentMap, Character* humanCharacter);
	void setGameMap(GameMap* currentMap);
	void setHumanCharacter(Character* humanCharacter);
	bool play();
};

void gameLoopDriver();

#endif