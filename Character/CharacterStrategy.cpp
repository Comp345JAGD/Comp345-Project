#include "CharacterStrategy.h"

void FriendlyStrategy::execute(Character *character, GameMap *map)
{
    {
        int numRows = map->getNumRows();
        int numCols = map->getNumColumns();
        int playerRow = -1;
        int playerCol = -1;
        for (int i = 0; i < numCols; i++)
        {
            for (int j = 0; j < numRows; j++)
            {
                if (dynamic_cast<Character *>(map->getCell(j, i)) != nullptr)
                { // need a function to check if a character at a cell is a player or NPC
                    playerRow = j;
                    playerCol = i;

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
            map->moveOneCellTowardsTarget(character->getRow(), character->getColumn(), playerRow, playerCol);
        }
    }
}

void AggressorStrategy::execute(Character *character, GameMap *map)
{
    int numRows = map->getNumRows();
    int numCols = map->getNumColumns();
    int myRow = character->getRow();
    int myCol = character->getColumn();
    int playerRow = -1;
    int playerCol = -1;
    for (int i = 0; i < numCols; i++)
    {
        for (int j = 0; j < numRows; j++)
        {
            if (dynamic_cast<Character *>(map->getCell(j, i)) != nullptr)
            {
                playerRow = j;
                playerCol = i;
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
    else if ((playerRow + 1 == myRow && playerCol + 1 == myCol) || (playerRow + 1 == myRow && playerCol == myCol) || (playerRow + 1 == myRow && playerCol - 1 == myCol) ||
             (playerRow == myRow && playerCol + 1 == myCol) || (playerRow == myRow && playerCol == myCol) || (playerRow == myRow && playerCol - 1 == myCol) ||
             (playerRow - 1 == myRow && playerCol + 1 == myCol) || (playerRow - 1 == myRow && playerCol == myCol) || (playerRow - 1 == myRow && playerCol - 1 == myCol))
    {
        // attack logic
        string attackMessage = "A monster attacked the player!\n";
        // c->logNotify(attackMessage);
    }
    else
    {
        map->moveOneCellTowardsTarget(character->getRow(), character->getColumn(), playerRow, playerCol);
    }
}

void HumanPlayerStrategy::execute(Character *character, GameMap *map)
{
    {
        int decision;
        bool validity = false;

        // character->logNotify("Player turn starting...");

        std::cout << "Please choose an action:\n";

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
            bool validity2 = false;
            int decision2;
            int targetRow, targetColumn;

            std::cout << "Select a surrounding cell you wish to move to. Your character is represented by 'C'.\n";

            while (!validity2)
            {

                std::cout << "1 2 3\n4 X 5\n6 7 8\n\n";

                if (std::cin >> decision2)
                {
                    if (decision2 >= 1 && decision <= 8)
                        validity2 = true;
                    else
                        std::cout << "Invalid integer, please enter a number between 1 and 8.\n";
                }
                else
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input, please enter a number between 1 and 8.\n";
                }

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
            }
        }
        case 2:
        {
            bool outerValidity = false;
            int decision2;
            bool validity2 = false;
            int targetRow, targetColumn;

            while (!outerValidity)
            {

                std::cout << "Select a surrounding cell you wish to attack. Your character is represented by the 'C'.\n";

                while (!validity2)
                {
                    std::cout << "1 2 3\n4 C 5\n6 7 8\n\n";

                    if (std::cin >> decision2)
                    {
                        if (decision2 >= 1 && decision2 <= 8)
                            validity2 = true;
                        else
                            std::cout << "Invalid integer, please enter a number between 1 and 8.\n";
                    }
                    else
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input, please enter a number between 1 and 8.\n";
                    }
                }

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
                    Character *targetChar = dynamic_cast<Character *>(map->getCell(targetRow, targetColumn));
                    if (targetChar != nullptr) //  if correct, find if the cell is a character cell
                    {
                        int damage = character->attack();
                        int damageTaken = targetChar->attacked(damage);
                        std::cout << "Dealt " << damageTaken << " damage to the target.\n";
                        outerValidity = true;
                    }
                    else
                    {
                        std::cout << "Selected target is not a enemy, please try again.\n";
                        validity2 = false;
                    }
                }
            }
        }
        case 3:
        {
            std::cout << "You perform a passionate wardance!\n";
            std::cout << "It has no effects, but looked great.\n\n";
        }
        }
        // character->logNotify("Player turn ending...\n");
    }
}