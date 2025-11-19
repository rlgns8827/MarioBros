// Kihoon Yoo
// 2486883
// kiyoo@chapman.edu 
// CPSC-350-03
// PA 2: Not So Super Mario Bros

#include "Mario.h"
#include <cstdlib>  

// Initialize Mario's stats and position
Mario::Mario(int initialLives) {
    lives = initialLives;
    coins = 0;
    powerLevel = 0;
    enemiesDefeated = 0;
    row = 0;
    col = 0;
}

// Gain coin; +1 life for every 20 coins
void Mario::collectCoin() {
    coins++;
    if (coins >= 20) {
        lives++;
        coins = 0;
    }
}

// Eat mushroom to raise power (max PL2)
void Mario::eatMushroom() {
    if (powerLevel < 2)
        powerLevel++;
}

// Fight Goomba (80%) or Koopa (65%); returns true if win
bool Mario::fightEnemy(char type) {
    int winChance = (type == 'g') ? 80 : 65;
    int roll = std::rand() % 100;

    if (roll < winChance) {                 // win case
        enemiesDefeated++;
        if (enemiesDefeated == 7) {         // bonus life after 7 wins
            lives++;
            enemiesDefeated = 0;
        }
        return true;
    }

    enemiesDefeated = 0;                    // loss resets streak
    if (powerLevel == 0) lives--;           // lose life if weak
    else powerLevel--;                      // otherwise lose power
    return false;
}

// Boss fight (50% win); returns result constant
int Mario::fightBoss() {
    int roll = std::rand() % 100;
    enemiesDefeated = 0;

    if (roll < 50) return BOSS_WIN;         // win

    if (powerLevel == 2) {                  // lose from PL2 → retry
        powerLevel = 0;
        return BOSS_LOSE_RETRY;
    }

    lives--;                                // lose life otherwise
    powerLevel = 0;
    if (lives <= 0) return BOSS_LOSE_DEAD;  // game over
    return BOSS_LOSE_RETRY;                 // retry if still alive
}
