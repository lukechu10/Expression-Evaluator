#include <iostream>
#include <cmath>
#include <string>
using namespace std;
#include "expression.hpp"

int main() {
  cout << "expression parser v0.0.1\n";
  cout << "Type any expression in postfix notation. Type \"exit\" to exit.\n";

  while (true) {
    string temp;
    cout << ">>>";
    getline(cin, temp);
    if (temp == "exit") {
      break;
    }
    // check if no input
    if (temp == "") {
      continue;
    }
    long double tempResult = Expression(temp).compute(); // compute string

    // make sure result is NAN
    if (tempResult != tempResult) {
      continue;
    }
    // print result
    else {
      cout << "Result: " << tempResult << endl;
    }
  }
  return 0;
}