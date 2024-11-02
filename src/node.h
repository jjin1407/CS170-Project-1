#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>

using namespace std;

// Define a type alias for a 2D vector of integers representing the puzzle
typedef vector<vector<int>> intVec;

struct NodeStruct {
  // Costs used in evaluating the node
  int uniformCost = 0;  
  int heuristicCost = 0; 
  int totalCost = 0;     

  // Pointers to child nodes 
  NodeStruct *child0 = NULL;
  NodeStruct *child1 = NULL;
  NodeStruct *child2 = NULL;
  NodeStruct *child3 = NULL;

  // Pointer to parent node
  NodeStruct *parent = NULL;

  // Stores current puzzle config
  intVec puzzle;

  // Initialize the node with a puzzle state and set costs to 0
  NodeStruct(intVec vec) {
    uniformCost = 0;
    heuristicCost = 0;
    puzzle = vec;
  }

  // Initialize the node with a puzzle state and a given uniform cost
  NodeStruct(intVec vec, int uniform_cost) {
    puzzle = vec;
    uniformCost = uniform_cost;
    heuristicCost = 0;
  }

  // Copy constructor to create a new node from an existing one
  NodeStruct(const NodeStruct &vec) {
    puzzle = vec.puzzle;
    heuristicCost = vec.heuristicCost;
    uniformCost = vec.uniformCost;
    totalCost = vec.totalCost;
    child0 = vec.child0;
    child1 = vec.child1;
    child2 = vec.child2;
    child3 = vec.child3;
    parent = vec.parent;
  }

  // Operator overload to copy values from another node
  void operator=(const NodeStruct &vec) {
    puzzle = vec.puzzle;
    heuristicCost = vec.heuristicCost;
    uniformCost = vec.uniformCost;
    totalCost = vec.totalCost;
    child0 = vec.child0;
    child1 = vec.child1;
    child2 = vec.child2;
    child3 = vec.child3;
    parent = vec.parent;
  }

  // Display the current puzzle state
  void displayPuzzle() {
    for (int row = 0; row < 3; row++) {
      for (int col = 0; col < 3; col++) {
        cout << puzzle[row][col];
      }
      cout << endl;
    }
  }
};

// Prioritizing nodes in a priority queue
// The node with the lower total cost has higher priority
struct NodeComparison {
  bool operator()(const NodeStruct &leftNode, const NodeStruct &rightNode) {
    return leftNode.totalCost > rightNode.totalCost;
  }
};

#endif
