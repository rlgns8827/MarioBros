// Kihoon Yoo
// 2486883
// kiyoo@chapman.edu 
// CPSC-350-03
// PA 2: Not So Super Mario Bros

#ifndef MARIO_H
#define MARIO_H

// Represents Mario and his stats/actions
class Mario {
public:
    int lives;             // remaining lives
    int coins;             // collected coins
    int powerLevel;        // 0 = weak, 2 = strong
    int row, col;          // current grid position
    int enemiesDefeated;   // streak for bonus life

    // Boss fight outcomes
    static const int BOSS_WIN        = 0;
    static const int BOSS_LOSE_RETRY = 1;
    static const int BOSS_LOSE_DEAD  = 2;

    Mario(int initialLives);

    void collectCoin();     // gain coins, +1 life per 20
    void eatMushroom();     // raise power up to PL2
    bool fightEnemy(char type); // fight Goomba/Koopa
    int fightBoss();        // fight boss, returns outcome
};

#endif // MARIO_H
