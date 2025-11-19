// Kihoon Yoo
// 2486883
// kiyoo@chapman.edu 
// CPSC-350-03
// PA 2: Not So Super Mario Bros

#include "Level.h"
#include <cstdlib>  

// Constructor — initialize empty level
Level::Level() {
    size = 0;
    grid = 0;
}

// Overloaded constructor — create NxN grid filled with 'x'
Level::Level(int gridSize) {
    size = gridSize;

    grid = new char*[size];
    for (int i = 0; i < size; ++i) {
        grid[i] = new char[size];
        for (int j = 0; j < size; ++j)
            grid[i][j] = 'x';  // 'x' means empty tile
    }
}

// Destructor — deallocate dynamic 2D array
Level::~Level() {
    if (grid) {
        for (int i = 0; i < size; ++i)
            delete[] grid[i];
        delete[] grid;
    }
}

// Randomly place a given symbol (coin, enemy, etc.) in empty cells
void Level::placeRandom(char symbol, int count) {
    while (count > 0) {
        int r = std::rand() % size;
        int c = std::rand() % size;

        if (grid[r][c] == 'x') {
            grid[r][c] = symbol;
            count--;
        }
    }
}

// Populate the level grid according to the given element percentages
void Level::populateLevel(int coinPct, int emptyPct, int goombaPct,
                          int koopaPct, int mushroomPct, bool hasWarp)
{
    int totalCells = size * size;

    // Calculate number of each item type
    int numCoins     = totalCells * coinPct     / 100;
    int numGoombas   = totalCells * goombaPct   / 100;
    int numKoopas    = totalCells * koopaPct    / 100;
    int numMushrooms = totalCells * mushroomPct / 100;

    // Initialize grid as empty
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            grid[i][j] = 'x';

    // Place basic elements randomly
    placeRandom('c', numCoins);     // coins
    placeRandom('g', numGoombas);   // Goombas
    placeRandom('k', numKoopas);    // Koopas
    placeRandom('m', numMushrooms); // mushrooms

    // Place exactly one boss ('b')
    int br, bc;
    do {
        br = std::rand() % size;
        bc = std::rand() % size;
    } while (grid[br][bc] != 'x');
    grid[br][bc] = 'b';

    // If not the last level, place one warp ('w')
    if (hasWarp) {
        int wr, wc;
        do {
            wr = std::rand() % size;
            wc = std::rand() % size;
        } while (grid[wr][wc] != 'x');
        grid[wr][wc] = 'w';
    }
}

// Return what’s currently at position (r,c)
char Level::getPosition(int r, int c) const {
    if (r >= 0 && r < size && c >= 0 && c < size)
        return grid[r][c];
    return 'x';
}

// Replace symbol at position (r,c)
void Level::setPosition(int r, int c, char val) {
    if (r >= 0 && r < size && c >= 0 && c < size)
        grid[r][c] = val;
}

// Get the grid size (N)
int Level::getSize() const {
    return size;
}

// Print the level layout with spaces between cells
void Level::printLevel(std::ofstream& outFile) const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            outFile << grid[i][j];
            if (j < size - 1) outFile << ' ';
        }
        outFile << "\n";
    }
}

// Print the layout with Mario’s position ('H') marked
void Level::printLevelWithMario(std::ofstream& outFile, int marioRow, int marioCol) const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == marioRow && j == marioCol)
                outFile << 'H';
            else
                outFile << grid[i][j];
            if (j < size - 1) outFile << ' ';
        }
        outFile << "\n";
    }
}
