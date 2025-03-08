/**
 * @file game.h
 * @brief Header file for the turn-based RPG game.
 *
 * ECE 264: Assignment 1
 * @author Abhijeet Khirdekar <abhijeet.khirdekar@cooper.edu>
 * 
 * This file contains the core classes and functions used in the RPG battle simulation.
 * It defines a base class 'Character' and derived classes for character types Archer, Warrior, Mage, and Enemy. 
 * It also provides a factory function to create characters and a GameManager class 
 * to handle game initialization, simulation, and output.
 * 
 * Classes:
 * - Character (Base class): Defines shared attributes (name, HP, AP, attack count).
 * - Archer: Special attack (Triple Shot) deals 3×AP damage.
 * - Warrior: Special attack (Crushing Blow) deals AP + 15 damage.
 * - Mage: Special attack (Arcane Blast) deals 2×AP + 50% of target's current HP.
 * - Enemy: Special attack (Savage Strike) deals 2×AP damage.
 * - GameManager' Handles game initialization, combat simulation, and result output.
 *
 * Game Rules:
 * - Characters take turns attacking: heroes attack first, then enemies.
 * - Every third attack triggers a special attack.
 * - A character is defeated when HP reaches 0.
 * - The game continues until all heroes or all enemies are defeated.
 * - The program reads character data from an input text file and simulates combat.
 * - The final battle results are printed.
 * 
 */

 #pragma once

 #include <string>
 #include <vector>
 #include <stdexcept>
 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include <algorithm>
 
 /**
  * @class Character
  * @brief Base class for all characters in the game.
  *
  * This class encapsulates common properties (name, HP, AP, and attack count) and methods
  * for all characters. Derived classes override the specialAttackDamage method to provide 
  * character-specific special attack logic.
  */
 class Character {
 protected:
     std::string name_;   ///< Name of the character.
     int hp_;             ///< Current hit points.
     int ap_;             ///< Base attack points.
     int attackCount_;    ///< Cumulative count of attacks made.
 
 public:
     /**
      * @brief Constructor for Character.
      * @param name Name of the character.
      * @param hp Initial hit points.
      * @param ap Attack points.
      */
     Character(const std::string &name, int hp, int ap);
     
     /// Virtual destructor.
     virtual ~Character() = default;
     
     /**
      * @brief Get the name of the character.
      * @return Name as a std::string.
      */
     std::string getName() const;
     
     /**
      * @brief Get the current hit points.
      * @return Current HP.
      */
     int getHP() const;
     
     /**
      * @brief Check if the character is alive.
      * @return True if HP > 0, otherwise false.
      */
     bool isAlive() const;
     
     /**
      * @brief Reduces the character's HP by the specified damage.
      *
      * The character's HP will not drop below 0.
      *
      * @param damage Amount of damage to subtract.
      */
     void receiveDamage(int damage);
     
     /**
      * @brief Perform an attack on a target character.
      *
      * Increments the attack counter. On every third attack, the character uses its special attack.
      * Otherwise, it uses a normal attack (dealing damage equal to its AP).
      *
      * @param target The character being attacked.
      */
     void attack(Character &target);
     
 protected:
     /**
      * @brief Calculate the damage for the special attack.
      *
      * This is a pure virtual function and must be overridden by derived classes.
      *
      * @param target The target character (used by Mage special attack).
      * @return Damage value for the special attack.
      */
     virtual int specialAttackDamage(const Character &target) const = 0;
 };
 
 /**
  * @class Archer
  * @brief Derived class representing an Archer.
  *
  * The Archer's special attack (Triple Shot) deals 3×AP damage.
  */
 class Archer : public Character {
 public:
     /**
      * @brief Constructor for Archer.
      * @param name Name of the Archer.
      * @param hp Initial hit points.
      * @param ap Attack points.
      */
     Archer(const std::string &name, int hp, int ap);
     
 protected:
     /**
      * @brief Calculate the Archer's special attack damage.
      * @param target The target character (unused for Archer).
      * @return Damage equal to 3×AP.
      */
     int specialAttackDamage(const Character &target) const override;
 };
 
 /**
  * @class Warrior
  * @brief Derived class representing a Warrior.
  *
  * The Warrior's special attack (Crushing Blow) deals damage equal to AP + 15.
  */
 class Warrior : public Character {
 public:
     /**
      * @brief Constructor for Warrior.
      * @param name Name of the Warrior.
      * @param hp Initial hit points.
      * @param ap Attack points.
      */
     Warrior(const std::string &name, int hp, int ap);
     
 protected:
     /**
      * @brief Calculate the Warrior's special attack damage.
      * @param target The target character (unused for Warrior).
      * @return Damage equal to AP + 15.
      */
     int specialAttackDamage(const Character &target) const override;
 };
 
 /**
  * @class Mage
  * @brief Derived class representing a Mage.
  *
  * The Mage's special attack (Arcane Blast) deals damage equal to 2×AP plus 50% of the target's current HP.
  */
 class Mage : public Character {
 public:
     /**
      * @brief Constructor for Mage.
      * @param name Name of the Mage.
      * @param hp Initial hit points.
      * @param ap Attack points.
      */
     Mage(const std::string &name, int hp, int ap);
     
 protected:
     /**
      * @brief Calculate the Mage's special attack damage.
      *
      * @param target The target character.
      * @return Damage equal to 2×AP plus 50% of the target's current HP (using integer arithmetic).
      */
     int specialAttackDamage(const Character &target) const override;
 };
 
 /**
  * @class Enemy
  * @brief Derived class representing an Enemy.
  *
  * The Enemy's special attack (Savage Strike) deals damage equal to 2×AP.
  */
 class Enemy : public Character {
 public:
     /**
      * @brief Constructor for Enemy.
      * @param name Name of the Enemy.
      * @param hp Initial hit points.
      * @param ap Attack points.
      */
     Enemy(const std::string &name, int hp, int ap);
     
 protected:
     /**
      * @brief Calculate the Enemy's special attack damage.
      * @param target The target character (unused for Enemy).
      * @return Damage equal to 2×AP.
      */
     int specialAttackDamage(const Character &target) const override;
 };
 
 /**
  * @brief Factory function to create a Character object based on type.
  *
  * @param type The character type (e.g., "Archer", "Warrior", "Mage", "Enemy").
  * @param name The name of the character.
  * @param hp Hit points.
  * @param ap Attack points.
  * @return Pointer to a newly created Character.
  * @throws std::invalid_argument if the character type is unknown.
  */
 Character* createCharacter(const std::string &type, const std::string &name, int hp, int ap);
 
 /**
  * @class GameManager
  * @brief Class to manage the game.
  *
  * The GameManager handles loading characters from a file, running the battle simulation,
  * and printing the final results.
  */
 class GameManager {
 private:
     std::vector<Character*> heroes_;  ///< List of hero characters (Archer, Warrior, Mage).
     std::vector<Character*> enemies_; ///< List of enemy characters.
     
 public:
     /// Destructor to free allocated memory.
     ~GameManager();
     
     /**
      * @brief Load characters from a specified file.
      *
      * Each line in the file should have the format:
      * `<CharacterType> <Name> <HP> <AP>`
      *
      * @param filename Path to the input file.
      * @throws std::runtime_error if the file cannot be opened or a line is improperly formatted.
      */
     void loadCharacters(const std::string &filename);
     
     /**
      * @brief Run the battle simulation.
      *
      * The battle proceeds in rounds:
      * - Heroes attack first (each alive hero attacks the first alive enemy).
      * - Enemies then attack (each alive enemy attacks the first alive hero).
      * The simulation stops when one side is completely defeated.
      */
     void runBattle();
     
     /**
      * @brief Print the final status of each character and the battle outcome.
      *
      * The status is printed in the format:
      * `{Name} - HP: {hit_points}, Status: {Alive/Defeated}`
      * Heroes are printed first, followed by enemies.
      */
     void printResults() const;
     
     /**
      * @brief Determine the battle outcome.
      *
      * @return A string indicating the battle result:
      * - "Your party has won the battle!"
      * - "The enemies have won the battle!"
      * - "The battle ended in a draw!"
      */
     std::string determineOutcome() const;
 };
 
