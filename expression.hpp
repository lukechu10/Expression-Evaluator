#pragma once

#include <string>
using std::string;

class Expression {
public:
  // parse expression from postfix string
  Expression(string str);

  string getPostfixString();
  long double compute();

  static string infixToPostfix(string);
  // returns if character is an operator
  static bool isOperator(char &c) {
    switch (c) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
      return true;
    default:
      return false;
    }
  }

private:
  string postfixExpression = "";
  static short int precedence(char &c);
};