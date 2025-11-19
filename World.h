// Kihoon Yoo
// 2486883
// kiyoo@chap`n.edu 
// CPSC-350-03
// PA 2: Not So Super Mario Bros

#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <fstream>
#include "Level.h"
#include "Mario.h"

// Manages all levels and game flow
class World {
private:
    int levels;          // total number of levels
    Level** gameLevels;  // array of level pointers
    Mario* mario;        // Mario instance

public:
    World();
    World(const std::string& inputFile);
    ~World();

    void playLevel(int levelIdx, std::ofstream& logFile); // run one level

    int getLevelCount() const;
    Level* getLevel(int i) const;
    Mario* getMario() const;
};

#endif // WORLD_H
