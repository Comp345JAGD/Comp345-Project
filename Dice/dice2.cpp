#include <iostream>
#include <string>
#include <random>
#include "dice2.h"

using namespace std;

int RollDice(string diceRoll)
{

    /*Creating random number generator using mersenne twister distribution*/
    random_device dice;
    mt19937 gen(dice());

    /*Some delimiters for separating values and converting to integer values when doing the rolls*/
    string diceDelimiter = "d";
    string bonusDelimiter = "[+";

    /*Parsing number of rolls*/
    string numOfRolls = diceRoll.substr(0, diceRoll.find(diceDelimiter));

    /*Parsing number of dice faces*/
    string numOfFaces = diceRoll.substr(diceRoll.find(diceDelimiter) + 1, diceRoll.find(bonusDelimiter) - 2);

    /*Parsing the dice bonus*/
    string valOfBonus = diceRoll.substr(diceRoll.find(bonusDelimiter) + 2, diceRoll.size());

    /*parsing strings as integers*/
    try
    {
        int rolls = stoi(numOfRolls);
        int faces = stoi(numOfFaces);
        int bonus = stoi(valOfBonus);

        /*checking for valid number of faces*/
        if (!(faces == 4 || faces == 6 || faces == 8 || faces == 10 || faces == 12 || faces == 20 || faces == 100))
        {
            cout << "You did not roll a dice with an accepted number of faces.";
            return 0;
        }

        /*Creating a random integer distribution for rolling between 1 and the number of faces*/
        uniform_int_distribution<int> distribution(1, faces);
        int result = 0;

        /*Rolling the dice*/
        for (int i = 0; i < rolls; i++)
        {
            int interim_result = distribution(dice);
            result += interim_result;
        }

        return result + bonus;
    }
    catch (const std::exception &e)
    {
        cout << "You made an invalid input, please use the format \"xdy[+z]\"" << endl;
        return 0;
    }
}