// Kihoon Yoo
// 2486883
// kiyoo@chapman.edu
// CPSC-350-03
// PA 2: Not So Super Mario Bros

#include "World.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

// Entry point for the Mario simulation
int main(int argc, char* argv[]) {
    // Require exactly two command-line arguments
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>\n";
        return 1;
    }

    // Seed random number generator for varied runs
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    // Open output log file
    std::ofstream logFile(outputFile);
    if (!logFile.is_open()) {
        std::cerr << "Error: Could not open output file.\n";
        return 1;
    }

    // Build the game world from the input file
    World world(inputFile);

    // Play through all levels until Mario dies or wins
    for (int i = 0; i < world.getLevelCount() && world.getMario()->lives > 0; ++i) {
        world.playLevel(i, logFile);
        if (world.getMario()->lives <= 0) break;
    }

    logFile.close();
    return 0;
}
