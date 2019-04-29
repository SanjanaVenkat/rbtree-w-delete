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
TreeNode* remove(TreeNode* root, TreeNode* todelete);
void printlevel(TreeNode* root, int level);
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
TreeNode* searchnode(TreeNode* root, int search);
TreeNode* delete1(TreeNode* root, TreeNode* todelete);
void delete2(TreeNode* root, TreeNode* todelete);
void delete3(TreeNode* root, TreeNode* todelete);
void delete4(TreeNode* root, TreeNode* todelete);
void delete5(TreeNode* root, TreeNode* todelete);
void delete6(TreeNode* root, TreeNode* todelete);
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
  // cout << "Case 4" << endl;
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
    printlevel(root, 0);
}


//prints numbers in each level, recursive
void printlevel(TreeNode* root, int level) {
  if (root != NULL) {
    if (root->getRight() != NULL) {
      printlevel(root->getRight(), level + 1);
    }
    for (int i = level; i > 0; i--) {
      cout << "   ";
    }
    cout << root->getNumber() << root->getRedBlack() << endl;
    if (root->getLeft() != NULL) {
      printlevel(root->getLeft(), level + 1);
    }
    
  }

}

TreeNode* delete1(TreeNode* root, TreeNode* todelete) {
  cout << "Delete case 1" << endl;
  if (todelete != NULL) {
  if (todelete->getParent(root, todelete->getNumber(), 0) != NULL) {
    //cout << "Tree: " << endl;
    //print(root, 0);
    delete2(root, todelete);
    }
  else {
    root = todelete;
  }
  }
}

void delete2(TreeNode* root, TreeNode* todelete) {
  cout << "Delete case 2" << endl;
  char red[2] = "R";
  char black[2] = "B";
  TreeNode* parent = todelete->getParent(root, todelete->getNumber(), 0);
  TreeNode* sibling;
  if (parent->getLeft() == todelete) {
    sibling = parent->getRight();
  }
  else if (parent->getRight() == todelete) {
    sibling = parent->getLeft();
  }
  if (sibling != NULL && strcmp(sibling->getRedBlack(), red) == 0) {
    parent->setRedBlack(red);
    sibling->setRedBlack(black);
  }
  if (todelete == parent->getLeft()) {
    rotate_left(root, parent);
  }
  else {
    rotate_right(root, parent);
  }
  //  cout << "Tree: " << endl;
  //print (root, 0);
  delete3(root, todelete);
}

void delete3(TreeNode* root, TreeNode* todelete) {
  cout << "Delete case 3" << endl;
  char red[2] = "R";
  char black[2] = "B";
  TreeNode* parent = todelete->getParent(root, todelete->getNumber(), 0);
  TreeNode* sibling;
  if (parent != NULL) {
  if (parent->getLeft() == todelete) {
    sibling = parent->getRight();
  }
  else if (parent->getRight() == todelete) {
    sibling = parent->getLeft();
  }
  }
  if (parent != NULL && sibling != NULL) {
    if ((strcmp(parent->getRedBlack(), black) == 0 && strcmp(sibling->getRedBlack(), black) == 0)) {
	if (sibling->getLeft() == NULL && sibling->getRight() == NULL) {
	   sibling->setRedBlack(red);
	  delete1(root, parent);
    	}
	 if (sibling->getLeft() != NULL && strcmp(sibling->getLeft()->getRedBlack(), black) == 0 && sibling->getRight() == NULL) {
      	  sibling->setRedBlack(red);
	  delete1(root, parent);
	}
	 if (sibling->getRight() != NULL && strcmp(sibling->getRight()->getRedBlack(), black) == 0 && sibling->getLeft() == NULL) {
	   sibling->setRedBlack(red);
	  delete1(root, parent);
	}
       if (sibling->getLeft() != NULL && strcmp(sibling->getLeft()->getRedBlack(), black) == 0 && sibling->getRight() != NULL && strcmp(sibling->getRight()->getRedBlack(), black) == 0) {
	 sibling->setRedBlack(red);
	    delete1(root, parent);
	  }
	else {
	  /*	  cout << "Tree: " << endl;
	  print(root, 0);
	  */
   delete4(root, todelete);
 }
      }
  else {
    /*
    cout << "Tree: " << endl;
    print(root, 0);
    */  
 delete4(root, todelete);
 }  
  }
 else {
   /*
   cout << "Tree: " << endl;
   print (root, 0);
   */  
 delete4(root, todelete);
 }
  

}


void delete4(TreeNode* root, TreeNode* todelete) {

  cout << "Delete case 4" << endl;
  char red[2] = "R";
  char black[2] = "B";
  TreeNode* parent = todelete->getParent(root, todelete->getNumber(), 0);
  TreeNode* sibling;
  if (parent != NULL) {
  if (parent->getLeft() == todelete) {
    sibling = parent->getRight();
  }
  else if (parent->getRight() == todelete) {
    sibling = parent->getLeft();
  }
  }
  
  if (parent != NULL && sibling != NULL) {
    if ((strcmp(parent->getRedBlack(), red) == 0 && strcmp(sibling->getRedBlack(), black) == 0)) {
      //both of sibling's children are NULL
      if (sibling->getLeft() == NULL && sibling->getRight() == NULL) {
	  sibling->setRedBlack(red);
	  parent->setRedBlack(black);
      	}
      //sibling's right child is NULL, left is black
	else if (sibling->getLeft() != NULL && strcmp(sibling->getLeft()->getRedBlack(), black) == 0 && sibling->getRight() == NULL) {
	  sibling->setRedBlack(red);
	  parent->setRedBlack(black);
	}
      //sibling's left child is NULL, right is black
	else if (sibling->getRight() != NULL && strcmp(sibling->getRight()->getRedBlack(), black) == 0 && sibling->getLeft() == NULL) {
	  sibling->setRedBlack(red);
	  parent->setRedBlack(black);
	}
      //both of sibling's children are black
	  else if (sibling->getLeft() != NULL && strcmp(sibling->getLeft()->getRedBlack(), black) == 0 && sibling->getRight() != NULL && strcmp(sibling->getRight()->getRedBlack(), black) == 0) {
	    sibling->setRedBlack(red);
	    parent->setRedBlack(black);
	  }
      }
    
    }
	else {
	  delete5(root, todelete);
	}
}
    

void delete5(TreeNode* root, TreeNode* todelete) {
  cout << "Delete case 5" << endl;
  char red[2] = "R";
  char black[2] = "B";
  TreeNode* parent = todelete->getParent(root, todelete->getNumber(), 0);
  TreeNode* sibling;
  if (parent != NULL) {
  if (parent->getLeft() == todelete) {
    sibling = parent->getRight();
    if (sibling != NULL && strcmp(sibling->getRedBlack(), black) == 0) {
	if (sibling->getLeft() != NULL && strcmp(sibling->getLeft()->getRedBlack(),red) == 0) {
	  if (sibling->getRight() == NULL) {
	    rotate_right(root, sibling);
	    sibling->setRedBlack(red);
	    sibling->getParent(root, sibling->getNumber(), 0)->setRedBlack(black);
	  }
	  else if (strcmp(sibling->getRight()->getRedBlack(), black) == 0) {
	    rotate_right(root, sibling);
	    sibling->setRedBlack(red);
	     sibling->getParent(root, sibling->getNumber(), 0)->setRedBlack(black);
	  }
	}
      }
      
  }
  else if (parent->getRight() == todelete) {
    sibling = parent->getLeft();
    if (sibling != NULL && strcmp(sibling->getRedBlack(), black) == 0) {
        if (sibling->getRight() != NULL && strcmp(sibling->getRight()->getRedBlack(),red) == 0) {
          if (sibling->getLeft() == NULL) {
            rotate_left(root, sibling);
            sibling->setRedBlack(red);
            sibling->getParent(root, sibling->getNumber(), 0)->setRedBlack(black);
          }
          else if (strcmp(sibling->getLeft()->getRedBlack(), black) == 0) {
            rotate_left(root, sibling);
            sibling->setRedBlack(red);
             sibling->getParent(root, sibling->getNumber(), 0)->setRedBlack(black);
          }
        }
      }
   
   }
  }

  delete6(root, todelete);

  }


void delete6 (TreeNode* root, TreeNode* todelete) {
  cout << "Delete case 6" << endl;
char red[2] = "R";
  char black[2] = "B";
  TreeNode* parent = todelete->getParent(root, todelete->getNumber(), 0);
  TreeNode* sibling = NULL;;
  if (parent != NULL) {
  if (parent->getLeft() == todelete) {
    sibling = parent->getRight();
    if (sibling != NULL && strcmp (sibling->getRedBlack(), black) == 0) {
      if (sibling->getRight() != NULL && strcmp(sibling->getRight()->getRedBlack(), red) == 0) {
	rotate_left(root, parent);
	char parentcolor[2];
	strcpy(parentcolor, parent->getRedBlack());
	parent->setRedBlack(sibling->getRedBlack());
	sibling->setRedBlack(parentcolor);
	cout << "parent" << parent->getNumber() << endl;
      }
    }
    else if (sibling == NULL) {
      if (todelete->getLeft() != NULL) {
	parent->setLeft(todelete->getLeft());
	parent->setRight(todelete->getRight());
      }
      else if (todelete->getRight() != NULL) {
	parent->setLeft(todelete->getRight());
	parent->setRight(todelete->getLeft());
      }
      else {
	parent->setLeft(NULL);
      }
      parent->setRedBlack(red);
    }
  }
  else if (parent->getRight() == todelete) {
    sibling = parent->getLeft();
 if (sibling != NULL && strcmp (sibling->getRedBlack(), black) == 0) {
      if (sibling->getLeft() != NULL && strcmp(sibling->getLeft()->getRedBlack(), red) == 0) {
        rotate_right(root, parent);
	char parentcolor[2];
        strcpy(parentcolor, parent->getRedBlack());
        parent->setRedBlack(sibling->getRedBlack());
        sibling->setRedBlack(parentcolor);
	  cout << "parent" << parent->getNumber() << endl;

      }
    }
 else if (sibling == NULL) {
   if (todelete->getRight() != NULL) {
     parent->setRight(todelete->getRight());
     parent->setLeft(todelete->getLeft());
   }
   else if (todelete->getLeft() != NULL) {
     parent->setRight(todelete->getLeft());
     parent->setLeft(todelete->getLeft());
   }
   else {
     parent->setRight(NULL);
   }
   parent->setRedBlack(red);
 }
  }
  }
}
	
//remove
TreeNode* remove (TreeNode* root, TreeNode* todelete) {
  char red[2] = "R";
  char black[2] = "B";
  if (todelete != NULL) {
    if (todelete == root) {
      cout << "Need to delete root" << endl;
      TreeNode* newroot = root->getLeft();
      while (newroot->getRight() != NULL) {
	newroot = newroot->getRight();
      }
      cout << newroot->getNumber() << endl;
      TreeNode* newparent = newroot->getParent(root, newroot->getNumber(), 0);

      root->setNumber(newroot->getNumber());
      //delete newroot;
      
      if (newparent->getLeft() == newroot) {
	newparent->setLeft(NULL);
      }
      else if (newparent->getRight() == newroot) {
	newparent->setRight(NULL);
      }
      if ( newroot = root->getLeft()) {
      root->setNumber(newroot->getNumber());
      }
      root->setLeft(newroot->getLeft());
      delete newroot;
      //      return root;
    }			   
    TreeNode* child = NULL;
    TreeNode* todeletedata = todelete;
    if (todelete->getLeft() != NULL) {
    child = todelete->getLeft();
    int todeletenumber = todeletedata->getNumber();
    todelete->setNumber(todeletenumber);
    todelete->setRedBlack(todeletedata->getRedBlack());
    }
    else if (todelete->getRight() != NULL) {
      child = todelete->getRight();
    }
    if (child != NULL) {
      //      cout << "Child" << child->getNumber() << endl;
}
    else if (child == NULL) {
      cout << "Child is NULL" << endl;
    }
    TreeNode* parent = todelete->getParent(root, todelete->getNumber(), 0);
    if (strcmp(todelete->getRedBlack(), red) == 0) {
      if (parent->getLeft() == NULL || parent->getRight() == NULL) {
      cout << "todelete is red" << endl;
      if (parent->getLeft() == todelete) {
	parent->setLeft(child);
	//	cout << "First case" << endl;
	parent->setRight(todelete->getRight());
	//cout << "Todelete left" << todelete->getLeft()->getNumber() << endl;
	//cout << "Todelete right" << todelete->getRight()->getNumber() << endl;
      }
      
      else if (parent->getRight() == todelete) {
	parent->setRight(child);
	//cout << "Second case" << endl;
	//cout << "Todelete left" << todelete->getLeft()->getNumber() << endl;
	//cout << "Todelete right" << todelete->getRight()->getNumber() << endl;
	parent->setLeft(todelete->getRight());
      }
    if (child != NULL) {
      child->setRedBlack(black);
    }
    delete todelete;
    //return root;
      }
      else {
	delete1(root, todelete);
      }
  
    }
    else if (strcmp(todelete->getRedBlack(), black) == 0) {
      cout << "todelete is black" << endl;
      if (parent == NULL) {
	cout << "parent is null" << endl;
	delete1(root, todelete);
      }
      else {
	if (parent->getLeft() == todelete) {
	  parent->setLeft(todelete->getLeft());
	}
	else if (parent->getRight() == todelete) {
	  parent->setRight(todelete->getRight());
	}

      }
    }  
      else if (parent != NULL) {
	cout << "parent is not null" << endl;
	if (parent->getLeft() == todelete) {
	  parent->setLeft(child);
	}
	else if (parent->getRight() == todelete) {
	  parent->setRight(child);
	}
      delete todelete;
      delete1(root, child);
      }
      else if (parent != NULL && strcmp(parent->getRedBlack(), black) == 0) {
	cout << "parent is black" << endl;
	if (parent->getLeft() == todelete) {
	  parent->setLeft(child);
	}
	else if (parent->getRight() == todelete) {
	  parent->setRight(child);
	}
	delete todelete;
	//return root;						  
      }
    }
    }

    

//rotate right to balance, used in case 4
TreeNode* rotate_right(TreeNode* root, TreeNode* current)  {
  //cout << "Rotate right" << endl;
  bool checkroot = false;
  if (current == root) {
    checkroot = true;
  }
  //  cout << current->getNumber() << endl;
  TreeNode* parent = current->getParent(root, current->getNumber(), 0);
  TreeNode* currentchild = current->getLeft();
  TreeNode* child = currentchild->getLeft();
  TreeNode* otherchild = NULL;
  if (currentchild != NULL) {
  otherchild = currentchild->getRight();
  }
  if (currentchild != NULL) {
  currentchild->setRight(current);
  }
  if (current != NULL) {
  current->setLeft(otherchild);
  }
  if (currentchild != NULL) {
  currentchild->setLeft(child);
  }
  // cout << "Current " << current->getNumber() << endl;
  if (parent != NULL && currentchild != NULL && parent->getNumber() > currentchild->getNumber()) {
    parent->setLeft(currentchild);
  }
  else if (parent != NULL && currentchild != NULL && parent->getNumber() < currentchild->getNumber()) {
    parent->setRight(currentchild);
  }
  if(checkroot == true) {
    return currentchild;
  }
  else {
    return root;
  }

}


//rotate left to balance, used in case 4
TreeNode* rotate_left(TreeNode* root, TreeNode* current) {
  // cout << "Rotate left" << endl;
  bool checkroot = false;
  if (current == root) {
    checkroot = true;
  }
  TreeNode* parent = current->getParent(root, current->getNumber(), 0);
  TreeNode* currentchild = current->getRight();
  TreeNode* child = currentchild->getRight();
  TreeNode* otherchild = NULL;
  if (currentchild != NULL) {
  otherchild = currentchild->getLeft();
  }
  if (currentchild != NULL) {
  currentchild->setLeft(current);
  }
  if (current != NULL ) {
  current->setRight(otherchild);
  }
  if (currentchild != NULL) {
  currentchild->setRight(child);
  }
  //  cout << "Current " << current->getNumber() << endl;
  if (parent != NULL && currentchild != NULL && parent->getNumber() < currentchild->getNumber()) {
    parent->setRight(currentchild);
  }
  else if (parent != NULL && currentchild != NULL && parent->getNumber() > currentchild->getNumber()) {
    parent->setLeft(currentchild);
  }
  if (checkroot == true) {
    return currentchild;
  }
  else {
    return root;
  }

}

TreeNode* searchnode(TreeNode* root, int search) {
  if (root != NULL) {
  if (root->getNumber() == search) {
    cout << "Number is part of tree" << endl;
    return root;
  }
  else {
    while (root->getNumber() != search) {
      if (root->getLeft() != NULL) {
	if (root->getLeft()->getNumber() == search) {
	  cout << "Number is part of tree" << endl;
	  return root->getLeft();
	}
      }
      if (root->getRight() != NULL) {
	if (root->getRight()->getNumber() == search) {
	  cout << "Number is part of tree" << endl;
	  return root->getRight();
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
	return NULL;
      }
    }
  }
  // else {
      cout << "Number is not part of tree" << endl;
      return NULL;
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
  if (response == 4) {
    cout << "What node do you want to delete?" << endl;
    int deleter;
    cin >> deleter;
    TreeNode* todelete = searchnode(root, deleter);
    if (todelete != NULL) {
     remove(root, todelete);
    }
    print(root, 0);
    cout << "Next" << endl;
    cin >>response;
  }
  }
}
