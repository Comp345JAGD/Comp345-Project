#include "CharacterStrategy.h"

void FriendlyStrategy::execute(Character *character, GameMap *map)
{

    string info = "";
    
    if (character->getCurrentHealth() <= 0) {
        map->setCell(character->getRow(), character->getColumn(), new EmptyCell()); // change to chest later
        info += character->getName() + " ELIMINATED!";

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

    if (character->getCurrentHealth() <= 0) {
        map->setCell(character->getRow(), character->getColumn(), new EmptyCell()); // change to chest later
        string info = "";
        info += character->getName() + " ELIMINATED!";

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
        info = character->getName() + " moved!";
        map->moveOneCellTowardsTarget(character->getRow(), character->getColumn(), playerRow, playerCol);
    }

    system("CLS");
    map->printInfoBar();
    map->printMap();
    std::cout << character->getName() + " TURN\n\n" << info << endl << endl;
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

        // character->logNotify("Player turn starting...");

        std::cout << "YOUR TURN\n\nPlease choose an action:\n";

        while (!validity)
        {
            std::cout << "1. Move\n2. Attack\n3. Free Action" << endl;

            if (std::cin >> decision)
            {
                if (decision >= 1 && decision <= 3)
                    validity = true;
                else
                    std::cout << "Invalid integer, please enter a number between 1 and 3.\n";
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input, please enter a number between 1 and 3.\n";
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
        }
        // character->logNotify("Player turn ending...\n");
    }

    system("CLS");
    map->printInfoBar();
    map->printMap();
    std::cout << info << endl << endl;
}