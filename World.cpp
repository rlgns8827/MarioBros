// Kihoon Yoo
// 2486883
// kiyoo@chapman.edu 
// CPSC-350-03
// PA 2: Not So Super Mario Bros

#include "World.h"
#include <iostream>
#include <fstream>
#include <cstdlib>  

// Default constructor
World::World() {
    levels = 0;
    gameLevels = 0;
    mario = 0;
}

// Read setup from input file and build the game world
World::World(const std::string& inputFile) {
    std::ifstream file(inputFile.c_str());
    if (!file.is_open()) {
        std::cerr << "Error opening input file\n";
        std::exit(1);
    }

    int gridSize, lives;
    int coinPct, emptyPct, goombaPct, koopaPct, mushroomPct;

    // Input order: L, N, lives, and percentages of each element
    file >> levels >> gridSize >> lives;
    file >> coinPct >> emptyPct >> goombaPct >> koopaPct >> mushroomPct;
    file.close();

    // Percentages must add up to 100%
    if (coinPct + emptyPct + goombaPct + koopaPct + mushroomPct != 100) {
        std::cerr << "Percentages must sum to 100.\n";
        std::exit(1);
    }

    mario = new Mario(lives);

    // Create and populate all levels
    gameLevels = new Level*[levels];
    for (int i = 0; i < levels; ++i) {
        gameLevels[i] = new Level(gridSize);
        bool hasWarp = (i != levels - 1); // no warp in last level
        gameLevels[i]->populateLevel(coinPct, emptyPct, goombaPct,
                                     koopaPct, mushroomPct, hasWarp);
    }
}

// Destructor to free all memory
World::~World() {
    if (mario) delete mario;
    if (gameLevels) {
        for (int i = 0; i < levels; ++i)
            delete gameLevels[i];
        delete[] gameLevels;
    }
}

// Accessors
int World::getLevelCount() const { return levels; }
Level* World::getLevel(int i) const { return gameLevels[i]; }
Mario* World::getMario() const { return mario; }

// Main game loop for one level
void World::playLevel(int levelIdx, std::ofstream& logFile) {
    static bool printedInitial = false;

    // Print initial layout of all levels once at the start
    if (!printedInitial) {
        for (int i = 0; i < levels; ++i) {
            logFile << "Initial layout of Level " << (i + 1) << ":\n";
            gameLevels[i]->printLevel(logFile);
            logFile << "\n";
        }
        printedInitial = true;
    }

    Level* lvl = gameLevels[levelIdx];
    int N = lvl->getSize();

    // Place Mario on a random empty space
    do {
        mario->row = std::rand() % N;
        mario->col = std::rand() % N;
    } while (lvl->getPosition(mario->row, mario->col) != 'x');

    logFile << "Mario starting position: (" << mario->row << "," << mario->col << ")\n";
    lvl->printLevelWithMario(logFile, mario->row, mario->col);
    logFile << "\n";

    int pendingDir = std::rand() % 4;  // choose initial random move
    int moves = 0;                     // track total moves

    // Continue until Mario loses all lives or wins
    while (mario->lives > 0) {
        int dir = pendingDir;
        int newR = mario->row;
        int newC = mario->col;

        // Move randomly (grid wraps around)
        if (dir == 0) newR = (newR - 1 + N) % N;
        else if (dir == 1) newR = (newR + 1) % N;
        else if (dir == 2) newC = (newC - 1 + N) % N;
        else newC = (newC + 1) % N;

        char tile = lvl->getPosition(newR, newC);
        int nextPendingDir = std::rand() % 4;
        std::string nextMoveStr =
            (nextPendingDir == 0 ? "UP" :
            (nextPendingDir == 1 ? "DOWN" :
            (nextPendingDir == 2 ? "LEFT" : "RIGHT")));

        //  Boss Fight Section
        if (tile == 'b') {
            mario->row = newR;
            mario->col = newC;
            while (true) {
                int prePower = mario->powerLevel;
                int result = mario->fightBoss();

                if (result == Mario::BOSS_WIN) {
                    lvl->setPosition(mario->row, mario->col, 'x');
                    logFile << "Level " << (levelIdx + 1)
                            << " | (" << mario->row << "," << mario->col << ")"
                            << " | Power before: " << prePower
                            << " | Action: fought the level boss and won"
                            << " | Lives: " << mario->lives
                            << " | Coins: " << mario->coins
                            << " | Next move: STAY PUT\n";
                    lvl->printLevelWithMario(logFile, mario->row, mario->col);
                    logFile << "\n";
                    moves++;
                    if (levelIdx == levels - 1) {
                        logFile << "Mario Wins! The princess is saved!\n";
                        logFile << "Mario won in " << moves << " moves.\n";
                    }
                    return;
                }

                // Boss loss cases
                if (mario->lives <= 0) {
                    logFile << "Level " << (levelIdx + 1)
                            << " | (" << mario->row << "," << mario->col << ")"
                            << " | Power before: " << prePower
                            << " | Action: fought the level boss and lost"
                            << " | Lives: " << mario->lives
                            << " | Coins: " << mario->coins
                            << " | Next move: STAY PUT\n";
                    lvl->printLevelWithMario(logFile, mario->row, mario->col);
                    logFile << "\nMario lost all lives and the game is over.\n";
                    logFile << "Mario lost in " << (moves + 1) << " moves.\n";
                    return;
                } else {
                    // Lost but can retry
                    logFile << "Level " << (levelIdx + 1)
                            << " | (" << mario->row << "," << mario->col << ")"
                            << " | Power before: " << prePower
                            << " | Action: fought the level boss and lost"
                            << " | Lives: " << mario->lives
                            << " | Coins: " << mario->coins
                            << " | Next move: STAY PUT\n";
                    lvl->printLevelWithMario(logFile, mario->row, mario->col);
                    logFile << "\n";
                    moves++;
                }
            }
        }

        //  Warp Pipe Section
        if (tile == 'w') {
            mario->row = newR;
            mario->col = newC;
            lvl->setPosition(newR, newC, 'x');
            int prePower = mario->powerLevel;

            logFile << "Level " << (levelIdx + 1)
                    << " | (" << mario->row << "," << mario->col << ")"
                    << " | Power before: " << prePower
                    << " | Action: warped to next level"
                    << " | Lives: " << mario->lives
                    << " | Coins: " << mario->coins
                    << " | Next move: " << nextMoveStr << "\n";
            lvl->printLevelWithMario(logFile, mario->row, mario->col);
            logFile << "\n";
            moves++;

            levelIdx++;
            if (levelIdx < levels) {
                logFile << "--- Mario warped to Level " << (levelIdx + 1) << " ---\n";
                gameLevels[levelIdx]->printLevel(logFile);
                logFile << "\n";
            } else {
                logFile << "Mario reached the end through warp!\n";
                logFile << "Mario won in " << moves << " moves.\n";
            }
            return;
        }

        //  Regular Tile Section
        mario->row = newR;
        mario->col = newC;
        int prePower = mario->powerLevel;
        std::string action;

        // Handle interactions based on what Mario lands on
        if (tile == 'c') {
            mario->collectCoin();
            lvl->setPosition(newR, newC, 'x');
            action = "collected a coin";
        } else if (tile == 'm') {
            mario->eatMushroom();
            lvl->setPosition(newR, newC, 'x');
            action = "ate a mushroom";
        } else if (tile == 'g' || tile == 'k') {
            bool won = mario->fightEnemy(tile);
            if (won) {
                lvl->setPosition(newR, newC, 'x');
                action = (tile == 'g') ? "fought a Goomba and won" : "fought a Koopa and won";
            } else {
                action = (tile == 'g') ? "fought a Goomba and lost" : "fought a Koopa and lost";
            }
        } else {
            action = "the position is empty";
        }

        // Log current move
        logFile << "Level " << (levelIdx + 1)
                << " | (" << mario->row << "," << mario->col << ")"
                << " | Power before: " << prePower
                << " | Action: " << action
                << " | Lives: " << mario->lives
                << " | Coins: " << mario->coins
                << " | Next move: " << nextMoveStr << "\n";
        lvl->printLevelWithMario(logFile, mario->row, mario->col);
        logFile << "\n";
        moves++;

        // End game if no lives remain
        if (mario->lives <= 0) {
            logFile << "Mario lost all lives and the game is over.\n";
            logFile << "Mario lost in " << moves << " moves.\n";
            return;
        }

        pendingDir = nextPendingDir; // continue next random move
    }
}
