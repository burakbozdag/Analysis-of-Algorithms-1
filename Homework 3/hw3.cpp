//Burak Bozdag
//150170110
//Note: In hw3.h file, you missed a semicolon (;) after the struct declaration!


#include <iostream>
#include "hw3.h"

using namespace std;

struct Node
{
  int size;
  int ordinal;
  int occur;
  Node *parent;
  Node *left;
  Node *right;
  char color;
};

class rbTree
{
private:
  Node* root;
  Node* NIL;
  HW3_Result result;

  void preOrderHelper(Node* node) //Counting nodes using pre order traversal
  {
    if (node != NIL)
    {
      ++result.packageCount;
      if(node->color == 'r') ++result.redNodeCount;
      else ++result.blackNodeCount;
      preOrderHelper(node->left);
      preOrderHelper(node->right);
    }
  };

  Node* searchTreeHelper(Node* node, int key) //Searching
  {
    if (node == NIL || key == node->size) return node;
    if (key < node->size) return searchTreeHelper(node->left, key);
    return searchTreeHelper(node->right, key);
  };

  void deleteFix(Node* x) //Fixing violations after deleting
  {
    Node* s;
    while (x != root && x->color == 'b')
    {
      if (x == x->parent->left)
      {
        s = x->parent->right;
        if (s->color == 'r')
        {
          s->color = 'b';
          x->parent->color = 'r';
          rotateLeft(x->parent);
          s = x->parent->right;
        }
        if (s->left->color == 'b' && s->right->color == 'b')
        {
          s->color = 'r';
          x = x->parent;
        }
        else
        {
          if (s->right->color == 'b')
          {
            s->left->color = 'b';
            s->color = 'r';
            rotateRight(s);
            s = x->parent->right;
          }
          s->color = x->parent->color;
          x->parent->color = 'b';
          s->right->color = 'b';
          rotateLeft(x->parent);
          x = root;
        }
      }
      else
      {
        s = x->parent->left;
        if (s->color == 'r')
        {
          s->color = 'b';
          x->parent->color = 'r';
          rotateRight(x->parent);
          s = x->parent->left;
        }
          if (s->right->color == 'b') {
              if (s->right->color == 'b') {
                  s->color = 'r';
                  x = x->parent;
              } else {
                  if (s->left->color == 'b') {
                      s->right->color = 'b';
                      s->color = 'r';
                      rotateLeft(s);
                      s = x->parent->left;
                  }
                  s->color = x->parent->color;
                  x->parent->color = 'b';
                  s->left->color = 'b';
                  rotateRight(x->parent);
                  x = root;
              }
          } else {
              if (s->left->color == 'b') {
                  s->right->color = 'b';
                  s->color = 'r';
                  rotateLeft(s);
                  s = x->parent->left;
              }
              s->color = x->parent->color;
              x->parent->color = 'b';
              s->left->color = 'b';
              rotateRight(x->parent);
              x = root;
          }
      }
    }
    x->color = 'b';
  };

  void rbTransplant(Node* u, Node* v)
  {
    if (u->parent == NULL) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
  };

  void deleteNodeHelper(Node* node, int key) //Deleting a node
  {
    Node* z = NIL;
    Node *x, *y;
    while (node != NIL)
    {
      if (node->size == key) z = node;
      if (node->size <= key) node = node->right;
      else node = node->left;
    }
    if (z == NIL) return;
    y = z;
    int y_original_color = y->color;
    if (z->left == NIL)
    {
      x = z->right;
      rbTransplant(z, z->right);
    }
    else if (z->right == NIL)
    {
      x = z->left;
      rbTransplant(z, z->left);
    }
    else
    {
      y = min(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z) x->parent = y;
      else
      {
        rbTransplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }
      rbTransplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    delete z;
    if (y_original_color == 'b') deleteFix(x);
  };

  void insertFix(Node* k) //Fixing violations after inserting
  {
    Node* u;
    while (k->parent->color == 'r')
    {
      if (k->parent == k->parent->parent->right)
      {
        u = k->parent->parent->left;
        if (u->color == 'r')
        {
          u->color = 'b';
          k->parent->color = 'b';
          k->parent->parent->color = 'r';
          k = k->parent->parent;
        }
        else
        {
          if (k == k->parent->left)
          {
            k = k->parent;
            rotateRight(k);
          }
          k->parent->color = 'b';
          k->parent->parent->color = 'r';
          rotateLeft(k->parent->parent);
        }
      }
      else
      {
        u = k->parent->parent->right;
        if (u->color == 'r')
        {
          u->color = 'b';
          k->parent->color = 'b';
          k->parent->parent->color = 'r';
          k = k->parent->parent;
        }
        else
        {
          if (k == k->parent->right)
          {
            k = k->parent;
            rotateLeft(k);
          }
          k->parent->color = 'b';
          k->parent->parent->color = 'r';
          rotateRight(k->parent->parent);
        }
      }
      if (k == root) break;
    }
    root->color = 'b';
  };

public:
  rbTree()
  {
    NIL = new Node;
    NIL->size = 0;
    NIL->ordinal = 0;
    NIL->occur = 0;
    NIL->color = 'b';
    NIL->parent = NIL;
    NIL->left = NULL;
    NIL->right = NULL;
    root = NIL;
    result.packageCount = 0;
    result.redNodeCount = 0;
    result.blackNodeCount = 0;
  };

  HW3_Result preOrder() //Counting nodes using pre order traversal
  {
    preOrderHelper(this->root);
    return result;
  };

  Node* searchTree(int k) //Searching
  {
    return searchTreeHelper(this->root, k);
  };

  Node* min(Node* node) //Returns the node with minimum size
  {
    while (node->left != NIL) node = node->left;
    return node;
  };

  Node* successor(Node* x) //Returns the successor of the node
  {
    if (x->right != NIL) return min(x->right);
    Node* y = x->parent;
    while (y != NIL && x == y->right)
    {
      x = y;
      y = y->parent;
    }
    return y;
  };

  void rotateLeft(Node* x) //Rotates left by given node
  {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) this->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
  };

  void rotateRight(Node* x) //Rotates right by given node
  {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) this->root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
  };

  void insert(int key, int ord) //Inserts a node
  {
    Node* node = new Node;
    node->parent = NULL;
    node->size = key;
    node->ordinal = ord;
    node->occur = 1;
    node->left = NIL;
    node->right = NIL;
    node->color = 'r';
    Node* y = NULL;
    Node* x = this->root;
    while (x != NIL)
    {
      y = x;
      if (node->size < x->size) x = x->left;
      else x = x->right;
    }
    node->parent = y;
    if (y == NULL) root = node;
    else if (node->size < y->size) y->left = node;
    else y->right = node;
    if (node->parent == NULL)
    {
      node->color = 'b';
      return;
    }
    if (node->parent->parent == NULL) return;
    insertFix(node);
  };

  Node* getRoot() //Returns the root of the tree
  {
    return this->root;
  };

  void deleteNode(int size) //Deletes a node
  {
    deleteNodeHelper(this->root, size);
  };
};

HW3_Result hw3(int eastWarehousePackageCount, int eastWarehousePackageSizes [],
int eastWarehousePackageOrdinals [], int westWarehousePackageCount,
int westWarehousePackageSizes [], int westWarehousePackageOrdinals [])
{
  rbTree east;
  for (int i = 0; i < eastWarehousePackageCount; ++i){
    Node* temp = east.searchTree(eastWarehousePackageSizes[i]);
    if(temp->size == 0)
      east.insert(eastWarehousePackageSizes[i], eastWarehousePackageOrdinals[i]);
    else{
      temp->occur += 1;
      if(temp->ordinal > eastWarehousePackageOrdinals[i])
        temp->ordinal = eastWarehousePackageOrdinals[i];
    }
  }

  rbTree west;
  for (int i = 0; i < westWarehousePackageCount; ++i){
    Node* temp = west.searchTree(westWarehousePackageSizes[i]);
    if(temp->size == 0)
      west.insert(westWarehousePackageSizes[i], westWarehousePackageOrdinals[i]);
    else{
      temp->occur += 1;
      if(temp->ordinal > westWarehousePackageOrdinals[i])
        temp->ordinal = westWarehousePackageOrdinals[i];
    }
  }

  Node* shipment = east.min(east.getRoot()); //Begins carrying from the east warehouse
  Node* small;
  char resultWarehouse;
  bool DNE;
  while (true)
  {
    //East -> West
    if(shipment == east.getRoot()){ //Checks if it is the last shipment
      Node temp = *shipment;
      east.deleteNode(shipment->size);
      Node* check = west.searchTree(temp.size);
      if(check->size == 0)
        west.insert(temp.size, temp.ordinal);
      else
        check->occur += 1;
      resultWarehouse = 'w';
      break;
    }

    int ord = shipment->ordinal;
    small = west.min(west.getRoot());
    DNE = false;
    for (int i = 0; i < ord - 1; ++i) { //ord. smallest package(s)
      if(small == west.getRoot()){
        DNE = true;
        break;
      }
      else small = west.successor(small);
    }
    if(DNE){ //ord. smallest package does not exist
      east.deleteNode(shipment->size); //Forwarded to smaller warehouses
      shipment = west.min(west.getRoot()); //Continues carrying the smallest package(s)
    }
    else{ //ord. smallest package exists
      Node temp = *shipment;
      east.deleteNode(shipment->size);
      Node* check = west.searchTree(temp.size);
      if(check->size == 0)
        west.insert(temp.size, temp.ordinal);
      else{
        check->occur += 1;
        if(check->ordinal > temp.ordinal)
          temp.ordinal = check->ordinal;
      }
      shipment = small;
    }

    //West -> East
    if(shipment == west.getRoot()){ //Checks if it is the last shipment
      Node temp = *shipment;
      west.deleteNode(shipment->size);
      Node* check = east.searchTree(temp.size);
      if(check->size == 0)
        east.insert(temp.size, temp.ordinal);
      else
        check->occur += 1;
      resultWarehouse = 'e';
      break;
    }

    ord = shipment->ordinal;
    small = east.min(east.getRoot());
    DNE = false;
    for (int i = 0; i < ord - 1; ++i) { //ord. smallest package(s)
      if(small == east.getRoot()){
        DNE = true;
        break;
      }
      else small = east.successor(small);
    }
    if(DNE){ //ord. smallest package does not exist
      west.deleteNode(shipment->size);
      shipment = east.min(east.getRoot()); //Continues carrying the smallest package(s)
    }
    else{ //ord. smallest package exists
      Node temp = *shipment;
      west.deleteNode(shipment->size);
      Node* check = east.searchTree(temp.size);
      if(check->size == 0)
        east.insert(temp.size, temp.ordinal);
      else{
        check->occur += 1;
        if(check->ordinal > temp.ordinal)
          temp.ordinal = check->ordinal;
      }
      shipment = small;
    }
  }

  HW3_Result results;
  if (resultWarehouse == 'e') results = east.preOrder();
  else results = west.preOrder();

  return results;
}
