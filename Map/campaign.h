
#pragma once
#include "gameMap.h"
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#ifndef CAMPAIGN_H
#define CAMPAIGN_H
class Campaign
{
private:
    std::string campaignName;
    std::vector<GameMap> maps;

public:
    Campaign(const std::string& name);
    int getNumMaps() const;
    void addMap(const GameMap& map);
    void moveMap(int fromIndex, int toIndex);
    void removeMap(int index);
    GameMap& getMapAtIndex(int index);
    void writeMapDetails(std::fstream& file) const;
    void readMapDetails(std::ifstream& inputFile);
};

void selectCampaign();
void createCampaign();
void loadCampaignInterface();
#endif 