#include "doctor.h"

Doctor::Doctor(std::string name) : Character(name)
{
    setClassType("Doctor");
}

Doctor::Doctor(std::string inputName, int inputStrength, int inputDexterity, int inputConstitution, int inputIntelligence, int inputWisdom, int inputCharisma) : Character(inputName, inputStrength, inputDexterity, inputConstitution, inputIntelligence, inputWisdom, inputCharisma)
{
    setClassType("Doctor");
}

void Doctor::addDoctorBonus()
{
    std::cout << "Because you have selected the Doctor class, you get 2 bonus intelligence and 1 bonus wisdom!\n";

    intelligence += 2;
    wisdom += 1;

    std::cout << "Here are now your final Doctor stats:\n\n";
    displayScores2();
}

void Doctor::addDoctorBonusSilent()
{
    intelligence += 2;
    wisdom += 1;
}

void Doctor::groupedCalculate()
{
    addDoctorBonus();
    Character::groupedCalculate();

    std::cout << "Here are your class bonuses:\n";
    displayScores3();
}

void Doctor::groupCalculateSilent()
{
    addDoctorBonusSilent();
    Character::groupCalculateSilent();
}


vector<string>* Doctor::getGridRepresentation()
{

    vector<string>* art;

    art = new vector<string>(
        {
         "  (oo) O",
         " __||__|",
       R"(  /  \  )",
       R"( /____\ )" });

    return art;
}