#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

void addvertex();



void addvertex() {
  int vertexlabel;
  cout << "Adding vertex" << endl;
  cout << "What number would you like to label your vertex with?" << endl;
  cin >> vertexlabel;
  Node* vertex = new Node(vertexlabel);
  cout << "Vertex has been added" << endl;
}


int main() {
  int response;
    cout << "Enter 1 to add vertex, 2 to add edge, 3 to remove vertex, 4 to remove edge, and 5 to find shortest path" << endl;
  cin >> response;
  while (response != 1000000000) {
  if (response == 1) {
    //   cout << "Add vertex" << endl;
    addvertex();
    cout << "Enter 1 to add vertex, 2 to add edge, 3 to remove vertex, 4 to remove edge, and 5 to find shortest path" << endl;
  cin >> response;
  }
  if (response == 2) {
    cout << "Add edge" << endl;
    cout << "Enter 1 to add vertex, 2 to add edge, 3 to remove vertex, 4 to remove edge, and 5 to find shortest path" << endl;
  cin >> response;
  }
  if (response == 3) {
    cout << "Remove vertex" << endl;
    cout << "Enter 1 to add vertex, 2 to add edge, 3 to remove vertex, 4 to remove edge, and 5 to find shortest path" << endl;
  cin >> response;
  }
  if (response == 4) {
    cout << "Remove edge" << endl;
cout << "Enter 1 to add vertex, 2 to add edge, 3 to remove vertex, 4 to remove edge, and 5 to find shortest path" << endl;
  cin >> response;
  }
  if (response == 5) {
    cout << "Find shortest path" << endl;
    cout << "Enter 1 to add vertex, 2 to add edge, 3 to remove vertex, 4 to remove edge, and 5 to find shortest path" << endl;
  cin >> response;
  }
  }
  return 0;
}
