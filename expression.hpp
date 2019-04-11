#pragma once

#include <string>
using std::string;

class Expression {
public:
  // parse expression from string
  Expression(string);

  static string infixToPostfix(string);
};