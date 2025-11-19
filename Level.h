// Kihoon Yoo
// 2486883
// kiyoo@chapman.edu 
// CPSC-350-03
// PA 2: Not So Super Mario Bros

#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>

// Single NxN game level
class Level {
private:
    int size;        // grid dimension
    char** grid;     // 2D grid of elements

    void placeRandom(char symbol, int count); // helper for random placement

public:
    Level();
    Level(int gridSize);
    ~Level();

    void populateLevel(int coinPct, int emptyPct, int goombaPct,
                       int koopaPct, int mushroomPct, bool hasWarp);

    char getPosition(int r, int c) const;
    void setPosition(int r, int c, char val);
    int getSize() const;

    void printLevelWithMario(std::ofstream& outFile, int marioRow, int marioCol) const;
    void printLevel(std::ofstream& outFile) const;
};

#endif // LEVEL_H
