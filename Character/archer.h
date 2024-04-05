#ifndef ARCHER_H
#define ARCHER_H

#include "character.h"

class Archer : public Character
{

public:
    Archer(std::string name);
    Archer(std::string inputName, int inputStrength, int inputDexterity, int inputConstitution, int inputIntelligence, int inputWisdom, int inputCharisma);
    void addArcherBonus();
    void addArcherBonusSilent();
    void groupedCalculate() override;
    void groupCalculateSilent() override;
};

#endif // ARCHER_H
