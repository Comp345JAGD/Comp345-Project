#ifndef MONSTER_H
#define MONSTER_H

#include "character.h"

class Monster : public Character {

public:
	Monster(std::string monsterName);
	virtual vector<string>* getGridRepresentation() override;


};

#endif MONSTER_H