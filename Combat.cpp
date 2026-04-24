#include "Combat.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool Combat::startBattle(Character& player, Enemy& enemy) {
    srand(time(0));
    
    cout << "\n=== BATTLE START ===" << endl;
    cout << "A wild " << enemy.getName() << " appears!" << endl;
    
    while (player.isAlive() && enemy.isAlive()) {
        cout << "\n--- Your Turn ---" << endl;
        enemy.displayStats();
        player.displayStats();
        
        playerTurn(player, enemy);
        
        if (!enemy.isAlive()) {
            cout << "\nVictory! " << enemy.getName() << " defeated!" << endl;
            player.addRemnant(enemy.getRemnantDrop());
            cout << "Gained " << enemy.getRemnantDrop() << " Remnant from the fallen." << endl;
            player.incrementBattles();
            return true;
        }
        
        enemyTurn(player, enemy);
        
        if (!player.isAlive()) {
            cout << "\nYou have been defeated..." << endl;
            return false;
        }
    }
    
    return false;
}

void Combat::playerTurn(Character& player, Enemy& enemy) {
    cout << "\n1. Attack" << endl;
    cout << "2. Defend" << endl;
    cout << "3. Use Item" << endl;
    cout << "Choose action: ";
    
    int choice;
    cin >> choice;
    
    player.setDefending(false);
    
    if (choice == 1) {
        cout << "\nYou attack!" << endl;
        int damage = player.getAttack() + (rand() % 5);
        
        bool isCrit = (rand() % 100) < player.getCritChance();
        if (isCrit) {
            damage = damage * 2;
            cout << "CRITICAL HIT! (2x damage)" << endl;
        }
        
        enemy.takeDamage(damage);
        
        if ((rand() % 100) < player.getComboChance()) {
            cout << "\nCOMBO! You strike again!" << endl;
            int comboDamage = player.getAttack() + (rand() % 5);
            
            if ((rand() % 100) < player.getCritChance()) {
                comboDamage *= 2;
                cout << "CRITICAL HIT!" << endl;
            }
            
            enemy.takeDamage(comboDamage);
        }
        
    } else if (choice == 2) {
        cout << "\nYou brace for impact!" << endl;
        player.setDefending(true);
        
    } else if (choice == 3) {
        player.displayInventory();
        
        if (player.getCurrentHP() == player.getMaxHP()) {
            cout << "HP is already full!" << endl;
            playerTurn(player, enemy);
            return;
        }
        
        cout << "Enter item number (0 to cancel): ";
        int itemChoice;
        cin >> itemChoice;
        
        if (itemChoice == 0) {
            playerTurn(player, enemy);
            return;
        }
        
        if (player.useItem(itemChoice - 1)) {
            cout << "Item used!" << endl;
        } else {
            cout << "Invalid item!" << endl;
            playerTurn(player, enemy);
        }
    } else {
        cout << "Invalid choice!" << endl;
        playerTurn(player, enemy);
    }
}

void Combat::enemyTurn(Character& player, Enemy& enemy) {
    cout << "\n--- Enemy Turn ---" << endl;
    
    int decision = enemy.makeDecision();
    
    if (decision == 0) {
        cout << enemy.getName() << " attacks!" << endl;
        int damage = enemy.getAttack() + (rand() % 3);
        player.takeDamage(damage);
    } else {
        cout << enemy.getName() << " defends!" << endl;
    }
}