#include "characterTestDriver.h"

void characterTestDriver()
{
DungeonMaster dm;
Character* myChar = dm.creationMenu();
dm.saveCharacter(myChar);
std::vector<std::unique_ptr<Character>> charArr = dm.loadCharacters();
dm.displayCharacters(charArr);

}