#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include "Item.h"

class Character {
private:
    std::string name;
    int maxHP;
    int currentHP;
    int baseAttack;
    int baseDefense;
    std::vector<Item> inventory;
    int remnant;
    bool isDefending;
    int battlesWon;
    
    // Leveling system
    int level;
    int strength;
    int vitality;
    int dexterity;
    int luck;
    
    // Equipment slots
    Item* equippedWeapon;
    Item* equippedArmor;

public:
    Character(std::string n, int hp, int atk, int def);
    ~Character();
    
    // Getters
    std::string getName() const { return name; }
    int getCurrentHP() const { return currentHP; }
    int getMaxHP() const { return maxHP; }
    int getAttack() const;
    int getDefense() const;
    int getRemnant() const { return remnant; }
    bool getIsDefending() const { return isDefending; }
    int getBattlesWon() const { return battlesWon; }
    int getLevel() const { return level; }
    int getStrength() const { return strength; }
    int getVitality() const { return vitality; }
    int getDexterity() const { return dexterity; }
    int getLuck() const { return luck; }
    
    // Combat stats
    int getComboChance() const;
    int getCritChance() const;
    
    // Actions
    void takeDamage(int damage);
    void heal(int amount);
    void setDefending(bool state) { isDefending = state; }
    void addRemnant(int amount) { remnant += amount; }
    void addItem(Item item);
    void displayStats() const;
    void displayInventory() const;
    bool useItem(int index);
    void incrementBattles() { battlesWon++; }
    
    // Equipment
    void equipWeapon(int inventoryIndex);
    void equipArmor(int inventoryIndex);
    void displayEquipment() const;
    
    // Leveling
    void displayLevelUpMenu();
    bool levelUpStat(int statChoice);
    int getUpgradeCost() const;
    
    // Check if alive
    bool isAlive() const { return currentHP > 0; }
    
    // Save/Load
    void saveToFile(const std::string& filename) const;
    static Character loadFromFile(const std::string& filename, bool& success);
};

#endif