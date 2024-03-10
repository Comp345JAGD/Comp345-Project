#ifndef PLAYER_H
#define PLAYER_H

#include "Observer.h"
#include "character.h"

class Player : public Observer{
    public:
        Player();
        Player(Character* s);
        ~Player();
        void update(StatType statChange, int value) override;

    private:
        Character *_subject;
};

#endif //PLAYER_H
