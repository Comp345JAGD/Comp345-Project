#include "campaign.h"
#include <string>

using namespace std;

Campaign::Campaign(const std::string& name) : campaignName(name) {
    campaignName = name;
}

int Campaign::getNumMaps() const {
    return maps.size();
}

void Campaign::addMap(const GameMap& map) {
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

GameMap& Campaign::getMapAtIndex(int index) {
    if (index >= 0 && index < maps.size()) {
        return maps[index];
    }
    else {
        throw std::out_of_range("Index out of range");
    }
}

void Campaign::writeMapDetails(std::fstream& file) const {
    for (size_t i = 0; i < maps.size(); ++i) {
        file << "Map " << i + 1 << std::endl;
        GameMap map = maps[i];
        for (int row = 0; row < map.getNumRows(); ++row) {
            for (int col = 0; col < map.getNumColumns(); ++col) {
                IGridCell* cell = map.getCell(row, col);
                if (cell->isWalkable()) {
                    if (row == map.getStartRow() && col == map.getStartColumn()) {
                        file << "S";
                    }
                    else if (row == map.getEndRow() && col == map.getEndColumn()) {
                        file << "E";
                    }
                    else {
                        file << "O";
                    }
                }
                else {
                    file << "X";
                }
            }
            file << std::endl;
        }
        file << std::endl;
    }
}

void Campaign::readMapDetails(std::ifstream& inputFile) {
    std::string line;
    int mapIndex = 0;

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
}

void selectCampaign() {
    string campaignName;
    string filePath;
    GameMap targetMap(2, 2, 0, 0, 0, 0);

    cout << "Input campaign name.\n";
    cin >> campaignName;
    Campaign campaign(campaignName);

    cout << "Input file path.\n";
    cin >> filePath;

    fstream file(filePath, ios::in | ios::out);

    if (file.is_open()) {
        int mapDecision = 0;
        while (mapDecision != 6) {
            cout << "==================================\n";
            cout << "Welcome to Map select! Respond with the following integer for desired:\n";
            cout << "1. Create Map\n2. Edit Map\n3. Move Map\n4. Remove Map\n5. Save Map (Any unsaved data will be lost!)\n6. Exit\n";
            cout << "==================================\n";

            cin >> mapDecision;
            while (mapDecision < 1 || mapDecision >= 7) {
                cout << "Error! The input you have tried is invalid. Please try again.\n";
                cin >> mapDecision;
            }

            switch (mapDecision) {
            case 1:
            {
                int numRows, numColumns, startRow, startColumn, endRow, endColumn;
                cout << "Enter specifics for map. Please input numRows, numColumns, startRow, startColumn, endRow, endColumn:\n";
                cin >> numRows >> numColumns >> startRow >> startColumn >> endRow >> endColumn;
                GameMap map(numRows, numColumns, startRow, startColumn, endRow, endColumn);
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
                        targetMap = campaign.getMapAtIndex(targetMapIndex);
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
                cout << "Enter target index of Map 1 and Map 2:\n";
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
                file.clear();
                file.seekp(0);
                campaign.writeMapDetails(file);
                break;

            default:
                cout << "Error! The input you have tried is invalid. Please try again.\n";
                break;
            }
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
        cout << "==================================\n";
        cout << "Welcome to Campaign Interface!\nSelect a campaign or create a new campaign:\n1 Select a campaign.\n2 Create a new campaign.\n3 Exit\n";
        cout << "==================================\n";
        cin >> decision;
        while (decision < 1 || decision >= 4) {
            cout << "Error! The input you have tried is invalid. Please try again.";
            cin >> decision;
        }
        switch (decision) {
        case 1:
            selectCampaign();
            break;
        case 2:
            createCampaign();
            break;
        default:
            cout << "Error! The input you have tried is invalid. Please try again.";
        }
    }
}
