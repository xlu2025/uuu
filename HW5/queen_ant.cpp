#include "queen_ant.hpp"
#include "simulation.hpp"
#include <cstdlib>
#include <ctime>

QueenAnt::QueenAnt(int r, int c) : Ant(r, c, false), mated(false), breedSteps(0) {}

// Move method for QueenAnt
void QueenAnt::move(Simulation* sim) {
    if (!mated) {
        return; // Queen doesn't move until it has mated
    }
    Ant::move(sim);
}

// Breed method for QueenAnt
void QueenAnt::breed(Simulation* sim) {
    if (breedSteps >= 30) {
        static const int directions[16][2] = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1},  // Up, Down, Left, Right
            {-1, -1}, {-1, 1}, {1, -1}, {1, 1}, // 4 corners
            {-2, 0}, {2, 0}, {0, -2}, {0, 2},  // 2 steps in 4 main directions
            {-2, -2}, {-2, 2}, {2, -2}, {2, 2} // 2 steps in 4 diagonal directions
        };

        for (int i = 0; i < 16; ++i) {
            int newRow = row + directions[i][0];
            int newCol = col + directions[i][1];

            if (sim->isInBounds(newRow, newCol) && sim->isCellEmpty(newRow, newCol)) {
                srand(time(nullptr));
                bool isMale = rand() % 2;
                sim->addOrganism(new Ant(newRow, newCol, isMale));
                if (isMale) { sim->numMaleAnts++; }
                else { sim->numFemaleAnts++; }
            }
        }

        breedSteps = 0;
    }
    else {
        breedSteps++;
    }
}

// Starve method for QueenAnt
void QueenAnt::starve(Simulation* sim) {
    // QueenAnts do not starve
}