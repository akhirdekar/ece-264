# RPG Turn-Based Battle Game

## Description
This is a simple turn-based RPG battle game implemented in C++. The game follows a structured turn-based combat system where heroes and enemies take turns attacking each other until one side is fully defeated. It demonstrates C++ fundamentals and object-oriented design (OOP) principles.

## Features
- Four character types: **Archer, Warrior, Mage, and Enemy**, each with unique base and special attacks.
- **Turn-based combat** where each hero and enemy attacks in order.
- **Special attacks** automatically activate every third attack.
- **Battle system** where characters attack the first alive enemy or hero.
- **File-based character loading** from a structured text file.
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
- Make (if using Makefile)

### Steps to Compile and Run:
```sh
# Clone the repository
git clone https://github.com/yourusername/RPG-Game.git
cd RPG-Game

# Compile the game (assuming a Makefile is provided)
make

# Run the game
./rpg_game
```
If compiling manually without a Makefile:
```sh
g++ -o rpg_game src/*.cpp -I src/
./rpg_game
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
Example:
```txt
Archer Legolas 100 20
Warrior Conan 150 25
Mage Merlin 120 30
Enemy Orc 90 15
```

## Project Structure
```
RPG-Game/
│── src/                # All C++ source code files
│── assets/             # (Optional) Images, sounds, additional files
│── docs/               # Documentation, flowcharts, etc.
│── test/               # Test cases (if applicable)
│── .clang-format       # Formatting configuration
│── .gitignore          # Ignore unnecessary files
│── Makefile / CMakeLists.txt # Build system
│── README.md           # Main documentation file
```

## Contributors
- **Your Name** (@yourgithubhandle)

## License
This project is open-source under the MIT License.

