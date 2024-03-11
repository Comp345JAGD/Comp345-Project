#pragma once
#include "cell.h"
#include "gameMap.h"
#include "gameMapDriver.h"
#include <iostream>
#include <map>
#include <vector>


using namespace std;

class Campaign
{
private:
	string campaignName;
	vector<GameMap> maps;
public:

	Campaign( string campaignName);
	void addMap() {}
	void moveMap() {}
	void removeMap(int index) {}
	GameMap& getMapAtIndex(int index) {}
	void writeMapDetails(ofstream& outputFile) const {}
};


void loadCampaignInterface() {}
void createCampaign() {}
void selectCampaign(string campaignName) {}
