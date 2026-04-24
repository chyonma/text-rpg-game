#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "Character.h"
#include "Enemy.h"
#include "Combat.h"
#include "Item.h"

using namespace std;

Enemy createRandomEnemy(int battleCount) {
    int type = rand() % 4;
    float scale = 1.0f + (battleCount * 0.15f);
    
    if (type == 0) {
        return Enemy("Goblin", 30 * scale, 8 * scale, 2, 10);
    } else if (type == 1) {
        return Enemy("Orc", 50 * scale, 12 * scale, 4, 25);
    } else if (type == 2) {
        return Enemy("Troll", 80 * scale, 15 * scale, 6, 50);
    } else {
        return Enemy("Dragon", 120 * scale, 20 * scale, 8, 100);
    }
}

void generateLoot(Character& player, int enemyRemnant) {
    cout << "\n--- Loot Drop ---" << endl;
    
    if (rand() % 100 < 60) {
        player.addItem(Item("Health Potion", "Restores 30 HP", ItemType::HEALTH_POTION, 30));
    }
    
    if (rand() % 100 < 15) {
        int weaponType = rand() % 3;
        if (weaponType == 0) {
            player.addItem(Item("Iron Sword", "A sturdy blade", ItemType::WEAPON, 5));
        } else if (weaponType == 1) {
            player.addItem(Item("Steel Axe", "Heavy and powerful", ItemType::WEAPON, 8));
        } else {
            player.addItem(Item("Legendary Blade", "Forged by ancients", ItemType::WEAPON, 12));
        }
    }
    
    if (rand() % 100 < 15) {
        int armorType = rand() % 3;
        if (armorType == 0) {
            player.addItem(Item("Leather Armor", "Light protection", ItemType::ARMOR, 3));
        } else if (armorType == 1) {
            player.addItem(Item("Chainmail", "Solid defense", ItemType::ARMOR, 6));
        } else {
            player.addItem(Item("Plate Armor", "Maximum protection", ItemType::ARMOR, 10));
        }
    }
}

bool saveFileExists() {
    ifstream file("savegame.txt");
    return file.good();
}

int main() {
    srand(time(0));
    
    cout << "=== TEXT RPG BATTLE ===" << endl;
    
    Character* player = nullptr;
    
    if (saveFileExists()) {
        cout << "\nSave file found!" << endl;
        cout << "1. Load Game" << endl;
        cout << "2. New Game (erases save)" << endl;
        cout << "3. Quit" << endl;
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            bool success;
            Character loadedPlayer = Character::loadFromFile("savegame.txt", success);
            
            if (success) {
                player = new Character(loadedPlayer);
                cout << "\nGame loaded successfully!" << endl;
                player->displayStats();
            } else {
                cout << "Failed to load game. Starting new game..." << endl;
            }
        } else if (choice == 3) {
            return 0;
        }
    }
    
    if (player == nullptr) {
        cout << "\nEnter your name: ";
        string playerName;
        getline(cin >> ws, playerName);
        
        player = new Character(playerName, 100, 15, 5);
        
        player->addItem(Item("Health Potion", "Restores 30 HP", ItemType::HEALTH_POTION, 30));
        player->addItem(Item("Health Potion", "Restores 30 HP", ItemType::HEALTH_POTION, 30));
        player->addItem(Item("Rusty Sword", "Better than nothing", ItemType::WEAPON, 3));
        
        cout << "\nYou begin your journey with meager equipment and fading hope..." << endl;
    }
    
    while (player->isAlive()) {
        cout << "\n==================" << endl;
        cout << "1. Fight Enemy" << endl;
        cout << "2. View Stats" << endl;
        cout << "3. View Inventory" << endl;
        cout << "4. Level Up" << endl;
        cout << "5. View Equipment" << endl;
        cout << "6. Rest (Full Heal)" << endl;
        cout << "7. Save Game" << endl;
        cout << "8. Quit" << endl;
        cout << "Choice: ";
        
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            Enemy enemy = createRandomEnemy(player->getBattlesWon());
            bool victory = Combat::startBattle(*player, enemy);
            
            if (victory) {
                generateLoot(*player, enemy.getRemnantDrop());
            } else {
                break;
            }
            
        } else if (choice == 2) {
            player->displayStats();
            
        } else if (choice == 3) {
            player->displayInventory();
            cout << "\nEquip item? (Enter number, 0 to cancel): ";
            int equipChoice;
            cin >> equipChoice;
            
            if (equipChoice > 0) {
                player->useItem(equipChoice - 1);
            }
            
        } else if (choice == 4) {
            player->displayLevelUpMenu();
            cout << "\nUpgrade stat: ";
            int upgradeChoice;
            cin >> upgradeChoice;
            player->levelUpStat(upgradeChoice);
            
        } else if (choice == 5) {
            player->displayEquipment();
            
        } else if (choice == 6) {
            player->heal(player->getMaxHP());
            cout << "You rest at the bonfire and recover fully." << endl;
            
        } else if (choice == 7) {
            player->saveToFile("savegame.txt");
            
        } else if (choice == 8) {
            cout << "Save before quitting? (y/n): ";
            char saveChoice;
            cin >> saveChoice;
            
            if (saveChoice == 'y' || saveChoice == 'Y') {
                player->saveToFile("savegame.txt");
            }
            break;
        }
    }
    
    cout << "\n=== GAME OVER ===" << endl;
    player->displayStats();
    
    delete player;
    return 0;
}