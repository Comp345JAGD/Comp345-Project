#ifndef FIGHTER_H
#define FIGHTER_H

#include "character.h"

class Fighter : public Character
{

public:
    Fighter(std::string name);
    Fighter(std::string inputName, int inputStrength, int inputDexterity, int inputConstitution, int inputIntelligence, int inputWisdom, int inputCharisma);
    void addFighterBonus();
    void addFighterBonusSilent();
    void calculateHitPoints() override;
    void calculateArmorClass() override;
    void calculateAttackBonus() override;
    void calculateDamageBonus() override;
    void groupedCalculate() override;
    void groupCalculateSilent() override;
    virtual vector<string>* getGridRepresentation() override;
};

#endif // FIGHTER_H