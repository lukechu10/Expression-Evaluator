#include <iostream>
#include <cmath>
#include <string>
#include <exception>
#include <cstdlib> // abort()
using namespace std;
#include "expression.hpp"

void terminateHandler() {
  std::cerr << "An error occured\n";
  abort(); // forces abnormal termination
}

int main() {
  // set terminate handler
  std::set_terminate(terminateHandler);

  cout << "expression parser v0.0.1\n";
  cout << "Type any expression in postfix notation. Type \"exit\" to exit "
          "program.\n";

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
    try {
      Expression tempExpression(Expression::infixToPostfix(temp));
      // print result
      cout << "Postfix notation: " << tempExpression.getPostfixString() << endl;

      long double result = tempExpression.compute();
      cout << "= " << result << endl;

    } catch (exception &e) {
      cout << e.what() << endl;
    }
  }
  return 0;
}