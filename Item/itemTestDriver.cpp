#include "itemTestDriver.h"

void itemTestDriver()
{
	// Example usage
	CharacterEquipment characterEquipment;

	// Assume you have created instances of Helmet, Armor, Ring, etc.

	// Equip items
	characterEquipment.equip(new Helmet("Enchanted Helmet", EnhancementType::Intelligence, 2));
	characterEquipment.equip(new Armor("Enchanted Armor", EnhancementType::ArmorClass, 3));
	characterEquipment.equip(new Ring("Ring of Strength", EnhancementType::Strength, 1));
	characterEquipment.equip(new Ring("Ring of Dexterity", EnhancementType::Dexterity, 1));

	// Display worn items
	characterEquipment.displayWornItems();

	// Attempt to equip an item in an occupied slot
	characterEquipment.equip(new Belt("Magic Belt", EnhancementType::Strength, 1));

	characterEquipment.unequip((ItemType::Ring));
	// Display updated worn items
	characterEquipment.displayWornItems();
	characterEquipment.displayTotalBonuses();
}