#include "Character.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

Character::Character(string n, int hp, int atk, int def) 
    : name(n), maxHP(hp), currentHP(hp), baseAttack(atk), baseDefense(def), 
      remnant(0), isDefending(false), battlesWon(0), 
      level(1), strength(0), vitality(0), dexterity(0), luck(0),
      equippedWeapon(nullptr), equippedArmor(nullptr) {}

Character::~Character() {
    delete equippedWeapon;
    delete equippedArmor;
}

int Character::getAttack() const {
    int totalAttack = baseAttack + (strength * 2);
    if (equippedWeapon) {
        totalAttack += equippedWeapon->getValue();
    }
    return totalAttack;
}

int Character::getDefense() const {
    int totalDefense = baseDefense;
    if (equippedArmor) {
        totalDefense += equippedArmor->getValue();
    }
    return totalDefense;
}

int Character::getComboChance() const {
    return 10 + (dexterity * 5);
}

int Character::getCritChance() const {
    return 10 + (luck * 5);
}

void Character::takeDamage(int damage) {
    int actualDamage = damage - getDefense();
    if (isDefending) {
        actualDamage /= 2;
    }
    if (actualDamage < 0) actualDamage = 0;
    
    currentHP -= actualDamage;
    if (currentHP < 0) currentHP = 0;
    
    cout << name << " takes " << actualDamage << " damage! ";
    cout << "(" << currentHP << "/" << maxHP << " HP)" << endl;
}

void Character::heal(int amount) {
    currentHP += amount;
    if (currentHP > maxHP) currentHP = maxHP;
    cout << name << " heals " << amount << " HP! ";
    cout << "(" << currentHP << "/" << maxHP << " HP)" << endl;
}

void Character::displayStats() const {
    cout << "\n=== " << name << " ===" << endl;
    cout << "Level: " << level << endl;
    cout << "HP: " << currentHP << "/" << maxHP;
    if (vitality > 0) cout << " (+" << (vitality * 10) << " from Vitality)";
    cout << endl;
    
    cout << "Attack: " << getAttack();
    if (strength > 0) cout << " (+" << (strength * 2) << " from Strength)";
    if (equippedWeapon) cout << " [+" << equippedWeapon->getValue() << " " << equippedWeapon->getName() << "]";
    cout << endl;
    
    cout << "Defense: " << getDefense();
    if (equippedArmor) cout << " [+" << equippedArmor->getValue() << " " << equippedArmor->getName() << "]";
    cout << endl;
    
    cout << "Combo Chance: " << getComboChance() << "%";
    if (dexterity > 0) cout << " (+" << (dexterity * 5) << "% from Dexterity)";
    cout << endl;
    
    cout << "Crit Chance: " << getCritChance() << "%";
    if (luck > 0) cout << " (+" << (luck * 5) << "% from Luck)";
    cout << endl;
    
    cout << "\n--- Stats ---" << endl;
    cout << "Strength: " << strength << endl;
    cout << "Vitality: " << vitality << endl;
    cout << "Dexterity: " << dexterity << endl;
    cout << "Luck: " << luck << endl;
    
    cout << "\nRemnant: " << remnant << endl;
    cout << "Battles Won: " << battlesWon << endl;
}

void Character::addItem(Item item) {
    inventory.push_back(item);
    cout << "Obtained: " << item.getName() << endl;
}

void Character::displayInventory() const {
    cout << "\n--- Inventory ---" << endl;
    if (inventory.empty()) {
        cout << "Empty" << endl;
        return;
    }
    for (size_t i = 0; i < inventory.size(); i++) {
        cout << i + 1 << ". " << inventory[i].getName() 
             << " - " << inventory[i].getDescription();
        
        if (inventory[i].getType() == ItemType::WEAPON) {
            cout << " [ATK +" << inventory[i].getValue() << "]";
        } else if (inventory[i].getType() == ItemType::ARMOR) {
            cout << " [DEF +" << inventory[i].getValue() << "]";
        }
        cout << endl;
    }
}

bool Character::useItem(int index) {
    if (index < 0 || index >= (int)inventory.size()) {
        return false;
    }
    
    Item& item = inventory[index];
    
    if (item.getType() == ItemType::HEALTH_POTION) {
        heal(item.getValue());
        inventory.erase(inventory.begin() + index);
        return true;
    } else if (item.getType() == ItemType::WEAPON) {
        equipWeapon(index);
        return true;
    } else if (item.getType() == ItemType::ARMOR) {
        equipArmor(index);
        return true;
    }
    
    return false;
}

void Character::equipWeapon(int inventoryIndex) {
    if (inventoryIndex < 0 || inventoryIndex >= (int)inventory.size()) {
        return;
    }
    
    Item& item = inventory[inventoryIndex];
    if (item.getType() != ItemType::WEAPON) {
        return;
    }
    
    if (equippedWeapon) {
        inventory.push_back(*equippedWeapon);
        delete equippedWeapon;
    }
    
    equippedWeapon = new Item(item);
    inventory.erase(inventory.begin() + inventoryIndex);
    cout << "Equipped: " << equippedWeapon->getName() << " (+ATK " << equippedWeapon->getValue() << ")" << endl;
}

void Character::equipArmor(int inventoryIndex) {
    if (inventoryIndex < 0 || inventoryIndex >= (int)inventory.size()) {
        return;
    }
    
    Item& item = inventory[inventoryIndex];
    if (item.getType() != ItemType::ARMOR) {
        return;
    }
    
    if (equippedArmor) {
        inventory.push_back(*equippedArmor);
        delete equippedArmor;
    }
    
    equippedArmor = new Item(item);
    inventory.erase(inventory.begin() + inventoryIndex);
    cout << "Equipped: " << equippedArmor->getName() << " (+DEF " << equippedArmor->getValue() << ")" << endl;
}

void Character::displayEquipment() const {
    cout << "\n--- Equipment ---" << endl;
    cout << "Weapon: ";
    if (equippedWeapon) {
        cout << equippedWeapon->getName() << " (+ATK " << equippedWeapon->getValue() << ")" << endl;
    } else {
        cout << "None" << endl;
    }
    
    cout << "Armor: ";
    if (equippedArmor) {
        cout << equippedArmor->getName() << " (+DEF " << equippedArmor->getValue() << ")" << endl;
    } else {
        cout << "None" << endl;
    }
}

int Character::getUpgradeCost() const {
    return 50 * pow(1.5, level - 1);
}

void Character::displayLevelUpMenu() {
    int cost = getUpgradeCost();
    
    cout << "\n=== LEVEL UP (Cost: " << cost << " Remnant) ===" << endl;
    cout << "Current Remnant: " << remnant << endl;
    cout << "\n1. Strength [" << strength << "] - Increases attack (+2 ATK)" << endl;
    cout << "2. Vitality [" << vitality << "] - Increases max HP (+10 HP)" << endl;
    cout << "3. Dexterity [" << dexterity << "] - Increases combo chance (+5%)" << endl;
    cout << "4. Luck [" << luck << "] - Increases crit chance (+5%)" << endl;
    cout << "5. Cancel" << endl;
}

bool Character::levelUpStat(int statChoice) {
    int cost = getUpgradeCost();
    
    if (remnant < cost) {
        cout << "Not enough Remnant! Need " << cost << ", have " << remnant << endl;
        return false;
    }
    
    if (statChoice < 1 || statChoice > 4) {
        return false;
    }
    
    remnant -= cost;
    level++;
    
    if (statChoice == 1) {
        strength++;
        cout << "\nStrength increased to " << strength << "!" << '\n';
        cout << "Attack: " << getAttack() << " (+" << (strength * 2) << " from STR)" << '\n';
    } else if (statChoice == 2) {
        vitality++;
        int oldMaxHP = maxHP;
        maxHP += 10;
        currentHP += 10;
        cout << "\nVitality increased to " << vitality << "!" << '\n';
        cout << "Max HP: " << oldMaxHP << " → " << maxHP << endl;
    } else if (statChoice == 3) {
        dexterity++;
        cout << "\nDexterity increased to " << dexterity << "!" << endl;
        cout << "Combo Chance: " << getComboChance() << "%" << endl;
    } else if (statChoice == 4) {
        luck++;
        cout << "\nLuck increased to " << luck << "!" << endl;
        cout << "Crit Chance: " << getCritChance() << "%" << endl;
    }
    
    cout << "Level up! Now level " << level << endl;
    cout << "Next upgrade cost: " << getUpgradeCost() << " Remnant" << endl;
    return true;
}

void Character::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not save game!" << endl;
        return;
    }
    
    file << name << endl;
    file << maxHP << endl;
    file << currentHP << endl;
    file << baseAttack << endl;
    file << baseDefense << endl;
    file << remnant << endl;
    file << battlesWon << endl;
    file << level << endl;
    file << strength << endl;
    file << vitality << endl;
    file << dexterity << endl;
    file << luck << endl;
    
    if (equippedWeapon) {
        file << "WEAPON:" << equippedWeapon->serialize() << endl;
    } else {
        file << "WEAPON:NONE" << endl;
    }
    
    if (equippedArmor) {
        file << "ARMOR:" << equippedArmor->serialize() << endl;
    } else {
        file << "ARMOR:NONE" << endl;
    }
    
    file << inventory.size() << endl;
    
    for (const Item& item : inventory) {
        file << item.serialize() << endl;
    }
    
    file.close();
    cout << "\nGame saved successfully!" << endl;
}

Character Character::loadFromFile(const string& filename, bool& success) {
    ifstream file(filename);
    success = false;
    
    if (!file.is_open()) {
        return Character("", 0, 0, 0);
    }
    
    string name;
    int maxHP, currentHP, baseAttack, baseDefense, remnant, battlesWon;
    int level, strength, vitality, dexterity, luck;
    
    getline(file, name);
    file >> maxHP >> currentHP >> baseAttack >> baseDefense >> remnant >> battlesWon;
    file >> level >> strength >> vitality >> dexterity >> luck;
    file.ignore();
    
    Character player(name, maxHP, baseAttack, baseDefense);
    player.currentHP = currentHP;
    player.remnant = remnant;
    player.battlesWon = battlesWon;
    player.level = level;
    player.strength = strength;
    player.vitality = vitality;
    player.dexterity = dexterity;
    player.luck = luck;
    
    string weaponLine;
    getline(file, weaponLine);
    if (weaponLine.substr(7) != "NONE") {
        player.equippedWeapon = new Item(Item::deserialize(weaponLine.substr(7)));
    }
    
    string armorLine;
    getline(file, armorLine);
    if (armorLine.substr(6) != "NONE") {
        player.equippedArmor = new Item(Item::deserialize(armorLine.substr(6)));
    }
    
    int inventorySize;
    file >> inventorySize;
    file.ignore();
    
    for (int i = 0; i < inventorySize; i++) {
        string itemData;
        getline(file, itemData);
        player.inventory.push_back(Item::deserialize(itemData));
    }
    
    file.close();
    success = true;
    return player;
}