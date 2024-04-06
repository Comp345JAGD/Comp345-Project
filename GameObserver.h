#ifndef GAMEOBSERVER_H
#define GAMEOBSERVER_H

#include <string>

class GameObserver {
	public:
		virtual void update(const std::string &message) = 0;
};


#endif