#ifndef MONSTER_H
#define MONSTER_H

#include "character.h"

class Monster : public Character {

public:
	Monster(std::string monsterName);
	virtual vector<string>* getGridRepresentation() override;
	void calculateArmorClass() override;


};

#endif MONSTER_H