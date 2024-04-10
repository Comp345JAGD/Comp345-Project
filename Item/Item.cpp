
#include "Item.h"
void ItemContainer::addItem(Item* newItem) {

    items.push_back(newItem);
}

void CharacterEquipment::addItem(Item* newItem) {

    inventory.push_back(newItem);
}
void ItemContainer::addItem(ItemType itemType, string itemName, EnhancementType enhancementType, int enhancementBonus)
{
    Item* newItem = nullptr;

    switch (itemType)
    {
    case ItemType::Helmet:
        newItem = new Helmet(itemName, enhancementType, enhancementBonus);
        break;

    case ItemType::Armor:
        newItem = new Armor(itemName, enhancementType, enhancementBonus);
        break;

    case ItemType::Shield:
        newItem = new Shield(itemName, enhancementType, enhancementBonus);
        break;

    case ItemType::Ring:
        newItem = new Ring(itemName, enhancementType, enhancementBonus);
        break;

    case ItemType::Belt:
        newItem = new Belt(itemName, enhancementType, enhancementBonus);
        break;

    case ItemType::Boots:
        newItem = new Boots(itemName, enhancementType, enhancementBonus);
        break;

    case ItemType::Weapon:
        newItem = new Weapon(itemName, enhancementType, enhancementBonus);
        break;

    default:
        cerr << "Item has an invalid type." << endl;
        return; // Do not proceed if the type is invalid
    }

    items.push_back(newItem);
}



void ItemContainer::dropItem(Item* item)
{
    items.erase(std::remove(items.begin(), items.end(), item), items.end());
    delete item;
}

vector<Item*> ItemContainer::getItems(ItemType type) const
{
    vector<Item*> foundItems;
    for (Item* item : items)
    {
        if (item->getItemType() == type)
        {
            foundItems.push_back(item);
        }
    }
    return foundItems;
}

ItemContainer::~ItemContainer()
{
    for (Item* item : items)
    {
        delete item;
    }
}


bool CharacterEquipment::isSlotEmpty(ItemType slot) const
{
    return equipmentSlots[static_cast<size_t>(slot)] == nullptr;
}

CharacterEquipment::CharacterEquipment() : character("John Doe")
{
    for (int i = 0; i < static_cast<int>(ItemType::Weapon) + 1; ++i)
    {
        equipmentSlots.push_back(nullptr);
    }
}
CharacterEquipment::CharacterEquipment(Character player) : character(player)
{
    for (int i = 0; i < static_cast<int>(ItemType::Weapon) + 1; ++i)
    {
        equipmentSlots.push_back(nullptr);
    }

}
void CharacterEquipment::equip(Item* item) {
    ItemType itemType = item->getItemType();

    if (!isSlotEmpty(itemType)) {
        std::cerr << "Cannot equip " << item->getName() << ". Slot already occupied." << std::endl;
        return;
    }

    equipmentSlots[static_cast<size_t>(itemType)] = item;

    bonusesByType[item->getEnhancement().type] += item->getEnhancement().bonus;

    std::cout << "Equipped " << item->getName() << " in " << toString(itemType) << " Slot" << std::endl;
}
void CharacterEquipment::equip(int index) {
    Item* item = getItem(index);
    if (item != nullptr) {
        equip(item);
        remove(index);
    }
    else {
        std::cerr << "No item found at index " << index << std::endl;
    }
}

void CharacterEquipment::remove(int index) {
    Item* item = getItem(index);
    if (item != nullptr) {
        inventory.erase(inventory.begin() + index); // Remove the item from the inventory vector
        delete item; // Delete the item from memory
    } else {
        std::cerr << "No item found at index " << index << std::endl;
    }
}

void CharacterEquipment::remove(ItemType itemType)
{
    if (equipmentSlots[static_cast<size_t>(itemType)] != nullptr)
    {
        Item* equippedItem = equipmentSlots[static_cast<size_t>(itemType)];
        equipmentSlots[static_cast<size_t>(itemType)] = nullptr;

        bonusesByType[equippedItem->getEnhancement().type] -= equippedItem->getEnhancement().bonus;

        std::cout << "Unequipped " << equippedItem->getName() << " from slot " << static_cast<int>(itemType) << std::endl;

        delete equippedItem;
    }
    else
    {
        std::cerr << "No item equipped in slot " << static_cast<int>(itemType) << std::endl;
    }
}


void CharacterEquipment::displayWornItems() const {
    std::cout << "Character Worn Items:" << std::endl;
    std::vector<std::string> slotNames = { "Helmet", "Armor", "Shield", "Ring", "Belt", "Boots", "Weapon" };

    for (size_t i = 0; i < equipmentSlots.size(); ++i) {
        if (equipmentSlots[i] != nullptr) {
            std::cout << equipmentSlots[i]->getName() << " - Slot: " << slotNames[i]
                << ", Type: " << static_cast<int>(equipmentSlots[i]->getEnhancement().type)
                << ", Bonus: " << equipmentSlots[i]->getEnhancement().bonus << std::endl;
        }
        else {
            std::cout << "Empty " << slotNames[i] << " Slot" << std::endl;
        }
    }
}

int CharacterEquipment::calculateTotalBonus(EnhancementType type) const
{
    return bonusesByType.at(type);
}

void CharacterEquipment::displayTotalGearBonuses() const
{
    std::cout << "Total Bonuses by Type:" << endl << "0. Strength\n1. Dexterity\n2. Constitution\n3. Intelligence\n4. Wisdom\n5. Charisma\n6. ArmorClass\n7. AttackBonus\n8. DamageBonus" << endl;
    for (const auto& entry : bonusesByType)
    {
        std::cout << "Type: " << static_cast<int>(entry.first) << ", Total Bonus: " << entry.second << std::endl;
    }
}


CharacterEquipment::~CharacterEquipment()
{
  

}


int CharacterEquipment::getTotalStength() {
    return character.getStrength() + bonusesByType[EnhancementType::Strength];
}

int CharacterEquipment::getTotalDexterity() {
    return  character.getDexterity() + bonusesByType[EnhancementType::Dexterity];
}

int CharacterEquipment::getTotalConstitution() {
    return character.getConstitution() + bonusesByType[EnhancementType::Constitution];
}

int CharacterEquipment::getTotalIntelligence() {
    return  character.getIntelligence() + bonusesByType[EnhancementType::Intelligence];
}

int CharacterEquipment::getTotalWisdom() {
    return  character.getWisdom() + bonusesByType[EnhancementType::Wisdom];
}
int CharacterEquipment::getTotalCharisma() {
    return  character.getCharisma() + bonusesByType[EnhancementType::Charisma];
}
int CharacterEquipment::getTotalArmorClass() {
    return  character.getArmorClass() + bonusesByType[EnhancementType::ArmorClass];
}
int CharacterEquipment::getTotalAttackBonus() {
    return  character.getAttackBonus() + bonusesByType[EnhancementType::AttackBonus];
}
int CharacterEquipment::getTotalDamageBonus() {
    return  character.getDamageBonus() + bonusesByType[EnhancementType::DamageBonus];
}
void CharacterEquipment::displayScores2() {
    cout << "Strength: " << getTotalStength() << "\n"
        << "Dexterity: " << getTotalDexterity() << "\n"
        << "Constitution: " << getTotalConstitution() << "\n"
        << "Intelligence: " << getTotalIntelligence() << "\n"
        << "Wisdom: " << getTotalWisdom() << "\n"
        << "Charisma: " << getTotalWisdom() << std::endl;
}
void CharacterEquipment::displayScores3()
{
    std::cout << "Hit Points: " << character.getHitPoints() << "\n"
        << "Armor Class: " << getTotalArmorClass() << "\n"
        << "Attack Bonus: " << getTotalAttackBonus() << "\n"
        << "Damage Bonus: " << getTotalDamageBonus() << "\n\n";
}

void ItemContainer::displayInventory() const
{
    if (items.empty())
    {
        std::cout << "Inventory is empty." << std::endl;
        return;
    }
    cout << "         Inventory         " << endl;
    cout << "===========================" << std::endl;
    int index = 1;
    for (Item* item : items)
    {
        std::cout << index << ". ";
        std::cout << "+" << item->getEnhancement().bonus << " " << item->getName() << " (" << toString(item->getEnhancement().type) << ")" << std::endl;
        index++;
    }
    std::cout << "===========================" << std::endl;
}

void CharacterEquipment::displayInventory() const
{
    if (inventory.empty())
    {
        std::cout << "Inventory is empty." << std::endl;
        return;
    }
    cout << "         Inventory         " << endl;
    std::cout << "===========================" << std::endl;
    int index = 1;
    for (Item* item : inventory)
    {
        std::cout << index << ". ";
        std::cout << "+" << item->getEnhancement().bonus << " " << item->getName() << " (" << toString(item->getEnhancement().type) << ")" << std::endl;
        index++;
    }
    std::cout << "===========================" << std::endl;
}

std::string ItemContainer::toString(EnhancementType type) const
{
    switch (type)
    {
    case EnhancementType::Strength:
        return "Strength";
    case EnhancementType::Dexterity:
        return "Dexterity";
    case EnhancementType::Constitution:
        return "Constitution";
    case EnhancementType::Intelligence:
        return "Intelligence";
    case EnhancementType::Wisdom:
        return "Wisdom";
    case EnhancementType::Charisma:
        return "Charisma";
    case EnhancementType::ArmorClass:
        return "Armor Class";
    case EnhancementType::AttackBonus:
        return "Attack Bonus";
    case EnhancementType::DamageBonus:
        return "Damage Bonus";
    default:
        return "Unknown";
    }
}


void ItemContainer::loadItemsFromFile(const string& filename) {
    ifstream file(filename);
    string line, itemName, itemTypeStr, enhancementTypeStr;
    int enhancementBonus = 1;
    EnhancementType enhancementType = EnhancementType::Dexterity;
    ItemType itemType = ItemType::Weapon;

    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.substr(0, 4) == "Name") {
                itemName = line.substr(line.find(":") + 2);
                continue;
            }
            else if (line.substr(0, 4) == "Type") {
                itemTypeStr = line.substr(line.find(":") + 2);
                itemType = convertItemTypeFromString(itemTypeStr);
                continue;
            }
            else if (line.substr(0, 11) == "Enhancement") {
                enhancementTypeStr = line.substr(line.find(":") + 2);
                enhancementType = convertEnhancementTypeFromString(enhancementTypeStr);
                continue;
            }
            else if (line.substr(0, 5) == "Bonus") {
                istringstream iss(line.substr(line.find(":") + 2));
                iss >> enhancementBonus;
            }

            if (line == "---") {
                // Create Item object using createItem function and add it to the container
                Item* newItem = createItem(itemType, itemName, enhancementType, enhancementBonus);
                if (newItem != nullptr) {
                    items.push_back(newItem);
                }
            }
        }
    }
    else {
        cerr << "Error opening file for reading." << endl;
    }
    file.close();
}

ItemType ItemContainer::convertItemTypeFromString(string& itemTypeStr) {
    if (itemTypeStr == "Helmet")
        return ItemType::Helmet;
    else if (itemTypeStr == "Armor")
        return ItemType::Armor;
    else if (itemTypeStr == "Shield")
        return ItemType::Shield;
    else if (itemTypeStr == "Ring")
        return ItemType::Ring;
    else if (itemTypeStr == "Belt")
        return ItemType::Belt;
    else if (itemTypeStr == "Boots")
        return ItemType::Boots;
    else if (itemTypeStr == "Weapon")
        return ItemType::Weapon;
    else {
        std::cerr << "Unknown item type: " << itemTypeStr << std::endl;
    }
}

EnhancementType ItemContainer::convertEnhancementTypeFromString(string& enhancementTypeStr) {
    if (enhancementTypeStr == "Strength")
        return EnhancementType::Strength;
    else if (enhancementTypeStr == "Dexterity")
        return EnhancementType::Dexterity;
    else if (enhancementTypeStr == "Constitution")
        return EnhancementType::Constitution;
    else if (enhancementTypeStr == "Intelligence")
        return EnhancementType::Intelligence;
    else if (enhancementTypeStr == "Wisdom")
        return EnhancementType::Wisdom;
    else if (enhancementTypeStr == "Charisma")
        return EnhancementType::Charisma;
    else if (enhancementTypeStr == "ArmorClass")
        return EnhancementType::ArmorClass;
    else if (enhancementTypeStr == "AttackBonus")
        return EnhancementType::AttackBonus;
    else if (enhancementTypeStr == "DamageBonus")
        return EnhancementType::DamageBonus;
    else {
        std::cerr << "Unknown enhancement type: " << enhancementTypeStr << std::endl;
    }
}

Item* ItemContainer::createItem(ItemType itemType, string& itemName, EnhancementType enhancementType, int enhancementBonus) {
    switch (itemType) {
    case ItemType::Helmet:
        return new Helmet(itemName, enhancementType, enhancementBonus);
    case ItemType::Armor:
        return new Armor(itemName, enhancementType, enhancementBonus);
    case ItemType::Shield:
        return new Shield(itemName, enhancementType, enhancementBonus);
    case ItemType::Ring:
        return new Ring(itemName, enhancementType, enhancementBonus);
    case ItemType::Belt:
        return new Belt(itemName, enhancementType, enhancementBonus);
    case ItemType::Boots:
        return new Boots(itemName, enhancementType, enhancementBonus);
    case ItemType::Weapon:
        return new Weapon(itemName, enhancementType, enhancementBonus);
    default:
        std::cerr << "Unknown item type: " << static_cast<int>(itemType) << std::endl;
        return nullptr;
    }
}

void ItemContainer::saveItemsToFile(const string& filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        for (Item* item : items) {
            file << "Name: " << item->getName() << endl;
            file << "Type: " << item->toString() << endl;
            file << "Enhancement: " << toString(item->getEnhancement().type) << endl;
            file << "Bonus: " << item->getEnhancement().bonus << endl;
            file << "---" << endl;
        }
        cout << "Items saved to file: " << filename << endl;
    }
    else {
        cerr << "Error opening file for writing." << endl;
    }
    file.close();
}
Item* CharacterEquipment::getItem(int index) {

    if (index >= 0 && index < inventory.size()) {
        return inventory[index];
    }
}
Item* ItemContainer::getItem(int index) {
    if (index >= 0 && index < items.size()) {
        return items[index];
    }
    else {
        return nullptr;
    }
}

void CharacterEquipment::addInventory(ItemContainer& otherInventory)
{
    vector<Item*> otherItems = otherInventory.getItems();

    for (Item* item : otherItems)
    {
        addItem(item);
    }
}
vector<Item*> ItemContainer::getItems()
{
    return items;
}
/*
Item CharacterEquipment::getItemFromInventory(int index) const {
    return inventory.getItem(index);
}

Item* CharacterEquipment::getItems(int index) {
    if (index >= 0 && index < items.size()) {
        return items[index];
    }
    else {
        return nullptr;
    }
}
*/

string ItemContainer::toString(ItemType type) {
    switch (type) {
    case ItemType::Helmet:
        return "Helmet";
    case ItemType::Armor:
        return "Armor";
    case ItemType::Shield:
        return "Shield";
    case ItemType::Ring:
        return "Ring";
    case ItemType::Belt:
        return "Belt";
    case ItemType::Boots:
        return "Boots";
    case ItemType::Weapon:
        return "Weapon";
    default:
        return "Unknown";
    }
}

Chest::Chest() {
    containers.push_back(new ItemContainer());
    containers[0]->addItem(ItemType::Weapon, "Iron Dagger", EnhancementType::Strength, 1);
    containers[0]->addItem(ItemType::Weapon, "Wooden Staff", EnhancementType::Intelligence, 1);

    containers.push_back(new ItemContainer());
    containers[1]->addItem(ItemType::Boots, "Leather Boots", EnhancementType::ArmorClass, 1);

    containers.push_back(new ItemContainer());
    containers[2]->addItem(ItemType::Helmet, "Leather Helmet", EnhancementType::Dexterity, 1);

    containers.push_back(new ItemContainer());
    containers[3]->addItem(ItemType::Ring, "Ring of Strength", EnhancementType::Strength, 2);
    containers[3]->addItem(ItemType::Ring, "Ring of Intelligence", EnhancementType::Intelligence, 2);

    containers.push_back(new ItemContainer());
    containers[4]->addItem(ItemType::Shield, "Iron Studded Shield", EnhancementType::ArmorClass, 2);

    containers.push_back(new ItemContainer());
    containers[5]->addItem(ItemType::Weapon, "Silver Sword", EnhancementType::Strength, 3);

    containers.push_back(new ItemContainer());
    containers[6]->addItem(ItemType::Armor, "Steel Plated Armor", EnhancementType::ArmorClass, 4);

    containers.push_back(new ItemContainer());
    containers[7]->addItem(ItemType::Shield, "Steel Plated Shield", EnhancementType::ArmorClass, 3);

    containers.push_back(new ItemContainer());
    containers[8]->addItem(ItemType::Weapon, "Staff of Piercing", EnhancementType::Intelligence, 5);

    containers.push_back(new ItemContainer());
    containers[9]->addItem(ItemType::Weapon, "Master Sword", EnhancementType::Strength, 5);

    containers.push_back(new ItemContainer());
    containers[10]->addItem(ItemType::Boots, "Boots of Swiftness", EnhancementType::Dexterity, 5);
}
void Chest::loadContainers() {


}

ItemContainer* Chest::getItemContainer(int index) const {
    if (index >= 0 && index < containers.size()) {
        return containers[index];
    }
    else {
        return nullptr;
    }
}
