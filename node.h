#include <iostream>
#include <cstring>

using namespace std;


class Node {
 public:
  Node(int n);
  ~Node();
  void setAdjacent(Node* newadjacent);
  int getNumber();
  void setNumber(int n);
  Node* getAdjacent();
 private:
  Node* adjacent;
  int number;
};
