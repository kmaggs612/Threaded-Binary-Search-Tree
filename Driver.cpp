// Kristen Maggs and Amanda Todakonzie
// This is TreeDriver.cpp. It demonstrates the methods of the Tree class.

#include "Tree.h"

using namespace std;

// prompts users for a positive number until it receives a valid one
// pre: user must eventually enter a valid positive number
// post: creates a tree of ints from 1 to that number, copies the tree, then
// removes all the even numbers from the copy, printing each step
int main() {
  int n;
  bool test = false;
  while (!test) {
    cout << "Please enter a positive number ";
    cout << "(decimals will be rounded down to the nearest integer):" << endl;
    cin >> n;
    if (n < 1) {
      cout << "Invalid number." << endl;
      cin.clear();
      cin.ignore();
    } else {
      test = true;
    }
  }
  Tree tr(n);
  cout << "Your tree: " << tr << endl;
  Tree tr2 = tr;
  cout << "A copy of your tree: " << tr2 << endl;
  tr2.removeEven();
  cout << "The copy after removing evens: " << tr2 << endl;
  return 0;
}