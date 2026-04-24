#ifndef ITEM_H
#define ITEM_H

#include <string>

enum class ItemType {
    HEALTH_POTION,
    WEAPON,
    ARMOR
};

class Item {
private:
    std::string name;
    std::string description;
    ItemType type;
    int value;

public:
    Item(std::string n, std::string desc, ItemType t, int v);
    
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    ItemType getType() const { return type; }
    int getValue() const { return value; }
    
    // For save/load
    std::string serialize() const;
    static Item deserialize(const std::string& data);
};

#endif