#ifndef DUNGEONMASTER_H
#define DUNGEONMASTER_H

#include "CharacterBuilder.h"

class DungeonMaster // Director Class
{
public:
    void setCharacterBuilder(CharacterBuilder* cb)
    {
        produced_characterBuilder = cb;
    }
    Character* getCharacter()
    {
        return produced_characterBuilder->getCharacter();
    }
    void constructCharacter(string classType, string name);
    Character* creationMenu();
    void saveCharacter(Character* character);
    std::vector<std::unique_ptr<Character>> loadCharacters();
    void displayCharacters(std::vector<std::unique_ptr<Character>>& characters);
    std::unique_ptr<Character> createCharType(std::string& classType, std::string& name, int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma);
private:
    CharacterBuilder* produced_characterBuilder;
};

#endif //DUNGEONMASTER_H