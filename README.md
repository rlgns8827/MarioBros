# Not So Super Mario

#### Overview
This project showcases my proficiency in data structures and algorithms with a focus on array manipulation and object-oriented programming in C++. The simulation of Super Mario involves reading level data from input files, processing and managing gameplay states, and writing results to output files. Mario navigates through a multi-level world represented by a 3D array, interacting dynamically with his environment through a series of conditional events and game logic structures.

#### Key features
- Mario Simulation: Simulates Mario navigating the grid, interacting with the environment, battling enemies, collecting coins, eating mushrooms, and moving through levels.
- Randomized World Generation: Builds a multi-level world based on runtime parameters, with randomized placement of coins, enemies, mushrooms, bosses, and warp pipes.
- Life and Power Management: Tracks Mario’s lives, coins (extra lives earned after collecting 20 coins), and power levels (PL0, PL1, PL2).
- Battle Logic: Includes probabilistic outcomes for battles against Goombas, Koopas, and Bosses, affecting Mario’s survival and power level.
- Toroidal Grid Movement: Implements grid wrapping horizontally and vertically to allow continuous movement (torus behavior).
- Warp Pipes: Allows Mario to instantly advance to the next level if a warp pipe is found.
- Detailed Logging: Records every move Mario makes into an output text file, including actions taken, Mario’s state, and the updated map.
- Array-Only Data Structure: Implements the world using a 3D L x N x N array of characters without using any advanced data structures like vector or list.

#### How to Run
To compile and run the program:

1. **Compile**: Use g++ to compile the `main.cpp` file.
   ```bash
   g++ main.cpp -o mario 
   ```

2. **Run**: Execute the compiled program with the input file name as a command-line argument.
   ```bash
   ./mario_game input.txt output.txt
   ```

#### Requirements
- C++ compiler (tested with g++)
- Text editor or IDE (e.g., VSCode) for code editing
- Terminal or command prompt for running compiled executable

#### References
- No external libraries or non-primitive data structures (e.g., vectors) are used, as per project requirements.

