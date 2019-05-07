#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

Node::Node(int n) {
  adjacent = NULL;
  number = n;
}

Node::~Node() {
  adjacent = NULL;
}

void Node::setAdjacent(Node* newadjacent) {
  adjacent = newadjacent;
}

Node* Node::getAdjacent() {
  return adjacent;
}

void Node::setNumber(int n) {
  number = n;
}

int Node::getNumber() {
  return number;
}
