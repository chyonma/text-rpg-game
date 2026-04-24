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
```

**Linux/macOS:**
```bash
g++ main.cpp Character.cpp Enemy.cpp Combat.cpp Item.cpp -o game
./game
```

## How to Play

### Starting a New Game
1. Run the executable
2. Choose "New Game" if no save exists
3. Enter your character name
4. You start with:
   - 100 HP
   - 15 base attack
   - 5 base defense
   - 2 health potions
   - 1 rusty sword

### Main Menu Options
1. **Fight Enemy** - Enter combat with a random enemy
2. **View Stats** - See your current stats, level, and Remnant
3. **View Inventory** - Manage items and equipment
4. **Level Up** - Spend Remnant to upgrade stats
5. **View Equipment** - Check equipped weapon and armor
6. **Rest** - Fully restore HP (free at bonfire)
7. **Save Game** - Save progress to file
8. **Quit** - Exit (option to save before quitting)

### Combat Tips
- **Early game:** Focus on Strength and Vitality
- **Mid game:** Add Dexterity for combos or Luck for crits
- **Against Dragon:** Need at least level 5-6 with good equipment
- **Defend strategically:** Use when low HP and enemy is about to attack
- **Save Remnant:** Don't spend all your Remnant immediately—save for bigger upgrades

### Recommended Builds

**Glass Cannon (High Risk/High Reward):**
- Max Strength + Luck
- Rely on crits to burst down enemies
- Low survivability

**Tank (Safe & Steady):**
- Max Vitality + Strength
- High HP pool to survive longer fights
- Slower progression

**Combo Master (Skill-based):**
- Max Dexterity + Luck
- Chain attacks with high crit chance
- Fun but RNG-dependent

## File Structure
TextRPG/
├── main.cpp          # Game loop and main menu
├── Character.h/cpp   # Player class with stats, inventory, leveling
├── Enemy.h/cpp       # Enemy class with AI
├── Combat.h/cpp      # Battle system
├── Item.h/cpp        # Item system (potions, weapons, armor)
├── savegame.txt      # Save file (auto-generated)
└── README.md         

## Save System

Progress is saved to `savegame.txt` in the same directory as the executable.

**Saved data includes:**
- Character name, HP, stats
- Current level and stat points
- Equipped weapon and armor
- Inventory items
- Battles won
- Remnant count

## Technical Details

### Combat Formula
- **Damage dealt:** `(Attack + Random(0-4)) - Enemy Defense`
- **Critical hit:** `Damage × 2`
- **Defend:** `Incoming Damage ÷ 2`
- **Combo:** Second attack with independent crit roll

### Enemy AI
- **High HP (>30%):** Always attacks
- **Low HP (<30%):** 40% chance to defend, 60% attack

### Scaling
- **Enemy stats:** `Base × (1 + Battles Won × 0.15)`
- **Level cost:** `50 × (1.5 ^ Current Level)`

## Known Limitations
- Console-only (no graphics)
- Single save slot
- No skill tree or magic system
- Limited enemy variety (4 types)

## Future Improvements (If Expanding)
- Multiple enemy types per tier
- Boss-specific mechanics
- Magic/spell system
- Skill trees
- Multiple save slots
- ASCII art for enemies
- Status effects (poison, burn, stun)
- Dungeon/area system

## Credits

**Developer:** Raihan(chyonma)
**GitHub:** [github.com/chyonma](https://github.com/chyonma)  
**Inspiration:** Dark Souls series  
**Built with:** C++, vanilla standard library  

## License

Free to use, modify, and distribute.
