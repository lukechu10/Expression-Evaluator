#include <iostream>
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
    cout << Expression(temp).compute() << endl;
  }
  return 0;
}