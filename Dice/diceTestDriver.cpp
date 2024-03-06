#include "diceTestDriver.h"

void diceTestDriver()
{
    string validOptions = "yYnN";

    while (true)
    {
        cout << "Please enter a dice roll with the faces 4, 6, 8 , 10, 12, 20, 100: ";
        string diceRoll;
        cin >> diceRoll;
        cout << endl;
        int result = RollDice(diceRoll);
        if (result > 0)
        {
            cout << "Your result is: " << result << endl;
        }
        cout << "Would you like to roll again? (Y/N) ";

        string choice;
        cin >> choice;
        while (choice.size() != 1 || validOptions.find(choice) == std::string::npos)
        {
            cout << "Wrong input, please write either Y or N." << endl;
            cin >> choice;
        }
        if (choice.compare("n") == 0 || choice.compare("N") == 0)
        {
            cout << "Thank you for rolling your dice with this program." << endl;
            exit(0);
        }
    }
}