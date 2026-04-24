#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
private:
    std::string name;
    int maxHP;
    int currentHP;
    int attack;
    int defense;
    int remnantDrop;
    
public:
    Enemy(std::string n, int hp, int atk, int def, int remnant);
    
    std::string getName() const { return name; }
    int getCurrentHP() const { return currentHP; }
    int getMaxHP() const { return maxHP; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    int getRemnantDrop() const { return remnantDrop; }
    
    void takeDamage(int damage);
    void displayStats() const;
    bool isAlive() const { return currentHP > 0; }
    
    int makeDecision();
};

#endif