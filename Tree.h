// Kristen Maggs and Amanda Todakonzie
// This is Tree.h. It can dynamically create and destroy a balanced
// threaded binary search tree of ints, print the tree, copy the tree into
// another tree, remove all evens as well as individual nodes, and clear it.

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <stack>

using namespace std;

class Tree;

class TreeNode {

  friend class Tree;

  // sends an tree to an ostream
  // pre: must be given a valid ostream and tree
  // post: sends the tree to the ostream in order
  friend ostream &operator<<(ostream &out, const Tree &tree);

private:

  // creates a new TreeNode
  // pre: must be given a valid int
  // post: creates a new TreeNode with the given data and all other values
  // set to nullptr/false
  explicit TreeNode(int data);

  int data;

  TreeNode * left;

  TreeNode * right;

  bool leftThread;

  bool rightThread;
};

class Tree {

  // sends an tree to an ostream
  // pre: must be given a valid ostream and tree
  // post: sends the tree to the ostream in order
  friend ostream &operator<<(ostream &out, const Tree &tree);

public:

  // creates a new Tree from another Tree
  // pre: must be given a valid binary Tree
  // post: copies that Tree into another new threaded binary tree
  explicit Tree(int n);

  // removes a Tree from memory
  // pre: none
  // post: removes a Tree from memory
  Tree(const Tree &other);

  virtual ~Tree();

  // removes all the even nodes from a Tree
  // pre: none
  // post: returns true and removes all the even nodes from a Tree or returns
  // false if not successful
  bool removeEven();

  // removes a node with data matching a given number
  // pre: must be given a valid int to find the node
  // post: removes the node if present and returns true or returns false if
  // the tree is empty or does not contain the given node
  bool remove(const int &target);

  // clears a Tree
  // pre: none
  // post: removes all nodes from the Tree
  void clear();

private:

  TreeNode * root;

  int n;

  // creates a balanced binary search Tree
  // pre: must be given two ints
  // post: creates a balanced tree of all ints ranging from the first int to
  // the second
  TreeNode * balancedTree(int min, int max);

  // adds right threads to the Tree
  // pre: none
  // post: adds right threads to all nodes with null right pointers and in
  // order successors
  void addRightThreads();

  // adds left threads to the Tree
  // pre: none
  // post: adds left threads to all nodes with null right pointers and in order
  // successors
  void addLeftThreads();

  // copies a Tree
  // pre: must be given a TreeNode for the root to start copying
  // post: copies the other Tree starting at the node given and returns a new
  // node for the new Tree's root
  TreeNode * copyTree(TreeNode * node);

  // removes a node from the Tree
  // pre: must be given two node pointers: one for the node to be removed and
  // one for its parent
  // post: removes the given node from the tree and returns true if successful
  // or false if unsuccessful
  bool removeHelper(TreeNode * curr, TreeNode * prev);

  // deletes a node and all its descendants
  // pre: must be given a node pointer for the parent node
  // post: removes all the descendant nodes of a given node from the Tree
  void destroy (TreeNode * root);
};

#endif