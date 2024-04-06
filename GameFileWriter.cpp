#include "GameFileWriter.h"
#include <iostream>
#include <fstream>
#include <ctime>


GameFileWriter::GameFileWriter(const std::string logName) : logName(logName) {}


void GameFileWriter::update(const std::string& message) {
	std::ofstream file(logName, std::ios::app);
	if (file.is_open()) {
		file << message << std::endl;
		file.close();
	}
}

void GameFileWriter::newLog() {
	std::ofstream file(logName);
}