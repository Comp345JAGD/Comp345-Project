#include "campaign.h"
#include <string>
#include <direct.h>  
#include <Windows.h> 
#include <io.h>
#include <fstream>]
#include <vector>
using namespace std;

class Campaign
{
private:
    string campaignName;
    vector<GameMap> maps;
public:
    Campaign(string name){
        campaignName = name;
    }
    void addMap(const  GameMap& map) {
     maps.push_back(map);
    }

    void moveMap(int fromIndex, int toIndex) {
        if (fromIndex >= 0 && fromIndex < maps.size() && toIndex >= 0 && toIndex < maps.size()) {
            swap(maps[fromIndex], maps[toIndex]);
        }
    }
    void removeMap(int index) {
        if (index >= 0 && index < maps.size()) {
            maps.erase(maps.begin() + index);
        }
    }
    GameMap& getMapAtIndex(int index) {
        if (index >= 0 && index < maps.size()) {
            return maps[index];
        }
        else {
            throw out_of_range("Index out of range");
        }
    }
    void writeMapDetails(ofstream& outputFile) const {
        for (const GameMap& map : maps) {
          //  outputFile << map.getMapDetails(); // Map print function pls
        }
    }
   
  
};

void loadCampaignInterface() {
    int decision;
    string name;
    cout << "Welcome to Campaign Interface!\nSelect a campaign or create a new campaign:\n1 Select a campaign.\n2 Create a new campaign.\n3 Exit\n";
    cin >> decision;
    while (decision < 1 && decision >= 4) {
        cout << "Error! The input you have tried is invalid.Please try again.";
        cin >> decision;
    }
    while (decision != 3) {
        switch (decision) {
        case 1:
            cout << "Input name of campaign";
            cin >> name;
            selectCampaign(name);
            break;
        case 2:
            createCampaign;
            break;
        default:
            cout << "Error! The input you have tried is invalid.Please try again.";
        }
    }
}
void selectCampaign() {
    string campaignName;
    int mapDecision;
    int numRows;
    int numColumns;
    int startRow;
    int startColumn,
    int endRow;
    int endColumn;
    int targetRow;
    int targetCol;
    bool isWalkable;
    int targetMapIndex;
    int swapTargetMapIndex;
    bool editChoice = true;

    cout << "Input campaign name.\n";
    cin >> campaignName;
    Campaign campaign(campaignName);
    
    string filePath = "C:\\Users\\Jonathan\\source\\repos\\Comp345 - Project\\" + campaignName;
    ofstream outputFile(filePath);

    if (outputFile.is_open()) {
        cout << "Welcome to Map select! Respond with the following integer for desired:\n1 Create Map\n2 Edit Map\n3Move Map\n4 Remove Map\n5 Exit\n";
        cin >> mapDecision;
        while (mapDecision < 1 && mapDecision >= 4) {
            cout << "Error! The input you have tried is invalid.Please try again.";
            cin >> mapDecision;
        }
        while (mapDecision != 5) {
            switch (mapDecision) {
            case 1:
                cout << "Enter specifics for map.Please Input numRows,numColumns,startRow,startColumn,endRow,endColumn";
                cin >> numRows >> numColumns >> startRow >> startColumn >> endRow >> endColumn;
                GameMap map(numRows, numColumns, startRow, startColumn, endRow, endColumn);
                campaign.addMap(map);
                break;
            case 2:
                while (editChoice) {
                    cout << "Enter target map index";
                    cin >> targetMapIndex;
                    GameMap targetMap = campaign.getMapAtIndex(targetMapIndex);
                    cout << "Enter the row and column cell you wish to Change.Enter true or false if the cell you wish to update is walkable.\n ";
                    cin >> targetRow >> targetCol >> isWalkable;
                    if (isWalkable) {
                        targetMap.setCell(targetRow, targetCol, new EmptyCell);
                    }
                    else {
                        targetMap.setCell(targetRow, targetCol, new WallCell);
                    }
                    cout << "Edit saved!Do you wish to continue?\n";
                    cin >> editChoice;
                }
                break;

            case 3:
                cout <<  "Enter target index of Map 1 and Map 2.\n";
                cin >> targetMapIndex >> swapTargetMapIndex;
                campaign.moveMap(targetMapIndex,swapTargetMapIndex);
                cout << "Swap made!";
            case 4:
                cout << "Enter target index of Map to be deleted";
                cin >> targetMapIndex;
                campaign.removeMap(targetMapIndex);
            default:
                cout << "Error! The input you have tried is invalid.Please try again.";
            }
            campaign.writeMapDetails(outputFile);
            outputFile.close();
            cout << "Files created successfully: " << filePath << endl;
        }
    }
    else {
        cerr << "Error: Unable to open the file for writing." << endl;
    }
 }

void createCampaign() {
    string campaignName;
    cout << "Input campaign name.\n";
    cin >> campaignName;
    Campaign campaign(campaignName);
  
    if (_mkdir(campaignName.c_str()) == -1) {
        cerr << "Error creating directory.\n";
    }
    else {
        cout << "Directory created successfully.\n";
    }
}





