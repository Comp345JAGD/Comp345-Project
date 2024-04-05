#ifndef HUNTER_H
#define HUNTER_H

#include "character.h"

class Hunter : public Character
{

public:
    Hunter(std::string name);
    Hunter(std::string inputName, int inputStrength, int inputDexterity, int inputConstitution, int inputIntelligence, int inputWisdom, int inputCharisma);
    void addHunterBonus();
    void groupedCalculate() override;
};

#endif // HUNTER_H
