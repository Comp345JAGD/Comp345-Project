#ifndef GAME_MAP_DRIVER_H
#define GAME_MAP_DRIVER_H

#include <iostream>
#include "cell.h"
#include "gameMap.h"
using namespace std;

void gameMapDriver();

class MapObserver : public Observer
{
private:
	GameMap* gameMap;
public:
	MapObserver(
		GameMap* gameMap
	);
	void update() override;
};

#endif // GAME_MAP_DRIVER_H