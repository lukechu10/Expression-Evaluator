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

    // if whitespace, push read value to stack
    if (this->postfixExpression[pos] == ' ') {
      if (isdigit(temp[0]) || temp[0] == '-') {
        // push number to numStack
        numStack.push(stold(temp));
        cout << "numStack.top(): " << numStack.top() << endl;
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
      // save numbers to variables
      long double tempNum1 = numStack.top();
      numStack.pop();
      long double tempNum2 = numStack.top();
      numStack.pop();

      cout << "1: " << tempNum1 << "\t2: " << tempNum2 << endl;
      // select operator
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
        numStack.push(tempNum1 / tempNum2);
        break;
      }
    }
    default:
      break;
    }
  }
  cout << "Stack size: " << numStack.size() << endl;
  return numStack.top();
}