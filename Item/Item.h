#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include "../Character/character.h"
#include "../Character/CharacterStrategy.h"

using namespace std;

// Items and their Attributes
enum class ItemType
{
    Helmet,
    Armor,
    Shield,
    Ring,
    Belt,
    Boots,
    Weapon
};

enum class EnhancementType
{
    Strength,
    Dexterity,
    Constitution,
    Intelligence,
    Wisdom,
    Charisma,
    ArmorClass,
    AttackBonus,
    DamageBonus
};

struct Enhancement
{
    EnhancementType type;
    int bonus;
};

class Item
{
protected:
    string name;
    Enhancement enhancement;

public:
    Item(string &itemName, EnhancementType enhancementType, int enhancementBonus)
        : name(itemName), enhancement({enhancementType, enhancementBonus}) {}

    Enhancement getEnhancement() const
    {
        return enhancement;
    }

    virtual ItemType getItemType() const = 0;

    string getName()
    {
        return name;
    }

    virtual ~Item() {}
};

class Helmet : public Item
{
public:
    Helmet(string itemName, EnhancementType enhancementType, int enhancementBonus)
        : Item(itemName, enhancementType, enhancementBonus) {}

    ItemType getItemType() const override
    {
        return ItemType::Helmet;
    }
};

class Armor : public Item
{
public:
    Armor(string itemName, EnhancementType enhancementType, int enhancementBonus)
        : Item(itemName, enhancementType, enhancementBonus) {}

    ItemType getItemType() const override
    {
        return ItemType::Armor;
    }
};

class Shield : public Item
{
public:
    Shield(string itemName, EnhancementType enhancementType, int enhancementBonus)
        : Item(itemName, enhancementType, enhancementBonus) {}

    ItemType getItemType() const override
    {
        return ItemType::Shield;
    }
};

class Ring : public Item
{
public:
    Ring(string itemName, EnhancementType enhancementType, int enhancementBonus)
        : Item(itemName, enhancementType, enhancementBonus) {}

    ItemType getItemType() const override
    {
        return ItemType::Ring;
    }
};

class Belt : public Item
{
public:
    Belt(string itemName, EnhancementType enhancementType, int enhancementBonus)
        : Item(itemName, enhancementType, enhancementBonus) {}

    ItemType getItemType() const override
    {
        return ItemType::Belt;
    }
};

class Boots : public Item
{
public:
    Boots(string itemName, EnhancementType enhancementType, int enhancementBonus)
        : Item(itemName, enhancementType, enhancementBonus) {}

    ItemType getItemType() const override
    {
        return ItemType::Boots;
    }
};

class Weapon : public Item
{
public:
    Weapon(string itemName, EnhancementType enhancementType, int enhancementBonus)
        : Item(itemName, enhancementType, enhancementBonus) {}

    ItemType getItemType() const override
    {
        return ItemType::Weapon;
    }

};

class ItemContainer
{
private:
    vector<Item *> items;

public:
    void displayInventory() const;
    ItemType convertItemTypeFromString(const std::string& itemTypeStr); 
    EnhancementType convertEnhancementTypeFromString(const std::string& enhancementTypeStr); 
    Item* createItem(ItemType itemType, const std::string& itemName, EnhancementType enhancementType, int enhancementBonus); 
    string toString(EnhancementType type) const;
    vector<Item*> loadItemsFromFile(const std::string& filename);
    void addItem(ItemType itemType, string itemName, EnhancementType enhancementType, int enhancementBonus);
    void addItem(Item* item);
    void dropItem(Item *item);

    vector<Item *> getItems(ItemType type) const;

    ~ItemContainer();
};

class CharacterEquipment :public Character,ItemContainer
{
private:
    Character character;
    vector<Item *> equipmentSlots;
    ItemContainer inventory;
    map<EnhancementType, int> bonusesByType;

    bool isSlotEmpty(ItemType slot) const;

public:
    CharacterEquipment();
    CharacterEquipment(Character character);
    void equip(Item *item);
    void unequip(ItemType itemType);
    void displayWornItems() const;
    int calculateTotalBonus(EnhancementType type) const;
    void displayTotalGearBonuses() const;
    int getTotalStength();
    int getTotalDexterity();
    int getTotalConstitution();
    int getTotalIntelligence();
    int getTotalWisdom();
    int getTotalCharisma();
    int getTotalArmorClass();
    int getTotalAttackBonus();
    int getTotalDamageBonus();
    void displayScores2();
    void displayScores3();

 

    ~CharacterEquipment();
};



#endif // ITEM_H