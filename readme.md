# Souls-Like Text RPG

A terminal-based RPG combat system inspired by Dark Souls, featuring a deep leveling system, equipment progression, and challenging enemy encounters.

## Features

### Core Gameplay
- **Turn-based combat** - Strategic battles against increasingly difficult enemies
- **Souls-like progression** - Spend "Remnant" (currency dropped by enemies) to level up stats
- **Equipment system** - Find and equip weapons and armor with stat bonuses
- **Save/Load system** - Persistent progress across sessions
- **Enemy scaling** - Enemies get stronger as you win more battles

### Combat Mechanics
- **Attack** - Deal damage to enemies
- **Defend** - Reduce incoming damage by 50% for one turn
- **Items** - Use health potions during battle
- **Combo attacks** - Chance to strike twice in one turn (scales with Dexterity)
- **Critical hits** - Deal 2x damage (scales with Luck)

### Character Progression
Four core stats to upgrade:

- **Strength** - +2 Attack per level
- **Vitality** - +10 Max HP per level
- **Dexterity** - +5% Combo Chance per level (base 10%)
- **Luck** - +5% Critical Hit Chance per level (base 10%)

Level-up costs scale exponentially (50 → 75 → 112 → 168...), following the formula: `50 × (1.5 ^ level)`

### Enemy Types
- **Goblin** - Weak but quick (30 HP, 8 ATK, 10 Remnant)
- **Orc** - Balanced stats (50 HP, 12 ATK, 25 Remnant)
- **Troll** - High HP tank (80 HP, 15 ATK, 50 Remnant)
- **Dragon** - Boss enemy (120 HP, 20 ATK, 100 Remnant)

All enemies scale 15% stronger per battle won.

### Loot System
- **Health Potions** - 60% drop rate, restores 30 HP
- **Weapons** - 15% drop rate
  - Iron Sword (+5 ATK)
  - Steel Axe (+8 ATK)
  - Legendary Blade (+12 ATK)
- **Armor** - 15% drop rate
  - Leather Armor (+3 DEF)
  - Chainmail (+6 DEF)
  - Plate Armor (+10 DEF)

## Installation

### Requirements
- C++ compiler with C++11 support (g++, clang, MSVC)
- Windows/Linux/macOS

### Compilation

**Windows (g++):**
```bash
g++ main.cpp Character.cpp Enemy.cpp Combat.cpp Item.cpp -o game.exe
./game.exe

## License
Free to use, modify, and distribute.
