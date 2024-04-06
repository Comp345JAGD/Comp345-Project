#ifndef GAMEFILEWRITER_H
#define GAMEFILEWRITER_H

#include "GameObserver.h"

class GameFileWriter : public GameObserver {
	public:
		GameFileWriter(const std::string logName);
		void update(const std::string &message) override;
		void newLog();

	private:
		std::string logName;
};


#endif