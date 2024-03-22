#ifndef FIGHTER_H
#define FIGHTER_H

#include "character.h"

class Fighter : public Character
{

public:
    Fighter();
    Fighter(const std::string &inputName, int inputLevel);
    void addFighterBonus();
    void calculateHitPoints() override;
    void calculateArmorClass() override;
    void calculateAttackBonus() override;
    void calculateDamageBonus() override;
    void groupedCalculate() override;

};

#endif // FIGHTER_H