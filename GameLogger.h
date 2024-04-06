#ifndef GAMELOGGER_H
#define GAMELOGGER_H

#include <vector>
#include <string>
#include "GameObserver.h"

class GameLogger {
	public:
		void logAttach(GameObserver* gameObs);
		void logDetach(GameObserver* gameObs);
		void log(const std::string& message);

	private:
		std::vector<GameObserver*> gameObservers;
};



#endif