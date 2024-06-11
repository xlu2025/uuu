#pragma once

#include "organism.hpp"
#include <vector>

class Simulation {
    friend class Ant;
    friend class QueenAnt;
    friend class DoodleBug;
private:
    int rows;
    int cols;
    int time_steps;
public:
    int numMaleAnts;
    int numFemaleAnts;
    int numDoodlebugs;
    int numQueens;
    vector<vector<Organism*>> grid;
    Simulation(int r, int c, int steps, int maleants, int femaleants, int doodlebugs, int queens)
        : rows(r), cols(c), time_steps(steps), numMaleAnts(maleants), numFemaleAnts(femaleants), numDoodlebugs(doodlebugs), numQueens(queens) {
        grid.resize(rows, vector<Organism*>(cols, nullptr));
    }
    ~Simulation();

    void initialize(int numMaleAnts, int numFemaleAnts, int numQueens, int numDoodlebugs);
    void simulate();
    void printGrid() const;

    bool isInBounds(int r, int c) const;
    bool isCellEmpty(int r, int c) const;
    bool isAnt(int r, int c) const;

    void moveOrganism(int oldRow, int oldCol, int newRow, int newCol);
    void addOrganism(Organism* org);
    void removeOrganism(int r, int c);
    bool checkExtinction() const {
        return (numMaleAnts + numQueens + numFemaleAnts) == 0 || numDoodlebugs == 0;
    }
};