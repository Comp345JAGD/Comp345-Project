#include "CharacterStrategy.h"


int chestEnocuntered = 0;

void FriendlyStrategy::execute(Character *character, GameMap *map)
{

    string info = "";
    
    character->log(character->getName() + " turn starting...");

    if (character->getCurrentHealth() <= 0) {
        map->setCell(character->getRow(), character->getColumn(), new ChestCell()); // change to chest later
        info += character->getName() + " ELIMINATED!";
        character->log("Player killed " + character->getName() + ".");

        system("CLS");
        map->printInfoBar();
        map->printMap();
        std::cout << info << endl << endl;

        return;
    }

    bool didMove = false;

    if(character->getCurrentHealth() == character->getHitPoints())
    {
        int numRows = map->getNumRows();
        int numCols = map->getNumColumns();
        int playerRow = -1;
        int playerCol = -1;
        for (int i = 0; i < numRows; i++)
        {
            for (int j = 0; j < numCols; j++)
            {
                Character* character = dynamic_cast<Character*>(map->getCell(i, j));
                if (character != nullptr && dynamic_cast<HumanPlayerStrategy*>(character->getStrategy()) != nullptr)
                { // need a function to check if a character at a cell is a player or NPC

                    playerRow = i;
                    playerCol = j;

                    break;
                }
            }
            if (playerRow >= 0)
            {
                break;
            }
        }
        if (playerRow < 0)
        {
            return; // No player on map?
        }
        else
        {

            didMove = map->moveOneCellTowardsTarget(character->getRow(), character->getColumn(), playerRow, playerCol);
            character->log(character->getName() + " moved to position: [" + to_string(character->getRow()) + "][" + to_string(character->getColumn()) + "].");
        }

        // clear HERE, and wait for user input in map
        system("CLS");
        map->printInfoBar();
        map->printMap();
        std::cout << character->getName() + " TURN\n\n" << (didMove ? character->getName() + " moved!" : character->getName() + " was not able to move!") << endl << endl;
    }
    else {
        AggressorStrategy* strat = new AggressorStrategy();
        strat->execute(character, map);

    }

    
}

void AggressorStrategy::execute(Character *character, GameMap *map)
{   
    character->log(character->getName() + " turn starting...");

    if (character->getCurrentHealth() <= 0) {
        map->setCell(character->getRow(), character->getColumn(), new ChestCell()); // change to chest later
        string info = "";
        info += character->getName() + " ELIMINATED!";
        character->log("Player killed " + character->getName() + ".");
        

        system("CLS");
        map->printInfoBar();
        map->printMap();
        std::cout << info << endl << endl;

        return;
    }

    int numRows = map->getNumRows();
    int numCols = map->getNumColumns();
    int myRow = character->getRow();
    int myCol = character->getColumn();
    int playerRow = -1;
    int playerCol = -1;
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            Character* character = dynamic_cast<Character*>(map->getCell(i, j));
            if (character != nullptr && dynamic_cast<HumanPlayerStrategy*>(character->getStrategy()) != nullptr)
            { // need a function to check if a character at a cell is a player or NPC
                playerRow = i;
                playerCol = j;

                break;
            }
        }
        if (playerRow >= 0)
        {
            break;
        }
    }
    if (playerRow < 0)
    {
        return; // No player on map?
    }
    

    // attack logic

    int rowDirections[] = { -1, 1, 0, 0 };
    int columnDirections[] = { 0, 0, -1, 1 };

    bool didAttack = false;

    string info = "";

    for (int i = 0; i < 4; i++)
    {
        int nextRow = myRow + rowDirections[i];
        int nextColumn = myCol + columnDirections[i];

        if (nextRow == playerRow && nextColumn == playerCol) {
            int damage = character->attack();
            int damageTaken = dynamic_cast<Character*>(map->getCell(playerRow, playerCol))->attacked(damage);
            info = character->getName() + " dealt " + std::to_string(damageTaken) + " damage to the player!\n\n";

            didAttack = true;

            break;
        }
    }


    if(!didAttack)
    {
        
        bool didMove = map->moveOneCellTowardsTarget(character->getRow(), character->getColumn(), playerRow, playerCol);
        if (didMove) {
            info = character->getName() + " moved!";
        }
        else {
            info = character->getName() + " stayed idle!";
        }
        character->log(character->getName() + " moved to position: [" + to_string(character->getRow()) + "][" + to_string(character->getColumn()) + "].");
    }

    system("CLS");
    map->printInfoBar();
    map->printMap();
    std::cout << character->getName() + " TURN\n\n" << info << endl << endl;
    character->log(character->getName() + " turn ended.");
}

void HumanPlayerStrategy::execute(Character *character, GameMap *map)
{

    system("CLS");
    map->printInfoBar();
    map->printMap();
  

    string info = "";
    bool moveDone = false;
    while(!moveDone)
    {
        int decision;
        bool validity = false;

        character->log(character->getName() + " turn starting...");

        std::cout << "YOUR TURN\n\nPlease choose an action:\n";

        while (!validity)
        {
            std::cout << "1. Move\n2. Attack\n3. Free Action\n4. Loot Chest\n5. Open Inventory" << endl;

            if (std::cin >> decision)
            {
                if (decision >= 1 && decision <= 5)
                    validity = true;
                else
                    std::cout << "Invalid integer, please enter a number between 1 and 4.\n";
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input, please enter a number between 1 and 4.\n";
            }
        }

        switch (decision)
        {
        case 1:
        {
            bool isDecisionDone = false;

            while (!isDecisionDone) {

                bool validity2 = false;
                int decision2;
                int targetRow, targetColumn;

                std::cout << "Select a surrounding cell you wish to move to. Choose 9 to cancel. Your character is represented by 'C'.\n";

                bool didCancel = false;

                while (!validity2)
                {

                    std::cout << "1 2 3\n4 C 5\n6 7 8\n\n";


                    if (std::cin >> decision2)
                    {
                        if (decision2 == 9) {
                            didCancel = true;
                            isDecisionDone = true;
                            std::cout << "\nYou Canceled your decision!\n\n";
                            break;
                        }

                        if (decision2 >= 1 && decision <= 8)
                            validity2 = true;
                        else
                            std::cout << "Invalid integer, please enter a number between 1 and 9.\n";
                    }
                    else
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input, please enter a number between 1 and 9.\n";
                    }
                }

                if (!didCancel) {
                    switch (decision2)
                    {
                    case 1:
                    {
                        targetRow = character->getRow() - 1;
                        targetColumn = character->getColumn() - 1;
                        break;
                    }
                    case 2:
                    {
                        targetRow = character->getRow() - 1;
                        targetColumn = character->getColumn();
                        break;
                    }
                    case 3:
                    {
                        targetRow = character->getRow() - 1;
                        targetColumn = character->getColumn() + 1;
                        break;
                    }
                    case 4:
                    {
                        targetRow = character->getRow();
                        targetColumn = character->getColumn() - 1;
                        break;
                    }
                    case 5:
                    {
                        targetRow = character->getRow();
                        targetColumn = character->getColumn() + 1;
                        break;
                    }
                    case 6:
                    {
                        targetRow = character->getRow() + 1;
                        targetColumn = character->getColumn() - 1;
                        break;
                    }
                    case 7:
                    {
                        targetRow = character->getRow() + 1;
                        targetColumn = character->getColumn();
                        break;
                    }
                    case 8:
                    {
                        targetRow = character->getRow() + 1;
                        targetColumn = character->getColumn() + 1;
                        break;
                    }
                    }


                    if (!map->moveCell(character->getRow(), character->getColumn(), targetRow, targetColumn)) {
                        std::cout << "You can't move there YO! Try again:\n";
                    }
                    else {
                        info = "You moved!";
                        character->log(character->getName() + " moved to position: [" + to_string(targetRow) + "][" + to_string(targetColumn) + "].");
                        isDecisionDone = true;
                        moveDone = true;
                    }

                }

            }

            
            break;
        }
        case 2:
        {
            
            bool isDecisionDone = false;

            while (!isDecisionDone) {

                int decision2;
                bool validity2 = false;
                int targetRow, targetColumn;
                bool didCancel = false;

                while (!validity2)
                {
                    std::cout << "Select a surrounding cell you wish to attack. Press 9 to cancel. Your character is represented by the 'C'.\n";

                    std::cout << "1 2 3\n4 C 5\n6 7 8\n\n";

                    if (std::cin >> decision2)
                    {

                        if (decision2 == 9) {
                            didCancel = true;
                            isDecisionDone = true;
                            std::cout << "\nYou Canceled your decision!\n\n";
                            break;
                        }

                        if (decision2 >= 1 && decision2 <= 8)
                            validity2 = true;
                        else
                            std::cout << "Invalid integer, please enter a number between 1 and 9.\n";
                    }
                    else
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input, please enter a number between 1 and 9.\n";
                    }
                }

                if (!didCancel) {

                    switch (decision2)
                    {
                    case 1:
                    {
                        targetRow = character->getRow() - 1;
                        targetColumn = character->getColumn() - 1;
                        break;
                    }
                    case 2:
                    {
                        targetRow = character->getRow() - 1;
                        targetColumn = character->getColumn();
                        break;
                    }
                    case 3:
                    {
                        targetRow = character->getRow() - 1;
                        targetColumn = character->getColumn() + 1;
                        break;
                    }
                    case 4:
                    {
                        targetRow = character->getRow();
                        targetColumn = character->getColumn() - 1;
                        break;
                    }
                    case 5:
                    {
                        targetRow = character->getRow();
                        targetColumn = character->getColumn() + 1;
                        break;
                    }
                    case 6:
                    {
                        targetRow = character->getRow() + 1;
                        targetColumn = character->getColumn() - 1;
                        break;
                    }
                    case 7:
                    {
                        targetRow = character->getRow() + 1;
                        targetColumn = character->getColumn();
                        break;
                    }
                    case 8:
                    {
                        targetRow = character->getRow() + 1;
                        targetColumn = character->getColumn() + 1;
                        break;
                    }
                    }

                    bool isOutOfBounds = map->isOutOfBounds(targetRow, targetColumn);
                    if (isOutOfBounds) // if out of bound, select new target
                    {
                        std::cout << "Selected target is out of bounds, please try again.\n";
                    }
                    else
                    {
                        Character* targetChar = dynamic_cast<Character*>(map->getCell(targetRow, targetColumn));
                        if (targetChar != nullptr) //  if correct, find if the cell is a character cell
                        {
                            int damage = character->attack();
                            int damageTaken = targetChar->attacked(damage);
                            info = "Player dealt " + std::to_string(damageTaken) + " damage to the target.\n";

                            isDecisionDone = true;
                            moveDone = true;
                        }
                        else
                        {
                            std::cout << "Selected target is not a enemy, please try again.\n";
                        }
                    }
                    

                }

            }
            

            break;
        }
        case 3:
        {
            info = "You perform a passionate pose!\nIt has no effects, but looked great.";
            moveDone = true;

            break;
        }
        
        case 4:
        {

            int rowDirections[] = { -1, 1, 0, 0 };
            int columnDirections[] = { 0, 0, -1, 1 };

            bool didOpenChest = false;

            int myRow = character->getRow();
            int myCol = character->getColumn();

            for (int i = 0; i < 4; i++)
            {
                int nextRow = myRow + rowDirections[i];
                int nextColumn = myCol + columnDirections[i];

                if (map->isOutOfBounds(nextRow, nextColumn)) {
                    continue;
                }

                if (dynamic_cast<ChestCell*>(map->getCell(nextRow, nextColumn)) != nullptr) {
                    didOpenChest = true;
                    map->setCell(nextRow, nextColumn, new EmptyCell());
                    
                    break;
                }
            }

            if (didOpenChest) {
             
                Chest chest;
                ItemContainer* container = chest.getItemContainer(chestEnocuntered);
                character->characterEquipment->addInventory(container);

                vector<Item*>* otherItems = container->getItems();

                info = "You Opened a chest!\n\n";

                for (Item* item : *otherItems)
                {
                    info += "Obtained " + item->getName() + "!\n";
                }
                chestEnocuntered++;
                moveDone = true;
            }
            else {
                cout << "No chest found. You have to be next to a chest vertically or horizontally to open it.\n\n";
            }


            

            break;
        }
        case 5: {
            int choiceInput, equipItemInput, removeItemInput;

            do {
                character->characterEquipment->displayWornItems();
                character->characterEquipment->displayInventory();
                cout << "Here are Worn Items and Inventory" << endl << "Enter one of the following options:\n1. Equip Item\n2. Remove Item\n3. View Stats\n4. Exit" << endl;
                cin >> choiceInput;
                if (choiceInput == 1) {
                    cout << "Input item you want to equip ";
                    cin >> equipItemInput;
                    character->characterEquipment->equip(character->characterEquipment->getItem(equipItemInput -1));
                    cout << endl;
                }
                else if (choiceInput == 2) {
  
                        cout << "Input item you want to remove\n1. Weapon\n2. Shield\n3. Armor\n4. Helmet\n5. Boots\n6. Belt \n7. Ring "<<endl;
                    cin >> removeItemInput;
                    if (removeItemInput == 1) { character->characterEquipment->remove(ItemType::Weapon); }
                    else   if (removeItemInput == 2) { character->characterEquipment->remove(ItemType::Shield); }
                    else if (removeItemInput == 3) { character->characterEquipment->remove(ItemType::Armor); }
                    else if (removeItemInput == 4) { character->characterEquipment->remove(ItemType::Helmet); }
                    else if (removeItemInput == 5) { character->characterEquipment->remove(ItemType::Boots); }
                    else if (removeItemInput == 6) { character->characterEquipment->remove(ItemType::Belt); }
                    else if (removeItemInput == 7) { character->characterEquipment->remove(ItemType::Ring); }
                    else {
                        cout << "Incorrect Input";
                    }
                    cout << endl;
                }
                else if (choiceInput == 3) {
                    character->characterEquipment->displayScores2();
                    character->characterEquipment->displayScores3();
                    cout << endl;
                 
                }
                else if (choiceInput == 4) {
                    character->characterEquipment->displayScores2();
                    character->characterEquipment->displayScores3();

                    cout << "Thank you for using Item Menu" << endl;
                }
                else {
                    cout << "Incorrect Input!" << endl;
                }

            } while (choiceInput != 4);
            
            moveDone = true;
            break;

        }

        }
    }

    system("CLS");
    map->printInfoBar();
    map->printMap();
    std::cout << info << endl << endl;
    character->log(character->getName() + " turn ended.");
}

