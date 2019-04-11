#pragma once

#include <string>
using std::string;

class Expression {
public:
  // parse expression from postfix string
  Expression(string str);

  static string infixToPostfix(string);

  string getPostfixString();
  long double compute();

private:
  string postfixExpression = "";
};