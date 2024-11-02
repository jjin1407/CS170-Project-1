#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <queue>
#include <stack>
#include <unistd.h>
#include <vector>

#include "node.h"
using namespace std;

// Check if a puzzle state has been previously visited
bool hasPreviousNodes(intVec puzzle, vector<NodeStruct> traversedNodes) {
  for (long unsigned int j = 0; j < traversedNodes.size(); j++) {
    if (traversedNodes[j].puzzle == puzzle) {
      return true; // True if state was already visited
    }
  }
  return false; // False if state is new
}

// Display nodes from initial state to current state
void displayPuzzleNodes(NodeStruct node, int expandedNodes, int maxNodesInQueue) {
  stack<NodeStruct> nodeStack;   
  NodeStruct currentNode = node; 

  // Push nodes onto the stack from current to initial state
  nodeStack.push(currentNode);
  while (currentNode.parent != NULL) {
    currentNode = *currentNode.parent;
    nodeStack.push(currentNode);
  }

  // Display the initial state
  cout << "Expanding state" << endl;
  nodeStack.top().displayPuzzle();
  cout << "\n";
  nodeStack.pop();

  // Print the sequence of moves from the initial state to the goal
  while (nodeStack.size() > 1) {
    cout << "The best state to expand with g(n) = "
         << nodeStack.top().uniformCost
         << " and h(n) = " << nodeStack.top().heuristicCost << " is...\n";
    nodeStack.top().displayPuzzle();
    cout << "Expanding node\n" << endl;
    nodeStack.pop();
  }

  // Print the final state, max number of nodes in queue, and expanded nodes
  cout << "123 \n"
       << "456 \n"
       << "780 \n"
       << "Goal reached \n"
       << endl;
  cout << "Maximum number of nodes in the queue at any one time is "
       << maxNodesInQueue << ". \n";
  cout << "The search algorithm expanded a total of " << expandedNodes
       << " nodes \n";
}

#endif
