// Kristen Maggs and Amanda Todakonzie
// This is Tree.cpp. It can dynamically create and destroy a balanced
// threaded binary search tree of ints, print the tree, copy the tree into
// another tree, remove all evens as well as individual nodes, and clear it.

#include <cassert>
#include <iostream>
#include <stack>

#include "Tree.h"

using namespace std;

// sends an tree to an ostream
// pre: must be given a valid ostream and tree
// post: sends the tree to the ostream in order
ostream &operator<<(ostream &out, const Tree &tree) {
  TreeNode *prev = tree.root;
  TreeNode *curr = tree.root;
  while (curr != nullptr) {
    while (curr->left != nullptr && !curr->leftThread) {
      curr = curr->left;
      prev = curr;
    }
    while (
        curr != nullptr &&
        (curr->rightThread || curr->left == nullptr ||
         curr->left->data <= prev->data)) { // got rid of curr->right == nullptr
      prev = curr;
      curr = curr->right;
      out << prev->data << " ";
    }
  }
  return out;
}

// creates a new TreeNode
// pre: must be given a valid int
// post: creates a new TreeNode with the given data and all other values
// set to nullptr/false
TreeNode::TreeNode(int data) : data{data} {
  this->left = nullptr;
  this->right = nullptr;
  this->leftThread = false;
  this->rightThread = false;
}

// creates a new Tree
// pre: must be given a valid positive int
// post: creates a new binary threaded search Tree containing ints from 1 to n
Tree::Tree(int n) {
  assert(n > 0);
  this->n = n;
  root = balancedTree(1, n);
  addRightThreads();
  addLeftThreads();
}

// creates a new Tree from another Tree
// pre: must be given a valid binary Tree
// post: copies that Tree into another new threaded binary tree
Tree::Tree(const Tree &other) {
  this->root = copyTree(other.root);
  this->n = other.n;
  addRightThreads();
  addLeftThreads();
}

// removes a Tree from memory
// pre: none
// post: removes a Tree from memory
Tree::~Tree() {
  destroy(root);
  root = nullptr;
}

// removes all the even nodes from a Tree
// pre: none
// post: returns true and removes all the even nodes from a Tree or returns
// false if not successful
bool Tree::removeEven() {
  for (int i = 1; i <= n; i++) {
    if (i % 2 == 0) { // if no remainder, then i is even number
      if (!remove(i)) {
        return false;
      }
    }
  }
  return true;
}

// removes a node with data matching a given number
// pre: must be given a valid int to find the node
// post: removes the node if present and returns true or returns false if
// the tree is empty or does not contain the given node
bool Tree::remove(const int &target) {
  TreeNode *curr = root;
  TreeNode *prev = nullptr;
  while (curr != nullptr &&
         ((!curr->leftThread && curr->left != nullptr) ||
          (!curr->rightThread && curr->right != nullptr)) &&
         curr->data != target) { // not sure this should be and since some have
                                 // only left or only right
    if (target < curr->data) {
      prev = curr;
      curr = curr->left;
    } else {
      prev = curr;
      curr = curr->right;
    }
  }
  if (curr == nullptr || curr->data != target) {
    return false;
  } else {
    bool result = removeHelper(curr, prev);
    return result;
  }
}

// clears a Tree
// pre: none
// post: removes all nodes from the Tree
void Tree::clear() {
  destroy(root);
  root = nullptr;
}

// creates a balanced binary search Tree
// pre: must be given two ints
// post: creates a balanced tree of all ints ranging from the first int to
// the second
TreeNode *Tree::balancedTree(int min, int max) {
  if (min > max) {
    return nullptr;
  } else {
    int midpoint = (min + max) / 2;
    TreeNode *node = new TreeNode(midpoint);
    node->left = balancedTree(min, midpoint - 1);
    node->right = balancedTree(midpoint + 1, max);
    return node;
  }
}

// adds right threads to the Tree
// pre: none
// post: adds right threads to all nodes with null right pointers and in order
// successors
void Tree::addRightThreads() {
  stack<TreeNode *> nodeStack;
  TreeNode *curr = root;
  TreeNode *prev = root;
  if (root != nullptr) {
    nodeStack.push(curr);
  }
  while (!nodeStack.empty()) {
    while (curr != nullptr) {
      prev = curr;
      nodeStack.push(curr);
      curr = curr->left;
    }
    while (curr == nullptr || (curr->right == nullptr && !nodeStack.empty())) {
      curr = nodeStack.top();
      nodeStack.pop();
    }
    if (!nodeStack.empty() && curr->data > prev->data) {
      prev->right = curr;
      prev->rightThread = true;
    }
    curr = curr->right;
  }
}

// adds left threads to the Tree
// pre: none
// post: adds left threads to all nodes with null right pointers and in order
// successors
void Tree::addLeftThreads() {
  stack<TreeNode *> nodeStack;
  TreeNode *curr = root;
  TreeNode *prev = root;
  if (root != nullptr) {
    nodeStack.push(curr);
  }
  while (!nodeStack.empty()) {
    while (curr != nullptr) {
      prev = curr;
      nodeStack.push(curr);
      if (!curr->rightThread) {
        curr = curr->right;
      } else {
        curr = nullptr;
      }
    }
    while (curr == nullptr ||
           (curr->left == nullptr && prev->data <= curr->data &&
            !nodeStack.empty())) {
      curr = nodeStack.top();
      nodeStack.pop();
    }
    if (curr->data < prev->data) {
      prev->left = curr;
      prev->leftThread = true;
    }
    if (prev->left == curr) {
      prev = curr;
    }
    curr = curr->left;
  }
}

// copies a Tree
// pre: must be given a TreeNode for the root to start copying
// post: copies the other Tree starting at the node given and returns a new
// node for the new Tree's root
TreeNode *Tree::copyTree(TreeNode *node) {
  if (node != nullptr) {
    TreeNode *newNode = new TreeNode(node->data);
    if (!node->leftThread) {
      newNode->left = copyTree(node->left);
    }
    if (!node->rightThread) {
      newNode->right = copyTree(node->right);
    }
    return newNode;
  }
  return nullptr;
}

// removes a node from the Tree
// pre: must be given two node pointers: one for the node to be removed and
// one for its parent
// post: removes the given node from the tree and returns true if successful
// or false if unsuccessful
bool Tree::removeHelper(TreeNode *curr, TreeNode *prev) {
  if ((curr->leftThread || curr->left == nullptr) &&
      (curr->rightThread || curr->right == nullptr)) { // curr has no children
    if (curr == prev->left) {
      prev->left = curr->left;
      if (prev->left != nullptr) {
        prev->leftThread = true;
      }
    } else {
      prev->right = curr->right;
      if (prev->right != nullptr) {
        prev->rightThread = true;
      }
    }
    delete curr;
    return true;
  } else if (!curr->leftThread && !curr->rightThread && curr->left != nullptr &&
             curr->right != nullptr) { // curr has two children
    TreeNode *next = curr->right;
    TreeNode *nextPrev = curr;
    while (!next->leftThread) { // move left until next is in order successor
      nextPrev = next;
      next = next->left;
    }
    curr->data = next->data;
    return removeHelper(next, nextPrev);
  } else { // curr has one child
    TreeNode *next = nullptr;
    if (curr->leftThread || curr->right != nullptr) {
      next = curr->right;
    } else if (curr->rightThread || curr->left != nullptr) {
      next = curr->left;
    }
    if (prev == nullptr) { // delete root node
      root = next;
    } else if (curr == prev->left) {
      prev->left = next;
    } else {
      prev->right = next;
    }
    prev = curr->left; // set prev to in order predescesor
    if (!curr->leftThread) {
      while (prev != nullptr && !prev->rightThread) {
        prev = prev->right;
      }
    }
    next = curr->right; // seet next to in order successor
    if (!curr->rightThread) {
      while (next != nullptr && !next->leftThread) {
        next = next->left;
      }
    }
    if (!curr->leftThread && prev != nullptr) {
      prev->right = next;
    } else if (!curr->rightThread && next != nullptr) {
      next->left = prev;
    }
    delete curr;
    return true;
  }
}

// deletes a node and all its descendants
// pre: must be given a node pointer for the parent node
// post: removes all the descendant nodes of a given node from the Tree
void Tree::destroy(TreeNode *node) {
  if (node != nullptr) {
    if (!node->leftThread) {
      destroy(node->left);
    }
    if (!node->rightThread) {
      destroy(node->right);
    }
    delete node;
  }
}