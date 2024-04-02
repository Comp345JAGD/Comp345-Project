#include "Item.h"

void ItemContainer::addItem(ItemType itemType, string itemName, EnhancementType enhancementType, int enhancementBonus)
{
    Item *newItem = nullptr;

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

void ItemContainer::dropItem(Item *item)
{
    items.erase(std::remove(items.begin(), items.end(), item), items.end());
    delete item;
}

vector<Item *> ItemContainer::getItems(ItemType type) const
{
    vector<Item *> foundItems;
    for (Item *item : items)
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
    for (Item *item : items)
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
void CharacterEquipment::equip(Item *item)
{
    ItemType itemType = item->getItemType();

    if (!isSlotEmpty(itemType))
    {
        std::cerr << "Cannot equip " << item->getName() << ". Slot already occupied." << std::endl;
        return;
    }

    equipmentSlots[static_cast<size_t>(itemType)] = item;

    bonusesByType[item->getEnhancement().type] += item->getEnhancement().bonus;

    std::cout << "Equipped " << item->getName() << " in slot " << static_cast<int>(itemType) << std::endl;
}

void CharacterEquipment::unequip(ItemType itemType)
{
    if (equipmentSlots[static_cast<size_t>(itemType)] != nullptr)
    {
        Item *equippedItem = equipmentSlots[static_cast<size_t>(itemType)];
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

void CharacterEquipment::displayWornItems() const
{
    std::cout << "Character Worn Items:" << std::endl;
    for (size_t i = 0; i < equipmentSlots.size(); ++i)
    {
        if (equipmentSlots[i] != nullptr)
        {
            std::cout << equipmentSlots[i]->getName() << " - Type: "
                      << static_cast<int>(equipmentSlots[i]->getEnhancement().type)
                      << ", Bonus: " << equipmentSlots[i]->getEnhancement().bonus << std::endl;
        }
        else
        {
            std::cout << "Empty slot: " << i << std::endl;
        }
    }
}

int CharacterEquipment::calculateTotalBonus(EnhancementType type) const
{
    return bonusesByType.at(type);
}

void CharacterEquipment::displayTotalGearBonuses() const
{
    std::cout << "Total Bonuses by Type:" << endl<< "0. Strength\n1. Dexterity\n2. Constitution\n3. Intelligence\n4. Wisdom\n5. Charisma\n6. ArmorClass\n7. AttackBonus\n8. DamageBonus" <<endl;
    for (const auto &entry : bonusesByType)
    {
        std::cout << "Type: " << static_cast<int>(entry.first) << ", Total Bonus: " << entry.second << std::endl;
    }
}

CharacterEquipment::~CharacterEquipment()
{
    for (Item *item : equipmentSlots)
    {
        delete item;
    }
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
    cout << "Strength: " <<getTotalStength() << "\n"
        << "Dexterity: " <<  getTotalDexterity() << "\n"
        << "Constitution: " <<  getTotalConstitution() << "\n"
        << "Intelligence: " <<  getTotalIntelligence() << "\n"
        << "Wisdom: " <<  getTotalWisdom() << "\n"
        << "Charisma: " <<  getTotalWisdom() << std::endl;
}
void CharacterEquipment::displayScores3()
{
    std::cout << "Hit Points: " << character.getHitPoints() << "\n"
        << "Armor Class: " << getTotalArmorClass() << "\n"
        << "Attack Bonus: " << getTotalAttackBonus() << "\n"
        << "Damage Bonus: " << getTotalDamageBonus() << "\n\n";
}
