#ifndef DOCTOR_H
#define DOCTOR_H

#include "character.h"

class Doctor : public Character
{

public:
    Doctor(std::string name);
    Doctor(std::string inputName, int inputStrength, int inputDexterity, int inputConstitution, int inputIntelligence, int inputWisdom, int inputCharisma);
    void addDoctorBonus();
    void addDoctorBonusSilent();
    void groupedCalculate() override;
    void groupCalculateSilent() override;
};

#endif // DOCTOR_H
