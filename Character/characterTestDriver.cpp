#include "characterTestDriver.h"

void characterTestDriver()
{
DungeonMaster dm;
Character* myChar = dm.creationMenu();
dm.saveCharacter(myChar);
}