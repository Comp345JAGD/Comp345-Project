#ifndef CHARACTERSTRATEGY_H
#define CHARACTERSTRATEGY_H

#include "character.h"
#include "../Map/GameMap.h"

class CharacterStrategy
{
public:
    virtual ~CharacterStrategy() = default;
    virtual void execute(Character *character, GameMap *map) = 0;
};

class friendlyStrategy : public CharacterStrategy
{
    void execute(Character *c, GameMap *m)
    {
        int numRows = m->getNumRows();
        int numCols = m->getNumColumns();
        int playerRow = -1;
        int playerCol = -1;
        for (int i = 0; i < numCols; i++)
        {
            for (int j = 0; j < numRows; j++)
            {
                if (dynamic_cast<Character *>(m->getCell(j, i)) != nullptr)
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
            m->moveOneCellTowardsTarget(c->getRow(), c->getColumn(), playerRow, playerCol);
        }
    }
};

class agressorStrategy : public CharacterStrategy
{
    void execute(Character *c, GameMap *m)
    {
        int numRows = m->getNumRows();
        int numCols = m->getNumColumns();
        int myRow = c->getRow();
        int myCol = c->getColumn();
        int playerRow = -1;
        int playerCol = -1;
        for (int i = 0; i < numCols; i++)
        {
            for (int j = 0; j < numRows; j++)
            {
                if (dynamic_cast<Character *>(m->getCell(j, i)) != nullptr)
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
            m->moveOneCellTowardsTarget(c->getRow(), c->getColumn(), playerRow, playerCol);
        }
    }
};

class HumanPlayerStrategy : public CharacterStrategy
{
    void execute(Character *character, GameMap *map)
    {
        int decision;
        bool validity = false;

        // character->logNotify("Player turn starting...");

        std::cout << "Please choose an action:\n";
        std::cout << "1. Move\n2. Attack\n 3. Free Action";

        while (!validity)
        {
            std::cout << "1. Move\n2. Attack\n 3. Free Action";

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
                }

                switch (decision2)
                {
                case 1:
                {
                    targetRow = character->getRow() - 1;
                    targetColumn = character->getColumn() - 1;
                }
                case 2:
                {
                    targetRow = character->getRow() - 1;
                    targetColumn = character->getColumn();
                }
                case 3:
                {
                    targetRow = character->getRow() - 1;
                    targetColumn = character->getColumn() + 1;
                }
                case 4:
                {
                    targetRow = character->getRow();
                    targetColumn = character->getColumn() - 1;
                }
                case 5:
                {
                    targetRow = character->getRow();
                    targetColumn = character->getColumn() + 1;
                }
                case 6:
                {
                    targetRow = character->getRow() + 1;
                    targetColumn = character->getColumn() - 1;
                }
                case 7:
                {
                    targetRow = character->getRow() + 1;
                    targetColumn = character->getColumn();
                }
                case 8:
                {
                    targetRow = character->getRow() + 1;
                    targetColumn = character->getColumn() + 1;
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
};

#endif // CHARACTERSTRATEGY_H