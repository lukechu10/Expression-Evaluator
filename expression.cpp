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
    // if whitespace or end of string, push number value to stack
    if (this->postfixExpression[pos] == ' ' ||
        pos == this->postfixExpression.length() - 1) {
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

short int Expression::precedence(char &c) {
  switch (c) {
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
    return 2;
  case '(':
    return 10;
  default:
    return -1;
  }
}

string Expression::infixToPostfix(string infix) {
  // throw invalid_argument("test");
  string postfix = "";
  postfix.reserve(2 * infix.length()); // reserve memory to prevent allocation
  stack<char, vector<char>> opStack;

  for (int pos = 0; pos < infix.length(); pos++) {
    // number
    if (isdigit(infix[pos])) {
      string tempNum = "";
      while (isdigit(infix[pos]) || infix[pos] == '.') {
        tempNum += infix[pos];
        pos++;
      }
      // append number to end of postfix
      postfix.append(tempNum);
      postfix.push_back(' ');
      pos--;
    }

    // operator
    if (isOperator(infix[pos])) {
      // highest precedence
      // push without popping operators
      if (infix[pos] == '(')
        opStack.push(infix[pos]);

      // append operators until openning parenthesis is found
      // !opStack.empty()
      else if (infix[pos] == ')') {
        while (!opStack.empty()) {
          if (opStack.top() == '(') {
            break;
          } else {
            postfix.push_back(opStack.top());
            postfix.push_back(' ');
            opStack.pop();
          }
        }
        /*
// error
if (opStack.empty())
throw invalid_argument(
"Syntax Error: Missing matching opening parenthesis for closing "
"parenthesis.\n\tFound at pos " +
to_string(pos));
else
// pop '('
opStack.pop();
                */
      }

      // normal operator
      else {
        // pop until precedence is equal or bigger
        while (!opStack.empty() && /*smaller precedence than top of stack*/
               precedence(infix[pos]) <= precedence(opStack.top())) {

          postfix.push_back(opStack.top());
          postfix.push_back(' ');
          opStack.pop();
        }
        opStack.push(infix[pos]);
      }
    }
  }

  // clear stack
  while (!opStack.empty()) {
    postfix.push_back(opStack.top());
    postfix.push_back(' ');
    opStack.pop();
  }

  // remove redundant space
  postfix.pop_back();
  postfix.shrink_to_fit(); // save memory
  return postfix;
}