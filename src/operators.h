#ifndef OPERATORS_H_
#define OPERATORS_H_

#include <iostream>
#include <vector>
#include "node.h"

using namespace std;

// 2D vector representing the puzzle state
typedef vector<vector<int>> intVec;

// Swapping positions of two elements in the puzzle
intVec swapPositions(int, int, int, int, intVec);

// Move the empty tile down
intVec moveDown(intVec puzzle) {
    int row = 0;
    int col = 0;

    // Empty tile should not be in the first row
    for (int j = 0; j < 3; j++) {
        if (puzzle[0][j] == 0) { 
            return puzzle; 
        }
    }

    // Locate empty tile starting from second row
    for (int j = 1; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            if (puzzle[j][k] == 0) {
                row = j;
                col = k;
            }
        }
    }
    // Swap the empty tile with the element above it
    return swapPositions(row, col, (row - 1), col, puzzle);
}

// Move the empty tile up
intVec moveUp(intVec puzzle) {
    int row = 0;
    int col = 0;

    // Empty tile should not be in the last row
    for (int j = 0; j < 3; j++) {
        if (puzzle[2][j] == 0) { 
            return puzzle; 
        }
    }

    // Locate the empty tile 
    for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 3; k++) {
            if (puzzle[j][k] == 0) {
                row = j;
                col = k;
            }
        }
    }
    // Swap the empty tile with the element below it
    return swapPositions(row, col, (row + 1), col, puzzle);
}

// Move the empty tile to the right
intVec moveRight(intVec puzzle) {
    int row = 0;
    int col = 0;

    // The empty tile should not be in the leftmost column
    for (int j = 0; j < 3; j++) {
        if (puzzle[j][0] == 0) { 
            return puzzle; 
        }
    }

    // Locate the empty tile
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            if (puzzle[j][k] == 0) {
                row = j;
                col = k;
            }
        }
    }
    // Swap the empty tile with the element to its left
    return swapPositions(row, col, row, (col - 1), puzzle);
}

// Move the empty tile to the left
intVec moveLeft(intVec puzzle) {
    int row = 0;
    int col = 0;

    // The empty tile should not be in the rightmost column
    for (int j = 0; j < 3; j++) {
        if (puzzle[j][2] == 0) { 
            return puzzle; 
        }
    }

    // Locate the empty tile 
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 2; k++) { 
            if (puzzle[j][k] == 0) {
                row = j;
                col = k;
            }
        }
    }
    // Swap the empty tile with the element to its right
    return swapPositions(row, col, row, (col + 1), puzzle);
}

// Swap the positions of two elements in the puzzle
intVec swapPositions(int x, int y, int i, int j, intVec puzzle) {
    int temp = puzzle[i][j]; 
    puzzle[x][y] = temp;     
    puzzle[i][j] = 0;        
    return puzzle;
}

#endif