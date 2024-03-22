#include "Logger.h"

Logger::Logger(){
    std::ofstream gameLog;
    gameLog.open("GameLog.txt", std::ofstream::out | std::ofstream::trunc);
    gameLog.close();
}


Logger::Logger(Character *c){
    Character* tempCharacter = c;
    logPointer = c;
    objectType = 1;
    tempCharacter->logAttach(this,1);
}

Logger::Logger(Dice *d){
    Dice* tempDice = d;
    logPointer = d;
    objectType = 2;
    tempDice->logAttach(this,2);
}

Logger::Logger(GameLoop *g){
    GameLoop* tempGameLoop = g;
    logPointer = g;
    objectType = 3;
    tempGameLoop->logAttach(this, 3);
}

Logger::Logger(GameMap *m){
    GameMap* tempGameMap = m;
    logPointer = m;
    objectType = 4;
    tempGameMap->logAttach(this, 4);
}

Logger::~Logger(){
    if (objectType == 1){
        static_cast<Character *>(logPointer)->logDetach(this);
    }
    else if(objectType == 2){
        static_cast<Dice *>(logPointer)->logDetach(this);
    }
    else if(objectType == 3){
        static_cast<GameLoop *>(logPointer)->logDetach(this);
    }
    else if(objectType == 4){
        static_cast<GameMap *>(logPointer)->logDetach(this);
    }
}

void log(const std::string &message, int type){
    std::ofstream gameLog;
    gameLog.open("GameLog.txt", std::ios_base::app);
    gameLog << message << std::endl;
}

void logAttack(){

}

void logMovement(){

}

void logDiceRoll(){

}

void logGamePhase(){
    
}