# RPG Turn-Based Battle Game

## Description
This is a simple turn-based RPG battle game implemented in C++. The game follows a structured turn-based combat system where heroes and enemies take turns attacking each other until one side is fully defeated. Each character has a name, hit points (HP), and attack points (AP). The program loads characters from a structured input file

## Features
- There are four character types: **Archer, Warrior, Mage, and Enemy**, each with unique base and special attacks.
- **Turn-based combat** where each hero and enemy attacks in order.
- **Special attacks** automatically activate every third attack.
- **Battle system** where characters attack the first alive enemy or hero.
- **File-based character loading** from a sample text file.
- **Game Manager** that handles character turns and victory conditions.

## Character Classes & Special Attacks
- **Archer**: Shoots arrows (base) and performs *Triple Shot* (triples AP).
- **Warrior**: Swings a sword (base) and executes *Crushing Blow* (+15 AP).
- **Mage**: Casts fireballs (base) and unleashes *Arcane Blast* (double AP + 50% target’s HP).
- **Enemy**: Basic attack and *Savage Strike* (doubles AP).

## Game Rules
- Characters attack in turns; heroes first, then enemies.
- Defeated characters (HP = 0) cannot attack or be attacked.
- Special attacks activate automatically every third attack.
- The battle ends when all heroes or all enemies are defeated.

## Installation & Compilation
### Requirements:
- C++ Compiler (g++ or Clang recommended)
- Make or CMake

## Steps to Compile and Run:
```sh
Using Makefile:

# Clone the repository
git clone https://github.com/akhirdekar/RPG-Game.git
cd RPG-Game

# Compile the game
make

# Run the game with an input file
./rpg_game data/sample_input.txt
```
```sh
Using CMake:

mkdir build
cmake -B build/
cmake --build build/
./build/rpg_game data/sample_input.txt
```

## How to Play
1. The game loads characters from a text file.
2. Heroes and enemies take turns attacking.
3. Each character automatically uses their special attack every third attack.
4. The game ends when one side is completely defeated.

## Input Format
Characters are loaded from a text file where each line contains:
```txt
<character_type> <name> <HP> <AP>
```
Example (Sample provided in sample_input.txt):
```txt
Archer Legolas 100 20
Warrior Conan 150 25
Mage Merlin 120 30
Enemy Orc 90 15
```

## Copyright & Licensing

**Copyright (C) 2025 Abhijeet Khirdekar** | <akhirdekar144@gmail.com>

Distributed under the *MIT License*. See [LICENSE](https://github.com/akhirdekar/ece-264/blob/main/LICENSE) for details.

*This project was created as part of the coursework for *ECE-264: Data Strucutres and Algorithms I*, taught by [Professor Von Bargen](https://github.com/cdvonbargen)) during the Spring 2025 semester at The Cooper Union.*

