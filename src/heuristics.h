#ifndef HEURISTICS_H_
#define HEURISTICS_H_

#include "node.h"
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

// Goal state for the 8-puzzle
const intVec goalState = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

// Calculates the Euclidean Distance heuristic
// Calculate distance of each tile from goal
int euclideanDistanceHeuristic(intVec puzzle) {
  int distance = 0;
  // Iterate through each tile
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      // Skip blank
      if (puzzle[row][col] == 0) {
        continue;
      }
      // Find the position of the current tile in the goal state
      if (puzzle[row][col] != goalState[row][col]) {
        int targetRow = 0;
        int targetCol = 0;

        for (int goalRow = 0; goalRow < 3; goalRow++) {
          for (int goalCol = 0; goalCol < 3; goalCol++) {
            if (goalState[goalRow][goalCol] == puzzle[row][col]) {
              targetRow = goalRow;
              targetCol = goalCol;
            }
          }
        }
        // Calculate the Euclidean distance between the current position and the goal position
        int rowDifference = row - targetRow;
        int colDifference = col - targetCol;
        distance += sqrt(pow(rowDifference, 2) + pow(colDifference, 2));
      }
    }
  }
  return distance;
}

// Calculates the Misplaced Tile heuristic
// Counts the number of tiles that are not in goal position
int misplacedTileHeuristic(intVec puzzle) {
  int misplacedTiles = 0;
  // Iterate through each tile in the puzzle
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      // Skip blank
      if (puzzle[row][col] == 0) {
        continue;
      }
      // Count the tile if not in goal position
      if (puzzle[row][col] != goalState[row][col]) {
        misplacedTiles++;
      }
    }
  }
  return misplacedTiles;
}

#endif
