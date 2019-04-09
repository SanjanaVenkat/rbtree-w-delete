//Sanjana Venkat
//3.31.19
//Red Black Tree
#include <iostream>
#include <cstring>
#include "node.h"
#include <fstream>

using namespace std;  
//functions
void print(TreeNode* root, int level);
TreeNode* remove(TreeNode* realroot, TreeNode* root, TreeNode* parent, int num, int lr);
bool printlevel(TreeNode* root, int level, int startlevel);
void redblackupdate(TreeNode* root, TreeNode* parent);
TreeNode* rotate_right(TreeNode* root, TreeNode* current);
TreeNode* rotate_left(TreeNode* root, TreeNode* current);
void insertrecursive(TreeNode* root, TreeNode* n);
TreeNode* insertrepairtree(TreeNode* root, TreeNode* current);
TreeNode* case1(TreeNode* current, TreeNode* root);
TreeNode* case2(TreeNode* current, TreeNode* root);
void case3(TreeNode* current, TreeNode* uncle, TreeNode* root);
TreeNode* case4(TreeNode* current, TreeNode* root);
TreeNode* insert(TreeNode* root, int current);
TreeNode* case4_2(TreeNode* current, TreeNode* root);
void searchnode(TreeNode* root, int search);

//add to tree
TreeNode* insert(TreeNode* root, int current) {
  TreeNode* realroot = root;
  char black[2] = "B";
  TreeNode* n = new TreeNode(current, black);
  insertrecursive(root, n);

  //  cout << "Test1" << endl;
  // print(root, 0);
  root = insertrepairtree(root, n);
  // cout << root->getNumber() << endl;
  //print(root, 0);
  //  cout << root->getNumber() << endl;
  //print the tree
  cout << "Tree: " << endl;
  print(root, 0);
  //cout << "Root " << root->getNumber() << endl;
  return root;
  }

//repairs the tree to follow case rules
TreeNode* insertrepairtree(TreeNode* root, TreeNode* current) {
  /*
  if (current->getParent(root, current->getNumber(), 0) == NULL) {
    root = case1(current, root);
    return root;
  }
  else if (strcmp(current->getParent(root, current->getNumber(),0)->getRedBlack(), "B") == 0) {
    case2(current, root);
  }
  */
  //find uncle
  TreeNode* parent = current->getParent(root, current->getNumber(), 0);
  TreeNode* grandparent = NULL;
   if (parent != NULL) {
    grandparent = parent->getParent(root, parent->getNumber(), 0);
   }
  TreeNode* uncle = NULL;
  if (parent != NULL) {
  if (grandparent != NULL) {
    if (grandparent->getLeft() == current->getParent(root, current->getNumber(), 0)) {
	if (grandparent->getRight() != NULL) {

	  uncle = grandparent->getRight();
	}
	else {
	  uncle = NULL;
	}
      }
    else if (grandparent->getRight() == current->getParent(root, current->getNumber(), 0)) {
	if (grandparent->getLeft() != NULL) {
	  uncle = grandparent->getLeft();
	}
	else {
	  uncle = NULL;
	}
	  }
	 }
  }
  //  cout << "STATS" << endl;
  //if (uncle != NULL) {
  //cout << "Uncle " << uncle->getNumber() << endl;
  //}
  //  print(root, 0);
  
  if (current->getParent(root, current->getNumber(), 0) == NULL) {
    //cout << "Test4" << endl;
    //cout << "Case 1" << endl;
    root = case1(current, root);
    return root;
    //    cout << "Test8" << endl;
  }
  //cout << "Test9" << endl;
  else if (strcmp(current->getParent(root, current->getNumber(), 0)->getRedBlack(), "B") == 0) {
    //cout << "Case 2" << endl;
    case2(current, root);
  }
  
    else if (uncle != NULL && strcmp(uncle->getRedBlack(), "R") == 0) {
      //cout << "Case 3" << endl;
      case3(current, uncle, root);
    }
  
    else {
      //  cout << "Case 4" << endl;
      root = case4(current, root);
      return root;
    }
   
  }
//case 4 part 1
TreeNode* case4(TreeNode* current, TreeNode* root) {
  //cout << "Case 4" << endl;
  TreeNode* p = current->getParent(root, current->getNumber(), 0);
  TreeNode* g = NULL;
  if (p != NULL) {
    g = p->getParent(root, p->getNumber(), 0);
  }
  if (current == p->getRight() && p == g->getLeft()) {
   rotate_left(root, p);
    //    cout << "Rotated left" << endl;
    current = current->getLeft();
  }
  else if (current == p->getLeft() && p == g->getRight()) {
   rotate_right(root, p);
    //cout << "Rotated right" << endl;
    current = current->getRight();
  }
TreeNode* hold = case4_2(current, root);
//cout << hold->getNumber() << endl;
return hold;
}

//case 4 part 2
TreeNode*  case4_2(TreeNode* current, TreeNode* root) {
  //cout << "Case 4 part 2" << endl;
  char black[2] = "B";
  char red[2] = "R";
  TreeNode* p;
  if (current != NULL) {
  p = current->getParent(root, current->getNumber(), 0);
  }
  TreeNode* g;
  if (p != NULL) {
    g = p->getParent(root, p->getNumber(), 0);
  }
  //cout << "Test" << endl;
  if (current == p->getLeft()) {
    //cout << "RR" << endl;
  root = rotate_right(root, g);
   //  cout << "Rotated right" << endl;
  }
  else {
    //cout << "RL" << endl;
   root = rotate_left(root, g);
    //cout << "Rotated Left" << endl;
  }
  p->setRedBlack(black);
  g->setRedBlack(red);
  return root;
}

//case 1, root
TreeNode* case1(TreeNode* current, TreeNode* root) {
  //cout << "Case 1" << endl;
  if(current->getParent(root, current->getNumber(), 0) == NULL) {
    //cout << "Test5" << endl;
    char black[2] = "B";
    current->setRedBlack(black);
    //cout << "Test6" << endl;
    return current;
    }
  }

//case 2, parent is black, child inserted red
TreeNode* case2(TreeNode* current, TreeNode* root) {
  //cout << "Case 2" << endl;
  TreeNode* p;
  if (current != NULL) {
   p = current->getParent(root, current->getNumber(), 0);
  }
  char red[2] = "R";
  if (strcmp(p->getRedBlack(), "B") == 0) {
    if (p->getNumber() > current->getNumber()) {
      p->setLeft(current);
      current->setRedBlack(red);
    }
    else if (p->getNumber() < current->getNumber()) {
      p->setRight(current);
      current->setRedBlack(red);
    }
  }
  return root;
}

//case three, colors need to be adjusted after insert
void case3(TreeNode* current, TreeNode* uncle, TreeNode* root) {
  //cout << "Case 3" << endl;
  char black[2] = "B";
  char red[2] = "R";
  current->getParent(root, current->getNumber(), 0)->setRedBlack(black);
  uncle->setRedBlack(black);
  TreeNode* parent = current->getParent(root, current->getNumber(), 0);
  TreeNode* grandparent = current->getParent(root, parent->getNumber(), 0);
  grandparent->setRedBlack(red);
  insertrepairtree(root, grandparent);
}

//recursive where to insert 
void insertrecursive(TreeNode* root, TreeNode* n) {

  char black[2] = "B";
  char red[2] = "R";
  TreeNode* newnode = n;
  if (root != NULL && newnode->getNumber() < root->getNumber()) {

    if (root->getLeft() != NULL) {
      TreeNode* left = root->getLeft();
      if (left->getLeft() == NULL || left->getRight() == NULL || left->getRight() != NULL) {
  
      insertrecursive(left, newnode);
      //    cout << "Going left" << endl;
    }
    }
  else {

    root->setLeft(newnode);
    //cout << "Left" << endl;
    //return;
  }
    
    //cout << "D" << endl;
  }
  else if (root != NULL && newnode->getNumber() > root->getNumber()) {
    //cout << "Test" << endl;
      if (root->getRight() != NULL) {
	TreeNode* right = root->getRight();
	if (right->getRight() == NULL || right->getLeft() == NULL || right->getLeft() != NULL) {
       
	insertrecursive(right, newnode);
	//	cout << "Going right" << endl;
	}
      }
      else {
	root->setRight(newnode);
	//	cout << "Test2" << endl;
	//cout << "Right" << endl;
	//	return;
      }
      
  }
  TreeNode* p = newnode->getParent(root, newnode->getNumber(), 0);
  if (p != NULL) {
    p = root;
  }
  /*
  if (newnode != NULL && newnode != root) {
    cout << "Test" << endl;
    TreeNode* newnodep = newnode->getParent(root, newnode->getNumber(), 0);
  newnodep = root;
  TreeNode* nll = newnode->getLeft()->getLeft();
  nll= NULL;
  TreeNode* nlr = newnode->getLeft()->getRight();
  nlr = NULL;
  TreeNode* nrl = newnode->getRight()->getLeft();
  nrl = NULL;
  TreeNode* nrr = newnode->getRight()->getRight();
  nrr = NULL;
  */
newnode->setRedBlack(red);
   
  
}

//print levels
void print (TreeNode* root, int level) {
  int setlevel = 0;
  bool done = true;
  while (done == true) {
    done = printlevel(root, setlevel, 0);
    cout << endl;
    setlevel = setlevel + 1;
  }
}


//prints numbers in each level, recursive
bool printlevel(TreeNode* root, int level, int startlevel) {
  bool check = false;
  if (root != NULL) {
  if (startlevel == level) {
    cout << root->getNumber() << root->getRedBlack() << " ";
    check = true;
  }
  else {
    if (root->getLeft() != NULL) {
      check = printlevel(root->getLeft(), level, startlevel+1);
      //    cout << " ";
    }
    
    if (root->getRight() != NULL) {
      //cout << " ";
      bool checkhold = printlevel(root->getRight(), level, startlevel+1);
      if (check == true) {
	return check;
      }
      else {
	return checkhold;
      }
    }

  }
  return check;
  }

}

//remove
TreeNode* remove (TreeNode* realroot, TreeNode* root, TreeNode* parent, int num, int lr) {
  
}



//rotate right to balance, used in case 4
TreeNode* rotate_right(TreeNode* root, TreeNode* current)  {
  //cout << "Rotate right" << endl;
  // print(root, 0);
  current = current->getLeft();
  TreeNode* newcurrent = current->getLeft();
  // cout << current->getNumber() << endl;
  //cout << newcurrent->getNumber() << endl;
  TreeNode* parent = current->getParent(root, current->getNumber(), 0);
  if (parent->getLeft() != NULL) {
    parent->setLeft(newcurrent->getParent(root, newcurrent->getNumber(), 0)->getRight());
  }
  else {
  parent->setLeft(NULL);
  }
  TreeNode* newtop = current;
  newtop->setLeft(newcurrent);
  newtop->setRight(parent);
  TreeNode* grandparent;
  if (parent != NULL && parent != root) {
  grandparent = parent->getParent(root, parent->getNumber(), 0);
  }
  else {
  grandparent = NULL;
  }
  if (parent == NULL || parent == root && grandparent == NULL) {
    return newtop;
  }
  else {
    if (grandparent->getNumber() > newtop->getNumber()) {
      grandparent->setLeft(newtop);
    }
    else if (grandparent->getNumber() < newtop->getNumber()) {
      grandparent->setRight(newtop);
    }
    return root;
    }

  
}


//rotate left to balance, used in case 4
TreeNode* rotate_left(TreeNode* root, TreeNode* current) {
  //cout << "Rotate left" << endl;
  current = current->getRight();
  TreeNode* newcurrent = current->getRight();
  //cout << newcurrent->getNumber() << endl;
  TreeNode* parent = current->getParent(root, current->getNumber(), 0);
  if (parent->getRight() != NULL) {
    parent->setRight(newcurrent->getParent(root, newcurrent->getNumber(), 0)->getLeft());
  }
  else {
    parent->setRight(NULL);
  }
  TreeNode* newtop = current;
  newtop->setRight(newcurrent);
  newtop->setLeft(parent);
  TreeNode* grandparent = NULL;
  if (parent != NULL && parent != root) {
    grandparent = parent->getParent(root, parent->getNumber(), 0);
  }
  else {
    grandparent = NULL;
  }
  if (parent == NULL || parent == root && grandparent == NULL) {
    return newtop;
  }
  else {
    if (grandparent->getNumber() > newtop->getNumber()) {
      grandparent->setLeft(newtop);
    }
    else if (grandparent->getNumber() < newtop->getNumber()) {
      grandparent->setRight(newtop);
    }
    return root;
  }


}

void searchnode(TreeNode* root, int search) {
  if (root->getNumber() == search) {
    cout << "Number is part of tree" << endl;
    return;
  }
  else {
    while (root->getNumber() != search) {
      if (root->getLeft() != NULL) {
	if (root->getLeft()->getNumber() == search) {
	  cout << "Number is part of tree" << endl;
	  return;
	}
      }
      if (root->getRight() != NULL) {
	if (root->getRight()->getNumber() == search) {
	  cout << "Number is part of tree" << endl;
	  return;
	}

      }
      if (root->getLeft() != NULL && root->getNumber() > search) {
	root = root->getLeft();
      }
      else if (root->getRight() != NULL && root->getNumber() < search) {
	root = root->getRight();
      }
      else {
	cout << "Number is not part of tree" << endl;
	return;
      }
    }
    //    else {
      cout << "Number is not part of tree" << endl;
      return;
      //}
  }
}







//for testing only
void redblackupdate(TreeNode* root, TreeNode* parent) {
  char black[2] = "B";
  char red[2] = "R";
  if (root != NULL) {
  if (parent == NULL) {
    root->setRedBlack(black);
    if (root->getLeft() != NULL) {
      redblackupdate(root->getLeft(), root);
    }
    if (root->getRight() != NULL) {
      redblackupdate(root->getRight(), root);
    }
  }
  else {
    if (strcmp(parent->getRedBlack(), black) == 0) {
    root->setRedBlack(red);
    if (root->getLeft() != NULL) {
      redblackupdate(root->getLeft(), root);
    }
    if (root->getRight() != NULL) {
      redblackupdate(root->getRight(), root);
    }
    }
    else {
      root ->setRedBlack(black);
      if (root->getLeft() != NULL) {
	redblackupdate(root->getLeft(), root);
      }
      if (root->getRight() != NULL) {
	redblackupdate(root->getRight(), root);
      }
    }
  }
  }

}

//main
int main() {
  bool running = true;
  int response = 0;
  cout << "Enter 1 for add, 2 to find parent of a node, 3 to search for a node" << endl;
  cin >> response;
  TreeNode* root = NULL;
  while (running != false) {
    //add
  if (response == 1) {
    int responset;
    cout << "Enter 1 to enter from command line, or 2 to have numbers read from file" << endl;
    cin >> responset;
    //command line
    if (responset == 1) {
    cout << "How many numbers do you want to enter?" << endl;
  int numofnum = 0;
  cin >> numofnum;
  cout << "Enter your numbers, seperate with spaces" << endl;
  int counter = 0;
  int num = 0;
  while (counter != numofnum) {
    cin >> num;
    if (root == NULL) {
root = insert(root, num);
    }
  else {
root =  insert(root, num);
  }
  counter++;
  }
  //  redblackupdate(root, NULL);
    }
    //file
  else if (responset == 2) {
    ifstream inData;
     cout << "Enter filename" << endl;
    char filename[1000];
    cin >> filename;
    inData.open(filename);
    int datanum;
    int num;
    while (inData >> num) {
      datanum = num;
      if (root == NULL) {
       	root = insert(root, datanum);
      }
      else {
root =	insert(root, datanum);
      }
         inData.ignore();
    }

  }
  
   cout << "Enter 1 for add, 2 to find parent of a node, 3 to search for a node" << endl;
  cin >> response;
  }
  //print
  /*
  if (response == 2) {
    cout << "Tree:" << endl;
     print(root, 0);
 cout << "Enter 1 for add, 2 for print, 3 for delete, and 4 to find parent" << endl;
  cin >> response;
  }
  //delete
  if (response == 3) {
    int numofnum = 0;
    int num = 0;
  int delcounter = 0;
  cout << "Enter how many numbers you want to delete" << endl;
  cin >> numofnum;
  cout << "Enter your numbers, seperate with spaces" << endl;
  while (delcounter != numofnum) {
    cin >> num;
    root = remove(root, root, NULL, num, 0);
       delcounter = delcounter + 1;
      }
  cout << "Done deleting" << endl;
   cout << "Enter 1 for add, 2 for print, 3 for delete, and 4 to find parent" << endl;
  cin >> response;

  }
  */
  //prints parent of any node
  if (response == 2) {
    int current = 0;
    cout << "Enter node to find parent of" << endl;
    cin >> current;
    TreeNode* holder = root->getParent(root, current, 4);
    if (holder != NULL) {
    cout << holder->getNumber() << endl;
    }
    else {
      cout << "Parent does not exist" << endl;
    }
   cout << "Enter 1 for add, 2 to find parent of a node, 3 to search for a node" << endl;
   cin >> response;
  }
  

  if (response == 3) {
    //    int search;
    cout << "What node do you want to search for?" << endl;
    int search;
    cin >> search;
    searchnode(root, search);
    cout << "Enter 1 for add, 2 to find the parent of a node, 3 to search for a node" << endl;
    cin >>response;
  }
  }
}
