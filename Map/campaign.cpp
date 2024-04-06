#include "campaign.h"
#include <string>
#include <iostream>
#include <sstream>
#include "../MapBuilder/MapBuilder.h"
#include "GameFileWriter.h"

using namespace std;

Campaign::Campaign(const std::string& name) : campaignName(name) {
    campaignName = name;
}

int Campaign::getNumMaps() const {
    return maps.size();
}

void Campaign::addMap(GameMap* map) {
    maps.push_back(map);
}

void Campaign::moveMap(int fromIndex, int toIndex) {
    if (fromIndex >= 0 && fromIndex < maps.size() && toIndex >= 0 && toIndex < maps.size()) {
        std::swap(maps[fromIndex], maps[toIndex]);
    }
}

void Campaign::removeMap(int index) {
    if (index >= 0 && index < maps.size()) {
        maps.erase(maps.begin() + index);
    }
}

GameMap* Campaign::getMapAtIndex(int index) {
    if (index >= 0 && index < maps.size()) {
        return maps[index];
    }
    else {
        throw std::out_of_range("Index out of range");
    }
}

void Campaign::writeMapDetails(std::fstream& file) const {
    cout << "Map Changed:" << endl;

    for (size_t i = 0; i < maps.size(); ++i) {
        file << "Map" << i + 1 << std::endl;
        GameMap* map = maps[i];
        for (int row = 0; row < map->getNumRows(); ++row) {
            for (int col = 0; col < map->getNumColumns(); ++col) {
                IGridCell* cell = map->getCell(row, col);
                if (cell->isWalkable()) {
                    if (row == map->getStartRow() && col == map->getStartColumn()) {
                        file << "S";
                    }
                    else if (row == map->getEndRow() && col == map->getEndColumn()) {
                        file << "E";
                    }
                    else {
                        file << "O";
                    }
                }
                else {
                    file << "W";
                }

                file << ",";
            }
            file << std::endl;
        }
        file << std::endl;
    }
}

void Campaign::readMapDetails(std::ifstream& inputFile) {
    std::string line;
    int mapIndex = 0;

    /*
    while (getline(inputFile, line)) {
        if (line.find("Map") != std::string::npos) {
            mapIndex++;

            int numRows, numColumns;
            if (sscanf_s(line.c_str(), "Map %d", &numRows) != 1) {
                std::cerr << "Error: Unable to extract map size from line: " << line << std::endl;
                continue;
            }
            numColumns = static_cast<int>(line.length() - 4);

            GameMap map(numRows, numColumns, 0, 0, 0, 0);

            int currentRow = 0;
            while (getline(inputFile, line)) {
                if (line.find("Map") != std::string::npos) {
                    break;
                }

                for (size_t i = 0; i < line.length(); i++) {
                    switch (line[i]) {
                    case 'S':
                        map.setStartRow(currentRow);
                        map.setStartColumn(i);
                        break;
                    case 'E':
                        map.setEndRow(currentRow);
                        map.setEndColumn(i);
                        break;
                    case 'O':
                        map.setCell(currentRow, i, new EmptyCell);
                        break;
                    case 'X':
                        map.setCell(currentRow, i, new WallCell);
                        break;
                    default:
                        break;
                    }
                }

                currentRow++;
            }

            addMap(map);
        }
    }
    */
}

 Campaign* loadCampain(string filePath, string campaignName){

     Campaign* campain = new Campaign(campaignName);

    // fetch map from file

    ifstream inputFile(filePath);

    //cout << "----------" << inputFile.fail() << endl;

    string mapString = "";


    if (!inputFile.fail()) {
        string line;
        while (inputFile >> line) {
            //cout << line << endl;
            if (line.substr(0, 3) == "Map") {
                if (mapString != "") {

                    makeMapFromString(mapString, campain);
                }
            }
            else {
                mapString += line + "$";
            }
        }

        if (mapString != "") {

            makeMapFromString(mapString, campain);
        }

    }

    inputFile.close();

    return campain;


}

 void makeMapFromString(std::string& mapString, Campaign* campain)
 {
     MapBuilder* builder = new EditorMapBuilder();
     GameMap* gameMap = builder->setMapAsString(mapString)
         ->build();

     campain->addMap(gameMap);

     mapString = "";
 }

void selectCampaign() {
    string campaignName;
    string filePath;
    GameMap targetMap(2, 2, 0, 0, 0, 0);

    GameFileWriter Logger("Game_Log.txt");

    cout << "Input campaign name.\n";
    cin >> campaignName;

    cout << "Input file path.\n";
    cin >> filePath;

    Campaign campaign = *loadCampain(filePath, campaignName);

    fstream file(filePath, ios::in | ios::out);

    if (file.is_open()) {
        int mapDecision = 0;
        while (mapDecision != 6) {
            system("CLS");
            cout << "==================================\n";
            cout << "You have selected a campain! Respond with the following integer for desired:\n";
            cout << "0. Play the Campain\n1. Create Map\n2. Edit Map\n3. Move Map\n4. Remove Map\n5. Save Map (Any unsaved data will be lost!)\n6. Exit\n";
            cout << "==================================\n";

            cin >> mapDecision;
            while (mapDecision < 0 || mapDecision >= 7) {
                cout << "Error! The input you have tried is invalid. Please try again.\n";
                cin >> mapDecision;
            }

            switch (mapDecision) {
            case 0:
            {
                DungeonMaster dm;
                std::vector<std::unique_ptr<Character>> charArr = dm.loadCharacters();
                
                Character* chosenCharacter;

                if (charArr.size() == 0) {
                    cout << "You do not have any characters saved, lets create a new character\n\n";

                    system("pause");
                    system("CLS");
                    
                    chosenCharacter = dm.creationMenu();
                    dm.saveCharacter(chosenCharacter);

                    system("pause");
                    system("CLS");
                }
                else {
                    cout << "Here are all your characters:\n\n";
                    vector<Character*> characters;

                    for (int i = 0; i < charArr.size(); i++)
                    {
                        characters.push_back(charArr.at(i).get());
                    }
                    displayCharacters(characters);

                    bool isValid = false;
                    int decision;

                    while (!isValid) {

                        cout << "\nChoose one of them:\n\n";

                        dm.displayCharacters(charArr);

                        if (std::cin >> decision)
                        {
                            if (decision >= 1 && decision <= charArr.size())
                                isValid = true;
                            else
                                std::cout << "\nInvalid integer, please enter a number between 1 and " + std::to_string(charArr.size()) + ".\n\n";
                        }
                        else
                        {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "\nInvalid input, please enter a number between 1 and " + std::to_string(charArr.size()) + ".\n\n";
                        }
                    }


                    chosenCharacter = charArr.at(decision - 1).get();
                }
                

                chosenCharacter->setStrategy(new HumanPlayerStrategy());
                chosenCharacter->logAttach(&Logger);

                cout << "\nLet's start the campaign!:\n\n";


                for (int i = 0; i < campaign.getNumMaps(); i++)
                {

                    system("pause");
                    system("CLS");

                    GameMap* currentMap = campaign.getMapAtIndex(i);

                    GameLoop gameLoop(currentMap, chosenCharacter);

                    bool didPlayerWin = gameLoop.play();

                    // congrates you won do you want to continue??? unless end

                    
                    if (didPlayerWin) {
                        if (i == campaign.getNumMaps() - 1) {
                            cout << "*** Congratulations, you finished the campaign! ***" << endl;
                            system("pause");
                            break;

                        }

                        cout << "\n*** Congratulations, you reached the end of the map! ***\n\n";
                        cout << "Press any key to continue to the next map. Press 'q' to quit.\n\n";
                        string inputStr;
                        cin >> inputStr;

                        if (inputStr == "q") {
                            break;
                        } 
                        else {
                            continue;
                        }
                    }
                    else {
                        cout << "\n*** GAME OVER ***\n\n";
                        break;
                    }



                    // fail go back to main menu

                }
               
                break;
            }
            case 1:
            {
                int numRows, numColumns, startRow, startColumn, endRow, endColumn;
                cout << "Enter specifics for map. Please input numRows, numColumns, startRow, startColumn, endRow, endColumn:\n";
                cin >> numRows >> numColumns >> startRow >> startColumn >> endRow >> endColumn;
                GameMap* map = new GameMap(numRows, numColumns, startRow, startColumn, endRow, endColumn);
                campaign.addMap(map);
                cout << "Map created!\n";
                break;
            }

            case 2:
            {
                int targetMapIndex, targetRow, targetCol;
                bool isWalkable, continueEditing = true;

                while (continueEditing) {
                    cout << "Enter target map index: ";
                    cin >> targetMapIndex;

                    if (targetMapIndex >= 0 && targetMapIndex < campaign.getNumMaps()) {
                        targetMap = *campaign.getMapAtIndex(targetMapIndex);
                        cout << "Enter the row, column, and walkable status (true/false) of the cell you wish to update: ";
                        cin >> targetRow >> targetCol >> isWalkable;

                        if (isWalkable) {
                            targetMap.setCell(targetRow, targetCol, new EmptyCell);
                        }
                        else {
                            targetMap.setCell(targetRow, targetCol, new WallCell);
                        }

                        cout << "Edit saved! Do you wish to continue editing? (1 for yes, 0 for no): ";
                        cin >> continueEditing;
                    }
                    else {
                        cout << "Invalid map index. Please try again.\n";
                    }
                }
                break;
            }

            case 3:
            {
                int targetMapIndex, swapTargetMapIndex;
                cout << "Enter target index of First Map and SecondMap you wish to swap:\n";
                cin >> targetMapIndex >> swapTargetMapIndex;

                campaign.moveMap(targetMapIndex, swapTargetMapIndex);
                cout << "Swap has been made!\n";
                break;
            }

            case 4:
            {
                int targetMapIndex;
                cout << "Enter target index of Map to be deleted: ";
                cin >> targetMapIndex;

                campaign.removeMap(targetMapIndex);
                break;
            }

            case 5:
                cout << "Files updated successfully: " << filePath << endl;
                file.close();
                file.open(filePath, ios::out | ios::trunc);
                campaign.writeMapDetails(file);
                break;

            case 6:
                cout << "Thank you for your time!\n";
                break;
            default:
                cout << "Error! The input you have tried is invalid. Please try again.\n";
                break;
            }
            system("pause");
        }

        file.close();
    }
    else {
        cerr << "Error: Unable to open the file for reading and writing.\n";
    }
}

void createCampaign() {
    string campaignName;
    cout << "Input campaign name.\n";
    cin >> campaignName;

    ofstream outputFile(campaignName + ".txt");

    if (outputFile.is_open()) {
        cout << "File created successfully: " << campaignName << ".txt" << endl;
        outputFile.close();
    }
    else {
        cerr << "Error: Unable to create the file.\n";
    }
}

void loadCampaignInterface() {
    int decision = 0;
    string name;
    while (decision != 3) {
        system("CLS");
        cout << "==================================\n";
        cout << "Welcome to Campaign Interface!\nSelect a campaign or create a new campaign:\n0 Create a Character\n1 Select a campaign.\n2 Create a new campaign.\n3 Exit\n";
        cout << "==================================\n";
        cin >> decision;
        while (decision < 0 || decision >= 4) {
            cout << "Error! The input you have tried is invalid. Please try again.";
            cin >> decision;
        }
        switch (decision) {
        case 0:
        {
            DungeonMaster dm;
            Character* myChar = dm.creationMenu();
            dm.saveCharacter(myChar);
            break;
        }
        case 1:
            selectCampaign();
            break;
        case 2:
            createCampaign();
            break;
        case 3:
            cout << "Thank you for your time!\n";
            break;
        default:
            cout << "Error! The input you have tried is invalid. Please try again.";
        }
        system("pause");
    }
}
