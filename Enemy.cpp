#include "Enemy.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Enemy::Enemy(string n, int hp, int atk, int def, int remnant)
    : name(n), maxHP(hp), currentHP(hp), attack(atk), defense(def), remnantDrop(remnant) {}

void Enemy::takeDamage(int damage) {
    int actualDamage = damage - defense;
    if (actualDamage < 0) actualDamage = 0;
    
    currentHP -= actualDamage;
    if (currentHP < 0) currentHP = 0;
    
    cout << name << " takes " << actualDamage << " damage! ";
    cout << "(" << currentHP << "/" << maxHP << " HP)" << endl;
}

void Enemy::displayStats() const {
    cout << name << " [HP: " << currentHP << "/" << maxHP << "]" << endl;
}

int Enemy::makeDecision() {
    float hpPercent = (float)currentHP / maxHP;
    
    if (hpPercent < 0.3f && rand() % 100 < 40) {
        return 1;
    }
    return 0;
}