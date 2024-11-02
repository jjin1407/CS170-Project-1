#include <iostream>
#include <queue>
#include <stack>
#include <unistd.h>
#include <vector>

#include "functions.h"
#include "heuristics.h"
#include "node.h"
#include "operators.h"

using namespace std;

// Stores nodes that have been traversed
vector<NodeStruct> traversedNodes;

// Priority queue for nodes
priority_queue<NodeStruct, vector<NodeStruct>, NodeComparison> findQueue;

void solutionFinder(intVec, string);

void solutionFinder(intVec puzzle, string heuristic) {

  int expandedNodes;
  long unsigned int maxNodesInQueue = 0;

  NodeStruct currentNode(puzzle);
  expandedNodes = 0;

  traversedNodes.push_back(currentNode);
  findQueue.push(currentNode);

  // Which heuristic is being used
  if (heuristic == "Euclidean") {
    cout << "Using Euclidean Distance Heuristic \n" << endl;
  }

  if (heuristic == "Misplaced") {
    cout << "Using Misplaced Tile Heuristic \n" << endl;
  }

  // Continue while the queue is not empty
  while (findQueue.size() > 0) {

    NodeStruct *node;

    node = new NodeStruct(findQueue.top());

    // Goal state?
    if (goalState == findQueue.top().puzzle) {
      displayPuzzleNodes(findQueue.top(), maxNodesInQueue, expandedNodes);
      break;
    } else {
      // Add to traversed nodes and max queue
      traversedNodes.push_back(findQueue.top());
      if (maxNodesInQueue < findQueue.size()) {
        maxNodesInQueue = findQueue.size();
      }

      findQueue.pop();

      // Expand nodes
      expandedNodes++;
      NodeStruct *nodeUp =
          new NodeStruct(moveUp(node->puzzle), (node->uniformCost + 1));
      NodeStruct *nodeDown =
          new NodeStruct(moveDown(node->puzzle), (node->uniformCost + 1));
      NodeStruct *nodeLeft =
          new NodeStruct(moveLeft(node->puzzle), (node->uniformCost + 1));
      NodeStruct *nodeRight =
          new NodeStruct(moveRight(node->puzzle), (node->uniformCost + 1));

      // Calculate heuristic cost
      if ("Euclidean" == heuristic) {
        nodeRight->heuristicCost =
            euclideanDistanceHeuristic(nodeRight->puzzle);
        nodeUp->heuristicCost = euclideanDistanceHeuristic(nodeUp->puzzle);
        nodeLeft->heuristicCost = euclideanDistanceHeuristic(nodeLeft->puzzle);
        nodeDown->heuristicCost = euclideanDistanceHeuristic(nodeDown->puzzle);
      }
      if ("Misplaced" == heuristic) {
        nodeUp->heuristicCost = misplacedTileHeuristic(nodeUp->puzzle);
        nodeDown->heuristicCost = misplacedTileHeuristic(nodeDown->puzzle);
        nodeRight->heuristicCost = misplacedTileHeuristic(nodeRight->puzzle);
        nodeLeft->heuristicCost = misplacedTileHeuristic(nodeLeft->puzzle);
      }

      // Calculate total cost for each node
      nodeLeft->totalCost = nodeLeft->heuristicCost + nodeLeft->uniformCost;
      nodeRight->totalCost = nodeRight->heuristicCost + nodeRight->uniformCost;
      nodeUp->totalCost = nodeUp->heuristicCost + nodeUp->uniformCost;
      nodeDown->totalCost = nodeDown->heuristicCost + nodeDown->uniformCost;

      // Add nodes to the queue if have not traversed
      if (!hasPreviousNodes(nodeRight->puzzle, traversedNodes)) {
        node->child0 = nodeRight;
        nodeRight->parent = node;
        findQueue.push(*nodeRight);
      }

      if (!hasPreviousNodes(nodeLeft->puzzle, traversedNodes)) {
        node->child1 = nodeLeft;
        nodeLeft->parent = node;
        findQueue.push(*nodeLeft);
      }

      if (!hasPreviousNodes(nodeUp->puzzle, traversedNodes)) {
        node->child2 = nodeUp;
        nodeUp->parent = node;
        findQueue.push(*nodeUp);
      }

      if (!hasPreviousNodes(nodeDown->puzzle, traversedNodes)) {
        node->child3 = nodeDown;
        nodeDown->parent = node;
        findQueue.push(*nodeDown);
      }
    }
  }
}

int main() {
  // Default puzzle values
  int a = 1;
  int b = 2;
  int c = 0;
  int d = 4;
  int e = 5;
  int f = 3;
  int g = 7;
  int h = 8;
  int i = 6;

  cout << "1 to use default puzzle or 2 to enter puzzle" << endl;
  int opt = 0; // Holder for puzzle option

  cin >> opt; // Store user input
  cout << "\n";

  vector<int> user;
  if (opt == 1) {
    // If choose default puzzle configuration
    user.push_back(a);
    user.push_back(b);
    user.push_back(c);
    user.push_back(d);
    user.push_back(e);
    user.push_back(f);
    user.push_back(g);
    user.push_back(h);
    user.push_back(i);
  }
  if (opt == 2) {
    // Custom puzzle configuration
    cout << "Input your puzzle: use zero to represent the empty space " << endl;
    cout << "First row, use a space in between each number " << endl;
    cin >> a >> b >> c;
    cout << "Second row, use a space in between each number " << endl;
    cin >> d >> e >> f;
    cout << "Third row, use a space in between each number " << endl;
    cin >> g >> h >> i;

    user.push_back(a);
    user.push_back(b);
    user.push_back(c);
    user.push_back(d);
    user.push_back(e);
    user.push_back(f);
    user.push_back(g);
    user.push_back(h);
    user.push_back(i);
  }

  intVec puzzleq(3, vector<int>(3)); // 3x3 puzzle configuration
  int count = 0;

  // Input user input values
  for (int j = 0; j < 3; j++) {
    for (int k = 0; k < 3; k++) {
      puzzleq[j][k] = user[count];
      cout << puzzleq[j][k];
      count++;
    }
    cout << endl;
  }

  // Reset option variable
  opt = 0;

  // Which algorithm to use?
  cout << "What algorithm?" << endl;
  cout << "1: Uniform Cost Search " << endl;
  cout << "2: A* with the Misplaced Tile Heuristic " << endl;
  cout << "3: A* with the Euclidean Distance Heuristic" << endl;
  cout << endl;

  cin >> opt; // User choice for algorithm

  string choice = " ";

  if (opt == 1) {
    choice = "Uniform";
  } else if (opt == 2) {
    choice = "Misplaced";
  } else if (opt == 3) {
    choice = "Euclidean";
  } else {
    choice = "Uniform";
  }

  // Call solution finder with the puzzle and algorithm
  solutionFinder(puzzleq, choice);

  cout << endl;

  return 0;
}
