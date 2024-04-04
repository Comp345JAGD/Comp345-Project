#ifndef MAGICIAN_H
#define MAGICIAN_H

#include "character.h"

class Magician : public Character
{

public:
    Magician(std::string name);
    Magician(std::string inputName, int inputStrength, int inputDexterity, int inputConstitution, int inputIntelligence, int inputWisdom, int inputCharisma);
    void addMagicianBonus();
    void groupedCalculate() override;
};

#endif // MAGICIAN_H
