#include "game.h"

// ---------------------- Character Implementation ---------------------- //

/**
 * @brief Constructs a Character with the given name, HP, and AP.
 */
Character::Character(const std::string &name, int hp, int ap)
    : name_(name), hp_(hp), ap_(ap), attackCount_(0) {}

/**
 * @brief Returns the character's name.
 */
std::string Character::getName() const 
{
    return name_;
}

/**
 * @brief Returns the character's current HP.
 */
int Character::getHP() const 
{
    return hp_;
}

/**
 * @brief Checks whether the character is alive.
 */
bool Character::isAlive() const 
{
    return hp_ > 0;
}

/**
 * @brief Decreases the character's HP by damage, without going below 0.
 */
void Character::receiveDamage(int damage) 
{
    hp_ = std::max(0, hp_ - damage);
}

/**
 * @brief Makes the character attack a target.
 *
 * Increments the attack counter. Uses the special attack on every third attack; otherwise, a normal attack.
 *
 * @param target The character to attack.
 */
void Character::attack(Character &target) 
{
    // Do nothing if this character is defeated.
    if (!isAlive()) return;
    attackCount_++;
    int damage = 0;
    // On every third attack, use special attack.
    if (attackCount_ % 3 == 0) 
    {
        damage = specialAttackDamage(target);
    } 
    else 
    {
        damage = ap_;
    }
    target.receiveDamage(damage);
}

// ---------------------- Archer Implementation ---------------------- //

/**
 * @brief Constructs an Archer.
 */
Archer::Archer(const std::string &name, int hp, int ap)
    : Character(name, hp, ap) {}

/**
 * @brief Calculates the Archer's special attack damage (Triple Shot).
 * @param target The target character (unused).
 * @return 3 × AP.
 */
int Archer::specialAttackDamage(const Character &target) const 
{
    (void)target; // Parameter unused.
    return 3 * ap_;
}

// ---------------------- Warrior Implementation ----------------------

/**
 * @brief Constructs a Warrior.
 */
Warrior::Warrior(const std::string &name, int hp, int ap)
    : Character(name, hp, ap) {}

/**
 * @brief Calculates the Warrior's special attack damage (Crushing Blow).
 * @param target The target character (unused).
 * @return AP + 15.
 */
int Warrior::specialAttackDamage(const Character &target) const 
{
    (void)target; // Parameter unused.
    return ap_ + 15;
}

// ---------------------- Mage Implementation ----------------------

/**
 * @brief Constructs a Mage.
 */
Mage::Mage(const std::string &name, int hp, int ap)
    : Character(name, hp, ap) {}

/**
 * @brief Calculates the Mage's special attack damage (Arcane Blast).
 *
 * Damage is computed as 2 × AP plus 50% of the target's current HP (using integer arithmetic).
 *
 * @param target The target character.
 * @return Calculated damage.
 */
int Mage::specialAttackDamage(const Character &target) const 
{
    return (2 * ap_) + (target.getHP() / 2);
}

// ---------------------- Enemy Implementation ----------------------

/**
 * @brief Constructs an Enemy.
 */
Enemy::Enemy(const std::string &name, int hp, int ap)
    : Character(name, hp, ap) {}

/**
 * @brief Calculates the Enemy's special attack damage (Savage Strike).
 * @param target The target character (unused).
 * @return 2 × AP.
 */
int Enemy::specialAttackDamage(const Character &target) const 
{
    (void)target; // Parameter unused.
    return 2 * ap_;
}

// ---------------------- Factory Function ----------------------

/**
 * @brief Factory function creates a character based on the provided type.
 *
 * @param type The type of character ("Archer", "Warrior", "Mage", or "Enemy").
 * @param name Name of the character.
 * @param hp Hit points.
 * @param ap Attack points.
 * @return Pointer to a new Character object.
 * @throws std::invalid_argument if the character type is unknown.
 */

Character* createCharacter(const std::string &type, const std::string &name, int hp, int ap) 
{
    if (type == "Archer") 
    {
        return new Archer(name, hp, ap);
    } 
    else if (type == "Warrior") 
    {
        return new Warrior(name, hp, ap);
    } 
    else if (type == "Mage") 
    {
        return new Mage(name, hp, ap);
    } 
    else if (type == "Enemy") 
    {
        return new Enemy(name, hp, ap);
    } 
    else 
    {
        throw std::invalid_argument("Unknown character type: " + type);
    }
}

// ---------------------- GameManager Implementation ---------------------- //

/**
 * @brief Destructor for GameManager.
 *
 * Frees all dynamically allocated character objects.
 */
GameManager::~GameManager() 
{
    for (Character* hero : heroes_) 
    {
        delete hero;
    }
    for (Character* enemy : enemies_) 
    {
        delete enemy;
    }
}

/**
 * @brief Loads characters from a file.
 *
 * The file must have one character per line in the following format:
 * `<CharacterType> <Name> <HP> <AP>`
 *
 * @param filename Path to the input file.
 * @throws std::runtime_error if the file cannot be opened or the format is invalid.
 */
void GameManager::loadCharacters(const std::string &filename) 
{
    std::ifstream infile(filename);
    if (!infile.is_open()) 
    {
        throw std::runtime_error("Error opening file: " + filename);
    }
    
    std::string line;
    while (std::getline(infile, line)) 
    {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string type, name;
        int hp, ap;
        if (!(iss >> type >> name >> hp >> ap)) 
        {
            throw std::runtime_error("Invalid line format: " + line);
        }
        Character* character = createCharacter(type, name, hp, ap);

        // Categorize into heroes or enemies based on the character type.
        if (type == "Enemy") 
        {
            enemies_.push_back(character);
        } 
        else 
        {
            heroes_.push_back(character);
        }
    }
    infile.close();
}

/**
 * @brief Simulates the battle between heroes and enemies.
 *
 * The simulation alternates turns:
 * - Heroes' turn: each alive hero attacks the first alive enemy.
 * - Enemies' turn: each alive enemy attacks the first alive hero.
 * The simulation stops when one side is entirely defeated.
 */
void GameManager::runBattle() 
{
    while (true) 
    {
        // Heroes' turn.
        for (Character* hero : heroes_) 
        {
            if (hero->isAlive()) 
            {
                Character* target = nullptr;
                for (Character* enemy : enemies_) 
                {
                    if (enemy->isAlive()) 
                    {
                        target = enemy;
                        break;
                    }
                }
                if (target == nullptr) return; // All enemies defeated.
                hero->attack(*target);
            }
        }
        
        // Check if any enemy is still alive.
        bool enemyAlive = false;
        for (Character* enemy : enemies_) 
        {
            if (enemy->isAlive()) 
            {
                enemyAlive = true;
                break;
            }
        }
        if (!enemyAlive) break;
        
        // Enemies' turn.
        for (Character* enemy : enemies_) 
        {
            if (enemy->isAlive()) 
            {
                Character* target = nullptr;
                for (Character* hero : heroes_) 
                {
                    if (hero->isAlive()) 
                    {
                        target = hero;
                        break;
                    }
                }
                if (target == nullptr) return; // All heroes defeated.
                enemy->attack(*target);
            }
        }
        
        // Check if any hero is still alive.
        bool heroAlive = false;
        for (Character* hero : heroes_) 
        {
            if (hero->isAlive()) 
            {
                heroAlive = true;
                break;
            }
        }
        if (!heroAlive) break;
    }
}

/**
 * @brief Determines the outcome of the battle.
 *
 * @return A string indicating the outcome:
 * - "Your party has won the battle!"
 * - "The enemies have won the battle!"
 * - "The battle ended in a draw!" (if both sides are defeated simultaneously)
 */
std::string GameManager::determineOutcome() const 
{
    bool anyHeroAlive = false;
    bool anyEnemyAlive = false;
    
    for (const Character* hero : heroes_) 
    {
        if (hero->isAlive()) 
        {
            anyHeroAlive = true;
            break;
        }
    }
    for (const Character* enemy : enemies_) 
    {
        if (enemy->isAlive()) 
        {
            anyEnemyAlive = true;
            break;
        }
    }
    
    if (anyHeroAlive && !anyEnemyAlive) 
    {
        return "Your party has won the battle!";
    } 
    else if (!anyHeroAlive && anyEnemyAlive) 
    {
        return "The enemies have won the battle!";
    } 
    else if (!anyHeroAlive && !anyEnemyAlive) 
    {
        return "The battle ended in a draw!";
    }
    return "";
}

/**
 * @brief Prints the final status of all characters and the battle outcome.
 *
 * Characters are printed in the order:
 * - Heroes (in order read from the file)
 * - Enemies (in order read from the file)
 *
 * Each character's status is displayed as:
 * `{Name} - HP: {hit_points}, Status: {Alive/Defeated}`
 */
void GameManager::printResults() const 
{
    // Print heroes.
    for (const Character* hero : heroes_) 
    {
        std::cout << hero->getName() << " - HP: " << hero->getHP()
                  << ", Status: " << (hero->isAlive() ? "Alive" : "Defeated") << "\n";
    }
    // Print enemies.
    for (const Character* enemy : enemies_) 
    {
        std::cout << enemy->getName() << " - HP: " << enemy->getHP()
                  << ", Status: " << (enemy->isAlive() ? "Alive" : "Defeated") << "\n";
    }
    // Print final outcome.
    std::cout << determineOutcome() << "\n";
}
