#include "Player.h"

// Concrete Observer/View

Player::Player()
{
}

Player::Player(Character *s)
{
    _subject = s;
    _subject->attach(this);
}

Player::~Player()
{
    _subject->detach(this);
}

void Player::update(StatType statChange, int value)
{
    switch (statChange)
    {
    case lvl:
        std::cout << "Level updated to " << value << ".\n";
        break;
    case str:
        std::cout << "Strength updated to " << value << ".\n";
        break;
    case dex:
        std::cout << "Dexterity updated to " << value << ".\n";
        break;
    case consti:
        std::cout << "Constitution updated to " << value << ".\n";
        break;
    case intel:
        std::cout << "Intelligence updated to " << value << ".\n";
        break;
    case wis:
        std::cout << "Wisdom updated to " << value << ".\n";
        break;
    case chrm:
        std::cout << "Charisma updated to " << value << ".\n";
        break;
    case hp:
        std::cout << "Hit Points updated to " << value << ".\n";
        break;
    case aClass:
        std::cout << "Armor Class updated to " << value << ".\n";
        break;
    case aBonus:
        std::cout << "Attack Bonus updated to " << value << ".\n";
        break;
    case dBonus:
        std::cout << "Damage bonus updated to " << value << ".\n";
        break;
    default:
        std::cout << "default.\n";
    }
}