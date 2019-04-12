#include <iostream> // for testing

#include <cmath>
#include <stack>
#include <vector>
using namespace std;

#include "expression.hpp"

Expression::Expression(string str) { postfixExpression = str; }

string Expression::getPostfixString() { return this->postfixExpression; }

long double Expression::compute() {
  stack<long double, vector<long double>> numStack; // stack for number values
  string temp = ""; // temp string for storing values seperated by whitespace
  for (int pos = 0; pos < this->postfixExpression.length(); pos++) {
    // if whitespace, push number value to stack
    if (this->postfixExpression[pos] == ' ') {
      if (isdigit(temp[0]) || temp[0] == '-') {
        // push number to numStack
        numStack.push(stold(temp));
        // reset temp value
        temp = "";
      }
    }

    // if digit or period or negative number
    else if (isdigit(this->postfixExpression[pos]) ||
             this->postfixExpression[pos] == '.' ||
             /* negative number*/
             (this->postfixExpression[pos] == '-' &&
              isdigit(this->postfixExpression[pos + 1]))) {
      temp += this->postfixExpression[pos];
    }
    // if operator
    switch (this->postfixExpression[pos]) {
    case '+':
    case '-':
    case '/':
    case '*': {
      // make sure it is not a negative number
      if (isdigit(this->postfixExpression[pos + 1])) {
        break;
      }
      // make sure there are more than 2 numbers on stack
      if (numStack.size() < 2) {
        cout << "Error: Missing numbers\n";
        return NAN;
      }
      // save numbers to variables
      long double tempNum1 = numStack.top();
      numStack.pop();
      long double tempNum2 = numStack.top();
      numStack.pop();

      // uncomment for debug use

      // cout << "Computing " << tempNum2 << " " << this->postfixExpression[pos]
      // << " " << tempNum1 << endl; select operator

      switch (this->postfixExpression[pos]) {
      case '+':
        numStack.push(tempNum1 + tempNum2);
        break;
      case '-':
        numStack.push(tempNum2 - tempNum1);
        break;
      case '*':
        numStack.push(tempNum1 * tempNum2);
        break;
      case '/':
        numStack.push(tempNum2 / tempNum1);
        break;
      }
    }
    default:
      break;
    }
  }
  // make sure stack is empty
  if (numStack.size() != 1) {
    cout << "Error: Missing operators\n";
    return NAN;
  }
  return numStack.top();
}