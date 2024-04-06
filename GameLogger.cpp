#include "GameLogger.h"


void GameLogger::logAttach(GameObserver *gameObs) {
	gameObservers.push_back(gameObs);
}

void GameLogger::logDetach(GameObserver* gameObs) {
	std::vector<GameObserver*>:: iterator position = find(gameObservers.begin(), gameObservers.end(), gameObs);
	if (position != gameObservers.end()) gameObservers.erase(position);

}

void GameLogger::log(const std::string &message) {
	for (GameObserver* gameObs : gameObservers) {
		gameObs->update(message);
	}
}