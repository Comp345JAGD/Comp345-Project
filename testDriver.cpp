#include "Character/characterTestDriver.h"
#include "Map/gameMapDriver.h"
#include "Item/itemTestDriver.h"
#include "Dice/diceTestDriver.h"
#include "Map/campaign.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include "GameController/GameLoop.h"

// Main method to test functionality of every individual section (Character, Dice, Item, Map). Comment out individual drivers
// to test separately. Please refer to each specific driver cpp file for commented guidance of its functionality.
// TO COMPILE AND RUN, COPY PASTE THE FOLLOWING AND RUN THE ./a.exe:
// g++ .\Character\character.cpp .\Character\characterTestDriver.cpp .\Character\dice.cpp .\Character\fighter.cpp .\Map\cell.cpp .\Map\gameMap.cpp .\Map\gameMapDriver.cpp .\Item\Item.cpp .\Item\itemTestDriver.cpp .\Dice\dice2.cpp .\Dice\diceTestDriver.cpp  testDriver.cpp

int main()
{

	GameFileWriter masterLog("Game_Log.txt");
	masterLog.newLog();
	//itemTestDriver();
	// diceTestDriver();



	//characterTestDriver();
	//gameMapDriver();
	//loadCampaignInterface();

	gameLoopDriver();
	
    return 0;
}
