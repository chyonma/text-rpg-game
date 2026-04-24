#ifndef COMBAT_H
#define COMBAT_H

#include "Character.h"
#include "Enemy.h"

class Combat {
public:
    static bool startBattle(Character& player, Enemy& enemy);
private:
    static void playerTurn(Character& player, Enemy& enemy);
    static void enemyTurn(Character& player, Enemy& enemy);
};

#endif