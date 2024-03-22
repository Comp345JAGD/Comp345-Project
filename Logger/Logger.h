#ifndef LOGGER_H
#define LOGGER_H

#include "logObserver.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include "character.h"
#include "dice.h"
#include "gameMap.h"
#include "GameLoop.h"
#include "gameMapDriver.h"

class Logger : public logObserver {
    public:
    Logger();
    Logger(Character *c);
    Logger(GameLoop *g);
    Logger(GameMap *m);
    Logger(Dice *d);
    ~Logger();
    void log(const std::string &message);
    int getObjectType();


    private:
        void* logPointer;
        int objectType;
};


#endif